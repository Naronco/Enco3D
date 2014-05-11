#include "Enco3DEngine.h"
#include "FontPool.h"
#include "ShaderPool.h"
#include "DebugLogger.h"

void Enco3D::Core::Enco3DEngine::Init(char *windowTitle, unsigned int windowWidth, unsigned int windowHeight, bool multisampleEnabled, unsigned int aaSamples, IGame *game)
{
	Core::DebugLogger::Init();
	
	m_window = new GLWindow(windowTitle, windowWidth, windowHeight, multisampleEnabled, aaSamples);
	m_timer = new Timer(true);
	m_game = game;
	m_renderingEngine = new Rendering::RenderingEngine(windowWidth, windowHeight);
	m_physicsEngine = new Physics::PhysicsEngine;
	m_audioEngine = new Audio::AudioEngine;

	m_physicsEngine->SetTimer(m_timer);
	Random::SetSeed(m_timer->GetTime());
	
	m_window->Show();

	m_game->SetRenderingEngine(m_renderingEngine);
	m_game->SetPhysicsEngine(m_physicsEngine);
	m_game->SetAudioEngine(m_audioEngine);
	m_game->SetWindow(m_window);
	m_game->SetTimer(m_timer);

	m_game->AddGameComponent(m_renderingEngine->GetGUICamera());

	m_game->Init();
}

void Enco3D::Core::Enco3DEngine::Deinit()
{
	Rendering::FontPool::GetInstance()->Release();
	Rendering::ShaderPool::GetInstance()->Release();

	if (m_game)
	{
		m_game->Deinit();

		GameObject *rootGameObject = m_game->GetRootObject();
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
		m_window->Close();
		delete m_window;
	}

	Core::DebugLogger::Deinit();
}

void Enco3D::Core::Enco3DEngine::MainLoop()
{
	float unprocessedSeconds = 0.0f;

	Event event;
	while (m_window->Update(&event))
	{
		if (!m_window->IsFocused() && m_window->IsFullscreen())
			m_window->SetFullscreen(false);

		if (event.type == EventType::Window && event.windowEvent.event == SDL_WINDOWEVENT_RESIZED)
		{
			unsigned int newWidth = (unsigned int)event.windowEvent.data1;
			unsigned int newHeight = (unsigned int)event.windowEvent.data2;

			m_renderingEngine->Resize(newWidth, newHeight);
			m_game->GetRootObject()->Resize(newWidth, newHeight);
		}
		
		m_timer->Update();

		m_renderingEngine->Render(m_game->GetRootObject());
		
		unprocessedSeconds += m_timer->GetDeltaTime() * 60.0f;
		while (unprocessedSeconds >= 1.0f)
		{
			m_game->GetRootObject()->Update();
			m_physicsEngine->Update();
			m_game->Update();

			m_timer->increaseFps();

			unprocessedSeconds -= 1.0f;
		}
	}
}