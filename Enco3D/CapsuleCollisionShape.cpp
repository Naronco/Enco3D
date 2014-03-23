#include "CapsuleCollisionShape.h"

CapsuleCollisionShape::CapsuleCollisionShape()
{
}

CapsuleCollisionShape::CapsuleCollisionShape(float radius, float height)
{
	m_radius = radius;
	m_height = height;
}

btCollisionShape *CapsuleCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btCapsuleShape(m_radius, m_height);
}