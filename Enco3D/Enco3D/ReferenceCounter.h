#ifndef _ENCO3D_REFERENCECOUNTER_H_
#define _ENCO3D_REFERENCECOUNTER_H_

#include "DLLExport.h"

namespace Enco3D
{
	namespace Core
	{
		template <typename T>
		class DLL_EXPORT ReferenceCounter
		{
		private:
			T m_refCount;

		public:
			inline ReferenceCounter()
			{
				m_refCount = 1;
			}

			inline void addReference()
			{
				m_refCount++;
			}

			inline bool removeReference()
			{
				return --m_refCount == 0;
			}
		};
	}
}

#endif