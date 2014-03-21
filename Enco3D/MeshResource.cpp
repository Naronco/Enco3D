#include "MeshResource.h"

MeshResource::MeshResource()
{
}

MeshResource::MeshResource(unsigned int vertexCount, unsigned int indexCount)
{
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	m_vertexCount = vertexCount;
	m_indexCount = indexCount;
}

MeshResource::~MeshResource()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}