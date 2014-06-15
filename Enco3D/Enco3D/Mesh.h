#ifndef _ENCO3D_MESH_H_
#define _ENCO3D_MESH_H_

#include <GL/glew.h>
#include <string>
#include <map>

#include "Vertex.h"
#include "MeshResource.h"
#include "DLLExport.h"

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
		class DLL_EXPORT Mesh
		{
		protected:
			MeshResource *m_resource{ nullptr };

		protected:
			void buildBuffers(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);

		public:
			Mesh();
			Mesh(Vertex *vertices, unsigned int vertexCount);
			Mesh(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);
			~Mesh();

			void render();

			void updateVertices(unsigned int offsetInVertices, unsigned int sizeInVertices, Vertex *newVertexData);

			inline Vertex *getVertices() const { return m_resource->getVertices(); }
			inline unsigned int getVertexCount() const { return m_resource->getVertexCount(); }

			inline unsigned int *getIndices() const { return m_resource->getIndices(); }
			inline unsigned int getIndexCount() const { return m_resource->getIndexCount(); }

			static void renderErrorMesh(Rendering::Shader *shader, Core::Transform *transform, const Component::Camera *camera, Rendering::RenderingEngine *renderingEngine);
		};
	}
}

#endif