#ifndef _ENCO3D_ENCO3DENGINE_H_
#define _ENCO3D_ENCO3DENGINE_H_

#include "GLWindow.h"
#include "Timer.h"
#include "IGame.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "AudioEngine.h"
#include "Random.h"
#include "TSingleton.h"
#include "GUIText.h"

#include <string>

namespace Enco3D
{
	namespace Core
	{
		class Enco3DEngine : public TSingleton<Enco3DEngine>
		{
		private:
			GLWindow *m_window{ nullptr };
			Timer *m_timer{ nullptr };
			IGame *m_game{ nullptr };
			Rendering::RenderingEngine *m_renderingEngine{ nullptr };
			Physics::PhysicsEngine *m_physicsEngine{ nullptr };
			Audio::AudioEngine *m_audioEngine{ nullptr };

		public:
			inline Enco3DEngine() {  }

			void init(char *windowTitle, unsigned int windowWidth, unsigned int windowHeight, bool multisampleEnabled, unsigned int aaSamples, IGame *game);
			void deinit();
			void mainLoop();

			inline GLWindow *getWindow() const { return m_window; }
			inline Timer *getTimer() const { return m_timer; }
			inline IGame *getGame() const { return m_game; }
			inline Rendering::RenderingEngine *getRenderingEngine() const { return m_renderingEngine; }
			inline Physics::PhysicsEngine *getPhysicsEngine() const { return m_physicsEngine; }
			inline Audio::AudioEngine *getAudioEngine() const { return m_audioEngine; }
		};
	}
}

#endif