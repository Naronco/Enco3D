#ifndef _ENCO3D_MOUSELOCK_H_
#define _ENCO3D_MOUSELOCK_H_

#include "IGameComponent.h"
#include "FreeMove.h"
#include "FreeLook.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Component
	{
		class DLL_EXPORT MouseLock : public Core::IGameComponent
		{
		private:
			bool m_mouseLocked{ false };

		public:
			void update();
		};
	}
}

#endif