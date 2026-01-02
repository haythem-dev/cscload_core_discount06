//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/customerinvoice/customerinvoicecollectionacc.h"
#include "infrastructure/accessor/customerinvoice/customerinvoicecollectionacc_definitions.h"

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
namespace customerInvoice
{
    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( lit::CUSTOMER_INVOICE_COLLECTION_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::AMOUNT       )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::DOC_TYPE     )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PARTNER_NO   )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::TEXT_KEY     )

            ACCESS_METHOD( lit::FIND_CUSTOMER_INVOICE_COLLECTION_BY_KEY  )
                SQL_BUILDER_CREATE   ( FindCustomerInvoiceCollectionByKey )
                SQL_BUILDER_PUSH_BACK( FindCustomerInvoiceCollectionByKey )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( FindCustomerInvoiceCollectionByKey )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( FindCustomerInvoiceCollectionByKey )

        bool FindCustomerInvoiceCollectionByKey::isExecutable() const
        {
            METHODNAME_DEF( FindCustomerInvoiceCollectionByKey, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet( properties::PARTNER_NO.toPropertyString() );
            
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void FindCustomerInvoiceCollectionByKey::buildSQLString()
        {
            static const basar::VarString constSQL(
                "SELECT k.partnernr AS "                              + properties::PARTNER_NO.getName()  +
                ", d.amount AS "                                      + properties::AMOUNT.getName()      +
                ", d.doctype AS "                                     + properties::DOC_TYPE.getName()    +
                ", d.textkey AS "                                     + properties::TEXT_KEY.getName()    +
                " FROM cstinvoicedata d"
                " JOIN kunde k ON d.branchno = k.filialnr AND d.customerno = k.idfnr"
                " WHERE d.invoiced = 0 AND k.partnernr = "            + properties::PARTNER_NO.toSQLReplacementString()
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }

} // end namespace customerInvoice
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
