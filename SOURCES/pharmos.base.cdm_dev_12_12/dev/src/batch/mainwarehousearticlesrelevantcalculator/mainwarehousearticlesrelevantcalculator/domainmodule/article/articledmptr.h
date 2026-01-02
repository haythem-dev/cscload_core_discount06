#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_ARTICLEDMPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_ARTICLEDMPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace domMod
    {
        namespace article
        {
            class ArticleDM;
            typedef boost::shared_ptr< ArticleDM > ArticleDMPtr;
        }
    }
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_ARTICLEDMPTR_H
