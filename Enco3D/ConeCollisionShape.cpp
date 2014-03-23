#include "ConeCollisionShape.h"

ConeCollisionShape::ConeCollisionShape()
{
}

ConeCollisionShape::ConeCollisionShape(float radius, float height)
{
	m_radius = radius;
	m_height = height;
}

btCollisionShape *ConeCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btConeShape(m_radius, m_height);
}