#ifndef _ENCO3D_CONFIG_H_
#define _ENCO3D_CONFIG_H_

#include <string>
#include <fstream>
#include <streambuf>
#include "DLLExport.h"

namespace Enco3D
{
	namespace IO
	{
		namespace ConfigType
		{
			enum DLL_EXPORT ConfigTypes
			{
				JSON
			};
		}

		class DLL_EXPORT Config
		{
		public:
			Config(const std::string& content, ConfigType::ConfigTypes type);
			~Config();

			static Config FromFile(const std::string& file, ConfigType::ConfigTypes type);

		protected:
			ConfigType::ConfigTypes configType;
		};
	}
}
#endif