#include "Enco3DEngine.h"

void Enco3D::Core::Enco3DEngine::Init(char *windowTitle, unsigned int windowWidth, unsigned int windowHeight, IGame *game)
{
	m_window = new GLWindow(windowTitle, windowWidth, windowHeight);
	m_timer = new Timer(true);
	m_game = game;
	m_renderingEngine = new RenderingEngine(windowWidth, windowHeight);
	m_physicsEngine = new PhysicsEngine;

	m_physicsEngine->SetTimer(m_timer);
	Random::SetSeed(m_timer->GetTime());
	
	m_window->Show();

	m_game->SetRenderingEngine(m_renderingEngine);
	m_game->SetPhysicsEngine(m_physicsEngine);
	m_game->SetWindow(m_window);
	m_game->SetTimer(m_timer);

	m_game->Init();
}

void Enco3D::Core::Enco3DEngine::Deinit()
{
	if (m_game)
	{
		m_game->Deinit();
		delete m_game;
		m_game = nullptr;
	}

	if (m_physicsEngine)
	{
		delete m_physicsEngine;
		m_physicsEngine = nullptr;
	}

	if (m_renderingEngine)
	{
		delete m_renderingEngine;
		m_renderingEngine = nullptr;
	}

	if (m_timer)
	{
		delete m_timer;
		m_timer = nullptr;
	}

	if (m_window)
	{
		m_window->Close();
		delete m_window;
		m_window = nullptr;
	}
}

void Enco3D::Core::Enco3DEngine::MainLoop()
{
	Event event;

	while (m_window->Update(&event))
	{
		if (!m_window->IsFocused() && m_window->IsFullscreen())
		{
			m_window->SetFullscreen(false);
		}

		m_game->GetRootObject()->Update();

		m_physicsEngine->Update();
		m_renderingEngine->Render(m_game->GetRootObject());

		m_timer->Update();

		m_game->Update();
		m_game->Render();
	}
}