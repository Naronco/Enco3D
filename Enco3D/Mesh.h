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
		private:
			MeshResource *m_resource{ nullptr };
			string m_filename;

		private:
			static map<string, MeshResource *> s_loadedModels;

		private:
			void BuildBuffers(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);
			void LoadMesh(const string &filename);

		public:
			Mesh();
			Mesh(Vertex *vertices, unsigned int vertexCount);
			Mesh(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);
			Mesh(const string &filename);
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