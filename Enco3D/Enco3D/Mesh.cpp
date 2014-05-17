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

	buildBuffers(vertices, vertexCount, indices, vertexCount);
}

Enco3D::Rendering::Mesh::Mesh(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount)
{
	buildBuffers(vertices, vertexCount, indices, indexCount);
}

Enco3D::Rendering::Mesh::~Mesh()
{
}

void Enco3D::Rendering::Mesh::buildBuffers(Vertex *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount)
{
	m_resource = new MeshResource(vertices, vertexCount, indices, indexCount);
}

void Enco3D::Rendering::Mesh::render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_resource->getVBO());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float) * 6));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_resource->getIBO());
	glDrawElements(GL_TRIANGLES, m_resource->getIndexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

void Enco3D::Rendering::Mesh::updateVertices(unsigned int offsetInVertices, unsigned int sizeInVertices, Vertex *newVertexData)
{
	unsigned int offsetInBytes = sizeof(Vertex)* offsetInVertices;
	unsigned int sizeInBytes = sizeof(Vertex)*sizeInVertices;

	glBindBuffer(GL_ARRAY_BUFFER, m_resource->getVBO());
	glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)offsetInBytes, (GLsizeiptr)sizeInBytes, (const GLvoid*)newVertexData);

	m_resource->updateVertices(offsetInVertices, sizeInVertices, newVertexData);
}

void Enco3D::Rendering::Mesh::renderErrorMesh(Rendering::Shader *shader, Core::Transform *transform, const Component::Camera *camera, Rendering::RenderingEngine *renderingEngine)
{
	static bool initializedMeshAndMaterial = false;
	static Mesh errorMesh;
	static Material errorMaterial;

	if (!initializedMeshAndMaterial)
	{
		initializedMeshAndMaterial = true;

		Vertex vertices[8] = {
			Vertex(-1, -1, 0).setTexCoord(1, 1, 0).setNormal(0, 0, +1),
			Vertex(+1, -1, 0).setTexCoord(0, 1, 0).setNormal(0, 0, +1),
			Vertex(+1, +1, 0).setTexCoord(0, 0, 0).setNormal(0, 0, +1),
			Vertex(-1, +1, 0).setTexCoord(1, 0, 0).setNormal(0, 0, +1),

			Vertex(+1, -1, 0).setTexCoord(1, 1, 0).setNormal(0, 0, -1),
			Vertex(-1, -1, 0).setTexCoord(0, 1, 0).setNormal(0, 0, -1),
			Vertex(-1, +1, 0).setTexCoord(0, 0, 0).setNormal(0, 0, -1),
			Vertex(+1, +1, 0).setTexCoord(1, 0, 0).setNormal(0, 0, -1),
		};

		unsigned int indices[12] = {
			0, 1, 2, 0, 2, 3,
			4, 5, 6, 4, 6, 7,
		};

		errorMesh = Mesh(vertices, 8, indices, 12);

		errorMaterial.addTexture2D("diffuseTexture", new Texture2D("texture/error.png", TextureFilter::Linear));
		errorMaterial.addVector3f("diffuseColor", Core::Color3Template::White);
		errorMaterial.addFloat("specularIntensity", 0.0f);
		errorMaterial.addFloat("specularExponent", 1.0f);
	}

	Core::Transform billboardTransform;
	billboardTransform.setTranslation(transform->getTranslation());
	billboardTransform.setScaling(transform->getScaling());
	billboardTransform.setBillboardEnabled(true);
	billboardTransform.setBillboardCamera((Component::Camera*)camera);

	billboardTransform.update();

	shader->bind();
	shader->updateUniforms(&billboardTransform, camera, renderingEngine, &errorMaterial);

	errorMesh.render();
}