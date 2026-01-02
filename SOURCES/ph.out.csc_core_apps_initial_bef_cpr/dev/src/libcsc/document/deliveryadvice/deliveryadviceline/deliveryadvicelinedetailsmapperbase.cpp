#include "deliveryadvicelinedetailsmapperbase.h"
#include "deliveryadvicelinedetails.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace document {

DeliveryAdviceLineDetailsMapperBase::DeliveryAdviceLineDetailsMapperBase( DeliveryAdviceLineDetailsPtr deliveryAdviceLineDetails ) :
	m_DeliveryAdviceLineDetails( deliveryAdviceLineDetails )
{
}

DeliveryAdviceLineDetailsMapperBase::~DeliveryAdviceLineDetailsMapperBase()
{
}

void DeliveryAdviceLineDetailsMapperBase::map()
{
	doMap();
}

void	DeliveryAdviceLineDetailsMapperBase::setBranchNo(const basar::Int16 branchNo)
{
	m_DeliveryAdviceLineDetails->m_BranchNo = branchNo;
	m_DeliveryAdviceLineDetails->m_BranchNo.setClean();
}

void	DeliveryAdviceLineDetailsMapperBase::setCustomerNo( const basar::Int32 customerNo )
{
	m_DeliveryAdviceLineDetails->m_CustomerNo = customerNo;
	m_DeliveryAdviceLineDetails->m_CustomerNo.setClean();
}

void	DeliveryAdviceLineDetailsMapperBase::setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate )
{
	m_DeliveryAdviceLineDetails->m_DeliveryAdviceDate = deliveryAdviceDate;
	m_DeliveryAdviceLineDetails->m_DeliveryAdviceDate.setClean();
}

void	DeliveryAdviceLineDetailsMapperBase::setPharmosOrderNo( const basar::Int32 pharmosOrderNo )
{
	m_DeliveryAdviceLineDetails->m_PharmosOrderNo = pharmosOrderNo;
	m_DeliveryAdviceLineDetails->m_PharmosOrderNo.setClean();
}

void	DeliveryAdviceLineDetailsMapperBase::setPharmosOrderPosNo( const basar::Int32 pharmosOrderPosNo )
{
	m_DeliveryAdviceLineDetails->m_PharmosOrderPosNo = pharmosOrderPosNo;
	m_DeliveryAdviceLineDetails->m_PharmosOrderPosNo.setClean();
}

void	DeliveryAdviceLineDetailsMapperBase::setDeliveryPosNo( const basar::Int32 deliveryPosNo )
{
	m_DeliveryAdviceLineDetails->m_DeliveryPosNo = deliveryPosNo;
	m_DeliveryAdviceLineDetails->m_DeliveryPosNo.setClean();
}

void	DeliveryAdviceLineDetailsMapperBase::setQuantityDelivery( const basar::Int32 quantityDelivery )
{
	m_DeliveryAdviceLineDetails->m_QuantityDelivery = quantityDelivery;
	m_DeliveryAdviceLineDetails->m_QuantityDelivery.setClean();
}

void	DeliveryAdviceLineDetailsMapperBase::setBatch(const basar::VarString & batch)
{
	m_DeliveryAdviceLineDetails->m_Batch = batch;
	m_DeliveryAdviceLineDetails->m_Batch.setClean();
}

void	DeliveryAdviceLineDetailsMapperBase::setExpiryDate( const basar::Date& expiryDate )
{
	m_DeliveryAdviceLineDetails->m_ExpiryDate = expiryDate;
	m_DeliveryAdviceLineDetails->m_ExpiryDate.setClean();
}

void	DeliveryAdviceLineDetailsMapperBase::setPackageId( const basar::Int32 packageId )
{
	m_DeliveryAdviceLineDetails->m_PackageId = packageId;
	m_DeliveryAdviceLineDetails->m_PackageId.setClean();
}

void	DeliveryAdviceLineDetailsMapperBase::setTrackingId( const basar::VarString & trackingId )
{
	m_DeliveryAdviceLineDetails->m_TrackingId = trackingId;
	m_DeliveryAdviceLineDetails->m_TrackingId.setClean();
}

void	DeliveryAdviceLineDetailsMapperBase::setQuantityLack( const basar::Int32 quantityLack)
{
	m_DeliveryAdviceLineDetails->m_QuantityLack = quantityLack;
	m_DeliveryAdviceLineDetails->m_QuantityLack.setClean();
}

void DeliveryAdviceLineDetailsMapperBase::setPreCalcBatchChanged(const basar::Int16 preCalcBatchChanged)
{
	m_DeliveryAdviceLineDetails->m_PreCalcBatchChanged = preCalcBatchChanged;
	m_DeliveryAdviceLineDetails->m_PreCalcBatchChanged.setClean();
}

} // end namespace document
} // end namespace libcsc
