//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       12.06.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTORDERIMPORT_INFRASTRUCTURE_SETUP_IBTORDERIMPORTINFRASTRUCTURESETUP_H
#define GUARD_IBTORDERIMPORT_INFRASTRUCTURE_SETUP_IBTORDERIMPORTINFRASTRUCTURESETUP_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include "infrastructure/setup/iibtorderimportlogingetterptr.h"
#include <persistence/connectionptr.h>
#include "infrastructure/cmdline/ibtorderimportcmdlineevaluator.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace ibtorderimport
{
    namespace infrastructure
    {
        namespace setup
        {
            class IBTORDERIMPORTInfrastructureSetup : public libutil::infrastructure::InfrastructureSetupBase
            {
                public:
                    IBTORDERIMPORTInfrastructureSetup();
	                virtual ~IBTORDERIMPORTInfrastructureSetup();
        	    
                    void injectLoginGetter( IIBTORDERIMPORTLoginGetterConstPtr );
					void injectCscDbConnection( libcsc::persistence::ConnectionPtr ); 
					void injectDbParameterGateway ( libutil::infrastructure::parameter::IParameterGatewayPtr );
					libutil::infrastructure::parameter::IParameterGatewayPtr getDbParameterGateway() const;
					libcsc::persistence::ConnectionPtr getCscDbConnection() const;

                protected:
                    virtual void    doInit();
	                virtual void    doShutdown();
        	    
                private:
                    ////////////////////////////////
                    // methods
                    ////////////////////////////////
                    IBTORDERIMPORTInfrastructureSetup( const IBTORDERIMPORTInfrastructureSetup& r );
	                IBTORDERIMPORTInfrastructureSetup& operator=( const IBTORDERIMPORTInfrastructureSetup& r );

					basar::VarString getDbServer();
					basar::VarString getDatabase();
					const ibtorderimport::infrastructure::cmdLine::AppArgs& getAppArgs();
					
					void establishCscDbConnection();
					void releaseCscDbConnection();

                    void login();
                    void prepareLogin();

                    ////////////////////////////////
                    // variables
                    ////////////////////////////////
                    IIBTORDERIMPORTLoginGetterConstPtr						m_IBTORDERIMPORTLoginGetter;
					libcsc::persistence::ConnectionPtr						m_CscDbConnection;
					libutil::infrastructure::parameter::IParameterGatewayPtr m_DbParameterGateway;
            };
        }
    }
}

#endif
