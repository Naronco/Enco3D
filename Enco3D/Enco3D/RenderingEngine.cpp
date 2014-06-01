#include "RenderingEngine.h"
#include "GameObject.h"
#include "Camera.h"
#include "ILight.h"
#include "Skybox.h"
#include "ShaderPool.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "IPostProcessEffect.h"
#include "DebugLogger.h"

void Enco3D::Rendering::RenderingEngine::initDeferredShading()
{
	m_gbuffer0 = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_gbuffer1 = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_depthBuffer = new Texture2D(m_width, m_height, GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_NEAREST, GL_CLAMP_TO_EDGE);

	m_geometryFramebuffer = new Framebuffer;
	m_geometryFramebuffer->attachTexture2D(m_gbuffer0, Attachment::Color0);
	m_geometryFramebuffer->attachTexture2D(m_gbuffer1, Attachment::Color1);
	m_geometryFramebuffer->attachTexture2D(m_depthBuffer, Attachment::Depth);
	m_geometryFramebuffer->pack();

	Vertex vertices[4] =
	{
		Vertex((float)m_width, 0, 0).setTexCoord(0, 0, 0).setNormal(0, 0, 1),
		Vertex((float)m_width, (float)m_height, 0).setTexCoord(0, 1, 0).setNormal(0, 0, 1),
		Vertex(0, (float)m_height, 0).setTexCoord(1, 1, 0).setNormal(0, 0, 1),
		Vertex(0, 0, 0).setTexCoord(1, 0, 0).setNormal(0, 0, 1),
	};

	unsigned int indices[6] =
	{
		2, 0, 1,
		3, 0, 2,
	};

	m_renderWindow = new Mesh(vertices, 4, indices, 6);
}

void Enco3D::Rendering::RenderingEngine::deinitDeferredShading()
{
	delete m_geometryFramebuffer;
	m_geometryFramebuffer = nullptr;

	delete m_depthBuffer;
	m_depthBuffer = nullptr;

	delete m_gbuffer1;
	m_gbuffer1 = nullptr;

	delete m_gbuffer0;
	m_gbuffer0 = nullptr;

	delete m_renderWindow;
	m_renderWindow = nullptr;
}

Enco3D::Rendering::RenderingEngine::RenderingEngine()
{
}

Enco3D::Rendering::RenderingEngine::RenderingEngine(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;

	m_globalAmbientColor.set(0.1f, 0.1f, 0.1f);

	m_GUICamera = new Component::Camera;
	m_GUICamera->setOrthographicProjection(0, (float)width, (float)height, 0, -1, 1);

	m_textureShader = ShaderPool::getInstance()->getShader("shaders/texture", ShaderType::VertexShader | ShaderType::FragmentShader);
	m_ambientShader = ShaderPool::getInstance()->getShader("shaders/forwardAmbient", ShaderType::VertexShader | ShaderType::FragmentShader);
	m_finalShader = ShaderPool::getInstance()->getShader("shaders/final", ShaderType::VertexShader | ShaderType::FragmentShader);
	m_geometryBufferShader = ShaderPool::getInstance()->getShader("shaders/geometryBuffer", ShaderType::VertexShader | ShaderType::FragmentShader);

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glEnable(GL_ALPHA_TEST);
	//	glAlphaFunc(GL_GREATER, 0.5f);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
}

#define SAFE_DELETE(x) { if(x) { delete x; x = nullptr; } }

Enco3D::Rendering::RenderingEngine::~RenderingEngine()
{
	SAFE_DELETE(m_renderWindow);

	SAFE_DELETE(m_gbuffer0);
	SAFE_DELETE(m_gbuffer1);
	SAFE_DELETE(m_depthBuffer);
	SAFE_DELETE(m_geometryFramebuffer);
}

void Enco3D::Rendering::RenderingEngine::resize(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;

	Vertex vertices[4] =
	{
		Vertex((float)width, 0, 0).setTexCoord(0, 0, 0).setNormal(0, 0, 1),
		Vertex((float)width, (float)height, 0).setTexCoord(0, 1, 0).setNormal(0, 0, 1),
		Vertex(0, (float)height, 0).setTexCoord(1, 1, 0).setNormal(0, 0, 1),
		Vertex(0, 0, 0).setTexCoord(1, 0, 0).setNormal(0, 0, 1),
	};

	m_renderWindow->updateVertices(0, 4, vertices);

	delete m_depthBuffer;
	delete m_gbuffer1;
	delete m_gbuffer0;

	m_gbuffer0 = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_gbuffer1 = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_depthBuffer = new Texture2D(m_width, m_height, GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_NEAREST, GL_CLAMP_TO_EDGE);

	delete m_geometryFramebuffer;

	m_geometryFramebuffer = new Framebuffer;
	m_geometryFramebuffer->attachTexture2D(m_gbuffer0, Attachment::Color0);
	m_geometryFramebuffer->attachTexture2D(m_gbuffer1, Attachment::Color1);
	m_geometryFramebuffer->attachTexture2D(m_depthBuffer, Attachment::Depth);
	m_geometryFramebuffer->pack();
}

void Enco3D::Rendering::RenderingEngine::render(Enco3D::Core::GameObject *gameObject)
{
	glPolygonMode(GL_FRONT_AND_BACK, m_rasterizerMode);
	for (int i = 0; i < MAX_CAMERAS; i++)
	{
		if (m_cameras[i] == nullptr)
			continue;

		if (m_deferredShadingEnabled)
			renderCamera_Deferred(gameObject, m_cameras[i]);
		else
			renderCamera_Forward(gameObject, m_cameras[i]);
	}

	// GUI Rendering

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gameObject->renderGUI(m_GUICamera, m_textureShader);
	glEnable(GL_DEPTH_TEST);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		Core::DebugLogger::log("[GL_ERROR] GL reported an error with code: " + std::to_string(error));
}

void Enco3D::Rendering::RenderingEngine::renderCamera_Forward(Enco3D::Core::GameObject *gameObject, Enco3D::Component::Camera *camera)
{
	//////////////////////////////////////////////////////////////////////////////
	////////////////////////// RENDER INTO FRAMEBUFFER ///////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_skybox != nullptr)
	{
		glDisable(GL_DEPTH_TEST);
		m_skybox->render(camera);
		glEnable(GL_DEPTH_TEST);
	}

	gameObject->render(camera, m_ambientShader);

	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);

	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		gameObject->render(camera, m_lights[i]->getShader());
	}

	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Enco3D::Rendering::RenderingEngine::renderCamera_Deferred(Enco3D::Core::GameObject *gameObject, Enco3D::Component::Camera *camera)
{
	//////////////////////////////////////////////////////////////////////////////
	////////////////////////// RENDER INTO FRAMEBUFFER ///////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	bindFramebuffer(m_geometryFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_skybox != nullptr)
	{
		glDisable(GL_DEPTH_TEST);
		m_skybox->render(camera);
		glEnable(GL_DEPTH_TEST);
	}

	gameObject->render(camera, m_geometryBufferShader);

	//	glBlendFunc(GL_ONE, GL_ONE);
	//	glDepthMask(GL_FALSE);

	/*	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
	m_activeLight = m_lights[i];
	gameObject->Render(m_mainCamera, m_lights[i]->GetShader());
	}*/

	//	glDepthMask(GL_TRUE);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Skybox Rendering

	bindFramebuffer(nullptr);

	//////////////////////////////////////////////////////////////////////////////
	////////////////////////////// POST PROCESSING ///////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	std::vector<Component::IPostProcessEffect*> postProcessEffects = camera->getPostProcessEffects();

	glDisable(GL_DEPTH_TEST);

	// Post Processing

	m_postProcessWorldViewProjectionMatrix.setOrthographicProjection((float)m_width, 0, 0, (float)m_height, -1, 1);
	m_postProcessTexelSize.set(1.0f / (float)m_width, 1.0f / (float)m_height);

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	for (unsigned int i = 0; i < postProcessEffects.size(); i++)
		postProcessEffects[i]->postProcess(camera);

	glClear(GL_COLOR_BUFFER_BIT);

	m_finalShader->bind();
	m_finalShader->setUniformMatrix4x4f("matrix_worldViewProjectionMatrix", m_postProcessWorldViewProjectionMatrix);

	for (unsigned int i = 0; i < postProcessEffects.size(); i++)
	{
		int slot = (int)postProcessEffects[i]->getGeneratedImageSlot();
		postProcessEffects[i]->getFinalBuffer()->bind(10 + slot);
		m_finalShader->setUniformInt("generatedImage_slot" + std::to_string(10 + slot), 10 + slot);
	}

	m_depthBuffer->bind(TextureSampler::Sampler2); m_finalShader->setUniformInt("gbuffer_depth", TextureSampler::Sampler2);
	m_gbuffer1->bind(TextureSampler::Sampler1); m_finalShader->setUniformInt("gbuffer_1", TextureSampler::Sampler1);
	m_gbuffer0->bind(TextureSampler::Sampler0); m_finalShader->setUniformInt("gbuffer_0", TextureSampler::Sampler0);

	m_finalShader->setUniformVector2f("postProcess_texelSize", m_postProcessTexelSize);

	m_finalShader->setUniformFloat("camera_tanHalfFov", camera->getTanHalfFov());
	m_finalShader->setUniformFloat("camera_aspectRatio", camera->getAspectRatio());
	m_finalShader->setUniformFloat("camera_zNearClippingPlane", camera->getZNearClippingPlane());
	m_finalShader->setUniformFloat("camera_zFarClippingPlane", camera->getZFarClippingPlane());

	m_finalShader->setUniformFloat("velocityScale", 1.0f);

	m_renderWindow->render();
}

bool Enco3D::Rendering::RenderingEngine::setDeferredShadingEnabled(bool enabled)
{
	if (enabled && m_deferredShadingEnabled)
	{
		Core::DebugLogger::log("Deferred shading already enabled! Aborting");
		return false;
	}
	else if (!enabled && !m_deferredShadingEnabled)
	{
		Core::DebugLogger::log("Deferred shading isn't enabled! Aborting");
		return false;
	}

	m_deferredShadingEnabled = enabled;
	if (enabled)
	{
		initDeferredShading();
	}
	else
	{
		deinitDeferredShading();
	}

	return true;
}

void Enco3D::Rendering::RenderingEngine::initializePostProcessEffect(Component::IPostProcessEffect *effect)
{
	effect->setGBuffer0(m_gbuffer0);
	effect->setGBuffer1(m_gbuffer1);
	effect->setDepthBuffer(m_depthBuffer);
}

Enco3D::Component::Camera *Enco3D::Rendering::RenderingEngine::createPerspectiveCamera(float fovInRadians, float zNear, float zFar)
{
	float aspectRatio = (float)m_width / (float)m_height;
	return new Component::Camera(fovInRadians, aspectRatio, zNear, zFar);
}

Enco3D::Component::Camera *Enco3D::Rendering::RenderingEngine::createOrthographicCamera(float zNear, float zFar, float size)
{
	return new Component::Camera(-size, size, -size, size, zNear, zFar);
}