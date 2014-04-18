#ifndef __ENCO3D_IGRAPHICSDEVICE_H_INCLUDED__
#define __ENCO3D_IGRAPHICSDEVICE_H_INCLUDED__

#include "SDimension2.h"
#include "SColor4.h"
#include "EVertexComponents.h"
#include "SMatrixNxM.h"
#include "SColor4.h"
#include "SVector2.h"
#include "SVector3.h"

namespace enco
{
	namespace core
	{
		struct IVertexBuffer {};
		struct IIndexBuffer {};

		struct IShader {};
		struct IShaderType {};
		
		struct ITexture2D {};

		enum EShaderTypes
		{
			eSHADERTYPE_VERTEXSHADER,
			eSHADERTYPE_PIXELSHADER,
		};

		enum ETextureFilter
		{
			eTEXTUREFILTER_NEAREST,
			eTEXTUREFILTER_LINEAR,
		};

		enum ETextureWrap
		{
			eTEXTUREWRAP_CLAMP,
			eTEXTUREWRAP_REPEAT,
		};

		enum ETextureSlot
		{
			eTEXTURESLOT_SLOT0,
			eTEXTURESLOT_SLOT1,
			eTEXTURESLOT_SLOT2,
			eTEXTURESLOT_SLOT3,
			eTEXTURESLOT_SLOT4,
			eTEXTURESLOT_SLOT5,
			eTEXTURESLOT_SLOT6,
			eTEXTURESLOT_SLOT7,
			eTEXTURESLOT_SLOT8,
			eTEXTURESLOT_SLOT9,
		};

		enum EBlendingModes
		{
			eBLENDINGMODE_DISABLED,
			eBLENDINGMODE_ADD,
			eBLENDINGMODE_TRANSPARENCY,
		};

		class IGraphicsDevice
		{
		public:
			virtual void create(const Dimension2u32 &size) = 0;
			virtual void release() = 0;

			virtual void beginScene(const Color4f32 &clearColor) = 0;
			virtual void endScene() = 0;

			virtual void setSize(const Dimension2u32 &size) = 0;

			virtual IVertexBuffer *buildVertexBuffer(uint32 sizeInBytes, void *data, sint32 vertexComponents) = 0;
			virtual void updateVertexBuffer(IVertexBuffer *vertexBuffer, sint32 offset, sint32 size, void *data) = 0;
			virtual void releaseVertexBuffer(IVertexBuffer *vertexBuffer) = 0;
			
			virtual IIndexBuffer *buildIndexBuffer(uint32 sizeInBytes, void *data, uint32 indexCount) = 0;
			virtual void releaseIndexBuffer(IIndexBuffer *indexBuffer) = 0;

			virtual IShaderType *buildShaderType(const char *filename, sint32 shaderType) = 0;
			virtual void releaseShaderType(IShaderType *shaderType) = 0;

			virtual IShader *buildShader() = 0;
			virtual void appendShaderType(IShader *shader, const IShaderType *shaderType) = 0;
			virtual void compileShader(IShader *shader) = 0;
			virtual void releaseShader(IShader *shader) = 0;

			virtual void setUniformMatrix4x4f32(IShader *shader, const char *name, const math::Matrix4x4f32 &matrix) = 0;
			virtual void setUniformMatrix4x4f64(IShader *shader, const char *name, const math::Matrix4x4f64 &matrix) = 0;
			virtual void setUniformMatrix3x3f32(IShader *shader, const char *name, const math::Matrix3x3f32 &matrix) = 0;
			virtual void setUniformMatrix3x3f64(IShader *shader, const char *name, const math::Matrix3x3f64 &matrix) = 0;
			virtual void setUniformColor4f32(IShader *shader, const char *name, const Color4f32 &color) = 0;
			virtual void setUniformColor4f64(IShader *shader, const char *name, const Color4f64 &color) = 0;
			virtual void setUniformVector2f32(IShader *shader, const char *name, const math::Vector2f32 &vector) = 0;
			virtual void setUniformVector2f64(IShader *shader, const char *name, const math::Vector2f64 &vector) = 0;
			virtual void setUniformVector3f32(IShader *shader, const char *name, const math::Vector3f32 &vector) = 0;
			virtual void setUniformVector3f64(IShader *shader, const char *name, const math::Vector3f64 &vector) = 0;
			virtual void setUniformTexture2D(IShader *shader, const char *name, sint32 slot) = 0;
			virtual void setUniformFloat32(IShader *shader, const char *name, float32 value) = 0;
			virtual void setUniformInt32(IShader *shader, const char *name, sint32 value) = 0;

			virtual void setActiveShader(const IShader *shader) = 0;

			virtual ITexture2D *buildTexture2D(const char *filename, sint32 filter, sint32 wrap) = 0;
			virtual void setActiveTexture2D(ITexture2D *texture, sint32 slot) = 0;
			virtual void releaseTexture2D(ITexture2D *texture) = 0;

			virtual void render(const IVertexBuffer *vertexBuffer, const IIndexBuffer *indexBuffer) = 0;

			virtual void setDepthWritingEnabled(bool enabled) = 0;
			virtual void setBlendingMode(sint32 blendingMode) = 0;
		};
	}
}

#endif