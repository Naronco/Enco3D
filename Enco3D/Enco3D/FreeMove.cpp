#include "FreeMove.h"

Enco3D::Component::FreeMove::FreeMove() {  }

Enco3D::Component::FreeMove::FreeMove(float moveSpeed) : m_moveSpeed(moveSpeed) {  }

void Enco3D::Component::FreeMove::update()
{
	if (m_movingEnabled)
	{
		static Core::Vector3f motion;

		Core::Vector3f movement;

		if (Core::Input::isKeyDown(m_moveForwardKey))
			movement += getTransform()->getRotation().getForward();
		if (Core::Input::isKeyDown(m_moveBackwardKey))
			movement -= getTransform()->getRotation().getForward();
		if (Core::Input::isKeyDown(m_moveLeftKey))
			movement -= getTransform()->getRotation().getRight();
		if (Core::Input::isKeyDown(m_moveRightKey))
			movement += getTransform()->getRotation().getRight();
		if (Core::Input::isKeyDown(m_moveUpKey))
			movement += Core::Vector3Template::Up;
		if (Core::Input::isKeyDown(m_moveDownKey))
			movement -= Core::Vector3Template::Up;

		if (movement.getSquaredLength() > 0.0f)
		{
			movement = movement.normalize();
			movement *= m_moveSpeed;
			motion += movement;
		}

		motion *= 0.92f;
		getTransform()->translate(motion);
	}
}