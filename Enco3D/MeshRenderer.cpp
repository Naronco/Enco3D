#include "MeshRenderer.h"

Enco3D::Component::MeshRenderer::MeshRenderer()
{
}

Enco3D::Component::MeshRenderer::MeshRenderer(Enco3D::Rendering::Mesh *mesh, Enco3D::Rendering::Material *material)
{
	m_mesh = mesh;
	m_material = material;
}

void Enco3D::Component::MeshRenderer::Render(const Enco3D::Rendering::Camera *camera, Enco3D::Rendering::Shader *shader)
{
	Matrix4x4f worldMatrix = GetTransform()->GetTransformation();
	Matrix4x4f projectedMatrix = GetRenderingEngine()->GetViewProjectedMatrix(camera, worldMatrix);

	shader->Bind();
	shader->UpdateUniforms(worldMatrix, projectedMatrix, *m_material);
	m_mesh->Render();
}

void Enco3D::Component::MeshRenderer::Deinit()
{
	if (m_mesh)
	{
		delete m_mesh;
		m_mesh = nullptr;
	}

	if (m_material)
	{
		delete m_material;
		m_material = nullptr;
	}
}