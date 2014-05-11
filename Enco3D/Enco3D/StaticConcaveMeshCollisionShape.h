#ifndef _ENCO3D_STATICCONCAVEMESHCOLLISIONSHAPE_H_
#define _ENCO3D_STATICCONCAVEMESHCOLLISIONSHAPE_H_

#include "ICollisionShape.h"
#include "Vector3.h"
#include "PhysicsHelper.h"
#include "Mesh.h"

#include <vector>

namespace Enco3D
{
	namespace Physics
	{
		class StaticConcaveMeshCollisionShape : public ICollisionShape
		{
		private:
			Rendering::Mesh *m_mesh{ nullptr };

		public:
			StaticConcaveMeshCollisionShape();
			StaticConcaveMeshCollisionShape(Rendering::Mesh *mesh);

			btCollisionShape *ToBulletPhysicsCollisionShape();

			inline void SetMesh(Rendering::Mesh *mesh) { m_mesh = mesh; }
			inline Rendering::Mesh *GetMesh() const { return m_mesh; }
		};
	}
}

#endif