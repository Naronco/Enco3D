#ifndef _ENCO3D_SPOTLIGHT_H_
#define _ENCO3D_SPOTLIGHT_H_

#include "ILight.h"

namespace Enco3D
{
	namespace Component
	{
		class SpotLight : public ILight
		{
		private:
			float m_range, m_cutoff;

		public:
			SpotLight()
			{
				m_shader = ShaderPool::GetInstance()->GetShader("shaders/forwardSpotLight", ShaderType::VertexShader | ShaderType::FragmentShader);
			}

			inline void SetRange(float range) { m_range = range; }
			inline void SetCutoff(float cutoff) { m_cutoff = cutoff; }

			inline float GetRange() const { return m_range; }
			inline float GetCutoff() const { return m_cutoff; }
		};
	}
}

#endif