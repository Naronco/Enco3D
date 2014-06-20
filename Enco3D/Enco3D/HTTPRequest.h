#ifndef _ENCO3D_HTTPREQUEST_H_
#define _ENCO3D_HTTPREQUEST_H_

#include <string>
#include <boost\asio.hpp>
#include <iostream>
#include "DLLExport.h"
#include "TextBasedProtocol.h"

namespace Enco3D
{
	namespace Net
	{
		class DLL_EXPORT HTTPRequest : public TextBasedProtocol
		{
		public:
			HTTPRequest();
			~HTTPRequest();

			void setHost(const std::string& host);
			std::string getHost();

			std::string get(const std::string& site);
			std::string post(const std::string& site, const std::string& content, const std::string& contentType = "application/x-www-form-urlencoded");
			std::string head(const std::string& site);
			std::string put(const std::string& site, const std::string& content, const std::string& contentType = "text/plain");
			std::string del(const std::string& site);
		};
	}
}

#endif