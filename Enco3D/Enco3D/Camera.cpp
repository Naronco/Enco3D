#include "Camera.h"
#include "IPostProcessEffect.h"

Enco3D::Component::Camera::Camera()
{
	m_projection.SetIdentity();
}

Enco3D::Component::Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
	m_projection.SetPerspectiveProjection(fov, aspect, zNear, zFar);
	m_projectionMode = ProjectionMode::Perspective;

	m_fov = fov;
	m_tanHalfFov = tanf(fov*0.5f);
	m_aspectRatio = aspect;
	m_zNearClippingPlane = zNear;
	m_zFarClippingPlane = zFar;
}

Enco3D::Component::Camera::Camera(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection.SetOrthographicProjection(left, right, bottom, top, zNear, zFar);
	m_projectionMode = ProjectionMode::Orthographic;

	m_left = left;
	m_right = right;
	m_bottom = bottom;
	m_top = top;
	m_zNearClippingPlane = zNear;
	m_zFarClippingPlane = zFar;
}

void Enco3D::Component::Camera::InitRendering()
{
	GetRenderingEngine()->SetCamera(this, m_depth);
	GetRenderingEngine()->SetZNearClippingPlane(m_zNearClippingPlane);
	GetRenderingEngine()->SetZFarClippingPlane(m_zFarClippingPlane);

	for (unsigned int i = 0; i < m_postProcessEffects.size(); i++)
		GetRenderingEngine()->InitializePostProcessEffect(m_postProcessEffects[i]);
}

void Enco3D::Component::Camera::Update()
{
	Core::Matrix4x4f cameraRotation = (-GetTransform()->GetRotation()).ToRotationMatrix4x4();
	Core::Vector3f cameraPos = -GetTransform()->GetTranslation();

	Core::Matrix4x4f cameraTranslation = Core::Matrix4x4f().Translate(cameraPos.x, cameraPos.y, cameraPos.z);

	m_prevView = m_view;
	m_view = cameraRotation * cameraTranslation;
	
	m_prevViewProjection = m_viewProjection;
	m_viewProjection = m_projection * m_view;
}

void Enco3D::Component::Camera::Resize(unsigned int width, unsigned int height)
{
/*	for (unsigned int i = 0; i < m_postProcessEffects.size(); i++)
		GetRenderingEngine()->InitializePostProcessEffect(m_postProcessEffects[i]);

	if (m_projectionMode == ProjectionMode::Perspective)
	{
		m_aspectRatio = (float)width / (float)height;
		SetPerspectiveProjection(m_fov, m_aspectRatio, m_zNearClippingPlane, m_zFarClippingPlane);
	}*/
}

void Enco3D::Component::Camera::OnAddComponentToObject(Core::IGameComponent *component)
{
//	if (typeid(*component) == typeid(IPostProcessEffect))
//		m_postProcessEffects.push_back((IPostProcessEffect*)component);
}

void Enco3D::Component::Camera::OnRemoveComponentFromObject(Core::IGameComponent *component)
{
/*	if (typeid(*component) == typeid(IPostProcessEffect))
	{
		std::cout << m_postProcessEffects.size() << std::endl;

		IPostProcessEffect *effect = (IPostProcessEffect*)component;
		m_postProcessEffects.erase(std::remove(m_postProcessEffects.begin(), m_postProcessEffects.end(), effect), m_postProcessEffects.end());
	}*/
}

void Enco3D::Component::Camera::SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar)
{
	m_projection.SetPerspectiveProjection(fov, aspect, zNear, zFar);
	m_projectionMode = ProjectionMode::Perspective;

	m_fov = fov;
	m_tanHalfFov = tanf(fov*0.5f);
	m_aspectRatio = aspect;
	m_zNearClippingPlane = zNear;
	m_zFarClippingPlane = zFar;
}

void Enco3D::Component::Camera::SetOrthographicProjection(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection.SetOrthographicProjection(left, right, bottom, top, zNear, zFar);
	m_projectionMode = ProjectionMode::Orthographic;

	m_left = left;
	m_right = right;
	m_bottom = bottom;
	m_top = top;
	m_zNearClippingPlane = zNear;
	m_zFarClippingPlane = zFar;
}