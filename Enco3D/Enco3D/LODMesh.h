#ifndef _ENCO3D_LODMESH_H_
#define _ENCO3D_LODMESH_H_

#include "WavefrontMesh.h"
#include "GameObject.h"

namespace Enco3D
{
	namespace Component
	{
		/// <summary>
		/// WIP - Not working
		/// </summary>
		class LODMesh : public Core::IGameComponent
		{
		public:
			LODMesh();
			/// <summary>
			/// <param name="file">Wavefront file name without extension</param>
			/// <param name="count">LOD Count</param>
			/// <param name="material">Material to render</param>
			/// <summary>
			LODMesh(const std::string& file, int count, Rendering::Material *material);
			~LODMesh();

			void render(const Component::Camera *camera, Rendering::Shader *shader);
			void setup();

			inline void setDistanceDifference(int meters) { m_meshDiff = meters; }
			inline int getDistanceDifference() { return m_meshDiff; }

		protected:
			std::vector<WavefrontMesh*> m_meshes;
			int m_maxMeshes;
			int m_meshDiff = 20;
			bool added = false;
		};
	}
}
#endif