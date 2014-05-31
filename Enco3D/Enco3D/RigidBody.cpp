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

Enco3D::Component::RigidBody::~RigidBody()
{
}

void Enco3D::Component::RigidBody::initPhysics()
{
	getPhysicsEngine()->addRigidBody(this);
}

void Enco3D::Component::RigidBody::deinit()
{
	getPhysicsEngine()->removeRigidBody(this);
}

void Enco3D::Component::RigidBody::update()
{
	if (m_bulletPhysicsInstance == nullptr)
		return;

	m_bulletPhysicsInstance->getMotionState()->getWorldTransform(m_transform);
	getTransform()->setTranslation(Physics::PhysicsHelper::toEnco3DVec3<float>(m_transform.getOrigin()));
	getTransform()->setRotation(Physics::PhysicsHelper::toEnco3DQuat<float>(m_transform.getRotation()));
}

btRigidBody *Enco3D::Component::RigidBody::createBulletPhysicsInstance()
{
	btDefaultMotionState *motionState = new btDefaultMotionState(btTransform(Physics::PhysicsHelper::toBulletPhysicsQuat(getTransform()->getRotation()), Physics::PhysicsHelper::toBulletPhysicsVec3(getTransform()->getTranslation())));
	btCollisionShape *shape = m_collisionShape->toBulletPhysicsCollisionShape();
	btVector3 inertia(0, 0, 0);

	if (m_mass > 0.0f)
		shape->calculateLocalInertia(m_mass, inertia);

	btRigidBody::btRigidBodyConstructionInfo constructionInfo(m_mass, motionState, shape, inertia);
	m_bulletPhysicsInstance = new btRigidBody(constructionInfo);
	m_bulletPhysicsInstance->setRestitution(m_restitution);
	m_bulletPhysicsInstance->setFriction(m_friction);
	m_bulletPhysicsInstance->setDamping(m_linearDamping, m_angularDamping);

	if (m_alwaysStanding)
	{
		m_bulletPhysicsInstance->setInvInertiaDiagLocal(btVector3(0, 0, 0));
		m_bulletPhysicsInstance->updateInertiaTensor();
	}

	return m_bulletPhysicsInstance;
}