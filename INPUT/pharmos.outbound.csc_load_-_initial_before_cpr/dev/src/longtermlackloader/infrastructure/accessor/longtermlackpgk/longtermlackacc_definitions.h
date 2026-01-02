//----------------------------------------------------------------------------
/*! \file
    \brief  global definitions for customer module
 *  \author
 *  \date
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_ACCESSOR_LONGTERMLACKACC_DEFINITIONS_H
#define GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_ACCESSOR_LONGTERMLACKACC_DEFINITIONS_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil_parameterlist.h>

//----------------------------------------------------------------------------//
// lit definition section
//----------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace accessor
        {
            namespace longtermlack
            {
                enum ArticleActiveTagEnum
                {
                    ARTICLE_ACTIVE_TAG = 1,
                    ARTICLE_PSEUDO_TAG = 2
                };
                
                enum SwitchEnum
                {
                    SWITCH_OFF = 0,
                    SWITCH_ON  = 1
                };

                namespace lit
                {
                    static const basar::VarString LONG_TERM_LACK_ACC                        ( "LongTermLackAcc" );

                    static const basar::VarString PREPARE_ARTICLES_WITHOUT_STOCK            ( "PrepareArticleWithoutStock" );
                    static const basar::VarString PREPARE_SUBSTITUTION_ARTICLES_WITH_STOCK  ( "PrepareSubstitutionArticleWithStock" );
                    static const basar::VarString PREPARE_LONG_TERM_LACK                    ( "PrepareLongTermLack" );
                    static const basar::VarString PREPARE_PSEUDO_ARTICLES                   ( "PreparePseudoArticles");
                    static const basar::VarString PREPARE_ARTICLES_WITH_ACTIVATION_TAG      ( "PrepareArticlesWithActivationTag" );
                    static const basar::VarString PREPARE_ARTICLES_WITHOUT_STOCK_BOOKING    ( "PrepareArticlesWithoutSockBooking" );
                    static const basar::VarString PREPARE_RESERVED_ARTICLES                 ( "PrepareReservedArticles");
                    static const basar::VarString PREPARE_SPECIAL_PZNS                      ( "PrepareSpecialPZNs");
                    static const basar::VarString PREPARE_ARTICLES_REIMPORT                 ( "PrepareArticlesReimport");
                    static const basar::VarString SUBSTRACT_ARTICLES_FROM_ARTICLES_BASE     ( "SubstractArticlesFromArticlesBase" );
                    
                    static const basar::VarString DISCARD_DB_TEMP_TABLE                     ( "DiscardDBTempTable" );
                    static const basar::VarString COUNT_DB_ROWS                             ( "CountDBRows" );
                    static const basar::VarString SAVE_LONG_TERM_LACK                       ( "SaveLongTermLack" );
                }
            }
        }
    }
}

#endif
