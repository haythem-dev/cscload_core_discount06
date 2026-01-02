//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   08.07.2013
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_LONGTERMLACKLOADER_COMPONENTMANAGER_LONGTERMLACKLOADERAPPLCOMPMGR_H
#define GUARD_LONGTERMLACKLOADER_COMPONENTMANAGER_LONGTERMLACKLOADERAPPLCOMPMGR_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/irunnableptr.h>

// uc
#include "iusecasegetter.h"

// libutil
#include <libutil/applcomponent.h>
#include <boost/enable_shared_from_this.hpp>

#include <libutil/accessor.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class ConnectionRef;
        }
    }
}

namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// class declaration setcion
//-------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace componentManager
    {
        class ApplCompMgr : public libutil::componentManager::ApplCompMgrBase,
                            //public IUseCaseGetter,
                            public boost::enable_shared_from_this< ApplCompMgr >
        {
            public:
                ApplCompMgr();
                virtual ~ApplCompMgr();

                /////////////////////////////////////////////////////////////////////
                // use case
                /////////////////////////////////////////////////////////////////////
                libutil::useCase::IRunnablePtr                                          getMainUC();
                void                                                                    injectDBConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr);

            protected:
                virtual void                                                            doClear();

                /////////////////////////////////////////////////////////////////////
                // others
                /////////////////////////////////////////////////////////////////////
                
                
                /////////////////////////////////////////////////////////////////////
                // db connection
                /////////////////////////////////////////////////////////////////////
                /*libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr   getDBConnection();
                basar::db::aspect::ConnectionRef                                        getBasarDBConnection();*/

            private:
                ApplCompMgr( const ApplCompMgr& );
                ApplCompMgr& operator=( const ApplCompMgr& );

                /////////////////////////////////////////////////////////////////////
                // accessors getters
                /////////////////////////////////////////////////////////////////////
                libutil::infrastructure::accessor::IAccessorPtr                         getLongTermLackAccesssor();
                const log4cplus::Logger&                                                getLogger() const;
                libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr   getDBConnectionDataGetter();

            private:
                ///////////////////////////////////////////////////////////////////
                // member variables
                ///////////////////////////////////////////////////////////////////
                const log4cplus::Logger&                                                m_Logger;
                libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr   m_DBConnectionDataGetter;
        };

    } // end namnespace componentManager
} // end namnespace longtermlackloader

#endif
