#include "GameObject.h"
#include "IGameComponent.h"
#include "Camera.h"

Enco3D::Core::GameObject::GameObject()
{
	m_transform = new Transform;
}

Enco3D::Core::GameObject::GameObject(const string &name)
{
	m_name = name;
	m_transform = new Transform;
}

Enco3D::Core::GameObject::~GameObject()
{
	for (unsigned int j = 0; j < m_components.size(); j++)
	{
		m_components[j]->deinit();
		delete m_components[j];
	}

	m_components.clear();

	for (unsigned int i = 0; i < m_children.size(); i++)
		if (m_children[i])
			delete m_children[i];
}

void Enco3D::Core::GameObject::update()
{
	if (!m_enabled)
		return;

	m_transform->update();

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->update();

	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->update();
}

void Enco3D::Core::GameObject::render(const Enco3D::Component::Camera *camera, Enco3D::Rendering::Shader *shader)
{
	if (!m_enabled)
		return;

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->render(camera, shader);

	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->render(camera, shader);
}

void Enco3D::Core::GameObject::renderGUI(const Enco3D::Component::Camera *camera, Enco3D::Rendering::Shader *shader)
{
	if (!m_enabled)
		return;

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->renderGUI(camera, shader);

	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->renderGUI(camera, shader);
}

void Enco3D::Core::GameObject::resize(unsigned int width, unsigned int height)
{
	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->resize(width, height);

	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->resize(width, height);
}

Enco3D::Core::GameObject *Enco3D::Core::GameObject::addChild(GameObject *child)
{
	if (m_renderingEngine)
		child->setRenderingEngine(m_renderingEngine);
	
	if (m_physicsEngine)
		child->setPhysicsEngine(m_physicsEngine);

	child->setWindow(m_window);
	child->setTimer(m_timer);
	child->getTransform()->setParentTransform(m_transform);
	m_children.push_back(child);

	return this;
}

Enco3D::Core::GameObject *Enco3D::Core::GameObject::addComponent(IGameComponent *component)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->onAddComponentToObject(component);

	component->setGameObject(this);
	component->init();
	m_components.push_back(component);

	return this;
}

void Enco3D::Core::GameObject::removeComponent(IGameComponent *component)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
		if (m_components[i] != component)
			m_components[i]->onRemoveComponentFromObject(component);

	component->deinit();
	delete component;

	m_components.erase(std::remove(m_components.begin(), m_components.end(), component), m_components.end());
}

void Enco3D::Core::GameObject::setRenderingEngine(Enco3D::Rendering::RenderingEngine *renderingEngine)
{
	m_renderingEngine = renderingEngine;

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->setRenderingEngine(renderingEngine);

	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->initRendering();
}

void Enco3D::Core::GameObject::setPhysicsEngine(Enco3D::Physics::PhysicsEngine *physicsEngine)
{
	m_physicsEngine = physicsEngine;

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->setPhysicsEngine(physicsEngine);

	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->initPhysics();
}

void Enco3D::Core::GameObject::setWindow(GLWindow *window)
{
	m_window = window;

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->setWindow(window);
}

void Enco3D::Core::GameObject::setTimer(Timer *timer)
{
	m_timer = timer;

	for (unsigned int i = 0; i < m_children.size(); i++)
		m_children[i]->setTimer(timer);
}

Enco3D::Core::GameObject *Enco3D::Core::GameObject::getChild(const string &name) const
{
	for (unsigned int i = m_children.size() - 1; i >= 0; i--)
		if (m_children[i]->getName() == name)
			return m_children[i];

	return nullptr;
}