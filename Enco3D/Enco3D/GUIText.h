#ifndef _ENCO3D_GUITEXT_H_
#define _ENCO3D_GUITEXT_H_

#include "Vector3.h"
#include "IGameComponent.h"

#include "Texture2D.h"
#include "Mesh.h"
#include "Shader.h"
#include "FontPool.h"

#include <string>

namespace Enco3D
{
	namespace Component
	{
		const unsigned int __defaultFontSize = 32;

		class GUIText : public Core::IGameComponent
		{
		private:
			std::string m_text;
			Core::Vector3f m_color;
			Rendering::Font *m_font{ nullptr };
			Rendering::Mesh *m_mesh{ nullptr };
			Rendering::Material m_material;

		private:
			void UpdateMesh();

		public:
			GUIText();
			GUIText(const std::string &text, Rendering::Font *font);
			GUIText(const std::string &text, const Core::Vector3f &color, Rendering::Font *font);
			~GUIText();

			void InitRendering();

			void RenderGUI(const Component::Camera *camera, Rendering::Shader *shader);

			inline void SetText(const std::string &text) { m_text = text; UpdateMesh(); }
			inline void SetColor(const Core::Vector3f &color) { m_color.Set(color); m_material.SetVector3f("diffuseColor", m_color); }

			inline std::string GetText() const { return m_text; }
			inline Core::Vector3f GetColor() const { return m_color; }
			inline Rendering::Font *GetFont() const { return m_font; }
		};
	}
}

#endif