#include "Skybox.h"

Enco3D::Rendering::Skybox::Skybox()
{
}

Enco3D::Rendering::Skybox::Skybox(const string &filename)
{
	string cubeMapFilenames[6] =
	{
		filename + string("@x+.png"),
		filename + string("@x-.png"),
		filename + string("@y+.png"),
		filename + string("@y-.png"),
		filename + string("@z+.png"),
		filename + string("@z-.png"),
	};

	Texture *cubeMapTexture = new Texture(cubeMapFilenames, TextureFilter::Nearest, TextureWrap::Clamp);

	m_material = new Material;
	m_material->AddTexture("skybox", cubeMapTexture);

	m_skyboxShader = SkyboxShader::GetInstance();

	Vertex vertices[24] =
	{
		Vertex(-1, -1, +1),
		Vertex(+1, -1, +1),
		Vertex(+1, -1, -1),
		Vertex(-1, -1, -1),

		Vertex(+1, +1, +1),
		Vertex(-1, +1, +1),
		Vertex(-1, +1, -1),
		Vertex(+1, +1, -1),

		Vertex(+1, -1, +1),
		Vertex(-1, -1, +1),
		Vertex(-1, +1, +1),
		Vertex(+1, +1, +1),

		Vertex(-1, -1, -1),
		Vertex(+1, -1, -1),
		Vertex(+1, +1, -1),
		Vertex(-1, +1, -1),

		Vertex(-1, +1, +1),
		Vertex(-1, -1, +1),
		Vertex(-1, -1, -1),
		Vertex(-1, +1, -1),

		Vertex(+1, +1, -1),
		Vertex(+1, -1, -1),
		Vertex(+1, -1, +1),
		Vertex(+1, +1, +1),
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
	Matrix4x4f projectedMatrix = GetRenderingEngine()->GetViewProjectedMatrix(camera, worldMatrix);

	m_skyboxShader->SetEyePos(camera->GetTransform()->GetTranslation());

	m_skyboxShader->Bind();
	m_skyboxShader->UpdateUniforms(worldMatrix, projectedMatrix, *m_material);

	m_mesh->Render();
}