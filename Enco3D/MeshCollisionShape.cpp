#include "MeshCollisionShape.h"

Enco3D::Physics::MeshCollisionShape::MeshCollisionShape()
{
}

Enco3D::Physics::MeshCollisionShape::MeshCollisionShape(Enco3D::Rendering::Mesh* mesh, bool convex)
{
	m_mesh = mesh;
	m_convex = convex;
}

btCollisionShape *Enco3D::Physics::MeshCollisionShape::ToBulletPhysicsCollisionShape()
{
/*	int numTriangles = (int)(m_mesh->GetIndexCount() / 3);
	int *indices = new int[m_mesh->GetIndexCount()];
	for (unsigned int i = 0; i < m_mesh->GetIndexCount(); i++)
	{
		indices[i] = (int)m_mesh->GetIndices()[i];
	}

	int indexStride = 3 * sizeof(int);
	
	int numVertices = (int)(m_mesh->GetVertexCount());
	float *vertices = new float[m_mesh->GetVertexCount() * 3];
	for (unsigned int i = 0; i < m_mesh->GetVertexCount(); i++)
	{
		vertices[(i * 3) + 0] = m_mesh->GetVertices()[i].x;
		vertices[(i * 3) + 1] = m_mesh->GetVertices()[i].y;
		vertices[(i * 3) + 2] = m_mesh->GetVertices()[i].z;
	}

	int vertexStride = 3 * sizeof(float);

	btTriangleIndexVertexArray *triangleIndexVertexArray = new btTriangleIndexVertexArray(numTriangles, indices, indexStride, numVertices, vertices, vertexStride);
	*/
	btTriangleMesh *triangleMesh = new btTriangleMesh;
	for (unsigned int i = 0; i < m_mesh->GetIndexCount(); i += 3)
	{
		unsigned int index0 = m_mesh->GetIndices()[i + 0];
		unsigned int index1 = m_mesh->GetIndices()[i + 1];
		unsigned int index2 = m_mesh->GetIndices()[i + 2];

		btVector3 vertex0(m_mesh->GetVertices()[index0].x, m_mesh->GetVertices()[index0].y, m_mesh->GetVertices()[index0].z);
		btVector3 vertex1(m_mesh->GetVertices()[index1].x, m_mesh->GetVertices()[index1].y, m_mesh->GetVertices()[index1].z);
		btVector3 vertex2(m_mesh->GetVertices()[index2].x, m_mesh->GetVertices()[index2].y, m_mesh->GetVertices()[index2].z);

		triangleMesh->addTriangle(vertex0, vertex1, vertex2);
	}

	if (m_convex)
	{
		return new btConvexTriangleMeshShape(triangleMesh, true);
	}
	else
	{
		return new btBvhTriangleMeshShape(triangleMesh, true);
	}
}