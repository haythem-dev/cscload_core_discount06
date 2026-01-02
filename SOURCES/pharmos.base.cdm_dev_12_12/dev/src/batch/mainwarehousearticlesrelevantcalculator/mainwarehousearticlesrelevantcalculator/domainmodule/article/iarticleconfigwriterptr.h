#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLECONFIGWRITERPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLECONFIGWRITERPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace domMod
    {
        namespace article
        {
            class IArticleConfigWriter;
            typedef boost::shared_ptr< IArticleConfigWriter > IArticleConfigWriterPtr;
        }
    }
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLECONFIGWRITERPTR_H
