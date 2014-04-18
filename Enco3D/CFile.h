#ifndef __ENCO3D_CFILE_H_INCLUDED__
#define __ENCO3D_CFILE_H_INCLUDED__

#include <fstream>
#include <iostream>
#include <string>

namespace enco
{
	namespace core
	{
		namespace io
		{
			class CFile
			{
			private:
				std::ifstream m_stream;

			public:
				inline void open(const char *filename) { m_stream.open(filename); }
				inline void close() { m_stream.close(); }

				inline std::string getLine() { static std::string line; std::getline(m_stream, line); return line; }

				inline bool isOpen() const { return m_stream.is_open(); }
				inline bool isValidCursor() const { return m_stream.good(); }
				inline bool isInvalidCursor() const { return !m_stream.good(); }
			};
		}
	}
}

#endif