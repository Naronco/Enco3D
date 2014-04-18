#ifndef __ENCO3D_RENDERUTIL_H_INCLUDED__
#define __ENCO3D_RENDERUTIL_H_INCLUDED__

#include "SVector2.h"
#include "SVector3.h"

namespace enco
{
	namespace core
	{
		namespace renderutil
		{
			template <typename T> inline static math::Vector3<T> calculateTangent(const math::Vector3<T> &v0, const math::Vector2<T> &t0,
																				  const math::Vector3<T> &v1, const math::Vector2<T> &t1,
																				  const math::Vector3<T> &v2, const math::Vector2<T> &t2) {
				math::Vector3<T> vu = v1 - v0;
				math::Vector3<T> vv = v2 - v0;

				math::Vector2<T> tu = t1 - t0;
				math::Vector2<T> tv = t2 - t0;

				T den = (T)(1.0 / (tu.x * tv.y - tu.y * tv.x));

				math::Vector3<T> tangent;

				tangent.x = (tv.y * vu.x - tu.y * vv.x) * den;
				tangent.y = (tv.y * vu.y - tu.y * vv.y) * den;
				tangent.z = (tv.y * vu.z - tu.y * vv.z) * den;

				return tangent.getNormalized();
			}
			
			template <typename T> inline static math::Vector3<T> calculateBinormal(const math::Vector3<T> &v0, const math::Vector2<T> &t0,
																				   const math::Vector3<T> &v1, const math::Vector2<T> &t1,
																				   const math::Vector3<T> &v2, const math::Vector2<T> &t2) {
				math::Vector3<T> vu = v1 - v0;
				math::Vector3<T> vv = v2 - v0;

				math::Vector2<T> tu = t1 - t0;
				math::Vector2<T> tv = t2 - t0;

				T den = (T)(1.0 / (tu.x * tv.y - tu.y * tv.x));

				math::Vector3<T> binormal;

				binormal.x = (tu.x * vv.x - tv.x * vu.x) * den;
				binormal.y = (tu.x * vv.y - tv.x * vu.y) * den;
				binormal.z = (tu.x * vv.z - tv.x * vu.z) * den;

				return binormal.getNormalized();
			}
		}
	}
}

#endif