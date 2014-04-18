#ifndef __ENCO3D_IPHYSICSDEVICE_H_INCLUDED__
#define __ENCO3D_IPHYSICSDEVICE_H_INCLUDED__

#include "SVector3.h"
#include "CTimer.h"
#include <vector>

namespace enco
{
	namespace core
	{
		struct IShape { math::Vector3f32 position, rotation; };
		struct ISphereShape : public IShape {
			float32 radius;
		};
		struct IStaticPlaneShape : public IShape {
		};

		struct RigidBodyData
		{
			IShape *shape;
			float32 mass;
			float32 restitution;
			float32 friction;
			float32 linearDamping, angularDamping;
			bool rotationEnabled;
		};

		struct IRigidBody {  };

		class IPhysicsDevice
		{
		protected:
			std::vector<IRigidBody*> m_rigidBodies;
			math::Vector3f32 m_gravity;
			CTimer *m_timer;

			std::vector<IShape*> m_shapes;

			inline void releaseCreatedShapes() {
				for (uint32 i = 0; i < m_shapes.size(); i++) {
					delete m_shapes[i];
				}
			}

		public:
			virtual void create() = 0;
			virtual void release() = 0;

			virtual void update() = 0;

			virtual IRigidBody *addRigidBody(const RigidBodyData &rigidBodyData) = 0;
			virtual void removeRigidBody(IRigidBody *rigidBody) = 0;

			virtual ISphereShape *createSphereShape(float32 radius) = 0;
			virtual IStaticPlaneShape *createStaticPlaneShape() = 0;

			virtual void setGravity(const math::Vector3f32 &gravity) = 0;
			inline math::Vector3f32 getGravity() const { return m_gravity; }

			inline void setTimer(CTimer *timer) { m_timer = timer; }
			inline CTimer *getTimer() const { return m_timer; }
		};
	}
}

#endif