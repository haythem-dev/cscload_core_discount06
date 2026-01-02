//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/customerorder/customerordercollectionacc.h"
#include "infrastructure/accessor/customerorder/customerordercollectionacc_definitions.h"

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
namespace customerOrder
{
    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( lit::CUSTOMER_ORDER_COLLECTION_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::CUSTOMER_NO    )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::DELIVERY_VALUE )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PARTNER_NO     )

            ACCESS_METHOD( lit::FIND_CUSTOMER_ORDER_COLLECTION     )
                SQL_BUILDER_CREATE   ( FindCustomerOrderCollection )
                SQL_BUILDER_PUSH_BACK( FindCustomerOrderCollection )

        END_ACCESSOR_DEFINITION


        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( FindCustomerOrderCollection )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( FindCustomerOrderCollection )

        bool FindCustomerOrderCollection::isExecutable() const
        {
            METHODNAME_DEF( FindCustomerOrderCollection, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet( properties::PARTNER_NO );
            
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void FindCustomerOrderCollection::buildSQLString()
        {
            static const basar::VarString constSQL(
                "SELECT k.partnernr AS "                                             + properties::PARTNER_NO.getName()     +
                ", a.idfnr AS "                                                      + properties::CUSTOMER_NO.getName()    +
                ", a.wertlieferung AS "                                              + properties::DELIVERY_VALUE.getName() +
                " FROM kdauftrag a "
                " JOIN kunde k ON a.idfnr = k.idfnr AND a.filialnr = k.filialnr "
                " WHERE k.partnernr = "                                              + properties::PARTNER_NO.toSQLReplacementString()
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }

} // end namespace customerOrder
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
