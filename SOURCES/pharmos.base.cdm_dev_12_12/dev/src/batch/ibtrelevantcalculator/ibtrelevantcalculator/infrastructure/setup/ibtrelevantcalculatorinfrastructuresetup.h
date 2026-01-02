//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       12.06.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IBTRELEVANTCALCULATORINFRASTRUCTURESETUP_H
#define GUARD_IBTRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IBTRELEVANTCALCULATORINFRASTRUCTURESETUP_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include "infrastructure/setup/iibtrelevantcalculatorlogingetterptr.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            class IBTRELEVANTCALCULATORInfrastructureSetup : public libutil::infrastructure::InfrastructureSetupBase
            {
                public:
                    IBTRELEVANTCALCULATORInfrastructureSetup();
	                virtual ~IBTRELEVANTCALCULATORInfrastructureSetup();
        	    
                    void injectLoginGetter( IIBTRELEVANTCALCULATORLoginGetterConstPtr );

                protected:
                    virtual void    doInit();
	                virtual void    doShutdown();
        	    
                private:
                    ////////////////////////////////
                    // methods
                    ////////////////////////////////
                    IBTRELEVANTCALCULATORInfrastructureSetup( const IBTRELEVANTCALCULATORInfrastructureSetup& r );
	                IBTRELEVANTCALCULATORInfrastructureSetup& operator=( const IBTRELEVANTCALCULATORInfrastructureSetup& r );

                    void login();
                    void prepareLogin();

                    ////////////////////////////////
                    // variables
                    ////////////////////////////////
                    IIBTRELEVANTCALCULATORLoginGetterConstPtr m_IBTRELEVANTCALCULATORLoginGetter;
            };
        }
    }
}

#endif
