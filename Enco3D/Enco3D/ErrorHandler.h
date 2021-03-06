#ifndef _ENCO3D_ERRORHANDLER_H_
#define _ENCO3D_ERRORHANDLER_H_

#include <string>
#include "DLLExport.h"

namespace Enco3D
{
	namespace Core
	{
		class Enco3DEngine;
	}
}

namespace Enco3D
{
	namespace Core
	{
		class DLL_EXPORT ErrorHandler
		{
		private:
			std::string m_errorPrefix{ std::string("[ERROR]") };
			Enco3DEngine *m_engine{ nullptr };

		public:
			ErrorHandler(Enco3DEngine *engine);

			void logError(const std::string &errorText);
			bool logErrorAndShutdown(const std::string &errorText, bool forceShutdown = true);
			void logErrorAndForceQuit(const std::string &errorText);

			inline void setEngine(Enco3DEngine *engine) { m_engine = engine; }
			inline void changeErrorPrefix(const std::string &errorPrefix) { m_errorPrefix = errorPrefix; }
		};
	}
}

#endif