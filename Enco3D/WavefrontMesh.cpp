#include "WavefrontMesh.h"

Enco3D::Rendering::WavefrontMesh::WavefrontMesh()
{
}

Enco3D::Rendering::WavefrontMesh::WavefrontMesh(const string &filename)
{
	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate /*| aiProcess_GenSmoothNormals */| aiProcess_FlipUVs);

	if (scene)
	{
		cout << "Successfully loaded OBJ model " << filename << endl;
		InitFromScene(scene, filename);
	}
	else
	{
		cerr << "[ERROR] Failed to load OBJ model " << filename << endl;
	}
}

Enco3D::Rendering::WavefrontMesh::~WavefrontMesh()
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		if (m_meshes[i])
		{
			delete m_meshes[i];
			m_meshes[i] = nullptr;
		}
	}

	for (unsigned int i = 0; i < m_materials.size(); i++)
	{
		if (m_materials[i])
		{
			delete m_materials[i];
			m_materials[i] = nullptr;
		}
	}
}

void Enco3D::Rendering::WavefrontMesh::Render(const Camera *camera, Shader *shader)
{
	Matrix4x4f worldMatrix = GetTransform()->GetTransformation();
	Matrix4x4f projectedMatrix = GetRenderingEngine()->GetViewProjectedMatrix(camera, worldMatrix);

	shader->Bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		shader->UpdateUniforms(worldMatrix, projectedMatrix, *m_materials[m_meshes[i]->GetMaterialIndex()]);

		glBindBuffer(GL_ARRAY_BUFFER, m_meshes[i]->GetVBO());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float)* 3));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(float)* 6));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshes[i]->GetIBO());
		glDrawElements(GL_TRIANGLES, m_meshes[i]->GetIndexCount(), GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

bool Enco3D::Rendering::WavefrontMesh::InitFromScene(const aiScene *scene, const string &filename)
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

void Enco3D::Rendering::WavefrontMesh::InitMesh(unsigned int index, const aiMesh *mesh)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vector3f position = Vector3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		Vector3f texCoord = mesh->HasTextureCoords(0) ? Vector3f(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, mesh->mTextureCoords[0][i].z) : Enco3D::Core::Vector3Template::Zero;
		Vector3f normal = Vector3f(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		vertices.push_back(Vertex(position.x, position.y, position.z, texCoord.x, texCoord.y, texCoord.z, normal.x, normal.y, normal.z));
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace &face = mesh->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	Vertex *arrVertices = new Vertex[vertices.size()];
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		arrVertices[i] = vertices[i];
	}

	unsigned int *arrIndices = new unsigned int[indices.size()];
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		arrIndices[i] = indices[i];
	}

	m_meshes[index] = new MeshResource(arrVertices, vertices.size(), arrIndices, indices.size());
	m_meshes[index]->SetMaterialIndex(mesh->mMaterialIndex);

	delete arrVertices;
	delete arrIndices;
}

bool Enco3D::Rendering::WavefrontMesh::InitMaterials(const aiScene *scene, const string &filename)
{
	for (unsigned int i = 0; i < scene->mNumMaterials; i++)
	{
		const aiMaterial *material = scene->mMaterials[i];

		Material *meshMaterial = new Material;

/*		aiColor3D diffuseColor;
		if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS)
		{
			meshMaterial->AddVector3f("diffuse", Vector3f(diffuseColor.r, diffuseColor.g, diffuseColor.b));
		}

		aiColor3D specularColor;
		if (material->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == AI_SUCCESS)
		{
			meshMaterial->AddFloat("specularIntensity", (specularColor.r + specularColor.g + specularColor.b) / 3.0f);
		}*/

		meshMaterial->AddVector3f("diffuse", Vector3f(1, 1, 1));
		meshMaterial->AddFloat("specularIntensity", 0.0f);
		meshMaterial->AddFloat("specularExponent", 0.0f);
		
		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS)
			{
				meshMaterial->AddTexture("diffuse", new Texture(string("models/") + string(path.data)));
			}
		}

		m_materials[i] = meshMaterial;
	}

	return true;
}