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

void Enco3D::Component::Camera::LookAt(const Enco3D::Core::Vector3f &pos, const Enco3D::Core::Vector3f &lookAt)
{
	GetTransform()->SetTranslation(pos);

	Vector3f forward = (lookAt - pos).Normalize();
	Vector3f up = Vector3f(0, 1, 0);
	Vector3f right = up.Cross(forward).Normalize();
	up = forward.Cross(right).Normalize();

	GetTransform()->SetRotation(Quaternionf(forward, right, up));
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