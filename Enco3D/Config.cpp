#include "Config.h"

Enco3D::IO::Config::Config(const std::string& content, ConfigType::ConfigTypes type)
{
	configType = type;
	if (type == ConfigType::JSON)
	{
		if (!JSONReader.parse(content, JSONDocument))
		{
			// Do something critical
		}
	}
}

Enco3D::IO::Config::~Config()
{
}

Enco3D::IO::Config Enco3D::IO::Config::FromFile(const std::string& file, ConfigType::ConfigTypes type)
{
	std::ifstream t(file.c_str());
	std::string content((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return Config(content, type);
}