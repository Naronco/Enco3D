#include "TextureShader.h"

TextureShader::TextureShader()
{
	AddVertexShaderFromFile("shaders/texture.vs");
	AddFragmentShaderFromFile("shaders/texture.fs");

	SetAttribLocation("in_position", 0);
	SetAttribLocation("in_texCoord", 1);

	CompileShader();

	AddUniform("worldMatrix");
	AddUniform("projectedMatrix");

	AddUniform("color");
	AddUniform("diffuseTexture");
}

void TextureShader::UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f &projectedMatrix, Material &material) const
{
	SetUniformMatrix4x4f("worldMatrix", worldMatrix);
	SetUniformMatrix4x4f("projectedMatrix", projectedMatrix);

	material.GetTexture("diffuse").Bind(0);

	SetUniformVector3f("color", material.GetVector3f("color"));
	SetUniformInt("diffuseTexture", 0);
}