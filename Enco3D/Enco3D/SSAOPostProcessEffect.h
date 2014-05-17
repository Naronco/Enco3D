#ifndef _ENCO3D_SSAOPOSTPROCESSEFFECT_H_
#define _ENCO3D_SSAOPOSTPROCESSEFFECT_H_

#include "IPostProcessEffect.h"

namespace Enco3D
{
	namespace Component
	{
		class SSAOPostProcessEffect : public IPostProcessEffect
		{
		private:
			Rendering::Framebuffer *m_ssaoFramebuffer, *m_blurFramebuffer;
			Rendering::Texture2D *m_ssaoBuffer, *m_blurBuffer, *m_randomTexture;
			Rendering::Shader *m_ssaoShader, *m_blurShader;

			float m_ssaoRadius{ 0.5f }, m_ssaoPower{ 1.0f }, m_ssaoStrength{ 1.0f };

		public:
			void initRendering();
			void deinit();

			void postProcess(const Camera *camera);
			void resize(unsigned int width, unsigned int height);

			inline void setSSAORadius(float radius) { m_ssaoRadius = radius; }
			inline void setSSAOPower(float power) { m_ssaoPower = power; }
			inline void setSSAOStrength(float strength) { m_ssaoStrength = strength; }

			inline Rendering::Texture2D *getFinalBuffer() { return m_blurBuffer; }
		};
	}
}

#endif