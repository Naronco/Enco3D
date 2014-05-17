#include "StaticPlaneCollisionShape.h"

Enco3D::Physics::StaticPlaneCollisionShape::StaticPlaneCollisionShape()
{
	m_normal.set(0, 0, 0);
}

Enco3D::Physics::StaticPlaneCollisionShape::StaticPlaneCollisionShape(const Enco3D::Core::Vector3f &normal)
{
	m_normal.set(normal);
}

Enco3D::Physics::StaticPlaneCollisionShape::StaticPlaneCollisionShape(const Enco3D::Core::Vector3f &p0, const Enco3D::Core::Vector3f &p1, const Enco3D::Core::Vector3f &p2)
{
	m_normal.set((p1 - p0).cross(p2 - p0).normalize());
}

Enco3D::Physics::StaticPlaneCollisionShape::~StaticPlaneCollisionShape()
{
}

btCollisionShape *Enco3D::Physics::StaticPlaneCollisionShape::toBulletPhysicsCollisionShape()
{
	return new btStaticPlaneShape((const btVector3 &)m_normal, 0);
}