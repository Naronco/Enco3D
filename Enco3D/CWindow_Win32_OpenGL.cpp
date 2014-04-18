#include "CWindow_Win32_OpenGL.h"

void enco::core::CWindow_Win32_OpenGL::create(char *title, const enco::core::Dimension2u32 &size, uint8 samples)
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

	uint32 pixelFormat;
	WNDCLASS wndClass;
	DWORD dwExStyle;
	DWORD dwStyle;
	RECT windowRect;

	windowRect.left = (sint64)0;
	windowRect.right = (sint64)size.x;
	windowRect.top = (sint64)0;
	windowRect.bottom = (sint64)size.y;

	const wchar_t *titleWideChar = util::getWideChar(title);

	m_hInstance = GetModuleHandle(NULL);
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = (WNDPROC)__staticWndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = titleWideChar;

	if (!RegisterClass(&wndClass))
	{
		return;
	}

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	dwStyle = WS_OVERLAPPEDWINDOW;

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	uint32 windowSizeX = windowRect.right - windowRect.left;
	uint32 windowSizeY = windowRect.bottom - windowRect.top;
	uint32 windowPosX = (GetSystemMetrics(SM_CXSCREEN) - windowSizeX) >> 1;
	uint32 windowPosY = (GetSystemMetrics(SM_CYSCREEN) - windowSizeY) >> 1;

	m_hWnd = CreateWindowEx(dwExStyle, titleWideChar, titleWideChar, dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, windowPosX, windowPosY, windowSizeX, windowSizeY, NULL, NULL, m_hInstance, NULL);
	if (!m_hWnd)
	{
		return;
	}

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	m_hDC = GetDC(m_hWnd);
	
	pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, pixelFormat, &pfd);

	m_hRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hRC);

	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	glewInit();
}

void enco::core::CWindow_Win32_OpenGL::release()
{
	if (m_hRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hRC);

		m_hRC = NULL;
	}

	if (m_hDC)
	{
		ReleaseDC(m_hWnd, m_hDC);
		m_hDC = NULL;
	}

	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}

	UnregisterClass(NULL, m_hInstance);
	m_hInstance = NULL;
}

void enco::core::CWindow_Win32_OpenGL::update()
{
	static MSG msg;

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			m_closeRequested = true;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	SwapBuffers(m_hDC);
}

void enco::core::CWindow_Win32_OpenGL::show()
{
	ShowWindow(m_hWnd, SW_SHOW);
}

void enco::core::CWindow_Win32_OpenGL::hide()
{
	ShowWindow(m_hWnd, SW_HIDE);
}

void enco::core::CWindow_Win32_OpenGL::setTitle(char *title)
{
	m_title = title;
	SetWindowText(m_hWnd, util::getWideChar(title));
}

void enco::core::CWindow_Win32_OpenGL::setPosition(const enco::core::math::Vector2s32 &position)
{
}

void enco::core::CWindow_Win32_OpenGL::setSize(const enco::core::Dimension2u32 &size)
{
	m_size = size;
}

void enco::core::CWindow_Win32_OpenGL::setCursorPosition(const enco::core::math::Vector2s32 &position)
{
	m_cursorPosition = position;

	POINT pt;
	pt.x = (sint64)m_cursorPosition.x;
	pt.y = (sint64)m_cursorPosition.y;

	ClientToScreen(m_hWnd, &pt);
	SetCursorPos(pt.x, pt.y);
}

void enco::core::CWindow_Win32_OpenGL::setCursor(bool visible)
{
	ShowCursor(visible);
}

LRESULT CALLBACK enco::core::CWindow_Win32_OpenGL::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		m_keys[(sint32)wParam] = true;
		break;

	case WM_KEYUP:
		m_keys[(sint32)wParam] = false;
		break;

	case WM_LBUTTONDOWN:
		m_buttons[0] = true;
		break;

	case WM_LBUTTONUP:
		m_buttons[0] = false;
		break;

	case WM_RBUTTONDOWN:
		m_buttons[1] = true;
		break;

	case WM_RBUTTONUP:
		m_buttons[1] = false;
		break;

	case WM_MBUTTONDOWN:
		m_buttons[2] = true;
		break;

	case WM_MBUTTONUP:
		m_buttons[2] = false;
		break;

	case WM_MOUSEMOVE:
/*		POINT mousePos;
		mousePos.x = LOWORD(lParam);
		mousePos.y = HIWORD(lParam);

		RECT imagePos;
		GetWindowRect(m_hWnd, &imagePos);

		m_cursorPosition.x = mousePos.x - imagePos.left;
		m_cursorPosition.y = mousePos.y - imagePos.top;
		*/
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return 0;
}

static LRESULT CALLBACK enco::core::__staticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return windowPtr->wndProc(hWnd, msg, wParam, lParam);
}