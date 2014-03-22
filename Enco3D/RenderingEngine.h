#ifndef _ENCO3D_RENDERINGENGINE_H_
#define _ENCO3D_RENDERINGENGINE_H_

#include "Matrix4x4.h"
#include "Transform.h"

#include <vector>
#include <GL/glew.h>

using namespace std;

class GameObject;
class Camera;
class Light;

class RenderingEngine
{
private:
	Camera *m_mainCamera{ nullptr };
	vector<Light *> m_lights;
	Vector3f m_globalAmbientColor;

public:
	RenderingEngine();
	~RenderingEngine();

	void Render(GameObject *gameObject);

	Matrix4x4f GetProjectedMatrix(const Matrix4x4f &worldMatrix);

	inline void AddLight(Light *light) { m_lights.push_back(light); }

	inline void SetClearColor(float r, float g, float b) const { glClearColor(r, g, b, 1); }

	inline void SetMainCamera(Camera *mainCamera) { m_mainCamera = mainCamera; }
	inline void SetGlobalAmbientColor(const Vector3f &globalAmbientColor) { m_globalAmbientColor = globalAmbientColor; }

	inline Camera *GetMainCamera() const { return m_mainCamera; }
	inline vector<Light *> GetLights() const { return m_lights; }
	inline Vector3f GetGlobalAmbientColor() const { return m_globalAmbientColor; }
};

#endif