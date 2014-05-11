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

Enco3D::Rendering::RenderingEngine::RenderingEngine()
{
}

Enco3D::Rendering::RenderingEngine::RenderingEngine(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;

	m_globalAmbientColor.Set(0.1f, 0.1f, 0.1f);
	m_GUICamera = new Component::Camera;

	m_GUICamera->SetOrthographicProjection(0, (float)width, (float)height, 0, -1, 1);

	m_textureShader        = ShaderPool::GetInstance()->GetShader("shaders/texture", ShaderType::VertexShader | ShaderType::FragmentShader);
	m_geometryBufferShader = ShaderPool::GetInstance()->GetShader("shaders/geometryBuffer", ShaderType::VertexShader | ShaderType::FragmentShader);

// POST PROCESS INITIALIZATION //

	m_positionBuffer   = new Texture2D(m_width, m_height, GL_RGBA32F, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_normalBuffer     = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_lightBuffer      = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_backgroundBuffer = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_velocityBuffer   = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_depthBuffer      = new Texture2D(m_width, m_height, GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_NEAREST, GL_CLAMP_TO_EDGE);
	
	m_geometryFramebuffer = new Framebuffer;
	m_geometryFramebuffer->AttachTexture2D(m_positionBuffer, Attachment::Color0);
	m_geometryFramebuffer->AttachTexture2D(m_normalBuffer, Attachment::Color1);
	m_geometryFramebuffer->AttachTexture2D(m_lightBuffer, Attachment::Color2);
	m_geometryFramebuffer->AttachTexture2D(m_backgroundBuffer, Attachment::Color3);
	m_geometryFramebuffer->AttachTexture2D(m_velocityBuffer, Attachment::Color4);
	m_geometryFramebuffer->AttachTexture2D(m_depthBuffer, Attachment::Depth);
	m_geometryFramebuffer->Pack();

	m_compositeShader = ShaderPool::GetInstance()->GetShader("shaders/composite", ShaderType::VertexShader | ShaderType::FragmentShader);
	m_finalShader = ShaderPool::GetInstance()->GetShader("shaders/final", ShaderType::VertexShader | ShaderType::FragmentShader);

	m_compositeBuffer = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_compositeFramebuffer = new Framebuffer;
	m_compositeFramebuffer->AttachTexture2D(m_compositeBuffer, Attachment::Color0);
	m_compositeFramebuffer->Pack();

////////////////////////////

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

	Vertex vertices[4] =
	{
		Vertex((float)width, 0, 0).SetTexCoord(0, 0, 0).SetNormal(0, 0, 1),
		Vertex((float)width, (float)height, 0).SetTexCoord(0, 1, 0).SetNormal(0, 0, 1),
		Vertex(0, (float)height, 0).SetTexCoord(1, 1, 0).SetNormal(0, 0, 1),
		Vertex(0, 0, 0).SetTexCoord(1, 0, 0).SetNormal(0, 0, 1),
	};

	unsigned int indices[6] =
	{
		2, 0, 1,
		3, 0, 2,
	};

	m_renderWindow = new Mesh(vertices, 4, indices, 6);
}

#define __safedelete(x) { if(x){delete x;x=nullptr;} }
 
Enco3D::Rendering::RenderingEngine::~RenderingEngine()
{
	__safedelete(m_renderWindow);

	__safedelete(m_velocityBuffer);
	__safedelete(m_backgroundBuffer);
	__safedelete(m_depthBuffer);
	__safedelete(m_lightBuffer);
	__safedelete(m_normalBuffer);
	__safedelete(m_positionBuffer);
	__safedelete(m_geometryFramebuffer);

	__safedelete(m_compositeBuffer);
	__safedelete(m_compositeFramebuffer);
}

void Enco3D::Rendering::RenderingEngine::Resize(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;

	Vertex vertices[4] =
	{
		Vertex((float)width, 0, 0).SetTexCoord(0, 0, 0).SetNormal(0, 0, 1),
		Vertex((float)width, (float)height, 0).SetTexCoord(0, 1, 0).SetNormal(0, 0, 1),
		Vertex(0, (float)height, 0).SetTexCoord(1, 1, 0).SetNormal(0, 0, 1),
		Vertex(0, 0, 0).SetTexCoord(1, 0, 0).SetNormal(0, 0, 1),
	};

	m_renderWindow->UpdateVertices(0, 4, vertices);

//	m_GUICamera->SetOrthographicProjection(0, (float)width, (float)height, 0, -1, 1);

	delete m_depthBuffer;
	delete m_velocityBuffer;
	delete m_backgroundBuffer;
	delete m_lightBuffer;
	delete m_normalBuffer;
	delete m_positionBuffer;

	m_positionBuffer = new Texture2D(m_width, m_height, GL_RGBA32F, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_normalBuffer = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_lightBuffer = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_backgroundBuffer = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_velocityBuffer = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_depthBuffer = new Texture2D(m_width, m_height, GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_NEAREST, GL_CLAMP_TO_EDGE);

	delete m_geometryFramebuffer;

	m_geometryFramebuffer = new Framebuffer;
	m_geometryFramebuffer->AttachTexture2D(m_positionBuffer, Attachment::Color0);
	m_geometryFramebuffer->AttachTexture2D(m_normalBuffer, Attachment::Color1);
	m_geometryFramebuffer->AttachTexture2D(m_lightBuffer, Attachment::Color2);
	m_geometryFramebuffer->AttachTexture2D(m_backgroundBuffer, Attachment::Color3);
	m_geometryFramebuffer->AttachTexture2D(m_velocityBuffer, Attachment::Color4);
	m_geometryFramebuffer->AttachTexture2D(m_depthBuffer, Attachment::Depth);
	m_geometryFramebuffer->Pack();

	delete m_compositeBuffer;

	m_compositeBuffer = new Texture2D(m_width, m_height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);

	delete m_compositeFramebuffer;

	m_compositeFramebuffer = new Framebuffer;
	m_compositeFramebuffer->AttachTexture2D(m_compositeBuffer, Attachment::Color0);
	m_compositeFramebuffer->Pack();
}

void Enco3D::Rendering::RenderingEngine::Render(Enco3D::Core::GameObject *gameObject)
{
	for (int i = 0; i < MAX_CAMERAS; i++)
	{
		if (m_cameras[i] == nullptr)
			continue;

		RenderCamera(gameObject, m_cameras[i]);
	}

	// GUI Rendering

	gameObject->RenderGUI(m_GUICamera, m_textureShader);
	glEnable(GL_DEPTH_TEST);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		cerr << "[GL_ERROR] GL reported an error with code: " << error << endl;
}

void Enco3D::Rendering::RenderingEngine::RenderCamera(Enco3D::Core::GameObject *gameObject, Enco3D::Component::Camera *camera)
{
	//////////////////////////////////////////////////////////////////////////////
	////////////////////////// RENDER INTO FRAMEBUFFER ///////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	BindFramebuffer(m_geometryFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Light Rendering

	gameObject->Render(camera, m_geometryBufferShader);

	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);

/*	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		gameObject->Render(m_mainCamera, m_lights[i]->GetShader());
	}*/

	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Skybox Rendering

	if (m_skybox != nullptr)
	{
		glDisable(GL_DEPTH_TEST);
		m_skybox->Render(camera);
		glEnable(GL_DEPTH_TEST);
	}

	BindFramebuffer(nullptr);

	//////////////////////////////////////////////////////////////////////////////
	////////////////////////////// POST PROCESSING ///////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	std::vector<Component::IPostProcessEffect*> postProcessEffects;

	glDisable(GL_DEPTH_TEST);

	// Post Processing

	m_postProcessWorldViewProjectionMatrix.SetOrthographicProjection((float)m_width, 0, 0, (float)m_height, -1, 1);
	m_postProcessTexelSize.Set(1.0f / (float)m_width, 1.0f / (float)m_height);

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	BindFramebuffer(m_compositeFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_compositeShader->Bind();
	m_compositeShader->SetUniformMatrix4x4f("matrix_worldViewProjectionMatrix", m_postProcessWorldViewProjectionMatrix);

	m_backgroundBuffer->Bind(TextureSampler::Sampler1); m_compositeShader->SetUniformInt("gbuffer_backgroundTexture", TextureSampler::Sampler1);
	m_lightBuffer->Bind(TextureSampler::Sampler0);      m_compositeShader->SetUniformInt("gbuffer_lightTexture", TextureSampler::Sampler0);

	m_renderWindow->Render();
	BindFramebuffer(nullptr);

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	for (unsigned int i = 0; i < postProcessEffects.size(); i++)
		postProcessEffects[i]->PostProcess(camera);

	glClear(GL_COLOR_BUFFER_BIT);

	m_finalShader->Bind();
	m_finalShader->SetUniformMatrix4x4f("matrix_worldViewProjectionMatrix", m_postProcessWorldViewProjectionMatrix);

	for (unsigned int i = 0; i < postProcessEffects.size(); i++)
	{
		int slot = (int)postProcessEffects[i]->GetGeneratedImageSlot();
		postProcessEffects[i]->GetFinalBuffer()->Bind(10 + slot);
		m_finalShader->SetUniformInt("generatedImage_slot" + std::to_string(10 + slot), 10 + slot);
	}

	//
	m_compositeBuffer->Bind(TextureSampler::Sampler8);  m_finalShader->SetUniformInt("postProcess_compositeTexture", TextureSampler::Sampler8);
	//
	//
	m_depthBuffer->Bind(TextureSampler::Sampler5);      m_finalShader->SetUniformInt("gbuffer_depthTexture", TextureSampler::Sampler5);
	m_velocityBuffer->Bind(TextureSampler::Sampler4);   m_finalShader->SetUniformInt("gbuffer_velocityTexture", TextureSampler::Sampler4);
	m_backgroundBuffer->Bind(TextureSampler::Sampler3); m_finalShader->SetUniformInt("gbuffer_backgroundTexture", TextureSampler::Sampler3);
	m_lightBuffer->Bind(TextureSampler::Sampler2);      m_finalShader->SetUniformInt("gbuffer_lightTexture", TextureSampler::Sampler2);
	m_normalBuffer->Bind(TextureSampler::Sampler1);     m_finalShader->SetUniformInt("gbuffer_normalTexture", TextureSampler::Sampler1);
	m_positionBuffer->Bind(TextureSampler::Sampler0);   m_finalShader->SetUniformInt("gbuffer_positionTexture", TextureSampler::Sampler0);

	m_finalShader->SetUniformVector2f("postProcess_texelSize", m_postProcessTexelSize);

	m_finalShader->SetUniformFloat("camera_tanHalfFov", camera->GetTanHalfFov());
	m_finalShader->SetUniformFloat("camera_aspectRatio", camera->GetAspectRatio());
	m_finalShader->SetUniformFloat("camera_zNearClippingPlane", camera->GetZNearClippingPlane());
	m_finalShader->SetUniformFloat("camera_zFarClippingPlane", camera->GetZFarClippingPlane());

	m_finalShader->SetUniformFloat("velocityScale", 1.0f);

	m_renderWindow->Render();
}

void Enco3D::Rendering::RenderingEngine::InitializePostProcessEffect(Component::IPostProcessEffect *effect)
{
	effect->SetPositionBuffer(m_positionBuffer);
	effect->SetNormalBuffer(m_normalBuffer);
	effect->SetLightBuffer(m_lightBuffer);
	effect->SetBackgroundBuffer(m_backgroundBuffer);
	effect->SetVelocityBuffer(m_velocityBuffer);
	effect->SetDepthBuffer(m_depthBuffer);
	effect->SetCompositeBuffer(m_compositeBuffer);
}

Enco3D::Component::Camera *Enco3D::Rendering::RenderingEngine::CreatePerspectiveCamera(float fovInRadians, float zNear, float zFar)
{
	float aspectRatio = (float)m_width / (float)m_height;
	return new Component::Camera(fovInRadians, aspectRatio, zNear, zFar);
}

Enco3D::Component::Camera *Enco3D::Rendering::RenderingEngine::CreateOrthographicCamera(float zNear, float zFar)
{
	return new Component::Camera(-1.0f, 1.0f, -1.0f, 1.0f, zNear, zFar);
}