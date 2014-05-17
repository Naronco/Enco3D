#include "PhysicsEngine.h"
#include "RigidBody.h"

Enco3D::Physics::PhysicsEngine::PhysicsEngine()
{
	m_gravity.set(0, -9.81f, 0);

	m_broadphase = new btDbvtBroadphase;

	m_collisionConfiguration = new btDefaultCollisionConfiguration;
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	m_solver = new btSequentialImpulseConstraintSolver;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	m_dynamicsWorld->setGravity(PhysicsHelper::toBulletPhysicsVec3(m_gravity));
}

Enco3D::Physics::PhysicsEngine::~PhysicsEngine()
{
	if (m_dynamicsWorld)
	{
		delete m_dynamicsWorld;
		m_dynamicsWorld = nullptr;
	}

	if (m_solver)
	{
		delete m_solver;
		m_solver = nullptr;
	}

	if (m_collisionConfiguration)
	{
		delete m_collisionConfiguration;
		m_collisionConfiguration = nullptr;
	}

	if (m_dispatcher)
	{
		delete m_dispatcher;
		m_dispatcher = nullptr;
	}

	if (m_broadphase)
	{
		delete m_broadphase;
		m_broadphase = nullptr;
	}
}

void Enco3D::Physics::PhysicsEngine::update()
{
	m_dynamicsWorld->stepSimulation(1.0f / 60.0f, 10);
}

void Enco3D::Physics::PhysicsEngine::addRigidBody(Enco3D::Component::RigidBody *rigidBody)
{
	m_dynamicsWorld->addRigidBody(rigidBody->createBulletPhysicsInstance());
}

void Enco3D::Physics::PhysicsEngine::removeRigidBody(Enco3D::Component::RigidBody *rigidBody)
{
	btRigidBody *btInstance = rigidBody->getBulletPhysicsInstance();

	m_dynamicsWorld->removeRigidBody(btInstance);
	delete btInstance->getMotionState();
	delete btInstance;

	delete rigidBody->getCollisionShape();
}