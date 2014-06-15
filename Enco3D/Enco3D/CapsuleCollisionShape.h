#ifndef _ENCO3D_CAPSULECOLLISIONSHAPE_H_
#define _ENCO3D_CAPSULECOLLISIONSHAPE_H_

#include "ICollisionShape.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Physics
	{
		class DLL_EXPORT CapsuleCollisionShape : public ICollisionShape
		{
		private:
			float m_radius, m_height;

		public:
			CapsuleCollisionShape();
			CapsuleCollisionShape(float radius, float height);

			btCollisionShape *toBulletPhysicsCollisionShape();

			inline void setRadius(float radius) { m_radius = radius; }
			inline void setHeight(float height) { m_height = height; }

			inline float getRadius() const { return m_radius; }
			inline float getHeight() const { return m_height; }
		};
	}
}

#endif