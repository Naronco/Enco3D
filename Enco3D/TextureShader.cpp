#include "TextureShader.h"

Enco3D::Rendering::TextureShader::TextureShader()
{
	AddVertexShaderFromFile("shaders/texture.vs");
	AddFragmentShaderFromFile("shaders/texture.fs");

	SetAttribLocation("in_position", 0);
	SetAttribLocation("in_texCoord", 1);
	SetAttribLocation("in_normal", 2);

	CompileShader();

	AddUniform("worldMatrix");
	AddUniform("projectedMatrix");

	AddUniform("diffuseColor");
	AddUniform("diffuseTexture");
}

void Enco3D::Rendering::TextureShader::UpdateUniforms(const Enco3D::Core::Matrix4x4f &worldMatrix, const Enco3D::Core::Matrix4x4f projectedMatrix, Material &material) const
{
	SetUniformMatrix4x4f("worldMatrix", worldMatrix);
	SetUniformMatrix4x4f("projectedMatrix", projectedMatrix);

	material.GetTexture("diffuse").Bind(0);

	SetUniformVector3f("diffuseColor", material.GetVector3f("diffuse"));
	SetUniformInt("diffuseTexture", 0);
}