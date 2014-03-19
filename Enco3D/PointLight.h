#ifndef _ENCO3D_POINTLIGHT_H_
#define _ENCO3D_POINTLIGHT_H_

#include "BaseLight.h"
#include "PointLightShader.h"

struct PointLight : public BaseLight
{
	Vector3f position;
	float range{ 0.0f };
	
	PointLight()
	{
		shader = PointLightShader::GetInstance();
	}

	void BindToShader(const Vector3f &eyePos)
	{
		((PointLightShader *)shader)->SetEyePos(eyePos);
		((PointLightShader *)shader)->SetPointLight(color, intensity, position, range);
	}
};

#endif