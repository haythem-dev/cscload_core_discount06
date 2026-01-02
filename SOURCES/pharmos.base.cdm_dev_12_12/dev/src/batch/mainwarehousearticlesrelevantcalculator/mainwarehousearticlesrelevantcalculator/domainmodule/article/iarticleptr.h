#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLEPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLEPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace domMod
    {
        namespace article
        {
            class IArticle;
            typedef boost::shared_ptr< IArticle > IArticlePtr;
        }
    }
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLEPTR_H
