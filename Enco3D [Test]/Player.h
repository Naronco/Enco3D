#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
using namespace std;

#include <Enco3D/Enco3D.h>

using namespace Enco3D::Core;
using namespace Enco3D::Component;

class Player : public IGameComponent
{
private:
	Camera *m_camera{ nullptr };
	RigidBody *m_rigidBody{ nullptr };
	Vector3f m_cameraOffset;

public:
	void Init()
	{
		m_cameraOffset.Set(0, 5, -5);
	}

	void Update()
	{
		if (m_rigidBody == nullptr)
		{
			m_rigidBody = (RigidBody *)GetGameObject()->GetGameComponent("rigidBody");
		}

		if (m_camera == nullptr)
		{
			m_camera = (Camera *)GetGameObject()->GetChild("mainCamera")->GetGameComponent("camera");
		}

		bool walking = false;
		float walkSpeed = 4.0f;
		float rotateSpeed = 3.0f;

		Vector3f linearVelocity, angularVelocity;

		if (Input::IsKeyDown(SDLK_w))
		{
			linearVelocity += GetTransform()->GetRotation().GetForward() * walkSpeed;
			walking = true;
		}

		if (Input::IsKeyDown(SDLK_s))
		{
			linearVelocity += GetTransform()->GetRotation().GetForward() * -walkSpeed;
			walking = true;
		}

		if (Input::IsKeyDown(SDLK_a))
		{
			Quaternionf rotationAmount = Quaternionf(Vector3f(0, 1, 0), -1.0f * GetTimer()->GetDeltaTime());
			m_camera->GetTransform()->SetRotation((rotationAmount * m_camera->GetTransform()->GetRotation()).Normalize());
			//angularVelocity += Vector3f(0, -rotateSpeed, 0);
			//linearVelocity += GetTransform()->GetRotation().GetRight() * -walkSpeed;
			//walking = true;
		}

		if (Input::IsKeyDown(SDLK_d))
		{
			Quaternionf rotationAmount = Quaternionf(Vector3f(0, 1, 0), 1.0f * GetTimer()->GetDeltaTime());
			m_camera->GetTransform()->SetRotation((rotationAmount * m_camera->GetTransform()->GetRotation()).Normalize());
			//angularVelocity += Vector3f(0, rotateSpeed, 0);
			//linearVelocity += GetTransform()->GetRotation().GetRight() * walkSpeed;
			//walking = true;
		}

		linearVelocity.y = m_rigidBody->GetLinearVelocity().y;
		m_rigidBody->SetLinearVelocity(linearVelocity);
		m_rigidBody->SetAngularVelocity(angularVelocity);

		m_camera->LookAt(m_cameraOffset, GetTransform()->GetTranslation() - m_camera->GetTransform()->GetTranslation());
	}
};

#endif