#ifndef _IGAMECOMPONENT_H_
#define _IGAMECOMPONENT_H_

#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "GLWindow.h"
#include "Timer.h"
#include "Transform.h"
#include "GameObject.h"

#include <string>

namespace Enco3D
{
	namespace Core
	{
		class IGameComponent
		{
		protected:
			GameObject *m_gameObject;

			bool m_enabled;
			
		public:
			virtual void init() {  }
			virtual void deinit() {  }

			virtual void initRendering() {  }
			virtual void initPhysics() {  }

			virtual void update() {  }
			virtual void render(const Component::Camera *camera, Rendering::Shader *shader) {  }
			virtual void renderGUI(const Component::Camera *camera, Rendering::Shader *shader) {  }

			virtual void resize(unsigned int width, unsigned int height) {  }

			virtual void onAddComponentToObject(IGameComponent *component) {  }
			virtual void onRemoveComponentFromObject(IGameComponent *component) {  }

			inline void setGameObject(GameObject *gameObject) { m_gameObject = gameObject; }

			inline GameObject *getGameObject() const { return m_gameObject; }
			inline Rendering::RenderingEngine *getRenderingEngine() const { return m_gameObject->getRenderingEngine(); }
			inline Physics::PhysicsEngine *getPhysicsEngine() const { return m_gameObject->getPhysicsEngine(); }
			inline GLWindow *getWindow() const { return m_gameObject->getWindow(); }
			inline Timer *getTimer() const { return m_gameObject->getTimer(); }
			inline Transform *getTransform() const { return m_gameObject->getTransform(); }
			inline void enable() { m_enabled = true; }
			inline void disable() { m_enabled = false; }
		};
	}
}

#endif