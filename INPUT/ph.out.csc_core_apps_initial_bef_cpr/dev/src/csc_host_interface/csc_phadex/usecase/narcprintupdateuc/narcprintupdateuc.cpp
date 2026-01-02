#include "narcprintupdateuc.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include "domainmodule/phadextransaction/transactionrecord/narcprintupdate/inarcprintupdate.h"
#include "domainmodule/narcotics/inarcotics.h"
#include "domainmodule/csc_phadex_properties_definitions.h"

namespace csc_phadex
{
namespace useCase
{
NarcPrintUpdateUC::NarcPrintUpdateUC()
: m_Logger( LoggerPool::getLoggerUseCases() )
{
    METHODNAME_DEF( NarcPrintUpdateUC, NarcPrintUpdateUC );
    BLOG_TRACE_METHOD( m_Logger, fun );
}

NarcPrintUpdateUC::~NarcPrintUpdateUC()
{
    METHODNAME_DEF( NarcPrintUpdateUC, ~NarcPrintUpdateUC );
    BLOG_TRACE_METHOD( m_Logger, fun );
}

void NarcPrintUpdateUC::injectNarcoticsDM( csc_phadex::domMod::narcotics::INarcoticsPtr narcotics)
{
    m_Narcotics = narcotics;
}

void NarcPrintUpdateUC::setNarcPrintUpdate( csc_phadex::domMod::phadexTransaction::INarcPrintUpdatePtr narcPrintUpdate)
{
    m_NarcPrintUpdate = narcPrintUpdate;
}

void NarcPrintUpdateUC::run()
{
    METHODNAME_DEF( NarcPrintUpdateUC, run );
    BLOG_TRACE_METHOD( m_Logger, fun );

    try
    {
        m_Narcotics->save( getSearchYIterator() );
    }
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( m_Logger, e.what() );
    }
}

basar::db::aspect::AccessorPropertyTable_YIterator NarcPrintUpdateUC::getSearchYIterator()
{
    METHODNAME_DEF( NarcPrintUpdateUC, getSearchYIterator )
    BLOG_TRACE_METHOD( m_Logger, fun);

    basar::db::aspect::AccessorPropertyTable_YIterator searchYit;
    try
    {
        m_Narcotics->resetSearchYit();
        searchYit = m_Narcotics->getSearchYit();

        searchYit.setInt16( properties::BRANCH_NO, m_NarcPrintUpdate->getBranchno() );
        searchYit.setInt32( properties::CUSTOMERSUPPLIERNO, m_NarcPrintUpdate->getCustomerNo() );
        searchYit.setInt32( properties::ORDER_NO, m_NarcPrintUpdate->getOrderNo() );
		searchYit.setInt32( properties::WAREHOUSE_ORDER_NO, m_NarcPrintUpdate->getWarehouseOrderNo());
	}
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( m_Logger, e.what() );
    }

    return searchYit;
}

} // namespace usecase
} // namespace csc_phadex
