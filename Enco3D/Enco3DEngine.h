#ifndef _ENCO3D_ENCO3DENGINE_H_
#define _ENCO3D_ENCO3DENGINE_H_

#include "GLWindow.h"
#include "Timer.h"
#include "IGame.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "AudioEngine.h"
#include "Random.h"

namespace Enco3D
{
	namespace Core
	{
		using namespace Rendering;
		using namespace Physics;
		using namespace Audio;

		class Enco3DEngine
		{
		private:
			GLWindow *m_window{ nullptr };
			Timer *m_timer{ nullptr };
			IGame *m_game{ nullptr };
			RenderingEngine *m_renderingEngine{ nullptr };
			PhysicsEngine *m_physicsEngine{ nullptr };
			AudioEngine *m_audioEngine{ nullptr };

		public:
			inline Enco3DEngine() {  }

			void Init(char *windowTitle, unsigned int windowWidth, unsigned int windowHeight, IGame *game);
			void Deinit();
			void MainLoop();

			inline GLWindow *GetWindow() const { return m_window; }
			inline Timer *GetTimer() const { return m_timer; }
			inline IGame *GetGame() const { return m_game; }
			inline RenderingEngine *GetRenderingEngine() const { return m_renderingEngine; }
			inline PhysicsEngine *GetPhysicsEngine() const { return m_physicsEngine; }
			inline AudioEngine *GetAudioEngine() const { return m_audioEngine; }

		public:
			inline static Enco3DEngine *GetInstance()
			{
				static Enco3DEngine *coreEngine = nullptr;

				if (coreEngine == nullptr)
				{
					coreEngine = new Enco3DEngine;
				}

				return coreEngine;
			}
		};
	}
}

#endif