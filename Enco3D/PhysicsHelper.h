#ifndef _ENCO3D_PHYSICSHELPER_H_
#define _ENCO3D_PHYSICSHELPER_H_

#include "Vector3.h"
#include "Quaternion.h"

#include <btBulletDynamicsCommon.h>

namespace PhysicsHelper
{
	template <typename T>
	inline static btVector3 ToBulletPhysicsVec3(const Vector3<T> &v)
	{
		btVector3 result;

		result.setX(v.x);
		result.setY(v.y);
		result.setZ(v.z);

		return result;
	}

	template <typename T>
	inline static btQuaternion ToBulletPhysicsQuat(const Quaternion<T> &q)
	{
		btQuaternion result;

		result.setX(q.x);
		result.setY(q.y);
		result.setZ(q.z);
		result.setW(q.w);

		return result;
	}

	template <typename T>
	inline static Vector3<T> ToEnco3DVec3(const btVector3 &v)
	{
		return Vector3<T>(v.x(), v.y(), v.z());
	}

	template <typename T>
	inline static Quaternion<T> ToEnco3DQuat(const btQuaternion &q)
	{
		return Quaternion<T>(q.x(), q.y(), q.z(), q.w());
	}
}

#endif