#include "ConeCollisionShape.h"

Enco3D::Physics::ConeCollisionShape::ConeCollisionShape()
{
}

Enco3D::Physics::ConeCollisionShape::ConeCollisionShape(float radius, float height)
{
	m_radius = radius;
	m_height = height;
}

btCollisionShape *Enco3D::Physics::ConeCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btConeShape(m_radius, m_height);
}