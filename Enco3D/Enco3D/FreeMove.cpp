#include "FreeMove.h"

Enco3D::Component::FreeMove::FreeMove() {  }

Enco3D::Component::FreeMove::FreeMove(float moveSpeed) : m_moveSpeed(moveSpeed) {  }

void Enco3D::Component::FreeMove::Update()
{
	if (m_movingEnabled)
	{
		static Core::Vector3f motion;

		Core::Vector3f movement;

		if (Core::Input::IsKeyDown(m_moveForwardKey))
			movement += GetTransform()->GetRotation().GetForward();
		if (Core::Input::IsKeyDown(m_moveBackwardKey))
			movement -= GetTransform()->GetRotation().GetForward();
		if (Core::Input::IsKeyDown(m_moveLeftKey))
			movement -= GetTransform()->GetRotation().GetRight();
		if (Core::Input::IsKeyDown(m_moveRightKey))
			movement += GetTransform()->GetRotation().GetRight();

		if (movement.GetSquaredLength() > 0.0f)
		{
			movement.Normalize();
			movement *= m_moveSpeed;
			motion += movement;
		}

		motion *= 0.92f;
		GetTransform()->Translate(motion);
	}
}