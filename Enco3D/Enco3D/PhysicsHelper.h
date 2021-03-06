#ifndef _ENCO3D_PHYSICSHELPER_H_
#define _ENCO3D_PHYSICSHELPER_H_

#include "Vector3.h"
#include "Quaternion.h"
#include "DLLExport.h"

#include <btBulletDynamicsCommon.h>

namespace Enco3D
{
	namespace Physics
	{
		namespace PhysicsHelper
		{
			template <typename T>
			inline static btVector3 toBulletPhysicsVec3(const Core::Vector3<T> &v)
			{
				btVector3 result;

				result.setX(v.x);
				result.setY(v.y);
				result.setZ(v.z);

				return result;
			}

			template <typename T>
			inline static btQuaternion toBulletPhysicsQuat(const Core::Quaternion<T> &q)
			{
				btQuaternion result;

				result.setX(q.x);
				result.setY(q.y);
				result.setZ(q.z);
				result.setW(q.w);

				return result;
			}

			template <typename T>
			inline static Core::Vector3<T> toEnco3DVec3(const btVector3 &v)
			{
				return Core::Vector3<T>(v.x(), v.y(), v.z());
			}

			template <typename T>
			inline static Core::Quaternion<T> toEnco3DQuat(const btQuaternion &q)
			{
				return Core::Quaternion<T>(q.x(), q.y(), q.z(), q.w());
			}
		}
	}
}

#endif