#ifndef _ENCO3D_SPHERECOLLISIONSHAPE_H_
#define _ENCO3D_SPHERECOLLISIONSHAPE_H_

#include "ICollisionShape.h"
#include "Vector3.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Physics
	{
		class DLL_EXPORT SphereCollisionShape : public ICollisionShape
		{
		private:
			float m_radius;

		public:
			SphereCollisionShape();
			SphereCollisionShape(float radius);

			btCollisionShape *toBulletPhysicsCollisionShape();

			inline void setRadius(float radius) { m_radius = radius; }
			inline float getRadius() const { return m_radius; }
		};
	}
}

#endif