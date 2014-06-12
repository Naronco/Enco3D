#ifndef _ENCO3D_BILLBOARD_H_
#define _ENCO3D_BILLBOARD_H_

#include "IGameComponent.h"

namespace Enco3D
{
	namespace Component
	{
		class Billboard : public Core::IGameComponent
		{
		public:
			Billboard();
			~Billboard();

			/// <summary>WIP</summary>
			bool m_lockY{ false };

			void render(const Component::Camera *camera, Rendering::Shader *shader);
		protected:
		};
	}
}
#endif