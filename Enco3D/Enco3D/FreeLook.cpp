#include "FreeLook.h"

Enco3D::Component::FreeLook::FreeLook()
{

}

Enco3D::Component::FreeLook::FreeLook(float rotateSpeed)
{
	m_rotateSpeed = rotateSpeed;
}

void Enco3D::Component::FreeLook::Update()
{
	static unsigned int lastMouseX = Core::Input::GetMouseX();
	static unsigned int lastMouseY = Core::Input::GetMouseY();

	unsigned int currentMouseX = Core::Input::GetMouseX();
	unsigned int currentMouseY = Core::Input::GetMouseY();

	int relativeX = currentMouseX - lastMouseX;
	int relativeY = currentMouseY - lastMouseY;

	lastMouseX = currentMouseX;
	lastMouseY = currentMouseY;

	static float rotationXAmount = 0.0f;
	static float rotationYAmount = 0.0f;

	if (Core::Input::IsMouseButtonDown(Core::Mouse::Right))
	{
		bool rotateX = relativeX != 0;
		bool rotateY = relativeY != 0;

		if (rotateX) rotationXAmount += (float)relativeX * m_rotateSpeed;
		if (rotateY) rotationYAmount += (float)relativeY * m_rotateSpeed;
	}

	Core::Quaternionf rotationAmountX = Core::Quaternionf(Core::Vector3f(0, 1, 0), Core::MathUtil::ToRadians(rotationXAmount));
	GetTransform()->SetRotation((rotationAmountX * GetTransform()->GetRotation()).Normalize());

	Core::Quaternionf rotationAmountY = Core::Quaternionf(GetTransform()->GetRotation().GetRight(), Core::MathUtil::ToRadians(rotationYAmount));
	GetTransform()->SetRotation((rotationAmountY * GetTransform()->GetRotation()).Normalize());

	rotationXAmount *= 0.92f;
	rotationYAmount *= 0.92f;
}