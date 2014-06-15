#ifndef _ENCO3D_FREELOOK_H_
#define _ENCO3D_FREELOOK_H_

#include "IGameComponent.h"
#include "MathUtil.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Component
	{
		class DLL_EXPORT FreeLook : public Core::IGameComponent
		{
		private:
			bool m_rotationEnabled{ false };
			float m_rotateSpeed{ 0.05f };

		public:
			FreeLook();
			FreeLook(float rotateSpeed);

			void update();

			inline void setRotationEnabled(bool enabled) { m_rotationEnabled = enabled; }

			inline void setRotateSpeed(float rotateSpeed) { m_rotateSpeed = rotateSpeed; }
			inline float getRotateSpeed() const { return m_rotateSpeed; }
		};
	}
}

#endif