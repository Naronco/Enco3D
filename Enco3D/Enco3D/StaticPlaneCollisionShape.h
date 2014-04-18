#ifndef _ENCO3D_STATICPLANECOLLISIONSHAPE_H_
#define _ENCO3D_STATICPLANECOLLISIONSHAPE_H_

#include "ICollisionShape.h"
#include "Vector3.h"

namespace Enco3D
{
	namespace Physics
	{
		using namespace Core;

		class StaticPlaneCollisionShape : public ICollisionShape
		{
		private:
			Vector3f m_normal;

		public:
			StaticPlaneCollisionShape();
			StaticPlaneCollisionShape(const Vector3f &normal);
			StaticPlaneCollisionShape(const Vector3f &p0, const Vector3f &p1, const Vector3f &p2);
			~StaticPlaneCollisionShape();

			btCollisionShape *ToBulletPhysicsCollisionShape();

			inline void SetNormal(const Vector3f &normal) { m_normal.Set(normal); }
			inline Vector3f GetNormal() const { return m_normal; }
		};
	}
}

#endif