#ifndef _ENCO3D_CAMERA_H_
#define _ENCO3D_CAMERA_H_

#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "IGameComponent.h"

class Camera : public IGameComponent
{
private:
	Matrix4x4f m_projection;

public:
	Camera();
	Camera(float fov, float aspect, float zNear, float zFar);
	Camera(float left, float right, float bottom, float top, float zNear, float zFar);

	void InitRendering();

	void SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar);
	void SetOrthographicProjection(float left, float right, float bottom, float top, float zNear, float zFar);

	Matrix4x4f GetViewProjection() const;

	inline void SetTranslation(const Vector3f &translation) { GetTransform()->SetTranslation(translation); }
	inline void SetRotation(const Quaternionf &rotation) { GetTransform()->SetRotation(rotation); }
	inline void SetScaling(const Vector3f &scaling) { GetTransform()->SetScaling(scaling); }

	inline Matrix4x4f GetProjection() const { return m_projection; }
	inline Vector3f GetForward() const { return GetTransform()->GetRotation().GetForward(); }
	inline Vector3f GetUp() const { return GetTransform()->GetRotation().GetUp(); }
	inline Vector3f GetRight() const { return GetTransform()->GetRotation().GetRight(); }
};

#endif