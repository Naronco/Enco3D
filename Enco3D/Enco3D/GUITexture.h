#ifndef _ENCO3D_GUITEXTURE_H_
#define _ENCO3D_GUITEXTURE_H_

#include "IGameComponent.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

#include <string>

namespace Enco3D
{
	namespace Component
	{
		using namespace Rendering;

		class GUITexture : public IGameComponent
		{
		private:
			Texture *m_texture;
			Vector3f m_color;
			Material m_material;

		private:
			static Mesh *s_rectangleMesh;
			static unsigned int s_numReferences;

		private:
			void ReleaseTexture();

		public:
			GUITexture();
			GUITexture(Texture *texture);
			GUITexture(Texture *texture, const Vector3f &color);
			GUITexture(const string &filename);
			GUITexture(const string &filename, const Vector3f &color);

			void RenderGUI(const Camera *camera, Shader *shader);

			void Deinit();

			inline void SetTexture(Texture *texture) { ReleaseTexture(); m_material.SetTexture("diffuseTexture", texture); m_texture = texture; }
			inline void SetColor(const Vector3f &color) { m_material.SetVector3f("diffuseColor", color); m_color.Set(color); }

			inline Texture *GetTexture() const { return m_texture; }
			inline Vector3f GetColor() const { return m_color; }
		};
	}
}

#endif