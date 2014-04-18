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
				m_shader = ShaderPool::GetInstance()->GetShader("shaders/forwardPointLight", ShaderType::VertexShader | ShaderType::FragmentShader);
			}

			inline void SetRange(float range) { m_range = range; }
			inline float GetRange() const { return m_range; }
		};
	}
}

#endif