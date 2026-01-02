#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_USECASE_MAINUCPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_USECASE_MAINUCPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace useCase
    {
        class MainUC;
        typedef boost::shared_ptr< MainUC > MainUCPtr;
    }
}

#endif //end GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_USECASE_MAINUCPTR_H
