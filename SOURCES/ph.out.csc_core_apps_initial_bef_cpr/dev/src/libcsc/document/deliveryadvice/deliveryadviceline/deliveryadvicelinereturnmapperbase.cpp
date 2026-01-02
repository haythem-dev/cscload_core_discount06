#include "deliveryadvicelinereturnmapperbase.h"
#include "deliveryadvicelinereturn.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace document {

DeliveryAdviceLineReturnMapperBase::DeliveryAdviceLineReturnMapperBase( DeliveryAdviceLineReturnPtr deliveryAdviceLineReturn ) :
	m_DeliveryAdviceLineReturn( deliveryAdviceLineReturn )
{
}

DeliveryAdviceLineReturnMapperBase::~DeliveryAdviceLineReturnMapperBase()
{
}

void DeliveryAdviceLineReturnMapperBase::map()
{
	doMap();
}

void DeliveryAdviceLineReturnMapperBase::setBranchNo(const basar::Int16 branchNo)
{
	m_DeliveryAdviceLineReturn->m_BranchNo = branchNo;
	m_DeliveryAdviceLineReturn->m_BranchNo.setClean();
}
void DeliveryAdviceLineReturnMapperBase::setCustomerNo( const basar::Int32 customerNo )
{
	m_DeliveryAdviceLineReturn->m_CustomerNo = customerNo;
	m_DeliveryAdviceLineReturn->m_CustomerNo.setClean();
}

void DeliveryAdviceLineReturnMapperBase::setDeliveryAdviceDate(const basar::Date & deliveryAdviceDate)
{
	m_DeliveryAdviceLineReturn->m_DeliveryAdviceDate = deliveryAdviceDate;
	m_DeliveryAdviceLineReturn->m_DeliveryAdviceDate.setClean();
}

void DeliveryAdviceLineReturnMapperBase::setDeliveryAdviceNo(const basar::VarString & deliveryAdviceNo)
{
	m_DeliveryAdviceLineReturn->m_DeliveryAdviceNo = deliveryAdviceNo;
	m_DeliveryAdviceLineReturn->m_DeliveryAdviceNo.setClean();
}

void DeliveryAdviceLineReturnMapperBase::setDeliveryAdvicePosNo(const basar::Int32 deliveryAdvicePosNo)
{
	m_DeliveryAdviceLineReturn->m_DeliveryAdvicePosNo = deliveryAdvicePosNo;
	m_DeliveryAdviceLineReturn->m_DeliveryAdvicePosNo.setClean();
}

void DeliveryAdviceLineReturnMapperBase::setBlockedForreturns(const basar::Int16 blockedForreturns)
{
	m_DeliveryAdviceLineReturn->m_BlockedForreturns = blockedForreturns;
	m_DeliveryAdviceLineReturn->m_BlockedForreturns.setClean();
}

void DeliveryAdviceLineReturnMapperBase::setQuantityReturned(const basar::Int32 quantityReturned)
{
	m_DeliveryAdviceLineReturn->m_QuantityReturned = quantityReturned;
	m_DeliveryAdviceLineReturn->m_QuantityReturned.setClean();
}

void DeliveryAdviceLineReturnMapperBase::setQuantityReturnedRebateInKind(const basar::Int32 quantityReturnedRebateInKind)
{
	m_DeliveryAdviceLineReturn->m_QuantityReturnedRebateInKind = quantityReturnedRebateInKind;
	m_DeliveryAdviceLineReturn->m_QuantityReturnedRebateInKind.setClean();
}

void DeliveryAdviceLineReturnMapperBase::setQuantityReturnRejected(const basar::Int32 quantityReturnRejected)
{
	m_DeliveryAdviceLineReturn->m_QuantityReturnRejected = quantityReturnRejected;
	m_DeliveryAdviceLineReturn->m_QuantityReturnRejected.setClean();
}



} // end namespace document
} // end namespace libcsc
