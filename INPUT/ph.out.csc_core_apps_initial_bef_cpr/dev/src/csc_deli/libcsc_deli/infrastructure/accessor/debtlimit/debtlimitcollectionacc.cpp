//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/debtlimit/debtlimitcollectionacc.h"
#include "infrastructure/accessor/debtlimit/debtlimitcollectionacc_definitions.h"

#include "loggerpool/libcsc_deli_loggerpool.h"
#include "domainmodule/libcsc_deli_properties_definitions.h"

#include <libbasardbaspect.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
namespace debtLimit
{
    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( lit::DEBTLIMIT_COLLECTION_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PARTNER_NO          )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PARTNER_NAME        ) // filled later
                PROPERTY_DESCRIPTION_LIST_ADD( properties::LIMIT               )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_DEBIT_SIDE      )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_CREDIT_SIDE     )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_TURNOVER_MONTH  )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_TURNOVER_DAY    )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_RETURNS         )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_GOODS_RECEIPT   )

            ACCESS_METHOD( lit::SELECT_DEBTLIMIT_COLLECTION )
                SQL_BUILDER_CREATE   ( SelectDebtLimitCollection )
                SQL_BUILDER_PUSH_BACK( SelectDebtLimitCollection )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectDebtLimitCollection )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectDebtLimitCollection )

        bool SelectDebtLimitCollection::isExecutable() const
        {
            METHODNAME_DEF( SelectDebtLimit, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = true;

            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void SelectDebtLimitCollection::buildSQLString()
        {
            static const basar::VarString constSQL(
                "SELECT dl.partnerno        AS "                         + properties::PARTNER_NO.getName()         +
                     ", dl.limit            AS "                         + properties::LIMIT.getName()              +
                     ", dl.sum_debitside    AS "                         + properties::SUM_DEBIT_SIDE.getName()     +
                     ", dl.sum_creditside   AS "                         + properties::SUM_CREDIT_SIDE.getName()    +
                     ", dl.sum_monturnover  AS "                         + properties::SUM_TURNOVER_MONTH.getName() +
                     ", dl.sum_dayturnover  AS "                         + properties::SUM_TURNOVER_DAY.getName()   +
                     ", dl.sum_returns      AS "                         + properties::SUM_RETURNS.getName()        +
                     ", dl.sum_goodsreceipt AS "                         + properties::SUM_GOODS_RECEIPT.getName()  +
                " FROM debtlimit dl "
                " ORDER BY dl.partnerno DESC"
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }

} // end namespace debtLimit
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
