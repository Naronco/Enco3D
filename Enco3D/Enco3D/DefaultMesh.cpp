#include "DefaultMesh.h"

Enco3D::Component::DefaultMesh::DefaultMesh()
{
}

Enco3D::Component::DefaultMesh::DefaultMesh(Rendering::Mesh *mesh, Rendering::Material *material)
{
	m_mesh = mesh;
	m_material = material;
}

void Enco3D::Component::DefaultMesh::render(const Camera *camera, Rendering::Shader *shader)
{
	shader->bind();
	shader->updateUniforms(m_gameObject->getTransform(), camera, m_gameObject->getRenderingEngine(), m_material);

	m_mesh->render();
}

void Enco3D::Component::DefaultMesh::deinit()
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