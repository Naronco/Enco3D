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
			Mesh *m_mesh{ nullptr };
			bool m_convex{ true };

		public:
			MeshCollisionShape();
			MeshCollisionShape(Mesh *mesh, bool convex = true);

			btCollisionShape *ToBulletPhysicsCollisionShape();

			inline void SetMesh(Mesh *mesh) { m_mesh = mesh; }
			inline void SetConvex(bool convex) { m_convex = convex; }

			inline Mesh *GetMesh() const { return m_mesh; }
			inline bool IsConvex() const { return m_convex; }
		};
	}
}

#endif