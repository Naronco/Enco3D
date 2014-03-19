#include "Enco3DEngine.h"

void Enco3DEngine::Init(char *windowTitle, unsigned int windowWidth, unsigned int windowHeight, IGame *game)
{
	m_window = new GLWindow(windowTitle, windowWidth, windowHeight);
	m_timer = new Timer(true);
	m_game = game;
	m_renderingEngine = new RenderingEngine;

	m_window->Show();

	m_game->SetRenderingEngine(m_renderingEngine);
	m_game->SetWindow(m_window);
	m_game->SetTimer(m_timer);

	m_game->Init();
}

void Enco3DEngine::Deinit()
{
	if (m_renderingEngine)
	{
		delete m_renderingEngine;
		m_renderingEngine = nullptr;
	}

	if (m_game)
	{
		m_game->Deinit();
		delete m_game;
		m_game = nullptr;
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

void Enco3DEngine::MainLoop()
{
	Event event;

	while (m_window->Update(&event))
	{
		if (!m_window->IsFocused() && m_window->IsFullscreen())
		{
			m_window->SetFullscreen(false);
		}

		m_timer->Update();

		m_game->UpdateGameObjects();
		m_game->Update();

		m_game->RenderGameObjects();
		m_game->Render();
	}
}