#ifndef _ENCO3D_SPOTLIGHT_H_
#define _ENCO3D_SPOTLIGHT_H_

#include "BaseLight.h"
#include "SpotLightShader.h"

struct SpotLight : public BaseLight
{
	Vector3f position, direction;
	float range, cutoff;

	SpotLight()
	{
		shader = SpotLightShader::GetInstance();
	}

	void BindToShader(const Vector3f &eyePos)
	{
		((SpotLightShader *)shader)->SetEyePos(eyePos);
		((SpotLightShader *)shader)->SetSpotLight(color, intensity, position, direction, range, cutoff);
	}
};

#endif