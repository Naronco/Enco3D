#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::MeshRenderer(Mesh *mesh, Material *material)
{
	m_mesh = mesh;
	m_material = material;
}

void MeshRenderer::Render(Shader *shader)
{
	Matrix4x4f worldMatrix = GetTransform()->GetTransformation();
	Matrix4x4f projectedMatrix = GetRenderingEngine()->GetProjectedMatrix(worldMatrix);

/*	LightGlobalAmbientShader::GetInstance()->SetGlobalAmbientLight(GetRenderingEngine()->GetGlobalAmbientColor());

	LightGlobalAmbientShader::GetInstance()->Bind();
	LightGlobalAmbientShader::GetInstance()->UpdateUniforms(worldMatrix, projectedMatrix, *m_material);*/

	shader->Bind();
	shader->UpdateUniforms(worldMatrix, projectedMatrix, *m_material);
	m_mesh->Render();

/*	vector<BaseLight *> lights = GetRenderingEngine()->GetLights();

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);

	for (unsigned int i = 0; i < lights.size(); i++)
	{
		lights[i]->BindToShader(GetRenderingEngine()->GetMainCamera()->GetTranslation());

		lights[i]->shader->Bind();
		lights[i]->shader->UpdateUniforms(worldMatrix, projectedMatrix, *m_material);

		m_mesh->Render();
	}

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);*/
}