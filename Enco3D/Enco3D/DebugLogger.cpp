#include "DebugLogger.h"

bool Enco3D::Core::DebugLogger::s_flags[Enco3D::Core::DebugLoggerFlag::NumDebugLoggerFlags];
std::ofstream Enco3D::Core::DebugLogger::s_outputStream;

void Enco3D::Core::DebugLogger::init()
{
	s_outputStream.open("debug.log", std::ios::out);

	s_flags[WriteToConsole] = true;
	s_flags[WriteToFile] = true;
}

void Enco3D::Core::DebugLogger::deinit()
{
	s_outputStream.close();
}

void Enco3D::Core::DebugLogger::log(const std::string &text)
{
	if (s_flags[WriteToConsole])
		std::cout << text << std::endl;

	if (s_flags[WriteToFile])
		s_outputStream << text << std::endl;
}