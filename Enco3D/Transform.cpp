#include "Transform.h"

Enco3D::Core::Transform::Transform()
{
	m_translation.Set(0, 0, 0);
	m_rotation.Set(0, 0, 0, 1);
	m_scaling.Set(1, 1, 1);
}

Enco3D::Core::Transform::Transform(const Transform &other)
{
	m_parentTransform = other.GetParentTransform();
	m_translation.Set(other.GetTranslation());
	m_rotation.Set(other.GetRotation());
	m_scaling.Set(other.GetScaling());
}

void Enco3D::Core::Transform::Update()
{
}

bool Enco3D::Core::Transform::HasChanged()
{
	if (m_parentTransform != nullptr && m_parentTransform->HasChanged())
	{
		return true;
	}

	if (m_translation != m_oldTranslation)
	{
		return true;
	}

	if (m_rotation != m_oldRotation)
	{
		return true;
	}

	if (m_scaling != m_oldScaling)
	{
		return true;
	}

	return false;
}

void Enco3D::Core::Transform::Translate(const Vector3f &translation)
{
	m_translation += translation;
}

void Enco3D::Core::Transform::Rotate(const Quaternionf &rotation)
{
	m_rotation = (rotation * m_rotation).Normalize();
}

void Enco3D::Core::Transform::Scale(const Vector3f &scaling)
{
	m_scaling.Set(m_scaling.x * scaling.x, m_scaling.y * scaling.y, m_scaling.z * scaling.z);
}

Enco3D::Core::Matrix4x4f Enco3D::Core::Transform::GetTransformation()
{
	Matrix4x4f translationMatrix = Matrix4x4f().Translate(m_translation.x, m_translation.y, m_translation.z);
	Matrix4x4f rotationMatrix = m_rotation.ToRotationMatrix4x4();
	Matrix4x4f scalingMatrix = Matrix4x4f().Scale(m_scaling.x, m_scaling.y, m_scaling.z);

	return translationMatrix * scalingMatrix * rotationMatrix * GetParentMatrix();
}