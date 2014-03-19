#ifndef _ENCO3D_CAMERA_H_
#define _ENCO3D_CAMERA_H_

#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

template <typename T>
struct FrustumPlane
{
	T a, b, c, d;

	inline FrustumPlane() : a(0), b(0), c(0), d(0)
	{
	}

	inline FrustumPlane(T _a, T _b, T _c, T _d) : a(_a), b(_b), c(_c), d(_d)
	{
	}

	inline FrustumPlane<T> &Normalize()
	{
		T norm = (T)(1.0 / sqrt(a * a + b * b + c * c));
		a *= norm;
		b *= norm;
		c *= norm;
		return *this;
	}
};

typedef FrustumPlane<float> FrustumPlanef;

class Camera
{
private:
	Vector3f m_translation, m_scaling;
	Quaternionf m_rotation;
	Matrix4x4f m_projection;

	FrustumPlanef m_frustumPlanes[6];

public:
	Camera();
	Camera(float fov, float aspect, float zNear, float zFar);
	Camera(float left, float right, float bottom, float top, float zNear, float zFar);

	void SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar);
	void SetOrthographicProjection(float left, float right, float bottom, float top, float zNear, float zFar);

	Matrix4x4f GetViewProjection() const;

	void Rotate(const Quaternionf &q);
	void Move(const Vector3f &dir, float amount);

	inline Vector3f GetTranslation() const { return m_translation; }
	inline Quaternionf GetRotation() const { return m_rotation; }
	inline Vector3f GetScaling() const { return m_scaling; }
	inline Matrix4x4f GetProjection() const { return m_projection; }
	inline Vector3f GetForward() const { return m_rotation.GetForward(); }
	inline Vector3f GetUp() const { return m_rotation.GetUp(); }
	inline Vector3f GetRight() const { return m_rotation.GetRight(); }
};

#endif