#include "GameObject.h"
#include "IGameComponent.h"
#include "Camera.h"

Enco3D::Core::GameObject::GameObject()
{
	m_transform = new Transform;
}

Enco3D::Core::GameObject::GameObject(const string &name)
{
	m_name = name;
	m_transform = new Transform;
}

Enco3D::Core::GameObject::~GameObject()
{
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		if (m_children[i])
		{
			delete m_children[i];
			m_children[i] = nullptr;
		}
	}

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		if (m_components[i])
		{
			m_components[i]->Deinit();
			delete m_components[i];
			m_components[i] = nullptr;
		}
	}
}

void Enco3D::Core::GameObject::Update()
{
	if (!m_enabled)
	{
		return;
	}

	m_transform->Update();

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->Update();
	}

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->Update();
	}
}

void Enco3D::Core::GameObject::Render(const Enco3D::Rendering::Camera *camera, Enco3D::Rendering::Shader *shader)
{
	if (!m_enabled)
	{
		return;
	}

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->Render(camera, shader);
	}

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->Render(camera, shader);
	}
}

void Enco3D::Core::GameObject::RenderGUI(const Enco3D::Rendering::Camera *camera, Enco3D::Rendering::Shader *shader)
{
	if (!m_enabled)
	{
		return;
	}

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->RenderGUI(camera, shader);
	}

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->RenderGUI(camera, shader);
	}
}

Enco3D::Core::GameObject *Enco3D::Core::GameObject::AddChild(GameObject *child)
{
	if (m_renderingEngine)
	{
		child->SetRenderingEngine(m_renderingEngine);
	}

	if (m_physicsEngine)
	{
		child->SetPhysicsEngine(m_physicsEngine);
	}

	child->SetWindow(m_window);
	child->SetTimer(m_timer);
	child->GetTransform()->SetParentTransform(m_transform);
	m_children.push_back(child);

	return this;
}

Enco3D::Core::GameObject *Enco3D::Core::GameObject::AddComponent(IGameComponent *component)
{
	component->SetGameObject(this);
	component->Init();
	m_components.push_back(component);

	return this;
}

void Enco3D::Core::GameObject::SetRenderingEngine(Enco3D::Rendering::RenderingEngine *renderingEngine)
{
	m_renderingEngine = renderingEngine;

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->SetRenderingEngine(renderingEngine);
	}

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->InitRendering();
	}
}

void Enco3D::Core::GameObject::SetPhysicsEngine(Enco3D::Physics::PhysicsEngine *physicsEngine)
{
	m_physicsEngine = physicsEngine;

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->SetPhysicsEngine(physicsEngine);
	}

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->InitPhysics();
	}
}

void Enco3D::Core::GameObject::SetWindow(GLWindow *window)
{
	m_window = window;

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->SetWindow(window);
	}
}

void Enco3D::Core::GameObject::SetTimer(Timer *timer)
{
	m_timer = timer;

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->SetTimer(timer);
	}
}

Enco3D::Core::GameObject *Enco3D::Core::GameObject::GetChild(const string &name) const
{
	for (unsigned int i = m_children.size() - 1; i >= 0; i--)
	{
		if (m_children[i]->GetName() == name)
		{
			return m_children[i];
		}
	}

	return nullptr;
}

Enco3D::Core::IGameComponent *Enco3D::Core::GameObject::GetGameComponent(const string &name) const
{
	for (unsigned int i = m_components.size() - 1; i >= 0; i--)
	{
		if (m_components[i]->GetName() == name)
		{
			return m_components[i];
		}
	}

	return nullptr;
}