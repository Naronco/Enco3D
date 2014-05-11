#ifndef _ENCO3D_TRANSFORM_H_
#define _ENCO3D_TRANSFORM_H_

#include "Vector3.h"
#include "Quaternion.h"

namespace Enco3D
{
	namespace Component
	{
		class Camera;
	}
}

namespace Enco3D
{
	namespace Core
	{
		class Transform
		{
		private:
			Transform *m_parentTransform{ nullptr };
			Matrix4x4f m_parentMatrix;

			Matrix4x4f m_transformation;
			Matrix4x4f m_prevTransformation;

			Vector3f m_translation;
			Quaternionf m_rotation;
			Vector3f m_scaling;

			bool m_billboardEnabled{ false };
			Component::Camera *m_billboardCamera{ nullptr };

		public:
			Transform();
			Transform(const Transform &other);

			void Update();
			bool HasChanged() const;

			void Translate(const Vector3f &translation);
			void Rotate(const Quaternionf &rotation);
			void Scale(const Vector3f &scaling);

			Matrix4x4f GetTransformation();

			inline void SetParentTransform(Transform *parentTransform) { m_parentTransform = parentTransform; }

			inline void SetTranslation(const Vector3f &translation) { m_translation = translation; }
			inline void SetRotation(const Quaternionf &rotation) { m_rotation = rotation; }
			inline void SetScaling(const Vector3f &scaling) { m_scaling = scaling; }

			inline void SetBillboardEnabled(bool enabled) { m_billboardEnabled = enabled; }
			inline void SetBillboardCamera(Component::Camera *camera) { m_billboardCamera = camera; }

			inline Matrix4x4f GetPrevTransformation() const { return m_prevTransformation; }

			inline Transform *GetParentTransform() const { return m_parentTransform; }
			inline Matrix4x4f GetParentMatrix() const { return m_parentMatrix; }

			inline Vector3f GetTranslation() const { return GetParentMatrix() * m_translation; }
			inline Quaternionf GetRotation() const { Quaternionf parentRotation = m_parentTransform != nullptr ? m_parentTransform->GetRotation() : Quaternionf(0, 0, 0, 1); return parentRotation * m_rotation; }
			inline Vector3f GetScaling() const { return m_scaling; }

			inline bool IsBillboardEnabled() const { return m_billboardEnabled; }
			inline Component::Camera *GetBillboardCamera() const { return m_billboardCamera; }
		};
	}
}

#endif