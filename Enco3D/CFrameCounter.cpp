#include "CFrameCounter.h"

void enco::core::CFrameCounter::create(enco::core::CTimer *timer)
{
	m_timer = timer;
	m_frameCount = 0;
	m_lastFrameTime = m_timer->getTime();
	m_printFpsInConsoleEnabled = true;
}

void enco::core::CFrameCounter::release()
{
}

void enco::core::CFrameCounter::update()
{
	m_frameCount++;

	uint32 now = m_timer->getTime();
	if (now - m_lastFrameTime > 1000)
	{
		m_framesPerSecond = m_frameCount;
		m_frameCount = 0;
		m_lastFrameTime += 1000;

		if (m_printFpsInConsoleEnabled)
			std::cout << m_framesPerSecond << " fps" << std::endl;
	}
}