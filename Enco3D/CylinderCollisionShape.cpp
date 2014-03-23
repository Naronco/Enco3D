#include "CylinderCollisionShape.h"

Enco3D::Physics::CylinderCollisionShape::CylinderCollisionShape()
{
}

Enco3D::Physics::CylinderCollisionShape::CylinderCollisionShape(const Enco3D::Core::Vector3f &size)
{
	m_halfSize.Set(size * 0.5f);
}

btCollisionShape *Enco3D::Physics::CylinderCollisionShape::ToBulletPhysicsCollisionShape()
{
	return new btCylinderShape(PhysicsHelper::ToBulletPhysicsVec3(m_halfSize));
}