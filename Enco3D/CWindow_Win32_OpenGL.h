#ifndef __ENCO3D_CWINDOW_WIN32_OPENGL_H_INCLUDED__
#define __ENCO3D_CWINDOW_WIN32_OPENGL_H_INCLUDED__

#include <Windows.h>
#include <GL/glew.h>
#include "IWindow.h"
#include "Enco3DUtil.h"

namespace enco
{
	namespace core
	{
		class CWindow_Win32_OpenGL : public IWindow
		{
		private:
			HDC m_hDC;
			HGLRC m_hRC;
			HWND m_hWnd;
			HINSTANCE m_hInstance;

		public:
			void create(char *title, const Dimension2u32 &size, uint8 samples);
			void release();

			void update();

			void show();
			void hide();

			void setTitle(char *title);
			void setPosition(const math::Vector2s32 &position);
			void setSize(const Dimension2u32 &size);
			void setCursorPosition(const math::Vector2s32 &position);
			void setCursor(bool visible);

			LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		};

		static CWindow_Win32_OpenGL *windowPtr = 0;

		static LRESULT CALLBACK __staticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	}
}

#endif