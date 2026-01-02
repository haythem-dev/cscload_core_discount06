//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   14.10.2022
 */
//----------------------------------------------------------------------------
#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_ILOGINGETTER_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_INFRASTRUCTURE_SETUP_ILOGINGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/login.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            //------------------------------------------------------------------------------//
            // class 
            //------------------------------------------------------------------------------//
            class ISUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetter
            {
                public:
                    virtual ~ISUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetter(){};
                    virtual libutil::infrastructure::login::ILoginPtr getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const = 0;
            };
        }
    }
}

#endif
