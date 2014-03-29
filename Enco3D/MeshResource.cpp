#include "MeshResource.h"

Enco3D::Rendering::MeshResource::MeshResource()
{
}

Enco3D::Rendering::MeshResource::MeshResource(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount)
{
	m_vertices = new Vertex[vertexCount];
	for (unsigned int i = 0; i < vertexCount; i++)
	{
		m_vertices[i] = vertices[i];
	}

	m_indices = new unsigned int[indexCount];
	for (unsigned int i = 0; i < indexCount; i++)
	{
		m_indices[i] = indices[i];
	}

	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	m_vertexCount = vertexCount;
	m_indexCount = indexCount;

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

Enco3D::Rendering::MeshResource::~MeshResource()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);

	if (m_vertices)
	{
		delete m_vertices;
		m_vertices = nullptr;
	}

	if (m_indices)
	{
		delete m_indices;
		m_indices = nullptr;
	}
}