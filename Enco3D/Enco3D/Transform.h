#ifndef _ENCO3D_TRANSFORM_H_
#define _ENCO3D_TRANSFORM_H_

#include "Vector3.h"
#include "Quaternion.h"
#include "DLLExport.h"

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
		class DLL_EXPORT Transform
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

			void update();
			bool hasChanged() const;

			void translate(float x, float y, float z);
			void translate(const Vector3f &translation);

			void rotate(const Quaternionf &rotation);

			void scale(float x, float y, float z);
			void scale(float s);
			void scale(const Vector3f &scaling);

			Matrix4x4f getTransformation();

			inline void setParentTransform(Transform *parentTransform) { m_parentTransform = parentTransform; }

			inline void setTranslation(const Vector3f &translation) { m_translation = translation; }
			inline void setTranslation(float x, float y, float z) { m_translation.set(x, y, z); }

			inline void setRotation(const Quaternionf &rotation) { m_rotation = rotation; }

			inline void setScaling(float x, float y, float z) { m_scaling.set(x, y, z); }
			inline void setScaling(float s) { m_scaling.set(s, s, s); }
			inline void setScaling(const Vector3f &scaling) { m_scaling = scaling; }

			inline void setBillboardEnabled(bool enabled) { m_billboardEnabled = enabled; }
			inline void setBillboardCamera(Component::Camera *camera) { m_billboardCamera = camera; }

			inline Matrix4x4f getPrevTransformation() const { return m_prevTransformation; }

			inline Transform *getParentTransform() const { return m_parentTransform; }
			inline Matrix4x4f getParentMatrix() const { return m_parentMatrix; }

			inline Vector3f getTranslation() const { return getParentMatrix() * m_translation; }
			inline Quaternionf getRotation() const { Quaternionf parentRotation = m_parentTransform != nullptr ? m_parentTransform->getRotation() : Quaternionf(0, 0, 0, 1); return parentRotation * m_rotation; }
			inline Vector3f getScaling() const { return m_scaling; }

			inline bool isBillboardEnabled() const { return m_billboardEnabled; }
			inline Component::Camera *getBillboardCamera() const { return m_billboardCamera; }
		};
	}
}

#endif