#include "CTimer.h"

enco::core::uint32 enco::core::CTimer::s_currentTime = 0;
enco::core::float32 enco::core::CTimer::s_deltaTime = 0.0f;

void enco::core::CTimer::create()
{
	s_currentTime = get_current_time();
}

void enco::core::CTimer::release()
{
}

void enco::core::CTimer::update()
{
	uint32 time = get_current_time();
	s_deltaTime = (time - s_currentTime) * 0.001f;
	s_currentTime = time;
}

// privates
enco::core::uint32 enco::core::CTimer::get_current_time()
{
#ifdef __ENCO3D_WIN32
	return timeGetTime();
#elif __ENCO3D_APPLE
	timeval time;
	gettimeofday(&time, 0);
	return (uint32)((time.tv_sec * 1000) + (time.tv_usec / 1000));
#else
	return 0;
#endif
}