#ifndef _ENCO3D_POSTPROCESSSHADER_H_
#define _ENCO3D_POSTPROCESSSHADER_H_

#include "Shader.h"
#include "GBuffer.h"

class PostProcessShader : public Shader
{
private:
	GBuffer *m_gbuffer{ nullptr };

public:
	PostProcessShader();

	void UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f &projectedMatrix, Material &material) const;

	inline void SetGBuffer(GBuffer *gbuffer) { m_gbuffer = gbuffer; }
	inline GBuffer *GetGBuffer() const { return m_gbuffer; }

public:
	inline static PostProcessShader *GetInstance()
	{
		static PostProcessShader *instance = nullptr;

		if (instance == nullptr)
		{
			instance = new PostProcessShader;
		}

		return instance;
	}
};

#endif