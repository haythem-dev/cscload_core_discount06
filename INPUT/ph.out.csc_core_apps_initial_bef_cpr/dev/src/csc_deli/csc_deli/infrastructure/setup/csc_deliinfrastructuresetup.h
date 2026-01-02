#ifndef GUARD_CSC_DELI_INFRASTRUCTURE_SETUP_CSC_DELIINFRASTRUCTURESETUP_H
#define GUARD_CSC_DELI_INFRASTRUCTURE_SETUP_CSC_DELIINFRASTRUCTURESETUP_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include "infrastructure/setup/icsc_delilogingetterptr.h"
#include "infrastructure/cmdline/csc_delicmdlineevaluatorconstptr.h"
#include <infrastructure/connectionpool/iconnectionpoolptr.h>

#include <libutil/parameter.h>

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace csc_deli
{
namespace infrastructure
{
namespace setup
{
    class CSC_DELIInfrastructureSetup : public libutil::infrastructure::InfrastructureSetupBase
    {
        public:
            CSC_DELIInfrastructureSetup();
	        virtual ~CSC_DELIInfrastructureSetup();
        	    
            void            injectLoginGetter     ( ICSC_DELILoginGetterConstPtr );
            void            injectDBConnectionPool( libcsc_deli::infrastructure::connectionPool::IConnectionPoolPtr );
            void            injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr );

        protected:
            virtual void    doInit();
	        virtual void    doShutdown();
        	    
        private:
            ////////////////////////////////
            // methods
            ////////////////////////////////
            CSC_DELIInfrastructureSetup( const CSC_DELIInfrastructureSetup& r );
	        CSC_DELIInfrastructureSetup& operator = ( const CSC_DELIInfrastructureSetup& r );

            libcsc_deli::infrastructure::connectionPool::IConnectionPoolPtr     getDBConnectionPool() const;
            csc_deli::infrastructure::cmdLine::CSC_DELICmdLineEvaluatorConstPtr getCscDeliCmdLineEvaluator();
            libutil::infrastructure::parameter::IParameterGatewayPtr            getParameterGateway() const;

            void                                                                login();
            void                                                                prepareLogin();

            void                                                                prepareDBConnections();
            void                                                                establishDBConnections();
            void                                                                releaseDBConnections();

            ////////////////////////////////
            // variables
            ////////////////////////////////
            ICSC_DELILoginGetterConstPtr                                        m_CSC_DELILoginGetter;
            libcsc_deli::infrastructure::connectionPool::IConnectionPoolPtr     m_DBConnectionPool;
            libutil::infrastructure::parameter::IParameterGatewayPtr            m_ParameterGateway;
    };
} // end namespace setup
} // end namespace infrastructure
} // end namespace csc_deli

#endif // GUARD_CSC_DELI_INFRASTRUCTURE_SETUP_CSC_DELIINFRASTRUCTURESETUP_H
