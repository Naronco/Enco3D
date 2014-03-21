#include "StaticPlaneCollisionShape.h"

StaticPlaneCollisionShape::StaticPlaneCollisionShape()
{
	m_normal.Set(0, 0, 0);
	m_origin = 0;
}

StaticPlaneCollisionShape::StaticPlaneCollisionShape(const Vector3f &normal, float origin)
{
	m_normal.Set(normal);
	m_origin = origin;
}

StaticPlaneCollisionShape::StaticPlaneCollisionShape(const Vector3f &p0, const Vector3f &p1, const Vector3f &p2)
{
	m_normal.Set((p1 - p0).Cross(p2 - p0).Normalize());
	m_origin = m_normal.Dot(p0);
}

StaticPlaneCollisionShape::~StaticPlaneCollisionShape()
{
}

btCollisionShape *StaticPlaneCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btStaticPlaneShape((const btVector3 &)m_normal, m_origin);
}