//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.07.2015
 */
//----------------------------------------------------------------------------
#ifndef GUARD_CSC_PHADEX_INFRASTRUCTURE_SETUP_ICSC_PHADEXLOGINGETTER_H
#define GUARD_CSC_PHADEX_INFRASTRUCTURE_SETUP_ICSC_PHADEXLOGINGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/login.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace csc_phadex
{
    namespace infrastructure
    {
        namespace setup
        {
            //------------------------------------------------------------------------------//
            // class 
            //------------------------------------------------------------------------------//
            class ICscPhadexLoginGetter
            {
                public:
                    virtual ~ICscPhadexLoginGetter(){};
                    //virtual libutil::infrastructure::login::ILoginPtr getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const = 0;
            };
        }
    }
}

#endif
