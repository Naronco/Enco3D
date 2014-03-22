#ifndef _ENCO3D_LIGHT_H_
#define _ENCO3D_LIGHT_H_

#include "Vector3.h"
#include "Shader.h"
#include "Matrix4x4.h"
#include "IGameComponent.h"

class Light : public IGameComponent
{
protected:
	Vector3f m_color;
	float m_intensity{ 0 };
	Shader *m_shader{ nullptr };
	
public:
	void InitRendering() { GetRenderingEngine()->AddLight(this); }

	virtual void BindToShader(const Vector3f &eyePos) {  }

	inline void SetColor(const Vector3f &color) { m_color.Set(color); }
	inline void SetIntensity(float intensity) { m_intensity = intensity; }
	
	inline Vector3f GetColor() const { return m_color; }
	inline float GetIntensity() const { return m_intensity; }
	inline Shader *GetShader() const { return m_shader; }
};

#endif