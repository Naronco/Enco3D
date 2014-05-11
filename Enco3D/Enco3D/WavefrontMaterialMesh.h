#ifndef _ENCO3D_WAVEFRONTMATERIALMESH_H_
#define _ENCO3D_WAVEFRONTMATERIALMESH_H_

#include "IGameComponent.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshResource.h"
#include "Material.h"
#include "Shader.h"
#include "Vertex.h"
#include "Texture2D.h"
#include "DebugLogger.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <string>
#include <vector>
#include <iostream>

namespace Enco3D
{
	namespace Physics
	{
		class StaticConcaveMeshCollisionShape;
	}
}

namespace Enco3D
{
	namespace Component
	{
		class WavefrontMaterialMesh : public Core::IGameComponent
		{
		private:
			std::vector<Rendering::MeshResource *> m_meshes;
			std::vector<Rendering::Material *> m_materials;
			bool m_successfullyLoadedMesh;
			mutable Rendering::Mesh *m_staticConcaveMeshCollisionShape;

		private:
			bool InitFromScene(const aiScene *scene, const std::string &filename);
			void InitMesh(unsigned int index, const aiMesh *mesh);
			bool InitMaterials(const aiScene *scene, const std::string &filename);
			
		public:
			WavefrontMaterialMesh();
			WavefrontMaterialMesh(const std::string &filename);
			~WavefrontMaterialMesh();

			void Render(const Component::Camera *camera, Rendering::Shader *shader);

			Physics::StaticConcaveMeshCollisionShape *GetStaticConcaveMeshCollisionShape() const;
		};
	}
}

#endif