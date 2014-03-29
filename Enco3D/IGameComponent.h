#ifndef _IGAMECOMPONENT_H_
#define _IGAMECOMPONENT_H_

#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "GLWindow.h"
#include "Timer.h"
#include "Transform.h"
#include "GameObject.h"

#include <string>

using namespace std;

namespace Enco3D
{
	namespace Core
	{
		class IGameComponent
		{
		protected:
			GameObject *m_gameObject;
			string m_name;

		public:
			virtual void Init() {  }
			virtual void Deinit() {  }

			virtual void InitRendering() {  }
			virtual void InitPhysics() {  }

			virtual void Update() {  }
			virtual void Render(const Camera *camera, Shader *shader) {  }
			virtual void RenderGUI(const Camera *camera, Shader *shader) {  }

			inline void SetGameObject(GameObject *gameObject) { m_gameObject = gameObject; }
			inline void SetName(const string &name) { m_name = name; }

			inline GameObject *GetGameObject() const { return m_gameObject; }
			inline RenderingEngine *GetRenderingEngine() const { return m_gameObject->GetRenderingEngine(); }
			inline PhysicsEngine *GetPhysicsEngine() const { return m_gameObject->GetPhysicsEngine(); }
			inline GLWindow *GetWindow() const { return m_gameObject->GetWindow(); }
			inline Timer *GetTimer() const { return m_gameObject->GetTimer(); }
			inline Transform *GetTransform() const { return m_gameObject->GetTransform(); }
			inline string GetName() const { return m_name; }
		};
	}
}

#endif