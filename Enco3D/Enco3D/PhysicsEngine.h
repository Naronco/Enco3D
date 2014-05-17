#ifndef _ENCO3D_PHYSICSENGINE_H_
#define _ENCO3D_PHYSICSENGINE_H_

#include "Vector3.h"
#include "Timer.h"

#include <btBulletDynamicsCommon.h>

namespace Enco3D
{
	namespace Component
	{
		class RigidBody;
	}
}

namespace Enco3D
{
	namespace Physics
	{
		class PhysicsEngine
		{
		private:
			btBroadphaseInterface *m_broadphase{ nullptr };
			btDefaultCollisionConfiguration *m_collisionConfiguration{ nullptr };
			btCollisionDispatcher *m_dispatcher{ nullptr };
			btSequentialImpulseConstraintSolver *m_solver{ nullptr };
			btDiscreteDynamicsWorld *m_dynamicsWorld{ nullptr };

			Core::Vector3f m_gravity;
			Core::Timer *m_timer{ nullptr };

		public:
			PhysicsEngine();
			~PhysicsEngine();

			void update();

			void addRigidBody(Component::RigidBody *rigidBody);
			void removeRigidBody(Component::RigidBody *rigidBody);

			inline void setGravity(const Core::Vector3f &gravity) { m_gravity.set(gravity); }
			inline void setTimer(Core::Timer *timer) { m_timer = timer; }

			inline Core::Vector3f getGravity() const { return m_gravity; }
			inline Core::Timer *getTimer() const { return m_timer; }
		};
	}
}

#endif