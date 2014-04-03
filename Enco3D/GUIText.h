#ifndef _ENCO3D_GUITEXT_H_
#define _ENCO3D_GUITEXT_H_

#include "Vector3.h"

#include "IGUIElement.h"

#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "FontDatabase.h"

#include <string>

using Enco3D::Core::Vector3f;

using Enco3D::Rendering::Texture;
using Enco3D::Rendering::Mesh;
using Enco3D::Rendering::Shader;
using Enco3D::Rendering::FontDatabase;

using std::string;

namespace Enco3D
{
	namespace Component
	{
		class GUIText : public IGUIElement
		{
		private:
			string m_text;
			Vector3f m_color;
			Font *m_font{ nullptr };
			Mesh *m_mesh{ nullptr };
			Material m_material;

		private:
			void UpdateMesh();

		public:
			GUIText();
			GUIText(const string &text);
			GUIText(const string &text, const Vector3f &color);
			~GUIText();

			void InitRendering();

			void RenderGUI(const Camera *camera, Shader *shader);

			inline void SetText(const string &text) { m_text = text; UpdateMesh(); }
			inline void SetColor(const Vector3f &color) { m_color.Set(color); m_material.SetVector3f("diffuse", m_color); }

			inline string GetText() const { return m_text; }
			inline Vector3f GetColor() const { return m_color; }
			inline Font *GetFont() const { return m_font; }
		};
	}
}

#endif