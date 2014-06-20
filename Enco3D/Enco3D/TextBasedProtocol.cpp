#include "TextBasedProtocol.h"

Enco3D::Net::TextBasedProtocol::TextBasedProtocol() : io(), m_Socket(io)
{
}
Enco3D::Net::TextBasedProtocol::~TextBasedProtocol()
{
}

bool Enco3D::Net::TextBasedProtocol::connect(const std::string& host, const std::string& port)
{
	try
	{
		boost::asio::ip::tcp::resolver resolver(io);
		boost::asio::ip::tcp::resolver::query query(host, port);
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		boost::asio::connect(m_Socket, endpoint_iterator);
		m_Host = host;

		return true;
	}
	catch (std::exception e)
	{
		Core::DebugLogger::log("Error trying to connect to " + host + ": " + e.what());
		return false;
	}
}
void Enco3D::Net::TextBasedProtocol::disconnect()
{
	m_Socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	m_Socket.close();
}

bool Enco3D::Net::TextBasedProtocol::sendString(const std::string& msg)
{
	try
	{
		boost::asio::streambuf sb;
		std::ostream req(&sb);
		req << msg;
		boost::asio::write(m_Socket, sb);
		return true;
	}
	catch (std::exception& e)
	{
		Core::DebugLogger::log("Error sending string: " + (std::string)e.what());
		return false;
	}
}