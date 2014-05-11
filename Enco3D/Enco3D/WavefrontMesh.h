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

namespace Enco3D
{
	namespace Component
	{
		class WavefrontMesh : public Core::IGameComponent
		{
		private:
			std::vector<Rendering::MeshResource*> m_meshes;
			Rendering::Material *m_material;
			bool m_successfullyLoadedMesh;

		private:
			bool InitFromScene(const aiScene *scene, const std::string &filename);
			void InitMesh(unsigned int index, const aiMesh *mesh);
			
		public:
			WavefrontMesh();
			WavefrontMesh(const std::string &filename, Rendering::Material *material);
			~WavefrontMesh();

			void Render(const Component::Camera *camera, Rendering::Shader *shader);

			inline void SetMaterial(Rendering::Material *material) { m_material = material; }
			inline Rendering::Material *GetMaterial() const { return m_material; }
		};
	}
}

#endif