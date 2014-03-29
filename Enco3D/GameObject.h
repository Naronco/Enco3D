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

using namespace std;

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
		using namespace Rendering;
		using namespace Physics;

		class GameObject
		{
		private:
			Transform *m_transform{ nullptr };
			string m_name;

			vector<GameObject *> m_children;
			vector<IGameComponent *> m_components;

			RenderingEngine *m_renderingEngine{ nullptr };
			PhysicsEngine *m_physicsEngine{ nullptr };
			GLWindow *m_window{ nullptr };
			Timer *m_timer{ nullptr };

		public:
			GameObject();
			GameObject(const string &name);
			~GameObject();

			void Update();
			void Render(const Camera *camera, Shader *shader);
			void RenderGUI(const Camera *camera, Shader *shader);

			GameObject *AddChild(GameObject *child);
			GameObject *AddComponent(IGameComponent *component);

			void SetRenderingEngine(RenderingEngine *renderingEngine);
			void SetPhysicsEngine(PhysicsEngine *physicsEngine);
			void SetWindow(GLWindow *window);
			void SetTimer(Timer *timer);

			inline void SetName(const string &name) { m_name = name; }

			GameObject *GetChild(const string &name) const;
			IGameComponent *GetGameComponent(const string &name) const;

			inline Transform *GetTransform() const { return m_transform; }
			inline string GetName() const { return m_name; }
			inline vector<GameObject *> GetChildren() const { return m_children; }
			inline vector<IGameComponent *> GetComponents() const { return m_components; }
			inline RenderingEngine *GetRenderingEngine() const { return m_renderingEngine; }
			inline PhysicsEngine *GetPhysicsEngine() const { return m_physicsEngine; }
			inline GLWindow *GetWindow() const { return m_window; }
			inline Timer *GetTimer() const { return m_timer; }
		};
	}
}

#endif