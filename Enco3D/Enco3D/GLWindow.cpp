#include "GLWindow.h"
#include "ImageIO.h"

Enco3D::Core::GLWindow::GLWindow()
{
	Input::Init();
}

Enco3D::Core::GLWindow::GLWindow(char *title, unsigned int width, unsigned int height, bool multisampleEnabled, unsigned int aaSamples, const std::string &iconSource)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (multisampleEnabled)
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, (int)aaSamples);

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		glEnable(GL_MULTISAMPLE);
	}

	SDL_GL_SetSwapInterval(-1);

	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (m_window != nullptr)
	{
		m_running = true;
		m_width = width;
		m_height = height;
		m_context = SDL_GL_CreateContext(m_window);
	}
	else
	{
		Core::DebugLogger::log("Failed to create SDL window");
		return;
	}

	if (iconSource.length() > 0)
	{
		IO::ImageIO_Output iconOutput;
		IO::ImageIO::loadImage(iconSource, &iconOutput);

		unsigned int numPixels = iconOutput.width * iconOutput.height;
		unsigned int *pixels = new unsigned int[numPixels];

		for (unsigned int i = 0; i < numPixels; i++)
			pixels[i] = ((unsigned int)(iconOutput.pixels[(i << 2) + 3] * 255.0f)) << 24 | ((unsigned int)(iconOutput.pixels[i << 2] * 255.0f)) << 16 | ((unsigned int)(iconOutput.pixels[(i << 2) + 1] * 255.0f)) << 8 | ((unsigned int)(iconOutput.pixels[(i << 2) + 2] * 255.0f));

		SDL_Surface *iconSurface = SDL_CreateRGBSurfaceFrom(pixels, (int)iconOutput.width, (int)iconOutput.height, 32, sizeof(unsigned int)* (int)iconOutput.width, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
		SDL_SetWindowIcon(m_window, iconSurface);

		delete[] pixels;
		pixels = nullptr;
	}

	GLenum result = glewInit();
	if (result == GLEW_OK)
		Core::DebugLogger::log("Successfully initialized GLEW");
	else
		Core::DebugLogger::log("Failed to initialize GLEW");

	Input::Init();
}

void Enco3D::Core::GLWindow::show()
{
	if (m_window != nullptr)
		SDL_ShowWindow(m_window);
}

void Enco3D::Core::GLWindow::hide()
{
	if (m_window != nullptr)
		SDL_HideWindow(m_window);
}

void Enco3D::Core::GLWindow::close()
{
	if (m_window != nullptr)
	{
		SDL_DestroyWindow(m_window);
		Input::Deinit();
	}
}

void Enco3D::Core::GLWindow::resize(unsigned int width, unsigned int height)
{
	if (m_window)
	{
		SDL_SetWindowSize(m_window, width, height);
		glViewport(0, 0, width, height);

		m_width = width;
		m_height = height;
	}
}

void Enco3D::Core::GLWindow::setFullscreen(bool fullscreen)
{
	if (m_window && SDL_SetWindowFullscreen(m_window, fullscreen) == 0)
		m_fullscreen = fullscreen;
}

void Enco3D::Core::GLWindow::setPosition(int x, int y)
{
	if (m_window)
		SDL_SetWindowPosition(m_window, x, y);
}

bool Enco3D::Core::GLWindow::pollEvent(Event *e)
{
	SDL_Event ev;
	if (!SDL_PollEvent(&ev)) return false;

	Event ne;

	switch (ev.type)
	{
	case SDL_QUIT:
		ne.type = EventType::Quit;
		break;

	case SDL_WINDOWEVENT:
		ne.type = EventType::Window;
		ne.windowEvent.data1 = ev.window.data1;
		ne.windowEvent.data2 = ev.window.data2;
		ne.windowEvent.event = ev.window.event;
		ne.window = ev.window.windowID;

		if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
			m_running = false;

		if (ev.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
			m_focused = true;

		if (ev.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
			m_focused = false;

		if (ev.window.event == SDL_WINDOWEVENT_RESIZED)
			glViewport(0, 0, ev.window.data1, ev.window.data2);

		break;

	case SDL_KEYDOWN:
		ne.type = EventType::KeyDown;
		ne.keyboard.keyCode = ev.key.keysym.scancode;
		ne.keyboard.modifiers = ev.key.keysym.mod;
		ne.window = ev.key.windowID;
		break;

	case SDL_KEYUP:
		ne.type = EventType::KeyUp;
		ne.keyboard.keyCode = ev.key.keysym.scancode;
		ne.keyboard.modifiers = ev.key.keysym.mod;
		ne.window = ev.key.windowID;
		break;

	case SDL_MOUSEMOTION:
		ne.type = EventType::MouseMove;
		ne.mouseMove.destinationX = ev.motion.x;
		ne.mouseMove.destinationY = ev.motion.y;
		ne.mouseMove.relativeX = ev.motion.xrel;
		ne.mouseMove.relativeY = ev.motion.yrel;
		break;

	case SDL_MOUSEBUTTONDOWN:
		ne.type = EventType::MouseClick;
		ne.mouseButton.button = ev.button.button;
		ne.mouseButton.x = ev.button.x;
		ne.mouseButton.y = ev.button.y;
		ne.id = ev.button.which;
		ne.window = ev.button.windowID;
		break;

	case SDL_MOUSEBUTTONUP:
		ne.type = EventType::MouseRelease;
		ne.mouseButton.button = ev.button.button;
		ne.mouseButton.x = ev.button.x;
		ne.mouseButton.y = ev.button.y;
		ne.id = ev.button.which;
		ne.window = ev.button.windowID;
		break;

	case SDL_MOUSEWHEEL:
		ne.type = EventType::MouseWheel;
		ne.scroll.x = ev.wheel.x;
		ne.scroll.y = ev.wheel.y;
		ne.id = ev.wheel.which;
		ne.window = ev.wheel.windowID;
		break;

	case SDL_JOYAXISMOTION:
		ne.type = EventType::JoystickAxis;
		ne.cjAxis.axis = ev.jaxis.axis;
		ne.cjAxis.value = ev.jaxis.value;
		ne.id = ev.jaxis.which;
		break;

	case SDL_JOYBALLMOTION:
		ne.type = EventType::JoystickBall;
		ne.ball.ballIndex = ev.jball.ball;
		ne.ball.x = ev.jball.xrel;
		ne.ball.y = ev.jball.yrel;
		ne.id = ev.jball.which;
		break;

	case SDL_JOYHATMOTION:
		ne.type = EventType::JoystickHat;
		ne.hat.hatIndex = ev.jhat.hat;
		ne.hat.value = ev.jhat.value;
		ne.id = ev.jhat.which;
		break;

	case SDL_JOYBUTTONDOWN:
		ne.type = EventType::JoystickButtonDown;
		ne.cjButton.button = ev.jbutton.button;
		ne.id = ev.jbutton.which;
		break;

	case SDL_JOYBUTTONUP:
		ne.type = EventType::JoystickButtonUp;
		ne.cjButton.button = ev.jbutton.button;
		ne.id = ev.jbutton.which;
		break;

	case SDL_JOYDEVICEADDED:
		ne.type = EventType::JoystickAdded;
		ne.id = ev.jdevice.which;
		break;

	case SDL_JOYDEVICEREMOVED:
		ne.type = EventType::JoystickRemoved;
		ne.id = ev.jdevice.which;
		break;

	case SDL_CONTROLLERAXISMOTION:
		ne.type = EventType::ControllerAxis;
		ne.cjAxis.axis = ev.caxis.axis;
		ne.cjAxis.value = ev.caxis.value;
		ne.id = ev.caxis.which;
		break;

	case SDL_CONTROLLERBUTTONDOWN:
		ne.type = EventType::ControllerButtonDown;
		ne.cjButton.button = ev.cbutton.button;
		ne.id = ev.cbutton.which;
		break;

	case SDL_CONTROLLERBUTTONUP:
		ne.type = EventType::ControllerButtonUp;
		ne.cjButton.button = ev.cbutton.button;
		ne.id = ev.cbutton.which;
		break;

	case SDL_CONTROLLERDEVICEADDED:
		ne.type = EventType::ControllerAdded;
		ne.id = ev.cdevice.which;
		break;

	case SDL_CONTROLLERDEVICEREMOVED:
		ne.type = EventType::ControllerRemoved;
		ne.id = ev.cdevice.which;
		break;

	case SDL_DROPFILE:
		ne.type = EventType::DropFile;
		ne.file = ev.drop.file;
		break;

	case SDL_USEREVENT:
		ne.type = EventType::User;
		ne.user.code = ev.user.code;
		ne.user.data1 = ev.user.data1;
		ne.user.data2 = ev.user.data2;
		break;
	}

	if (ne.type == EventType::KeyDown)
	{
		Input::setKey(ne.keyboard.keyCode, true);
	}
	else if (ne.type == EventType::KeyUp)
	{
		Input::setKey(ne.keyboard.keyCode, false);
	}

	if (ne.type == EventType::MouseMove)
	{
		Input::setRelativeMouse(ne.mouseMove.relativeX, ne.mouseMove.relativeY);
		Input::setMousePos(ne.mouseMove.destinationX, ne.mouseMove.destinationY);
	}
	else
	{
		Input::setRelativeMouse(0, 0);
	}

	if (ne.type == EventType::MouseClick)
	{
		Input::setMouseButton(ne.mouseButton.button, true);
		Input::setMousePos(ne.mouseButton.x, ne.mouseButton.y);
	}
	else if (ne.type == EventType::MouseRelease)
	{
		Input::setMouseButton(ne.mouseButton.button, false);
		Input::setMousePos(ne.mouseButton.x, ne.mouseButton.y);
	}

	*e = ne;
	return true;
}

void Enco3D::Core::GLWindow::postQuitMessage()
{
	SDL_Event e;
	e.type = SDL_QUIT;
	SDL_PushEvent(&e);
}

bool Enco3D::Core::GLWindow::update()
{
	SDL_GL_SwapWindow(m_window);

	return m_running;
}