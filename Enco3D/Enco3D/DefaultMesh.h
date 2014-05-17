#ifndef _ENCO3D_DEFAULTMESH_H_
#define _ENCO3D_DEFAULTMESH_H_

#include "IGameComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

namespace Enco3D
{
	namespace Component
	{
		class DefaultMesh : public Core::IGameComponent
		{
		private:
			Rendering::Mesh *m_mesh{ nullptr };
			Rendering::Material *m_material{ nullptr };

		public:
			DefaultMesh();
			DefaultMesh(Rendering::Mesh *mesh, Rendering::Material *material);

			void render(const Camera *camera, Rendering::Shader *shader);
			void deinit();

			inline void setMesh(Rendering::Mesh *mesh) { m_mesh = mesh; }
			inline void setMaterial(Rendering::Material *material) { m_material = material; }
			
			inline Rendering::Mesh *getMesh() const { return m_mesh; }
			inline Rendering::Material *getMaterial() const { return m_material; }
		};
	}
}

#endif