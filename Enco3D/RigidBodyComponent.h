#ifndef _ENCO3D_RIGIDBODYCOMPONENT_H_
#define _ENCO3D_RIGIDBODYCOMPONENT_H_

#include "IGameComponent.h"
#include "RigidBody.h"

class RigidBodyComponent : public IGameComponent
{
private:
	RigidBody *m_rigidBody{ nullptr };

public:
	RigidBodyComponent();
	RigidBodyComponent(RigidBody *rigidBody);

	void InitPhysics();
	void Deinit();

	void Update();
};

#endif