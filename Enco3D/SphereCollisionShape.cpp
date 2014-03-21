#include "SphereCollisionShape.h"

SphereCollisionShape::SphereCollisionShape()
{
	m_radius = 0;
}

SphereCollisionShape::SphereCollisionShape(float radius)
{
	m_radius = radius;
}

btCollisionShape *SphereCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btSphereShape(m_radius);
}