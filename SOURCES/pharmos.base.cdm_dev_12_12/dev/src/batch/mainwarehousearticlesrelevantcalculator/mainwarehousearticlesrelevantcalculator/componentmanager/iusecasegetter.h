#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IUSECASEGETTER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IUSECASEGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/irunnableptr.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
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
            virtual libutil::useCase::IRunnablePtr   getRelevantCalculatorUC()    = 0;
            virtual libutil::useCase::IRunnablePtr   getAdmissionConsiderGroupUC() = 0;
    };
} // end namespace componentManager
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IUSECASEGETTER_H
