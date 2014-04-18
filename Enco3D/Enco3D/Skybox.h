#ifndef _ENCO3D_SKYBOX_H_
#define _ENCO3D_SKYBOX_H_

#include "IGameComponent.h"

#include "Camera.h"

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

#include <string>

using Enco3D::Core::IGameComponent;

using Enco3D::Component::Camera;

using Enco3D::Rendering::Mesh;
using Enco3D::Rendering::Material;
using Enco3D::Rendering::Texture;

using std::string;

namespace Enco3D
{
	namespace Component
	{
		class Skybox : public IGameComponent
		{
		private:
			Mesh *m_mesh{ nullptr };
			Texture *m_skyboxTexture{ nullptr };
			Shader *m_skyboxShader{ nullptr };

		public:
			Skybox();
			Skybox(const string &filename);
			~Skybox();

			void InitRendering();

			void Render(const Camera *camera);

			inline Texture *GetTexture() { return m_skyboxTexture; }
		};
	}
}

#endif