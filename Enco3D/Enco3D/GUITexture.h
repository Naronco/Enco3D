#ifndef _ENCO3D_GUITEXTURE_H_
#define _ENCO3D_GUITEXTURE_H_

#include "IGameComponent.h"
#include "Texture2D.h"
#include "Mesh.h"
#include "Shader.h"

#include <string>

namespace Enco3D
{
	namespace Component
	{
		class GUITexture : public Core::IGameComponent
		{
		private:
			Rendering::Texture2D *m_texture;
			Core::Vector3f m_color;
			Rendering::Material m_material;

		private:
			static Rendering::Mesh *s_rectangleMesh;
			static unsigned int s_numReferences;

		private:
			void ReleaseTexture();

		public:
			GUITexture();
			GUITexture(Rendering::Texture2D *texture);
			GUITexture(Rendering::Texture2D *texture, const Core::Vector3f &color);
			GUITexture(const string &filename);
			GUITexture(const string &filename, const Core::Vector3f &color);

			void RenderGUI(const Camera *camera, Rendering::Shader *shader);

			void Deinit();

			inline void SetTexture(Rendering::Texture2D *texture) { ReleaseTexture(); m_material.SetTexture2D("diffuseTexture", texture); m_texture = texture; }
			inline void SetColor(const Core::Vector3f &color) { m_material.SetVector3f("diffuseColor", color); m_color.Set(color); }

			inline Rendering::Texture2D *GetTexture() const { return m_texture; }
			inline Core::Vector3f GetColor() const { return m_color; }
		};
	}
}

#endif