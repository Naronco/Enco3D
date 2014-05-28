#include "HTTPRequest.h"

Enco3D::Net::HTTPRequest::HTTPRequest() : io(), m_Socket(io), m_IsConnected(false)
{
}

Enco3D::Net::HTTPRequest::~HTTPRequest()
{
	disconnect();
}

void Enco3D::Net::HTTPRequest::connect(const std::string& host, const std::string& port)
{
	m_IsConnected = true;
	m_Host = host;
	try
	{
		boost::asio::ip::tcp::resolver resolver(io);
		boost::asio::ip::tcp::resolver::query query(host, port);
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		boost::asio::connect(m_Socket, endpoint_iterator);
	}
	catch (std::exception e)
	{
		m_IsConnected = false;
	}
}

void Enco3D::Net::HTTPRequest::disconnect()
{
}

void Enco3D::Net::HTTPRequest::setHost(const std::string& host)
{
	m_Host = host;
}

std::string Enco3D::Net::HTTPRequest::getHost()
{
	return m_Host;
}

std::string Enco3D::Net::HTTPRequest::get(const std::string& site)
{
	try
	{
		boost::asio::streambuf sb;
		std::ostream req(&sb);
		req << "GET " << site << " HTTP/1.1\r\n";
		req << "Host: " << m_Host << "\r\n";
		req << "Connection: close\r\n\r\n";
		boost::asio::write(m_Socket, sb);

		boost::asio::streambuf response;

		std::ostringstream ss;
		boost::system::error_code error;

		while (boost::asio::read(m_Socket, response,
			boost::asio::transfer_at_least(1), error))
			ss << &response;
		if (error != boost::asio::error::eof)
			throw boost::system::system_error(error);

		return ss.str();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return "Failed to GET";
}

std::string Enco3D::Net::HTTPRequest::post(const std::string& site, const std::string& content, const std::string& contentType)
{
	boost::asio::streambuf sb;
	std::ostream req(&sb);
	req << "GET " << site << " HTTP/1.0\r\n";
	req << "Host: " << m_Host << "\r\n";
	req << "Connection: close\r\n";
	req << "Content-Type: " << contentType << "\r\n";
	req << "Content-Length: " << content.size() << "\r\n\r\n";
	req << content;
	boost::asio::write(m_Socket, sb);

	boost::asio::streambuf response;
	boost::asio::read_until(m_Socket, response, "\r\n");

	std::istream response_stream(&response);
	std::ostringstream ss;
	ss << response_stream.rdbuf();

	return ss.str();
}

std::string Enco3D::Net::HTTPRequest::head(const std::string& site)
{
	boost::asio::streambuf sb;
	std::ostream req(&sb);
	req << "HEAD " << site << " HTTP/1.0\r\n";
	req << "Host: " << m_Host << "\r\n";
	req << "Connection: close\r\n\r\n";
	boost::asio::write(m_Socket, sb);

	boost::asio::streambuf response;
	boost::asio::read_until(m_Socket, response, "\r\n");

	std::istream response_stream(&response);
	std::ostringstream ss;
	ss << response_stream.rdbuf();

	return ss.str();
}

std::string Enco3D::Net::HTTPRequest::put(const std::string& site, const std::string& content, const std::string& contentType)
{
	boost::asio::streambuf sb;
	std::ostream req(&sb);
	req << "PUT " << site << " HTTP/1.1\r\n";
	req << "Host: " << m_Host << "\r\n";
	req << "Connection: close\r\n";
	req << "Content-Type: " << contentType << "\r\n";
	req << "Content-Length: " << content.size() << "\r\n\r\n";
	req << content;
	boost::asio::write(m_Socket, sb);

	boost::asio::streambuf response;
	boost::asio::read_until(m_Socket, response, "\r\n");

	std::istream response_stream(&response);
	std::ostringstream ss;
	ss << response_stream.rdbuf();

	return ss.str();
}

std::string Enco3D::Net::HTTPRequest::del(const std::string& site)
{
	boost::asio::streambuf sb;
	std::ostream req(&sb);
	req << "DELETE " << site << " HTTP/1.1\r\n";
	req << "Host: " << m_Host << "\r\n";
	req << "Connection: close\r\n\r\n";
	boost::asio::write(m_Socket, sb);

	boost::asio::streambuf response;
	boost::asio::read_until(m_Socket, response, "\r\n");

	std::istream response_stream(&response);
	std::ostringstream ss;
	ss << response_stream.rdbuf();

	return ss.str();
}