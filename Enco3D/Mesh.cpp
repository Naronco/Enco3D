#include "Mesh.h"

Enco3D::Rendering::Mesh::Mesh()
{
}

Enco3D::Rendering::Mesh::Mesh(Vertex *vertices, unsigned int vertexCount)
{
	unsigned int *indices = new unsigned int[vertexCount];
	for (unsigned int i = 0; i < vertexCount; i++)
	{
		indices[i] = i;
	}

	BuildBuffers(vertices, vertexCount, indices, vertexCount);
}

Enco3D::Rendering::Mesh::Mesh(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount)
{
	BuildBuffers(vertices, vertexCount, indices, indexCount);
}

Enco3D::Rendering::Mesh::~Mesh()
{
}

void Enco3D::Rendering::Mesh::BuildBuffers(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount)
{
	m_resource = new MeshResource(vertices, vertexCount, indices, indexCount);

	glBindBuffer(GL_ARRAY_BUFFER, m_resource->GetVBO());
	glBufferData(GL_ARRAY_BUFFER, m_resource->GetVertexCount() * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_resource->GetIBO());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_resource->GetIndexCount() * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

/*void Enco3D::Rendering::Mesh::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_resource->GetVBO());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 5));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_resource->GetIBO());
	glDrawElements(GL_TRIANGLES, m_resource->GetIndexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}*/