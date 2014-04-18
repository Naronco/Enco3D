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
		using namespace Rendering;
		using namespace Physics;
		using namespace Audio;

		const unsigned int __consoleMaxLineCount = 16;

		class Enco3DEngine : public TSingleton<Enco3DEngine>
		{
		private:
			GLWindow *m_window{ nullptr };
			Timer *m_timer{ nullptr };
			IGame *m_game{ nullptr };
			RenderingEngine *m_renderingEngine{ nullptr };
			PhysicsEngine *m_physicsEngine{ nullptr };
			AudioEngine *m_audioEngine{ nullptr };

			GameObject *m_consoleObject{ nullptr };
			GUIText *m_consoleGuiText{ nullptr };
			std::string m_consoleText;
			unsigned int m_consoleLineCount{ 0 };

		public:
			inline Enco3DEngine() {  }

			void Init(char *windowTitle, unsigned int windowWidth, unsigned int windowHeight, bool multisampleEnabled, unsigned int aaSamples, IGame *game);
			void Deinit();
			void MainLoop();

			void Console_Print(char *text);
			void Console_PrintLine(char *text);
			void Console_PrintError(char *text);
			void Console_CheckAndShort();

			inline GLWindow *GetWindow() const { return m_window; }
			inline Timer *GetTimer() const { return m_timer; }
			inline IGame *GetGame() const { return m_game; }
			inline RenderingEngine *GetRenderingEngine() const { return m_renderingEngine; }
			inline PhysicsEngine *GetPhysicsEngine() const { return m_physicsEngine; }
			inline AudioEngine *GetAudioEngine() const { return m_audioEngine; }
		};
	}
}

#endif