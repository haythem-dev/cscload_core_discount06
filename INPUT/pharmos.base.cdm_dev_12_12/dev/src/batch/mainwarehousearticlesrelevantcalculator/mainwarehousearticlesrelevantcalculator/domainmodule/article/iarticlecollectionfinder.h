#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLECOLLECTIONFINDER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLECOLLECTIONFINDER_H

#include <libbasar_definitions.h>
#include "iarticleptr.h"

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//

namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTableRef;
            class AccessorPropertyTable_YIterator;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace article
{
    class IArticleCollectionFinder
    {
    public:
        virtual ~IArticleCollectionFinder() {}

        virtual basar::db::aspect::AccessorPropertyTableRef           get()     const                                                        = 0;
        virtual bool                                                  isEmpty() const                                                        = 0;

        virtual void                                                  findByBranchNo( basar::Int16 )                                         = 0;
        virtual IArticlePtr                                           getArticle( basar::db::aspect::AccessorPropertyTable_YIterator ) const = 0;
        virtual basar::Int32                                          countByBranchNo( basar::Int16 )                                        = 0;
    };

} // end namespace article
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_IARTICLECOLLECTIONFINDER_H
