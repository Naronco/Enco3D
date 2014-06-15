#ifndef _ENCO3D_BOXCOLLISIONSHAPE_H_
#define _ENCO3D_BOXCOLLISIONSHAPE_H_

#include "ICollisionShape.h"
#include "Vector3.h"
#include "PhysicsHelper.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Physics
	{
		class DLL_EXPORT BoxCollisionShape : public ICollisionShape
		{
		private:
			Core::Vector3f m_halfSize;

		public:
			BoxCollisionShape();
			BoxCollisionShape(const Core::Vector3f &size);

			btCollisionShape *toBulletPhysicsCollisionShape();

			inline void setHalfSize(const Core::Vector3f &halfSize) { m_halfSize.set(halfSize); }
			inline void setSize(const Core::Vector3f &size) { m_halfSize.set(size * 0.5f); }

			inline Core::Vector3f getHalfSize() const { return m_halfSize; }
			inline Core::Vector3f getSize() const { return m_halfSize * 2.0f; }
		};
	}
}

#endif