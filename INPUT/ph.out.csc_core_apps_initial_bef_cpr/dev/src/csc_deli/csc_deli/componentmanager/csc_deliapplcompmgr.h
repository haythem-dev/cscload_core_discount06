#ifndef GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIAPPLCOMPMGR_H
#define GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIAPPLCOMPMGR_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/irunnableptr.h>

// uc
#include "iusecasegetter.h"

// libcsc_deli
#include <componentmanager/libcsc_deliapplcompmgrptr.h>
#include <infrastructure/connectionpool/iconnectionpoolgetterptr.h>

// libutil
#include <libutil/applcomponent.h>
#include <boost/enable_shared_from_this.hpp>

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
namespace csc_deli
{
namespace componentManager
{
    class ApplCompMgr : public libutil::componentManager::ApplCompMgrBase,
                        public IUseCaseGetter,
                        public boost::enable_shared_from_this< ApplCompMgr >
    {
        public:
            ApplCompMgr();
            virtual ~ApplCompMgr();

            //void injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr );
            void injectDBConnectionPool( libcsc_deli::infrastructure::connectionPool::IConnectionPoolGetterPtr );

            /////////////////////////////////////////////////////////////////////
            // use case
            /////////////////////////////////////////////////////////////////////
            libutil::useCase::IRunnablePtr                                          getMainUC();
            virtual libutil::useCase::IRunnablePtr                                  getDebtLimitBatchUC();

        protected:
            virtual void                                                            doClear();

            /////////////////////////////////////////////////////////////////////
            // others
            /////////////////////////////////////////////////////////////////////
                
            /////////////////////////////////////////////////////////////////////
            // sub component manager(s)
            /////////////////////////////////////////////////////////////////////
            libcsc_deli::componentManager::ApplCompMgrPtr                           getLIBCSC_DELIApplCompMgr();

            /////////////////////////////////////////////////////////////////////
            // db connection
            /////////////////////////////////////////////////////////////////////
            libcsc_deli::infrastructure::connectionPool::IConnectionPoolGetterPtr   getDBConnectionPool();

        private:
            ApplCompMgr( const ApplCompMgr& );
            ApplCompMgr& operator = ( const ApplCompMgr& );
            
            //libutil::infrastructure::parameter::IParameterGatewayPtr                getParameterGateway();

        private:
            ///////////////////////////////////////////////////////////////////
            // member variables
            ///////////////////////////////////////////////////////////////////
            const log4cplus::Logger&                                                m_Logger;
            libcsc_deli::componentManager::ApplCompMgrPtr                           m_LIBCSC_DELIApplCompMgr;
            //libutil::infrastructure::parameter::IParameterGatewayPtr                m_ParameterGateway;
            libcsc_deli::infrastructure::connectionPool::IConnectionPoolGetterPtr   m_ConnectionPool;
    };

} // end namespace componentManager
} // end namespace csc_deli

#endif // GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIAPPLCOMPMGR_H
