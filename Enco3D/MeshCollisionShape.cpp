#include "MeshCollisionShape.h"

Enco3D::Physics::MeshCollisionShape::MeshCollisionShape()
{
}

Enco3D::Physics::MeshCollisionShape::MeshCollisionShape(const vector<Enco3D::Core::Vector3f> &points)
{
	for (unsigned int i = 0; i < points.size(); i++)
	{
		m_points.push_back(points[i]);
	}
}

Enco3D::Physics::MeshCollisionShape::MeshCollisionShape(const Enco3D::Rendering::Mesh* mesh)
{
	for (unsigned int i = 0; i < mesh->GetIndexCount(); i++)
	{
		unsigned int index = mesh->GetIndices()[i];
		Vertex vertex = mesh->GetVertices()[index];

		m_points.push_back(Vector3f(vertex.x, vertex.y, vertex.z));
	}
}

btCollisionShape *Enco3D::Physics::MeshCollisionShape::ToBulletPhysicsCollisionShape()
{
	btConvexHullShape *result = new btConvexHullShape;

	for (unsigned int i = 0; i < m_points.size(); i++)
	{
		result->addPoint(PhysicsHelper::ToBulletPhysicsVec3(m_points[i]));
	}

	return result;
}