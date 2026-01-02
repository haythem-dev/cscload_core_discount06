//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   14.10.2022
 */
//----------------------------------------------------------------------------
#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_IUSECASEGETTER_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_IUSECASEGETTER_H


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
namespace subsequentdeliveryrelevantcalculator
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
        };
    }
}

#endif
