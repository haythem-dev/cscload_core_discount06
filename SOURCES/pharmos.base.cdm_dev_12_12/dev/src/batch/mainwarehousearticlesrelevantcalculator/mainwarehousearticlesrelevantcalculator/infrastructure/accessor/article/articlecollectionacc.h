#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_ARTICLE_ARTICLECOLLECTIONACC_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_ARTICLE_ARTICLECOLLECTIONACC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasardbaspect_macros.h>
#include <libbasardbaspect_definitions.h>
#include <libbasardbaspect_sqlstringbuilder.h>

//-------------------------------------------------------------------------------------------------//
// sqlstring builder declaration section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{
namespace article
{
    BEGIN_QUERY_BUILDER_DECLARATION( SelectArticleCollection )
    END_BUILDER_DECLARATION

    BEGIN_AGGREGATE_QUERY_BUILDER_DECLARATION(SelectCountArticleCollection)
    END_BUILDER_DECLARATION

    BEGIN_AGGREGATE_QUERY_BUILDER_DECLARATION( SelectLastPrognosisDate )
    END_BUILDER_DECLARATION

} // end namespace article
} // end namespace accessor
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_ARTICLE_ARTICLECOLLECTIONACC_H
