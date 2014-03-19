#ifndef _ENCO3D_MESH_H_
#define _ENCO3D_MESH_H_

#include <GL/glew.h>
#include <string>

#include "Vertex.h"
#include "OBJModel.h"
#include "IndexedModel.h"

using namespace std;

class Mesh
{
private:
	GLuint m_vbo, m_ibo;
	unsigned int m_vertexCount, m_indexCount;

private:
	void GenerateBuffers();
	void BuildBuffers(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);

public:
	Mesh();

	Mesh(Vertex *vertices, unsigned int vertexCount);
	Mesh(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);
	
	Mesh(const string &filename);

	void Render();
};

#endif