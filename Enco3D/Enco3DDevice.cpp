#include "Enco3DDevice.h"

void enco::core::Enco3DDevice::create(const char *title, uint8 samples)
{
	m_window->create((char*)title, m_displayDim, samples);
	m_graphicsDevice->create(m_displayDim);
	m_sceneManager->create(m_graphicsDevice);
	m_timer->create();
	m_physicsDevice->setTimer(m_timer);
	m_physicsDevice->create();
	m_frameCounter->create(m_timer);
}

void enco::core::Enco3DDevice::release()
{
	m_frameCounter->release();
	m_timer->release();
	m_sceneManager->release();
	m_physicsDevice->release();
	m_graphicsDevice->release();
	m_window->release();
}

bool enco::core::Enco3DDevice::run()
{
	m_window->update();
	m_timer->update();
	m_frameCounter->update();
	m_physicsDevice->update();

	return !m_window->isCloseRequested();
}