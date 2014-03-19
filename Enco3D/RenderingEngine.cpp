#include "RenderingEngine.h"

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

Matrix4x4f RenderingEngine::GetProjectedMatrix(const Matrix4x4f &worldMatrix)
{
	return m_mainCamera->GetViewProjection() * worldMatrix;
}