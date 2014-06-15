#ifndef _ENCO3D_BOUNDINGSPHERE_H_
#define _ENCO3D_BOUNDINGSPHERE_H_

#include "Vector3.h"
#include "Matrix4x4.h"
#include <algorithm>
#include "Contains.h"
#include "BoundingBox.h"
#include "Frustum.h"
#include "Plane.h"
#include "PlaneIntersectionType.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Core
	{
		class DLL_EXPORT BoundingSphere
		{
		public:
			BoundingSphere(Vector3f center, float radius) : m_center(center), m_radius(radius) { }
			~BoundingSphere();

			inline BoundingSphere Transform(Matrix4x4f matrix)
			{
				return BoundingSphere(m_center.transform(matrix), m_radius * ((float)sqrt((double)std::max(((matrix.m11 * matrix.m11) + (matrix.m12 * matrix.m12)) + (matrix.m13 * matrix.m13), std::max(((matrix.m21 * matrix.m21) + (matrix.m22 * matrix.m22)) + (matrix.m23 * matrix.m23), ((matrix.m31 * matrix.m31) + (matrix.m32 * matrix.m32)) + (matrix.m33 * matrix.m33))))));
			}

			inline Contains contains(const BoundingBox& box)
			{
				bool inside = true;
				for (Vector3f corner : box.GetCorners())
				{
					if (contains(corner) == Contains::Exclude)
					{
						inside = false;
						break;
					}
				}

				if (inside)
					return Contains::Contain;

				double dmin = 0;

				if (m_center.x < box.m_min.x)
					dmin += (m_center.x - box.m_min.x) * (m_center.x - box.m_min.x);

				else if (m_center.x > box.m_max.x)
					dmin += (m_center.x - box.m_max.x) * (m_center.x - box.m_max.x);

				if (m_center.y < box.m_min.y)
					dmin += (m_center.y - box.m_min.y) * (m_center.y - box.m_min.y);

				else if (m_center.y > box.m_max.y)
					dmin += (m_center.y - box.m_max.y) * (m_center.y - box.m_max.y);

				if (m_center.z < box.m_min.z)
					dmin += (m_center.z - box.m_min.z) * (m_center.z - box.m_min.z);

				else if (m_center.z > box.m_max.z)
					dmin += (m_center.z - box.m_max.z) * (m_center.z - box.m_max.z);

				if (dmin <= Radius * Radius)
					return Contains::Intersect;

				return Contains::Exclude;
			}

			inline Contains contains(const Frustum& frustum)
			{
				bool inside = true;

				Vector3f* corners = frustum.GetCorners();
				foreach(Vector3f corner in corners)
				{
					if (contains(corner) == Contains::Exclude)
					{
						inside = false;
						break;
					}
				}
				if (inside)
					return Contains::Contain;

				double dmin = 0;

				if (dmin <= Radius * Radius)
					return Contains::Intersect;

				return Contains::Exclude;
			}

			inline Contains contains(const BoundingSphere& sphere)
			{
				float val = sphere.m_center.getSquaredDistance(m_center);

				if (val > (sphere.m_radius + m_radius) * (sphere.m_radius + m_radius))
					return Contains::Exclude;
				else if (val <= (m_radius - sphere.m_radius) * (m_radius - sphere.m_radius))
					return Contains::Contain;
				else
					return Contains::Intersect;
			}

			inline Contains contains(const Vector3f& point)
			{
				float distance = point.getSquaredDistance(m_center);

				if (distance > m_radius * m_radius)
					return Contains::Exclude;

				else if (distance < m_radius * m_radius)
					return Contains::Contain;

				return Contains::Intersect;
			}

			static BoundingSphere createFromBoundingBox(const BoundingBox& box)
			{
				Vector3f center((box.m_min.x + box.m_max.x) / 2.0f,
					(box.m_min.y + box.m_max.y) / 2.0f,
					(box.m_min.z + box.m_max.z) / 2.0f);

				float radius = center.getDistance<float>(box.m_max);

				return BoundingSphere(center, radius);
			}

			inline PlaneIntersectionType intersects(const Plane& plane)
			{
				float dist = plane.m_normal.dot<float>(m_center);
				dist += plane.m_d;
				if (dist > m_radius)
					return PlaneIntersectionType::Front;
				else if (dist < -m_radius)
					return PlaneIntersectionType::Back;
				else
					return PlaneIntersectionType::Intersecting;
			}

		protected:
			Vector3f m_center;
			float m_radius;
		};
	}
}
#endif