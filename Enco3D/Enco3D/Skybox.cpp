#include "Skybox.h"
#include "ShaderPool.h"

Enco3D::Component::Skybox::Skybox()
{
}

Enco3D::Component::Skybox::Skybox(const std::string &filename)
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

	m_skyboxTexture = new Rendering::TextureCubeMap(cubeMapFilenames, Rendering::TextureFilter::Nearest, Rendering::TextureWrap::Clamp);
	m_skyboxShader = Rendering::ShaderPool::getInstance()->getShader("shaders/skybox", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);

	Rendering::Vertex vertices[24] =
	{
		Rendering::Vertex(-1, -1, +1),
		Rendering::Vertex(+1, -1, +1),
		Rendering::Vertex(+1, -1, -1),
		Rendering::Vertex(-1, -1, -1),

		Rendering::Vertex(+1, +1, +1),
		Rendering::Vertex(-1, +1, +1),
		Rendering::Vertex(-1, +1, -1),
		Rendering::Vertex(+1, +1, -1),

		Rendering::Vertex(+1, -1, +1),
		Rendering::Vertex(-1, -1, +1),
		Rendering::Vertex(-1, +1, +1),
		Rendering::Vertex(+1, +1, +1),

		Rendering::Vertex(-1, -1, -1),
		Rendering::Vertex(+1, -1, -1),
		Rendering::Vertex(+1, +1, -1),
		Rendering::Vertex(-1, +1, -1),

		Rendering::Vertex(-1, +1, +1),
		Rendering::Vertex(-1, -1, +1),
		Rendering::Vertex(-1, -1, -1),
		Rendering::Vertex(-1, +1, -1),

		Rendering::Vertex(+1, +1, -1),
		Rendering::Vertex(+1, -1, -1),
		Rendering::Vertex(+1, -1, +1),
		Rendering::Vertex(+1, +1, +1),
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

	m_mesh = new Rendering::Mesh(vertices, 24, indices, 36);
}

Enco3D::Component::Skybox::~Skybox()
{
	if (m_skyboxTexture)
		delete m_skyboxTexture;
	if (m_mesh)
		delete m_mesh;
}

void Enco3D::Component::Skybox::initRendering()
{
	getRenderingEngine()->setSkybox(this);
}

void Enco3D::Component::Skybox::render(const Component::Camera *camera)
{
	m_skyboxShader->bind();
	m_skyboxShader->updateUniforms(getTransform(), camera, getRenderingEngine(), nullptr);
	
	m_mesh->render();
}