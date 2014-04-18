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
		cout << "[ERROR] Failed to create shader program" << endl;
	}
}

Enco3D::Rendering::Shader::Shader(const string &filename, unsigned int shaderTypes)
{
	m_program = glCreateProgram();

	if (m_program == 0)
	{
		cerr << "[ERROR] Failed to create shader program" << endl;
		return;
	}

	std::vector<std::string> shaderTexts;

	if ((shaderTypes & ShaderType::VertexShader) == ShaderType::VertexShader)
	{
		std::string shaderText = LoadShader(filename + ".vs");
		AddVertexShader(shaderText);
		shaderTexts.push_back(shaderText);
	}

	if ((shaderTypes & ShaderType::FragmentShader) == ShaderType::FragmentShader)
	{
		std::string shaderText = LoadShader(filename + ".fs");
		AddFragmentShader(shaderText);
		shaderTexts.push_back(shaderText);
	}

	if ((shaderTypes & ShaderType::GeometryShader) == ShaderType::GeometryShader)
	{
		std::string shaderText = LoadShader(filename + ".gs");
		AddGeometryShader(shaderText);
		shaderTexts.push_back(shaderText);
	}

	if ((shaderTypes & ShaderType::TessellationControlShader) == ShaderType::TessellationControlShader)
	{
		std::string shaderText = LoadShader(filename + ".cs");
		AddTessellationControlShader(shaderText);
		shaderTexts.push_back(shaderText);
	}

	if ((shaderTypes & ShaderType::TessellationEvaluationShader) == ShaderType::TessellationEvaluationShader)
	{
		std::string shaderText = LoadShader(filename + ".es");
		AddTessellationEvaluationShader(shaderText);
		shaderTexts.push_back(shaderText);
	}
	
	AddAllAttributes(shaderTexts[0]);

	CompileShader();

	for (unsigned int i = 0; i < shaderTexts.size(); i++)
	{
		AddShaderUniforms(shaderTexts[i]);
	}
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

void Enco3D::Rendering::Shader::AddProgram(const string &text, int type)
{
	int shader = glCreateShader(type);

	if (shader == 0)
	{
		cout << "[ERROR] Failed creating shader type " << type << endl;
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
		cout << "[ERROR] Failed to compile shader type " << type << ":" << endl;
		cout << infoLog << endl;

		return;
	}

	glAttachShader(m_program, shader);
	m_shaders.push_back(shader);
}

string Enco3D::Rendering::Shader::LoadShader(const string &filename)
{
	ifstream file;
	file.open(filename.c_str());
	
	string output, line;

	if (file.is_open())
	{
		cout << "Successfully loaded shader: " << filename << endl;
	
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		cout << "[ERROR] Failed to load shader: " << filename << endl;
	}

	return output;
}

void Enco3D::Rendering::Shader::CheckShaderError(int shader, int flag, bool isProgram, const string &errorMsg)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (!success)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), nullptr, error);
		}
		else
		{
			glGetProgramInfoLog(shader, sizeof(error), nullptr, error);
		}

		cout << errorMsg << ":" << endl;
		cout << error << endl;
	}
}

std::vector<Enco3D::Rendering::__UniformStruct> Enco3D::Rendering::Shader::FindUniformStructs(const std::string &shaderText)
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
		newStruct.name = FindUniformStructName(shaderText.substr(structLocation, braceOpening - structLocation));
		newStruct.memberNames = FindUniformStructComponents(shaderText.substr(braceOpening, braceClosing - braceOpening));

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

std::string Enco3D::Rendering::Shader::FindUniformStructName(const std::string &structStartToOpeningBrace)
{
	return __Split(__Split(structStartToOpeningBrace, ' ')[0], '\n')[0];
}

std::vector<Enco3D::Rendering::__TypedData> Enco3D::Rendering::Shader::FindUniformStructComponents(const std::string &openingBraceToClosingBrace)
{
	static const char charsToIgnore[] = {' ', '\n', '\t', '{'};
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
			{
				nameBegin = j;
			}
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

void Enco3D::Rendering::Shader::AddAllAttributes(const std::string &vertexShaderText)
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

void Enco3D::Rendering::Shader::AddShaderUniforms(const std::string &shaderText)
{
	static const std::string UNIFORM_KEY = "uniform";

	std::vector<__UniformStruct> structs = FindUniformStructs(shaderText);

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
			AddUniform(uniformName, uniformType, structs);
		}

		uniformLocation = shaderText.find(UNIFORM_KEY, uniformLocation + UNIFORM_KEY.length());
	}
}

void Enco3D::Rendering::Shader::AddUniform(const std::string &uniformName, const std::string &uniformType, const std::vector<Enco3D::Rendering::__UniformStruct>& structs)
{
	bool addThis = true;

	for (unsigned int i = 0; i < structs.size(); i++)
	{
		if (structs[i].name.compare(uniformType) == 0)
		{
			addThis = false;
			for (unsigned int j = 0; j < structs[i].memberNames.size(); j++)
			{
				AddUniform(uniformName + "." + structs[i].memberNames[j].name, structs[i].memberNames[j].type, structs);
			}
		}
	}

	if (!addThis)
		return;

	unsigned int location = glGetUniformLocation(m_program, uniformName.c_str());
	assert(location != INVALID_VALUE);
	m_uniformMap.insert(std::pair<std::string, unsigned int>(uniformName, location));
}

void Enco3D::Rendering::Shader::Bind() const
{
	if (s_lastBind != this)
	{
		glUseProgram(m_program);
		s_lastBind = this;
	}
}

void Enco3D::Rendering::Shader::AddVertexShader(const string &text)
{
	AddProgram(text, GL_VERTEX_SHADER);
}

void Enco3D::Rendering::Shader::AddFragmentShader(const string &text)
{
	AddProgram(text, GL_FRAGMENT_SHADER);
}

void Enco3D::Rendering::Shader::AddGeometryShader(const string &text)
{
	AddProgram(text, GL_GEOMETRY_SHADER);
}

void Enco3D::Rendering::Shader::AddTessellationControlShader(const string &text)
{
	AddProgram(text, GL_TESS_CONTROL_SHADER);
}

void Enco3D::Rendering::Shader::AddTessellationEvaluationShader(const string &text)
{
	AddProgram(text, GL_TESS_EVALUATION_SHADER);
}

void Enco3D::Rendering::Shader::AddVertexShaderFromFile(const string &filename)
{
	AddVertexShader(LoadShader(filename));
}

void Enco3D::Rendering::Shader::AddFragmentShaderFromFile(const string &filename)
{
	AddFragmentShader(LoadShader(filename));
}

void Enco3D::Rendering::Shader::AddGeometryShaderFromFile(const string &filename)
{
	AddGeometryShader(LoadShader(filename));
}

void Enco3D::Rendering::Shader::AddTessellationControlShaderFromFile(const string &filename)
{
	AddTessellationControlShader(LoadShader(filename));
}

void Enco3D::Rendering::Shader::AddTessellationEvaluationShaderFromFile(const string &filename)
{
	AddTessellationEvaluationShader(LoadShader(filename));
}

void Enco3D::Rendering::Shader::CompileShader()
{
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "[ERROR] Failed to link shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "[ERROR] Invalid shader program");
}

void Enco3D::Rendering::Shader::SetAttribLocation(const string &attributeName, int location)
{
	glBindAttribLocation(m_program, location, attributeName.c_str());
}

void Enco3D::Rendering::Shader::SetUniformInt(const string &name, int value)
{
	glUniform1i(m_uniformMap.at(name), value);
}

void Enco3D::Rendering::Shader::SetUniformFloat(const string &name, float value)
{
	glUniform1f(m_uniformMap.at(name), value);
}

void Enco3D::Rendering::Shader::SetUniformVector2f(const string &name, const Enco3D::Core::Vector2f &v)
{
	glUniform2f(m_uniformMap.at(name), v.x, v.y);
}

void Enco3D::Rendering::Shader::SetUniformVector3f(const string &name, const Enco3D::Core::Vector3f &v)
{
	glUniform3f(m_uniformMap.at(name), v.x, v.y, v.z);
}

void Enco3D::Rendering::Shader::SetUniformVector4f(const string &name, const Enco3D::Core::Vector4f &v)
{
	glUniform4f(m_uniformMap.at(name), v.x, v.y, v.z, v.w);
}

void Enco3D::Rendering::Shader::SetUniformMatrix3x3f(const string &name, const Enco3D::Core::Matrix3x3f &v)
{
	glUniformMatrix3fv(m_uniformMap.at(name), 1, GL_TRUE, (const GLfloat *)v.m);
}

void Enco3D::Rendering::Shader::SetUniformMatrix4x4f(const string &name, const Enco3D::Core::Matrix4x4f &v)
{
	glUniformMatrix4fv(m_uniformMap.at(name), 1, GL_TRUE, (const GLfloat *)v.m);
}

void Enco3D::Rendering::Shader::SetUniformDirectionalLight(const string &name, const Enco3D::Component::DirectionalLight *directionalLight)
{
	SetUniformVector3f(name + ".color", directionalLight->GetColor());
	SetUniformFloat(name + ".intensity", directionalLight->GetIntensity());
	SetUniformVector3f(name + ".direction", directionalLight->GetTransform()->GetRotation().GetForward());
}

void Enco3D::Rendering::Shader::SetUniformPointLight(const string &name, const Enco3D::Component::PointLight *pointLight)
{
	SetUniformVector3f(name + ".color", pointLight->GetColor());
	SetUniformFloat(name + ".intensity", pointLight->GetIntensity());
	SetUniformVector3f(name + ".position", pointLight->GetTransform()->GetTranslation());
	SetUniformFloat(name + ".range", pointLight->GetRange());
}

void Enco3D::Rendering::Shader::SetUniformSpotLight(const string &name, const Enco3D::Component::SpotLight *spotLight)
{
	SetUniformVector3f(name + ".color", spotLight->GetColor());
	SetUniformFloat(name + ".intensity", spotLight->GetIntensity());
/*	SetUniformVector3f(name + ".position", spotLight->GetTransform()->GetTranslation());
	SetUniformVector3f(name + ".direction", spotLight->GetTransform()->GetRotation().GetForward());
	SetUniformFloat(name + ".range", spotLight->GetRange());*/
	SetUniformFloat(name + ".cutoff", spotLight->GetCutoff());
}

void Enco3D::Rendering::Shader::UpdateUniforms(Enco3D::Core::Transform *transform, const Enco3D::Component::Camera *camera, Enco3D::Rendering::RenderingEngine *renderingEngine, Enco3D::Rendering::Material *material)
{
	Matrix4x4f worldMatrix = transform->GetTransformation();
	Matrix4x4f projectedMatrix = renderingEngine->GetViewProjectedMatrix(camera, worldMatrix);
	Matrix4x4f cameraMatrix = camera->GetViewProjection();

	for (unsigned int i = 0; i < m_uniformNames.size(); i++)
	{
		std::string uniformName = m_uniformNames[i];
		std::string uniformType = m_uniformTypes[i];

		if (uniformName == "matrix_worldMatrix")
		{
			SetUniformMatrix4x4f(uniformName, worldMatrix);
		}
		else if (uniformName == "matrix_projectedMatrix")
		{
			SetUniformMatrix4x4f(uniformName, projectedMatrix);
		}
		else if (uniformName == "matrix_cameraMatrix")
		{
			SetUniformMatrix4x4f(uniformName, cameraMatrix);
		}
		else if (uniformName == "camera_translation")
		{
			SetUniformVector3f(uniformName, camera->GetTransform()->GetTranslation());
		}
		else if (uniformName == "rendering_globalAmbientLight")
		{
			SetUniformVector3f(uniformName, renderingEngine->GetGlobalAmbientColor());
		}
		else if (uniformName == "rendering_skybox")
		{
			if (renderingEngine->GetSkybox() != nullptr)
			{
				renderingEngine->GetSkybox()->GetTexture()->Bind(1);
				SetUniformInt(uniformName, 1);
			}
		}

		if (uniformName.substr(0, 4) == "mat_")
		{
			string matComponentName = uniformName.substr(4, uniformName.size() - 4);
			if (uniformType == "float")
			{
				SetUniformFloat(uniformName, material->GetFloat(matComponentName));
			}
			else if (uniformType == "vec3")
			{
				SetUniformVector3f(uniformName, material->GetVector3f(matComponentName));
			}
			else if (uniformType == "sampler2D")
			{
				material->GetTexture(matComponentName)->Bind(0);
				SetUniformInt(uniformName, 0);
			}
		}

		if (uniformType == "DirectionalLight")
		{
			SetUniformDirectionalLight(uniformName, (DirectionalLight*)renderingEngine->GetActiveLight());
		}
		else if (uniformType == "PointLight")
		{
			SetUniformPointLight(uniformName, (PointLight*)renderingEngine->GetActiveLight());
		}
		else if (uniformType == "SpotLight")
		{
			SetUniformSpotLight(uniformName, (SpotLight*)renderingEngine->GetActiveLight());
		}
	}
}