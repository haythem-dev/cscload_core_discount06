#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IRELEVANTRULEFACTORYPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IRELEVANTRULEFACTORYPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace componentManager
    {
        class IRelevantRuleFactory;
        typedef boost::shared_ptr< IRelevantRuleFactory > IRelevantRuleFactoryPtr;
    }
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IRELEVANTRULEFACTORYPTR_H
