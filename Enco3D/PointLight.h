#ifndef _ENCO3D_POINTLIGHT_H_
#define _ENCO3D_POINTLIGHT_H_

#include "Light.h"
#include "PointLightShader.h"

class PointLight : public Light
{
private:
	float m_range{ 0.0f };
	
public:
	PointLight()
	{
		m_shader = PointLightShader::GetInstance();
	}

	void BindToShader(const Vector3f &eyePos)
	{
		((PointLightShader *)m_shader)->SetEyePos(eyePos);
		((PointLightShader *)m_shader)->SetPointLight(m_color, m_intensity, GetTransform()->GetTranslation(), m_range);
	}

	inline void SetRange(float range) { m_range = range; }
	inline float GetRange() const { return m_range; }
};

#endif