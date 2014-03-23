#ifndef _ENCO3D_SPOTLIGHT_H_
#define _ENCO3D_SPOTLIGHT_H_

#include "Light.h"
#include "SpotLightShader.h"

namespace Enco3D
{
	namespace Component
	{
		struct SpotLight : public Light
		{
		private:
			float m_range, m_cutoff;

		public:
			SpotLight()
			{
				m_shader = SpotLightShader::GetInstance();
			}

			void BindToShader(const Vector3f &eyePos)
			{
				((SpotLightShader *)m_shader)->SetEyePos(eyePos);
				((SpotLightShader *)m_shader)->SetSpotLight(m_color, m_intensity, GetTransform()->GetTranslation(), GetTransform()->GetRotation().GetForward(), m_range, m_cutoff);
			}

			inline void SetRange(float range) { m_range = range; }
			inline void SetCutoff(float cutoff) { m_cutoff = cutoff; }

			inline float GetRange() const { return m_range; }
			inline float GetCutoff() const { return m_cutoff; }
		};
	}
}

#endif