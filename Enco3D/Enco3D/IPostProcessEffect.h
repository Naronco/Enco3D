#ifndef _ENCO3D_IPOSTPROCESSEFFECT_H_
#define _ENCO3D_IPOSTPROCESSEFFECT_H_

#include "IGameComponent.h"
#include "ShaderPool.h"
#include <vector>
#include <string>

namespace Enco3D
{
	namespace Component
	{
		class IPostProcessEffect : public Core::IGameComponent
		{
		protected:
			Rendering::Texture2D *m_positionBuffer;
			Rendering::Texture2D *m_normalBuffer;
			Rendering::Texture2D *m_lightBuffer;
			Rendering::Texture2D *m_backgroundBuffer;
			Rendering::Texture2D *m_velocityBuffer;
			Rendering::Texture2D *m_depthBuffer;
			Rendering::Texture2D *m_compositeBuffer;

			unsigned int m_generatedImageSlot;

			inline void RenderScreen() { GetRenderingEngine()->GetRenderWindow()->Render(); }
			inline Core::Matrix4x4f GetWorldViewProjectionMatrix() const { return GetRenderingEngine()->GetPostProcessWorldViewProjectionMatrix(); }
			inline Core::Vector2f GetTexelSize() const { return GetRenderingEngine()->GetPostProcessTexelSize(); }
			inline unsigned int GetWidth() const { return GetRenderingEngine()->GetWidth(); }
			inline unsigned int GetHeight() const { return GetRenderingEngine()->GetHeight(); }

		public:
			virtual void PostProcess(const Camera *camera) = 0;
			
			virtual Rendering::Texture2D *GetFinalBuffer() = 0;

			inline void SetPositionBuffer(Rendering::Texture2D *buffer) { m_positionBuffer = buffer; }
			inline void SetNormalBuffer(Rendering::Texture2D *buffer) { m_normalBuffer = buffer; }
			inline void SetLightBuffer(Rendering::Texture2D *buffer) { m_lightBuffer = buffer; }
			inline void SetBackgroundBuffer(Rendering::Texture2D *buffer) { m_backgroundBuffer = buffer; }
			inline void SetVelocityBuffer(Rendering::Texture2D *buffer) { m_velocityBuffer = buffer; }
			inline void SetDepthBuffer(Rendering::Texture2D *buffer) { m_depthBuffer = buffer; }
			inline void SetCompositeBuffer(Rendering::Texture2D *buffer) { m_compositeBuffer = buffer; }

			inline unsigned int GetGeneratedImageSlot() const { return m_generatedImageSlot; }
		};
	}
}

#endif