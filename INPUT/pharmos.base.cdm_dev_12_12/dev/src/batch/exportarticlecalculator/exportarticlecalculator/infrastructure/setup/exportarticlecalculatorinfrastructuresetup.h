//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       12.06.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_SETUP_EXPORTARTICLECALCULATORINFRASTRUCTURESETUP_H
#define GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_SETUP_EXPORTARTICLECALCULATORINFRASTRUCTURESETUP_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include "infrastructure/setup/iexportarticlecalculatorlogingetterptr.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace exportarticlecalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            class EXPORTARTICLECALCULATORInfrastructureSetup : public libutil::infrastructure::InfrastructureSetupBase
            {
                public:
                    EXPORTARTICLECALCULATORInfrastructureSetup();
	                virtual ~EXPORTARTICLECALCULATORInfrastructureSetup();
        	    
                    void injectLoginGetter( IEXPORTARTICLECALCULATORLoginGetterConstPtr );

                protected:
                    virtual void    doInit();
	                virtual void    doShutdown();
        	    
                private:
                    ////////////////////////////////
                    // methods
                    ////////////////////////////////
                    EXPORTARTICLECALCULATORInfrastructureSetup( const EXPORTARTICLECALCULATORInfrastructureSetup& r );
	                EXPORTARTICLECALCULATORInfrastructureSetup& operator=( const EXPORTARTICLECALCULATORInfrastructureSetup& r );

                    void login();
                    void prepareLogin();

                    ////////////////////////////////
                    // variables
                    ////////////////////////////////
                    IEXPORTARTICLECALCULATORLoginGetterConstPtr m_EXPORTARTICLECALCULATORLoginGetter;
            };
        }
    }
}

#endif
