#ifndef _ENCO3D_STOPWATCH_H_
#define _ENCO3D_STOPWATCH_H_

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

namespace Enco3D
{
	namespace Core
	{
		class StopWatch
		{
		private:
			bool m_stopping{ false };
			unsigned int m_startTime, m_elapsedTime;

		public:
			void start();
			unsigned int stop();

			inline unsigned int getElapsed() const { return m_elapsedTime; }
		};
	}
}

#endif