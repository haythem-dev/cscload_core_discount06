//----------------------------------------------------------------------------
//! \file  importmedreg_webservice.h
// \brief  declarations of webservice for importmedreg
// \author Thomas Arnold
// \date   10.05.2022
//----------------------------------------------------------------------------

#ifndef GUARD_IMPORTMEDREG_WEBSERVICE_H
#define GUARD_IMPORTMEDREG_WEBSERVICE_H

#if _AIX
#define closesocket(fd) ::close(fd)
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#else
#include <winsock.h>
#endif
#include <string>
#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "importmedreg_loggerpool.h"

#if !defined(UINT_PTR) || !defined(BYTE)
#include <stdint.h> // uint8_t, uintptr_t
#endif

#ifndef BYTE
#define BYTE     uint8_t
#endif

#ifndef UINT_PTR
#define UINT_PTR uintptr_t
#endif

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace importmedreg
{
	static const int HTTP_GET = 0;
	static const int HTTP_POST = 1;

	static const int MAX_BUFFER = 1024;

	static const std::string BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	static const int SOCKET_READ_TIMEOUT_SEC = 5;

	class WebService
	{
	public:
		WebService();
		~WebService();

		bool proxy(std::string proxyhost, int proxyport, std::string authschema, std::string credentials);
		bool connect(std::string host, int port);
		bool authorize(std::string authschema, std::string credentials);
		bool request(std::string type, std::string request, std::string body, std::string bodytype);
		bool close();

		std::string getLastRequest();
		std::string getLastResponse();

	private:
		const log4cplus::Logger& getLogger() const;
		void clearSocket();
		std::string readResponse();
		std::string base64_encode(std::string text);
		std::string base64_decode(std::string text);

		const log4cplus::Logger&		m_Logger;
		int								m_intProxyPort;
		std::string						m_strProxyHost;
		std::string						m_strProxyAuthSchema;
		std::string						m_strProxyCredentials;
		int								m_intPort;
		std::string						m_strHost;
		bool							m_blnConnected;
		UINT_PTR						m_intSocket;
		UINT_PTR						m_intSSLSocket;
		std::string						m_strHTTPRequest;
		std::string						m_strHTTPResponse;
		bool							m_blnHTTPS;
		bool							m_blnProxy;
		SSL*							m_objSSL;
		std::string						m_strAuthSchema;
		std::string						m_strCredentials;
	};
}

#endif // GUARD_IMPORTMEDREG_WEBSERVICE_H
