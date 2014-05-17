#include "FreeLook.h"

Enco3D::Component::FreeLook::FreeLook()
{

}

Enco3D::Component::FreeLook::FreeLook(float rotateSpeed)
{
	m_rotateSpeed = rotateSpeed;
}

void Enco3D::Component::FreeLook::update()
{
	static unsigned int lastMouseX = Core::Input::getMouseX();
	static unsigned int lastMouseY = Core::Input::getMouseY();

	unsigned int currentMouseX = Core::Input::getMouseX();
	unsigned int currentMouseY = Core::Input::getMouseY();

	int relativeX = currentMouseX - lastMouseX;
	int relativeY = currentMouseY - lastMouseY;

	lastMouseX = currentMouseX;
	lastMouseY = currentMouseY;

	static float rotationXAmount = 0.0f;
	static float rotationYAmount = 0.0f;

	if (Core::Input::isMouseButtonDown(Core::Mouse::Right))
	{
		bool rotateX = relativeX != 0;
		bool rotateY = relativeY != 0;

		if (rotateX) rotationXAmount += (float)relativeX * m_rotateSpeed;
		if (rotateY) rotationYAmount += (float)relativeY * m_rotateSpeed;
	}

	Core::Quaternionf rotationAmountX = Core::Quaternionf(Core::Vector3f(0, 1, 0), Core::MathUtil::toRadians(rotationXAmount));
	getTransform()->setRotation((rotationAmountX * getTransform()->getRotation()).normalize());

	Core::Quaternionf rotationAmountY = Core::Quaternionf(getTransform()->getRotation().getRight(), Core::MathUtil::toRadians(rotationYAmount));
	getTransform()->setRotation((rotationAmountY * getTransform()->getRotation()).normalize());

	rotationXAmount *= 0.92f;
	rotationYAmount *= 0.92f;
}