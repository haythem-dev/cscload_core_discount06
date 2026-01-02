//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.07.2015
 */
//----------------------------------------------------------------------------
#ifndef GUARD_IBTRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IIBTRELEVANTCALCULATORLOGINGETTER_H
#define GUARD_IBTRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_IIBTRELEVANTCALCULATORLOGINGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/login.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            //------------------------------------------------------------------------------//
            // class 
            //------------------------------------------------------------------------------//
            class IIBTRELEVANTCALCULATORLoginGetter
            {
                public:
                    virtual ~IIBTRELEVANTCALCULATORLoginGetter(){};
                    virtual libutil::infrastructure::login::ILoginPtr getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const = 0;
            };
        }
    }
}

#endif
