//-----------------------------------------------------------------------------------------------//
// include section
//-----------------------------------------------------------------------------------------------//
#include "dbactionparameter.h"

#include <libbasarcmnutil.h>

//-----------------------------------------------------------------------------------------------//
// class definition section
//-----------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace parameter
        {
            // basic volume of articles
            const basar::VarString DBActionParameter::ART_WITHOUT_STOCK_SEL_ACTIVE      = "ART_WITHOUT_STOCK_SEL_ACTIVE";

            // first article set to subtract: substitution articles
            const basar::VarString DBActionParameter::SUBS_ART_WITH_STOCK_SEL_ACTIVE    = "SUBS_ART_WITH_STOCK_SEL_ACTIVE";

            // second article set to subtract: pseudo articles
            const basar::VarString DBActionParameter::PSEUDO_ARTICLES_SEL_ACTIVE        = "PSEUDO_ARTICLES_SEL_ACTIVE";

            // third article set to subtract: active articles
            const basar::VarString DBActionParameter::ACTIVE_ARTICLES_SEL_ACTIVE        = "ACTIVE_ARTICLES_SEL_ACTIVE";

            // fourth article set to subtract: articles, which have no stock booking
            const basar::VarString DBActionParameter::ART_WO_STCK_BOOKING_SEL_ACTIVE    = "ART_WO_STCK_BOOKING_SEL_ACTIVE";

            // fifth article set to subtract: reserved articles
            const basar::VarString DBActionParameter::RESERVED_ARTICLES_SEL_ACTIVE      = "RESERVED_ARTICLES_SEL_ACTIVE";

            // sixth article set to subtract: articles with special PZNs
            const basar::VarString DBActionParameter::SPECIAL_PZNS_SEL_ACTIVE           = "SPECIAL_PZNS_SEL_ACTIVE";

            const basar::VarString DBActionParameter::ART_REIMPORT_SEL_ACTIVE           = "ART_REIMPORT_SEL_ACTIVE";
            // not used any more (BB-02.12.2019)
            //const basar::VarString DBActionParameter::INACTIVE_ARTICLES_SEL_ACTIVE      = "INACTIVE_ARTICLES_SEL_ACTIVE";
            //const basar::VarString DBActionParameter::RES_ART_WITH_TYPE_SEL_ACTIVE      = "RES_ART_WITH_TYPE_SEL_ACTIVE";
            
            // PERSISTENCE_STRATEGY: 0 = Delete_Insert; 1 = Truncate_Insert;
            const basar::VarString DBActionParameter::PERSISTENCE_STRATEGY              = "PERSISTENCE_STRATEGY";

            DBActionParameter::DBActionParameter()
            {
            }

            DBActionParameter::~DBActionParameter()
            {
            }
        }
    }
}
