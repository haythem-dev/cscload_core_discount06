//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      Accessor for customer.
 *  \author
 *  \date
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_ACCESSOR_LONGTERMLACKACC_H
#define GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_ACCESSOR_LONGTERMLACKACC_H

//-------------------------------------------------------------------------------------------------//
// sqlstring builder declaration section
//-------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace accessor
        {
            namespace longtermlack
            {
                BEGIN_WRITE_BUILDER_DECLARATION( ArticlesWithoutStockPreparer)
                END_BUILDER_DECLARATION

                BEGIN_WRITE_BUILDER_DECLARATION( SubstitutionArticlesWithStockPreparer)
                END_BUILDER_DECLARATION

                BEGIN_WRITE_BUILDER_DECLARATION( PseudoArticlesPreparer)
                END_BUILDER_DECLARATION

                BEGIN_WRITE_BUILDER_DECLARATION( ArticlesWithActivationTagPreparer)
                END_BUILDER_DECLARATION

                BEGIN_WRITE_BUILDER_DECLARATION( ArticlesWithoutStockBookingPreparer )
                END_BUILDER_DECLARATION

                BEGIN_WRITE_BUILDER_DECLARATION( ReservedArticlesPreparer )
                END_BUILDER_DECLARATION

                BEGIN_WRITE_BUILDER_DECLARATION( SpecialPZNsPreparer )
                END_BUILDER_DECLARATION

                BEGIN_WRITE_BUILDER_DECLARATION( ArticlesReImportPreparer )
                END_BUILDER_DECLARATION

                BEGIN_WRITE_BUILDER_DECLARATION( ArticeFromArticleBaseSubstractor )
                END_BUILDER_DECLARATION

                BEGIN_AGGREGATE_QUERY_BUILDER_DECLARATION( DBTempTableRowsCounter )
                END_BUILDER_DECLARATION

                BEGIN_AGGREGATE_QUERY_BUILDER_DECLARATION( DBTempTableDiscarder )
                END_BUILDER_DECLARATION

                BEGIN_WRITE_BUILDER_DECLARATION( LongTermLackEraser )
                END_BUILDER_DECLARATION

                BEGIN_WRITE_BUILDER_DECLARATION( LongTermLackInserter )
                END_BUILDER_DECLARATION
            }
        }
    }
}

#endif
