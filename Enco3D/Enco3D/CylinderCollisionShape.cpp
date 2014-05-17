#include "CylinderCollisionShape.h"

Enco3D::Physics::CylinderCollisionShape::CylinderCollisionShape()
{
}

Enco3D::Physics::CylinderCollisionShape::CylinderCollisionShape(const Enco3D::Core::Vector3f &size)
{
	m_halfSize.set(size * 0.5f);
}

btCollisionShape *Enco3D::Physics::CylinderCollisionShape::toBulletPhysicsCollisionShape()
{
	return new btCylinderShape(PhysicsHelper::toBulletPhysicsVec3(m_halfSize));
}