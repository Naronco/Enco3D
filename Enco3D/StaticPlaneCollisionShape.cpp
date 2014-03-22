#include "StaticPlaneCollisionShape.h"

StaticPlaneCollisionShape::StaticPlaneCollisionShape()
{
	m_normal.Set(0, 0, 0);
}

StaticPlaneCollisionShape::StaticPlaneCollisionShape(const Vector3f &normal)
{
	m_normal.Set(normal);
}

StaticPlaneCollisionShape::StaticPlaneCollisionShape(const Vector3f &p0, const Vector3f &p1, const Vector3f &p2)
{
	m_normal.Set((p1 - p0).Cross(p2 - p0).Normalize());
}

StaticPlaneCollisionShape::~StaticPlaneCollisionShape()
{
}

btCollisionShape *StaticPlaneCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btStaticPlaneShape((const btVector3 &)m_normal, 0);
}