#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_ARTICLEFACTORYPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_ARTICLEFACTORYPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace componentManager
    {
        class ArticleFactory;
        typedef boost::shared_ptr< ArticleFactory > ArticleFactoryPtr;
    }
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_ARTICLEFACTORYPTR_H
