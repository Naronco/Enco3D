#ifndef _ENCO3D_MESHCOLLISIONSHAPE_H_
#define _ENCO3D_MESHCOLLISIONSHAPE_H_

#include "ICollisionShape.h"
#include "Vector3.h"
#include "PhysicsHelper.h"
#include "Mesh.h"

#include <vector>

using namespace std;

namespace Enco3D
{
	namespace Physics
	{
		using namespace Core;
		using namespace Rendering;

		class MeshCollisionShape : public ICollisionShape
		{
		private:
			vector<Vector3f> m_points;

		public:
			MeshCollisionShape();
			MeshCollisionShape(const vector<Vector3f> &points);
			MeshCollisionShape(const Mesh *mesh);

			btCollisionShape *ToBulletPhysicsCollisionShape();

			inline void AddPoint(const Vector3f &point) { m_points.push_back(point); }

			inline vector<Vector3f> GetPoints() const { return m_points; }
		};
	}
}

#endif