#ifndef __ENCO3D_CFRAMECOUNTER_H_INCLUDED__
#define __ENCO3D_CFRAMECOUNTER_H_INCLUDED__

#include "Enco3DDatatypes.h"
#include "CTimer.h"

namespace enco
{
	namespace core
	{
		class CFrameCounter
		{
		private:
			CTimer *m_timer;
			uint32 m_lastFrameTime;
			uint32 m_frameCount, m_framesPerSecond;
			bool m_printFpsInConsoleEnabled;

		public:
			void create(CTimer *timer);
			void release();

			void update();

			inline void setPrintFpsInConsoleEnabled(bool printFpsInConsoleEnabled) { m_printFpsInConsoleEnabled = printFpsInConsoleEnabled; }

			inline uint32 getFrameCount() const { return m_frameCount; }
			inline uint32 getFramesPerSecond() const { return m_framesPerSecond; }
			inline bool isPrintFpsInConsoleEnabled() const { return m_printFpsInConsoleEnabled; }
		};
	}
}

#endif