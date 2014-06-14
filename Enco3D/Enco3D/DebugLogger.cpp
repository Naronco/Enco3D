#include "DebugLogger.h"

Enco3D::Core::DebugLoggerFlag Enco3D::Core::DebugLogger::s_flags;
std::ofstream Enco3D::Core::DebugLogger::s_outputStream;

void Enco3D::Core::DebugLogger::init()
{
	s_outputStream.open("debug.log", std::ios::out);

	s_flags = (DebugLoggerFlag)(WriteToConsole | WriteToFile);
}

void Enco3D::Core::DebugLogger::deinit()
{
	s_outputStream.close();
}

void Enco3D::Core::DebugLogger::log(const std::string &text)
{
	if (isFlagEnabled(WriteToConsole))
		printf((text + "\n").c_str());

	if (isFlagEnabled(WriteToFile))
		s_outputStream.write((text + "\n").c_str(), text.length() + 1);
}