//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/cremamail/cremamailcleanupacc.h"
#include "infrastructure/accessor/cremamail/cremamailcleanupacc_definitions.h"

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
namespace cremaMail
{
    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( lit::CREMA_MAIL_CLEANUP_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PARTNER_NO    ) // dummy

            ACCESS_METHOD( lit::CLEANUP_SEND_MAIL_FLAG )
                SQL_BUILDER_CREATE( CleanupSendMailFlagForDebtLevel )
                SQL_BUILDER_PUSH_BACK( CleanupSendMailFlagForDebtLevel )
                SQL_BUILDER_CREATE( CleanupSendMailFlagForAmount )
                SQL_BUILDER_PUSH_BACK( CleanupSendMailFlagForAmount )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( CleanupSendMailFlagForDebtLevel )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( CleanupSendMailFlagForDebtLevel )

        bool CleanupSendMailFlagForDebtLevel::isExecutable() const
        {
            METHODNAME_DEF( CleanupSendMailFlagForDebtLevel, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = true; // execute always

            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void CleanupSendMailFlagForDebtLevel::buildSQLString()
        {
            static const basar::VarString constSQL(
                "DELETE FROM debtmailsend dms "
                "WHERE id IN ("
                   "SELECT dms.id "
                   "FROM debtmailsend dms "
                   " JOIN crematype ct ON dms.crematypeid = ct.id AND ct.type = 0 "
                   " JOIN debtlevelformail dlfm ON ct.typeid = dlfm.id "
                   " JOIN kunde k ON dms.partnerno = k.partnernr"
                   " JOIN debtlimit dl ON k.partnernr = dl.partnerno "
                   "WHERE dlfm.leveltype = 1 AND "
                        "(dl.sum_debitside + dl.sum_creditside + dl.sum_monturnover + dl.sum_dayturnover - dl.sum_returns - dl.sum_goodsreceipt) < "
                        "(dl.limit / 100 * dlfm.dlpercentage))"
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( CleanupSendMailFlagForAmount )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( CleanupSendMailFlagForAmount )

        bool CleanupSendMailFlagForAmount::isExecutable() const
        {
            METHODNAME_DEF( CleanupSendMailFlagForAmount, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = true; // execute always

            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void CleanupSendMailFlagForAmount::buildSQLString()
        {
            static const basar::VarString constSQL(
                "DELETE FROM debtmailsend "
                "WHERE id IN ("
                   "SELECT dms.id "
                   "FROM debtmailsend dms "
                   "JOIN crematype ct ON dms.crematypeid = ct.id AND ct.type = 1 "
                   "JOIN amountformail afm ON ct.typeid = afm.id "
                   "JOIN kunde k ON dms.partnerno = k.partnernr "
                   "JOIN debtlimit dl ON k.partnernr = dl.partnerno "
                   "WHERE (dl.sum_debitside + dl.sum_creditside + dl.sum_monturnover + dl.sum_dayturnover - dl.sum_returns - dl.sum_goodsreceipt) < "
                   "afm.thresholdamount)"
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }

} // end namespace cremaMail
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
