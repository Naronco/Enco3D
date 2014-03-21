#ifndef _ENCO3D_GAMEOBJECT_H_
#define _ENCO3D_GAMEOBJECT_H_

#include "Transform.h"
#include "IGameComponent.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "GLWindow.h"
#include "Timer.h"

#include <vector>
#include <iostream>

using namespace std;

class GameObject
{
private:
	Transform *m_transform{ nullptr };

	vector<GameObject *> m_children;
	vector<IGameComponent *> m_components;

	RenderingEngine *m_renderingEngine{ nullptr };
	PhysicsEngine *m_physicsEngine{ nullptr };
	GLWindow *m_window{ nullptr };
	Timer *m_timer{ nullptr };

public:
	GameObject();
	~GameObject();

	void Update();
	void Render();

	inline GameObject *AddChild(GameObject *child)
	{
		child->SetRenderingEngine(m_renderingEngine);
		child->SetPhysicsEngine(m_physicsEngine);
		child->SetWindow(m_window);
		child->SetTimer(m_timer);
		child->GetTransform()->SetParentTransform(m_transform);
		m_children.push_back(child);

		return this;
	}

	inline GameObject *AddComponent(IGameComponent *component)
	{
		component->SetTransform(m_transform);
		component->SetRenderingEngine(m_renderingEngine);
		component->SetPhysicsEngine(m_physicsEngine);
		component->SetWindow(m_window);
		component->SetTimer(m_timer);
		component->Init();
		m_components.push_back(component);

		return this;
	}

	inline void SetRenderingEngine(RenderingEngine *renderingEngine)
	{
		m_renderingEngine = renderingEngine;

		for (unsigned int i = 0; i < m_children.size(); i++)
		{
			m_children[i]->SetRenderingEngine(renderingEngine);
		}

		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->SetRenderingEngine(renderingEngine);
		}
	}

	inline void SetPhysicsEngine(PhysicsEngine *physicsEngine)
	{
		m_physicsEngine = physicsEngine;

		for (unsigned int i = 0; i < m_children.size(); i++)
		{
			m_children[i]->SetPhysicsEngine(physicsEngine);
		}

		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->SetPhysicsEngine(physicsEngine);
			m_components[i]->InitPhysics();
		}
	}

	inline void SetWindow(GLWindow *window)
	{
		m_window = window;

		for (unsigned int i = 0; i < m_children.size(); i++)
		{
			m_children[i]->SetWindow(window);
		}

		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->SetWindow(window);
		}
	}

	inline void SetTimer(Timer *timer)
	{
		m_timer = timer;

		for (unsigned int i = 0; i < m_children.size(); i++)
		{
			m_children[i]->SetTimer(timer);
		}

		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->SetTimer(timer);
		}
	}
	
	inline Transform *GetTransform() const { return m_transform; }
	inline vector<GameObject *> GetChildren() const { return m_children; }
	inline vector<IGameComponent *> GetComponents() const { return m_components; }
	inline RenderingEngine *GetRenderingEngine() const { return m_renderingEngine; }
	inline PhysicsEngine *GetPhysicsEngine() const { return m_physicsEngine; }
	inline GLWindow *GetWindow() const { return m_window; }
	inline Timer *GetTimer() const { return m_timer; }
};

#endif