#ifndef _ENCO3D_DIRECTIONALLIGHTSHADER_H_
#define _ENCO3D_DIRECTIONALLIGHTSHADER_H_

#include "Shader.h"

class DirectionalLightShader : public Shader
{
private:
	Vector3f m_color;
	float m_intensity;
	Vector3f m_direction;
	Vector3f m_eyePos;

public:
	DirectionalLightShader();

	void UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f projectedMatrix, Material &material) const;

	inline void SetEyePos(const Vector3f &eyePos) { m_eyePos = eyePos; }
	inline void SetDirectionalLight(const Vector3f &color, float intensity, const Vector3f &direction) { m_color = color; m_intensity = intensity; m_direction = direction; }

	inline Vector3f GetEyePos() const { return m_eyePos; }

public:
	inline static DirectionalLightShader *GetInstance()
	{
		static DirectionalLightShader *instance = nullptr;

		if (instance == nullptr)
		{
			instance = new DirectionalLightShader;
		}

		return instance;
	}
};

#endif