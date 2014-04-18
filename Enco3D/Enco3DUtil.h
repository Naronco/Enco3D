#ifndef __ENCO3D_ENCO3DUTIL_H_INCLUDED__
#define __ENCO3D_ENCO3DUTIL_H_INCLUDED__

#include <stdlib.h>
#include <cstring>
#include <iostream>

#define __ENCO3D_WIN32

#define __SAFEDELETE(x) { if(x) { delete (x); (x) = 0; } }
#define __SAFEDELETEARRAY(x) { if(x) { delete[] (x); (x) = 0; } }

#define __FILLARRAY(a, s, x) { for(unsigned int i = 0; i < s; i++) { a[i] = x; } }

#ifdef __ENCO3D_DEBUG
#	define __ASSERT(a) { if(!(a)) { std::cout << "assertion failed! " << #a << std::endl; exit(1); } }
#else
#	define __ASSERT(a) /* release */
#endif

namespace enco
{
	namespace core
	{
		namespace util
		{
			inline static const wchar_t *getWideChar(const char *c)
			{
				size_t origSize = strlen(c) + 1;
				const size_t newSize = 100;
				size_t convertedChars = 0;
				wchar_t *wcstring = new wchar_t[newSize];
				mbstowcs_s(&convertedChars, wcstring, origSize, c, _TRUNCATE);
				return wcstring;
			}
		}
	}
}

#endif