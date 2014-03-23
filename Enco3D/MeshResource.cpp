#include "MeshResource.h"

Enco3D::Rendering::MeshResource::MeshResource()
{
}

Enco3D::Rendering::MeshResource::MeshResource(unsigned int vertexCount, unsigned int indexCount)
{
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	m_vertexCount = vertexCount;
	m_indexCount = indexCount;
}

Enco3D::Rendering::MeshResource::~MeshResource()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}