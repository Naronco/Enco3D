#ifndef _ENCO3D_DIRECTIONALLIGHT_H_
#define _ENCO3D_DIRECTIONALLIGHT_H_

#include "BaseLight.h"
#include "DirectionalLightShader.h"

struct DirectionalLight : public BaseLight
{
	Vector3f direction;
	
	DirectionalLight()
	{
		shader = DirectionalLightShader::GetInstance();
	}

	void BindToShader(const Vector3f &eyePos)
	{
		((DirectionalLightShader *)shader)->SetEyePos(eyePos);
		((DirectionalLightShader *)shader)->SetDirectionalLight(color, intensity, direction);
	}
};

#endif