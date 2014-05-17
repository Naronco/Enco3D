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
			void releaseTexture();

		public:
			GUITexture();
			GUITexture(Rendering::Texture2D *texture);
			GUITexture(Rendering::Texture2D *texture, const Core::Vector3f &color);
			GUITexture(const string &filename);
			GUITexture(const string &filename, const Core::Vector3f &color);

			void renderGUI(const Camera *camera, Rendering::Shader *shader);

			void deinit();

			inline void setTexture(Rendering::Texture2D *texture) { releaseTexture(); m_material.setTexture2D("diffuseTexture", texture); m_texture = texture; }
			inline void setColor(const Core::Vector3f &color) { m_material.setVector3f("diffuseColor", color); m_color.set(color); }

			inline Rendering::Texture2D *getTexture() const { return m_texture; }
			inline Core::Vector3f getColor() const { return m_color; }
		};
	}
}

#endif