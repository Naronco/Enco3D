#include "RenderingEngine.h"

#include "GameObject.h"

#include "LightGlobalAmbientShader.h"
#include "TextureShader.h"
#include "GeometryPassShader.h"
#include "PostProcessShader.h"

#include "Camera.h"
#include "Light.h"
#include "Skybox.h"

Enco3D::Rendering::RenderingEngine::RenderingEngine()
{
	m_globalAmbientColor.Set(0.1f, 0.1f, 0.1f);
	m_gbuffer = new GBuffer;
	m_GUICamera = new Camera;

	m_GUICamera->SetOrthographicProjection(-1, 1, 1, -1, -1, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);
}

Enco3D::Rendering::RenderingEngine::RenderingEngine(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;

	m_globalAmbientColor.Set(0.1f, 0.1f, 0.1f);
	m_gbuffer = new GBuffer(width, height);
	m_GUICamera = new Camera;

	m_GUICamera->SetOrthographicProjection(-1, 1, 1, -1, -1, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);

	Vertex vertices[4] =
	{
		Vertex(-1, -1,  0).SetTexCoord(0, 0, 0).SetNormal(0, 0, 1),
		Vertex(-1,  1,  0).SetTexCoord(0, 1, 0).SetNormal(0, 0, 1),
		Vertex( 1,  1,  0).SetTexCoord(1, 1, 0).SetNormal(0, 0, 1),
		Vertex( 1, -1,  0).SetTexCoord(1, 0, 0).SetNormal(0, 0, 1),
	};

	unsigned int indices[6] =
	{
		0, 1, 2,
		0, 2, 3,
	};

	m_renderWindow = new Mesh(vertices, 4, indices, 6);
}

Enco3D::Rendering::RenderingEngine::~RenderingEngine()
{
	if (m_gbuffer)
	{
		delete m_gbuffer;
		m_gbuffer = nullptr;
	}

	if (m_GUICamera)
	{
		delete m_GUICamera;
		m_GUICamera = nullptr;
	}

	if (m_mainCamera)
	{
		delete m_mainCamera;
		m_mainCamera = nullptr;
	}

	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
		if (m_lights[i])
		{
			delete m_lights[i];
			m_lights[i] = nullptr;
		}
	}
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

	postProcessProjectedMatrix.SetOrthographicProjection(-1, 1, 1, -1, -1, 1);

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

	LightGlobalAmbientShader::GetInstance()->SetGlobalAmbientLight(m_globalAmbientColor);

	gameObject->Render(m_mainCamera, LightGlobalAmbientShader::GetInstance());

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);

	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_lights[i]->BindToShader(m_mainCamera->GetTransform()->GetTranslation());
		gameObject->Render(m_mainCamera, m_lights[i]->GetShader());
	}

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	// GUI Rendering

	glDisable(GL_DEPTH_TEST);
	gameObject->RenderGUI(m_GUICamera, TextureShader::GetInstance());
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