#ifndef __ENCO3D_CTRANSFORM_H_INCLUDED__
#define __ENCO3D_CTRANSFORM_H_INCLUDED__

#include "SMatrixNxM.h"

namespace enco
{
	namespace core
	{
		template <typename T>
		class CTransform
		{
		private:
			math::Vector3<T> m_translation, m_rotation, m_scaling;

		public:
			inline CTransform() { m_scaling.set(1, 1, 1); }

			inline void setTranslation(T x, T y, T z) { m_translation.set(x, y, z); }
			inline void setRotationX(T angle) { m_rotation.x = angle; }
			inline void setRotationY(T angle) { m_rotation.y = angle; }
			inline void setRotationZ(T angle) { m_rotation.z = angle; }
			inline void setScaling(T x, T y, T z) { m_scaling.set(x, y, z); }
			inline void setScaling(T scaling) { m_scaling.set(scaling, scaling, scaling); }

			inline math::MatrixNxM<T, 4, 4> getTransformationMatrix() const
			{
				math::MatrixNxM<T, 4, 4> translationMatrix;
				translationMatrix.setTranslation(m_translation.x, m_translation.y, m_translation.z);

				math::MatrixNxM<T, 4, 4> rotationX, rotationY, rotationZ;
				rotationX.setRotationX(m_rotation.x);
				rotationY.setRotationY(m_rotation.y);
				rotationZ.setRotationZ(m_rotation.z);

				math::MatrixNxM<T, 4, 4> rotationMatrix;
				rotationMatrix = rotationX * rotationY * rotationZ;

				math::MatrixNxM<T, 4, 4> scalingMatrix;
				scalingMatrix.setScaling(m_scaling.x, m_scaling.y, m_scaling.z);

				math::MatrixNxM<T, 4, 4> transformationMatrix;
				transformationMatrix = rotationMatrix * scalingMatrix * translationMatrix;

				return transformationMatrix;
			}

			inline math::Vector3<T> getTranslation() const { return m_translation; }
			inline math::Vector3<T> getRotation() const { return m_rotation; }
			inline math::Vector3<T> getScaling() const { return m_scaling; }
		};

		typedef CTransform<float32> CTransform_f32;
		typedef CTransform<float64> CTransform_f64;
	}
}

#endif