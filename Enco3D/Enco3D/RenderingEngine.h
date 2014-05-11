#ifndef _ENCO3D_RENDERINGENGINE_H_
#define _ENCO3D_RENDERINGENGINE_H_

#include "Matrix4x4.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Framebuffer.h"

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
		class Skybox;

		class ILight;
		class IPostProcessEffect;
	}

	namespace Rendering
	{
		class Shader;
	}
}

namespace Enco3D
{
	namespace Rendering
	{
		enum RasterizationMode : GLenum
		{
			Solid     = GL_FILL,
			Wireframe = GL_LINE,
		};

#		define MAX_CAMERAS 5

		class RenderingEngine
		{
		private:
			Component::Camera *m_GUICamera{ nullptr };
			Component::Camera *m_cameras[MAX_CAMERAS];
			Component::Skybox *m_skybox{ nullptr };
			vector<Component::ILight *> m_lights;
			Component::ILight *m_activeLight{ nullptr };
			Core::Vector3f m_globalAmbientColor;
			unsigned int m_width, m_height;
			float m_zNearClippingPlane{ 0.0f }, m_zFarClippingPlane{ 0.0f };

			Shader *m_textureShader{ nullptr };
			Shader *m_geometryBufferShader{ nullptr };

			Framebuffer *m_geometryFramebuffer;
			Texture2D *m_positionBuffer;
			Texture2D *m_normalBuffer;
			Texture2D *m_lightBuffer;
			Texture2D *m_backgroundBuffer;
			Texture2D *m_velocityBuffer;
			Texture2D *m_depthBuffer;

			Framebuffer *m_compositeFramebuffer;
			Texture2D *m_compositeBuffer;

			Core::Matrix4x4f m_postProcessWorldViewProjectionMatrix;
			Core::Vector2f m_postProcessTexelSize;
			
			Shader *m_compositeShader{ nullptr };
			Shader *m_finalShader{ nullptr };

			Mesh *m_renderWindow{ nullptr };

		public:
			RenderingEngine();
			RenderingEngine(unsigned int width, unsigned int height);
			~RenderingEngine();

			void Resize(unsigned int width, unsigned int height);

			void Render(Core::GameObject *gameObject);
			void RenderCamera(Core::GameObject *gameObject, Component::Camera *camera);

			inline void AddLight(Component::ILight *light) { m_lights.push_back(light); }
			inline void RemoveLight(Component::ILight *light) { m_lights.erase(remove(m_lights.begin(), m_lights.end(), light), m_lights.end()); }

			void InitializePostProcessEffect(Component::IPostProcessEffect *effect);

			Component::Camera *CreatePerspectiveCamera(float fovInRadians, float zNear, float zFar);
			Component::Camera *CreateOrthographicCamera(float zNear, float zFar);

			inline void SetClearColor(float r, float g, float b) const { glClearColor(r, g, b, 0); }
			inline void SetRasterizationMode(const RasterizationMode &mode) { glPolygonMode(GL_FRONT_AND_BACK, mode); }

			inline void SetCamera(Component::Camera *camera, unsigned int index) { m_cameras[index] = camera; }
			inline void SetSkybox(Component::Skybox *skybox) { m_skybox = skybox; }
			inline void SetGlobalAmbientColor(const Core::Vector3f &globalAmbientColor) { m_globalAmbientColor = globalAmbientColor; }
			inline void SetWidth(unsigned int width) { m_width = width; }
			inline void SetHeight(unsigned int height) { m_height = height; }
			inline void SetZNearClippingPlane(float val) { m_zNearClippingPlane = val; }
			inline void SetZFarClippingPlane(float val) { m_zFarClippingPlane = val; }

			inline Component::Camera *GetCamera(unsigned int depth) const { return m_cameras[depth]; }
			inline Component::Skybox *GetSkybox() const { return m_skybox; }
			inline Component::Camera *GetGUICamera() const { return m_GUICamera; }
			inline vector<Component::ILight *> GetLights() const { return m_lights; }
			inline Core::Vector3f GetGlobalAmbientColor() const { return m_globalAmbientColor; }
			inline Component::ILight *GetActiveLight() const { return m_activeLight; };
			inline float GetZNearClippingPlane() const { return m_zNearClippingPlane; }
			inline float GetZFarClippingPlane() const { return m_zFarClippingPlane; }
			inline Mesh *GetRenderWindow() const { return m_renderWindow; }
			inline Core::Matrix4x4f GetPostProcessWorldViewProjectionMatrix() const { return m_postProcessWorldViewProjectionMatrix; }
			inline Core::Vector2f GetPostProcessTexelSize() const { return m_postProcessTexelSize; }

			inline unsigned int GetWidth() const { return m_width; }
			inline unsigned int GetHeight() const { return m_height; }
		};
	}
}

#endif