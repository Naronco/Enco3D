#ifndef _ENCO3D_POINTLIGHT_H_
#define _ENCO3D_POINTLIGHT_H_

#include "ILight.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Component
	{
		class DLL_EXPORT PointLight : public ILight
		{
		private:
			float m_range{ 0.0f };

		public:
			PointLight()
			{
				m_shader = Rendering::ShaderPool::getInstance()->getShader("shaders/forwardPointLight", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
			}

			PointLight(const Core::Vector3f &color, float intensity, float range)
			{
				m_color.set(color);
				m_intensity = intensity;
				m_range = range;
				m_shader = Rendering::ShaderPool::getInstance()->getShader("shaders/forwardPointLight", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
			}

			PointLight(float r, float g, float b, float intensity, float range)
			{
				m_color.set(r, g, b);
				m_intensity = intensity;
				m_range = range;
				m_shader = Rendering::ShaderPool::getInstance()->getShader("shaders/forwardPointLight", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
			}

			inline void setRange(float range) { m_range = range; }
			inline float getRange() const { return m_range; }
		};
	}
}

#endif