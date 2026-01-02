#include <libutil/domainmodule.h>
#include "phadextransactiondm.h"
#include "domainmodule/csc_phadex_properties_definitions.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include <libutil/util.h>
#include <libbasar_definitions.h>
#include <libbasardbaspect.h>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
using namespace basar::db::aspect;

PhadexTransactionDM::PhadexTransactionDM( const basar::db::aspect::AccessorPropertyTable_YIterator yit )
: m_Yit( yit ),
  m_Logger( csc_phadex::LoggerPool::getLoggerDomModules() )
{
    METHODNAME_DEF( PhadexTransactionDM, PhadexTransactionDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

PhadexTransactionDM::~PhadexTransactionDM()
{
    METHODNAME_DEF( PhadexTransactionDM, ~PhadexTransactionDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

basar::db::aspect::AccessorPropertyTable_YIterator PhadexTransactionDM::getYit() const
{
    METHODNAME_DEF( PhadexTransactionDM, getYit )
    BLOG_TRACE_METHOD( m_Logger, fun );

	return m_Yit;
}

basar::Int16 PhadexTransactionDM::getBranchno() const
{
    METHODNAME_DEF( PhadexTransactionDM, getBranchno )
    BLOG_TRACE_METHOD( m_Logger, fun );
    return m_Yit.getInt16( properties::BRANCH_NO );
}

void PhadexTransactionDM::setBranchno( const basar::Int16 branchNo )
{
    METHODNAME_DEF( PhadexTransactionDM, setBranchno )
    BLOG_TRACE_METHOD( m_Logger, fun );
    m_Yit.setInt16( properties::BRANCH_NO.getName(), branchNo );
}

const basar::VarString PhadexTransactionDM::getData() const
{
    METHODNAME_DEF( PhadexTransactionDM, getData )
    BLOG_TRACE_METHOD( m_Logger, fun );
    return m_Yit.getString( properties::DATA );
}

void PhadexTransactionDM::setData( const basar::VarString & strData) 
{
    METHODNAME_DEF( PhadexTransactionDM, setData )
    BLOG_TRACE_METHOD( m_Logger, fun );
    m_Yit.setString( properties::DATA.getName(), strData );
}

basar::Int16 PhadexTransactionDM::getProcessedFlag() const
{
    METHODNAME_DEF( PhadexTransactionDM, getProcessedFlag )
    BLOG_TRACE_METHOD( m_Logger, fun );
    return m_Yit.getInt16( properties::PROCESSED_FLAG );
}

void PhadexTransactionDM::setProcessedFlag( const basar::Int16 procflag ) 
{
    METHODNAME_DEF( PhadexTransactionDM, setProcessedFlag )
    BLOG_TRACE_METHOD( m_Logger, fun );
    m_Yit.setInt16( properties::PROCESSED_FLAG.getName(), procflag );
}

const basar::DateTime & PhadexTransactionDM::getCreationDateTime() const
{
    METHODNAME_DEF( PhadexTransactionDM, getCreationDateTime )
    BLOG_TRACE_METHOD( m_Logger, fun );
    return m_Yit.getDateTime( properties::CREATION_DATETIME );
}

void PhadexTransactionDM::setCreationDateTime( const basar::DateTime & creationDateTime) 
{
    METHODNAME_DEF( PhadexTransactionDM, setCreationDateTime )
    BLOG_TRACE_METHOD( m_Logger, fun );
    m_Yit.setDateTime( properties::CREATION_DATETIME.getName(), creationDateTime );
}

const basar::DateTime & PhadexTransactionDM::getTransferDateTime() const
{
    METHODNAME_DEF( PhadexTransactionDM, getTransferDateTime )
    BLOG_TRACE_METHOD( m_Logger, fun );
    return m_Yit.getDateTime( properties::TRANSFER_DATETIME );
}

void PhadexTransactionDM::setTransferDateTime( const basar::DateTime & trfDateTime)
{
    METHODNAME_DEF( PhadexTransactionDM, setTransferDateTime )
    BLOG_TRACE_METHOD( m_Logger, fun );
    m_Yit.setDateTime( properties::TRANSFER_DATETIME.getName(), trfDateTime );
}

const basar::DateTime & PhadexTransactionDM::getProcessDateTime() const
{
    METHODNAME_DEF( PhadexTransactionDM, getProcessDateTime )
    BLOG_TRACE_METHOD( m_Logger, fun );
    return m_Yit.getDateTime( properties::PROCESS_DATETIME );
}

void PhadexTransactionDM::setProcessDateTime( const basar::DateTime & processdDateTime)
{
    METHODNAME_DEF( PhadexTransactionDM, setProcessDateTime )
    BLOG_TRACE_METHOD( m_Logger, fun );
    m_Yit.setDateTime( properties::PROCESS_DATETIME.getName(), processdDateTime );
}

basar::Int16 PhadexTransactionDM::getRecordType() const
{
    METHODNAME_DEF( PhadexTransactionDM, getRecordType )
    BLOG_TRACE_METHOD( m_Logger, fun );
    return m_Yit.getInt16( properties::RECORD_TYPE );
}

void PhadexTransactionDM::setRecordType( const basar::Int16 recType )
{
    METHODNAME_DEF( PhadexTransactionDM, setRecordType )
    BLOG_TRACE_METHOD( m_Logger, fun );
    m_Yit.setInt16( properties::RECORD_TYPE.getName(), recType );
}

basar::Int32 PhadexTransactionDM::getRecordNo() const
{
    METHODNAME_DEF( PhadexTransactionDM, getRecordNo )
    BLOG_TRACE_METHOD( m_Logger, fun );
    return m_Yit.getInt32( properties::RECORD_NO );
}

void PhadexTransactionDM::setRecordNo( const basar::Int32 rrNo )
{
    METHODNAME_DEF( PhadexTransactionDM, setRecordNo )
    BLOG_TRACE_METHOD( m_Logger, fun );
    m_Yit.setInt32( properties::RECORD_NO.getName(), rrNo );
}

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex