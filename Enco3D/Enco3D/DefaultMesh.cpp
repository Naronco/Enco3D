#include "DefaultMesh.h"

Enco3D::Component::DefaultMesh::DefaultMesh()
{
}

Enco3D::Component::DefaultMesh::DefaultMesh(Rendering::Mesh *mesh, Rendering::Material *material)
{
	m_mesh = std::make_shared<Rendering::Mesh>(mesh);
	m_material = std::make_shared<Rendering::Material>(material);
}

void Enco3D::Component::DefaultMesh::render(const Camera *camera, Rendering::Shader *shader)
{
	shader->bind();
	shader->updateUniforms(m_gameObject->getTransform(), camera, m_gameObject->getRenderingEngine(), *m_material);

	m_mesh->render();
}