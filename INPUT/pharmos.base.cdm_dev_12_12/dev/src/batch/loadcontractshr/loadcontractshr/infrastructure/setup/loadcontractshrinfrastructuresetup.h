//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       12.06.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LOADCONTRACTSHR_INFRASTRUCTURE_SETUP_LOADCONTRACTSHRINFRASTRUCTURESETUP_H
#define GUARD_LOADCONTRACTSHR_INFRASTRUCTURE_SETUP_LOADCONTRACTSHRINFRASTRUCTURESETUP_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include "infrastructure/setup/iloadcontractshrlogingetterptr.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace loadcontractshr
{
    namespace infrastructure
    {
        namespace setup
        {
            class LoadContractsHrInfrastructureSetup : public libutil::infrastructure::InfrastructureSetupBase
            {
                public:
                    LoadContractsHrInfrastructureSetup();
	                virtual ~LoadContractsHrInfrastructureSetup();
        	    
                    void injectLoginGetter( ILoadContractsHrLoginGetterConstPtr );

                protected:
                    virtual void    doInit();
	                virtual void    doShutdown();
        	    
                private:
                    ////////////////////////////////
                    // methods
                    ////////////////////////////////
                    LoadContractsHrInfrastructureSetup( const LoadContractsHrInfrastructureSetup& r );
	                LoadContractsHrInfrastructureSetup& operator=( const LoadContractsHrInfrastructureSetup& r );

                    void login();
                    void prepareLogin();

                    ////////////////////////////////
                    // variables
                    ////////////////////////////////
                    ILoadContractsHrLoginGetterConstPtr m_LoadContractsHrLoginGetter;
            };
        }
    }
}

#endif
