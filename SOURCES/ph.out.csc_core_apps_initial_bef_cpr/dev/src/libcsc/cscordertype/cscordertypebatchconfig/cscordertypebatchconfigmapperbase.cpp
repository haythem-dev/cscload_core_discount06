#include "cscordertypebatchconfigmapperbase.h"
#include "cscordertypebatchconfig.h"
#include <logger/loggerpool.h>

namespace libcsc
{
namespace cscordertype
{
CSCOrderTypeBatchConfigMapperBase::CSCOrderTypeBatchConfigMapperBase( CSCOrderTypeBatchConfigPtr batchConfig )
: m_BatchConfig( batchConfig )
{
}

CSCOrderTypeBatchConfigMapperBase::~CSCOrderTypeBatchConfigMapperBase()
{
}

void CSCOrderTypeBatchConfigMapperBase::map()
{
    doMap();

	// TODO
    std::stringstream ss;
    ss << "CSCOrderTypeBatchConfigMapperBase::map(), m_BatchConfig: " << *m_BatchConfig << std::endl;
    BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
}

void CSCOrderTypeBatchConfigMapperBase::setBranchNo( const basar::Int16 branchno )
{
    m_BatchConfig->m_BranchNo = branchno;
    m_BatchConfig->m_BranchNo.setClean();
}

void CSCOrderTypeBatchConfigMapperBase::setOrderType( const basar::VarString & orderType )
{
    m_BatchConfig->m_OrderType = orderType;
    m_BatchConfig->m_OrderType.setClean();
}

void CSCOrderTypeBatchConfigMapperBase::setAllowDesiredBatch( const bool allowDesiredBatch )
{
    m_BatchConfig->m_AllowDesiredBatch = allowDesiredBatch;
    m_BatchConfig->m_AllowDesiredBatch.setClean();
}

void CSCOrderTypeBatchConfigMapperBase::setAllowFixedBatch( const bool allowFixedBatch )
{
    m_BatchConfig->m_AllowFixedBatch = allowFixedBatch;
    m_BatchConfig->m_AllowFixedBatch.setClean();
}

void CSCOrderTypeBatchConfigMapperBase::setForbidUserChange( const bool forbidUserChange )
{
    m_BatchConfig->m_ForbidUserChange = forbidUserChange;
    m_BatchConfig->m_ForbidUserChange.setClean();
}

} // end namespace cscordertype
} // end namespace libcsc
