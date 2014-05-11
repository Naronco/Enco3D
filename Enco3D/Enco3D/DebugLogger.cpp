#include "DebugLogger.h"

bool Enco3D::Core::DebugLogger::s_flags[Enco3D::Core::DebugLoggerFlag::NumDebugLoggerFlags];
std::ofstream Enco3D::Core::DebugLogger::s_outputStream;

void Enco3D::Core::DebugLogger::Init()
{
	s_outputStream.open("debug.log", std::ios::out);

	s_flags[WriteToConsole] = true;
	s_flags[WriteToFile] = true;
}

void Enco3D::Core::DebugLogger::Deinit()
{
	s_outputStream.close();
	std::cout << "HALLO 2" << std::endl;
}

void Enco3D::Core::DebugLogger::Log(const std::string &text)
{
	if (s_flags[WriteToConsole])
		std::cout << text << std::endl;

	if (s_flags[WriteToFile])
		s_outputStream << text << std::endl;
}