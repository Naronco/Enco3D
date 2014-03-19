#ifndef _ENCO3D_TRANSFORM_H_
#define _ENCO3D_TRANSFORM_H_

#include "Vector3.h"
#include "Quaternion.h"

class Transform
{
private:
	Transform *m_parentTransform{ nullptr };
	Matrix4x4f m_parentMatrix;

	Vector3f m_translation;
	Quaternionf m_rotation;
	Vector3f m_scaling;

	Vector3f m_oldTranslation;
	Quaternionf m_oldRotation;
	Vector3f m_oldScaling;

public:
	Transform();
	Transform(const Transform &other);

	void Update();
	bool HasChanged();

	void Translate(const Vector3f &translation);
	void Rotate(const Quaternionf &rotation);
	void Scale(const Vector3f &scaling);

	Matrix4x4f GetTransformation();
	
	inline void SetParentTransform(Transform *parentTransform) { m_parentTransform = parentTransform; }

	inline void SetTranslation(const Vector3f &translation) { m_translation = translation; }
	inline void SetRotation(const Quaternionf &rotation) { m_rotation = rotation; }
	inline void SetScaling(const Vector3f &scaling) { m_scaling = scaling; }

	inline Transform *GetParentTransform() const { return m_parentTransform; }
	inline Matrix4x4f GetParentMatrix() { if (m_parentTransform != nullptr && m_parentTransform->HasChanged()) { m_parentMatrix = m_parentTransform->GetTransformation(); } return m_parentMatrix; }

	inline Vector3f GetTranslation() const { return m_translation; }
	inline Quaternionf GetRotation() const { return m_rotation; }
	inline Vector3f GetScaling() const { return m_scaling; }

	inline Vector3f GetTransformedTranslation() { return GetParentMatrix() * m_translation; }
	inline Quaternionf GetTransformedRotation() const { Quaternionf parentRotation = m_parentTransform != nullptr ? m_parentTransform->GetTransformedRotation() : Quaternionf(0, 0, 0, 1); return parentRotation * m_rotation; }
};

#endif