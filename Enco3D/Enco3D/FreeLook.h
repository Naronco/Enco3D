#ifndef _ENCO3D_FREELOOK_H_
#define _ENCO3D_FREELOOK_H_

#include "IGameComponent.h"
#include "MathUtil.h"

namespace Enco3D
{
	namespace Component
	{
		class FreeLook : public Core::IGameComponent
		{
		private:
			bool m_rotationEnabled{ false };
			float m_rotateSpeed{ 0.05f };

		public:
			FreeLook();
			FreeLook(float rotateSpeed);

			void Update();

			inline void SetRotationEnabled(bool enabled) { m_rotationEnabled = enabled; }

			inline void SetRotateSpeed(float rotateSpeed) { m_rotateSpeed = rotateSpeed; }
			inline float GetRotateSpeed() const { return m_rotateSpeed; }
		};
	}
}

#endif