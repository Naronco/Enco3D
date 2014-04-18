#ifndef __ENCO3D_ENCO3DDEVICE_H_INCLUDED__
#define __ENCO3D_ENCO3DDEVICE_H_INCLUDED__

#include "EEnco3DDriverTypes.h"
#include "SDimension2.h"
#include "CSceneManager.h"
#include "IGraphicsDevice.h"
#include "CGraphicsDevice_OpenGL15.h"
#include "IPhysicsDevice.h"
#include "CPhysicsDevice_BulletPhysics.h"
#include "IWindow.h"
#include "CWindow_SDL2.h"
#include "CWindow_Win32_OpenGL.h"
#include "Enco3DUtil.h"
#include "CTimer.h"
#include "CFrameCounter.h"

namespace enco
{
	namespace core
	{
		class Enco3DDevice
		{
		private:
			Dimension2u32 m_displayDim;
			IWindow *m_window;
			IGraphicsDevice *m_graphicsDevice;
			IPhysicsDevice *m_physicsDevice;
			CSceneManager *m_sceneManager;
			CTimer *m_timer;
			CFrameCounter *m_frameCounter;
			
		public:
			void create(const char *title, uint8 samples);
			void release();

			bool run();

			template <typename T> inline void setDisplayDim(const Dimension2<T> &dim) { m_displayDim = dim; }
			inline void setWindow(IWindow *window) { m_window = window; }
			inline void setGraphicsDevice(IGraphicsDevice *graphicsDevice) { m_graphicsDevice = graphicsDevice; }
			inline void setPhysicsDevice(IPhysicsDevice *physicsDevice) { m_physicsDevice = physicsDevice; }
			inline void setSceneManager(CSceneManager *sceneManager) { m_sceneManager = sceneManager; }
			inline void setTimer(CTimer *timer) { m_timer = timer; }
			inline void setFrameCounter(CFrameCounter *frameCounter) { m_frameCounter = frameCounter; }

			inline Dimension2u32 getDisplayDim() const { return m_displayDim; }
			inline IWindow *getWindow() const { return m_window; }
			inline IGraphicsDevice *getGraphicsDevice() const { return m_graphicsDevice; }
			inline IPhysicsDevice *getPhysicsDevice() const { return m_physicsDevice; }
			inline CSceneManager *getSceneManager() const { return m_sceneManager; }
			inline CTimer *getTimer() const { return m_timer; }
			inline CFrameCounter *getFrameCounter() const { return m_frameCounter; }
		};

		template <typename T> inline static Enco3DDevice *createDevice(int driverType, const Dimension2<T> &dim, const char *title, uint8 samples)
		{
			Enco3DDevice *device = 0;

			IGraphicsDevice *graphicsDevice = 0;
			IPhysicsDevice *physicsDevice = 0;
			CSceneManager *sceneManager = 0;
			IWindow *window = 0;
			CTimer *timer = 0;
			CFrameCounter *frameCounter = 0;

			device = new Enco3DDevice;

			switch (driverType)
			{
			case eENCO3DDRIVERTYPE_SDL2_OPENGL15:
				window = new CWindow_SDL2;
				graphicsDevice = new CGraphicsDevice_OpenGL15;
				break;

			case eENCO3DDRIVERTYPE_WIN32_OPENGL15:
				window = new CWindow_Win32_OpenGL;
				graphicsDevice = new CGraphicsDevice_OpenGL15;
				break;
			}

			physicsDevice = new CPhysicsDevice_BulletPhysics;
			sceneManager = new CSceneManager;
			timer = new CTimer;
			frameCounter = new CFrameCounter;

			device->setDisplayDim(dim);
			device->setWindow(window);
			device->setGraphicsDevice(graphicsDevice);
			device->setPhysicsDevice(physicsDevice);
			device->setSceneManager(sceneManager);
			device->setTimer(timer);
			device->setFrameCounter(frameCounter);

			device->create(title, samples);

			return device;
		}

		inline static void releaseDevice(Enco3DDevice *device)
		{
			if (!device) return;

			device->release();

			IWindow *window = device->getWindow();
			IGraphicsDevice *graphicsDevice = device->getGraphicsDevice();
			IPhysicsDevice *physicsDevice = device->getPhysicsDevice();
			CSceneManager *sceneManager = device->getSceneManager();
			CTimer *timer = device->getTimer();
			CFrameCounter *frameCounter = device->getFrameCounter();

			__SAFEDELETE(timer);
			__SAFEDELETE(sceneManager);
			__SAFEDELETE(physicsDevice);
			__SAFEDELETE(graphicsDevice);
			__SAFEDELETE(window);
			__SAFEDELETE(frameCounter);

			delete device;
		}
	}
}

#endif