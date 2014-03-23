#include "Camera.h"

Enco3D::Component::Camera::Camera()
{
	m_projection.SetIdentity();
}

Enco3D::Component::Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
	m_projection.SetPerspectiveProjection(fov, aspect, zNear, zFar);
}

Enco3D::Component::Camera::Camera(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection.SetOrthographicProjection(left, right, bottom, top, zNear, zFar);
}

void Enco3D::Component::Camera::InitRendering()
{
	GetRenderingEngine()->SetMainCamera(this);
}

void Enco3D::Component::Camera::SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar)
{
	m_projection.SetPerspectiveProjection(fov, aspect, zNear, zFar);
}

void Enco3D::Component::Camera::SetOrthographicProjection(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection.SetOrthographicProjection(left, right, bottom, top, zNear, zFar);
}

Enco3D::Core::Matrix4x4f Enco3D::Component::Camera::GetViewProjection() const
{
	Matrix4x4f cameraRotation = (-GetTransform()->GetRotation()).ToRotationMatrix4x4();
	Vector3f cameraPos = -GetTransform()->GetTranslation();

	Matrix4x4f cameraTranslation = Matrix4x4f().Translate(cameraPos.x, cameraPos.y, cameraPos.z);
	
	return m_projection * (cameraRotation * cameraTranslation);
}