#ifndef _ENCO3D_MESH_H_
#define _ENCO3D_MESH_H_

#include <GL/glew.h>
#include <string>
#include <map>

#include "Vertex.h"
#include "MeshResource.h"

namespace Enco3D
{
	namespace Core
	{
		class Transform;
	}

	namespace Rendering
	{
		class Shader;
		struct Material;
		class RenderingEngine;
	}

	namespace Component
	{
		class Camera;
	}
}

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

			void UpdateVertices(unsigned int offsetInVertices, unsigned int sizeInVertices, Vertex *newVertexData);

			inline Vertex *GetVertices() const { return m_resource->GetVertices(); }
			inline unsigned int GetVertexCount() const { return m_resource->GetVertexCount(); }

			inline unsigned int *GetIndices() const { return m_resource->GetIndices(); }
			inline unsigned int GetIndexCount() const { return m_resource->GetIndexCount(); }

			static void RenderErrorMesh(Rendering::Shader *shader, Core::Transform *transform, const Component::Camera *camera, Rendering::RenderingEngine *renderingEngine);
		};
	}
}

#endif