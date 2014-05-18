#include "StaticConcaveMeshCollisionShape.h"

Enco3D::Physics::StaticConcaveMeshCollisionShape::StaticConcaveMeshCollisionShape()
{
}

Enco3D::Physics::StaticConcaveMeshCollisionShape::StaticConcaveMeshCollisionShape(Enco3D::Rendering::Mesh *mesh)
{
	m_mesh = mesh;
}

btCollisionShape *Enco3D::Physics::StaticConcaveMeshCollisionShape::toBulletPhysicsCollisionShape()
{
	btTriangleMesh *triangleMesh = new btTriangleMesh;
	for (unsigned int i = 0; i < m_mesh->getIndexCount(); i += 3)
	{
		unsigned int index0 = m_mesh->getIndices()[i + 0];
		unsigned int index1 = m_mesh->getIndices()[i + 1];
		unsigned int index2 = m_mesh->getIndices()[i + 2];

		btVector3 vertex0(m_mesh->getVertices()[index0].x, m_mesh->getVertices()[index0].y, m_mesh->getVertices()[index0].z);
		btVector3 vertex1(m_mesh->getVertices()[index1].x, m_mesh->getVertices()[index1].y, m_mesh->getVertices()[index1].z);
		btVector3 vertex2(m_mesh->getVertices()[index2].x, m_mesh->getVertices()[index2].y, m_mesh->getVertices()[index2].z);

		triangleMesh->addTriangle(vertex0, vertex1, vertex2);
	}

	return new btBvhTriangleMeshShape(triangleMesh, true);
}