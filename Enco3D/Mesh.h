#ifndef _ENCO3D_MESH_H_
#define _ENCO3D_MESH_H_

#include <GL/glew.h>
#include <string>
#include <map>

#include "Vertex.h"
#include "OBJModel.h"
#include "IndexedModel.h"
#include "MeshResource.h"

using namespace std;

namespace Enco3D
{
	namespace Rendering
	{
		class Mesh
		{
		protected:
			MeshResource *m_resource{ nullptr };
			
		protected:
			void BuildBuffers(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);
			
		public:
			Mesh();
			Mesh(Vertex *vertices, unsigned int vertexCount);
			Mesh(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);
			~Mesh();

			void Render();

			inline Vertex *GetVertices() const { return m_resource->GetVertices(); }
			inline unsigned int GetVertexCount() const { return m_resource->GetVertexCount(); }

			inline unsigned int *GetIndices() const { return m_resource->GetIndices(); }
			inline unsigned int GetIndexCount() const { return m_resource->GetIndexCount(); }
		};
	}
}

#endif