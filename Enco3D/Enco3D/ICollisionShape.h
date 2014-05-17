#ifndef _ENCO3D_ICOLLISIONSHAPE_H_
#define _ENCO3D_ICOLLISIONSHAPE_H_

#include "Vector3.h"

#include <btBulletDynamicsCommon.h>

namespace Enco3D
{
	namespace Physics
	{
		class ICollisionShape
		{
		public:
			virtual btCollisionShape *toBulletPhysicsCollisionShape() = 0;
		};
	}
}

#endif