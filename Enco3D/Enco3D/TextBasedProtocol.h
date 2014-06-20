#ifndef _ENCO3D_ITEXTBASEDPROTOCOL_H_
#define _ENCO3D_ITEXTBASEDPROTOCOL_H_

#include <string>
#include <boost\asio.hpp>
#include <iostream>
#include "DLLExport.h"
#include "DebugLogger.h"

namespace Enco3D
{
	namespace Net
	{
		class DLL_EXPORT TextBasedProtocol
		{
		public:
			TextBasedProtocol();
			~TextBasedProtocol();

			bool connect(const std::string& host, const std::string& port);
			void disconnect();

			bool sendString(const std::string& msg);
		protected:

			std::string m_Host;
			boost::asio::io_service io;
			boost::asio::ip::tcp::socket m_Socket;
		};
	}
}
#endif