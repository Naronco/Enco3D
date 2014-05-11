#include "GUIText.h"

Enco3D::Component::GUIText::GUIText()
{
}

Enco3D::Component::GUIText::GUIText(const std::string &text, Rendering::Font *font)
{
	m_font = font;
	m_text = text;

	m_color.Set(1, 1, 1);

	m_material.AddTexture2D("diffuseTexture", m_font->GetTexture());
	m_material.AddVector3f("diffuseColor", m_color);
}

Enco3D::Component::GUIText::GUIText(const std::string &text, const Core::Vector3f &color, Rendering::Font *font)
{
	m_font = font;
	m_text = text;

	m_material.AddTexture2D("diffuseTexture", m_font->GetTexture());
	m_material.AddVector3f("diffuseColor", m_color);
}

Enco3D::Component::GUIText::~GUIText()
{
	if (m_mesh)
	{
		delete m_mesh;
		m_mesh = nullptr;
	}
}

void Enco3D::Component::GUIText::InitRendering()
{
	UpdateMesh();
}

void Enco3D::Component::GUIText::RenderGUI(const Component::Camera *camera, Rendering::Shader *shader)
{
	shader->Bind();
	shader->UpdateUniforms(GetTransform(), camera, GetRenderingEngine(), &m_material);

	m_mesh->Render();
}

void Enco3D::Component::GUIText::UpdateMesh()
{
	unsigned int vertexCount = m_text.size() * 4;
	unsigned int indexCount = m_text.size() * 6;

	Rendering::Vertex *vertices = new Rendering::Vertex[vertexCount];

	unsigned int vertexIndex = 0;

	float fontScaling = __defaultFontSize / (float)m_font->GetFontSize();

	float cursorPosX = 0.0f;
	float cursorPosY = 0.0f;

	for (unsigned int i = 0; i < m_text.size(); i++)
	{
		if (m_text[i] == '\n')
		{
			cursorPosY += (float)__defaultFontSize;
			cursorPosX = 0.0f;
			continue;
		}

		Rendering::CharacterData charaData = m_font->GetCharacterData((unsigned int)m_text[i]);

		float w = fontScaling * charaData.width;
		float h = fontScaling * charaData.height;
		float offsX = fontScaling * charaData.offsX;
		float offsY = fontScaling * charaData.offsY;

		vertices[vertexIndex + 0].SetPosition(w + cursorPosX + offsX, cursorPosY + offsY, 0);
		vertices[vertexIndex + 0].SetTexCoord(charaData.endU, charaData.startV, 0);

		vertices[vertexIndex + 1].SetPosition(w + cursorPosX + offsX, h + cursorPosY + offsY, 0);
		vertices[vertexIndex + 1].SetTexCoord(charaData.endU, charaData.endV, 0);

		vertices[vertexIndex + 2].SetPosition(cursorPosX + offsX, h + cursorPosY + offsY, 0);
		vertices[vertexIndex + 2].SetTexCoord(charaData.startU, charaData.endV, 0);

		vertices[vertexIndex + 3].SetPosition(cursorPosX + offsX, cursorPosY + offsY, 0);
		vertices[vertexIndex + 3].SetTexCoord(charaData.startU, charaData.startV, 0);

		vertexIndex += 4;
		cursorPosX += fontScaling * charaData.advanceX;
	}

	unsigned int *indices = new unsigned int[indexCount];

	unsigned int indexIndex = 0;
	vertexIndex = 0;

	for (unsigned int i = 0; i < m_text.size(); i++)
	{
		indices[indexIndex + 0] = vertexIndex + 0;
		indices[indexIndex + 1] = vertexIndex + 1;
		indices[indexIndex + 2] = vertexIndex + 2;
		indices[indexIndex + 3] = vertexIndex + 0;
		indices[indexIndex + 4] = vertexIndex + 2;
		indices[indexIndex + 5] = vertexIndex + 3;

		indexIndex += 6;
		vertexIndex += 4;
	}

	if (m_mesh)
		delete m_mesh;

	m_mesh = new Rendering::Mesh(vertices, vertexCount, indices, indexCount);

	delete[] vertices;
	delete[] indices;
}