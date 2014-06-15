#ifndef _ENCO3D_ILIGHT_H_
#define _ENCO3D_ILIGHT_H_

#include "Vector3.h"
#include "Shader.h"
#include "Matrix4x4.h"
#include "IGameComponent.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Component
	{
		class DLL_EXPORT ILight : public Core::IGameComponent
		{
		protected:
			Core::Vector3f m_color;
			float m_intensity{ 0 };
			Rendering::Shader *m_shader{ nullptr };

		public:
			void initRendering() { getRenderingEngine()->addLight(this); }
			void deinit() { getRenderingEngine()->removeLight(this); }

			virtual void setUpShader() {  }

			inline void setColor(const Core::Vector3f &color) { m_color.set(color); }
			inline void setIntensity(float intensity) { m_intensity = intensity; }

			inline Core::Vector3f getColor() const { return m_color; }
			inline float getIntensity() const { return m_intensity; }
			inline Rendering::Shader *getShader() const { return m_shader; }
		};
	}
}

#endif