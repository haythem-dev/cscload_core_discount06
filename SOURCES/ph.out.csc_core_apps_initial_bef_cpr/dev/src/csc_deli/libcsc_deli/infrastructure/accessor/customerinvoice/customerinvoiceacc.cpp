//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/customerinvoice/customerinvoiceacc.h"
#include "infrastructure/accessor/customerinvoice/customerinvoiceacc_definitions.h"

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
        BEGIN_ACCESSOR_DEFINITION( lit::CUSTOMER_INVOICE_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::BRANCH_NO    )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::CUSTOMER_NO  )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::DOC_TYPE     )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::DOC_NO       )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::DATE         )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::AMOUNT       )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::TEXT_KEY     )

            ACCESS_METHOD( lit::FIND_CUSTOMER_INVOICE_BY_PATTERN    )
                SQL_BUILDER_CREATE   ( FindCustomerInvoiceByPattern )
                SQL_BUILDER_PUSH_BACK( FindCustomerInvoiceByPattern )

            ACCESS_METHOD( lit::SAVE_CUSTOMER_INVOICE        )
                SQL_BUILDER_CREATE   ( InsertCustomerInvoice )
                SQL_BUILDER_PUSH_BACK( InsertCustomerInvoice )
                SQL_BUILDER_CREATE   ( UpdateCustomerInvoice )
                SQL_BUILDER_PUSH_BACK( UpdateCustomerInvoice )

            ACCESS_METHOD( lit::SET_INVOICED_FLAG            )
                SQL_BUILDER_CREATE   ( SetInvoicedFlag       )
                SQL_BUILDER_PUSH_BACK( SetInvoicedFlag       )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( FindCustomerInvoiceByPattern )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( FindCustomerInvoiceByPattern )

        bool FindCustomerInvoiceByPattern::isExecutable() const
        {
            METHODNAME_DEF( FindCustomerInvoiceByPattern, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet( properties::BRANCH_NO.toPropertyString() 
                                                    + properties::CUSTOMER_NO.toPropertyString() 
                                                    + properties::DOC_TYPE.toPropertyString() 
                                                    + properties::DOC_NO.toPropertyString() 
                                                    + properties::DATE.toPropertyString() );
            
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void FindCustomerInvoiceByPattern::buildSQLString()
        {
            static const basar::VarString constSQL(
                "SELECT branchno AS "                                 + properties::BRANCH_NO.getName()   +
                ", customerno AS "                                    + properties::CUSTOMER_NO.getName() +
                ", doctype AS "                                       + properties::DOC_TYPE.getName()    +
                ", docno AS "                                         + properties::DOC_NO.getName()      +
                ", date AS "                                          + properties::DATE.getName()        +
                ", amount AS "                                        + properties::AMOUNT.getName()      +
                ", textkey AS "                                       + properties::TEXT_KEY.getName()    +
                " FROM cstinvoicedata"
                " WHERE branchno = "                                  + properties::BRANCH_NO.toSQLReplacementString()   +
                " AND customerno = "                                  + properties::CUSTOMER_NO.toSQLReplacementString() +
                " AND doctype = "                                     + properties::DOC_TYPE.toSQLReplacementString()    +
                " AND docno = "                                       + properties::DOC_NO.toSQLReplacementString()      +
                " AND date = "                                        + properties::DATE.toSQLReplacementString()
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( InsertCustomerInvoice )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( InsertCustomerInvoice )

        bool InsertCustomerInvoice::isExecutable() const
        {
            METHODNAME_DEF( InsertCustomerInvoice, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSetAndAllInState( properties::BRANCH_NO.toPropertyString()   +
                                                                   properties::CUSTOMER_NO.toPropertyString() +
                                                                   properties::DOC_TYPE.toPropertyString()    +
                                                                   properties::DOC_NO.toPropertyString()      +
                                                                   properties::DATE.toPropertyString()        +
                                                                   properties::AMOUNT.toPropertyString()      +
                                                                   properties::TEXT_KEY.toPropertyString()    ,
                                                                   basar::SS_INSERT
                                                                 );
            
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void InsertCustomerInvoice::buildSQLString()
        {
            static const basar::VarString constSQL(
                "INSERT INTO cstinvoicedata"
                " (branchno, customerno, doctype, docno, date, amount, textkey, invoiced) "
                "VALUES("        + properties::BRANCH_NO.toSQLReplacementString()
                          + ", " + properties::CUSTOMER_NO.toSQLReplacementString()
                          + ", " + properties::DOC_TYPE.toSQLReplacementString()
                          + ", " + properties::DOC_NO.toSQLReplacementString("'", "'")
                          + ", " + properties::DATE.toSQLReplacementString()
                          + ", " + properties::AMOUNT.toSQLReplacementString("'", "'")
                          + ", " + properties::TEXT_KEY.toSQLReplacementString("'", "'")
                          + ", 0"
                ")"
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( UpdateCustomerInvoice )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( UpdateCustomerInvoice )

        bool UpdateCustomerInvoice::isExecutable() const
        {
            METHODNAME_DEF( UpdateCustomerInvoice, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );
            
            const bool executable = are1stPropertiesSetAnd2ndOneInState( properties::BRANCH_NO.toPropertyString()   +
                                                                         properties::CUSTOMER_NO.toPropertyString() +
                                                                         properties::DOC_TYPE.toPropertyString()    +
                                                                         properties::DOC_NO.toPropertyString()      +
                                                                         properties::DATE.toPropertyString()        ,
                                                                         properties::AMOUNT.toPropertyString()      ,
                                                                         basar::SS_UPDATE
                                                                       );
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void UpdateCustomerInvoice::buildSQLString()
        {
            static const basar::VarString constSQL(
                "UPDATE cstinvoicedata SET amount = "                  + properties::AMOUNT.toSQLReplacementString()      +
                " WHERE branchno = "                                   + properties::BRANCH_NO.toSQLReplacementString()   +
                " AND customerno = "                                   + properties::CUSTOMER_NO.toSQLReplacementString() +
                " AND doctype = "                                      + properties::DOC_TYPE.toSQLReplacementString()    +
                " AND docno = "                                        + properties::DOC_NO.toSQLReplacementString()      +
                " AND date = "                                         + properties::DATE.toSQLReplacementString()
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SetInvoicedFlag )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SetInvoicedFlag )

        bool SetInvoicedFlag::isExecutable() const
        {
            METHODNAME_DEF( SetInvoicedFlag, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet( properties::CUSTOMER_NO.toPropertyString() +
                                                      properties::DATE.toPropertyString()       );
            
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void SetInvoicedFlag::buildSQLString()
        {
            static const basar::VarString constSQL(
                "UPDATE cstinvoicedata SET invoiced = 1"
                " WHERE customerno = "                                 + properties::CUSTOMER_NO.toSQLReplacementString() +
                " AND date <= "                                        + properties::DATE.toSQLReplacementString()
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }
} // end namespace customerInvoice
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
