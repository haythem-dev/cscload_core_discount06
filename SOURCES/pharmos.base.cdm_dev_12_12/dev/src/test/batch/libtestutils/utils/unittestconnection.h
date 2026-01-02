//----------------------------------------------------------------------------
/*! \file unittestconnection.h
*  \brief connection class for a database in case of unit tests
*  \author	Stefan Suffa
*  \date 30.01.2008
*/
//----------------------------------------------------------------------------

#ifndef GUARD_LIBTEST_UNITTEST_CONNECTION_H
#define GUARD_LIBTEST_UNITTEST_CONNECTION_H

#include <libbasardbsql_connectionref.h>
#include <libbasardbaspect.h>
#include <libbasardbsql_databaseinfo.h>

namespace basar
{
	namespace db
	{
		namespace aspect
		{
			class ConnectionRef;
		}
		namespace sql
		{
			class ConnectionRef;
		}
	}
}


namespace test
{
namespace utils
{
	class UnitTestConnection
	{
	public:	
		/*!
		\brief Default constructor.
		*/
		UnitTestConnection();

		/*!
		\brief Destructor.
		*/
		virtual ~UnitTestConnection();

		/*!
		\brief Open the connection to the database for a given project.
		\see disconnect().
		*/
		void connect(const basar::I18nString& projectName //!< Name of the project to open unittest connection for.
			);

		/*!
		\brief Close a connection to a database.
		\see connect().
		*/
		void disconnect();

		/*!
		\brief Returns the active database connection created using connect().
		*/
		basar::db::aspect::ConnectionRef	getCurrentConnection() const;

		/*!
		\brief Returns the sql connection for the active database connection<BR>
		created using connect().
		*/
		basar::db::sql::ConnectionRef		getSqlConnection() const;
	private:
		basar::db::aspect::ConnectionRef::DatabaseInfo	m_DbInfo;		//!< info to active connection
		basar::db::aspect::ConnectionRef				m_ActivConn;	//!< reference to active connection

		/*!
		\brief Logon to database (using username UnitTest and branch number 90)
		*/
		void setDbInfo(const basar::I18nString& projectName //!< Name of the project to create connection for.
			);

		/*!
		\brief Create an output for an error message.
		*/
		basar::I18nString createMsg(const basar::I18nString& msg) const;
	};
}
}
#endif
