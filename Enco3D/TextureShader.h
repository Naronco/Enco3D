#ifndef _ENCO3D_TEXTURESHADER_H_
#define _ENCO3D_TEXTURESHADER_H_

#include "Shader.h"

class TextureShader : public Shader
{
public:
	TextureShader();

	void UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f &projectedMatrix, Material &material) const;

public:
	inline static TextureShader *GetInstance()
	{
		static TextureShader *instance = nullptr;

		if (instance == nullptr)
		{
			instance = new TextureShader;
		}

		return instance;
	}
};

#endif