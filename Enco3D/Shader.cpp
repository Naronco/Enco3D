#include "Shader.h"

const Shader *Shader::s_lastBind = nullptr;

Shader::Shader()
{
	m_program = glCreateProgram();

	if (m_program == 0)
	{
		cout << "[ERROR] Failed to create shader program" << endl;
	}
}

Shader::Shader(const string &vertexFilename, const string &fragmentFilename)
{
	m_program = glCreateProgram();

	if (m_program == 0)
	{
		cout << "[ERROR] Failed to create shader program" << endl;
		return;
	}

	AddVertexShaderFromFile(vertexFilename);
	AddFragmentShaderFromFile(fragmentFilename);

	SetAttribLocation("in_position", 0);
	SetAttribLocation("in_texCoord", 1);
	SetAttribLocation("in_normal", 2);

	CompileShader();
}

Shader::~Shader()
{
	for (list<int>::iterator it = m_shaders.begin(); it != m_shaders.end(); it++)
	{
		glDetachShader(m_program, *it);
		glDeleteShader(*it);
	}

	glDeleteProgram(m_program);
}

void Shader::AddProgram(const string &text, int type)
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

string Shader::LoadShader(const string &filename)
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

void Shader::CheckShaderError(int shader, int flag, bool isProgram, const string &errorMsg)
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

void Shader::Bind() const
{
	if (s_lastBind != this)
	{
		glUseProgram(m_program);
		s_lastBind = this;
	}
}

void Shader::AddUniform(const string &uniform)
{
	unsigned int location = glGetUniformLocation(m_program, uniform.c_str());
	m_uniforms.insert(pair<string, int>(uniform, location));
}

void Shader::AddVertexShader(const string &text)
{
	AddProgram(text, GL_VERTEX_SHADER);
}

void Shader::AddFragmentShader(const string &text)
{
	AddProgram(text, GL_FRAGMENT_SHADER);
}

void Shader::AddGeometryShader(const string &text)
{
	AddProgram(text, GL_GEOMETRY_SHADER);
}

void Shader::AddVertexShaderFromFile(const string &filename)
{
	AddVertexShader(LoadShader(filename));
}

void Shader::AddFragmentShaderFromFile(const string &filename)
{
	AddFragmentShader(LoadShader(filename));
}

void Shader::AddGeometryShaderFromFile(const string &filename)
{
	AddGeometryShader(LoadShader(filename));
}

void Shader::CompileShader()
{
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "[ERROR] Failed to link shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "[ERROR] Invalid shader program");
}

void Shader::SetAttribLocation(const string &attributeName, int location) const
{
	glBindAttribLocation(m_program, location, attributeName.c_str());
}

void Shader::SetUniformInt(const string &name, int value) const
{
	glUniform1i(m_uniforms.at(name), value);
}

void Shader::SetUniformFloat(const string &name, float value) const
{
	glUniform1f(m_uniforms.at(name), value);
}

void Shader::SetUniformVector2f(const string &name, const Vector2f &v) const
{
	glUniform2f(m_uniforms.at(name), v.x, v.y);
}

void Shader::SetUniformVector3f(const string &name, const Vector3f &v) const
{
	glUniform3f(m_uniforms.at(name), v.x, v.y, v.z);
}

void Shader::SetUniformVector4f(const string &name, const Vector4f &v) const
{
	glUniform4f(m_uniforms.at(name), v.x, v.y, v.z, v.w);
}

void Shader::SetUniformMatrix3x3f(const string &name, const Matrix3x3f &v) const
{
	glUniformMatrix3fv(m_uniforms.at(name), 1, GL_TRUE, (const GLfloat *)v.m);
}

void Shader::SetUniformMatrix4x4f(const string &name, const Matrix4x4f &v) const
{
	glUniformMatrix4fv(m_uniforms.at(name), 1, GL_TRUE, (const GLfloat *)v.m);
}

void Shader::UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f projectedMatrix, Material &material) const
{
}