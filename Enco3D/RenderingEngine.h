#ifndef _ENCO3D_RENDERINGENGINE_H_
#define _ENCO3D_RENDERINGENGINE_H_

#include "Matrix4x4.h"
#include "Camera.h"
#include "Transform.h"
#include "BaseLight.h"

#include <vector>

using namespace std;

class RenderingEngine
{
private:
	Camera *m_mainCamera{ nullptr };
	vector<BaseLight *> m_lights;
	Vector3f m_globalAmbientColor;

public:
	RenderingEngine();
	~RenderingEngine();

	Matrix4x4f GetProjectedMatrix(const Matrix4x4f &worldMatrix);

	inline void AddLight(BaseLight *baseLight) { m_lights.push_back(baseLight); }

	inline void SetClearColor(float r, float g, float b) const { glClearColor(r, g, b, 1); }

	inline void SetMainCamera(Camera *mainCamera) { m_mainCamera = mainCamera; }
	inline void SetGlobalAmbientColor(const Vector3f &globalAmbientColor) { m_globalAmbientColor = globalAmbientColor; }

	inline Camera *GetMainCamera() const { return m_mainCamera; }
	inline vector<BaseLight *> GetLights() const { return m_lights; }
	inline Vector3f GetGlobalAmbientColor() const { return m_globalAmbientColor; }
};

#endif