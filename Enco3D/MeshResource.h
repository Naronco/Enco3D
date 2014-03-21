#ifndef _ENCO3D_MESHRESOURCE_H_
#define _ENCO3D_MESHRESOURCE_H_

#include <GL\glew.h>

class MeshResource
{
private:
	GLuint m_vbo{ 0 }, m_ibo{ 0 };
	unsigned int m_vertexCount{ 0 }, m_indexCount{ 0 }, m_refCount{ 0 };

public:
	MeshResource();
	MeshResource(unsigned int vertexCount, unsigned int indexCount);
	~MeshResource();

	inline void AddReference() { m_refCount++; }
	inline bool RemoveReference() { m_refCount--; return m_refCount == 0; }

	inline GLuint GetVBO() const { return m_vbo; }
	inline GLuint GetIBO() const { return m_ibo; }
	inline unsigned int GetVertexCount() const { return m_vertexCount; }
	inline unsigned int GetIndexCount() const { return m_indexCount; }
};

#endif