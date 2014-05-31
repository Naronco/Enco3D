#ifndef _ENCO3D_PLANE_H_
#define _ENCO3D_PLANE_H_

#include "Vector3.h"
#include "Vector4.h"
#include "BoundingSphere.h"

namespace Enco3D
{
	namespace Core
	{
		class Plane
		{
		public:
			Plane(Vector4f value);
			Plane(Vector3f normal, float d);
			Plane(Vector3f a, Vector3f b, Vector3f c);
			Plane(float a, float b, float c, float d);
			~Plane();

			inline float dot(Vector4f value) { return ((((m_normal.x * value.x) + (m_normal.y * value.y)) + (m_normal.z * value.z)) + (m_d * value.w)); }
			inline float dotCoordinate(Vector3f value) { return ((((m_normal.x * value.x) + (m_normal.y * value.y)) + (m_normal.z * value.z)) + m_d); }
			inline float dotNormal(Vector3f value) { return (((m_normal.x * value.x) + (m_normal.y * value.y)) + (m_normal.z * value.z)); }

			inline void normalize()
			{
				float factor;
				Vector3f normal = m_normal;
				m_normal = m_normal.normalize();
				factor = (float)sqrt(m_normal.x * m_normal.x + m_normal.y * m_normal.y + m_normal.z * m_normal.z) /
					(float)sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
				m_d *= factor;
			}

			inline bool operator == (const Plane &other) const
			{
				return other.m_d == m_d && other.m_normal == m_normal;
			}

			friend class BoundingSphere;

		protected:

			float m_d;
			Vector3f m_normal;
		};
	}
}
#endif