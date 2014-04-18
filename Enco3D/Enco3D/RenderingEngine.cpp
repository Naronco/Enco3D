#include "RenderingEngine.h"

#include "GameObject.h"

#include "Camera.h"
#include "ILight.h"
#include "Skybox.h"
#include "ShaderPool.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

Enco3D::Rendering::RenderingEngine::RenderingEngine()
{
}

Enco3D::Rendering::RenderingEngine::RenderingEngine(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;

	m_globalAmbientColor.Set(0.1f, 0.1f, 0.1f);
	m_gbuffer = new GBuffer(width, height);
	m_GUICamera = new Camera;

	m_GUICamera->SetName("__STD_guicamera");
	m_GUICamera->SetOrthographicProjection(0, (float)width, (float)height, 0, -1, 1);

	m_textureShader                 = ShaderPool::GetInstance()->GetShader("shaders/texture", ShaderType::VertexShader | ShaderType::FragmentShader);
	m_forwardAmbientShader          = ShaderPool::GetInstance()->GetShader("shaders/forwardAmbient", ShaderType::VertexShader | ShaderType::FragmentShader);

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);

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
		0, 1, 2,
		0, 2, 3,
	};

	m_renderWindow = new Mesh(vertices, 4, indices, 6);
}

#define __safedelete(x) { if(x){delete x;x=nullptr;} }

Enco3D::Rendering::RenderingEngine::~RenderingEngine()
{
	__safedelete(m_forwardAmbientShader);
	__safedelete(m_textureShader);

	__safedelete(m_gbuffer);
	
	__safedelete(m_GUICamera);
	__safedelete(m_mainCamera);

	for (unsigned int i = 0; i < m_lights.size(); i++) { __safedelete(m_lights[i]); }
}

void Enco3D::Rendering::RenderingEngine::Render(Enco3D::Core::GameObject *gameObject)
{
/*	glBindFramebuffer(GL_FRAMEBUFFER, m_gbuffer->GetFBO());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gameObject->Render(m_mainCamera, TextureShader::GetInstance());
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	Matrix4x4f postProcessWorldMatrix;
	Matrix4x4f postProcessProjectedMatrix;

	postProcessProjectedMatrix.SetOrthographicProjection(0, (float)m_width, (float)m_height, 0, -1, 1);

	PostProcessShader::GetInstance()->SetGBuffer(m_gbuffer);
	PostProcessShader::GetInstance()->Bind();
	PostProcessShader::GetInstance()->UpdateUniforms(postProcessWorldMatrix, postProcessProjectedMatrix, m_renderWindowMaterial);

	m_renderWindow->Render();*/
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Skybox Render

	if (m_skybox != nullptr)
	{
		glDepthMask(GL_FALSE);
		m_skybox->Render(m_mainCamera);
		glDepthMask(GL_TRUE);
	}

	// Light Rendering

	gameObject->Render(m_mainCamera, m_forwardAmbientShader);

	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);

	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		gameObject->Render(m_mainCamera, m_lights[i]->GetShader());
	}

	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// GUI Rendering

	glDisable(GL_DEPTH_TEST);
	gameObject->RenderGUI(m_GUICamera, m_textureShader);
	glEnable(GL_DEPTH_TEST);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		cerr << "[GL_ERROR] GL reported an error with code: " << error << endl;
	}
}

Enco3D::Core::Matrix4x4f Enco3D::Rendering::RenderingEngine::GetProjectedMatrix(const Enco3D::Rendering::Camera *camera, const Enco3D::Core::Matrix4x4f &worldMatrix)
{
	return camera->GetProjection() * worldMatrix;
}

Enco3D::Core::Matrix4x4f Enco3D::Rendering::RenderingEngine::GetViewProjectedMatrix(const Enco3D::Rendering::Camera *camera, const Enco3D::Core::Matrix4x4f &worldMatrix)
{
	return camera->GetViewProjection() * worldMatrix;
}