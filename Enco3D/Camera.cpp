#include "Camera.h"

Camera::Camera()
{
	m_projection.SetIdentity();
	
	m_translation.Set(0, 0, 0);
	m_rotation.Set(0, 0, 0, 1);
	m_scaling.Set(1, 1, 1);
}

Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
	m_projection.SetPerspectiveProjection(fov, aspect, zNear, zFar);

	m_translation.Set(0, 0, 0);
	m_rotation.Set(0, 0, 0, 1);
	m_scaling.Set(1, 1, 1);
}

Camera::Camera(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection.SetOrthographicProjection(left, right, bottom, top, zNear, zFar);

	m_translation.Set(0, 0, 0);
	m_rotation.Set(0, 0, 0, 1);
	m_scaling.Set(1, 1, 1);
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
	Matrix4x4f cameraRotation = (-m_rotation).ToRotationMatrix4x4();
	Vector3f cameraPos = -m_translation;

	Matrix4x4f cameraTranslation = Matrix4x4f().Translate(cameraPos.x, cameraPos.y, cameraPos.z);
	
	Matrix4x4f projectedMatrix = m_projection * (cameraRotation * cameraTranslation);
	
	return projectedMatrix;
}

void Camera::Rotate(const Quaternionf &q)
{
	m_rotation = (q * m_rotation).Normalize();
}

void Camera::Move(const Vector3f &dir, float amount)
{
	m_translation += dir * amount;
}