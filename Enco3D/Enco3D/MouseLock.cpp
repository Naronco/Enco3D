#include "MouseLock.h"

void Enco3D::Component::MouseLock::Update()
{
	if (!GetWindow()->IsFocused())
		m_mouseLocked = false;

	if (Core::Input::IsMouseButtonDown(Core::Mouse::Left) && !m_mouseLocked)
	{
		m_mouseLocked = true;
		GetWindow()->SetCursor(false);
		GetWindow()->SetCursorPosition(GetWindow()->GetWidth() >> 1, GetWindow()->GetHeight() >> 1);
	}

	if (Core::Input::IsKeyDown(Core::Keyboard::Escape) && m_mouseLocked)
	{
		m_mouseLocked = false;
		GetWindow()->SetCursor(true);
	}

	FreeMove *freeMove = (FreeMove*)m_gameObject->GetGameComponent<FreeMove>();
	FreeLook *freeLook = (FreeLook*)m_gameObject->GetGameComponent<FreeLook>();

	if (freeMove != nullptr)
		freeMove->SetMovingEnabled(m_mouseLocked);
	
	if (freeLook != nullptr)
		freeLook->SetRotationEnabled(m_mouseLocked);
}