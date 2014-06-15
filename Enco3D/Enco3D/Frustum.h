#ifndef _ENCO3D_FRUSTUM_H_
#define _ENCO3D_FRUSTUM_H_

#include "Matrix4x4.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Core
	{
		class DLL_EXPORT Frustum
		{
		public:
			Frustum(Matrix4x4f matrix);
			~Frustum();

			inline bool operator == (const Frustum &other) const
			{
				return other.m_matrix == m_matrix;
			}

			inline bool operator != (const Frustum &other) const
			{
				return !(other.m_matrix == m_matrix);
			}

			inline Matrix4x4f getMatrix() const { return m_matrix; }

		protected:

			Matrix4x4f m_matrix;
		};
	}
}
#endif