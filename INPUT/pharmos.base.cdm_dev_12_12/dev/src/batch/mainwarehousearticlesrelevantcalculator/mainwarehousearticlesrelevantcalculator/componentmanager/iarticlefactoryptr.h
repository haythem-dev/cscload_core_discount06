#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IARTICLEFACTORYTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IARTICLEFACTORYTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace componentManager
    {
        class IArticleFactory;
        typedef boost::shared_ptr< IArticleFactory > IArticleFactoryPtr;
    }
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IARTICLEFACTORYTR_H
