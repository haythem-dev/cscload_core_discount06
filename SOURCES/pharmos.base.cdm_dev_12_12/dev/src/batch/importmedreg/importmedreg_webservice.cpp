//-----------------------------------------------------------------------------------------------------//
//! \file  importmedreg_webservice
// \brief  application class (webservice) for import medreg
// \author Thomas Arnold
// \date   09.05.2022
//-----------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------//
// includes
//-----------------------------------------------------------------------------------------------------//

#include <cstring> // memset
#include <sstream>

#include "importmedreg_webservice.h"

//-----------------------------------------------------------------------------------------------------//
// namespace
//-----------------------------------------------------------------------------------------------------//
namespace importmedreg
{
	//-------------------------------------------------------------------------------------------------//
	//! standard constructor of importmedred webservice
	//-------------------------------------------------------------------------------------------------//
	WebService::WebService() : m_Logger(importmedreg::LoggerPool::getLoggerWebService())
	{
		METHODNAME_DEF(WebService, WebService);
		BLOG_TRACE_METHOD(getLogger(), fun);

		m_intSocket = 0;
		m_blnConnected = false;
		m_strHTTPRequest = "";
		m_strHTTPResponse = "";
		m_strProxyHost = "";
		m_intProxyPort = 0;
		m_strHost = "";
		m_intPort = 0;
		m_blnHTTPS = false;
		m_blnProxy = false;
		m_objSSL = NULL;
		m_intSSLSocket = 0;
		m_strAuthSchema = "";
		m_strCredentials = "";
		m_strProxyAuthSchema = "";
		m_strProxyCredentials = "";
	}

	//-------------------------------------------------------------------------------------------------//
	//! standard destructor of importmedred webservice
	//-------------------------------------------------------------------------------------------------//
	WebService::~WebService()
	{
		METHODNAME_DEF(WebService, ~WebService);
		BLOG_TRACE_METHOD(getLogger(), fun);

		close();
	}

	//-------------------------------------------------------------------------------------------------//
	//! internal function to get the webservice logger
	//-------------------------------------------------------------------------------------------------//
	const log4cplus::Logger& WebService::getLogger() const
	{
		return m_Logger;
	}

	//-------------------------------------------------------------------------------------------------//
	//! set proxy in case if needed
	//-------------------------------------------------------------------------------------------------//
	bool WebService::proxy(std::string proxyhost, int proxyport, std::string authschema, std::string credentials)
	{
		bool ret = true;

		m_strProxyHost = proxyhost;
		m_intProxyPort = proxyport;
		m_strProxyAuthSchema = authschema;
		m_strProxyCredentials = credentials;
		int pos = (int)credentials.find(":", 0);
		if ((authschema.compare("Basic") == 0) && (pos > 0))
		{
			//encode credentials with base64
			m_strProxyCredentials = base64_encode(credentials);
		}
		return ret;
	}

	//-------------------------------------------------------------------------------------------------//
	//! set authorization in case if needed
	//-------------------------------------------------------------------------------------------------//
	bool WebService::authorize(std::string authschema, std::string credentials)
	{
		bool ret = true;

		m_strAuthSchema = authschema;
		m_strCredentials = credentials;
		int pos = (int)credentials.find(":", 0);
		if ((authschema.compare("Basic") == 0) && (pos > 0))
		{
			//encode credentials with base64
			m_strCredentials = base64_encode(credentials);
		}
		return ret;
	}

	//-------------------------------------------------------------------------------------------------//
	//! connect to web service with host and port
	//-------------------------------------------------------------------------------------------------//
	bool WebService::connect(std::string host, int port)
	{
		METHODNAME_DEF(WebService, connect);
		BLOG_TRACE_METHOD(getLogger(), fun);

		bool ret = true;

		m_strHost = host;
		m_intPort = port;
		m_blnHTTPS = false;
		m_blnProxy = false;

#if defined WIN32
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) 
		{
			printf("error at WSAStartup\n");
			return false;
		}

		m_intSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		ret = (m_intSocket >= 0);
#else
		int socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		m_intSocket = socket_fd;
		ret = (-1 != socket_fd);
#endif
		if (ret == false)
		{
			printf("socket creation failed.\n");
			// closesocket(m_intSocket);
			clearSocket();
			return false;
		}

		// Server address construction
		struct sockaddr_in sad;
		std::memset(&sad, 0, sizeof(sad));
		sad.sin_family = AF_INET;
		if ((m_strProxyHost.empty() == false) && (m_intProxyPort > 0))
		{
			m_blnProxy = true;
			struct hostent* phostent = gethostbyname(m_strProxyHost.c_str()); // server name of proxy
			if (phostent != NULL)
			{
				in_addr* address = (in_addr*)phostent->h_addr;
				memcpy(&sad.sin_addr, address, sizeof(in_addr));
			}
			else
			{
				sad.sin_addr.s_addr = inet_addr(m_strProxyHost.c_str()); // server IP of proxy
			}
			sad.sin_port = htons(m_intProxyPort); // Server port of proxy
		}
		else
		{
			printf("Trying to resolve host (%s)...\n", m_strHost.c_str());
			struct hostent* phostent = gethostbyname(m_strHost.c_str()); // server name
			if (phostent != NULL)
			{
				in_addr* address = (in_addr*)phostent->h_addr;
				memcpy(&sad.sin_addr, address, sizeof(in_addr));
			}
			else
			{
				sad.sin_addr.s_addr = inet_addr(m_strHost.c_str()); // server IP
			}
			sad.sin_port = htons(m_intPort); // Server port
		}
		// Connection to the proxy or server
		printf("Trying to connect ip (%s)...\n", inet_ntoa(sad.sin_addr));
		if (::connect(m_intSocket, (struct sockaddr *) &sad, sizeof(sad)) < 0)
		{
			printf("Failed to connect.\n");
			closesocket(m_intSocket);
			clearSocket();
			return false;
		}

		// define timeout for responses
		struct timeval timeout;
#if defined WIN32
		timeout.tv_sec = SOCKET_READ_TIMEOUT_SEC * 1000; // windows expects timeout in milliseconds
#else
		timeout.tv_sec = SOCKET_READ_TIMEOUT_SEC; // linux/unix expects timeout in seconds
#endif
		timeout.tv_usec = 0;
		::setsockopt(m_intSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

		// in case its a proxy then tunnel the connectivity
		if (m_blnProxy == true)
		{
			std::stringstream strm;
			strm << "CONNECT " << m_strHost << ":" << m_intPort << " HTTP/1.1\r\n"
				 << "Host: " << m_strHost << "\r\n"
				 << "Proxy-Connection: keep-alive\r\n"
				 << "Proxy-Authorization: " << m_strProxyAuthSchema << " " << m_strProxyCredentials << "\r\n"
				 << "User-Agent: importmedreg/1.0\r\n"
				 << "Pragma: no-cache\r\nCache-Control: no-cache\r\n\r\n";
			
			std::string httpheader = strm.str();
			int len = (int)httpheader.length();
			if (::send(m_intSocket, httpheader.c_str(), len, 0) != len)
			{
				printf("connection to remote server via proxy not established, send() sent a different number of bytes than expected");
				closesocket(m_intSocket);
				clearSocket();
				return false;
			}
			std::string resp = readResponse();
			int pos = (int)resp.find("HTTP/1.1 200 Connection established");
			if (pos < 0)
			{
				printf("connection to remote server via proxy not established");
				if (m_strProxyAuthSchema.compare("Basic") == 0)
				{
					printf(" with user %s", base64_decode(m_strProxyCredentials).c_str());
				}
				printf(", server returned with %s\r\n", resp.c_str());
				closesocket(m_intSocket);
				clearSocket();
				return false;
			}
		}
		if ((m_intProxyPort == 443) || (m_intPort == 443))
		{
			m_blnHTTPS = true;
		}

		if (m_blnHTTPS == true)
		{
			SSL_library_init();
			SSLeay_add_ssl_algorithms();
			SSL_load_error_strings();
			const SSL_METHOD *meth = TLSv1_2_client_method();
			SSL_CTX *ctx = SSL_CTX_new(meth);
			m_objSSL = SSL_new(ctx);
			if (m_objSSL == NULL)
			{
				printf("Error creating SSL.\n");
				closesocket(m_intSocket);
				clearSocket();
				return false;
			}
			m_intSSLSocket = SSL_get_fd(m_objSSL);
			SSL_set_fd(m_objSSL, (int)m_intSocket);
			int err = SSL_connect(m_objSSL);
			if (err <= 0)
			{
				printf("Error creating SSL connection.  err=%x\n", err);
				closesocket(m_intSocket);
				clearSocket();
				return false;
			}
			printf("SSL connection using %s\n", SSL_get_cipher(m_objSSL));
		}
		m_blnConnected = true;
		return true;
	}

	//-------------------------------------------------------------------------------------------------//
	//! request to webservice with given type (GET, POST) and optionally authentication and body
	//-------------------------------------------------------------------------------------------------//
	bool WebService::request(std::string type, std::string request, std::string body, std::string bodytype)
	{
		METHODNAME_DEF(WebService, request);
		BLOG_TRACE_METHOD(getLogger(), fun);

		bool ret = false;
		if ((m_blnConnected == false) || (m_intSocket == 0))
		{
			printf("request cannot be sent, no connection established.\n");
			return ret;
		}

		std::stringstream strm;
		strm << type << " " << request << " HTTP/1.1\r\n"
			 << "Host: " << m_strHost << "\r\n";

		if (body.empty() == false)
		{
			strm << "Content-Type: " << bodytype << "\r\n"
				 << "Content-Length: " << body.length() << "\r\n";
		}
		strm << "Accept: */*\r\n"
			 << "User-Agent: importmedreg/1.0\r\n";
		if (!m_strAuthSchema.empty() && !m_strCredentials.empty())
		{
			strm << "Authorization: " << m_strAuthSchema << " " << m_strCredentials << "\r\n";
		}
		strm << "Pragma: no-cache\r\n"
			<< "Cache-Control: no-cache\r\n\r\n";

		m_strHTTPRequest = strm.str() + body;

		int len = (int)m_strHTTPRequest.length();

		if (m_blnHTTPS == true)
		{
			// use SSL encryption to send request
			int retval = SSL_write(m_objSSL, m_strHTTPRequest.c_str(), len);
			if (retval < 0)
			{
				int err = SSL_get_error(m_objSSL, retval);
				switch (err)
				{
					case SSL_ERROR_WANT_WRITE:
						err = 0;
					case SSL_ERROR_WANT_READ:
						err = 0;
					case SSL_ERROR_ZERO_RETURN:
					case SSL_ERROR_SYSCALL:
					case SSL_ERROR_SSL:
					default:
						err = -1;
				}
				if (err < 0)
				{
					close();
					return ret;
				}
			}
		}
		else
		{
			// use plain request to send to server
			if (::send(m_intSocket, m_strHTTPRequest.c_str(), len, 0) != len)
			{
				printf("send() sent a different number of bytes than expected");
				close();
				return ret;
			}
		}

		m_strHTTPResponse = readResponse();
		
		ret = true;

		return ret;
	}

	//-------------------------------------------------------------------------------------------------//
	//! read and return the response from server after a request
	//-------------------------------------------------------------------------------------------------//
	std::string WebService::readResponse()
	{
		std::string ret = "";
		int bytesRcvd = 0;
		int totalBytesRcvd = 0;
		m_strHTTPResponse = "";
		char buf[MAX_BUFFER]; // buffer for data from the server

		if ((m_blnHTTPS == true) && (m_objSSL != NULL))
		{
			do
			{
				bytesRcvd = SSL_read(m_objSSL, buf, MAX_BUFFER - 1);
				if (bytesRcvd >= 0)
				{
					totalBytesRcvd += bytesRcvd; // Keep tally of total bytes
					buf[bytesRcvd] = '\0'; // Add \0 so printf knows where to stop
					ret += buf;
				}
			} while (bytesRcvd > 0);

			if (bytesRcvd < 0)
			{
				int err = SSL_get_error(m_objSSL, bytesRcvd);
				if ((err == SSL_ERROR_WANT_READ) || (err == SSL_ERROR_WANT_WRITE))
				{
					err = 0;
				}
				if (err == SSL_ERROR_ZERO_RETURN || err == SSL_ERROR_SYSCALL || err == SSL_ERROR_SSL)
				{
					err = -1;
				}
			}
		}
		else
		{
			do
			{
				bytesRcvd = ::recv(m_intSocket, buf, MAX_BUFFER - 1, 0);
				if (bytesRcvd > 0)
				{
					totalBytesRcvd += bytesRcvd; // Keep tally of total bytes
					buf[bytesRcvd] = '\0'; // Add \0 so printf knows where to stop
					ret += buf;
				}
			} while (bytesRcvd >= (MAX_BUFFER - 1));
		}
		return ret;
	}

	//-------------------------------------------------------------------------------------------------//
	//! returns the last created http request
	//-------------------------------------------------------------------------------------------------//
	std::string WebService::getLastRequest()
	{
		return m_strHTTPRequest;
	}

	//-------------------------------------------------------------------------------------------------//
	//! returns the last received http response
	//-------------------------------------------------------------------------------------------------//
	std::string WebService::getLastResponse()
	{
		return m_strHTTPResponse;
	}

	//-------------------------------------------------------------------------------------------------//
	//! close the importmedreg webservice and resets the data
	//-------------------------------------------------------------------------------------------------//
	bool WebService::close()
	{
		METHODNAME_DEF(WebService, close);
		BLOG_TRACE_METHOD(getLogger(), fun);

		bool ret = false;

		if (m_intSocket > 0)
		{
			if (m_objSSL != NULL)
			{
				SSL_free(m_objSSL);
				m_objSSL = NULL;
			}
			m_intSSLSocket = 0;
			closesocket(m_intSocket);
			clearSocket();
			m_blnConnected = false;
			ret = true;
		}
		return ret;
	}

	//-------------------------------------------------------------------------------------------------//
	//! internal function to clear importmedreg webservice and resets the socket data
	//-------------------------------------------------------------------------------------------------//
	void WebService::clearSocket()
	{
#if defined WIN32
		WSACleanup();
#endif
		m_intSocket = 0;
	}

	std::string WebService::base64_encode(std::string text)
	{
		std::string ret = "";
		int i = 0;
		int j = 0;
		BYTE char_array_3[3];
		BYTE char_array_4[4];

		int buflen = (int)text.length();
		const char* buf = text.c_str();
		while (buflen--)
		{
			char_array_3[i++] = *(buf++);
			if (i == 3)
			{
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for (i = 0; (i <4); i++)
				{
					ret += BASE64_CHARS[char_array_4[i]];
				}
				i = 0;
			}
		}

		if (i)
		{
			for (j = i; j < 3; j++)
			{
				char_array_3[j] = '\0';
			}
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (j = 0; (j < i + 1); j++)
			{
				ret += BASE64_CHARS[char_array_4[j]];
			}
			while ((i++ < 3))
			{
				ret += '=';
			}
		}
		return ret;
	}

	std::string WebService::base64_decode(std::string text)
	{
		std::string ret = "";
		int in_len = (int)text.size();
		int i = 0;
		int j = 0;
		int in_ = 0;
		BYTE char_array_4[4], char_array_3[3];

		while ((in_len--) && (text[in_] != '=') && ((isalnum(text[in_])) || (text[in_] == '+') || (text[in_] == '/')))
		{
			char_array_4[i++] = text[in_]; in_++;
			if (i == 4)
			{
				for (i = 0; i < 4; i++)
				{
					char_array_4[i] = (BYTE)BASE64_CHARS.find(char_array_4[i]);
				}
				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

				for (i = 0; (i < 3); i++)
				{
					ret += char_array_3[i];
				}
				i = 0;
			}
		}
		if (i)
		{
			for (j = i; j < 4; j++)
			{
				char_array_4[j] = 0;
			}
			for (j = 0; j < 4; j++)
			{
				char_array_4[j] = (BYTE)BASE64_CHARS.find(char_array_4[j]);
			}
			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (j = 0; (j < i - 1); j++)
			{
				ret += char_array_3[j];
			}
		}
		return ret;
	}
}
