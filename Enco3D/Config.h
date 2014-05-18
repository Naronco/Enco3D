#ifndef _ENCO3D_CONFIG_H_
#define _ENCO3D_CONFIG_H_

#include <string>
#include <fstream>
#include <streambuf>
#include <rapidjson\document.h>
#include <rapidxml\rapidxml.hpp>

namespace Enco3D
{
	namespace IO
	{
		namespace ConfigType
		{
			enum ConfigTypes
			{
				XML,
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
			rapidxml::xml_document<> XMLDocument;

		protected:
			ConfigType::ConfigTypes configType;
		};
	}
}
#endif