#include "GUITexture.h"
#include <iostream>
using namespace std;

Enco3D::Rendering::Mesh *Enco3D::Component::GUITexture::s_rectangleMesh = nullptr;
unsigned int Enco3D::Component::GUITexture::s_numReferences = 0;

Enco3D::Component::GUITexture::GUITexture()
{
	s_numReferences++;
}

Enco3D::Component::GUITexture::GUITexture(Enco3D::Rendering::Texture *texture)
{
	m_texture = texture;
	m_material.AddTexture("diffuse", *m_texture);
	m_material.AddVector3f("diffuse", Vector3f(1, 1, 1));

	s_numReferences++;
}

Enco3D::Component::GUITexture::GUITexture(const string &filename)
{
	m_texture = new Texture(filename);
	m_material.AddTexture("diffuse", *m_texture);
	m_material.AddVector3f("diffuse", Vector3f(1, 1, 1));

	s_numReferences++;
}

void Enco3D::Component::GUITexture::ReleaseTexture()
{
	if (m_texture)
	{
		m_texture->Release();
		delete m_texture;
		m_texture = nullptr;
	}
}

void Enco3D::Component::GUITexture::RenderGUI(const Camera *camera, Enco3D::Rendering::Shader *shader)
{
	if (s_rectangleMesh == nullptr)
	{
		Vertex vertices[4] =
		{
			Vertex(-1, -1, 0).SetTexCoord(0, 0).SetNormal(0, 0, 1),
			Vertex(-1, 1, 0).SetTexCoord(0, 1).SetNormal(0, 0, 1),
			Vertex(1, 1, 0).SetTexCoord(1, 1).SetNormal(0, 0, 1),
			Vertex(1, -1, 0).SetTexCoord(1, 0).SetNormal(0, 0, 1),
		};

		unsigned int indices[6] =
		{
			0, 1, 2,
			0, 2, 3,
		};

		s_rectangleMesh = new Mesh(vertices, 4, indices, 6);
	}

	Matrix4x4f worldMatrix = GetTransform()->GetTransformation();
	Matrix4x4f projectedMatrix = GetRenderingEngine()->GetProjectedMatrix(camera, worldMatrix);

	shader->Bind();
	shader->UpdateUniforms(worldMatrix, projectedMatrix, m_material);

	s_rectangleMesh->Render();
}

void Enco3D::Component::GUITexture::Deinit()
{
	ReleaseTexture();

	s_numReferences--;
	if (s_numReferences <= 0 && s_rectangleMesh)
	{
		delete s_rectangleMesh;
		s_rectangleMesh = nullptr;
	}
}