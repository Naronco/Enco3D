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
#include "Texture.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <string>
#include <vector>
#include <iostream>

using Enco3D::Core::IGameComponent;
using Enco3D::Core::Vector3f;
using Enco3D::Core::Vector2f;

using Enco3D::Component::Camera;

using Enco3D::Rendering::MeshResource;
using Enco3D::Rendering::Material;
using Enco3D::Rendering::Shader;
using Enco3D::Rendering::Vertex;
using Enco3D::Rendering::Texture;

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

namespace Enco3D
{
	namespace Component
	{
		class WavefrontMesh : public IGameComponent
		{
		private:
			vector<MeshResource *> m_meshes;
			vector<Material *> m_materials;

		private:
			bool InitFromScene(const aiScene *scene, const string &filename);
			void InitMesh(unsigned int index, const aiMesh *mesh);
			bool InitMaterials(const aiScene *scene, const string &filename);
			
		public:
			WavefrontMesh();
			WavefrontMesh(const string &filename);
			~WavefrontMesh();

			void Render(const Camera *camera, Shader *shader);
		};
	}
}

#endif