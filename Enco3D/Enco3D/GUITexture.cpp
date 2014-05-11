#include "GUITexture.h"
#include <iostream>
using namespace std;

Enco3D::Rendering::Mesh *Enco3D::Component::GUITexture::s_rectangleMesh = nullptr;
unsigned int Enco3D::Component::GUITexture::s_numReferences = 0;

Enco3D::Component::GUITexture::GUITexture()
{
	s_numReferences++;
}

Enco3D::Component::GUITexture::GUITexture(Enco3D::Rendering::Texture2D *texture)
{
	m_texture = texture;
	m_color.Set(1, 1, 1);

	m_material.AddTexture2D("diffuseTexture", m_texture);
	m_material.AddVector3f("diffuseColor", m_color);

	s_numReferences++;
}

Enco3D::Component::GUITexture::GUITexture(Enco3D::Rendering::Texture2D *texture, const Enco3D::Core::Vector3f &color)
{
	m_texture = texture;
	m_color.Set(color);

	m_material.AddTexture2D("diffuseTexture", m_texture);
	m_material.AddVector3f("diffuseColor", m_color);

	s_numReferences++;
}

Enco3D::Component::GUITexture::GUITexture(const string &filename)
{
	m_texture = new Rendering::Texture2D(filename);
	m_color.Set(1, 1, 1);

	m_material.AddTexture2D("diffuseTexture", m_texture);
	m_material.AddVector3f("diffuseColor", m_color);

	s_numReferences++;
}

Enco3D::Component::GUITexture::GUITexture(const string &filename, const Enco3D::Core::Vector3f &color)
{
	m_texture = new Rendering::Texture2D(filename);
	m_color.Set(color);

	m_material.AddTexture2D("diffuseTexture", m_texture);
	m_material.AddVector3f("diffuseColor", m_color);

	s_numReferences++;
}

void Enco3D::Component::GUITexture::ReleaseTexture()
{
	if (m_texture)
	{
		delete m_texture;
		m_texture = nullptr;
	}
}

void Enco3D::Component::GUITexture::RenderGUI(const Camera *camera, Enco3D::Rendering::Shader *shader)
{
	if (s_rectangleMesh == nullptr)
	{
		Rendering::Vertex vertices[4] =
		{
			Rendering::Vertex(+0.5f, -0.5f, 0).SetTexCoord(1, 0, 0).SetNormal(0, 0, 1),
			Rendering::Vertex(+0.5f, +0.5f, 0).SetTexCoord(1, 1, 0).SetNormal(0, 0, 1),
			Rendering::Vertex(-0.5f, +0.5f, 0).SetTexCoord(0, 1, 0).SetNormal(0, 0, 1),
			Rendering::Vertex(-0.5f, -0.5f, 0).SetTexCoord(0, 0, 0).SetNormal(0, 0, 1),
		};

		unsigned int indices[6] =
		{
			0, 1, 2,
			0, 2, 3,
		};

		s_rectangleMesh = new Rendering::Mesh(vertices, 4, indices, 6);
	}

	shader->Bind();
	shader->UpdateUniforms(GetTransform(), camera, GetRenderingEngine(), &m_material);

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