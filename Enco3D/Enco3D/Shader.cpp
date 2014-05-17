#include "Shader.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

const Enco3D::Rendering::Shader *Enco3D::Rendering::Shader::s_lastBind = nullptr;

Enco3D::Rendering::Shader::Shader()
{
	m_program = glCreateProgram();

	if (m_program == 0)
	{
		Core::DebugLogger::log("[ERROR] Failed to create shader program");
	}
}

Enco3D::Rendering::Shader::Shader(const string &filename, unsigned int shaderTypes)
{
	m_program = glCreateProgram();

	if (m_program == 0)
	{
		Core::DebugLogger::log("[ERROR] Failed to create shader program");
		return;
	}

	std::vector<std::string> shaderTexts;

	if ((shaderTypes & ShaderType::VertexShader) == ShaderType::VertexShader)
	{
		std::string shaderText = loadShader(filename + ".vs");
		addVertexShader(shaderText);
		shaderTexts.push_back(shaderText);
	}

	if ((shaderTypes & ShaderType::FragmentShader) == ShaderType::FragmentShader)
	{
		std::string shaderText = loadShader(filename + ".ps");
		addFragmentShader(shaderText);
		shaderTexts.push_back(shaderText);
	}

	if ((shaderTypes & ShaderType::GeometryShader) == ShaderType::GeometryShader)
	{
		std::string shaderText = loadShader(filename + ".gs");
		addGeometryShader(shaderText);
		shaderTexts.push_back(shaderText);
	}

	if ((shaderTypes & ShaderType::TessellationControlShader) == ShaderType::TessellationControlShader)
	{
		std::string shaderText = loadShader(filename + ".cs");
		addTessellationControlShader(shaderText);
		shaderTexts.push_back(shaderText);
	}

	if ((shaderTypes & ShaderType::TessellationEvaluationShader) == ShaderType::TessellationEvaluationShader)
	{
		std::string shaderText = loadShader(filename + ".es");
		addTessellationEvaluationShader(shaderText);
		shaderTexts.push_back(shaderText);
	}

	addAllAttributes(shaderTexts[0]);

	compileShader();

	for (unsigned int i = 0; i < shaderTexts.size(); i++)
	{
		addShaderUniforms(shaderTexts[i]);
	}
}

Enco3D::Rendering::Shader::Shader(const std::string &vertexFilename, const std::string &fragmentFilename)
{
	m_program = glCreateProgram();

	if (m_program == 0)
	{
		Core::DebugLogger::log("[ERROR] Failed to create shader program");
		return;
	}

	std::string vertexShaderText = loadShader(vertexFilename);
	std::string fragmentShaderText = loadShader(fragmentFilename);

	addVertexShader(vertexShaderText);
	addFragmentShader(fragmentShaderText);

	addAllAttributes(vertexShaderText);

	compileShader();

	addShaderUniforms(vertexShaderText);
	addShaderUniforms(fragmentShaderText);
}

Enco3D::Rendering::Shader::~Shader()
{
	for (std::vector<int>::iterator it = m_shaders.begin(); it != m_shaders.end(); it++)
	{
		glDetachShader(m_program, *it);
		glDeleteShader(*it);
	}

	glDeleteProgram(m_program);
}

void Enco3D::Rendering::Shader::addProgram(const string &text, int type)
{
	int shader = glCreateShader(type);

	if (shader == 0)
	{
		Core::DebugLogger::log("[ERROR] Failed creating shader type " + std::to_string(type));
		return;
	}

	const GLchar *p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];

		glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
		Core::DebugLogger::log("[ERROR] Failed to compile shader type " + std::to_string(type) + ":");
		Core::DebugLogger::log(infoLog);

		return;
	}

	glAttachShader(m_program, shader);
	m_shaders.push_back(shader);
}

string Enco3D::Rendering::Shader::loadShader(const string &filename)
{
	ifstream file;
	file.open(filename.c_str());

	string output, line;

	if (file.is_open())
	{
		Core::DebugLogger::log("Successfully loaded shader: " + filename);

		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		Core::DebugLogger::log("[ERROR] Failed to load shader: " + filename);
	}

	return output;
}

void Enco3D::Rendering::Shader::checkShaderError(int shader, int flag, bool isProgram, const string &errorMsg)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (!success)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), nullptr, error);
		else
			glGetProgramInfoLog(shader, sizeof(error), nullptr, error);

		Core::DebugLogger::log(errorMsg + ":");
		Core::DebugLogger::log(error);
	}
}

std::vector<Enco3D::Rendering::__UniformStruct> Enco3D::Rendering::Shader::findUniformStructs(const std::string &shaderText)
{
	static const std::string STRUCT_KEY = "struct";
	std::vector<__UniformStruct> result;

	size_t structLocation = shaderText.find(STRUCT_KEY);
	while (structLocation != std::string::npos)
	{
		structLocation += STRUCT_KEY.length() + 1;

		size_t braceOpening = shaderText.find("{", structLocation);
		size_t braceClosing = shaderText.find("}", braceOpening);

		__UniformStruct newStruct;
		newStruct.name = findUniformStructName(shaderText.substr(structLocation, braceOpening - structLocation));
		newStruct.memberNames = findUniformStructComponents(shaderText.substr(braceOpening, braceClosing - braceOpening));

		result.push_back(newStruct);
		structLocation = shaderText.find(STRUCT_KEY, structLocation);
	}

	return result;
}

static std::vector<std::string> __Split(const std::string &s, char delim)
{
	std::vector<std::string> elems;

	const char* cstr = s.c_str();
	unsigned int strLength = (unsigned int)s.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength)
	{
		while (end <= strLength)
		{
			if (cstr[end] == delim)
				break;
			end++;
		}

		elems.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}

std::string Enco3D::Rendering::Shader::findUniformStructName(const std::string &structStartToOpeningBrace)
{
	return __Split(__Split(structStartToOpeningBrace, ' ')[0], '\n')[0];
}

std::vector<Enco3D::Rendering::__TypedData> Enco3D::Rendering::Shader::findUniformStructComponents(const std::string &openingBraceToClosingBrace)
{
	static const char charsToIgnore[] = { ' ', '\n', '\t', '{' };
	static const size_t UNSIGNED_NEG_ONE = (size_t)-1;

	std::vector<__TypedData> result;
	std::vector<std::string> structLines = __Split(openingBraceToClosingBrace, ';');

	for (unsigned int i = 0; i < structLines.size(); i++)
	{
		size_t nameBegin = UNSIGNED_NEG_ONE;
		size_t nameEnd = UNSIGNED_NEG_ONE;

		for (unsigned int j = 0; j < structLines[i].length(); j++)
		{
			bool isIgnoreableCharacter = false;

			for (unsigned int k = 0; k < sizeof(charsToIgnore) / sizeof(char); k++)
			{
				if (structLines[i][j] == charsToIgnore[k])
				{
					isIgnoreableCharacter = true;
					break;
				}
			}

			if (nameBegin == UNSIGNED_NEG_ONE && !isIgnoreableCharacter)
				nameBegin = j;
			else if (nameBegin != UNSIGNED_NEG_ONE && isIgnoreableCharacter)
			{
				nameEnd = j;
				break;
			}
		}

		if (nameBegin == UNSIGNED_NEG_ONE || nameEnd == UNSIGNED_NEG_ONE)
			continue;

		__TypedData newData;
		newData.type = structLines[i].substr(nameBegin, nameEnd - nameBegin);
		newData.name = structLines[i].substr(nameEnd + 1);

		result.push_back(newData);
	}

	return result;
}

void Enco3D::Rendering::Shader::addAllAttributes(const std::string &vertexShaderText)
{
	static const std::string ATTRIBUTE_KEY = "attribute";

	int currentAttribLocation = 0;
	size_t attributeLocation = vertexShaderText.find(ATTRIBUTE_KEY);
	while (attributeLocation != std::string::npos)
	{
		bool isCommented = false;
		size_t lastLineEnd = vertexShaderText.rfind(";", attributeLocation);

		if (lastLineEnd != std::string::npos)
		{
			std::string potentialCommentSection = vertexShaderText.substr(lastLineEnd, attributeLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}

		if (!isCommented)
		{
			size_t begin = attributeLocation + ATTRIBUTE_KEY.length();
			size_t end = vertexShaderText.find(";", begin);

			std::string attributeLine = vertexShaderText.substr(begin + 1, end - begin - 1);

			begin = attributeLine.find(" ");
			std::string attributeName = attributeLine.substr(begin + 1);

			glBindAttribLocation(m_program, currentAttribLocation, attributeName.c_str());
			currentAttribLocation++;
		}

		attributeLocation = vertexShaderText.find(ATTRIBUTE_KEY, attributeLocation + ATTRIBUTE_KEY.length());
	}
}

void Enco3D::Rendering::Shader::addShaderUniforms(const std::string &shaderText)
{
	static const std::string UNIFORM_KEY = "uniform";

	std::vector<__UniformStruct> structs = findUniformStructs(shaderText);

	size_t uniformLocation = shaderText.find(UNIFORM_KEY);
	while (uniformLocation != std::string::npos)
	{
		bool isCommented = false;
		size_t lastLineEnd = shaderText.rfind(";", uniformLocation);

		if (lastLineEnd != std::string::npos)
		{
			std::string potentialCommentSection = shaderText.substr(lastLineEnd, uniformLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}

		if (!isCommented)
		{
			size_t begin = uniformLocation + UNIFORM_KEY.length();
			size_t end = shaderText.find(";", begin);

			std::string uniformLine = shaderText.substr(begin + 1, end - begin - 1);

			begin = uniformLine.find(" ");
			std::string uniformName = uniformLine.substr(begin + 1);
			std::string uniformType = uniformLine.substr(0, begin);

			m_uniformNames.push_back(uniformName);
			m_uniformTypes.push_back(uniformType);
			addUniform(uniformName, uniformType, structs);
		}

		uniformLocation = shaderText.find(UNIFORM_KEY, uniformLocation + UNIFORM_KEY.length());
	}
}

void Enco3D::Rendering::Shader::addUniform(const std::string &uniformName, const std::string &uniformType, const std::vector<Enco3D::Rendering::__UniformStruct>& structs)
{
	bool addThis = true;

	for (unsigned int i = 0; i < structs.size(); i++)
	{
		if (structs[i].name.compare(uniformType) == 0)
		{
			addThis = false;
			for (unsigned int j = 0; j < structs[i].memberNames.size(); j++)
				addUniform(uniformName + "." + structs[i].memberNames[j].name, structs[i].memberNames[j].type, structs);
		}
	}

	if (!addThis)
		return;

	unsigned int location = glGetUniformLocation(m_program, uniformName.c_str());
	assert(location != 0xFFFFFFFF);
	m_uniformMap.insert(std::pair<std::string, unsigned int>(uniformName, location));
}

void Enco3D::Rendering::Shader::bind() const
{
	if (s_lastBind != this)
	{
		glUseProgram(m_program);
		s_lastBind = this;
	}
}

void Enco3D::Rendering::Shader::addVertexShader(const string &text)
{
	addProgram(text, GL_VERTEX_SHADER);
}

void Enco3D::Rendering::Shader::addFragmentShader(const string &text)
{
	addProgram(text, GL_FRAGMENT_SHADER);
}

void Enco3D::Rendering::Shader::addGeometryShader(const string &text)
{
	addProgram(text, GL_GEOMETRY_SHADER);
}

void Enco3D::Rendering::Shader::addTessellationControlShader(const string &text)
{
	addProgram(text, GL_TESS_CONTROL_SHADER);
}

void Enco3D::Rendering::Shader::addTessellationEvaluationShader(const string &text)
{
	addProgram(text, GL_TESS_EVALUATION_SHADER);
}

void Enco3D::Rendering::Shader::addVertexShaderFromFile(const string &filename)
{
	addVertexShader(loadShader(filename));
}

void Enco3D::Rendering::Shader::addFragmentShaderFromFile(const string &filename)
{
	addFragmentShader(loadShader(filename));
}

void Enco3D::Rendering::Shader::addGeometryShaderFromFile(const string &filename)
{
	addGeometryShader(loadShader(filename));
}

void Enco3D::Rendering::Shader::addTessellationControlShaderFromFile(const string &filename)
{
	addTessellationControlShader(loadShader(filename));
}

void Enco3D::Rendering::Shader::addTessellationEvaluationShaderFromFile(const string &filename)
{
	addTessellationEvaluationShader(loadShader(filename));
}

void Enco3D::Rendering::Shader::compileShader()
{
	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "[ERROR] Failed to link shader program");

	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "[ERROR] Invalid shader program");
}

void Enco3D::Rendering::Shader::setAttribLocation(const string &attributeName, int location)
{
	glBindAttribLocation(m_program, location, attributeName.c_str());
}

void Enco3D::Rendering::Shader::setUniformInt(const string &name, int value)
{
	glUniform1i(m_uniformMap.at(name), value);
}

void Enco3D::Rendering::Shader::setUniformFloat(const string &name, float value)
{
	glUniform1f(m_uniformMap.at(name), value);
}

void Enco3D::Rendering::Shader::setUniformVector2f(const string &name, const Enco3D::Core::Vector2f &v)
{
	glUniform2f(m_uniformMap.at(name), v.x, v.y);
}

void Enco3D::Rendering::Shader::setUniformVector3f(const string &name, const Enco3D::Core::Vector3f &v)
{
	glUniform3f(m_uniformMap.at(name), v.x, v.y, v.z);
}

void Enco3D::Rendering::Shader::setUniformVector4f(const string &name, const Enco3D::Core::Vector4f &v)
{
	glUniform4f(m_uniformMap.at(name), v.x, v.y, v.z, v.w);
}

void Enco3D::Rendering::Shader::setUniformMatrix3x3f(const string &name, const Enco3D::Core::Matrix3x3f &v)
{
	glUniformMatrix3fv(m_uniformMap.at(name), 1, GL_TRUE, (const GLfloat *)v.m);
}

void Enco3D::Rendering::Shader::setUniformMatrix4x4f(const string &name, const Enco3D::Core::Matrix4x4f &v)
{
	glUniformMatrix4fv(m_uniformMap.at(name), 1, GL_TRUE, (const GLfloat *)v.m);
}

void Enco3D::Rendering::Shader::setUniformDirectionalLight(const string &name, const Enco3D::Component::DirectionalLight *directionalLight)
{
	setUniformVector3f(name + ".color", directionalLight->getColor());
	setUniformFloat(name + ".intensity", directionalLight->getIntensity());
	setUniformVector3f(name + ".direction", directionalLight->getTransform()->getRotation().getForward());
}

void Enco3D::Rendering::Shader::setUniformPointLight(const string &name, const Enco3D::Component::PointLight *pointLight)
{
	setUniformVector3f(name + ".color", pointLight->getColor());
	setUniformFloat(name + ".intensity", pointLight->getIntensity());
	setUniformVector3f(name + ".position", pointLight->getTransform()->getTranslation());
	setUniformFloat(name + ".range", pointLight->getRange());
}

void Enco3D::Rendering::Shader::setUniformSpotLight(const string &name, const Enco3D::Component::SpotLight *spotLight)
{
	setUniformVector3f(name + ".color", spotLight->getColor());
	setUniformFloat(name + ".intensity", spotLight->getIntensity());
	setUniformVector3f(name + ".position", spotLight->getTransform()->getTranslation());
	setUniformVector3f(name + ".direction", spotLight->getTransform()->getRotation().getForward());
	setUniformFloat(name + ".range", spotLight->getRange());
	setUniformFloat(name + ".cutoff", spotLight->getCutoff());
}

void Enco3D::Rendering::Shader::updateUniforms(Enco3D::Core::Transform *transform, const Enco3D::Component::Camera *camera, Enco3D::Rendering::RenderingEngine *renderingEngine, Enco3D::Rendering::Material *material)
{
	Core::Matrix4x4f worldMatrix = transform->getTransformation();
	Core::Matrix4x4f worldViewMatrix = camera->getView() * worldMatrix;
	Core::Matrix4x4f worldViewProjectionMatrix = camera->getViewProjection() * worldMatrix;
	Core::Matrix4x4f viewProjectionMatrix = camera->getViewProjection();

	Core::Matrix4x4f prevWorldMatrix = transform->getPrevTransformation();
	Core::Matrix4x4f prevWorldViewMatrix = camera->getPrevView() * prevWorldMatrix;
	Core::Matrix4x4f prevWorldViewProjectionMatrix = camera->getPrevViewProjection() * prevWorldMatrix;
	Core::Matrix4x4f prevViewProjectionMatrix = camera->getPrevViewProjection();

	Core::Matrix4x4f rotationMatrix = camera->getRotationMatrix();
	Core::Matrix4x4f rotationProjectionMatrix = camera->getProjection() * rotationMatrix;

	Core::Matrix4x4f inverseProjectionMatrix = camera->getInverseProjection();
	Core::Matrix4x4f inverseViewMatrix = camera->getInverseView();
	Core::Matrix4x4f inverseViewProjectionMatrix = camera->getInverseViewProjection();

	for (unsigned int i = 0; i < m_uniformNames.size(); i++)
	{
		std::string uniformName = m_uniformNames[i];
		std::string uniformType = m_uniformTypes[i];

		if (uniformName == "matrix_worldMatrix")
			setUniformMatrix4x4f(uniformName, worldMatrix);
		else if (uniformName == "matrix_worldViewMatrix")
			setUniformMatrix4x4f(uniformName, worldViewMatrix);
		else if (uniformName == "matrix_worldViewProjectionMatrix")
			setUniformMatrix4x4f(uniformName, worldViewProjectionMatrix);
		else if (uniformName == "matrix_viewProjectionMatrix")
			setUniformMatrix4x4f(uniformName, viewProjectionMatrix);
		else if (uniformName == "matrix_prevWorldMatrix")
			setUniformMatrix4x4f(uniformName, prevWorldMatrix);
		else if (uniformName == "matrix_prevWorldViewMatrix")
			setUniformMatrix4x4f(uniformName, prevWorldViewMatrix);
		else if (uniformName == "matrix_prevWorldViewProjectionMatrix")
			setUniformMatrix4x4f(uniformName, prevWorldViewProjectionMatrix);
		else if (uniformName == "matrix_prevViewProjectionMatrix")
			setUniformMatrix4x4f(uniformName, prevViewProjectionMatrix);
		else if (uniformName == "matrix_rotationMatrix")
			setUniformMatrix4x4f(uniformName, rotationMatrix);
		else if (uniformName == "matrix_rotationProjectionMatrix")
			setUniformMatrix4x4f(uniformName, rotationProjectionMatrix);
		else if (uniformName == "matrix_inverseProjectionMatrix")
			setUniformMatrix4x4f(uniformName, inverseProjectionMatrix);
		else if (uniformName == "matrix_inverseViewMatrix")
			setUniformMatrix4x4f(uniformName, inverseViewMatrix);
		else if (uniformName == "matrix_inverseViewProjectionMatrix")
			setUniformMatrix4x4f(uniformName, inverseViewProjectionMatrix);
		else if (uniformName == "camera_translation")
			setUniformVector3f(uniformName, camera->getTransform()->getTranslation());
		else if (uniformName == "rendering_globalAmbientLightColor")
			setUniformVector3f(uniformName, renderingEngine->getGlobalAmbientColor());
		else if (uniformName == "rendering_zNearClippingPlane")
			setUniformFloat(uniformName, renderingEngine->getZNearClippingPlane());
		else if (uniformName == "rendering_zFarClippingPlane")
			setUniformFloat(uniformName, renderingEngine->getZFarClippingPlane());
		else if (uniformName == "rendering_skybox")
		{
			if (renderingEngine->getSkybox() != nullptr)
			{
				renderingEngine->getSkybox()->getTexture()->bind(1);
				setUniformInt(uniformName, 1);
			}
		}

		if (uniformName.substr(0, 4) == "mat_")
		{
			string matComponentName = uniformName.substr(4, uniformName.size() - 4);
			if (uniformType == "float")
				setUniformFloat(uniformName, material->getFloat(matComponentName));
			else if (uniformType == "vec3")
				setUniformVector3f(uniformName, material->getVector3f(matComponentName));
			else if (uniformType == "sampler2D")
			{
				material->getTexture2D(matComponentName)->bind(TextureSampler::Sampler0);
				setUniformInt(uniformName, 0);
			}
		}

		if (uniformType == "DirectionalLight")
			setUniformDirectionalLight(uniformName, (Component::DirectionalLight*)renderingEngine->getActiveLight());
		else if (uniformType == "PointLight")
			setUniformPointLight(uniformName, (Component::PointLight*)renderingEngine->getActiveLight());
		else if (uniformType == "SpotLight")
			setUniformSpotLight(uniformName, (Component::SpotLight*)renderingEngine->getActiveLight());
	}
}