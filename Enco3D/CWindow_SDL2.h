#ifndef __ENCO3D_CWINDOWSDL2_H_INCLUDED__
#define __ENCO3D_CWINDOWSDL2_H_INCLUDED__

#include <SDL.h>
#include <GL/glew.h>
#include "IWindow.h"
#include "Enco3DUtil.h"

namespace enco
{
	namespace core
	{
		class CWindow_SDL2 : public IWindow
		{
		private:
			SDL_Window *m_window;
			SDL_GLContext m_context;

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
		};
	}
}

#endif