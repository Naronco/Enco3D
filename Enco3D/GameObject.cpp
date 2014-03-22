#include "GameObject.h"
#include "IGameComponent.h"

GameObject::GameObject()
{
	m_transform = new Transform;
}

GameObject::GameObject(const string &name)
{
	m_name = name;
	m_transform = new Transform;
}

GameObject::~GameObject()
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

void GameObject::Update()
{
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->Update();
	}

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->Update();
	}
}

void GameObject::Render(Shader *shader)
{
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->Render(shader);
	}

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->Render(shader);
	}
}


GameObject *GameObject::AddChild(GameObject *child)
{
	child->SetRenderingEngine(m_renderingEngine);
	child->SetPhysicsEngine(m_physicsEngine);
	child->SetWindow(m_window);
	child->SetTimer(m_timer);
	child->GetTransform()->SetParentTransform(m_transform);
	m_children.push_back(child);

	return this;
}

GameObject *GameObject::AddComponent(IGameComponent *component)
{
	component->SetGameObject(this);
	component->Init();
	m_components.push_back(component);

	return this;
}

void GameObject::SetRenderingEngine(RenderingEngine *renderingEngine)
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

void GameObject::SetPhysicsEngine(PhysicsEngine *physicsEngine)
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

void GameObject::SetWindow(GLWindow *window)
{
	m_window = window;

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->SetWindow(window);
	}
}

void GameObject::SetTimer(Timer *timer)
{
	m_timer = timer;

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->SetTimer(timer);
	}
}
