#ifndef _ENCO3D_GAMEOBJECT_H_
#define _ENCO3D_GAMEOBJECT_H_

#include "Transform.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "GLWindow.h"
#include "Timer.h"
#include "DLLExport.h"

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
		class DLL_EXPORT GameObject
		{
		private:
			Transform *m_transform{ nullptr };
			std::string m_name;
			bool m_enabled{ true };

			std::vector<GameObject*> m_children;
			std::vector<IGameComponent*> m_components;

			Rendering::RenderingEngine *m_renderingEngine{ nullptr };
			Physics::PhysicsEngine *m_physicsEngine{ nullptr };
			GLWindow *m_window{ nullptr };
			Timer *m_timer{ nullptr };

		public:
			GameObject();
			GameObject(const std::string &name);
			~GameObject();

			void update();
			void render(const Component::Camera *camera, Rendering::Shader *shader);
			void renderGUI(const Component::Camera *camera, Rendering::Shader *shader);

			void resize(unsigned int width, unsigned int height);

			GameObject *addChild(GameObject *child);
			GameObject *addComponent(IGameComponent *component);
			void removeComponent(IGameComponent *component);

			void setRenderingEngine(Rendering::RenderingEngine *renderingEngine);
			void setPhysicsEngine(Physics::PhysicsEngine *physicsEngine);
			void setWindow(GLWindow *window);
			void setTimer(Timer *timer);

			inline void setName(const std::string &name) { m_name = name; }
			inline void setEnabled(bool enabled) { m_enabled = enabled; }

			GameObject *getChild(const std::string &name) const;

			template <typename T> IGameComponent *getGameComponent() const {
				for (unsigned int i = m_components.size() - 1; i >= 0; i--)
					if (typeid(*m_components[i]) == typeid(T))
						return m_components[i];
				return nullptr;
			}

			inline Transform *getTransform() const { return m_transform; }
			inline std::string getName() const { return m_name; }
			inline bool isEnabled() const { return m_enabled; }
			inline std::vector<GameObject *> getChildren() const { return m_children; }
			inline std::vector<IGameComponent *> getComponents() const { return m_components; }
			inline Rendering::RenderingEngine *getRenderingEngine() const { return m_renderingEngine; }
			inline Physics::PhysicsEngine *getPhysicsEngine() const { return m_physicsEngine; }
			inline GLWindow *getWindow() const { return m_window; }
			inline Timer *getTimer() const { return m_timer; }
		};
	}
}

#endif