#include "Config.h"

Enco3D::IO::Config::Config(std::string content, ConfigType::ConfigTypes type)
{
	configType = type;
	if (type == ConfigType::JSON)
	{
		JSONDocument.Parse<0>(content.c_str());
	}
	else if (type == ConfigType::XML)
	{
		XMLDocument.parse<0>((char*)content.c_str());
	}
}

Enco3D::IO::Config::~Config()
{
}

Enco3D::IO::Config Enco3D::IO::Config::FromFile(std::string file, ConfigType::ConfigTypes type)
{
	std::ifstream t(file.c_str());
	std::string content((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return Config(content, type);
}