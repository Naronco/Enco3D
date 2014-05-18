#ifndef _ENCO3D_DEFAULTMESH_H_
#define _ENCO3D_DEFAULTMESH_H_

#include "IGameComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include <memory>

namespace Enco3D
{
	namespace Component
	{
		class DefaultMesh : public Core::IGameComponent
		{
		private:
			std::shared_ptr<Rendering::Mesh> m_mesh;
			std::shared_ptr<Rendering::Material> m_material;

		public:
			DefaultMesh();
			DefaultMesh(Rendering::Mesh *mesh, Rendering::Material *material);

			void render(const Camera *camera, Rendering::Shader *shader);

			inline std::shared_ptr<Rendering::Mesh> getMesh() const { return m_mesh; }
			inline std::shared_ptr<Rendering::Material> getMaterial() const { return m_material; }
		};
	}
}

#endif