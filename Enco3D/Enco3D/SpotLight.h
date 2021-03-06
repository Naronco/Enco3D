#ifndef _ENCO3D_SPOTLIGHT_H_
#define _ENCO3D_SPOTLIGHT_H_

#include "ILight.h"
#include "ShaderPool.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Component
	{
		class DLL_EXPORT SpotLight : public ILight
		{
		private:
			float m_range, m_cutoff;

		public:
			SpotLight()
			{
				m_shader = Rendering::ShaderPool::getInstance()->getShader("shaders/forwardSpotLight", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
			}

			SpotLight(const Core::Vector3f &color, float intensity, float range, float cutoff)
			{
				m_color.set(color);
				m_intensity = intensity;
				m_range = range;
				m_cutoff = cutoff;
				m_shader = Rendering::ShaderPool::getInstance()->getShader("shaders/forwardSpotLight", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
			}

			SpotLight(float r, float g, float b, float intensity, float range, float cutoff)
			{
				m_color.set(r, g, b);
				m_intensity = intensity;
				m_range = range;
				m_cutoff = cutoff;
				m_shader = Rendering::ShaderPool::getInstance()->getShader("shaders/forwardSpotLight", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
			}

			inline void setRange(float range) { m_range = range; }
			inline void setCutoff(float cutoff) { m_cutoff = cutoff; }

			inline float getRange() const { return m_range; }
			inline float getCutoff() const { return m_cutoff; }
		};
	}
}

#endif