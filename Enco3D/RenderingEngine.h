#ifndef _ENCO3D_RENDERINGENGINE_H_
#define _ENCO3D_RENDERINGENGINE_H_

#include "Matrix4x4.h"
#include "Transform.h"
#include "GBuffer.h"
#include "Mesh.h"
#include "Material.h"

#include <vector>
#include <GL/glew.h>
#include <algorithm>

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

	GBuffer *m_gbuffer{ nullptr };
	unsigned int m_width, m_height;
	Mesh *m_renderWindow{ nullptr };
	Material m_renderWindowMaterial;

public:
	RenderingEngine();
	RenderingEngine(unsigned int width, unsigned int height);
	~RenderingEngine();

	void Render(GameObject *gameObject);

	Matrix4x4f GetProjectedMatrix(const Matrix4x4f &worldMatrix);

	inline void AddLight(Light *light) { m_lights.push_back(light); }
	inline void RemoveLight(Light *light) { m_lights.erase(remove(m_lights.begin(), m_lights.end(), light), m_lights.end()); }

	inline void SetClearColor(float r, float g, float b) const { glClearColor(r, g, b, 1); }

	inline void SetMainCamera(Camera *mainCamera) { m_mainCamera = mainCamera; }
	inline void SetGlobalAmbientColor(const Vector3f &globalAmbientColor) { m_globalAmbientColor = globalAmbientColor; }
	inline void SetWidth(unsigned int width) { m_width = width; }
	inline void SetHeight(unsigned int height) { m_height = height; }

	inline Camera *GetMainCamera() const { return m_mainCamera; }
	inline vector<Light *> GetLights() const { return m_lights; }
	inline Vector3f GetGlobalAmbientColor() const { return m_globalAmbientColor; }
	inline unsigned int GetWidth() const { return m_width; }
	inline unsigned int GetHeight() const { return m_height; }
};

#endif