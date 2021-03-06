#ifndef _ENCO3D_TIMER_H_
#define _ENCO3D_TIMER_H_

#ifdef _WIN32
#	include <Windows.h>
#	pragma comment (lib, "winmm.lib")
#	ifndef CURRENT_TIME
#		define CURRENT_TIME(x) { *x = timeGetTime(); }
#	endif
#elif __APPLE__
#	include <sys/time.h>
#	ifndef CURRENT_TIME
#		define CURRENT_TIME(x) { timeval time; gettimeofday(&time, nullptr); *x = time.wSecond * 1000 + time.wMilliseconds; }
#	endif
#endif

#include "DebugLogger.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Core
	{
		class DLL_EXPORT Timer
		{
		private:
			unsigned int m_lastTime, m_time, m_fpsCounter{ 0 }, m_fps{ 0 };
			float m_deltaTime;

			unsigned int m_lastFrameTime;
			bool m_printFps{ false };

		public:
			Timer();
			Timer(bool printFps);

			void update();

			inline void increaseFps() { m_fpsCounter++; }

			inline void setPrintFps(bool printFps) { m_printFps = printFps; }

			inline unsigned int getFPS() const { return m_fps; }
			inline float getDeltaTime() const { return m_deltaTime; }
			inline unsigned int getTime() const { return m_time; }
		};
	}
}

#endif