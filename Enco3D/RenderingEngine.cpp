#include "RenderingEngine.h"
#include "GameObject.h"
#include "LightGlobalAmbientShader.h"
#include "Camera.h"
#include "Light.h"

RenderingEngine::RenderingEngine()
{
	m_mainCamera = new Camera;
	m_globalAmbientColor.Set(0.1f, 0.1f, 0.1f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);
}

RenderingEngine::~RenderingEngine()
{
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

void RenderingEngine::Render(GameObject *gameObject)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LightGlobalAmbientShader::GetInstance()->SetGlobalAmbientLight(m_globalAmbientColor);

	gameObject->Render(LightGlobalAmbientShader::GetInstance());

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);

	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_lights[i]->BindToShader(m_mainCamera->GetTransform()->GetTranslation());
		gameObject->Render(m_lights[i]->GetShader());
	}

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

Matrix4x4f RenderingEngine::GetProjectedMatrix(const Matrix4x4f &worldMatrix)
{
	return m_mainCamera->GetViewProjection() * worldMatrix;
}