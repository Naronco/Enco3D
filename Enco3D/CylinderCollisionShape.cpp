#include "CylinderCollisionShape.h"

CylinderCollisionShape::CylinderCollisionShape()
{
}

CylinderCollisionShape::CylinderCollisionShape(const Vector3f &size)
{
	m_halfSize.Set(size * 0.5f);
}

btCollisionShape *CylinderCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btCylinderShape(PhysicsHelper::ToBulletPhysicsVec3(m_halfSize));
}