#include "deliveryadviceremarksmapperbase.h"
#include "deliveryadviceremarks.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace document {

DeliveryAdviceRemarksMapperBase::DeliveryAdviceRemarksMapperBase( DeliveryAdviceRemarksPtr deliveryAdviceRemarks ) :
	m_DeliveryAdviceRemarks( deliveryAdviceRemarks )
{
}

DeliveryAdviceRemarksMapperBase::~DeliveryAdviceRemarksMapperBase()
{
}

void DeliveryAdviceRemarksMapperBase::map()
{
	doMap();
}

void DeliveryAdviceRemarksMapperBase::setBranchNo( const basar::Int16 branchNo )
{
	m_DeliveryAdviceRemarks->m_BranchNo = branchNo;
	m_DeliveryAdviceRemarks->m_BranchNo.setClean();
}

void DeliveryAdviceRemarksMapperBase::setCustomerNo( const basar::Int32 customerNo )
{
	m_DeliveryAdviceRemarks->m_CustomerNo = customerNo;
	m_DeliveryAdviceRemarks->m_CustomerNo.setClean();
}

void DeliveryAdviceRemarksMapperBase::setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate )
{
	m_DeliveryAdviceRemarks->m_DeliveryAdviceDate = deliveryAdviceDate;
	m_DeliveryAdviceRemarks->m_DeliveryAdviceDate.setClean();
}

void DeliveryAdviceRemarksMapperBase::setCSCOrderNo( const basar::Int32 & CSCOrderNo )
{
	m_DeliveryAdviceRemarks->m_CSCOrderNo = CSCOrderNo;
	m_DeliveryAdviceRemarks->m_CSCOrderNo.setClean();
}


void DeliveryAdviceRemarksMapperBase::setCSCOrderPosNo( const basar::Int32 CSCOrderPosNo )
{
	m_DeliveryAdviceRemarks->m_CSCOrderPosNo = CSCOrderPosNo;
	m_DeliveryAdviceRemarks->m_CSCOrderPosNo.setClean();
}

void DeliveryAdviceRemarksMapperBase::setRemarkType( const ::OrderRemarkTypeEnum remarkType )
{
	m_DeliveryAdviceRemarks->m_RemarkType = remarkType;
	m_DeliveryAdviceRemarks->m_RemarkType.setClean();
}

void DeliveryAdviceRemarksMapperBase::setSerialNo( const basar::Int16 serialNo )
{
	m_DeliveryAdviceRemarks->m_SerialNo = serialNo;
	m_DeliveryAdviceRemarks->m_SerialNo.setClean();
}

void DeliveryAdviceRemarksMapperBase::setRemarkText( const basar::VarString & remarkText )
{
	m_DeliveryAdviceRemarks->m_RemarkText = remarkText;
	m_DeliveryAdviceRemarks->m_RemarkText.setClean();
}


} // end namespace document
} // end namespace libcsc
