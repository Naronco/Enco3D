#ifndef _ENCO3D_CONECOLLISIONSHAPE_H_
#define _ENCO3D_CONECOLLISIONSHAPE_H_

#include "ICollisionShape.h"

namespace Enco3D
{
	namespace Physics
	{
		class ConeCollisionShape : public ICollisionShape
		{
		private:
			float m_radius, m_height;

		public:
			ConeCollisionShape();
			ConeCollisionShape(float radius, float height);

			btCollisionShape *toBulletPhysicsCollisionShape();

			inline void setRadius(float radius) { m_radius = radius; }
			inline void setHeight(float height) { m_height = height; }

			inline float getRadius() const { return m_radius; }
			inline float getHeight() const { return m_height; }
		};
	}
}

#endif