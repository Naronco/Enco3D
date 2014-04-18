#ifndef _ENCO3D_CONSOLE_H_
#define _ENCO3D_CONSOLE_H_

#include "Enco3DEngine.h"

namespace Enco3D
{
	namespace Core
	{
		namespace Console
		{
			inline static void Print(char *text)
			{
				Enco3DEngine::GetInstance()->Console_Print(text);
			}

			inline static void PrintLine(char *text)
			{
				Enco3DEngine::GetInstance()->Console_PrintLine(text);
			}

			inline static void PrintError(char *text)
			{
				Enco3DEngine::GetInstance()->Console_PrintError(text);
			}
		}
	}
}

#endif