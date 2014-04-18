#include "CapsuleCollisionShape.h"

Enco3D::Physics::CapsuleCollisionShape::CapsuleCollisionShape()
{
}

Enco3D::Physics::CapsuleCollisionShape::CapsuleCollisionShape(float radius, float height)
{
	m_radius = radius;
	m_height = height;
}

btCollisionShape *Enco3D::Physics::CapsuleCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btCapsuleShape(m_radius, m_height);
}