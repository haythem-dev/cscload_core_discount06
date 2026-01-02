#include "ibtresponsemapperbase.h"
#include "ibtresponse.h"
#include <logger/loggerpool.h>

namespace libcsc
{
namespace ibt
{
IbtResponseMapperBase::IbtResponseMapperBase( IbtResponsePtr ibtResponse )
: m_IbtResponse( ibtResponse )
{
}

IbtResponseMapperBase::~IbtResponseMapperBase()
{
}

void IbtResponseMapperBase::map()
{
    doMap();

    std::stringstream ss;
    ss << "IbtResponseMapperBase::map(), m_IbtResponse: " << *m_IbtResponse << std::endl;
    BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
}

void IbtResponseMapperBase::setIbtResponseId( const basar::Int32 ibtResponseId )
{
	m_IbtResponse->m_IbtResponseId = ibtResponseId;
    m_IbtResponse->m_IbtResponseId.setClean();
}

void IbtResponseMapperBase::setIbtRequestId( const basar::Int32 ibtRequestId )
{
    m_IbtResponse->m_IbtRequestId = ibtRequestId;
    m_IbtResponse->m_IbtRequestId.setClean();
}

void IbtResponseMapperBase::setIbtOrderNo( const basar::Int32 ibtOrderNo )
{
	m_IbtResponse->m_IbtOrderNo = ibtOrderNo;
    m_IbtResponse->m_IbtOrderNo.setClean();
}

void IbtResponseMapperBase::setIbtOrderPosNo( const basar::Int32 ibtOrderPosNo )
{
	m_IbtResponse->m_IbtOrderPosNo = ibtOrderPosNo;
    m_IbtResponse->m_IbtOrderPosNo.setClean();
}

void IbtResponseMapperBase::setCreationDateTime( const basar::DateTime & creationDateTime )
{
	m_IbtResponse->m_CreationDateTime = creationDateTime;
    m_IbtResponse->m_CreationDateTime.setClean();
}

void IbtResponseMapperBase::setIbtConfirmedQuantity( const basar::Int32 quantity )
{
	m_IbtResponse->m_IbtConfirmedQuantity = quantity;
    m_IbtResponse->m_IbtConfirmedQuantity.setClean();
}

} // end namespace ibt
} // end namespace libcsc
