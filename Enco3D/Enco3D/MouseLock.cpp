#include "MouseLock.h"

void Enco3D::Component::MouseLock::update()
{
	if (!getWindow()->isFocused())
		m_mouseLocked = false;

	if (Core::Input::isMouseButtonDown(Core::Mouse::Left) && !m_mouseLocked)
	{
		m_mouseLocked = true;
		getWindow()->setCursor(false);
		getWindow()->setCursorPosition(getWindow()->getWidth() >> 1, getWindow()->getHeight() >> 1);
	}

	if (Core::Input::isKeyDown(Core::Keyboard::Escape) && m_mouseLocked)
	{
		m_mouseLocked = false;
		getWindow()->setCursor(true);
	}

	FreeMove *freeMove = (FreeMove*)m_gameObject->getGameComponent<FreeMove>();
	FreeLook *freeLook = (FreeLook*)m_gameObject->getGameComponent<FreeLook>();

	if (freeMove != nullptr)
		freeMove->setMovingEnabled(m_mouseLocked);
	
	if (freeLook != nullptr)
		freeLook->setRotationEnabled(m_mouseLocked);
}