#include "BoxCollisionShape.h"

BoxCollisionShape::BoxCollisionShape()
{
}

BoxCollisionShape::BoxCollisionShape(const Vector3f &size)
{
	m_halfSize.Set(size * 0.5f);
}

btCollisionShape *BoxCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btBoxShape(PhysicsHelper::ToBulletPhysicsVec3(m_halfSize));
}