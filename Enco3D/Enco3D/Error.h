#ifndef _ENCO3D_ERROR_H_
#define _ENCO3D_ERROR_H_

#include <iostream>

using namespace std;

namespace Enco3D
{
	namespace Core
	{
		enum Error
		{
			Success,
			Failed,
		};

		typedef int ErrorResult;
	}
}

#endif