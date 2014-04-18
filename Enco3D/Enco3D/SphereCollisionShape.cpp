#include "SphereCollisionShape.h"

Enco3D::Physics::SphereCollisionShape::SphereCollisionShape()
{
	m_radius = 0;
}

Enco3D::Physics::SphereCollisionShape::SphereCollisionShape(float radius)
{
	m_radius = radius;
}

btCollisionShape *Enco3D::Physics::SphereCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btSphereShape(m_radius);
}