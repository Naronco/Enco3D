#ifndef __ENCO3D_CCODEDMESH_H_INCLUDED__
#define __ENCO3D_CCODEDMESH_H_INCLUDED__

#include "IMesh.h"

namespace enco
{
	namespace core
	{
		class CCodedMesh : public IMesh
		{
		public:
			void create(uint32 vertexSizeInBytes, void *vertexData, sint32 vertexComponents, uint32 indexSizeInBytes, void *indexData, uint32 indexCount);
			void release();
		};
	}
}

#endif