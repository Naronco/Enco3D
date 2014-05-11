#ifndef _ENCO3D_DIRECTIONALLIGHT_H_
#define _ENCO3D_DIRECTIONALLIGHT_H_

#include "ILight.h"
#include "Skybox.h"
#include "ShaderPool.h"

namespace Enco3D
{
	namespace Component
	{
		class DirectionalLight : public ILight
		{
		public:
			DirectionalLight()
			{
				m_shader = Rendering::ShaderPool::GetInstance()->GetShader("shaders/forwardDirectionalLight", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
			}
		};
	}
}

#endif