//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/debtlimit/debtlimitacc.h"
#include "infrastructure/accessor/debtlimit/debtlimitacc_definitions.h"

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
        BEGIN_ACCESSOR_DEFINITION( lit::DEBTLIMIT_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PARTNER_NO          )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PARTNER_NAME        )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::LIMIT               )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_DEBIT_SIDE      )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_CREDIT_SIDE     )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_TURNOVER_MONTH  )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_TURNOVER_DAY    )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_RETURNS         )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::SUM_GOODS_RECEIPT   )

            ACCESS_METHOD( lit::SELECT_DEBTLIMIT )
                SQL_BUILDER_CREATE   ( SelectDebtLimit )
                SQL_BUILDER_PUSH_BACK( SelectDebtLimit )

            ACCESS_METHOD( lit::SAVE_DEBTLIMIT )
                SQL_BUILDER_CREATE   ( InsertDebtLimit )
                SQL_BUILDER_PUSH_BACK( InsertDebtLimit )
                SQL_BUILDER_CREATE   ( UpdateDebtLimit )
                SQL_BUILDER_PUSH_BACK( UpdateDebtLimit )

            ACCESS_METHOD( lit::DELETE_DEBTLIMIT )
                SQL_BUILDER_CREATE   ( DeleteDebtLimit )
                SQL_BUILDER_PUSH_BACK( DeleteDebtLimit )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectDebtLimit )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectDebtLimit )

        bool SelectDebtLimit::isExecutable() const
        {
            METHODNAME_DEF( SelectDebtLimit, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = isContainedAndSet( properties::PARTNER_NO );

            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void SelectDebtLimit::buildSQLString()
        {
            static const basar::VarString constSQL(
                "SELECT dl.partnerno "      "AS "                         + properties::PARTNER_NO.getName()         +
                     ", dl.partnername "    "AS "                         + properties::PARTNER_NAME.getName()       +
                     ", dl.limit "          "AS "                         + properties::LIMIT.getName()              +
                     ", dl.sum_debitside "  "AS "                         + properties::SUM_DEBIT_SIDE.getName()     +
                     ", dl.sum_creditside " "AS "                         + properties::SUM_CREDIT_SIDE.getName()    +
                     ", dl.sum_monturnover ""AS "                         + properties::SUM_TURNOVER_MONTH.getName() +
                     ", dl.sum_dayturnover ""AS "                         + properties::SUM_TURNOVER_DAY.getName()   +
                     ", dl.sum_returns "    "AS "                         + properties::SUM_RETURNS.getName()        +
                     ", dl.sum_goodsreceipt AS "                          + properties::SUM_GOODS_RECEIPT.getName()  +
                " FROM debtlimit dl "
                " WHERE dl.partnerno = "                                 + properties::PARTNER_NO.toSQLReplacementString()
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( InsertDebtLimit )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( InsertDebtLimit )

        bool InsertDebtLimit::isExecutable() const
        {
            METHODNAME_DEF( InsertDebtLimit, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSetAndAllInState(
                                        properties::PARTNER_NO.toPropertyString()         +
                                        properties::PARTNER_NAME.toPropertyString()       +
                                        properties::LIMIT.toPropertyString()              +
                                        properties::SUM_DEBIT_SIDE.toPropertyString()     +
                                        properties::SUM_CREDIT_SIDE.toPropertyString()    +
                                        properties::SUM_TURNOVER_DAY.toPropertyString()   +
                                        properties::SUM_TURNOVER_MONTH.toPropertyString() +
                                        properties::SUM_RETURNS.toPropertyString()        +
                                        properties::SUM_GOODS_RECEIPT.toPropertyString()  ,
                                        basar::SS_INSERT
                                    );

            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void InsertDebtLimit::buildSQLString()
        {
            static const basar::VarString constSQL(
                "INSERT INTO debtlimit "
                "(partnerno, partnername, limit, sum_debitside, sum_creditside, "
                "sum_monturnover, sum_dayturnover, sum_returns, sum_goodsreceipt)"
                " VALUES ("
                    + properties::PARTNER_NO.toSQLReplacementString()
                    + properties::PARTNER_NAME.toSQLReplacementString( ", '", "'" )
                    + properties::LIMIT.toSQLReplacementString( ", ", "" )
                    + properties::SUM_DEBIT_SIDE.toSQLReplacementString( ", '", "'" )
                    + properties::SUM_CREDIT_SIDE.toSQLReplacementString( ", '", "'" )
                    + properties::SUM_TURNOVER_MONTH.toSQLReplacementString( ", '", "'" )
                    + properties::SUM_TURNOVER_DAY.toSQLReplacementString( ", '", "'" )
                    + properties::SUM_RETURNS.toSQLReplacementString( ", '", "'" )
                    + properties::SUM_GOODS_RECEIPT.toSQLReplacementString( ", '", "'" )
                + ")"
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( UpdateDebtLimit )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( UpdateDebtLimit )

        bool UpdateDebtLimit::isExecutable() const
        {
            METHODNAME_DEF( UpdateDebtLimit, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = are1stPropertiesSetAnd2ndOneInState(
                                        properties::PARTNER_NO.toPropertyString()         ,
                                        properties::SUM_TURNOVER_DAY.toPropertyString()   +
                                        properties::SUM_TURNOVER_MONTH.toPropertyString() +
                                        properties::SUM_RETURNS.toPropertyString()        +
                                        properties::SUM_GOODS_RECEIPT.toPropertyString()  +
                                        properties::SUM_DEBIT_SIDE.toPropertyString()     +
                                        properties::PARTNER_NAME.toPropertyString()       +
                                        properties::LIMIT.toPropertyString()              ,
                                        basar::SS_UPDATE
                                    );

            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void UpdateDebtLimit::buildSQLString()
        {
            static const basar::VarString constSQL(
                "UPDATE debtlimit SET "
            );

            basar::VarString varSQL;
            basar::db::aspect::AccessorPropertyTable_YIterator yit = getPropertyList();
            for( basar::db::aspect::AccessorPropertyTable_XIterator xit = yit.begin( basar::SS_UPDATE ); ! xit.isEnd(); ++xit )
            {
                if( ! varSQL.empty() )
                {
                    varSQL.append( ", " );
                }

                basar::property::PropertyDescription propDesc( xit.getName().c_str() );
                if( xit.getType().getType() == basar::DECIMAL || xit.getType().getType() == basar::STRING )
                {
                    // enclose property with tick marks
                    varSQL.append( xit.getName() + " = " + propDesc.toSQLReplacementString( "'", "'" ) );
                }
                else
                {
                    varSQL.append( xit.getName() + " = " + propDesc.toSQLReplacementString() );
                }
            }

            varSQL.append( " WHERE partnerno = " + properties::PARTNER_NO.toSQLReplacementString() );

            resolve( constSQL + varSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( DeleteDebtLimit )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( DeleteDebtLimit )

        bool DeleteDebtLimit::isExecutable() const
        {
            METHODNAME_DEF( DeleteDebtLimit, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet( properties::PARTNER_NO );

            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void DeleteDebtLimit::buildSQLString()
        {
            static const basar::VarString constSQL(
                "DELETE FROM debtlimit "
                "WHERE partnerno = "                                    + properties::PARTNER_NO.toSQLReplacementString()
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }

} // end namespace debtLimit
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
