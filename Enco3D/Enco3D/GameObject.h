#ifndef _ENCO3D_GAMEOBJECT_H_
#define _ENCO3D_GAMEOBJECT_H_

#include "Transform.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "GLWindow.h"
#include "Timer.h"

#include <vector>
#include <iostream>
#include <string>

namespace Enco3D
{
	namespace Core
	{
		class IGameComponent;
	}

	namespace Rendering
	{
		class Shader;
	}
}

namespace Enco3D
{
	namespace Core
	{
		class GameObject
		{
		private:
			Transform *m_transform{ nullptr };
			string m_name;
			bool m_enabled{ true };

			vector<GameObject *> m_children;
			vector<IGameComponent *> m_components;

			Rendering::RenderingEngine *m_renderingEngine{ nullptr };
			Physics::PhysicsEngine *m_physicsEngine{ nullptr };
			GLWindow *m_window{ nullptr };
			Timer *m_timer{ nullptr };

		public:
			GameObject();
			GameObject(const string &name);
			~GameObject();

			void Update();
			void Render(const Component::Camera *camera, Rendering::Shader *shader);
			void RenderGUI(const Component::Camera *camera, Rendering::Shader *shader);

			void Resize(unsigned int width, unsigned int height);

			GameObject *AddChild(GameObject *child);
			GameObject *AddComponent(IGameComponent *component);
			void RemoveComponent(IGameComponent *component);

			void SetRenderingEngine(Rendering::RenderingEngine *renderingEngine);
			void SetPhysicsEngine(Physics::PhysicsEngine *physicsEngine);
			void SetWindow(GLWindow *window);
			void SetTimer(Timer *timer);

			inline void SetName(const string &name) { m_name = name; }
			inline void SetEnabled(bool enabled) { m_enabled = enabled; }

			GameObject *GetChild(const string &name) const;

			template <typename T>
			IGameComponent *GetGameComponent() const {
				for (unsigned int i = m_components.size() - 1; i >= 0; i--)
					if (typeid(*m_components[i]) == typeid(T))
						return m_components[i];

				return nullptr;
			}

			inline Transform *GetTransform() const { return m_transform; }
			inline string GetName() const { return m_name; }
			inline bool IsEnabled() const { return m_enabled; }
			inline vector<GameObject *> GetChildren() const { return m_children; }
			inline vector<IGameComponent *> GetComponents() const { return m_components; }
			inline Rendering::RenderingEngine *GetRenderingEngine() const { return m_renderingEngine; }
			inline Physics::PhysicsEngine *GetPhysicsEngine() const { return m_physicsEngine; }
			inline GLWindow *GetWindow() const { return m_window; }
			inline Timer *GetTimer() const { return m_timer; }
		};
	}
}

#endif