#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLECONFIGWRITER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLECONFIGWRITER_H

#include "domainmodule/article/iarticleptr.h"

//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace article
{
    class IArticleConfigWriter
    {
    public:
        virtual ~IArticleConfigWriter() {}

        virtual void                                                        writeConfig( domMod::article::IArticlePtr ) = 0;
        virtual void                                                        eraseDeprecatedConfig()                     = 0;
    };

} // end namespace article
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLECONFIGWRITER_H
