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
			unsigned int m_moveUpKey{ Core::Keyboard::Space };
			unsigned int m_moveDownKey{ Core::Keyboard::Shift };

		public:
			FreeMove();
			FreeMove(float moveSpeed);

			void update();

			inline void setMovingEnabled(bool enabled) { m_movingEnabled = enabled; }

			inline void setMoveSpeed(float moveSpeed) { m_moveSpeed = moveSpeed; }
			inline void setMoveForwardKey(unsigned int key) { m_moveForwardKey = key; }
			inline void setMoveBackwardKey(unsigned int key) { m_moveBackwardKey = key; }
			inline void setMoveLeftKey(unsigned int key) { m_moveLeftKey = key; }
			inline void setMoveRightKey(unsigned int key) { m_moveRightKey = key; }

			inline float getMoveSpeed() const { return m_moveSpeed; }
			inline unsigned int getMoveForwardKey() const { return m_moveForwardKey; }
			inline unsigned int getMoveBackwardKey() const { return m_moveBackwardKey; }
			inline unsigned int getMoveLeftKey() const { return m_moveLeftKey; }
			inline unsigned int getMoveRightKey() const { return m_moveRightKey; }
		};
	}
}

#endif