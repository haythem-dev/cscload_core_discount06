//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/customerturnover/customerturnovercollectionacc.h"
#include "infrastructure/accessor/customerturnover/customerturnovercollectionacc_definitions.h"

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
namespace customerTurnover
{
    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( lit::CUSTOMER_TURNOVER_COLLECTION_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::CUSTOMER_NO    )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::BRANCH_NO      )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_TURNOVER   )

            ACCESS_METHOD( lit::FIND_CUSTOMER_TURNOVER_COLLECTION  )
                SQL_BUILDER_CREATE   ( FindCustomerTurnoverCollection )
                SQL_BUILDER_PUSH_BACK( FindCustomerTurnoverCollection )

        END_ACCESSOR_DEFINITION 

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( FindCustomerTurnoverCollection )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( FindCustomerTurnoverCollection )

        bool FindCustomerTurnoverCollection::isExecutable() const
        {
            METHODNAME_DEF( FindCustomerTurnoverCollection, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = true;
            
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void FindCustomerTurnoverCollection::buildSQLString()
        {
            static const basar::VarString constSQL(
                "SELECT k.idfnr AS "									+ properties::CUSTOMER_NO.getName()  +
                ", k.filialnr AS "										+ properties::BRANCH_NO.getName()    +
                ", SUM(nvl(c.amount,0)) + "
				"      nvl((SELECT SUM(wertlieferung) FROM kdauftrag where idfnr = k.idfnr and filialnr = k.filialnr),0) AS " + properties::SUM_TURNOVER.getName() + 
                " FROM kunde k, filiale f, paraauftragbearb p, outer cstinvoicedata c "
                " WHERE f.filialnr = k.filialnr and p.screma = 1 and p.filialnr = k.filialnr "
				" and c.customerno = k.idfnr AND c.branchno = k.filialnr and c.invoiced = 0 AND (c.doctype = 1 OR (c.doctype = 2 AND (c.textkey = 20 OR c.textkey = 21))) "
                " GROUP BY k.idfnr, k.filialnr "
				" HAVING SUM(nvl(c.amount,0)) + nvl((SELECT SUM(wertlieferung) FROM kdauftrag where idfnr = k.idfnr and filialnr = k.filialnr),0) > 0 "
                " ORDER BY k.idfnr, k.filialnr "
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }

} // end namespace customerTurnover
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
