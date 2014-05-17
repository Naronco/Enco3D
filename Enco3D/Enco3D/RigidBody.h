#ifndef _ENCO3D_RIGIDBODY_H_
#define _ENCO3D_RIGIDBODY_H_

#include "ICollisionShape.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "PhysicsHelper.h"
#include "IGameComponent.h"
#include "PhysicsEngine.h"

namespace Enco3D
{
	namespace Component
	{
		class RigidBody : public Core::IGameComponent
		{
		private:
			float m_mass{ 0.0f };
			float m_restitution{ 0.0f };
			float m_friction{ 0.0f };
			float m_linearDamping{ 0.0f };
			float m_angularDamping{ 0.0f };
			bool m_alwaysStanding{ false };
			Physics::ICollisionShape *m_collisionShape{ nullptr };

			btRigidBody *m_bulletPhysicsInstance{ nullptr };
			btTransform m_transform;

		public:
			RigidBody();
			RigidBody(float mass, Physics::ICollisionShape *collisionShape);
			RigidBody(float mass, float restitution, float friction, float linearDamping, float angularDamping, Physics::ICollisionShape *collisionShape);

			void initPhysics();
			void deinit();

			void update();
			btRigidBody *createBulletPhysicsInstance();

			inline void setLinearVelocity(const Core::Vector3f &linearVelocity) { m_bulletPhysicsInstance->setLinearVelocity(Physics::PhysicsHelper::toBulletPhysicsVec3(linearVelocity)); }
			inline void setAngularVelocity(const Core::Vector3f &angularVelocity) { m_bulletPhysicsInstance->setAngularVelocity(Physics::PhysicsHelper::toBulletPhysicsVec3(angularVelocity)); }

			inline void setMass(float mass) { m_mass = mass; }
			inline void setRestitution(float restitution) { m_restitution = restitution; }
			inline void setFriction(float friction) { m_friction = friction; }
			inline void setLinearDamping(float linearDamping) { m_linearDamping = linearDamping; }
			inline void setAngularDamping(float angularDamping) { m_angularDamping = angularDamping; }
			inline void setAlwaysStanding(bool alwaysStanding) { m_alwaysStanding = alwaysStanding; }
			inline void setCollisionShape(Physics::ICollisionShape *collisionShape) { m_collisionShape = collisionShape; }

			inline float getMass() const { return m_mass; }
			inline float getRestitution() const { return m_restitution; }
			inline float getFriction() const { return m_friction; }
			inline float getLinearDamping() const { return m_linearDamping; }
			inline float getAngularDamping() const { return m_angularDamping; }
			inline bool isAlwaysStanding() const { return m_alwaysStanding; }
			inline Physics::ICollisionShape *getCollisionShape() const { return m_collisionShape; }
			inline btRigidBody *getBulletPhysicsInstance() const { return m_bulletPhysicsInstance; }
			inline Core::Vector3f getLinearVelocity() const { return Physics::PhysicsHelper::toEnco3DVec3<float>(m_bulletPhysicsInstance->getLinearVelocity()); }
			inline Core::Vector3f getAngularVelocity() const { return Physics::PhysicsHelper::toEnco3DVec3<float>(m_bulletPhysicsInstance->getAngularVelocity()); }
		};
	}
}

#endif