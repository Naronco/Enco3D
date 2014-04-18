#ifndef __ENCO3D_CCAMERA_H_INCLUDED__
#define __ENCO3D_CCAMERA_H_INCLUDED__

#include "SMatrixNxM.h"
#include "SVector3.h"

namespace enco
{
	namespace core
	{
		template <typename T> class CCamera
		{
		private:
			math::Vector3<T> m_translation, m_rotation;
			math::MatrixNxM<T, 4, 4> m_projectionMatrix;

		public:
			inline void setTranslation(T x, T y, T z) { m_translation.set(x, y, z); }
			inline void setTranslation(const math::Vector3<T> &v) { m_translation.set(v); }

			inline void setRotation(T yaw, T pitch, T roll) { m_rotation.set(pitch, yaw, roll); }
			
			inline void setPerspectiveProjection(T fov, T aspect, T zNear, T zFar) { m_projectionMatrix.setPerspectiveProjection(fov, aspect, zNear, zFar); }
			inline void setOrthographicProjection(T left, T right, T bottom, T top, T zNear, T zFar) { m_projectionMatrix.setOrthographicProjection(left, right, bottom, top, zNear, zFar); }

			inline math::MatrixNxM<T, 4, 4> getViewMatrix() const {
				math::MatrixNxM<T, 4, 4> rotationX, rotationY, rotationZ;
				rotationX.setRotationX(m_rotation.x);
				rotationY.setRotationY(m_rotation.y);
				rotationZ.setRotationZ(m_rotation.z);

				math::MatrixNxM<T, 4, 4> rotationMatrix;
				rotationMatrix = rotationX * rotationY * rotationZ;

				math::MatrixNxM<T, 4, 4> translationMatrix;
				translationMatrix.setTranslation(-m_translation.x, -m_translation.y, -m_translation.z);

				return rotationMatrix * translationMatrix;
			}

			inline math::MatrixNxM<T, 4, 4> getProjectionMatrix() const { return m_projectionMatrix; }
			inline math::MatrixNxM<T, 4, 4> getViewProjectionMatrix() const { return m_projectionMatrix * getViewMatrix(); }

			inline math::Vector3<T> getTranslation() const { return m_translation; }

			inline T getYaw() const { return m_rotation.y; }
			inline T getPitch() const { return m_rotation.x; }
			inline T getRoll() const { return m_rotation.z; }

			inline math::Vector3<T> getForward() const { return math::Vector3<T>().setDirectionFromYawPitch(m_rotation.y, m_rotation.x); }
			inline math::Vector3<T> getUp() const { return math::Vector3<T>().setDirectionFromYawPitch(m_rotation.y, m_rotation.x + (T)math::pi_div_2_f64); }
			inline math::Vector3<T> getRight() const { return math::Vector3<T>().setDirectionFromYawPitch(m_rotation.y + (T)math::pi_div_2_f64, 0); }

			inline math::Vector2<T> getForward2D() const { return math::Vector2<T>().setDirectionFromAngle(m_rotation.y); }
			inline math::Vector2<T> getRight2D() const { return math::Vector2<T>().setDirectionFromAngle(m_rotation.y + (T)math::pi_div_2_f64); }
		};

		typedef CCamera<float32> CCamera_f32;
		typedef CCamera<float64> CCamera_f64;
	}
}

#endif