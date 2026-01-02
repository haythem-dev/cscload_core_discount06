//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.07.2015
 */
//----------------------------------------------------------------------------
#ifndef GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_SETUP_ILONGTERMLACKLOADERLOGINGETTER_H
#define GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_SETUP_ILONGTERMLACKLOADERLOGINGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/login.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace setup
        {
            //------------------------------------------------------------------------------//
            // class
            //------------------------------------------------------------------------------//
            class ILongTermLackLoaderLoginGetter
            {
                public:
                    virtual ~ILongTermLackLoaderLoginGetter(){};
                    virtual libutil::infrastructure::login::ILoginPtr getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const = 0;
            };
        }
    }
}

#endif
