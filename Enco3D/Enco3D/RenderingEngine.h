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
			Solid = GL_FILL,
			Wireframe = GL_LINE,
		};

#		define MAX_CAMERAS 5

		class RenderingEngine
		{
		private:
			Component::Camera *m_GUICamera{ nullptr };
			Component::Camera *m_cameras[MAX_CAMERAS];
			Component::Skybox *m_skybox{ nullptr };
			std::vector<Component::ILight *> m_lights;
			Component::ILight *m_activeLight{ nullptr };
			Core::Vector3f m_globalAmbientColor;
			unsigned int m_width, m_height;
			unsigned int m_rasterizerMode{ GL_FILL };

			Shader *m_textureShader{ nullptr };

			// FORWARD RENDERING

			Shader *m_basicShader{ nullptr };
			Shader *m_ambientShader{ nullptr };

			// POST PROCESSING - DEFERRED SHADING

			bool m_deferredShadingEnabled{ false };

			Framebuffer *m_geometryFramebuffer;
			Texture2D *m_gbuffer0; // RGB = Albedo, A = Specular
			Texture2D *m_gbuffer1; // RGB = Normals, A = Glossiness
			Texture2D *m_depthBuffer; // Depth

			Core::Matrix4x4f m_postProcessWorldViewProjectionMatrix;
			Core::Vector2f m_postProcessTexelSize;

			Shader *m_finalShader{ nullptr };
			Shader *m_geometryBufferShader{ nullptr };
			Mesh *m_renderWindow{ nullptr };

		private:
			void initDeferredShading();
			void deinitDeferredShading();

		public:
			RenderingEngine();
			RenderingEngine(unsigned int width, unsigned int height);
			~RenderingEngine();

			void resize(unsigned int width, unsigned int height);

			void render(Core::GameObject *gameObject);
			void renderCamera_Forward(Core::GameObject *gameObject, Component::Camera *camera);
			void renderCamera_Deferred(Core::GameObject *gameObject, Component::Camera *camera);

			inline void addLight(Component::ILight *light) { m_lights.push_back(light); }
			inline void removeLight(Component::ILight *light) { m_lights.erase(remove(m_lights.begin(), m_lights.end(), light), m_lights.end()); }

			bool setDeferredShadingEnabled(bool enabled);

			void initializePostProcessEffect(Component::IPostProcessEffect *effect);

			Component::Camera *createPerspectiveCamera(float fovInRadians, float zNear, float zFar);
			Component::Camera *createOrthographicCamera(float zNear, float zFar, float size = 1.0f);

			inline void setClearColor(float r, float g, float b) const { glClearColor(r, g, b, 0); }
			inline void setClearColor(const Core::Vector3f &color) const { glClearColor(color.x, color.y, color.z, 0); }
			inline void setRasterizationMode(unsigned int mode) { m_rasterizerMode = mode; }
			inline void setCamera(Component::Camera *camera, unsigned int index) { m_cameras[index] = camera; }
			inline void setSkybox(Component::Skybox *skybox) { m_skybox = skybox; }
			inline void setGlobalAmbientColor(const Core::Vector3f &globalAmbientColor) { m_globalAmbientColor = globalAmbientColor; }
			inline void setGlobalAmbientColor(float r, float g, float b) { m_globalAmbientColor.set(r, g, b); }
			inline void setWidth(unsigned int width) { m_width = width; }
			inline void setHeight(unsigned int height) { m_height = height; }

			inline Component::Camera *getCamera(unsigned int depth) const { return m_cameras[depth]; }
			inline Component::Skybox *getSkybox() const { return m_skybox; }
			inline Component::Camera *getGUICamera() const { return m_GUICamera; }
			inline std::vector<Component::ILight*> getLights() const { return m_lights; }
			inline Core::Vector3f getGlobalAmbientColor() const { return m_globalAmbientColor; }
			inline Component::ILight *getActiveLight() const { return m_activeLight; };
			inline Mesh *getRenderWindow() const { return m_renderWindow; }
			inline Core::Matrix4x4f getPostProcessWorldViewProjectionMatrix() const { return m_postProcessWorldViewProjectionMatrix; }
			inline Core::Vector2f getPostProcessTexelSize() const { return m_postProcessTexelSize; }
			inline unsigned int getWidth() const { return m_width; }
			inline unsigned int getHeight() const { return m_height; }
		};
	}
}

#endif