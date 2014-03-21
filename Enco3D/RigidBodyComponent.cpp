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
	m_rigidBody->SetPosition(m_transform->GetTranslation());
	m_rigidBody->SetRotation(m_transform->GetRotation());
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