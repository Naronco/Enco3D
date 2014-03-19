#include "IndexedModel.h"

IndexedModel::IndexedModel()
{
}

void IndexedModel::CalcNormals()
{
	for (unsigned int i = 0; i < m_indices.size(); i += 3)
	{
		unsigned int i0 = m_indices[i];
		unsigned int i1 = m_indices[i + 1];
		unsigned int i2 = m_indices[i + 2];

		Vector3f v0 = m_positions[i1] - m_positions[i0];
		Vector3f v1 = m_positions[i2] - m_positions[i0];

		Vector3f normal = v0.Cross(v1).Normalize();

		m_normals[i0] += normal;
		m_normals[i1] += normal;
		m_normals[i2] += normal;
	}

	for (unsigned int i = 0; i < m_normals.size(); i++)
	{
		m_normals[i].Normalize();
	}
}