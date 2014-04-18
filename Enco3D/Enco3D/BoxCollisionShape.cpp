#include "BoxCollisionShape.h"

Enco3D::Physics::BoxCollisionShape::BoxCollisionShape()
{
}

Enco3D::Physics::BoxCollisionShape::BoxCollisionShape(const Enco3D::Core::Vector3f &size)
{
	m_halfSize.Set(size * 0.5f);
}

btCollisionShape *Enco3D::Physics::BoxCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btBoxShape(PhysicsHelper::ToBulletPhysicsVec3(m_halfSize));
}