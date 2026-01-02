//----------------------------------------------------------------------------
/*! \file unittestconnection.cpp
*  \brief connection class for a database in case of unit tests
*  \author	Stefan Suffa
*  \date 30.01.2008
*/
//----------------------------------------------------------------------------
#include "unittestconnection.h"
#include <libbasarlogin.h>



namespace test
{
namespace utils
{
	UnitTestConnection::UnitTestConnection()
	{
	}

	UnitTestConnection::~UnitTestConnection()
	{
		disconnect(); // error because of reference counter
	}

	void UnitTestConnection::connect(const basar::I18nString& projectName)
	{
		setDbInfo(projectName);
		m_ActivConn = basar::db::aspect::Manager::getInstance().createConnect(m_DbInfo);
		m_ActivConn.setIsolationLevel(basar::INFX_COMITTEDREAD);
		m_ActivConn.setLockModeWait(basar::WAITSECS, 30);	// 30 secs
	}

	void UnitTestConnection::setDbInfo(const basar::I18nString& projectName)
	{
		basar::VarString loginHost = "zdev21_tcp";  
		basar::VarString loginDb1 = "zpcua1";
		basar::VarString loginDb2 = "zpcua2";

		projectName;

		basar::login::Manager::getInstance().setConnectionConfig(	loginHost,
			loginHost,
			loginDb1,
			loginDb2);

		// name of parameters in user-administration
		const basar::Int16 BRANCHNO = 90;
		const basar::I18nString HOST = "HOST";
		const basar::I18nString DB = "DB";
		const basar::I18nString APPLICATIONNAME = "UNITTEST";
		const basar::I18nString USERNAME_UNITTEST = "unittest";
		const basar::I18nString PASSWORD_UNITTEST = "U|U`CxGz";

		basar::I18nString branch;
		branch.format("%d", BRANCHNO);

		// variables where parameters for host and database are put in
		basar::I18nString hostVal;			
		basar::I18nString databaseVal;

		basar::I18nString applicationName(APPLICATIONNAME);
		if(false == basar::login::Manager::getInstance().nonInteractiveLogin(
															applicationName,
															USERNAME_UNITTEST,
															PASSWORD_UNITTEST,
															BRANCHNO))
		{
#ifdef WIN32
			basar::I18nString msg = createMsg(basar::I18nString("Login failed for " + USERNAME_UNITTEST));
			std::cout << msg << std::endl;
			throw(std::exception(msg.c_str()));
#else
			throw(std::exception());
#endif
		}

		// ask login for parameters -> libbasarlogin has to be called before opening connection for irm
		if ( basar::login::Manager::getInstance().getParaValue(HOST, hostVal) == false ) {
#ifdef WIN32
			basar::I18nString msg = createMsg(basar::I18nString("No entry " + HOST + " for user " + USERNAME_UNITTEST));
			std::cout << msg << std::endl;
			throw(std::exception(msg.c_str()));
#else
			throw(std::exception());
#endif
		}
		projectName;
		if ( basar::login::Manager::getInstance().getParaValue( projectName , DB, databaseVal) == false ){
#ifdef WIN32
			basar::I18nString msg = createMsg(basar::I18nString("No entry " + DB + " for user " + USERNAME_UNITTEST));
			std::cout << msg << std::endl;
			throw(std::exception(msg.c_str()));
#else
			throw(std::exception());
#endif
		}

		m_DbInfo.eConnectType = basar::INFORMIX;
		m_DbInfo.dbServer			= hostVal;
		m_DbInfo.database			= databaseVal;
	}

	void UnitTestConnection::disconnect()
	{
		if ( !m_ActivConn.isNull() ){							
			m_ActivConn.close();			
		}
	}

	basar::db::aspect::ConnectionRef UnitTestConnection::getCurrentConnection() const
	{
		return m_ActivConn;
	}

	basar::db::sql::ConnectionRef UnitTestConnection::getSqlConnection() const
	{
		if (!m_ActivConn.isNull())  {
			return m_ActivConn.getSqlConnection();
		} else {
			return basar::db::sql::ConnectionRef();
		}
	}

	basar::I18nString UnitTestConnection::createMsg(const basar::I18nString& msg) const
	{
		const basar::I18nString HEADER = "#########################################\n";
		const basar::I18nString FOOTER = "\n#########################################\n";
		basar::I18nString result;
		result += HEADER;
		result += __FILE__;
		result += ": ";
		result += msg;
		result += FOOTER;

		return(result);
	}
}
}
