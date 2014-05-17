#include "Camera.h"
#include "IPostProcessEffect.h"

Enco3D::Component::Camera::Camera()
{
	m_projection.setIdentity();
}

Enco3D::Component::Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
	m_projection.setPerspectiveProjection(fov, aspect, zNear, zFar);
	m_inverseProjection = m_projection.getInverse();
	m_projectionMode = ProjectionMode::Perspective;

	m_fov = fov;
	m_tanHalfFov = tanf(fov * 0.5f);
	m_aspectRatio = aspect;
	m_zNearClippingPlane = zNear;
	m_zFarClippingPlane = zFar;
}

Enco3D::Component::Camera::Camera(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection.setOrthographicProjection(left, right, bottom, top, zNear, zFar);
	m_inverseProjection = m_projection.getInverse();
	m_projectionMode = ProjectionMode::Orthographic;

	m_left = left;
	m_right = right;
	m_bottom = bottom;
	m_top = top;
	m_zNearClippingPlane = zNear;
	m_zFarClippingPlane = zFar;
}

void Enco3D::Component::Camera::initRendering()
{
	getRenderingEngine()->setCamera(this, m_depth);
	getRenderingEngine()->setZNearClippingPlane(m_zNearClippingPlane);
	getRenderingEngine()->setZFarClippingPlane(m_zFarClippingPlane);

	for (unsigned int i = 0; i < m_postProcessEffects.size(); i++)
		getRenderingEngine()->initializePostProcessEffect(m_postProcessEffects[i]);
}

void Enco3D::Component::Camera::update()
{
	m_rotationMatrix = (-getTransform()->getRotation()).toRotationMatrix4x4();
	Core::Vector3f cameraPos = -getTransform()->getTranslation();

	Core::Matrix4x4f cameraTranslation = Core::Matrix4x4f().translate(cameraPos.x, cameraPos.y, cameraPos.z);

	m_prevView = m_view;
	m_view = m_rotationMatrix * cameraTranslation;
	m_inverseView = m_view.getInverse();

	m_prevViewProjection = m_viewProjection;
	m_viewProjection = m_projection * m_view;
	m_inverseViewProjection = m_viewProjection.getInverse();
}

void Enco3D::Component::Camera::resize(unsigned int width, unsigned int height)
{
	for (unsigned int i = 0; i < m_postProcessEffects.size(); i++)
		getRenderingEngine()->initializePostProcessEffect(m_postProcessEffects[i]);

	if (m_projectionMode == ProjectionMode::Perspective)
	{
		m_aspectRatio = (float)width / (float)height;
		setPerspectiveProjection(m_fov, m_aspectRatio, m_zNearClippingPlane, m_zFarClippingPlane);
	}
}

void Enco3D::Component::Camera::addPostProcessEffect(IPostProcessEffect *effect)
{
	m_gameObject->addComponent(effect);
	m_postProcessEffects.push_back(effect);
}

void Enco3D::Component::Camera::removePostProcessEffect(IPostProcessEffect *effect)
{
	m_postProcessEffects.erase(std::remove(m_postProcessEffects.begin(), m_postProcessEffects.end(), effect), m_postProcessEffects.end());
	m_gameObject->removeComponent(effect);
}

void Enco3D::Component::Camera::setPerspectiveProjection(float fov, float aspect, float zNear, float zFar)
{
	m_projection.setPerspectiveProjection(fov, aspect, zNear, zFar);
	m_inverseProjection = m_projection.getInverse();
	m_projectionMode = ProjectionMode::Perspective;

	m_fov = fov;
	m_tanHalfFov = tanf(fov * 0.5f);
	m_aspectRatio = aspect;
	m_zNearClippingPlane = zNear;
	m_zFarClippingPlane = zFar;
}

void Enco3D::Component::Camera::setOrthographicProjection(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection.setOrthographicProjection(left, right, bottom, top, zNear, zFar);
	m_inverseProjection = m_projection.getInverse();
	m_projectionMode = ProjectionMode::Orthographic;

	m_left = left;
	m_right = right;
	m_bottom = bottom;
	m_top = top;
	m_zNearClippingPlane = zNear;
	m_zFarClippingPlane = zFar;
}