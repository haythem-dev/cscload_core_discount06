//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief declaration of tcaccess connection class
 *  \author Dirk Kapusta
 *  \date 27.01.2009
 *  \version 00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_DBCONNECTION_TCA_CONNECTION_H
#define GUARD_LIBCSC_UTILS_DBCONNECTION_TCA_CONNECTION_H

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
    class TCAConnection : public ::libBatch::dbConnection::DBConnectionBase
    {
        public:	
	        TCAConnection( const basar::db::sql::DatabaseInfo& );
	        virtual ~TCAConnection();            			

        private:
			virtual void doConnect();
            virtual basar::ConnectionTypeEnum getConnectionType() const;

	        TCAConnection( const TCAConnection& );
	        TCAConnection& operator = ( const TCAConnection& );	
       };

} // end namespace libcsc_utils
} // end namespace csc_phatra

#endif // GUARD_LIBCSC_UTILS_DBCONNECTION_TCA_CONNECTION_H

