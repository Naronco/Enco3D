#ifndef _ENCO3D_MESHRENDERER_H_
#define _ENCO3D_MESHRENDERER_H_

#include "IGameComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

namespace Enco3D
{
	namespace Component
	{
		using namespace Core;
		using namespace Rendering;

		class MeshRenderer : public IGameComponent
		{
		private:
			Mesh *m_mesh{ nullptr };
			Material *m_material{ nullptr };

		public:
			MeshRenderer();
			MeshRenderer(Mesh *mesh, Material *material);

			void Render(const Camera *camera, Shader *shader);

			void Deinit();
		};
	}
}

#endif