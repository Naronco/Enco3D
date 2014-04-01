#ifndef _ENCO3D_DIRECTIONALLIGHT_H_
#define _ENCO3D_DIRECTIONALLIGHT_H_

#include "Light.h"
#include "DirectionalLightShader.h"
#include "Skybox.h"

namespace Enco3D
{
	namespace Component
	{
		class DirectionalLight : public Light
		{
		public:
			DirectionalLight()
			{
				m_shader = DirectionalLightShader::GetInstance();
			}

			void BindToShader(const Vector3f &eyePos)
			{
				((DirectionalLightShader *)m_shader)->SetEyePos(eyePos);
				((DirectionalLightShader *)m_shader)->SetDirectionalLight(m_color, m_intensity, GetTransform()->GetRotation().GetForward());

				Skybox *skybox = GetRenderingEngine()->GetSkybox();

				if (skybox != nullptr)
				{
					((DirectionalLightShader *)m_shader)->SetEnvironmentTexture(skybox->GetTexture());
				}
			}
		};
	}
}

#endif