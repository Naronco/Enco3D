#ifndef _ENCO3D_IMAGEIO_H_
#define _ENCO3D_IMAGEIO_H_

#include <string>
#include "DLLExport.h"

namespace Enco3D
{
	namespace IO
	{
		typedef struct DLL_EXPORT __ImageIO_Output
		{
			std::string filename;
			unsigned int width, height;
			float *pixels;
		} ImageIO_Output;

		class DLL_EXPORT ImageIO
		{
		public:
			static void loadImage(const std::string &filename, __ImageIO_Output *output);
			static void freeImage(__ImageIO_Output *output);
		};
	}
}

#endif