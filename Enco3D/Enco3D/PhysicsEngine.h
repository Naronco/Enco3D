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

			void Update();

			void AddRigidBody(Component::RigidBody *rigidBody);
			void RemoveRigidBody(Component::RigidBody *rigidBody);

			inline void SetGravity(const Core::Vector3f &gravity) { m_gravity.Set(gravity); }
			inline void SetTimer(Core::Timer *timer) { m_timer = timer; }

			inline Core::Vector3f GetGravity() const { return m_gravity; }
			inline Core::Timer *GetTimer() const { return m_timer; }
		};
	}
}

#endif