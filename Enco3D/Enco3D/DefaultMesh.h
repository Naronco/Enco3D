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

			void Render(const Camera *camera, Rendering::Shader *shader);
			void Deinit();

			inline void SetMesh(Rendering::Mesh *mesh) { m_mesh = mesh; }
			inline void SetMaterial(Rendering::Material *material) { m_material = material; }
			
			inline Rendering::Mesh *GetMesh() const { return m_mesh; }
			inline Rendering::Material *GetMaterial() const { return m_material; }
		};
	}
}

#endif