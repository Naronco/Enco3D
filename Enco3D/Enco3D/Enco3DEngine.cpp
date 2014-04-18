#include "Enco3DEngine.h"

void Enco3D::Core::Enco3DEngine::Init(char *windowTitle, unsigned int windowWidth, unsigned int windowHeight, bool multisampleEnabled, unsigned int aaSamples, IGame *game)
{
	m_window = new GLWindow(windowTitle, windowWidth, windowHeight, multisampleEnabled, aaSamples);
	m_timer = new Timer(true);
	m_game = game;
	m_renderingEngine = new RenderingEngine(windowWidth, windowHeight);
	m_physicsEngine = new PhysicsEngine;
	m_audioEngine = new AudioEngine;

	m_physicsEngine->SetTimer(m_timer);
	Random::SetSeed(m_timer->GetTime());
	
	m_window->Show();

	m_game->SetRenderingEngine(m_renderingEngine);
	m_game->SetPhysicsEngine(m_physicsEngine);
	m_game->SetAudioEngine(m_audioEngine);
	m_game->SetWindow(m_window);
	m_game->SetTimer(m_timer);

	m_consoleText = "Console:\n";
	m_consoleGuiText = new GUIText(m_consoleText, FontDatabase::GetInstance()->GetFont("font/courier_new", FontType::Default));

	m_consoleObject = new GameObject("__STD_console");
	m_consoleObject->AddComponent(m_consoleGuiText);
	m_consoleObject->GetTransform()->SetScaling(Vector3f(0.7f, 0.7f, 0.7f));

	m_game->AddGameObject(m_consoleObject);
	m_game->AddGameComponent(m_renderingEngine->GetGUICamera());

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

	if (m_audioEngine)
	{
		delete m_audioEngine;
		m_audioEngine = nullptr;
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

void Enco3D::Core::Enco3DEngine::Console_Print(char *text)
{
	m_consoleText += string(text);
	m_consoleGuiText->SetText(m_consoleText);
}

void Enco3D::Core::Enco3DEngine::Console_PrintLine(char *text)
{
	m_consoleText += string(text) + "\n";
	m_consoleLineCount++;
	Console_CheckAndShort();

	m_consoleGuiText->SetText(m_consoleText);
}

void Enco3D::Core::Enco3DEngine::Console_PrintError(char *text)
{
	m_consoleText += "[ERROR] " + string(text);
	m_consoleLineCount++;
	Console_CheckAndShort();

	m_consoleGuiText->SetText(m_consoleText);
}

void Enco3D::Core::Enco3DEngine::Console_CheckAndShort()
{
	if (m_consoleLineCount > __consoleMaxLineCount)
	{
		unsigned int linesToRemove = m_consoleLineCount - __consoleMaxLineCount;

		while (linesToRemove-- > 0)
		{
			unsigned int cursor = 0;

			while (true)
			{
				if (m_consoleText[cursor] == '\n')
				{
					unsigned int start = (unsigned int)cursor + 1;
					unsigned int end = (unsigned int)m_consoleText.size();
					m_consoleText = m_consoleText.substr(start, end - start);
					m_consoleLineCount--;
					break;
				}

				cursor++;
			}
		}
	}
}