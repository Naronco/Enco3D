#ifndef _ENCO3D_DEBUGLOGGER_H_
#define _ENCO3D_DEBUGLOGGER_H_

#include <string>
#include <fstream>
#include <iostream>

namespace Enco3D
{
	namespace Core
	{
		enum DebugLoggerFlag : unsigned char
		{
			WriteToConsole = 1 << 0,
			WriteToFile = 1 << 1,
		};

		class DebugLogger
		{
		private:
			static DebugLoggerFlag s_flags;
			static std::ofstream s_outputStream;

		public:
			static void init();
			static void deinit();

			static void log(const std::string &text);

			static void setFlag(DebugLoggerFlag flag, bool enabled) { if (isFlagEnabled(flag) && !enabled) { s_flags = (DebugLoggerFlag)(s_flags & flag); } else { s_flags = (DebugLoggerFlag)(s_flags | flag); } }
			static bool isFlagEnabled(DebugLoggerFlag flag) { return (s_flags & flag) != 0; }
		};
	}
}

#endif