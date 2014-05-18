#include "Enco3DEngine.h"
#include "FontPool.h"
#include "ShaderPool.h"
#include "DebugLogger.h"

void Enco3D::Core::Enco3DEngine::init(char *windowTitle, unsigned int windowWidth, unsigned int windowHeight, bool multisampleEnabled, unsigned int aaSamples, const std::string &iconSource, IGame *game)
{
	Core::DebugLogger::init();

	m_window = new GLWindow(windowTitle, windowWidth, windowHeight, multisampleEnabled, aaSamples, iconSource);
	m_timer = new Timer(true);
	m_game = game;
	m_renderingEngine = new Rendering::RenderingEngine(windowWidth, windowHeight);
	m_physicsEngine = new Physics::PhysicsEngine;
	m_audioEngine = new Audio::AudioEngine;

	m_physicsEngine->setTimer(m_timer);
	Random::setSeed(m_timer->getTime());

	m_window->show();

	m_game->setRenderingEngine(m_renderingEngine);
	m_game->setPhysicsEngine(m_physicsEngine);
	m_game->setAudioEngine(m_audioEngine);
	m_game->setWindow(m_window);
	m_game->setTimer(m_timer);

	m_game->addGameComponent(m_renderingEngine->getGUICamera());
}

void Enco3D::Core::Enco3DEngine::deinit()
{
	Rendering::FontPool::getInstance()->release();
	Rendering::ShaderPool::getInstance()->release();

	if (m_game)
	{
		m_game->deinit();

		GameObject *rootGameObject = m_game->getRootObject();
		if (rootGameObject)
			delete rootGameObject;

		delete m_game;
	}

	if (m_audioEngine)
		delete m_audioEngine;

	if (m_physicsEngine)
		delete m_physicsEngine;

	if (m_renderingEngine)
		delete m_renderingEngine;

	if (m_timer)
		delete m_timer;

	if (m_window)
	{
		m_window->close();
		delete m_window;
	}

	Core::DebugLogger::deinit();
}

void Enco3D::Core::Enco3DEngine::mainLoop()
{
	float unprocessedSeconds = 0.0f;

	Event event;
	while (m_window->update())
	{
		if (!m_window->isFocused() && m_window->isFullscreen())
			m_window->setFullscreen(false);

		while (m_window->pollEvent(&event))
		{
			if (event.type == EventType::Window && event.windowEvent.event == SDL_WINDOWEVENT_RESIZED)
			{
				unsigned int newWidth = (unsigned int)event.windowEvent.data1;
				unsigned int newHeight = (unsigned int)event.windowEvent.data2;

				m_renderingEngine->resize(newWidth, newHeight);
				m_game->getRootObject()->resize(newWidth, newHeight);
			}
		}

		m_timer->update();

		m_renderingEngine->render(m_game->getRootObject());

		unprocessedSeconds += m_timer->getDeltaTime() * 60.0f;
		while (unprocessedSeconds >= 1.0f)
		{
			m_game->getRootObject()->update();
			m_physicsEngine->update();
			m_game->update();

			m_timer->increaseFps();

			unprocessedSeconds -= 1.0f;
		}
	}
}