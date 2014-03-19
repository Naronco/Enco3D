#include "Mesh.h"

Mesh::Mesh()
{
	GenerateBuffers();
}

Mesh::Mesh(Vertex *vertices, unsigned int vertexCount)
{
	GenerateBuffers();

	unsigned int *indices = new unsigned int[vertexCount];
	for (unsigned int i = 0; i < vertexCount; i++)
	{
		indices[i] = i;
	}

	BuildBuffers(vertices, vertexCount, indices, vertexCount);
}

Mesh::Mesh(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount)
{
	GenerateBuffers();
	BuildBuffers(vertices, vertexCount, indices, indexCount);
}

Mesh::Mesh(const string &filename)
{
	OBJModel objModel(filename);

	IndexedModel indexedModel = objModel.ToIndexedModel();
	//indexedModel.CalcNormals();

	Vertex *vertices = new Vertex[indexedModel.GetPositions().size()];

	for (unsigned int i = 0; i < indexedModel.GetPositions().size(); i++)
	{
		vertices[i].SetPosition(indexedModel.GetPositions()[i].x, indexedModel.GetPositions()[i].y, indexedModel.GetPositions()[i].z);
		vertices[i].SetTexCoord(indexedModel.GetTexCoords()[i].x, indexedModel.GetTexCoords()[i].y);
		vertices[i].SetNormal(indexedModel.GetNormals()[i].x, indexedModel.GetNormals()[i].y, indexedModel.GetNormals()[i].z);
	}

	unsigned int *indices = new unsigned int[indexedModel.GetIndices().size()];

	for (unsigned int i = 0; i < indexedModel.GetIndices().size(); i++)
	{
		indices[i] = indexedModel.GetIndices()[i];
	}

	GenerateBuffers();
	BuildBuffers(vertices, indexedModel.GetPositions().size(), indices, indexedModel.GetIndices().size());

	if (vertices)
	{
		delete vertices;
		vertices = nullptr;
	}

	if (indices)
	{
		delete indices;
		indices = nullptr;
	}
}

void Mesh::GenerateBuffers()
{
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
}

void Mesh::BuildBuffers(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount)
{
	m_vertexCount = vertexCount;
	m_indexCount = indexCount;

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void Mesh::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 5));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}