#ifndef _ENCO3D_PHYSICSENGINE_H_
#define _ENCO3D_PHYSICSENGINE_H_

#include "Vector3.h"
#include "Timer.h"

#include <btBulletDynamicsCommon.h>

class RigidBody;

class PhysicsEngine
{
private:
	btBroadphaseInterface *m_broadphase{ nullptr };
	btDefaultCollisionConfiguration *m_collisionConfiguration{ nullptr };
	btCollisionDispatcher *m_dispatcher{ nullptr };
	btSequentialImpulseConstraintSolver *m_solver{ nullptr };
	btDiscreteDynamicsWorld *m_dynamicsWorld{ nullptr };

	Vector3f m_gravity;
	Timer *m_timer{ nullptr };

public:
	PhysicsEngine();
	~PhysicsEngine();

	void Update();

	void AddRigidBody(RigidBody *rigidBody);
	void RemoveRigidBody(RigidBody *rigidBody);

	inline void SetGravity(const Vector3f &gravity) { m_gravity.Set(gravity); }
	inline void SetTimer(Timer *timer) { m_timer = timer; }

	inline Vector3f GetGravity() const { return m_gravity; }
	inline Timer *GetTimer() const { return m_timer; }
};

#endif