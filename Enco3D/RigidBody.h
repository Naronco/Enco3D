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
		using namespace Core;
		using namespace Physics;

		class RigidBody : public IGameComponent
		{
		private:
			float m_mass{ 0.0f };
			float m_restitution{ 0.0f };
			float m_friction{ 0.0f };
			float m_linearDamping{ 0.0f };
			float m_angularDamping{ 0.0f };
			bool m_alwaysStanding{ false };
			ICollisionShape *m_collisionShape{ nullptr };

			btRigidBody *m_bulletPhysicsInstance{ nullptr };
			btTransform m_transform;

		public:
			RigidBody();
			RigidBody(float mass, ICollisionShape *collisionShape);
			RigidBody(float mass, float restitution, float friction, float linearDamping, float angularDamping, ICollisionShape *collisionShape);

			void InitPhysics();
			void Deinit();

			void Update();
			btRigidBody *CreateBulletPhysicsInstance();

			inline void SetLinearVelocity(const Vector3f &linearVelocity) { m_bulletPhysicsInstance->setLinearVelocity(PhysicsHelper::ToBulletPhysicsVec3(linearVelocity)); }
			inline void SetAngularVelocity(const Vector3f &angularVelocity) { m_bulletPhysicsInstance->setAngularVelocity(PhysicsHelper::ToBulletPhysicsVec3(angularVelocity)); }

			inline void SetMass(float mass) { m_mass = mass; }
			inline void SetRestitution(float restitution) { m_restitution = restitution; }
			inline void SetFriction(float friction) { m_friction = friction; }
			inline void SetLinearDamping(float linearDamping) { m_linearDamping = linearDamping; }
			inline void SetAngularDamping(float angularDamping) { m_angularDamping = angularDamping; }
			inline void SetAlwaysStanding(bool alwaysStanding) { m_alwaysStanding = alwaysStanding; }
			inline void SetCollisionShape(ICollisionShape *collisionShape) { m_collisionShape = collisionShape; }

			inline float GetMass() const { return m_mass; }
			inline float GetRestitution() const { return m_restitution; }
			inline float GetFriction() const { return m_friction; }
			inline float GetLinearDamping() const { return m_linearDamping; }
			inline float GetAngularDamping() const { return m_angularDamping; }
			inline bool IsAlwaysStanding() const { return m_alwaysStanding; }
			inline ICollisionShape *GetCollisionShape() const { return m_collisionShape; }
			inline btRigidBody *GetBulletPhysicsInstance() const { return m_bulletPhysicsInstance; }
			inline Vector3f GetLinearVelocity() const { return PhysicsHelper::ToEnco3DVec3<float>(m_bulletPhysicsInstance->getLinearVelocity()); }
			inline Vector3f GetAngularVelocity() const { return PhysicsHelper::ToEnco3DVec3<float>(m_bulletPhysicsInstance->getAngularVelocity()); }
		};
	}
}

#endif