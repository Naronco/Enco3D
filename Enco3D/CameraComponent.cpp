#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
}

CameraComponent::CameraComponent(Camera *camera)
{
	m_camera = camera;
}

CameraComponent::~CameraComponent()
{
	if (m_camera)
	{
		delete m_camera;
		m_camera = nullptr;
	}
}

void CameraComponent::InitRendering()
{
	GetRenderingEngine()->SetMainCamera(m_camera);
}

void CameraComponent::Update()
{
	m_camera->SetTranslation(GetTransform()->GetTranslation());
	m_camera->SetRotation(GetTransform()->GetRotation());
	m_camera->SetScaling(GetTransform()->GetScaling());
}