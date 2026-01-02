//--------------------------------------------------------------------------------------------------//
/*! \file ifxconnection.h
 *  \brief declaration of informix connection class
 *  \author Dirk Kapusta
 *  \date 27.01.2009
 *  \version 00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_DBCONNECTION_IFX_CONNECTION_H
#define GUARD_LIBCSC_UTILS_DBCONNECTION_IFX_CONNECTION_H

//--------------------------------------------------------------------------------------------------//
//  include section
//--------------------------------------------------------------------------------------------------//
#include <dbconnectionbase.h>

//--------------------------------------------------------------------------------------------------//
//  forward declaration section
//--------------------------------------------------------------------------------------------------//
//using basar::db::aspect::ConnectionRef;

//--------------------------------------------------------------------------------------------------//
//  class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
namespace dbConnection
{
    class IfxConnection : public ::libBatch::dbConnection::DBConnectionBase
    {
        public:	
	        IfxConnection( const basar::db::sql::DatabaseInfo& );
	        virtual ~IfxConnection();            

        private:
			virtual void doConnect();
            virtual basar::ConnectionTypeEnum getConnectionType() const;

	        IfxConnection( const IfxConnection& );
	        IfxConnection& operator = ( const IfxConnection& );	
        };

} // end namespace dbConnection
} // end namespace libcsc_utils

#endif // GUARD_LIBCSC_UTILS_DBCONNECTION_IFX_CONNECTION_H

