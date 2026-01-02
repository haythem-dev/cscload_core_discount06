#include "ibtrequestremark.h"

namespace libcsc
{
namespace ibt
{
IbtRequestRemark::IbtRequestRemark()
{
    m_PropertyCollection.add( m_IbtRequestId );
    m_PropertyCollection.add( m_RemarkLevel );
    m_PropertyCollection.add( m_Remark );
}

IbtRequestRemark::~IbtRequestRemark()
{
}

const libcsc::Int32 & IbtRequestRemark::getIbtRequestId() const
{
    return m_IbtRequestId;
}

const IbtRequestRemarkLevel & IbtRequestRemark::getRemarkLevel() const
{
    return m_RemarkLevel;
}

const basar::VarString & IbtRequestRemark::getRemark() const
{
    return m_Remark;
}

const OrderRemarkType & IbtRequestRemark::getRemarkType() const
{
	return m_RemarkType;
}

void IbtRequestRemark::setIbtRequestId( const basar::Int32 ibtRequestId )
{
    m_IbtRequestId = ibtRequestId;
}

void IbtRequestRemark::setRemarkLevel( const IbtRequestRemarkLevelEnum remarkLevel )
{
    m_RemarkLevel = remarkLevel;
}

void IbtRequestRemark::setRemarkType( const OrderRemarkTypeEnum remarkType )
{
	m_RemarkType = remarkType;
}

void IbtRequestRemark::setRemark( const basar::VarString & remark )
{
    m_Remark = remark;
}

bool IbtRequestRemark::isPosRemark() const
{
    return ( OrderPosRemark == m_RemarkLevel );
}

bool IbtRequestRemark::isHeadRemark() const
{
    return ( OrderHeadRemark == m_RemarkLevel );
}

std::ostream & IbtRequestRemark::toStream( std::ostream & strm /* = std::cout */ ) const
{
    strm << "m_IbtRequestId=<" << m_IbtRequestId << ">";
    strm << ", m_RemarkLevel=<" << m_RemarkLevel << ">";
    strm << ", m_Remark=<" << m_Remark << ">";
    return strm;
}


void IbtRequestRemark::setClean()
{
    m_PropertyCollection.setClean();
}

bool IbtRequestRemark::containsDirty() const
{
    return m_PropertyCollection.containsDirty();
}

} // namespace ibt
} // namespace libcsc
