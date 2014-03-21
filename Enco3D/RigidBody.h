#ifndef _ENCO3D_RIGIDBODY_H_
#define _ENCO3D_RIGIDBODY_H_

#include "ICollisionShape.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "PhysicsHelper.h"

class RigidBody
{
private:
	float m_mass{ 0.0f };
	float m_restitution{ 0.0f };
	float m_friction{ 0.0f };
	float m_linearDamping{ 0.0f };
	float m_angularDamping{ 0.0f };
	ICollisionShape *m_collisionShape{ nullptr };
	Vector3f m_position;
	Quaternionf m_rotation;

	btRigidBody *m_bulletPhysicsInstance{ nullptr };
	btTransform m_transform;

public:
	RigidBody();
	RigidBody(float mass, ICollisionShape *collisionShape);
	RigidBody(float mass, float restitution, float friction, float linearDamping, float angularDamping, ICollisionShape *collisionShape);
	
	void Update();
	btRigidBody *CreateBulletPhysicsInstance();

	inline void SetMass(float mass) { m_mass = mass; }
	inline void SetRestitution(float restitution) { m_restitution = restitution; }
	inline void SetFriction(float friction) { m_friction = friction; }
	inline void SetLinearDamping(float linearDamping) { m_linearDamping = linearDamping; }
	inline void SetAngularDamping(float angularDamping) { m_angularDamping = angularDamping; }
	inline void SetCollisionShape(ICollisionShape *collisionShape) { m_collisionShape = collisionShape; }
	inline void SetPosition(const Vector3f &position) { m_position.Set(position); }
	inline void SetRotation(const Quaternionf &rotation) { m_rotation.Set(rotation); }

	inline float GetMass() const { return m_mass; }
	inline float GetRestitution() const { return m_restitution; }
	inline float GetFriction() const { return m_friction; }
	inline float GetLinearDamping() const { return m_linearDamping; }
	inline float GetAngularDamping() const { return m_angularDamping; }
	inline ICollisionShape *GetCollisionShape() const { return m_collisionShape; }
	inline Vector3f GetPosition() const { return m_position; }
	inline Quaternionf GetRotation() const { return m_rotation; }
	inline btRigidBody *GetBulletPhysicsInstance() const { return m_bulletPhysicsInstance; }
};

#endif