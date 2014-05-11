#include "WavefrontMaterialMesh.h"
#include "StaticConcaveMeshCollisionShape.h"

Enco3D::Component::WavefrontMaterialMesh::WavefrontMaterialMesh()
{
	m_staticConcaveMeshCollisionShape = nullptr;
}

Enco3D::Component::WavefrontMaterialMesh::WavefrontMaterialMesh(const std::string &filename)
{
	m_staticConcaveMeshCollisionShape = nullptr;

	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

	if (scene)
	{
		m_successfullyLoadedMesh = true;
		Core::DebugLogger::Log("Successfully loaded OBJ model " + filename);
		InitFromScene(scene, filename);
	}
	else
	{
		m_successfullyLoadedMesh = false;
		Core::DebugLogger::Log("[ERROR] Failed to load OBJ model " + filename);
	}
}

Enco3D::Component::WavefrontMaterialMesh::~WavefrontMaterialMesh()
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		if (m_meshes[i])
			delete m_meshes[i];
	
	for (unsigned int i = 0; i < m_materials.size(); i++)
		if (m_materials[i])
			delete m_materials[i];

	if (m_staticConcaveMeshCollisionShape)
		delete m_staticConcaveMeshCollisionShape;
}

void Enco3D::Component::WavefrontMaterialMesh::Render(const Component::Camera *camera, Rendering::Shader *shader)
{
	if (m_successfullyLoadedMesh)
	{
		shader->Bind();

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		for (unsigned int i = 0; i < m_meshes.size(); i++)
		{
			shader->UpdateUniforms(GetTransform(), camera, GetRenderingEngine(), m_materials[m_meshes[i]->GetMaterialIndex()]);

			glBindBuffer(GL_ARRAY_BUFFER, m_meshes[i]->GetVBO());
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), 0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), (GLvoid *)(sizeof(float)* 3));
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), (GLvoid *)(sizeof(float)* 6));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshes[i]->GetIBO());
			glDrawElements(GL_TRIANGLES, m_meshes[i]->GetIndexCount(), GL_UNSIGNED_INT, 0);
		}

		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
	else
	{
		Rendering::Mesh::RenderErrorMesh(shader, GetTransform(), camera, GetRenderingEngine());
	}
}

bool Enco3D::Component::WavefrontMaterialMesh::InitFromScene(const aiScene *scene, const std::string &filename)
{
	m_meshes.resize(scene->mNumMeshes);
	m_materials.resize(scene->mNumMaterials);

	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		const aiMesh *mesh = scene->mMeshes[i];
		InitMesh(i, mesh);
	}

	return InitMaterials(scene, filename);
}

void Enco3D::Component::WavefrontMaterialMesh::InitMesh(unsigned int index, const aiMesh *mesh)
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
		arrVertices[i] = vertices[i];

	unsigned int *arrIndices = new unsigned int[indices.size()];
	for (unsigned int i = 0; i < indices.size(); i++)
		arrIndices[i] = indices[i];

	m_meshes[index] = new Rendering::MeshResource(arrVertices, vertices.size(), arrIndices, indices.size());
	m_meshes[index]->SetMaterialIndex(mesh->mMaterialIndex);

	delete arrVertices;
	delete arrIndices;
}

bool Enco3D::Component::WavefrontMaterialMesh::InitMaterials(const aiScene *scene, const std::string &filename)
{
	for (unsigned int i = 0; i < scene->mNumMaterials; i++)
	{
		const aiMaterial *material = scene->mMaterials[i];

		Rendering::Material *meshMaterial = new Rendering::Material;

		aiColor3D diffuseColor;
		if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS)
			meshMaterial->AddVector3f("diffuseColor", Core::Vector3f(diffuseColor.r, diffuseColor.g, diffuseColor.b));
		else
			meshMaterial->AddVector3f("diffuseColor", Core::Vector3f(1, 1, 1));
		
		aiColor3D specularColor;
		if (material->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == AI_SUCCESS)
			meshMaterial->AddFloat("specularIntensity", (specularColor.r + specularColor.g + specularColor.b) / 3.0f);
		else
			meshMaterial->AddFloat("specularIntensity", 0.0f);
		
		float specularExponent;
		if (material->Get(AI_MATKEY_SHININESS, specularExponent) == AI_SUCCESS)
		{
			if (specularExponent == 0.0f)
			{
				meshMaterial->AddFloat("specularExponent", 1.0f);
				meshMaterial->SetFloat("specularIntensity", 0.0f);
			}
			else
				meshMaterial->AddFloat("specularExponent", specularExponent);
		}
		else
			meshMaterial->AddFloat("specularExponent", 1.0f);
		
		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS)
			{
				std::string basePath = filename;
				
				for (unsigned int i = basePath.length(); i >= 0; i--)
				{
					if (basePath[i] == '/')
					{
						basePath = basePath.substr(0, i + 1);
						break;
					}
				}

				meshMaterial->AddTexture2D("diffuseTexture", new Rendering::Texture2D(basePath + std::string(path.data), Rendering::TextureFilter::MipmapLinear));
			}
		}

		m_materials[i] = meshMaterial;
	}

	return true;
}

Enco3D::Physics::StaticConcaveMeshCollisionShape *Enco3D::Component::WavefrontMaterialMesh::GetStaticConcaveMeshCollisionShape() const
{
	unsigned int vertexCount = 0, indexCount = 0;
	for (unsigned int i = 0; i < m_meshes.size(); i++) {
		vertexCount += m_meshes[i]->GetVertexCount();
		indexCount += m_meshes[i]->GetIndexCount();
	}

	Rendering::Vertex *vertices = new Rendering::Vertex[vertexCount];
	unsigned int *indices = new unsigned int[indexCount];

	unsigned int vertexCursor = 0, indexCursor = 0;

	for (unsigned int i = 0; i < m_meshes.size(); i++) {
		unsigned int meshVertexCount = m_meshes[i]->GetVertexCount();
		unsigned int meshIndexCount = m_meshes[i]->GetIndexCount();

		for (unsigned int j = 0; j < meshVertexCount; j++)
			vertices[vertexCursor + j] = m_meshes[i]->GetVertices()[j];
		
		for (unsigned int j = 0; j < meshIndexCount; j++)
			indices[indexCursor + j] = m_meshes[i]->GetIndices()[j];
		
		vertexCursor += meshVertexCount;
		indexCursor += meshIndexCount;
	}

	m_staticConcaveMeshCollisionShape = new Rendering::Mesh(vertices, vertexCount, indices, indexCount);

	Physics::StaticConcaveMeshCollisionShape *result = new Physics::StaticConcaveMeshCollisionShape(m_staticConcaveMeshCollisionShape);

	delete[] indices;
	delete[] vertices;

	return result;
}