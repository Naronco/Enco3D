#include "StopWatch.h"

void Enco3D::Core::StopWatch::start()
{

}

unsigned int Enco3D::Core::StopWatch::stop()
{
	if (!m_stopping)
	{

	}

	unsigned int now;
	CURRENT_TIME(&now);

	m_elapsedTime = now - m_startTime;

	return m_elapsedTime;
}