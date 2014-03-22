#include "PhysicsEngine.h"
#include "RigidBody.h"

PhysicsEngine::PhysicsEngine()
{
	m_gravity.Set(0, -9.81f, 0);

	m_broadphase = new btDbvtBroadphase;

	m_collisionConfiguration = new btDefaultCollisionConfiguration;
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	m_solver = new btSequentialImpulseConstraintSolver;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	m_dynamicsWorld->setGravity(PhysicsHelper::ToBulletPhysicsVec3(m_gravity));
}

PhysicsEngine::~PhysicsEngine()
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

void PhysicsEngine::Update()
{
	m_dynamicsWorld->stepSimulation(m_timer->GetDeltaTime(), 10);
}

void PhysicsEngine::AddRigidBody(RigidBody *rigidBody)
{
	m_dynamicsWorld->addRigidBody(rigidBody->CreateBulletPhysicsInstance());
}

void PhysicsEngine::RemoveRigidBody(RigidBody *rigidBody)
{
	btRigidBody *btInstance = rigidBody->GetBulletPhysicsInstance();

	m_dynamicsWorld->removeRigidBody(btInstance);
	delete btInstance->getMotionState();
	delete btInstance;

	delete rigidBody->GetCollisionShape();
	delete rigidBody;
}