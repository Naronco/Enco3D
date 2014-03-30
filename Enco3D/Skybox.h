#ifndef _ENCO3D_SKYBOX_H_
#define _ENCO3D_SKYBOX_H_

#include "IGameComponent.h"

#include "Camera.h"

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "TextureShader.h"

using Enco3D::Core::IGameComponent;

using Enco3D::Component::Camera;

using Enco3D::Rendering::Mesh;
using Enco3D::Rendering::Material;
using Enco3D::Rendering::Texture;
using Enco3D::Rendering::TextureShader;

namespace Enco3D
{
	namespace Component
	{
		class Skybox : public IGameComponent
		{
		private:
			Mesh *m_mesh{ nullptr };
			Material *m_material{ nullptr };
			TextureShader *m_textureShader{ nullptr };

		public:
			Skybox();
			Skybox(Texture *texture);
			~Skybox();

			void InitRendering();

			void Render(const Camera *camera);
		};
	}
}

#endif