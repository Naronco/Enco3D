#include "DefaultMesh.h"

Enco3D::Component::DefaultMesh::DefaultMesh()
{
}

Enco3D::Component::DefaultMesh::DefaultMesh(Rendering::Mesh *mesh, Rendering::Material *material)
{
	m_mesh = mesh;
	m_material = material;
}

void Enco3D::Component::DefaultMesh::Render(const Camera *camera, Rendering::Shader *shader)
{
	shader->Bind();
	shader->UpdateUniforms(m_gameObject->GetTransform(), camera, m_gameObject->GetRenderingEngine(), m_material);

	m_mesh->Render();
}

void Enco3D::Component::DefaultMesh::Deinit()
{
	if (m_mesh) {
		delete m_mesh;
		m_mesh = nullptr;
	}

	if (m_material) {
		delete m_material;
		m_material = nullptr;
	}
}