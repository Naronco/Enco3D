#include "Timer.h"

#include <iostream>

Enco3D::Core::Timer::Timer()
{
	CURRENT_TIME(&m_lastTime);
	CURRENT_TIME(&m_time);
	CURRENT_TIME(&m_lastFrameTime);
}

Enco3D::Core::Timer::Timer(bool printFps)
{
	m_printFps = printFps;

	CURRENT_TIME(&m_lastTime);
	CURRENT_TIME(&m_time);
	CURRENT_TIME(&m_lastFrameTime);
}

void Enco3D::Core::Timer::update()
{
	CURRENT_TIME(&m_time);
	m_deltaTime = (m_time - m_lastTime) * 0.001f;
	m_lastTime = m_time;

	if (m_time - m_lastFrameTime > 1000)
	{
		if (m_printFps)
			Core::DebugLogger::log(std::to_string(m_fpsCounter) + " fps");

		m_fps = m_fpsCounter;
		m_fpsCounter = 0;
		m_lastFrameTime += 1000;
	}
}