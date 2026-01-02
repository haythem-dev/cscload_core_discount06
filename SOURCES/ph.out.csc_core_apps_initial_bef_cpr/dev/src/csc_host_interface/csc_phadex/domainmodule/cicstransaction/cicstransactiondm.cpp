#include <libutil/domainmodule.h>
#include "cicstransactiondm.h"
#include "domainmodule/csc_phadex_properties_definitions.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include <libutil/util.h>
#include <libbasar_definitions.h>
#include <libbasardbaspect.h>

namespace csc_phadex
{
namespace domMod
{
namespace cicsTransaction
{
using namespace basar::db::aspect;

CICSTransactionDM::CICSTransactionDM( const basar::db::aspect::AccessorPropertyTable_YIterator yit )
: m_Yit( yit ),
  m_Logger( csc_phadex::LoggerPool::getLoggerDomModules() )
{
    METHODNAME_DEF( CICSTransactionDM, CICSTransactionDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

CICSTransactionDM::~CICSTransactionDM()
{
    METHODNAME_DEF( CICSTransactionDM, ~CICSTransactionDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

basar::Int16 CICSTransactionDM::getBranchno() const
{
    METHODNAME_DEF( CICSTransactionDM, getBranchno )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Yit.getInt16( properties::KSC_FIL );
}

basar::Int16 CICSTransactionDM::getRecordType() const
{
    METHODNAME_DEF( CICSTransactionDM, getRecordType )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Yit.getInt16( properties::KSC_SA );
}

basar::Int32 CICSTransactionDM::getCreationDate() const
{
    METHODNAME_DEF( CICSTransactionDM, getCreationDate )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Yit.getInt32( properties::KSC_DATUM );
}

basar::Int32 CICSTransactionDM::getCreationTime() const
{
    METHODNAME_DEF( CICSTransactionDM, getCreationTime )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Yit.getInt32( properties::KSC_ZEIT );
}

const basar::VarString CICSTransactionDM::getData() const
{
    METHODNAME_DEF( CICSTransactionDM, getData )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Yit.getString( properties::KSC_DATA );
}

basar::Int32 CICSTransactionDM::getRecordNo() const
{
    METHODNAME_DEF( CICSTransactionDM, getRecordNo )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return m_Yit.getInt32( properties::RRDS_RRN );
}

} // end namespace cicsTransaction
} // end namespace domMod
} // end namespace csc_phadex