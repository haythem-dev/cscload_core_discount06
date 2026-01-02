//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Michael Helmich
 *  \date       14.10.2022
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_INFRASTRUCTURESETUP_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_INFRASTRUCTURESETUP_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include "infrastructure/setup/isubsequentdeliveryrelevantcalculatorlogingetterptr.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            class SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup : public libutil::infrastructure::InfrastructureSetupBase
            {
                public:
                    SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup();
	                virtual ~SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup();
        	    
                    void injectLoginGetter( ISUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetterConstPtr );

                protected:
                    virtual void    doInit();
	                virtual void    doShutdown();
        	    
                private:
                    ////////////////////////////////
                    // methods
                    ////////////////////////////////
                    SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup( const SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup& r );
	                SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup& operator=( const SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup& r );

                    void login();
                    void prepareLogin();

                    ////////////////////////////////
                    // variables
                    ////////////////////////////////
                    ISUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetterConstPtr m_SUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetter;
            };
        }
    }
}

#endif
