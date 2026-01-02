//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief definition of tcaccess connection class
 *  \author Dirk Kapusta
 *  \date 27.01.2009
 *  \version 00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
//  include section
//--------------------------------------------------------------------------------------------------//
#include "tcaconnection.h"
#include "loggerpool.h"
#include <classinfo_macros.h>

//--------------------------------------------------------------------------------------------------//
//  class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
namespace dbConnection
{

/*!	\throw no-throw */
TCAConnection::TCAConnection( const basar::db::sql::DatabaseInfo& databaseInfo )
: DBConnectionBase( databaseInfo )
{
	METHODNAME_DEF( TCAConnection, TCAConnection )
	BLOG_TRACE_METHOD( m_Logger, fun );

}

/*!	\throw no-throw */
TCAConnection::~TCAConnection()
{
	METHODNAME_DEF( TCAConnection, ~TCAConnection )
	BLOG_TRACE_METHOD( m_Logger, fun );

}

void TCAConnection::doConnect()
{
	METHODNAME_DEF( TCAConnection, doConnect )
	BLOG_TRACE_METHOD( m_Logger, fun );
}

basar::ConnectionTypeEnum TCAConnection::getConnectionType() const
{
	return basar::CICS;
}

} // end namespace dbConnection
} // end namespace libcsc_utils
