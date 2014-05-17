#ifndef _ENCO3D_POINTLIGHT_H_
#define _ENCO3D_POINTLIGHT_H_

#include "ILight.h"

namespace Enco3D
{
	namespace Component
	{
		class PointLight : public ILight
		{
		private:
			float m_range{ 0.0f };

		public:
			PointLight()
			{
				m_shader = Rendering::ShaderPool::getInstance()->getShader("shaders/forwardPointLight", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
			}

			inline void setRange(float range) { m_range = range; }
			inline float getRange() const { return m_range; }
		};
	}
}

#endif