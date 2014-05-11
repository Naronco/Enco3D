#include "Transform.h"

#include "Camera.h"

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
	if (m_parentTransform != nullptr && m_parentTransform->HasChanged())
		m_parentMatrix = m_parentTransform->GetTransformation();
	
	if (m_billboardEnabled)
		m_rotation.Set(m_billboardCamera->GetTransform()->GetRotation());

	Matrix4x4f translationMatrix = Matrix4x4f().Translate(m_translation.x, m_translation.y, m_translation.z);
	Matrix4x4f rotationMatrix = m_rotation.ToRotationMatrix4x4();
	Matrix4x4f scalingMatrix = Matrix4x4f().Scale(m_scaling.x, m_scaling.y, m_scaling.z);

	m_prevTransformation = m_transformation;
	m_transformation = GetParentMatrix() * translationMatrix * scalingMatrix * rotationMatrix;
}

bool Enco3D::Core::Transform::HasChanged() const
{
	return true;
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
	return m_transformation;
}