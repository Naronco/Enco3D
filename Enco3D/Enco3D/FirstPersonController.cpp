#include "FirstPersonController.h"

Enco3D::Component::FirstPersonController::FirstPersonController()
{
}

Enco3D::Component::FirstPersonController::FirstPersonController(float moveSpeed, float rotateSpeed)
{
	m_moveSpeed = moveSpeed;
	m_rotateSpeed = rotateSpeed;
}

void Enco3D::Component::FirstPersonController::Update()
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
		Vector3f motion;

		if (Input::IsKeyDown(SDLK_w))
		{
			motion += GetTransform()->GetRotation().GetForward();
		}
		if (Input::IsKeyDown(SDLK_s))
		{
			motion -= GetTransform()->GetRotation().GetForward();
		}
		if (Input::IsKeyDown(SDLK_a))
		{
			motion -= GetTransform()->GetRotation().GetRight();
		}
		if (Input::IsKeyDown(SDLK_d))
		{
			motion += GetTransform()->GetRotation().GetRight();
		}

		if (motion.GetSquaredLength() > 0.0f)
		{
			motion = motion.Normalize() * speed;
			GetTransform()->Translate(motion);
		}

		int relativeX = Input::GetMouseX() - (GetWindow()->GetWidth() >> 1);
		int relativeY = Input::GetMouseY() - (GetWindow()->GetHeight() >> 1);

		bool rotateY = relativeX != 0;
		bool rotateX = relativeY != 0;

		if (rotateY)
		{
			Quaternionf rotationAmount = Quaternionf(Vector3f(0, 1, 0), MathUtil::ToRadians(relativeX * m_rotateSpeed));
			GetTransform()->SetRotation((rotationAmount * GetTransform()->GetRotation()).Normalize());
		}
		if (rotateX)
		{
			Quaternionf rotationAmount = Quaternionf(GetTransform()->GetRotation().GetRight(), MathUtil::ToRadians(relativeY * m_rotateSpeed));
			GetTransform()->SetRotation((rotationAmount * GetTransform()->GetRotation()).Normalize());
		}

		if (rotateY || rotateX)
		{
			GetWindow()->SetCursorPosition(GetWindow()->GetWidth() >> 1, GetWindow()->GetHeight() >> 1);
		}
	}
}