//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.07.2015
 */
//----------------------------------------------------------------------------
#ifndef GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IFMDRELEVANTCALCULATORLOGINGETTER_H
#define GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IFMDRELEVANTCALCULATORLOGINGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/login.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            //------------------------------------------------------------------------------//
            // class 
            //------------------------------------------------------------------------------//
            class IFMDRELEVANTCALCULATORLoginGetter
            {
                public:
                    virtual ~IFMDRELEVANTCALCULATORLoginGetter(){};
                    virtual libutil::infrastructure::login::ILoginPtr getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const = 0;
            };
        }
    }
}

#endif
