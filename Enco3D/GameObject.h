#ifndef _ENCO3D_GAMEOBJECT_H_
#define _ENCO3D_GAMEOBJECT_H_

#include "Transform.h"
#include "IGameComponent.h"
#include "GLWindow.h"
#include "Timer.h"

#include <vector>
#include <iostream>

using namespace std;

class GameObject
{
private:
	Transform *m_transform;

	vector<GameObject *> m_children;
	vector<IGameComponent *> m_components;

	RenderingEngine *m_renderingEngine;
	GLWindow *m_window;
	Timer *m_timer;

public:
	GameObject();
	~GameObject();

	void Update();
	void Render();

	void AddToRenderingEngine();

	inline GameObject *AddChild(GameObject *child)
	{
		child->SetRenderingEngine(m_renderingEngine);
		child->SetWindow(m_window);
		child->SetTimer(m_timer);
		child->GetTransform()->SetParentTransform(m_transform);
		child->AddToRenderingEngine();
		m_children.push_back(child);

		return this;
	}

	inline GameObject *AddComponent(IGameComponent *component)
	{
		component->SetTransform(m_transform);
		component->SetRenderingEngine(m_renderingEngine);
		component->SetWindow(m_window);
		component->SetTimer(m_timer);
		component->Init();
		component->AddToRenderingEngine();
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
	inline GLWindow *GetWindow() const { return m_window; }
	inline Timer *GetTimer() const { return m_timer; }
};

#endif