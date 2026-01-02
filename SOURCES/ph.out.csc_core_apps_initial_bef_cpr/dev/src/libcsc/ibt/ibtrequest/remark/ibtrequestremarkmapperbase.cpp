#include "ibtrequestremarkmapperbase.h"
#include "ibtrequestremark.h"
#include "logger/loggerpool.h"

namespace libcsc
{
namespace ibt
{
IbtRequestRemarkMapperBase::IbtRequestRemarkMapperBase( IbtRequestRemarkPtr ibtRequestRemark )
: m_IbtRequestRemark( ibtRequestRemark )
{
}

IbtRequestRemarkMapperBase::~IbtRequestRemarkMapperBase()
{
}

void IbtRequestRemarkMapperBase::map()
{
    doMap();

    std::stringstream ss;
    ss << "IbtRequestRemarkMapperBase::map(), m_IbtRequestRemark: " << *m_IbtRequestRemark << std::endl;
    BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
}

void IbtRequestRemarkMapperBase::setIbtRequestId( const basar::Int32 ibtRequestId )
{
    m_IbtRequestRemark->m_IbtRequestId = ibtRequestId;
    m_IbtRequestRemark->m_IbtRequestId.setClean();
}

void IbtRequestRemarkMapperBase::setRemarkLevel( const IbtRequestRemarkLevelEnum remarkLevel )
{
    m_IbtRequestRemark->m_RemarkLevel = remarkLevel;
    m_IbtRequestRemark->m_RemarkLevel.setClean();
}

void IbtRequestRemarkMapperBase::setRemark( const basar::VarString & remark )
{
    m_IbtRequestRemark->m_Remark = remark;
    m_IbtRequestRemark->m_Remark.setClean();
}

void IbtRequestRemarkMapperBase::setRemarkType( const OrderRemarkTypeEnum remarkType )
{
    m_IbtRequestRemark->m_RemarkType = remarkType;
    m_IbtRequestRemark->m_RemarkType.setClean();
}

} // end namespace ibt
} // end namespace libcsc
