#include "WavefrontMesh.h"

Enco3D::Component::WavefrontMesh::WavefrontMesh()
{
}

Enco3D::Component::WavefrontMesh::WavefrontMesh(const std::string &filename, Rendering::Material *material)
{
	m_material = material;

	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

	if (scene)
	{
		m_successfullyLoadedMesh = true;
		Core::DebugLogger::log("Successfully loaded OBJ model " + filename);
		initFromScene(scene, filename);
	}
	else
	{
		m_successfullyLoadedMesh = false;
		Core::DebugLogger::log("[ERROR] Failed to load OBJ model " + filename);
	}
}

Enco3D::Component::WavefrontMesh::~WavefrontMesh()
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		if (m_meshes[i])
			delete m_meshes[i];

	if (m_material)
		delete m_material;
}

void Enco3D::Component::WavefrontMesh::render(const Component::Camera *camera, Rendering::Shader *shader)
{
	if (m_successfullyLoadedMesh)
	{
		shader->bind();
		shader->updateUniforms(getTransform(), camera, getRenderingEngine(), *m_material);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		for (unsigned int i = 0; i < m_meshes.size(); i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_meshes[i]->getVBO());
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), 0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), (GLvoid *)(sizeof(float)* 3));
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), (GLvoid *)(sizeof(float)* 6));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshes[i]->getIBO());
			glDrawElements(GL_TRIANGLES, m_meshes[i]->getIndexCount(), GL_UNSIGNED_INT, 0);
		}

		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
	else
	{
		Rendering::Mesh::renderErrorMesh(shader, getTransform(), camera, getRenderingEngine());
	}
}

bool Enco3D::Component::WavefrontMesh::initFromScene(const aiScene *scene, const std::string &filename)
{
	m_meshes.resize(scene->mNumMeshes);
	
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		const aiMesh *mesh = scene->mMeshes[i];
		initMesh(i, mesh);
	}

	return true;
}

void Enco3D::Component::WavefrontMesh::initMesh(unsigned int index, const aiMesh *mesh)
{
	std::vector<Rendering::Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Core::Vector3f position = Core::Vector3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		Core::Vector3f texCoord = mesh->HasTextureCoords(0) ? Core::Vector3f(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, mesh->mTextureCoords[0][i].z) : Core::Vector3Template::Zero;
		Core::Vector3f normal = Core::Vector3f(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		vertices.push_back(Rendering::Vertex(position.x, position.y, position.z, texCoord.x, texCoord.y, texCoord.z, normal.x, normal.y, normal.z));
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace &face = mesh->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	Rendering::Vertex *arrVertices = new Rendering::Vertex[vertices.size()];
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		arrVertices[i] = vertices[i];
	}

	unsigned int *arrIndices = new unsigned int[indices.size()];
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		arrIndices[i] = indices[i];
	}

	m_meshes[index] = new Rendering::MeshResource(arrVertices, vertices.size(), arrIndices, indices.size());
	m_meshes[index]->setMaterialIndex(mesh->mMaterialIndex);

	delete arrVertices;
	delete arrIndices;
}