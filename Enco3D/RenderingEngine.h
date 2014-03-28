#ifndef _ENCO3D_RENDERINGENGINE_H_
#define _ENCO3D_RENDERINGENGINE_H_

#include "Matrix4x4.h"
#include "Transform.h"
#include "GBuffer.h"
#include "Mesh.h"
#include "Material.h"

#include <vector>
#include <GL/glew.h>
#include <algorithm>

using namespace std;

namespace Enco3D
{
	namespace Core
	{
		class GameObject;
	}

	namespace Component
	{
		class Camera;
		class Light;
	}
}

namespace Enco3D
{
	namespace Rendering
	{
		using namespace Core;
		using namespace Component;

		class RenderingEngine
		{
		private:
			Camera *m_mainCamera{ nullptr }, *m_GUICamera{ nullptr };
			vector<Light *> m_lights;
			Vector3f m_globalAmbientColor;

			GBuffer *m_gbuffer{ nullptr };
			unsigned int m_width, m_height;
			Mesh *m_renderWindow{ nullptr };
			Material m_renderWindowMaterial;

		public:
			RenderingEngine();
			RenderingEngine(unsigned int width, unsigned int height);
			~RenderingEngine();

			void Render(GameObject *gameObject);

			Matrix4x4f GetProjectedMatrix(const Camera *camera, const Matrix4x4f &worldMatrix);
			Matrix4x4f GetViewProjectedMatrix(const Camera *camera, const Matrix4x4f &worldMatrix);
			
			inline Vector3f PixelsToScreenCoords(float x, float y) const { return Vector3f(x / (float)m_width * 2.0f - 1.0f, y / (float)m_height * 2.0f - 1.0f, 0.0f); }
			inline Vector3f PixelsToImageScale(float width, float height) const { return Vector3f(width / (float)m_width, height / (float)m_height, 1.0f); }

			inline void AddLight(Light *light) { m_lights.push_back(light); }
			inline void RemoveLight(Light *light) { m_lights.erase(remove(m_lights.begin(), m_lights.end(), light), m_lights.end()); }

			inline void SetClearColor(float r, float g, float b) const { glClearColor(r, g, b, 1); }

			inline void SetMainCamera(Camera *mainCamera) { m_mainCamera = mainCamera; }
			inline void SetGlobalAmbientColor(const Vector3f &globalAmbientColor) { m_globalAmbientColor = globalAmbientColor; }
			inline void SetWidth(unsigned int width) { m_width = width; }
			inline void SetHeight(unsigned int height) { m_height = height; }

			inline Camera *GetMainCamera() const { return m_mainCamera; }
			inline Camera *GetGUICamera() const { return m_GUICamera; }
			inline vector<Light *> GetLights() const { return m_lights; }
			inline Vector3f GetGlobalAmbientColor() const { return m_globalAmbientColor; }

			inline unsigned int GetWidth() const { return m_width; }
			inline unsigned int GetHeight() const { return m_height; }
		};
	}
}

#endif