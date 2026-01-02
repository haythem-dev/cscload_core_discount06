//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   25.08.2021
 */
//----------------------------------------------------------------------------
#ifndef GUARD_IMPORTPRICELIST_INFRASTRUCTURE_SETUP_IIMPORTPRICELISTLOGINGETTER_H
#define GUARD_IMPORTPRICELIST_INFRASTRUCTURE_SETUP_IIMPORTPRICELISTLOGINGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/login.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace importpricelist
{
    namespace infrastructure
    {
        namespace setup
        {
            //------------------------------------------------------------------------------//
            // class 
            //------------------------------------------------------------------------------//
            class IIMPORTPRICELISTLoginGetter
            {
                public:
                    virtual ~IIMPORTPRICELISTLoginGetter(){};
                    virtual libutil::infrastructure::login::ILoginPtr getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const = 0;
            };
        }
    }
}

#endif
