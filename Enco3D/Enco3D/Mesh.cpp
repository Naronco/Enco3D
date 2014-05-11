#include "Mesh.h"

#include "Material.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include "RenderingEngine.h"

Enco3D::Rendering::Mesh::Mesh()
{
}

Enco3D::Rendering::Mesh::Mesh(Vertex *vertices, unsigned int vertexCount)
{
	unsigned int *indices = new unsigned int[vertexCount];
	for (unsigned int i = 0; i < vertexCount; i++)
	{
		indices[i] = i;
	}

	BuildBuffers(vertices, vertexCount, indices, vertexCount);
}

Enco3D::Rendering::Mesh::Mesh(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount)
{
	BuildBuffers(vertices, vertexCount, indices, indexCount);
}

Enco3D::Rendering::Mesh::~Mesh()
{
}

void Enco3D::Rendering::Mesh::BuildBuffers(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount)
{
	m_resource = new MeshResource(vertices, vertexCount, indices, indexCount);
}

void Enco3D::Rendering::Mesh::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_resource->GetVBO());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 6));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_resource->GetIBO());
	glDrawElements(GL_TRIANGLES, m_resource->GetIndexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

void Enco3D::Rendering::Mesh::UpdateVertices(unsigned int offsetInVertices, unsigned int sizeInVertices, Vertex *newVertexData)
{
	unsigned int offsetInBytes = sizeof(Vertex)* offsetInVertices;
	unsigned int sizeInBytes = sizeof(Vertex)*sizeInVertices;

	glBindBuffer(GL_ARRAY_BUFFER, m_resource->GetVBO());
	glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)offsetInBytes, (GLsizeiptr)sizeInBytes, (const GLvoid*)newVertexData);

	m_resource->UpdateVertices(offsetInVertices, sizeInVertices, newVertexData);
}

void Enco3D::Rendering::Mesh::RenderErrorMesh(Rendering::Shader *shader, Core::Transform *transform, const Component::Camera *camera, Rendering::RenderingEngine *renderingEngine)
{
	static bool initializedMeshAndMaterial = false;
	static Mesh errorMesh;
	static Material errorMaterial;

	if (!initializedMeshAndMaterial)
	{
		initializedMeshAndMaterial = true;

		Vertex vertices[8] = {
			Vertex(-1, -1, 0).SetTexCoord(1, 1, 0).SetNormal(0, 0, +1),
			Vertex(+1, -1, 0).SetTexCoord(0, 1, 0).SetNormal(0, 0, +1),
			Vertex(+1, +1, 0).SetTexCoord(0, 0, 0).SetNormal(0, 0, +1),
			Vertex(-1, +1, 0).SetTexCoord(1, 0, 0).SetNormal(0, 0, +1),

			Vertex(+1, -1, 0).SetTexCoord(1, 1, 0).SetNormal(0, 0, -1),
			Vertex(-1, -1, 0).SetTexCoord(0, 1, 0).SetNormal(0, 0, -1),
			Vertex(-1, +1, 0).SetTexCoord(0, 0, 0).SetNormal(0, 0, -1),
			Vertex(+1, +1, 0).SetTexCoord(1, 0, 0).SetNormal(0, 0, -1),
		};

		unsigned int indices[12] = {
			0, 1, 2, 0, 2, 3,
			4, 5, 6, 4, 6, 7,
		};

		errorMesh = Mesh(vertices, 8, indices, 12);

		errorMaterial.AddTexture2D("diffuseTexture", new Texture2D("texture/error.png", TextureFilter::Linear));
		errorMaterial.AddVector3f("diffuseColor", Core::Color3Template::White);
		errorMaterial.AddFloat("specularIntensity", 0.0f);
		errorMaterial.AddFloat("specularExponent", 1.0f);
	}

	Core::Transform billboardTransform;
	billboardTransform.SetTranslation(transform->GetTranslation());
	billboardTransform.SetScaling(transform->GetScaling());
	billboardTransform.SetBillboardEnabled(true);
	billboardTransform.SetBillboardCamera((Component::Camera*)camera);

	billboardTransform.Update();

	shader->Bind();
	shader->UpdateUniforms(&billboardTransform, camera, renderingEngine, &errorMaterial);

	errorMesh.Render();
}