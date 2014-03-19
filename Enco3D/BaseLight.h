#ifndef _ENCO3D_BASELIGHT_H_
#define _ENCO3D_BASELIGHT_H_

#include "Vector3.h"
#include "Shader.h"
#include "Matrix4x4.h"

struct BaseLight
{
	Vector3f color;
	float intensity{ 0 };
	Shader *shader{ nullptr };
	
	virtual void BindToShader(const Vector3f &eyePos) {  }
};

#endif