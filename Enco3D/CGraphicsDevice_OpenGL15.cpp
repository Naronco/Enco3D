#include "CGraphicsDevice_OpenGL15.h"
#include "stb_image.h"

void enco::core::CGraphicsDevice_OpenGL15::create(const enco::core::Dimension2u32 &size)
{
	glViewport(0, 0, (sint32)size.x, (sint32)size.y);
}

void enco::core::CGraphicsDevice_OpenGL15::release()
{
}

void enco::core::CGraphicsDevice_OpenGL15::beginScene(const enco::core::Color4f32 &clearColor)
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void enco::core::CGraphicsDevice_OpenGL15::endScene()
{
}

void enco::core::CGraphicsDevice_OpenGL15::setSize(const enco::core::Dimension2u32 &size)
{
	glViewport(0, 0, (sint32)size.x, (sint32)size.y);
}

enco::core::IVertexBuffer *enco::core::CGraphicsDevice_OpenGL15::buildVertexBuffer(uint32 sizeInBytes, void *data, sint32 vertexComponents)
{
	VertexBuffer_OpenGL15 *result;

	uint8 numVertexComponents = 0;
	uint8 vertexSize = 0;

	if ((vertexComponents & eVERTEXCOMPONENT_POSITION3F32) == eVERTEXCOMPONENT_POSITION3F32) { numVertexComponents++; vertexSize += (sizeof(float32)* 3); }
	if ((vertexComponents & eVERTEXCOMPONENT_TEXCOORD2F32) == eVERTEXCOMPONENT_TEXCOORD2F32) { numVertexComponents++; vertexSize += (sizeof(float32)* 2); }
	if ((vertexComponents & eVERTEXCOMPONENT_TEXCOORD3F32) == eVERTEXCOMPONENT_TEXCOORD3F32) { numVertexComponents++; vertexSize += (sizeof(float32)* 3); }
	if ((vertexComponents & eVERTEXCOMPONENT_NORMAL3F32  ) == eVERTEXCOMPONENT_NORMAL3F32  ) { numVertexComponents++; vertexSize += (sizeof(float32)* 3); }
	if ((vertexComponents & eVERTEXCOMPONENT_COLOR3F32   ) == eVERTEXCOMPONENT_COLOR3F32   ) { numVertexComponents++; vertexSize += (sizeof(float32)* 3); }
	if ((vertexComponents & eVERTEXCOMPONENT_TANGENT3F32 ) == eVERTEXCOMPONENT_TANGENT3F32 ) { numVertexComponents++; vertexSize += (sizeof(float32)* 3); }
	if ((vertexComponents & eVERTEXCOMPONENT_BINORMAL3F32) == eVERTEXCOMPONENT_BINORMAL3F32) { numVertexComponents++; vertexSize += (sizeof(float32)* 3); }

	result = new VertexBuffer_OpenGL15;
	result->sizeInBytes = sizeInBytes;
	result->data = data;
	result->vertexComponents = vertexComponents;
	result->numVertexComponents = numVertexComponents;
	result->vertexSize = vertexSize;

	glGenBuffers(1, &result->vertexBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, result->vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, GL_STATIC_DRAW);

	return result;
}

void enco::core::CGraphicsDevice_OpenGL15::updateVertexBuffer(enco::core::IVertexBuffer *vertexBuffer, sint32 offset, sint32 size, void *data)
{
	glBindBuffer(GL_ARRAY_BUFFER, ((VertexBuffer_OpenGL15*)vertexBuffer)->vertexBufferId);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void enco::core::CGraphicsDevice_OpenGL15::releaseVertexBuffer(IVertexBuffer *vertexBuffer)
{
	glDeleteBuffers(1, &((VertexBuffer_OpenGL15*)vertexBuffer)->vertexBufferId);
	delete vertexBuffer;
}

enco::core::IIndexBuffer *enco::core::CGraphicsDevice_OpenGL15::buildIndexBuffer(uint32 sizeInBytes, void *data, uint32 indexCount)
{
	IndexBuffer_OpenGL15 *result;

	result = new IndexBuffer_OpenGL15;
	result->sizeInBytes = sizeInBytes;
	result->data = data;
	result->indexCount = indexCount;
	
	glGenBuffers(1, &result->indexBufferId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result->indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInBytes, data, GL_STATIC_DRAW);
	
	return result;
}

void enco::core::CGraphicsDevice_OpenGL15::releaseIndexBuffer(IIndexBuffer *indexBuffer)
{
	glDeleteBuffers(1, &((IndexBuffer_OpenGL15*)indexBuffer)->indexBufferId);
	delete indexBuffer;
}

enco::core::IShaderType *enco::core::CGraphicsDevice_OpenGL15::buildShaderType(const char *filename, sint32 shaderType)
{
	uint32 gl_shaderType;

	switch (shaderType)
	{
	case eSHADERTYPE_VERTEXSHADER: gl_shaderType = GL_VERTEX_SHADER;   break;
	case eSHADERTYPE_PIXELSHADER:  gl_shaderType = GL_FRAGMENT_SHADER; break;
	}

	ShaderType_OpenGL15 *result;

	result = new ShaderType_OpenGL15;
	result->gl_shaderType = gl_shaderType;
	result->shaderTypeId = glCreateShader(gl_shaderType);

	__ASSERT(result->shaderTypeId != 0);

	std::string shaderText;

	io::CFile shaderFile;
	shaderFile.open(filename);

	__ASSERT(shaderFile.isOpen());

	while (shaderFile.isValidCursor())
	{
		shaderText += shaderFile.getLine() + "\n";
	}

	shaderFile.close();

	const char *shaderTextCharArray = shaderText.c_str();
	sint32 shaderTextLength = (sint32)shaderText.length();

	glShaderSource(result->shaderTypeId, 1, &shaderTextCharArray, &shaderTextLength);
	glCompileShader(result->shaderTypeId);

	return result;
}

void enco::core::CGraphicsDevice_OpenGL15::releaseShaderType(enco::core::IShaderType *shaderType)
{
	glDeleteShader(((ShaderType_OpenGL15*)shaderType)->shaderTypeId);
	delete shaderType;
}

enco::core::IShader *enco::core::CGraphicsDevice_OpenGL15::buildShader()
{
	Shader_OpenGL15 *result;

	result = new Shader_OpenGL15;
	result->program = glCreateProgram();

	return result;
}

void enco::core::CGraphicsDevice_OpenGL15::appendShaderType(enco::core::IShader *shader, const enco::core::IShaderType *shaderType)
{
	glAttachShader(((Shader_OpenGL15*)shader)->program, ((ShaderType_OpenGL15*)shaderType)->shaderTypeId);
}

void enco::core::CGraphicsDevice_OpenGL15::compileShader(enco::core::IShader *shader)
{
	glLinkProgram(((Shader_OpenGL15*)shader)->program);
	glValidateProgram(((Shader_OpenGL15*)shader)->program);
}

void enco::core::CGraphicsDevice_OpenGL15::releaseShader(enco::core::IShader *shader)
{
	glDeleteProgram(((Shader_OpenGL15*)shader)->program);
	delete shader;
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformMatrix4x4f32(IShader *shader, const char *name, const enco::core::math::Matrix4x4f32 &matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), 1, GL_TRUE, &(matrix.values[0][0]));
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformMatrix4x4f64(IShader *shader, const char *name, const enco::core::math::Matrix4x4f64 &matrix)
{
	glUniformMatrix4dv(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), 1, GL_TRUE, &(matrix.values[0][0]));
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformMatrix3x3f32(IShader *shader, const char *name, const enco::core::math::Matrix3x3f32 &matrix)
{
	glUniformMatrix3fv(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), 1, GL_TRUE, &(matrix.values[0][0]));
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformMatrix3x3f64(IShader *shader, const char *name, const enco::core::math::Matrix3x3f64 &matrix)
{
	glUniformMatrix3dv(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), 1, GL_TRUE, &(matrix.values[0][0]));
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformColor4f32(IShader *shader, const char *name, const enco::core::Color4f32 &color)
{
	glUniform4f(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), color.r, color.g, color.b, color.a);
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformColor4f64(IShader *shader, const char *name, const enco::core::Color4f64 &color)
{
	glUniform4d(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), color.r, color.g, color.b, color.a);
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformVector2f32(IShader *shader, const char *name, const enco::core::math::Vector2f32 &vector)
{
	glUniform2f(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), vector.x, vector.y);
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformVector2f64(IShader *shader, const char *name, const enco::core::math::Vector2f64 &vector)
{
	glUniform2d(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), vector.x, vector.y);
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformVector3f32(IShader *shader, const char *name, const enco::core::math::Vector3f32 &vector)
{
	glUniform3f(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), vector.x, vector.y, vector.z);
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformVector3f64(IShader *shader, const char *name, const enco::core::math::Vector3f64 &vector)
{
	glUniform3d(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), vector.x, vector.y, vector.z);
}

void enco::core::CGraphicsDevice_OpenGL15::setActiveShader(const IShader *shader)
{
	glUseProgram(shader == 0 ? 0 : ((Shader_OpenGL15*)shader)->program);
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformTexture2D(IShader *shader, const char *name, sint32 slot)
{
	glUniform1i(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), slot);
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformFloat32(IShader *shader, const char *name, float32 value)
{
	glUniform1f(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), value);
}

void enco::core::CGraphicsDevice_OpenGL15::setUniformInt32(IShader *shader, const char *name, sint32 value)
{
	glUniform1i(glGetUniformLocation(((Shader_OpenGL15*)shader)->program, name), value);
}

enco::core::ITexture2D *enco::core::CGraphicsDevice_OpenGL15::buildTexture2D(const char *filename, sint32 filter, sint32 wrap)
{
	Texture2D_OpenGL15 *result = 0;
	uint32 textureId = 0;

	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);
	switch (filter)
	{
	case eTEXTUREFILTER_NEAREST:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;

	case eTEXTUREFILTER_LINEAR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}

	switch (wrap)
	{
	case eTEXTUREWRAP_CLAMP:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		break;

	case eTEXTUREWRAP_REPEAT:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	}

	sint32 width, height, bytesPerPixel;
	uint8 *pixels = stbi_load(filename, &width, &height, &bytesPerPixel, 4);

	__ASSERT(pixels != 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	result = new Texture2D_OpenGL15;
	result->textureId = textureId;

	return result;
}

void enco::core::CGraphicsDevice_OpenGL15::setActiveTexture2D(ITexture2D *texture, sint32 slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ((Texture2D_OpenGL15*)texture)->textureId);
}

void enco::core::CGraphicsDevice_OpenGL15::releaseTexture2D(ITexture2D *texture)
{
	__ASSERT(texture != 0);
	glDeleteTextures(1, &((Texture2D_OpenGL15*)texture)->textureId);
	delete texture;
}

void enco::core::CGraphicsDevice_OpenGL15::render(const IVertexBuffer *vertexBuffer, const IIndexBuffer *indexBuffer)
{
	VertexBuffer_OpenGL15 *vb = (VertexBuffer_OpenGL15*)vertexBuffer;
	IndexBuffer_OpenGL15 *ib = (IndexBuffer_OpenGL15*)indexBuffer;

	for (uint8 i = 0; i < vb->numVertexComponents; i++)
		glEnableVertexAttribArray(i);
	
	glBindBuffer(GL_ARRAY_BUFFER, vb->vertexBufferId);
	uint8 vertexCounter = 0;
	float32 *vertexPointer = 0;

	if ((vb->vertexComponents & eVERTEXCOMPONENT_POSITION3F32) == eVERTEXCOMPONENT_POSITION3F32)
	{
		glVertexAttribPointer(vertexCounter, 3, GL_FLOAT, GL_FALSE, vb->vertexSize, vertexPointer);
		vertexPointer += 3;
		vertexCounter++;
	}

	if ((vb->vertexComponents & eVERTEXCOMPONENT_TEXCOORD2F32) == eVERTEXCOMPONENT_TEXCOORD2F32)
	{
		glVertexAttribPointer(vertexCounter, 2, GL_FLOAT, GL_FALSE, vb->vertexSize, vertexPointer);
		vertexPointer += 2;
		vertexCounter++;
	}

	if ((vb->vertexComponents & eVERTEXCOMPONENT_TEXCOORD3F32) == eVERTEXCOMPONENT_TEXCOORD3F32)
	{
		glVertexAttribPointer(vertexCounter, 3, GL_FLOAT, GL_FALSE, vb->vertexSize, vertexPointer);
		vertexPointer += 3;
		vertexCounter++;
	}

	if ((vb->vertexComponents & eVERTEXCOMPONENT_NORMAL3F32) == eVERTEXCOMPONENT_NORMAL3F32)
	{
		glVertexAttribPointer(vertexCounter, 3, GL_FLOAT, GL_FALSE, vb->vertexSize, vertexPointer);
		vertexPointer += 3;
		vertexCounter++;
	}

	if ((vb->vertexComponents & eVERTEXCOMPONENT_COLOR3F32) == eVERTEXCOMPONENT_COLOR3F32)
	{
		glVertexAttribPointer(vertexCounter, 3, GL_FLOAT, GL_FALSE, vb->vertexSize, vertexPointer);
		vertexPointer += 3;
		vertexCounter++;
	}

	if ((vb->vertexComponents & eVERTEXCOMPONENT_TANGENT3F32) == eVERTEXCOMPONENT_TANGENT3F32)
	{
		glVertexAttribPointer(vertexCounter, 3, GL_FLOAT, GL_FALSE, vb->vertexSize, vertexPointer);
		vertexPointer += 3;
		vertexCounter++;
	}

	if ((vb->vertexComponents & eVERTEXCOMPONENT_BINORMAL3F32) == eVERTEXCOMPONENT_BINORMAL3F32)
	{
		glVertexAttribPointer(vertexCounter, 3, GL_FLOAT, GL_FALSE, vb->vertexSize, vertexPointer);
		vertexPointer += 3;
		vertexCounter++;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->indexBufferId);
	glDrawElements(GL_TRIANGLES, ib->indexCount, GL_UNSIGNED_INT, 0);

	for (uint8 i = 0; i < vb->numVertexComponents; i++)
		glDisableVertexAttribArray(i);
}

void enco::core::CGraphicsDevice_OpenGL15::setDepthWritingEnabled(bool enabled)
{
	glDepthMask(enabled);
}

void enco::core::CGraphicsDevice_OpenGL15::setBlendingMode(sint32 blendingMode)
{
	switch (blendingMode)
	{
	case eBLENDINGMODE_DISABLED:
		glDisable(GL_BLEND);
		break;

	case eBLENDINGMODE_ADD:
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		break;

	case eBLENDINGMODE_TRANSPARENCY:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	}
}