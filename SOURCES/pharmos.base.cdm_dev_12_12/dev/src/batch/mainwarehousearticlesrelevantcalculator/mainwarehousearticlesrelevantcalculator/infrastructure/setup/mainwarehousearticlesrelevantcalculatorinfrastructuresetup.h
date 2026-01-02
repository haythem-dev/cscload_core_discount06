#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_MAINWAREHOUSEARTICLESRELEVANTCALCULATORINFRASTRUCTURESETUP_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_MAINWAREHOUSEARTICLESRELEVANTCALCULATORINFRASTRUCTURESETUP_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include "infrastructure/setup/imainwarehousearticlesrelevantcalculatorlogingetterptr.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace setup
{
    class MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup : public libutil::infrastructure::InfrastructureSetupBase
    {
        public:
            MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup();
            virtual ~MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup();
        
            void injectLoginGetter( IMAINWAREHOUSEARTICLESRELEVANTCALCULATORLoginGetterConstPtr );

        protected:
            virtual void    doInit();
            virtual void    doShutdown();
        
        private:
            ////////////////////////////////
            // methods
            ////////////////////////////////
            MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup( const MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup& r );
            MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup& operator=( const MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup& r );

            void login();
            void prepareLogin();

            ////////////////////////////////
            // variables
            ////////////////////////////////
            IMAINWAREHOUSEARTICLESRELEVANTCALCULATORLoginGetterConstPtr m_MAINWAREHOUSEARTICLESRELEVANTCALCULATORLoginGetter;
    };
} // end namespace setup
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_MAINWAREHOUSEARTICLESRELEVANTCALCULATORINFRASTRUCTURESETUP_H
