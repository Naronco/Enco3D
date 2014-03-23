#include "MeshRenderer.h"

Enco3D::Component::MeshRenderer::MeshRenderer()
{
}

Enco3D::Component::MeshRenderer::MeshRenderer(Enco3D::Rendering::Mesh *mesh, Enco3D::Rendering::Material *material)
{
	m_mesh = mesh;
	m_material = material;
}

void Enco3D::Component::MeshRenderer::Render(Enco3D::Rendering::Shader *shader)
{
	Matrix4x4f worldMatrix = GetTransform()->GetTransformation();
	Matrix4x4f projectedMatrix = GetRenderingEngine()->GetProjectedMatrix(worldMatrix);

	shader->Bind();
	shader->UpdateUniforms(worldMatrix, projectedMatrix, *m_material);
	m_mesh->Render();
}