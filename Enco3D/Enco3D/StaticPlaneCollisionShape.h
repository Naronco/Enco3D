#ifndef _ENCO3D_STATICPLANECOLLISIONSHAPE_H_
#define _ENCO3D_STATICPLANECOLLISIONSHAPE_H_

#include "ICollisionShape.h"
#include "Vector3.h"

namespace Enco3D
{
	namespace Physics
	{
		class StaticPlaneCollisionShape : public ICollisionShape
		{
		private:
			Core::Vector3f m_normal;

		public:
			StaticPlaneCollisionShape();
			StaticPlaneCollisionShape(const Core::Vector3f &normal);
			StaticPlaneCollisionShape(const Core::Vector3f &p0, const Core::Vector3f &p1, const Core::Vector3f &p2);
			~StaticPlaneCollisionShape();

			btCollisionShape *ToBulletPhysicsCollisionShape();

			inline void SetNormal(const Core::Vector3f &normal) { m_normal.Set(normal); }
			inline Core::Vector3f GetNormal() const { return m_normal; }
		};
	}
}

#endif