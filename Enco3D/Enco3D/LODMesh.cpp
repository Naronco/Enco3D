#include "LODMesh.h"

Enco3D::Component::LODMesh::LODMesh()
{
}

Enco3D::Component::LODMesh::LODMesh(const std::string& file, int count, Rendering::Material *material)
{
	for (int i = 0; i < count; i++)
	{
		m_meshes.push_back(new WavefrontMesh(file + std::string("@") + std::to_string(i) + std::string(".wavefront"), material));
	}
	m_maxMeshes = count;
}

Enco3D::Component::LODMesh::~LODMesh()
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		delete m_meshes[i];
	}
}

void Enco3D::Component::LODMesh::setup()
{
	if (!added)
	{
		for (unsigned int i = 0; i < m_meshes.size(); i++)
		{
			std::cout << i << std::endl;
			getGameObject()->addComponent(m_meshes[i]);
			m_meshes[i]->disable();
		}
		added = true;
	}
}

void Enco3D::Component::LODMesh::render(const Component::Camera *camera, Rendering::Shader *shader)
{
	if (added)
	{
		int n = min(m_maxMeshes - 1, m_maxMeshes - min(m_maxMeshes, ((int)camera->getTransform()->getTranslation().getSquaredDistance(getTransform()->getTranslation())) / (m_meshDiff * m_meshDiff) + 1));
		for (unsigned int i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i]->disable();
		}
		m_meshes[n]->enable();
	}
}