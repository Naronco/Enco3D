#include "RigidBodyComponent.h"

RigidBodyComponent::RigidBodyComponent()
{
}

RigidBodyComponent::RigidBodyComponent(RigidBody *rigidBody)
{
	m_rigidBody = rigidBody;
}

void RigidBodyComponent::InitPhysics()
{
	m_rigidBody->SetPosition(GetTransform()->GetTranslation());
	m_rigidBody->SetRotation(GetTransform()->GetRotation());
	GetPhysicsEngine()->AddRigidBody(m_rigidBody);
}

void RigidBodyComponent::Deinit()
{
	GetPhysicsEngine()->RemoveRigidBody(m_rigidBody);
}

void RigidBodyComponent::Update()
{
	m_rigidBody->Update();
	GetTransform()->SetTranslation(m_rigidBody->GetPosition());
	GetTransform()->SetRotation(m_rigidBody->GetRotation());
}