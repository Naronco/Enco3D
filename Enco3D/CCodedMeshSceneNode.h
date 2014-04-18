#ifndef __ENCO3D_CCODEDMESHSCENENODE_H_INCLUDED__
#define __ENCO3D_CCODEDMESHSCENENODE_H_INCLUDED__

#include "ISceneNode.h"
#include "CCodedMesh.h"

namespace enco
{
	namespace core
	{
		class CCodedMeshSceneNode : public ISceneNode
		{
		private:
			CCodedMesh *m_codedMesh;

		public:
			void create(IGraphicsDevice *graphicsDevice);
			void release();

			void render();

			inline void setCodedMesh(CCodedMesh *codedMesh) { m_codedMesh = codedMesh; }
			inline CCodedMesh *getCodedMesh() const { return m_codedMesh; }
		};
	}
}

#endif