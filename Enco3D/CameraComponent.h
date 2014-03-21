#ifndef _ENCO3D_CAMERACOMPONENT_H_
#define _ENCO3D_CAMERACOMPONENT_H_

#include "IGameComponent.h"
#include "Camera.h"

class CameraComponent : public IGameComponent
{
private:
	Camera *m_camera{ nullptr };

public:
	CameraComponent();
	CameraComponent(Camera *camera);
	~CameraComponent();

	void InitRendering();

	void Update();

	inline void SetCamera(Camera *camera) { m_camera = camera; }
	inline Camera *GetCamera() const { return m_camera; }
};

#endif