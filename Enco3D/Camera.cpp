#include "Camera.h"

Camera::Camera()
{
	m_projection.SetIdentity();
}

Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
	m_projection.SetPerspectiveProjection(fov, aspect, zNear, zFar);
}

Camera::Camera(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection.SetOrthographicProjection(left, right, bottom, top, zNear, zFar);
}

void Camera::InitRendering()
{
	GetRenderingEngine()->SetMainCamera(this);
}

void Camera::SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar)
{
	m_projection.SetPerspectiveProjection(fov, aspect, zNear, zFar);
}

void Camera::SetOrthographicProjection(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection.SetOrthographicProjection(left, right, bottom, top, zNear, zFar);
}

Matrix4x4f Camera::GetViewProjection() const
{
	Matrix4x4f cameraRotation = (-GetTransform()->GetRotation()).ToRotationMatrix4x4();
	Vector3f cameraPos = -GetTransform()->GetTranslation();

	Matrix4x4f cameraTranslation = Matrix4x4f().Translate(cameraPos.x, cameraPos.y, cameraPos.z);
	
	return m_projection * (cameraRotation * cameraTranslation);
}