#include "HTTPRequest.h"

Enco3D::Net::HTTPRequest::HTTPRequest()
{
}

Enco3D::Net::HTTPRequest::~HTTPRequest()
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
	std::ostringstream req;
	req << "GET " << site << " HTTP/1.1\r\n";
	req << "Host: " << m_Host << "\r\n";
	req << "Connection: close\r\n\r\n";
	if (!sendString(req.str())) return "Failed to GET";

	boost::asio::streambuf response;
	boost::system::error_code error;
	std::ostringstream ss;

	int headerLength = boost::asio::read_until(m_Socket, response, "\r\n\r\n", error);
	if (error && error != boost::asio::error::eof)
		throw boost::system::system_error(error);
	ss << &response;

	return ss.str().substr(headerLength);
}

std::string Enco3D::Net::HTTPRequest::post(const std::string& site, const std::string& content, const std::string& contentType)
{
	std::ostringstream req;
	req << "POST " << site << " HTTP/1.1\r\n";
	req << "Host: " << m_Host << "\r\n";
	req << "Connection: close\r\n";
	req << "Content-Type: " << contentType << "\r\n";
	req << "Content-Length: " << content.size() << "\r\n\r\n";
	req << content;
	if (!sendString(req.str())) return "Failed to POST";

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
	std::ostringstream req;
	req << "HEAD " << site << " HTTP/1.1\r\n";
	req << "Host: " << m_Host << "\r\n";
	req << "Connection: close\r\n\r\n";
	if (!sendString(req.str())) return "Failed to HEAD";

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
	std::ostringstream req;
	req << "PUT " << site << " HTTP/1.1\r\n";
	req << "Host: " << m_Host << "\r\n";
	req << "Connection: close\r\n";
	req << "Content-Type: " << contentType << "\r\n";
	req << "Content-Length: " << content.size() << "\r\n\r\n";
	req << content;
	if (!sendString(req.str())) return "Failed to PUT";

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
	std::ostringstream req;
	req << "DELETE " << site << " HTTP/1.1\r\n";
	req << "Host: " << m_Host << "\r\n";
	req << "Connection: close\r\n\r\n";
	if (!sendString(req.str())) return "Failed to DELETE";

	boost::asio::streambuf response;
	boost::system::error_code error;
	std::ostringstream ss;

	int headerLength = boost::asio::read_until(m_Socket, response, "\r\n\r\n", error);
	if (error && error != boost::asio::error::eof)
		throw boost::system::system_error(error);
	ss << &response;

	return ss.str().substr(headerLength);
}