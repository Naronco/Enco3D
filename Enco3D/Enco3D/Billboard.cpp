#include "Billboard.h"

Enco3D::Component::Billboard::Billboard()
{
}

Enco3D::Component::Billboard::~Billboard()
{
}

void Enco3D::Component::Billboard::render(const Component::Camera *camera, Rendering::Shader *shader)
{
	getTransform()->setBillboardEnabled(m_enabled);
	if (m_enabled)
	{
		getTransform()->setBillboardCamera((Component::Camera*)camera);
	}
}