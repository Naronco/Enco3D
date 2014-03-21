#ifndef _ENCO3D_IGAME_H_
#define _ENCO3D_IGAME_H_

#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "GLWindow.h"
#include "Timer.h"
#include "GameObject.h"

/// <summary>Main interface class for a game</summary>
class IGame
{
private:
	/// <summary>Pointer to the rendering engine</summary>
	RenderingEngine *m_renderingEngine{ nullptr };

	/// <summary>Pointer to the physics engine</summary>
	PhysicsEngine *m_physicsEngine{ nullptr };

	/// <summary>Pointer to the GL window</summary>
	GLWindow *m_window{ nullptr };

	/// <summary>Pointer to the timer</summary>
	Timer *m_timer{ nullptr };

	/// <summary>Pointer to the root game object of the hierarchy</summary>
	GameObject *m_rootObject{ nullptr };

public:
	/// <summary>Virtual void, which will be called when the game should be initialized</summary>
	virtual void Init() {  }

	/// <summary>Virtual void, which will be called if the game closes</summary>
	virtual void Deinit() {  }

	/// <summary>Virtual void, which will be called if the game updates (Called once per frame)</summary>
	virtual void Update() {  }

	/// <summary>Virtual void, which will be called if the game renders (Called once per frame)</summary>
	virtual void Render() {  }

	/// <summary>Updates all the game objects</summary>
	inline void UpdateGameObjects()
	{
		GetRootObject()->Update();
	}

	/// <summary>Renders all the game objects and clears the screen</summary>
	inline void RenderGameObjects()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GetRootObject()->Render();
	}

	/// <summary>Adds the given game object to the scene hierarchy</summary>
	/// <param name="gameObject">The game object to add</param>
	inline void AddGameObject(GameObject *gameObject)
	{
		GetRootObject()->AddChild(gameObject);
	}

	/// <summary>Adds the given game component to the scene hierarchy</summary>
	/// <param name="gameComponent">The game component to add</param>
	inline void AddGameComponent(IGameComponent *gameComponent)
	{
		GetRootObject()->AddComponent(gameComponent);
	}

	/// <summary>Sets the rendering engine of the hierarchy</summary>
	/// <param name="renderingEngine">The new rendering engine</param>
	inline void SetRenderingEngine(RenderingEngine *renderingEngine)
	{
		m_renderingEngine = renderingEngine;
		GetRootObject()->SetRenderingEngine(renderingEngine);
	}

	/// <summary>Sets the physics engine of the hierarchy</summary>
	/// <param name="physicsEngine">The new physics engine</param>
	inline void SetPhysicsEngine(PhysicsEngine *physicsEngine)
	{
		m_physicsEngine = physicsEngine;
		GetRootObject()->SetPhysicsEngine(physicsEngine);
	}

	/// <summary>Sets the main GL window of the hierarchy</summary>
	/// <param name="window">The new main GL window</param>
	inline void SetWindow(GLWindow *window)
	{
		m_window = window;
		GetRootObject()->SetWindow(window);
	}

	/// <summary>Sets the main timer of the hierarchy</summary>
	/// <param name="timer">The new main timer</param>
	inline void SetTimer(Timer *timer)
	{
		m_timer = timer;
		GetRootObject()->SetTimer(timer);
	}

	/// <summary>Returns the rendering engine</summary>
	inline RenderingEngine *GetRenderingEngine() const { return m_renderingEngine; }

	/// <summary>Returns the physics engine</summary>
	inline PhysicsEngine *GetPhysicsEngine() const { return m_physicsEngine; }

	/// <summary>Returns the main GL window</summary>
	inline GLWindow *GetWindow() const { return m_window; }

	/// <summary>Returns the main timer</summary>
	inline Timer *GetTimer() const { return m_timer; }

	/// <summary>Returns the root object of the hierarchy, and initializes it if it's a null pointer</summary>
	inline GameObject *GetRootObject()
	{
		if (m_rootObject == nullptr)
		{
			m_rootObject = new GameObject;
		}

		return m_rootObject;
	}
};

#endif