#include "cscordertypebatchconfig.h"

namespace libcsc
{
namespace cscordertype
{
CSCOrderTypeBatchConfig::CSCOrderTypeBatchConfig()
{
    m_PropertyCollection.add( m_BranchNo );
    m_PropertyCollection.add( m_OrderType );
    m_PropertyCollection.add( m_AllowDesiredBatch );
    m_PropertyCollection.add( m_AllowFixedBatch );
    m_PropertyCollection.add( m_ForbidUserChange );
}

CSCOrderTypeBatchConfig::~CSCOrderTypeBatchConfig()
{
}

const libcsc::Int16 & CSCOrderTypeBatchConfig::getBranchNo() const
{
	return m_BranchNo;
}

const libcsc::VarString & CSCOrderTypeBatchConfig::getOrderType() const
{
	return m_OrderType;
}

const libcsc::Bool & CSCOrderTypeBatchConfig::getAllowDesiredBatch() const
{
	return m_AllowDesiredBatch;
}

const libcsc::Bool & CSCOrderTypeBatchConfig::getAllowFixedBatch() const
{
	return m_AllowFixedBatch;
}

const libcsc::Bool & CSCOrderTypeBatchConfig::getForbidUserChange() const
{
	return m_ForbidUserChange;
}

void CSCOrderTypeBatchConfig::setBranchNo( const basar::Int16 branchno )
{
	m_BranchNo = branchno;
}

void CSCOrderTypeBatchConfig::setOrderType( const basar::VarString & orderType )
{
	m_OrderType = orderType;
}

void CSCOrderTypeBatchConfig::setAllowDesiredBatch( const bool allowDesiredBatch )
{
	m_AllowDesiredBatch = allowDesiredBatch;
}

void CSCOrderTypeBatchConfig::setAllowFixedBatch( const bool allowFixedBatch )
{
	m_AllowFixedBatch = allowFixedBatch;
}

void CSCOrderTypeBatchConfig::setForbidUserChange( const bool forbidUserChange )
{
	m_ForbidUserChange = forbidUserChange;
}

std::ostream & CSCOrderTypeBatchConfig::toStream( std::ostream & strm /* = std::cout */ ) const
{
    strm << "m_BranchNo=<" << m_BranchNo << ">";
    strm << ", m_OrderType=<" << m_OrderType << ">";
    strm << ", m_AllowDesiredBatch=<" << m_AllowDesiredBatch << ">";
    strm << ", m_AllowFixedBatch=<" << m_AllowFixedBatch << ">";
    strm << ", m_ForbidUserChange=<" << m_ForbidUserChange << ">";
    return strm;
}

void CSCOrderTypeBatchConfig::setClean()
{
    m_PropertyCollection.setClean();
}

bool CSCOrderTypeBatchConfig::containsDirty() const
{
    return m_PropertyCollection.containsDirty();
}

} // namespace cscordertype
} // namespace libcsc
