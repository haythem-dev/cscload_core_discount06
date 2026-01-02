#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IMAINWAREHOUSEARTICLESRELEVANTCALCULATORLOGINGETTER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IMAINWAREHOUSEARTICLESRELEVANTCALCULATORLOGINGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/login.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace setup
{
    //------------------------------------------------------------------------------//
    // class 
    //------------------------------------------------------------------------------//
    class IMAINWAREHOUSEARTICLESRELEVANTCALCULATORLoginGetter
    {
        public:
            virtual ~IMAINWAREHOUSEARTICLESRELEVANTCALCULATORLoginGetter(){};
            virtual libutil::infrastructure::login::ILoginPtr getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const = 0;
    };
} // end namespace setup
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IMAINWAREHOUSEARTICLESRELEVANTCALCULATORLOGINGETTER_H
