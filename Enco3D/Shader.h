#ifndef _ENCO3D_SHADER_H_
#define _ENCO3D_SHADER_H_

#include <GL\glew.h>
#include <map>
#include <list>
#include <string>
#include <iostream>
#include <fstream>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Material.h"

using namespace std;

class Shader
{
private:
	GLuint m_program;
	map<string, int> m_uniforms;
	list<int> m_shaders;

private:
	static const Shader *s_lastBind;

private:
	void AddProgram(const string &text, int type);
	string LoadShader(const string &filename);
	void CheckShaderError(int shader, int flag, bool isProgram, const string &errorMsg);

public:
	Shader();
	Shader(const string &vertexFilename, const string &fragmentFilename);
	virtual ~Shader();

	void Bind() const;
	
	void AddUniform(const string &uniform);

	void AddVertexShader(const string &text);
	void AddFragmentShader(const string &text);
	void AddGeometryShader(const string &text);

	void AddVertexShaderFromFile(const string &filename);
	void AddFragmentShaderFromFile(const string &filename);
	void AddGeometryShaderFromFile(const string &filename);
	
	void CompileShader();

	void SetAttribLocation(const string &attributeName, int location) const;
	void SetUniformInt(const string &name, int value) const;
	void SetUniformFloat(const string &name, float value) const;

	void SetUniformVector2f(const string &name, const Vector2f &v) const;
	void SetUniformVector3f(const string &name, const Vector3f &v) const;
	void SetUniformVector4f(const string &name, const Vector4f &v) const;

	void SetUniformMatrix3x3f(const string &name, const Matrix3x3f &v) const;
	void SetUniformMatrix4x4f(const string &name, const Matrix4x4f &v) const;

	virtual void UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f projectedMatrix, Material &material) const;
};

#endif