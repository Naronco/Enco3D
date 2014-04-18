#include "CPhysicsDevice_BulletPhysics.h"

void enco::core::CPhysicsDevice_BulletPhysics::create()
{
	m_gravity.set(0, -9.81f, 0);

	m_broadphase = new btDbvtBroadphase;

	m_collisionConfiguration = new btDefaultCollisionConfiguration;
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	m_solver = new btSequentialImpulseConstraintSolver;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	m_dynamicsWorld->setGravity(bulletphysics_util::Vector3_to_btVector3<float32>(m_gravity));
}

void enco::core::CPhysicsDevice_BulletPhysics::release()
{
	for (uint32 i = 0; i < m_rigidBodies.size(); i++)
		removeRigidBody(m_rigidBodies[i]);

	releaseCreatedShapes();

	__SAFEDELETE(m_dynamicsWorld);
	__SAFEDELETE(m_solver);
	__SAFEDELETE(m_dispatcher);
	__SAFEDELETE(m_collisionConfiguration);
	__SAFEDELETE(m_broadphase);
}

void enco::core::CPhysicsDevice_BulletPhysics::update()
{
	m_dynamicsWorld->stepSimulation(m_timer->getDeltaTime(), 10);

	for (uint32 i = 0; i < m_rigidBodies.size(); i++) {
//		RigidBody_BulletPhysics *rb = (RigidBody_BulletPhysics*)m_rigidBodies[i];

//		btTransform transform;
//		rb->bulletInstance->getMotionState()->getWorldTransform(transform);

//		rb->data.shape->position = bulletphysics_util::btVector3_to_Vector3<float32>(transform.getOrigin());
//		rb->data.shape->rotation = bulletphysics_util::btQuaternion_to_YawPitchRoll<float32>(transform.getRotation());
	}
}

enco::core::IRigidBody *enco::core::CPhysicsDevice_BulletPhysics::addRigidBody(const RigidBodyData &rigidBodyData)
{
	RigidBody_BulletPhysics *rigidBody = 0;

	btRigidBody *bulletBody = 0;
	btCollisionShape *collisionShape = 0;

	std::cout << "Hallo Welt 1" << std::endl;
	__IBulletPhysicsShape* baskdj = (__IBulletPhysicsShape*)rigidBodyData.shape;
	std::cout << baskdj << std::endl;
	baskdj->toCollisionShape();
//	collisionShape = ((__IBulletPhysicsShape*)rigidBodyData.shape)->toCollisionShape();
	std::cout << "Hallo Welt 2" << std::endl;

	btDefaultMotionState *motionState = new btDefaultMotionState(btTransform(bulletphysics_util::YawPitchRoll_to_btQuaternion(rigidBodyData.shape->rotation), bulletphysics_util::Vector3_to_btVector3(rigidBodyData.shape->position)));
	btVector3 inertia(0, 0, 0);

	if (rigidBodyData.mass > 0.0f)
		collisionShape->calculateLocalInertia(rigidBodyData.mass, inertia);

	btRigidBody::btRigidBodyConstructionInfo constructionInfo(rigidBodyData.mass, motionState, collisionShape, inertia);
	bulletBody = new btRigidBody(constructionInfo);
	bulletBody->setRestitution(rigidBodyData.restitution);
	bulletBody->setFriction(rigidBodyData.friction);
	bulletBody->setDamping(rigidBodyData.linearDamping, rigidBodyData.angularDamping);

	if (!rigidBodyData.rotationEnabled)
	{
		bulletBody->setInvInertiaDiagLocal(btVector3(0, 0, 0));
		bulletBody->updateInertiaTensor();
	}

	rigidBody = new RigidBody_BulletPhysics;
	rigidBody->data = rigidBodyData;
	rigidBody->bulletInstance = bulletBody;

	m_dynamicsWorld->addRigidBody(bulletBody);

	return rigidBody;
}

void enco::core::CPhysicsDevice_BulletPhysics::removeRigidBody(IRigidBody *rigidBody)
{
	btRigidBody *btInstance = ((RigidBody_BulletPhysics*)rigidBody)->bulletInstance;

	m_dynamicsWorld->removeRigidBody(btInstance);
	delete btInstance->getMotionState();
	delete btInstance;

	std::vector<IRigidBody*>::iterator pos = std::find(m_rigidBodies.begin(), m_rigidBodies.end(), rigidBody);
	__ASSERT(pos != m_rigidBodies.end());
	m_rigidBodies.erase(pos);

	delete rigidBody;
}

enco::core::ISphereShape *enco::core::CPhysicsDevice_BulletPhysics::createSphereShape(float32 radius)
{
	SphereShape_BulletPhysics *shape = 0;

	shape = new SphereShape_BulletPhysics;
	shape->radius = radius;

	m_shapes.push_back(shape);

	return shape;
}

enco::core::IStaticPlaneShape *enco::core::CPhysicsDevice_BulletPhysics::createStaticPlaneShape()
{
	StaticPlaneShape_BulletPhysics *shape = 0;

	shape = new StaticPlaneShape_BulletPhysics;

	m_shapes.push_back(shape);

	return shape;
}

void enco::core::CPhysicsDevice_BulletPhysics::setGravity(const math::Vector3f32 &gravity)
{
	m_gravity.set(gravity);
	m_dynamicsWorld->setGravity(bulletphysics_util::Vector3_to_btVector3<float32>(m_gravity));
}