#ifndef GUARD_CSC_DELI_COMPONENTMANAGER_IUSECASEGETTER_H
#define GUARD_CSC_DELI_COMPONENTMANAGER_IUSECASEGETTER_H

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
namespace csc_deli
{
namespace componentManager
{
    //--------------------------------------------------------------------------//
    // class IUseCaseGetter
    //--------------------------------------------------------------------------//
    class IUseCaseGetter
    {
        public:
            virtual ~IUseCaseGetter(){};
            virtual libutil::useCase::IRunnablePtr   getDebtLimitBatchUC()      = 0;
    };
}
}

#endif // GUARD_CSC_DELI_COMPONENTMANAGER_IUSECASEGETTER_H
