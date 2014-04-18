#ifndef _ENCO3D_CAPSULECOLLISIONSHAPE_H_
#define _ENCO3D_CAPSULECOLLISIONSHAPE_H_

#include "ICollisionShape.h"

namespace Enco3D
{
	namespace Physics
	{
		class CapsuleCollisionShape : public ICollisionShape
		{
		private:
			float m_radius, m_height;

		public:
			CapsuleCollisionShape();
			CapsuleCollisionShape(float radius, float height);

			btCollisionShape *ToBulletPhysicsCollisionShape();

			inline void SetRadius(float radius) { m_radius = radius; }
			inline void SetHeight(float height) { m_height = height; }

			inline float GetRadius() const { return m_radius; }
			inline float GetHeight() const { return m_height; }
		};
	}
}

#endif