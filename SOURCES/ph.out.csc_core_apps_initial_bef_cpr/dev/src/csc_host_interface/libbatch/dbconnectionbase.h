//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      declaration of abstract connection base class
 *  \author     Bischof Bjoern
 *  \date       27.01.2009
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBBATCH_DB_CONNECTION_BASE_H
#define GUARD_LIBBATCH_DB_CONNECTION_BASE_H

//--------------------------------------------------------------------------------------------------//
//  include section
//--------------------------------------------------------------------------------------------------//
#include <libbasardbaspect_connectionref.h>
#include <libbasardbsql_databaseinfo.h>
#include <libbasardbsql_connectionref.h>

//--------------------------------------------------------------------------------------------------//
//  forward declaration section
//--------------------------------------------------------------------------------------------------//
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
            class DatabaseInfo;
        }
    }
}

//--------------------------------------------------------------------------------------------------//
//  class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libBatch
{
namespace dbConnection
{
    class DBConnectionBase
    {
        public:    
            virtual                                 ~DBConnectionBase();
            void                                    connect();
            /*virtual bool                            establishConnection();*/
            bool                                    isOpen() const;
            bool                                    isValid() const;
            void                                    disconnect();
            void                                    setIsolationLevel( basar::IsolationLevelEnum eLevel );
            void                                    setLockModeWait( basar::LockModeEnum eMode, basar::UInt32 secs );

            const basar::db::aspect::ConnectionRef  getCurrentConnection        () const;
            const basar::db::sql::DatabaseInfo&     getDBInfo() const;

        private:
            ////////////////////////////////
            // methods
            ////////////////////////////////
        virtual void                                doConnect() = 0;
            virtual basar::ConnectionTypeEnum       getConnectionType() const = 0;
            void logConnect() const;
            void logDisconnect() const;

        protected:
            ////////////////////////////////
            // methods
            ////////////////////////////////
            DBConnectionBase( const basar::db::sql::DatabaseInfo& );

            ////////////////////////////////
            // members
            ////////////////////////////////
            const log4cplus::Logger&                m_Logger;

        private:
            ////////////////////////////////
            // methods
            ////////////////////////////////
            DBConnectionBase( const DBConnectionBase & r );
            DBConnectionBase & operator = ( const DBConnectionBase & r );
            
            ////////////////////////////////
            // members
            ////////////////////////////////
            basar::db::aspect::ConnectionRef    m_ActiveConn;
            basar::db::sql::DatabaseInfo        m_DatabaseInfo;

    };

} // end dbConnection
} // end namespace GUARD_LIBBATCH_CONNECTION_BASE_H

#include "dbconnectionbase.inl"

#endif // GUARD_LIBBATCH_DB_CONNECTION_BASE_H
