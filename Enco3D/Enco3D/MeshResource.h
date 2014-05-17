#ifndef _ENCO3D_MESHRESOURCE_H_
#define _ENCO3D_MESHRESOURCE_H_

#include <GL\glew.h>
#include <iostream>
#include "Vertex.h"
#include "DebugLogger.h"

namespace Enco3D
{
	namespace Rendering
	{
		class MeshResource
		{
		private:
			GLuint m_vbo{ 0 }, m_ibo{ 0 };
			Vertex *m_vertices;
			unsigned int *m_indices;
			unsigned int m_vertexCount{ 0 }, m_indexCount{ 0 }, m_refCount{ 0 };
			unsigned int m_materialIndex{ 0 };

		public:
			MeshResource();
			MeshResource(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);
			~MeshResource();

			inline void addReference() { m_refCount++; }
			inline bool removeReference() { return --m_refCount == 0; }

			inline void setMaterialIndex(unsigned int materialIndex) { m_materialIndex = materialIndex; }

			void updateVertices(unsigned int offsetInVertices, unsigned int sizeInVertices, Vertex *newVertices);

			inline GLuint getVBO() const { return m_vbo; }
			inline GLuint getIBO() const { return m_ibo; }
			inline unsigned int getVertexCount() const { return m_vertexCount; }
			inline unsigned int getIndexCount() const { return m_indexCount; }
			inline Vertex *getVertices() const { return m_vertices; }
			inline unsigned int *getIndices() const { return m_indices; }
			inline unsigned int getMaterialIndex() const { return m_materialIndex; }
		};
	}
}

#endif