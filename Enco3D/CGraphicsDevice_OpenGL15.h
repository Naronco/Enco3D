#ifndef __ENCO3D_CGRAPHICSDEVICE_OPENGL15_INCLUDED_H__
#define __ENCO3D_CGRAPHICSDEVICE_OPENGL15_INCLUDED_H__

#include <GL/glew.h>
#include <vector>
#include "IGraphicsDevice.h"
#include "Enco3DDatatypes.h"
#include "Enco3DUtil.h"
#include "CFile.h"

namespace enco
{
	namespace core
	{
		struct VertexBuffer_OpenGL15 : public IVertexBuffer
		{
			uint32 vertexBufferId;
			uint32 sizeInBytes;
			void *data;
			sint32 vertexComponents;
			uint8 numVertexComponents;
			uint8 vertexSize;
		};

		struct IndexBuffer_OpenGL15 : public IIndexBuffer
		{
			uint32 indexBufferId;
			uint32 sizeInBytes;
			void *data;
			uint32 indexCount;
		};

		struct Shader_OpenGL15 : public IShader
		{
			uint32 program;
		};

		struct ShaderType_OpenGL15 : public IShaderType
		{
			sint32 gl_shaderType;
			uint32 shaderTypeId;
		};

		struct Texture2D_OpenGL15 : public ITexture2D
		{
			uint32 textureId;
		};

		class CGraphicsDevice_OpenGL15 : public IGraphicsDevice
		{
		public:
			void create(const Dimension2u32 &size);
			void release();

			void beginScene(const Color4f32 &clearColor);
			void endScene();

			void setSize(const Dimension2u32 &size);

			IVertexBuffer *buildVertexBuffer(uint32 sizeInBytes, void *data, sint32 vertexComponents);
			void updateVertexBuffer(IVertexBuffer *vertexBuffer, sint32 offset, sint32 size, void *data);
			void releaseVertexBuffer(IVertexBuffer *vertexBuffer);

			IIndexBuffer *buildIndexBuffer(uint32 sizeInBytes, void *data, uint32 indexCount);
			void releaseIndexBuffer(IIndexBuffer *indexBuffer);

			IShaderType *buildShaderType(const char *filename, sint32 shaderType);
			void releaseShaderType(IShaderType *shaderType);

			IShader *buildShader();
			void appendShaderType(IShader *shader, const IShaderType *shaderType);
			void compileShader(IShader *shader);
			void releaseShader(IShader *shader);

			void setUniformMatrix4x4f32(IShader *shader, const char *name, const math::Matrix4x4f32 &matrix);
			void setUniformMatrix4x4f64(IShader *shader, const char *name, const math::Matrix4x4f64 &matrix);
			void setUniformMatrix3x3f32(IShader *shader, const char *name, const math::Matrix3x3f32 &matrix);
			void setUniformMatrix3x3f64(IShader *shader, const char *name, const math::Matrix3x3f64 &matrix);
			void setUniformColor4f32(IShader *shader, const char *name, const Color4f32 &color);
			void setUniformColor4f64(IShader *shader, const char *name, const Color4f64 &color);
			void setUniformVector2f32(IShader *shader, const char *name, const math::Vector2f32 &vector);
			void setUniformVector2f64(IShader *shader, const char *name, const math::Vector2f64 &vector);
			void setUniformVector3f32(IShader *shader, const char *name, const math::Vector3f32 &vector);
			void setUniformVector3f64(IShader *shader, const char *name, const math::Vector3f64 &vector);
			void setUniformTexture2D(IShader *shader, const char *name, sint32 slot);
			void setUniformFloat32(IShader *shader, const char *name, float32 value);
			void setUniformInt32(IShader *shader, const char *name, sint32 value);

			void setActiveShader(const IShader *shader);

			ITexture2D *buildTexture2D(const char *filename, sint32 filter, sint32 wrap);
			void setActiveTexture2D(ITexture2D *texture, sint32 slot);
			void releaseTexture2D(ITexture2D *texture);

			void render(const IVertexBuffer *vertexBuffer, const IIndexBuffer *indexBuffer);

			void setDepthWritingEnabled(bool enabled);
			void setBlendingMode(sint32 blendingMode);
		};
	}
}

#endif