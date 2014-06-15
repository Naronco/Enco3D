#ifndef _ENCO3D_GUITEXT_H_
#define _ENCO3D_GUITEXT_H_

#include "Vector3.h"
#include "IGameComponent.h"

#include "Texture2D.h"
#include "Mesh.h"
#include "Shader.h"
#include "FontPool.h"
#include "DLLExport.h"

#include <string>

namespace Enco3D
{
	namespace Component
	{
		const unsigned int __defaultFontSize = 32;

		class DLL_EXPORT GUIText : public Core::IGameComponent
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

			void initRendering();

			void renderGUI(const Component::Camera *camera, Rendering::Shader *shader);

			inline void setText(const std::string &text) { m_text = text; UpdateMesh(); }
			inline void setColor(const Core::Vector3f &color) { m_color.set(color); m_material.setVector3f("diffuseColor", m_color); }

			inline std::string getText() const { return m_text; }
			inline Core::Vector3f getColor() const { return m_color; }
			inline Rendering::Font *getFont() const { return m_font; }
		};
	}
}

#endif