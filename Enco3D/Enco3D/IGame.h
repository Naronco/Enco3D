#ifndef _ENCO3D_IGAME_H_
#define _ENCO3D_IGAME_H_

#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "AudioEngine.h"
#include "GLWindow.h"
#include "Timer.h"
#include "GameObject.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Core
	{
		/// <summary>Main interface class for a game</summary>
		class DLL_EXPORT IGame
		{
		private:
			/// <summary>Pointer to the rendering engine</summary>
			Rendering::RenderingEngine *m_renderingEngine{ nullptr };

			/// <summary>Pointer to the physics engine</summary>
			Physics::PhysicsEngine *m_physicsEngine{ nullptr };

			/// <summary>Pointer to the audio engine</summary>
			Audio::AudioEngine *m_audioEngine{ nullptr };

			/// <summary>Pointer to the GL window</summary>
			GLWindow *m_window{ nullptr };

			/// <summary>Pointer to the timer</summary>
			Timer *m_timer{ nullptr };

			/// <summary>Pointer to the root game object of the hierarchy</summary>
			GameObject *m_rootObject{ nullptr };

		public:
			/// <summary>Virtual void, which will be called when the game should be initialized</summary>
			virtual void init() {  }

			/// <summary>Virtual void, which will be called if the game closes</summary>
			virtual void deinit() {  }

			/// <summary>Virtual void, which will be called if the game updates (Called once per frame)</summary>
			virtual void update() {  }

			/// <summary>Adds the given game object to the scene hierarchy</summary>
			/// <param name="gameObject">The game object to add</param>
			inline void addGameObject(GameObject *gameObject)
			{
				getRootObject()->addChild(gameObject);
			}

			/// <summary>Adds the given game component to the scene hierarchy</summary>
			/// <param name="gameComponent">The game component to add</param>
			inline void addGameComponent(IGameComponent *gameComponent)
			{
				getRootObject()->addComponent(gameComponent);
			}

			/// <summary>Sets the rendering engine of the hierarchy</summary>
			/// <param name="renderingEngine">The new rendering engine</param>
			inline void setRenderingEngine(Rendering::RenderingEngine *renderingEngine)
			{
				m_renderingEngine = renderingEngine;
				getRootObject()->setRenderingEngine(renderingEngine);
			}

			/// <summary>Sets the physics engine of the hierarchy</summary>
			/// <param name="physicsEngine">The new physics engine</param>
			inline void setPhysicsEngine(Physics::PhysicsEngine *physicsEngine)
			{
				m_physicsEngine = physicsEngine;
				getRootObject()->setPhysicsEngine(physicsEngine);
			}

			/// <summary>Sets the audio engine of the hierarchy</summary>
			/// <param name="audioEngine">The new audio engine</param>
			inline void setAudioEngine(Audio::AudioEngine *audioEngine)
			{
				m_audioEngine = audioEngine;
			}

			/// <summary>Sets the main GL window of the hierarchy</summary>
			/// <param name="window">The new main GL window</param>
			inline void setWindow(GLWindow *window)
			{
				m_window = window;
				getRootObject()->setWindow(window);
			}

			/// <summary>Sets the main timer of the hierarchy</summary>
			/// <param name="timer">The new main timer</param>
			inline void setTimer(Timer *timer)
			{
				m_timer = timer;
				getRootObject()->setTimer(timer);
			}

			/// <summary>Returns the rendering engine</summary>
			inline Rendering::RenderingEngine *getRenderingEngine() const { return m_renderingEngine; }

			/// <summary>Returns the physics engine</summary>
			inline Physics::PhysicsEngine *getPhysicsEngine() const { return m_physicsEngine; }

			/// <summary>Returns the audio engine</summary>
			inline Audio::AudioEngine *getAudioEngine() const { return m_audioEngine; }

			/// <summary>Returns the main GL window</summary>
			inline GLWindow *getWindow() const { return m_window; }

			/// <summary>Returns the main timer</summary>
			inline Timer *getTimer() const { return m_timer; }

			/// <summary>Returns the root object of the hierarchy, and initializes it if it's a null pointer</summary>
			inline GameObject *getRootObject()
			{
				if (m_rootObject == nullptr)
					m_rootObject = new GameObject;

				return m_rootObject;
			}

			inline GameObject *createGameObject(const std::string &name)
			{
				GameObject *go = new GameObject(name);
				//				addGameObject(go);
				return go;
			}
		};
	}
}

#endif