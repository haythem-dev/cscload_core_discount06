#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_ARTICLECOLLECTIONFINDER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_ARTICLECOLLECTIONFINDER_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace domMod
    {
        namespace article
        {
            class IArticleCollectionFinder;
            typedef boost::shared_ptr< IArticleCollectionFinder > IArticleCollectionFinderPtr;
        }
    }
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_ARTICLECOLLECTIONFINDER_H
