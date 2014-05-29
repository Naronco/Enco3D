#include "HTTPRequest.h"

Enco3D::Net::HTTPRequest::HTTPRequest() : io(), m_Socket(io)
{
}

Enco3D::Net::HTTPRequest::~HTTPRequest()
{
}

void Enco3D::Net::HTTPRequest::connect(const std::string& host, const std::string& port)
{
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
	}
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
		boost::system::error_code error;
		std::ostringstream ss;

		int headerLength = boost::asio::read_until(m_Socket, response, "\r\n\r\n", error);
		if (error && error != boost::asio::error::eof)
			throw boost::system::system_error(error);
		ss << &response;

		return ss.str().substr(headerLength);
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
	req << "POST " << site << " HTTP/1.0\r\n";
	req << "Host: " << m_Host << "\r\n";
	req << "Connection: close\r\n";
	req << "Content-Type: " << contentType << "\r\n";
	req << "Content-Length: " << content.size() << "\r\n\r\n";
	req << content;
	boost::asio::write(m_Socket, sb);

	boost::asio::streambuf response;
	boost::system::error_code error;
	std::ostringstream ss;

	int headerLength = boost::asio::read_until(m_Socket, response, "\r\n\r\n", error);
	if (error && error != boost::asio::error::eof)
		throw boost::system::system_error(error);
	ss << &response;

	return ss.str().substr(headerLength);
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
	boost::system::error_code error;
	std::ostringstream ss;

	boost::asio::read_until(m_Socket, response, "\r\n\r\n", error);
	if (error && error != boost::asio::error::eof)
		throw boost::system::system_error(error);
	ss << &response;

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
	boost::system::error_code error;
	std::ostringstream ss;

	int headerLength = boost::asio::read_until(m_Socket, response, "\r\n\r\n", error);
	if (error && error != boost::asio::error::eof)
		throw boost::system::system_error(error);
	ss << &response;

	return ss.str().substr(headerLength);
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
	boost::system::error_code error;
	std::ostringstream ss;

	int headerLength = boost::asio::read_until(m_Socket, response, "\r\n\r\n", error);
	if (error && error != boost::asio::error::eof)
		throw boost::system::system_error(error);
	ss << &response;

	return ss.str().substr(headerLength);
}