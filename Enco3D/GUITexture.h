#ifndef _ENCO3D_GUITEXTURE_H_
#define _ENCO3D_GUITEXTURE_H_

#include "IGUIElement.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

#include <string>

namespace Enco3D
{
	namespace Component
	{
		using namespace Rendering;

		class GUITexture : public IGUIElement
		{
		private:
			Texture *m_texture;
			Material m_material;

		private:
			static Mesh *s_rectangleMesh;
			static unsigned int s_numReferences;

		private:
			void ReleaseTexture();

		public:
			GUITexture();
			GUITexture(Texture *texture);
			GUITexture(const string &filename);

			void RenderGUI(const Camera *camera, Shader *shader);

			void Deinit();

			inline void SetTexture(Texture *texture) { ReleaseTexture(); m_material.SetTexture("diffuse", *texture); m_texture = texture; }
			inline Texture *GetTexture() const { return m_texture; }
		};
	}
}

#endif