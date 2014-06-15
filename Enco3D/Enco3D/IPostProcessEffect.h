#ifndef _ENCO3D_IPOSTPROCESSEFFECT_H_
#define _ENCO3D_IPOSTPROCESSEFFECT_H_

#include "IGameComponent.h"
#include "ShaderPool.h"
#include <vector>
#include <string>
#include "DLLExport.h"

namespace Enco3D
{
	namespace Component
	{
		class DLL_EXPORT IPostProcessEffect : public Core::IGameComponent
		{
		protected:
			Rendering::Texture2D *m_gbuffer0;
			Rendering::Texture2D *m_gbuffer1;
			Rendering::Texture2D *m_depthBuffer;

			unsigned int m_generatedImageSlot;

			inline void renderScreen() { getRenderingEngine()->getRenderWindow()->render(); }
			inline Core::Matrix4x4f getWorldViewProjectionMatrix() const { return getRenderingEngine()->getPostProcessWorldViewProjectionMatrix(); }
			inline Core::Vector2f getTexelSize() const { return getRenderingEngine()->getPostProcessTexelSize(); }
			inline unsigned int getWidth() const { return getRenderingEngine()->getWidth(); }
			inline unsigned int getHeight() const { return getRenderingEngine()->getHeight(); }

		public:
			virtual void postProcess(const Camera *camera) = 0;

			virtual Rendering::Texture2D *getFinalBuffer() = 0;

			inline void setGBuffer0(Rendering::Texture2D *buffer) { m_gbuffer0 = buffer; }
			inline void setGBuffer1(Rendering::Texture2D *buffer) { m_gbuffer1 = buffer; }
			inline void setDepthBuffer(Rendering::Texture2D *buffer) { m_depthBuffer = buffer; }

			inline unsigned int getGeneratedImageSlot() const { return m_generatedImageSlot; }
		};
	}
}

#endif