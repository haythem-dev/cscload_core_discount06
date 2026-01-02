//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.07.2015
 */
//----------------------------------------------------------------------------
#ifndef GUARD_IBTORDERIMPORT_INFRASTRUCTURE_SETUP_IIBTORDERIMPORTLOGINGETTER_H
#define GUARD_IBTORDERIMPORT_INFRASTRUCTURE_SETUP_IIBTORDERIMPORTLOGINGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/login.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace ibtorderimport
{
    namespace infrastructure
    {
        namespace setup
        {
            //------------------------------------------------------------------------------//
            // class 
            //------------------------------------------------------------------------------//
            class IIBTORDERIMPORTLoginGetter
            {
                public:
                    virtual ~IIBTORDERIMPORTLoginGetter(){};
                    virtual libutil::infrastructure::login::ILoginPtr getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const = 0;
            };
        }
    }
}

#endif
