#include "RigidBody.h"

RigidBody::RigidBody()
{
}

RigidBody::RigidBody(float mass, ICollisionShape *collisionShape) : m_mass(mass), m_collisionShape(collisionShape)
{
}

RigidBody::RigidBody(float mass, float restitution, float friction, float linearDamping, float angularDamping, ICollisionShape *collisionShape) : m_mass(mass), m_restitution(restitution), m_friction(friction), m_linearDamping(linearDamping), m_angularDamping(angularDamping), m_collisionShape(collisionShape)
{
}

void RigidBody::Update()
{
	if (m_bulletPhysicsInstance == nullptr)
	{
		return;
	}

	m_bulletPhysicsInstance->getMotionState()->getWorldTransform(m_transform);
	m_position.Set(PhysicsHelper::ToEnco3DVec3<float>(m_transform.getOrigin()));
	m_rotation.Set(PhysicsHelper::ToEnco3DQuat<float>(m_transform.getRotation()));
}

btRigidBody *RigidBody::CreateBulletPhysicsInstance()
{
	btDefaultMotionState *motionState = new btDefaultMotionState(btTransform(PhysicsHelper::ToBulletPhysicsQuat(m_rotation), PhysicsHelper::ToBulletPhysicsVec3(m_position)));
	btCollisionShape *shape = m_collisionShape->ToBulletPhysicsCollisionShape();
	btVector3 inertia(0, 0, 0);

	if (m_mass > 0.0f)
	{
		shape->calculateLocalInertia(m_mass, inertia);
	}

	btRigidBody::btRigidBodyConstructionInfo constructionInfo(m_mass, motionState, shape, inertia);
	m_bulletPhysicsInstance = new btRigidBody(constructionInfo);
	m_bulletPhysicsInstance->setRestitution(m_restitution);
	m_bulletPhysicsInstance->setFriction(m_friction);
	m_bulletPhysicsInstance->setDamping(m_linearDamping, m_angularDamping);

	return m_bulletPhysicsInstance;
}