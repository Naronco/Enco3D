#ifndef _ENCO3D_STATICPLANECOLLISIONSHAPE_H_
#define _ENCO3D_STATICPLANECOLLISIONSHAPE_H_

#include "ICollisionShape.h"
#include "Vector3.h"

class StaticPlaneCollisionShape : public ICollisionShape
{
private:
	Vector3f m_normal;
	float m_origin;

public:
	StaticPlaneCollisionShape();
	StaticPlaneCollisionShape(const Vector3f &normal, float origin);
	StaticPlaneCollisionShape(const Vector3f &p0, const Vector3f &p1, const Vector3f &p2);
	~StaticPlaneCollisionShape();

	btCollisionShape *ToBulletPhysicsCollisionShape();
	
	inline void SetNormal(const Vector3f &normal) { m_normal.Set(normal); }
	inline void SetOrigin(float origin) { m_origin = origin; }

	inline Vector3f GetNormal() const { return m_normal; }
	inline float GetOrigin() const { return m_origin; }
};

#endif