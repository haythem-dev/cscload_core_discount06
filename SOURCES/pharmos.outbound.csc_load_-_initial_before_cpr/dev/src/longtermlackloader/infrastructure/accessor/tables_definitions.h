//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      Providing table names
 *  \author     Bischof Bjoern
 *  \date       01.03.2011
 *  \version    00.00.00.01 first version
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_ACCESSOR_TABLES_DEFINITIONS_H
#define GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_ACCESSOR_TABLES_DEFINITIONS_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasarproperty_definitions.h>
//#include <libbasarproperty_propertydescription.h>


//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace accessor
        {
            namespace tables
            {
                static const basar::VarString ARTICLES_WITHOUT_STOCK_TEMP           = "art_wo_st_tmp";
                static const basar::VarString SUBSTITUTION_ARTICLES_WITH_STOCK_TEMP = "su_art_with_st_tmp";
                static const basar::VarString PSEUDO_ARTICLES_TEMP                  = "pseudo_art_tmp";
                static const basar::VarString INACTIVE_ARTICLES_TEMP                = "inactive_art_tmp";
                static const basar::VarString ACTIVE_ARTICLES_TEMP                  = "active_art_tmp";
                static const basar::VarString ARTICLES_WITHOUT_STOCK_BOOKING_TEMP   = "art_wo_st_book_tmp";
                static const basar::VarString RESERVED_ARTICLES_TEMP                = "reserved_art_tmp";
                static const basar::VarString RESERVED_ARTICLES_WITH_TYPE_TEMP      = "res_art_w_type_tmp";
                static const basar::VarString SPECIAL_PZNS_TEMP                     = "special_pzns_temp";
                static const basar::VarString ARTICLES_REIMPORT_TEMP                = "art_reimport_temp";

                static const basar::VarString LONG_TERM_LACK = "longtermlack";
                static const basar::VarString ARTIKEL_LOKAL = "artikellokal";
                static const basar::VarString PARA_AUFTRAG_BEARBEITUNG = "paraauftragbearb";
                static const basar::VarString ARTICLE_RESERVATION = "articlereservation";
                static const basar::VarString ARTIKEL_ALTERNATIVE = "artikelaltern";
                static const basar::VarString ARTIKEL_REIMPORT = "artikelreimport";
                
                
                
            }
        }
    }
}
#endif
