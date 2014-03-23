#include "Timer.h"

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

void Enco3D::Core::Timer::Update()
{
	CURRENT_TIME(&m_time);
	m_deltaTime = (m_time - m_lastTime) * 0.001f;
	m_lastTime = m_time;

	m_fpsCounter++;

	if (m_time - m_lastFrameTime > 1000)
	{
		if (m_printFps)
		{
			cout << m_fpsCounter << " FPS" << endl;
		}

		m_fps = m_fpsCounter;
		m_fpsCounter = 0;
		m_lastFrameTime += 1000;
	}
}