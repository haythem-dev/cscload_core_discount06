//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.07.2015
 */
//----------------------------------------------------------------------------
#ifndef GUARD_LOADCONTRACTSHR_INFRASTRUCTURE_SETUP_ILOADCONTRACTSHRLOGINGETTER_H
#define GUARD_LOADCONTRACTSHR_INFRASTRUCTURE_SETUP_ILOADCONTRACTSHRLOGINGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/login.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace loadcontractshr
{
    namespace infrastructure
    {
        namespace setup
        {
            //------------------------------------------------------------------------------//
            // class 
            //------------------------------------------------------------------------------//
            class ILoadContractsHrLoginGetter
            {
                public:
                    virtual ~ILoadContractsHrLoginGetter(){};
                    virtual libutil::infrastructure::login::ILoginPtr getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const = 0;
            };
        }
    }
}

#endif
