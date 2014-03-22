#include "FirstPersonController.h"

FirstPersonController::FirstPersonController()
{
}

FirstPersonController::FirstPersonController(float moveSpeed, float rotateSpeed)
{
	m_moveSpeed = moveSpeed;
	m_rotateSpeed = rotateSpeed;
}

void FirstPersonController::Update()
{
	float speed = GetTimer()->GetDeltaTime() * m_moveSpeed;

	if (!GetWindow()->IsFocused())
	{
		m_mouseLocked = false;
	}

	if (Input::IsMouseButtonDown(MouseButton::Left) && !m_mouseLocked)
	{
		m_mouseLocked = true;
		GetWindow()->SetCursor(false);
		GetWindow()->SetCursorPosition(GetWindow()->GetWidth() >> 1, GetWindow()->GetHeight() >> 1);
	}

	if (Input::IsKeyDown(SDLK_ESCAPE) && m_mouseLocked)
	{
		m_mouseLocked = false;
		GetWindow()->SetCursor(true);
	}

	if (m_mouseLocked)
	{
		if (Input::IsKeyDown(SDLK_w))
		{
			GetTransform()->SetTranslation(GetTransform()->GetTranslation() + (GetTransform()->GetRotation().GetForward() * speed));
		}
		if (Input::IsKeyDown(SDLK_s))
		{
			GetTransform()->SetTranslation(GetTransform()->GetTranslation() + (-GetTransform()->GetRotation().GetForward() * speed));
		}
		if (Input::IsKeyDown(SDLK_a))
		{
			GetTransform()->SetTranslation(GetTransform()->GetTranslation() + (-GetTransform()->GetRotation().GetRight() * speed));
		}
		if (Input::IsKeyDown(SDLK_d))
		{
			GetTransform()->SetTranslation(GetTransform()->GetTranslation() + (GetTransform()->GetRotation().GetRight() * speed));
		}

		int relativeX = Input::GetMouseX() - (GetWindow()->GetWidth() >> 1);
		int relativeY = Input::GetMouseY() - (GetWindow()->GetHeight() >> 1);

		bool rotateY = relativeX != 0;
		bool rotateX = relativeY != 0;

		if (rotateY)
		{
			Quaternionf rotationAmount = Quaternionf(Vector3f(0, 1, 0), ToRadians(relativeX * m_rotateSpeed));
			GetTransform()->SetRotation((rotationAmount * GetTransform()->GetRotation()).Normalize());
		}
		if (rotateX)
		{
			Quaternionf rotationAmount = Quaternionf(GetTransform()->GetRotation().GetRight(), ToRadians(relativeY * m_rotateSpeed));
			GetTransform()->SetRotation((rotationAmount * GetTransform()->GetRotation()).Normalize());
		}

		if (rotateY || rotateX)
		{
			GetWindow()->SetCursorPosition(GetWindow()->GetWidth() >> 1, GetWindow()->GetHeight() >> 1);
		}
	}
}