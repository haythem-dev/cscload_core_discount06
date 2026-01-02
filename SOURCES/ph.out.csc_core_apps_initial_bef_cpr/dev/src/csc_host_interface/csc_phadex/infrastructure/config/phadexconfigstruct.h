#ifndef GUARD_LIBCSC_PHADEX_CONFIG_STRUCT_H
#define GUARD_LIBCSC_PHADEX_CONFIG_STRUCT_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include <iostream>

namespace csc_phadex
{
namespace infrastructure
{
struct PhadexConfigStruct
{
	basar::VarString	country;
	basar::Int16		branchno;
	basar::Int32		pollInterval;
	basar::VarString	logLevel;
	bool				test;
	basar::Int32		maxSelect;
	basar::VarString	smtpHost;
	basar::Int16		smtpPort;
	basar::VarString	smtpFromEmail;
	basar::VarString	smtpInfoEmail;
	basar::VarString	smtpWarningEmail;
	basar::VarString	smtpErrorEmail;
	bool				noCICS;
	basar::VarString	tcaTransaction;
	basar::VarString	tcaHost;
	basar::Int32		tcaConnectionRetries;
	basar::Int32		tcaConnectionWaitBeforeRetry;
	basar::VarString	tcaUsername;
	basar::VarString	tcaPassword;
	basar::VarString	tcaIPAddress;
	basar::Int16		tcaPort;
	basar::Int32		ifxConnectionRetries;
	basar::Int32		ifxConnectionWaitBeforeRetry;
	basar::VarString	ifxServiceName;
	basar::VarString	ifxHost;
	basar::VarString	ifxDatabase;
	basar::Int16		deviceType;
	basar::VarString	deviceName;
	basar::VarString	messageFile;

	PhadexConfigStruct() :
	country( "" ),
	branchno( 0 ),
	pollInterval( 0 ),
	logLevel( "" ),
	test( false ),
	maxSelect( 0 ),
	smtpHost( "" ),
	smtpPort( 0 ),
	smtpFromEmail( "" ),
	smtpInfoEmail( "" ),
	smtpWarningEmail( "" ),
	smtpErrorEmail( "" ),
	noCICS( false ),
	tcaTransaction( "" ),
	tcaHost( "" ),
	tcaConnectionRetries( 0 ),
	tcaConnectionWaitBeforeRetry( 0 ),
	tcaUsername( "" ),
	tcaPassword( "" ),
	tcaIPAddress( "" ),
	tcaPort( 0 ),
	ifxConnectionRetries( 0 ),
	ifxConnectionWaitBeforeRetry( 0 ),
	ifxServiceName( "" ),
	ifxHost( "" ),
	ifxDatabase( "" ),
	deviceType( 0 ),
	deviceName( "" ),
	messageFile ( "" )
	{
	}

	void toStream( std::ostream & stream = std::cout ) const
	{
		stream << "country=<" << country << ">" << std::endl;
		stream << "branchno=<" << branchno << ">" << std::endl;
		stream << "pollInterval=<" << pollInterval << ">" << std::endl;
		stream << "logLevel=<" << logLevel << ">" << std::endl;
		stream << "test=<" << test << ">" << std::endl;
		stream << "maxSelect=<" << maxSelect << ">" << std::endl;
		stream << "smtpHost=<" << smtpHost << ">" << std::endl;
		stream << "smtpPort=<" << smtpPort << ">" << std::endl;
		stream << "smtpFromEmail=<" << smtpFromEmail << ">" << std::endl;
		stream << "smtpInfoEmail=<" << smtpInfoEmail << ">" << std::endl;
		stream << "smtpWarningEmail=<" << smtpWarningEmail << ">" << std::endl;
		stream << "smtpErrorEmail=<" << smtpErrorEmail << ">" << std::endl;
		stream << "noCICS=<" << noCICS << ">" << std::endl;
		stream << "tcaTransaction=<" << tcaTransaction << ">" << std::endl;
		stream << "tcaConnectionRetries=<" << tcaConnectionRetries << ">" << std::endl;
		stream << "tcaConnectionWaitBeforeRetry=<" << tcaConnectionWaitBeforeRetry << ">" << std::endl;
		stream << "tcaUsername=<" << tcaUsername << ">" << std::endl;
		stream << "tcaPassword=<" << tcaPassword << ">" << std::endl;
		stream << "tcaIPAddress=<" << tcaIPAddress << ">" << std::endl;
		stream << "tcaPort=<" << tcaPort << ">" << std::endl;
		stream << "ifxConnectionRetries=<" << ifxConnectionRetries << ">" << std::endl;
		stream << "ifxConnectionWaitBeforeRetry=<" << ifxConnectionWaitBeforeRetry << ">" << std::endl;
		stream << "ifxServiceName=<" << ifxServiceName << ">" << std::endl;
		stream << "ifxHost=<" << ifxHost << ">" << std::endl;
		stream << "ifxDatabase=<" << ifxDatabase << ">" << std::endl;
		stream << "deviceType=<" << deviceType << ">" << std::endl;
		stream << "deviceName=<" << deviceName << ">" << std::endl;
		stream << "messageFile=<" << messageFile << ">" << std::endl;
	}
};

} // namespace infrastructure
} // namespace csc_phadex

inline std::ostream & operator<<( std::ostream & stream, const csc_phadex::infrastructure::PhadexConfigStruct & r )
{
	r.toStream( stream );
	return stream;
}

#endif	// GUARD_LIBCSC_PHADEX_CONFIG_STRUCT_H
