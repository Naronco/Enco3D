#ifndef _ENCO3D_WAVEFRONTMESH_H_
#define _ENCO3D_WAVEFRONTMESH_H_

#include "IGameComponent.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Camera.h"
#include "MeshResource.h"
#include "Material.h"
#include "Shader.h"
#include "Vertex.h"
#include "DebugLogger.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <string>
#include <vector>
#include <iostream>
#include <memory>

namespace Enco3D
{
	namespace Component
	{
		class WavefrontMesh : public Core::IGameComponent
		{
		private:
			std::vector<std::shared_ptr<Rendering::MeshResource>> m_meshes;
			std::shared_ptr<Rendering::Material> m_material;
			bool m_successfullyLoadedMesh;

		private:
			bool initFromScene(const aiScene *scene, const std::string &filename);
			void initMesh(unsigned int index, const aiMesh *mesh);

		public:
			WavefrontMesh();
			WavefrontMesh(const std::string &filename, Rendering::Material *material);

			void render(const Component::Camera *camera, Rendering::Shader *shader);

			inline std::shared_ptr<Rendering::Material> getMaterial() const { return m_material; }
		};
	}
}

#endif