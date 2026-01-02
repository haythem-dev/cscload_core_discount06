//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.07.2015
 */
//----------------------------------------------------------------------------
#ifndef GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_SETUP_IDBCONNECTIONGETTER_H
#define GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_SETUP_IDBCONNECTIONGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/dbconnection.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace setup
        {
            //------------------------------------------------------------------------------//
            // class 
            //------------------------------------------------------------------------------//
            class IDBConnectionGetter
            {
                public:
                    virtual ~IDBConnectionGetter(){};
                    virtual libutil::infrastructure::db::dbConnection::IDBConnectionPtr getDBConnection( libutil::infrastructure::db::dbConnection::DBServerInfo & ) const = 0;
            };
        }
    }
}

#endif
