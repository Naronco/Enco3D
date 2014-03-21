#include "GameObject.h"

GameObject::GameObject()
{
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

void GameObject::Render()
{
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->Render();
	}

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->Render();
	}
}