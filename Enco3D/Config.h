#ifndef _ENCO3D_CONFIG_H_
#define _ENCO3D_CONFIG_H_

#include <string>
#include <fstream>
#include <streambuf>
#ifdef JSON
#include <json\json.h>
#endif

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
			Config(const std::string& content, ConfigType::ConfigTypes type);
			~Config();

			static Config FromFile(const std::string& file, ConfigType::ConfigTypes type);

#ifdef JSON
			Json::Value JSONDocument;
			Json::Reader JSONReader;
#endif

		protected:
			ConfigType::ConfigTypes configType;
		};
	}
}
#endif