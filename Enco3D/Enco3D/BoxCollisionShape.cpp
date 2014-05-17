#include "BoxCollisionShape.h"

Enco3D::Physics::BoxCollisionShape::BoxCollisionShape()
{
}

Enco3D::Physics::BoxCollisionShape::BoxCollisionShape(const Enco3D::Core::Vector3f &size)
{
	m_halfSize.set(size * 0.5f);
}

btCollisionShape *Enco3D::Physics::BoxCollisionShape::toBulletPhysicsCollisionShape()
{
	return new btBoxShape(PhysicsHelper::toBulletPhysicsVec3(m_halfSize));
}