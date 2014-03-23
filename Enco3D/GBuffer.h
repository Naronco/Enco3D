#ifndef _ENCO3D_GBUFFER_H_
#define _ENCO3D_GBUFFER_H_

#include <GL\glew.h>
#include <iostream>

using namespace std;

enum GBufferTextureType
{
	Position,
	TexCoord,
	Normal,
	//
	NumTextures,
};

class GBuffer
{
private:
	GLuint m_fbo{ 0 };
	GLuint m_textures[GBufferTextureType::NumTextures];
	GLuint m_depthTexture{ 0 };

public:
	GBuffer();
	GBuffer(unsigned int width, unsigned int height);
	~GBuffer();

	void Bind();
	void Debind();

	inline GLuint GetTexture(unsigned int num) const { return m_textures[num]; }
	inline GLuint GetDepthTexture() const { return m_depthTexture; }
};

#endif