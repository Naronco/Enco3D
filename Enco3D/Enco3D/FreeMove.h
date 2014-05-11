#ifndef _ENCO3D_FREEMOVE_H_
#define _ENCO3D_FREEMOVE_H_

#include "IGameComponent.h"

namespace Enco3D
{
	namespace Component
	{
		class FreeMove : public Core::IGameComponent
		{
		private:
			float m_moveSpeed{ 0.01f };
			bool m_movingEnabled{ true };
			unsigned int m_moveForwardKey{ Core::Keyboard::W };
			unsigned int m_moveBackwardKey{ Core::Keyboard::S };
			unsigned int m_moveLeftKey{ Core::Keyboard::A };
			unsigned int m_moveRightKey{ Core::Keyboard::D };

		public:
			FreeMove();
			FreeMove(float moveSpeed);

			void Update();

			inline void SetMovingEnabled(bool enabled) { m_movingEnabled = enabled; }

			inline void SetMoveSpeed(float moveSpeed) { m_moveSpeed = moveSpeed; }
			inline void SetMoveForwardKey(unsigned int key) { m_moveForwardKey = key; }
			inline void SetMoveBackwardKey(unsigned int key) { m_moveBackwardKey = key; }
			inline void SetMoveLeftKey(unsigned int key) { m_moveLeftKey = key; }
			inline void SetMoveRightKey(unsigned int key) { m_moveRightKey = key; }

			inline float GetMoveSpeed() const { return m_moveSpeed; }
			inline unsigned int GetMoveForwardKey() const { return m_moveForwardKey; }
			inline unsigned int GetMoveBackwardKey() const { return m_moveBackwardKey; }
			inline unsigned int GetMoveLeftKey() const { return m_moveLeftKey; }
			inline unsigned int GetMoveRightKey() const { return m_moveRightKey; }
		};
	}
}

#endif