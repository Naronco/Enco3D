#ifndef _ENCO3D_CYLINDERCOLLISIONSHAPE_H_
#define _ENCO3D_CYLINDERCOLLISIONSHAPE_H_

#include "ICollisionShape.h"
#include "Vector3.h"
#include "PhysicsHelper.h"

namespace Enco3D
{
	namespace Physics
	{
		using namespace Core;

		class CylinderCollisionShape : public ICollisionShape
		{
		private:
			Vector3f m_halfSize;

		public:
			CylinderCollisionShape();
			CylinderCollisionShape(const Vector3f &size);

			btCollisionShape *ToBulletPhysicsCollisionShape();

			inline void SetHalfSize(const Vector3f &halfSize) { m_halfSize.Set(halfSize); }
			inline void SetSize(const Vector3f &size) { m_halfSize.Set(size * 0.5f); }

			inline Vector3f GetHalfSize() const { return m_halfSize; }
			inline Vector3f GetSize() const { return m_halfSize * 2.0f; }
		};
	}
}

#endif