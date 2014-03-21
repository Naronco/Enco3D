#ifndef _ENCO3D_ICOLLISIONSHAPE_H_
#define _ENCO3D_ICOLLISIONSHAPE_H_

#include "Vector3.h"

#include <btBulletDynamicsCommon.h>

class ICollisionShape
{
public:
	virtual btCollisionShape *ToBulletPhysicsCollisionShape() = 0;
};

#endif