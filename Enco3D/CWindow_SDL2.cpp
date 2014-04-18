#include "CWindow_SDL2.h"

void enco::core::CWindow_SDL2::create(char *title, const Dimension2u32 &size, uint8 samples)
{
	m_title = title;
	m_size = size;

	m_cursorPosition = math::Vector2s32(0, 0);

	m_keys = new bool[input::numKeys];
	m_buttons = new bool[input::numButtons];

	m_closeRequested = false;
	m_focused = true;

	__FILLARRAY(m_keys, input::numKeys, false);
	__FILLARRAY(m_buttons, input::numButtons, false);

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (samples > 0)
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, (sint32)samples);

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	}

	SDL_GL_SetSwapInterval(1);

	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_size.x, m_size.y, SDL_WINDOW_OPENGL);

	if (!m_window) return;

	m_context = SDL_GL_CreateContext(m_window);
	SDL_ShowWindow(m_window);

	glewInit();
}

void enco::core::CWindow_SDL2::release()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

void enco::core::CWindow_SDL2::update()
{
	SDL_Event ev;
	SDL_PollEvent(&ev);

	switch (ev.type)
	{
	case SDL_QUIT:
		m_closeRequested = true;
		break;

	case SDL_MOUSEMOTION:
		m_cursorPosition.x = ev.motion.x;
		m_cursorPosition.y = ev.motion.y;

		break;

	case SDL_KEYDOWN:
		m_keys[ev.key.keysym.scancode] = true;

		break;

	case SDL_KEYUP:
		m_keys[ev.key.keysym.scancode] = false;

		break;

	case SDL_MOUSEBUTTONDOWN:
		m_buttons[ev.button.button] = true;

		break;

	case SDL_MOUSEBUTTONUP:
		m_buttons[ev.button.button] = false;

		break;
	}

	SDL_GL_SwapWindow(m_window);
}

void enco::core::CWindow_SDL2::show()
{
	SDL_ShowWindow(m_window);
}

void enco::core::CWindow_SDL2::hide()
{
	SDL_HideWindow(m_window);
}

void enco::core::CWindow_SDL2::setTitle(char *title)
{
	m_title = title;
	SDL_SetWindowTitle(m_window, title);
}

void enco::core::CWindow_SDL2::setPosition(const enco::core::math::Vector2s32 &position)
{
	SDL_SetWindowPosition(m_window, position.x, position.y);
}

void enco::core::CWindow_SDL2::setSize(const enco::core::Dimension2u32 &size)
{
	m_size = size;
	SDL_SetWindowSize(m_window, size.x, size.y);
}

void enco::core::CWindow_SDL2::setCursorPosition(const enco::core::math::Vector2s32 &position)
{
	m_cursorPosition = position;
	SDL_WarpMouseInWindow(m_window, m_cursorPosition.x, m_cursorPosition.y);
}

void enco::core::CWindow_SDL2::setCursor(bool visible)
{
	SDL_ShowCursor(visible);
}