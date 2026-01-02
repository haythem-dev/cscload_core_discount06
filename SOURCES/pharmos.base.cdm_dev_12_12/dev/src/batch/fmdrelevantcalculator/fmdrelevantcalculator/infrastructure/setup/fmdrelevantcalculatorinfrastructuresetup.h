//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       12.06.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_FMDRELEVANTCALCULATORINFRASTRUCTURESETUP_H
#define GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_FMDRELEVANTCALCULATORINFRASTRUCTURESETUP_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include "infrastructure/setup/ifmdrelevantcalculatorlogingetterptr.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            class FMDRELEVANTCALCULATORInfrastructureSetup : public libutil::infrastructure::InfrastructureSetupBase
            {
                public:
                    FMDRELEVANTCALCULATORInfrastructureSetup();
	                virtual ~FMDRELEVANTCALCULATORInfrastructureSetup();
        	    
                    void injectLoginGetter( IFMDRELEVANTCALCULATORLoginGetterConstPtr );

                protected:
                    virtual void    doInit();
	                virtual void    doShutdown();
        	    
                private:
                    ////////////////////////////////
                    // methods
                    ////////////////////////////////
                    FMDRELEVANTCALCULATORInfrastructureSetup( const FMDRELEVANTCALCULATORInfrastructureSetup& r );
	                FMDRELEVANTCALCULATORInfrastructureSetup& operator=( const FMDRELEVANTCALCULATORInfrastructureSetup& r );

                    void login();
                    void prepareLogin();

                    ////////////////////////////////
                    // variables
                    ////////////////////////////////
                    IFMDRELEVANTCALCULATORLoginGetterConstPtr m_FMDRELEVANTCALCULATORLoginGetter;
            };
        }
    }
}

#endif
