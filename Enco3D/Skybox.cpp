#include "Skybox.h"

Enco3D::Rendering::Skybox::Skybox()
{
}

Enco3D::Rendering::Skybox::Skybox(Texture *texture)
{
	m_material = new Material;

	m_material->AddTexture("diffuse", texture);
	m_material->AddVector3f("diffuse", Vector3f(1, 1, 1));

	m_textureShader = TextureShader::GetInstance();

	Vertex vertices[24] =
	{
		Vertex(-1, -1, -1).SetTexCoord(0.25f, 0.75f).SetNormal(+0, -1, +0),
		Vertex(+1, -1, -1).SetTexCoord(0.50f, 0.75f).SetNormal(+0, -1, +0),
		Vertex(+1, -1, +1).SetTexCoord(0.50f, 0.50f).SetNormal(+0, -1, +0),
		Vertex(-1, -1, +1).SetTexCoord(0.25f, 0.50f).SetNormal(+0, -1, +0),

		Vertex(+1, +1, +1).SetTexCoord(0.50f, 0.25f).SetNormal(+0, +1, +0),
		Vertex(-1, +1, +1).SetTexCoord(0.25f, 0.25f).SetNormal(+0, +1, +0),
		Vertex(-1, +1, -1).SetTexCoord(0.25f, 0.00f).SetNormal(+0, +1, +0),
		Vertex(+1, +1, -1).SetTexCoord(0.50f, 0.00f).SetNormal(+0, +1, +0),

		Vertex(-1, -1, +1).SetTexCoord(0.25f, 0.50f).SetNormal(+0, +0, -1),
		Vertex(+1, -1, +1).SetTexCoord(0.50f, 0.50f).SetNormal(+0, +0, -1),
		Vertex(+1, +1, +1).SetTexCoord(0.50f, 0.25f).SetNormal(+0, +0, -1),
		Vertex(-1, +1, +1).SetTexCoord(0.25f, 0.25f).SetNormal(+0, +0, -1),

		Vertex(+1, +1, -1).SetTexCoord(0.75f, 0.25f).SetNormal(+0, +0, +1),
		Vertex(-1, +1, -1).SetTexCoord(1.00f, 0.25f).SetNormal(+0, +0, +1),
		Vertex(-1, -1, -1).SetTexCoord(1.00f, 0.50f).SetNormal(+0, +0, +1),
		Vertex(+1, -1, -1).SetTexCoord(0.75f, 0.50f).SetNormal(+0, +0, +1),

		Vertex(-1, -1, -1).SetTexCoord(0.00f, 0.50f).SetNormal(-1, +0, +0),
		Vertex(-1, +1, -1).SetTexCoord(0.00f, 0.25f).SetNormal(-1, +0, +0),
		Vertex(-1, +1, +1).SetTexCoord(0.25f, 0.25f).SetNormal(-1, +0, +0),
		Vertex(-1, -1, +1).SetTexCoord(0.25f, 0.50f).SetNormal(-1, +0, +0),

		Vertex(+1, -1, -1).SetTexCoord(0.75f, 0.50f).SetNormal(+1, +0, +0),
		Vertex(+1, +1, -1).SetTexCoord(0.75f, 0.25f).SetNormal(+1, +0, +0),
		Vertex(+1, +1, +1).SetTexCoord(0.50f, 0.25f).SetNormal(+1, +0, +0),
		Vertex(+1, -1, +1).SetTexCoord(0.50f, 0.50f).SetNormal(+1, +0, +0),
	};

	unsigned int indices[36] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23,
	};

	m_mesh = new Mesh(vertices, 24, indices, 36);
}

Enco3D::Rendering::Skybox::~Skybox()
{
	if (m_material)
	{
		delete m_material;
		m_material = nullptr;
	}

	if (m_mesh)
	{
		delete m_mesh;
		m_mesh = nullptr;
	}
}

void Enco3D::Rendering::Skybox::InitRendering()
{
	GetRenderingEngine()->SetSkybox(this);
}

void Enco3D::Rendering::Skybox::Render(const Camera *camera)
{
	Matrix4x4f worldMatrix;

	Vector3f translation = camera->GetTransform()->GetTranslation();
	worldMatrix.Translate(translation.x, translation.y, translation.z);

	Matrix4x4f projectedMatrix = GetRenderingEngine()->GetViewProjectedMatrix(camera, worldMatrix);

	m_textureShader->Bind();
	m_textureShader->UpdateUniforms(worldMatrix, projectedMatrix, *m_material);

	m_mesh->Render();
}