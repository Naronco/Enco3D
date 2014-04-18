#ifndef __ENCO3D_CPHYSICSDEVICE_BULLETPHYSICS_H_INCLUDED__
#define __ENCO3D_CPHYSICSDEVICE_BULLETPHYSICS_H_INCLUDED__

#include "IPhysicsDevice.h"
#include <btBulletDynamicsCommon.h>

namespace enco
{
	namespace core
	{
		namespace bulletphysics_util
		{
			template <typename T> inline static math::Vector3<T> btVector3_to_Vector3(const btVector3 &v) {
				return math::Vector3<T>(v.getX(), v.getY(), v.getZ());
			}

			template <typename T> inline static btVector3 Vector3_to_btVector3(const math::Vector3<T> &v) {
				btVector3 result;
				result.setValue((btScalar)v.x, (btScalar)v.y, (btScalar)v.z);
				return result;
			}

			template <typename T> inline static math::Vector3<T> btQuaternion_to_YawPitchRoll(const btQuaternion &quat)
			{
				T yaw = (T)math::asin(2 * quat.getX()*quat.getY() + 2 * quat.getZ()*quat.getW());
				T pitch = (T)math::atan2(2 * quat.getX()*quat.getW() - 2 * quat.getY()*quat.getZ(), 1 - 2 * quat.getX()*quat.getX() - 2 * quat.getZ()*quat.getZ());
				T roll = (T)math::atan2(2 * quat.getY()*quat.getW() - 2 * quat.getX()*quat.getZ(), 1 - 2 * quat.getY()*quat.getY() - 2 * quat.getZ()*quat.getZ());
				return math::Vector3<T>(pitch, yaw, roll);
			}

			template <typename T> inline static btQuaternion YawPitchRoll_to_btQuaternion(const math::Vector3<T> &rotation)
			{
				float64 sin_cos_rotX[2], sin_cos_rotY[2], sin_cos_rotZ[2];
				math::sin_cos((float64)rotation.x*0.5, sin_cos_rotX);
				math::sin_cos((float64)rotation.y*0.5, sin_cos_rotY);
				math::sin_cos((float64)rotation.z*0.5, sin_cos_rotZ);
				
				T w = (T)(sin_cos_rotX[__COS_INDEX] * sin_cos_rotY[__COS_INDEX] * sin_cos_rotZ[__COS_INDEX] + sin_cos_rotX[__SIN_INDEX] * sin_cos_rotY[__SIN_INDEX] * sin_cos_rotZ[__SIN_INDEX]);
				T x = (T)(sin_cos_rotX[__SIN_INDEX] * sin_cos_rotY[__COS_INDEX] * sin_cos_rotZ[__COS_INDEX] - sin_cos_rotX[__COS_INDEX] * sin_cos_rotY[__SIN_INDEX] * sin_cos_rotZ[__SIN_INDEX]);
				T y = (T)(sin_cos_rotX[__COS_INDEX] * sin_cos_rotY[__SIN_INDEX] * sin_cos_rotZ[__COS_INDEX] + sin_cos_rotX[__SIN_INDEX] * sin_cos_rotY[__COS_INDEX] * sin_cos_rotZ[__SIN_INDEX]);
				T z = (T)(sin_cos_rotX[__COS_INDEX] * sin_cos_rotY[__COS_INDEX] * sin_cos_rotZ[__SIN_INDEX] - sin_cos_rotX[__SIN_INDEX] * sin_cos_rotY[__SIN_INDEX] * sin_cos_rotZ[__COS_INDEX]);
				
				return btQuaternion((btScalar)x, (btScalar)y, (btScalar)z, (btScalar)w);
			}
		}

		struct __IBulletPhysicsShape
		{
			virtual btCollisionShape *toCollisionShape() = 0;
		};

		struct SphereShape_BulletPhysics : public ISphereShape, public __IBulletPhysicsShape
		{
			btCollisionShape *toCollisionShape() {
				return new btSphereShape((btScalar)radius);
			}
		};

		struct StaticPlaneShape_BulletPhysics : public IStaticPlaneShape, public __IBulletPhysicsShape
		{
			btCollisionShape *toCollisionShape() {
				std::cout << "HAAAAALLO" << std::endl;
//				math::Vector3f32 normal;
//				normal.setDirectionFromYawPitch(rotation.y, rotation.x);
//				float32 d = position.dot(normal);
//				return new btStaticPlaneShape(bulletphysics_util::Vector3_to_btVector3<float32>(normal), (btScalar)d);
				return 0;
			}
		};

		struct RigidBody_BulletPhysics : public IRigidBody
		{
			RigidBodyData data;
			btRigidBody *bulletInstance;
		};

		class CPhysicsDevice_BulletPhysics : public IPhysicsDevice
		{
		private:
			btBroadphaseInterface *m_broadphase;
			btDefaultCollisionConfiguration *m_collisionConfiguration;
			btCollisionDispatcher *m_dispatcher;
			btSequentialImpulseConstraintSolver *m_solver;
			btDiscreteDynamicsWorld *m_dynamicsWorld;

		public:
			void create();
			void release();

			void update();

			IRigidBody *addRigidBody(const RigidBodyData &rigidBodyData);
			void removeRigidBody(IRigidBody *rigidBody);

			ISphereShape *createSphereShape(float32 radius);
			IStaticPlaneShape *createStaticPlaneShape();

			void setGravity(const math::Vector3f32 &gravity);
		};
	}
}

#endif