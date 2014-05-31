#ifndef _ENCO3D_BOUNDINGBOX_H_
#define _ENCO3D_BOUNDINGBOX_H_

#include "BoundingSphere.h"
#include "Contains.h"
#include "Frustum.h"

namespace Enco3D
{
	namespace Core
	{
		class BoundingBox
		{
		public:
			BoundingBox(Vector3f min, Vector3f max) : m_min(min), m_max(max) { }
			~BoundingBox();

			inline Contains contains(const BoundingBox& box)
			{
				if (box.m_max.X < m_min.X
					|| box.m_min.X > m_max.X
					|| box.m_max.Y < m_min.Y
					|| box.m_min.Y > m_max.Y
					|| box.m_max.Z < m_min.Z
					|| box.m_min.Z > m_max.Z)
					return Contains::Exclude;

				if (box.m_min.X >= m_min.X
					&& box.m_max.X <= m_max.X
					&& box.m_min.Y >= m_min.Y
					&& box.m_max.Y <= m_max.Y
					&& box.m_min.Z >= m_min.Z
					&& box.m_max.Z <= m_max.Z)
					return Contains::Contain;

				return Contains::Intersect;
			}

			inline Contains contains(const Frustum& frustum)
			{
				int i;
				Contains contained;
				Vector3f* corners = frustum.GetCorners();

				for (i = 0; i < corners.Length; i++)
					if (contains(corners[i]) == Contains::Exclude)
						break;

				if (i == corners.Length)
					return Contains::Contain;

				if (i != 0)
					return Contains::Intersect;

				i++;
				for (; i < corners.Length; i++)
				{
					if (Contains(corners[i]) != Contains::Contain)
						return Contains::Intersect;
				}

				return Contains::Contain;
			}

			inline Contains contains(const BoundingSphere& sphere)
			{
				return sphere.contains(this);
			}

			inline Contains contains(const Vector3f& point)
			{
				if (point.x < m_min.x
					|| point.x > m_max.x
					|| point.Y < m_min.y
					|| point.y > m_max.y
					|| point.z < m_min.z
					|| point.z > m_max.z)
				{
					result = Contains::Exclude;
				}
				else if (point.x == m_min.x
					|| point.x == m_max.x
					|| point.y == m_min.y
					|| point.y == m_max.y
					|| point.z == m_min.z
					|| point.z == m_max.z)
					result = Contains::Intersect;
				else
					result = Contains::Contain;
			}

			inline Vector3f* getCorners() const
			{
				return
				{
					Vector3f(m_min.x, m_max.y, m_max.z),
					m_max,
					Vector3f(m_max.x, m_min.y, m_max.z),
					Vector3f(m_min.x, m_min.y, m_max.z),
					Vector3f(m_min.x, m_max.y, m_min.z),
					Vector3f(m_max.x, m_max.y, m_min.z),
					Vector3f(m_max.x, m_min.y, m_min.z),
					m_min
				};
			}

			friend class BoundingSphere;
		protected:

			Vector3f m_min;
			Vector3f m_max;
		};
	}
}
#endif