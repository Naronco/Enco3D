#ifndef _ENCO3D_GLWINDOW_H_
#define _ENCO3D_GLWINDOW_H_

#include <SDL.h>
#include <GL\glew.h>
#include <iostream>
#include "DLLExport.h"

#include "Event.h"
#include "Input.h"
#include "Texture2D.h"
#include "DebugLogger.h"

namespace Enco3D
{
	namespace Core
	{
		/// <summary>OpenGL window</summary>
		class DLL_EXPORT GLWindow
		{
		private:
			/// <summary>Checks, if the window is running</summary>
			bool m_running{ false };

			/// <summary>Checks, if the window is focused</summary>
			bool m_focused{ false };

			/// <summary>Checks, if the window is in fullscreen</summary>
			bool m_fullscreen{ false };

			/// <summary>Width of the window</summary>
			unsigned int m_width{ 0 };

			/// <summary>Height of the window</summary>
			unsigned int m_height{ 0 };

			/// <summary>Pointer to the SDL window</summary>
			SDL_Window *m_window{ nullptr };

			/// <summary>OpenGL context of the window</summary>
			SDL_GLContext m_context{ nullptr };

		public:
			GLWindow();

			/// <summary>Initializes a new window and creates a new GL context</summary>
			/// <param name="title">Title of the window</param>
			/// <param name="width">Width of the window</param>
			/// <param name="height">Height of the window</param>
			/// <param name="multisampleEnabled"></param>
			/// <param name="aaSamples"></param>
			GLWindow(char *title, unsigned int width, unsigned int height, bool multisampleEnabled, unsigned int aaSamples, const std::string &iconSource);

			/// <summary>Shows the window, if it it's hided</summary>
			void show();

			/// <summary>Hides the window, if it it's shown, but doesn't close it</summary>
			void hide();

			/// <summary>Closes the window and destroys the GL context</summary>
			void close();

			/// <summary>Resizes the window</summary>
			/// <param name="width">New width of the window</param>
			/// <param name="height">New height of the window</param>
			void resize(unsigned int width, unsigned int height);

			/// <summary>Sets the window to fullscreen or to windowed mode</summary>
			/// <param name="fullscreen">If true, the window changes into fullscreen</param>
			void setFullscreen(bool fullscreen);

			/// <summary>Sets the window to a new position</summary>
			/// <param name="x">New x coordinate</param>
			/// <param name="y">New y coordinate</param>
			void setPosition(int x, int y);

			void postQuitMessage();

			/// <summary>Gets a sended event width data</summary>
			/// <param name="e">Pointer to the data to be stored</param>
			bool pollEvent(Event *e);

			/// <summary>Updates the window and polls the event data into the pointer</summary>
			bool update();

			/// <summary>Hides or shows the cursor</summary>
			/// <param name="visible">True = cursor is visible; False = cursor is not visible</param>
			inline void setCursor(bool visible) { SDL_ShowCursor(visible ? 1 : 0); }

			/// <summary>Sets the cursor position relative in the window</summary>
			/// <param name="x">New x coordinate of the cursor</param>
			/// <param name="y">New y coordinate of the cursor</param>
			inline void setCursorPosition(int x, int y) { SDL_WarpMouseInWindow(m_window, x, y); }

			/// <summary>Returns true, if the window is running</summary>
			inline bool isRunning() const { return m_running; }

			/// <summary>Returns true, if the window is focused</summary>
			inline bool isFocused() const { return m_focused; }

			/// <summary>Returns true, if the window is in fullscreen</summary>
			inline bool isFullscreen() const { return m_fullscreen; }

			/// <summary>Returns the width of the window</summary>
			inline unsigned int getWidth() const { return m_width; }

			/// <summary>Returns the height of the window</summary>
			inline unsigned int getHeight() const { return m_height; }

			/// <summary>Returns the pointer to the SDL handle of the window</summary>
			inline SDL_Window *getSDLHandle() const { return m_window; }

			/// <summary>Returns GL context of the window</summary>
			inline SDL_GLContext getSDLGLContext() const { return m_context; }
		};
	}
}

#endif