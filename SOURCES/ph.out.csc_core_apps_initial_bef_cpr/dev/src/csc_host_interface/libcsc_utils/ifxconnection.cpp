//--------------------------------------------------------------------------------------------------//
/*! \file ifxconnection.cpp
 *  \brief definition of informix connection class
 *  \author Dirk Kapusta
 *  \date 27.01.2009
 *  \version 00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
//  include section
//--------------------------------------------------------------------------------------------------//
#include "ifxconnection.h"
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
IfxConnection::IfxConnection( const basar::db::sql::DatabaseInfo& databaseInfo )
: DBConnectionBase( databaseInfo )
{
	METHODNAME_DEF( IfxConnection, IfxConnection )
	BLOG_TRACE_METHOD( m_Logger, fun );

}

/*!	\throw no-throw */
IfxConnection::~IfxConnection()
{
	METHODNAME_DEF( IfxConnection, ~IfxConnection )
	BLOG_TRACE_METHOD( m_Logger, fun );

}

void IfxConnection::doConnect()
{
	METHODNAME_DEF( IfxConnection, connect )
	BLOG_TRACE_METHOD( m_Logger, fun );
        
    setIsolationLevel( basar::INFX_COMITTEDREAD_LASTCOMMITTED );
    const basar::UInt32 seconds = 30;
    setLockModeWait( basar::WAITSECS, seconds );
}

basar::ConnectionTypeEnum IfxConnection::getConnectionType() const
{
    return basar::INFORMIX;
}

} // end namespace dbConnection
} // end namespace libcsc_utils
