#include "ibtresponse.h"
//#include "iibtrequest.h"
#include <logger/loggerpool.h>

namespace libcsc
{
namespace ibt
{
IbtResponse::IbtResponse()
{
    m_PropertyCollection.add( m_IbtRequestId );
    m_PropertyCollection.add( m_IbtResponseId );
    m_PropertyCollection.add( m_IbtOrderNo );
    m_PropertyCollection.add( m_IbtOrderPosNo );
    m_PropertyCollection.add( m_CreationDateTime );
    m_PropertyCollection.add( m_IbtConfirmedQuantity );
}

IbtResponse::~IbtResponse()
{
}

const libcsc::Int32 & IbtResponse::getIbtResponseId() const
{
    return m_IbtResponseId;
}

const basar::Int32 & IbtResponse::getIbtRequestId() const
{
    return m_IbtRequestId;
}

const basar::Int32 & IbtResponse::getIbtOrderNo() const
{
    return m_IbtOrderNo;
}

const basar::Int32 & IbtResponse::getIbtOrderPosNo() const
{
    return m_IbtOrderPosNo;
}

const basar::DateTime & IbtResponse::getCreationDateTime() const
{
    return m_CreationDateTime;
}

const basar::Int32 & IbtResponse::getIbtConfirmedQuantity() const
{
    return m_IbtConfirmedQuantity;
}


void IbtResponse::setIbtResponseId( const basar::Int32 ibtResponseId )
{
    //if (m_IbtResponseId.isUnset()) // PK only set once
    //{
        m_IbtResponseId = ibtResponseId;
    //}
}

void IbtResponse::setIbtRequestId( const basar::Int32 ibtRequestId )
{
    //if (m_IbtRequestId.isUnset()) // PK only set once
    //{
        m_IbtRequestId = ibtRequestId;
    //}
}

void IbtResponse::setIbtOrderNo( const basar::Int32 ibtOrderNo )
{
	m_IbtOrderNo = ibtOrderNo;
}

void IbtResponse::setIbtOrderPosNo( const basar::Int32 ibtOrderPosNo )
{
	m_IbtOrderPosNo = ibtOrderPosNo;
}

void IbtResponse::setIbtConfirmedQuantity( const basar::Int32 quantity )
{
    m_IbtConfirmedQuantity = quantity;
}

void IbtResponse::setNoBooking()
{
	setIbtConfirmedQuantity( 0 ); 
	setIbtOrderPosNo( 0 ); 
	setIbtOrderNo( 0 );
}

std::ostream & IbtResponse::toStream( std::ostream& strm ) const
{
    strm << "m_IbtRequestId=<" << m_IbtRequestId << ">";
    strm << ", m_IbtResponseId=<" << m_IbtResponseId << ">";
    strm << ", m_IbtOrderNo=<" << m_IbtOrderNo << ">";
    strm << ", m_IbtOrderPosNo=<" << m_IbtOrderPosNo << ">";
    strm << ", m_CreationDateTime=<" << m_CreationDateTime << ">";
    strm << ", m_IbtConfirmedQuantity=<" << m_IbtConfirmedQuantity << ">";
    return strm;
}

void IbtResponse::setClean()
{
	m_PropertyCollection.setClean();
}

bool IbtResponse::containsDirty() const
{
	return m_PropertyCollection.containsDirty();
}

} // namespace ibt
} // namespace libcsc
