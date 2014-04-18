#ifndef __ENCO3D_CTIMER_H_INCLUDED__
#define __ENCO3D_CTIMER_H_INCLUDED__

#include "Enco3DDatatypes.h"
#include "Enco3DUtil.h"

#ifdef __ENCO3D_WIN32
#	include <Windows.h>
#	pragma comment (lib, "winmm.lib")
#elif __ENCO3D_APPLE
#	include <sys/time.h>
#endif

namespace enco
{
	namespace core
	{
		class CTimer
		{
		private:
			static uint32 s_currentTime;
			static float32 s_deltaTime;

			static uint32 get_current_time();

		public:
			static void create();
			static void release();

			static void update();

			inline static uint32 getTime() { return s_currentTime; }
			inline static float32 getDeltaTime() { return s_deltaTime; }
		};
	}
}

#endif