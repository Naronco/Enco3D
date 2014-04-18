#ifndef _ENCO3D_FIRSTPERSONCONTROLLER_H_
#define _ENCO3D_FIRSTPERSONCONTROLLER_H_

#include "IGameComponent.h"
#include "Input.h"
#include "MathUtil.h"

namespace Enco3D
{
	namespace Component
	{
		using namespace Core;

		class FirstPersonController : public IGameComponent
		{
		private:
			bool m_mouseLocked{ false };
			float m_moveSpeed{ 4.0f };
			float m_rotateSpeed{ 0.1f };

		public:
			FirstPersonController();
			FirstPersonController(float moveSpeed, float rotateSpeed);

			void Update();

			inline void SetMoveSpeed(float moveSpeed) { m_moveSpeed = moveSpeed; }
			inline void SetRotateSpeed(float rotateSpeed) { m_rotateSpeed = rotateSpeed; }

			inline float GetMoveSpeed() const { return m_moveSpeed; }
			inline float GetRotateSpeed() const { return m_rotateSpeed; }
		};
	}
}

#endif