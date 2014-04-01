#include "GeometryPassShader.h"

Enco3D::Rendering::GeometryPassShader::GeometryPassShader()
{
	AddVertexShaderFromFile("shaders/geometryPass.vs");
	AddFragmentShaderFromFile("shaders/geometryPass.fs");

	SetAttribLocation("in_position", 0);
	SetAttribLocation("in_texCoord", 1);
	SetAttribLocation("in_normal", 2);

	CompileShader();

	AddUniform("worldMatrix");
	AddUniform("projectedMatrix");

}

void Enco3D::Rendering::GeometryPassShader::UpdateUniforms(const Enco3D::Core::Matrix4x4f &worldMatrix, const Enco3D::Core::Matrix4x4f &projectedMatrix, Material &material) const
{
	SetUniformMatrix4x4f("worldMatrix", worldMatrix);
	SetUniformMatrix4x4f("projectedMatrix", projectedMatrix);
}