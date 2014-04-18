#ifndef __ENCO3D_IMESH_H_INCLUDED__
#define __ENCO3D_IMESH_H_INCLUDED__

#include "IGraphicsDevice.h"
#include "Enco3DUtil.h"

namespace enco
{
	namespace core
	{
		class IMesh
		{
		protected:
			IGraphicsDevice *m_graphicsDevice;

			IVertexBuffer *m_vertexBuffer;
			IIndexBuffer *m_indexBuffer;

		public:
			inline void render() { __ASSERT(m_graphicsDevice != 0); m_graphicsDevice->render(m_vertexBuffer, m_indexBuffer); }

			inline void setGraphicsDevice(IGraphicsDevice *graphicsDevice) { m_graphicsDevice = graphicsDevice; }
			inline IGraphicsDevice *getGraphicsDevice() const { return m_graphicsDevice; }
		};
	}
}

#endif