#include "GUIText.h"

Enco3D::Component::GUIText::GUIText()
{
}

Enco3D::Component::GUIText::GUIText(const string &text)
{
	m_font = FontDatabase::GetInstance()->GetFont("font/arial");
	m_text = text;

	m_color.Set(1, 1, 1);

	m_material.AddTexture("diffuse", m_font->GetTexture());
	m_material.AddVector3f("diffuse", m_color);
}

Enco3D::Component::GUIText::GUIText(const string &text, const Vector3f &color)
{
	m_text = text;

	m_material.AddTexture("diffuse", m_font->GetTexture());
	m_material.AddVector3f("diffuse", m_color);
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

void Enco3D::Component::GUIText::RenderGUI(const Camera *camera, Shader *shader)
{
	Matrix4x4f worldMatrix = GetTransform()->GetTransformation();
	Matrix4x4f projectedMatrix = GetRenderingEngine()->GetProjectedMatrix(camera, worldMatrix);

	shader->Bind();
	shader->UpdateUniforms(worldMatrix, projectedMatrix, m_material);

	m_mesh->Render();
}

void Enco3D::Component::GUIText::UpdateMesh()
{
	unsigned int vertexCount = m_text.size() * 4;
	unsigned int indexCount = m_text.size() * 6;

	Vertex *vertices = new Vertex[vertexCount];

	unsigned int vertexIndex = 0;

	float cursorPos_x = 0.0f;
	float cursorPos_y = 0.0f;

	for (unsigned int i = 0; i < m_text.size(); i++)
	{
		if (m_text[i] == '\n')
		{
			cursorPos_y += 24.0f;
			cursorPos_x = 0.0f;
			continue;
		}

		CharacterData charaData = m_font->GetCharacterData((unsigned int)m_text[i]);

		vertices[vertexIndex + 0].SetPosition(charaData.width + cursorPos_x + charaData.offsX, cursorPos_y + charaData.offsY, 0);
		vertices[vertexIndex + 0].SetTexCoord(charaData.end_u, charaData.start_v, 0);

		vertices[vertexIndex + 1].SetPosition(charaData.width + cursorPos_x + charaData.offsX, charaData.height + cursorPos_y + charaData.offsY, 0);
		vertices[vertexIndex + 1].SetTexCoord(charaData.end_u, charaData.end_v, 0);

		vertices[vertexIndex + 2].SetPosition(cursorPos_x + charaData.offsX, charaData.height + cursorPos_y + charaData.offsY, 0);
		vertices[vertexIndex + 2].SetTexCoord(charaData.start_u, charaData.end_v, 0);

		vertices[vertexIndex + 3].SetPosition(cursorPos_x + charaData.offsX, cursorPos_y + charaData.offsY, 0);
		vertices[vertexIndex + 3].SetTexCoord(charaData.start_u, charaData.start_v, 0);

		vertexIndex += 4;
		cursorPos_x += charaData.advanceX;
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
	{
		delete m_mesh;
	}

	m_mesh = new Mesh(vertices, vertexCount, indices, indexCount);

	delete[] vertices;
	delete[] indices;
}