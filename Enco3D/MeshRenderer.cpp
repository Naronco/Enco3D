#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::MeshRenderer(Mesh *mesh, Material *material)
{
	m_mesh = mesh;
	m_material = material;
}

void MeshRenderer::Render()
{
	Matrix4x4f worldMatrix = m_transform->GetTransformation();
	Matrix4x4f projectedMatrix = m_renderingEngine->GetProjectedMatrix(worldMatrix);

	LightGlobalAmbientShader::GetInstance()->SetGlobalAmbientLight(m_renderingEngine->GetGlobalAmbientColor());

	LightGlobalAmbientShader::GetInstance()->Bind();
	LightGlobalAmbientShader::GetInstance()->UpdateUniforms(worldMatrix, projectedMatrix, *m_material);
	m_mesh->Render();

	vector<BaseLight *> lights = m_renderingEngine->GetLights();

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);

	for (unsigned int i = 0; i < lights.size(); i++)
	{
		lights[i]->BindToShader(m_renderingEngine->GetMainCamera()->GetTranslation());

		lights[i]->shader->Bind();
		lights[i]->shader->UpdateUniforms(worldMatrix, projectedMatrix, *m_material);

		m_mesh->Render();
	}

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}