#include "RigidBody.h"

Enco3D::Component::RigidBody::RigidBody()
{
}

Enco3D::Component::RigidBody::RigidBody(float mass, Enco3D::Physics::ICollisionShape *collisionShape) : m_mass(mass), m_collisionShape(collisionShape)
{
}

Enco3D::Component::RigidBody::RigidBody(float mass, float restitution, float friction, float linearDamping, float angularDamping, Enco3D::Physics::ICollisionShape *collisionShape) : m_mass(mass), m_restitution(restitution), m_friction(friction), m_linearDamping(linearDamping), m_angularDamping(angularDamping), m_collisionShape(collisionShape)
{
}

void Enco3D::Component::RigidBody::InitPhysics()
{
	GetPhysicsEngine()->AddRigidBody(this);
}

void Enco3D::Component::RigidBody::Deinit()
{
	GetPhysicsEngine()->RemoveRigidBody(this);
}

void Enco3D::Component::RigidBody::Update()
{
	if (m_bulletPhysicsInstance == nullptr)
	{
		return;
	}

	m_bulletPhysicsInstance->getMotionState()->getWorldTransform(m_transform);
	GetTransform()->SetTranslation(PhysicsHelper::ToEnco3DVec3<float>(m_transform.getOrigin()));
	GetTransform()->SetRotation(PhysicsHelper::ToEnco3DQuat<float>(m_transform.getRotation()));
}

btRigidBody *Enco3D::Component::RigidBody::CreateBulletPhysicsInstance()
{
	btDefaultMotionState *motionState = new btDefaultMotionState(btTransform(PhysicsHelper::ToBulletPhysicsQuat(GetTransform()->GetRotation()), PhysicsHelper::ToBulletPhysicsVec3(GetTransform()->GetTranslation())));
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