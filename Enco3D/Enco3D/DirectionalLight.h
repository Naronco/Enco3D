#ifndef _ENCO3D_DIRECTIONALLIGHT_H_
#define _ENCO3D_DIRECTIONALLIGHT_H_

#include "ILight.h"
#include "Skybox.h"
#include "ShaderPool.h"

namespace Enco3D
{
	namespace Component
	{
		class DirectionalLight : public ILight
		{
		public:
			DirectionalLight()
			{
				m_shader = Rendering::ShaderPool::getInstance()->getShader("shaders/forwardDirectionalLight", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
			}

			DirectionalLight(const Core::Vector3f &color, float intensity)
			{
				m_color.set(color);
				m_intensity = intensity;
				m_shader = Rendering::ShaderPool::getInstance()->getShader("shaders/forwardDirectionalLight", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
			}

			DirectionalLight(float r, float g, float b, float intensity)
			{
				m_color.set(r, g, b);
				m_intensity = intensity;
				m_shader = Rendering::ShaderPool::getInstance()->getShader("shaders/forwardDirectionalLight", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
			}
		};
	}
}

#endif