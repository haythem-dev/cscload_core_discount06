//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   27.07.2013
 */
//----------------------------------------------------------------------------
#ifndef GUARD_LONGTERMLACKLOADER_COMPONENTMANAGER_IUSECASEGETTER_H
#define GUARD_LONGTERMLACKLOADER_COMPONENTMANAGER_IUSECASEGETTER_H


//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/irunnableptr.h>

//------------------------------------------------------------------------------//
// forward declaration
//------------------------------------------------------------------------------//

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace componentManager
    {
        //------------------------------------------------------------------------------//
        // class IUseCaseGetter
        //------------------------------------------------------------------------------//
        class IUseCaseGetter
        {
            public:
                virtual ~IUseCaseGetter(){};
                virtual libutil::useCase::IRunnablePtr   getSoleBatchUC()         = 0;
        };
    }
}

#endif
