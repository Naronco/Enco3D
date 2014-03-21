#ifndef _ENCO3D_SPHERECOLLISIONSHAPE_H_
#define _ENCO3D_SPHERECOLLISIONSHAPE_H_

#include "ICollisionShape.h"
#include "Vector3.h"

class SphereCollisionShape : public ICollisionShape
{
private:
	float m_radius;

public:
	SphereCollisionShape();
	SphereCollisionShape(float radius);
	
	btCollisionShape *ToBulletPhysicsCollisionShape();

	inline void SetRadius(float radius) { m_radius = radius; }
	inline float GetRadius() const { return m_radius; }
};

#endif