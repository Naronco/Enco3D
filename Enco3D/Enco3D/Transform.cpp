#include "Transform.h"

#include "Camera.h"

Enco3D::Core::Transform::Transform()
{
	m_translation.set(0, 0, 0);
	m_rotation.set(0, 0, 0, 1);
	m_scaling.set(1, 1, 1);
}

Enco3D::Core::Transform::Transform(const Transform &other)
{
	m_parentTransform = other.getParentTransform();
	m_translation.set(other.getTranslation());
	m_rotation.set(other.getRotation());
	m_scaling.set(other.getScaling());
}

void Enco3D::Core::Transform::update()
{
	if (m_parentTransform != nullptr && m_parentTransform->hasChanged())
		m_parentMatrix = m_parentTransform->getTransformation();
	
	if (m_billboardEnabled)
		m_rotation.set(m_billboardCamera->getTransform()->getRotation());

	Matrix4x4f translationMatrix = Matrix4x4f().translate(m_translation.x, m_translation.y, m_translation.z);
	Matrix4x4f rotationMatrix = m_rotation.toRotationMatrix4x4();
	Matrix4x4f scalingMatrix = Matrix4x4f().scale(m_scaling.x, m_scaling.y, m_scaling.z);

	m_prevTransformation = m_transformation;
	m_transformation = getParentMatrix() * translationMatrix * scalingMatrix * rotationMatrix;
}

bool Enco3D::Core::Transform::hasChanged() const
{
	return true;
}

void Enco3D::Core::Transform::translate(float x, float y, float z)
{
	m_translation.x += x;
	m_translation.y += y;
	m_translation.z += z;
}

void Enco3D::Core::Transform::translate(const Vector3f &translation)
{
	m_translation += translation;
}

void Enco3D::Core::Transform::rotate(const Quaternionf &rotation)
{
	m_rotation = (rotation * m_rotation).normalize();
}

void Enco3D::Core::Transform::scale(float x, float y, float z)
{
	m_scaling.set(m_scaling.x * x, m_scaling.y * y, m_scaling.z * z);
}

void Enco3D::Core::Transform::scale(float s)
{
	m_scaling.set(m_scaling.x * s, m_scaling.y * s, m_scaling.z * s);
}

void Enco3D::Core::Transform::scale(const Vector3f &scaling)
{
	m_scaling.set(m_scaling.x * scaling.x, m_scaling.y * scaling.y, m_scaling.z * scaling.z);
}

Enco3D::Core::Matrix4x4f Enco3D::Core::Transform::getTransformation()
{
	return m_transformation;
}