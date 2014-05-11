#ifndef _ENCO3D_SKYBOX_H_
#define _ENCO3D_SKYBOX_H_

#include "IGameComponent.h"

#include "Camera.h"

#include "Mesh.h"
#include "Material.h"
#include "TextureCubeMap.h"

#include <string>

namespace Enco3D
{
	namespace Component
	{
		class Skybox : public Core::IGameComponent
		{
		private:
			Rendering::Mesh *m_mesh{ nullptr };
			Rendering::TextureCubeMap *m_skyboxTexture{ nullptr };
			Rendering::Shader *m_skyboxShader{ nullptr };

		public:
			Skybox();
			Skybox(const std::string &filename);
			~Skybox();

			void InitRendering();

			void Render(const Component::Camera *camera);

			inline Rendering::TextureCubeMap *GetTexture() { return m_skyboxTexture; }
		};
	}
}

#endif