#ifndef _ENCO3D_CONFIG_H_
#define _ENCO3D_CONFIG_H_

#include <string>
#include <fstream>
#include <streambuf>
#include <rapidjson\document.h>

namespace Enco3D
{
	namespace IO
	{
		namespace ConfigType
		{
			enum ConfigTypes
			{
				JSON
			};
		}

		class Config
		{
		public:
			Config(std::string content, ConfigType::ConfigTypes type);
			~Config();

			static Config FromFile(std::string file, ConfigType::ConfigTypes type);

			rapidjson::Document JSONDocument;

		protected:
			ConfigType::ConfigTypes configType;
		};
	}
}
#endif