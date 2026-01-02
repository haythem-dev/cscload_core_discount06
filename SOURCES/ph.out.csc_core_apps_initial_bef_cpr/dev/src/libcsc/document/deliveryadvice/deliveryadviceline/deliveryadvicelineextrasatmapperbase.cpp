#include "deliveryadvicelineextrasatmapperbase.h"
#include "deliveryadvicelineextrasat.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace document {

DeliveryAdviceLineExtrasATMapperBase::DeliveryAdviceLineExtrasATMapperBase( DeliveryAdviceLineExtrasATPtr deliveryAdviceLineExtrasAT ) :
	m_DeliveryAdviceLineExtrasAT( deliveryAdviceLineExtrasAT )
{
}

DeliveryAdviceLineExtrasATMapperBase::~DeliveryAdviceLineExtrasATMapperBase()
{
}

void DeliveryAdviceLineExtrasATMapperBase::map()
{
	doMap();
}

void	DeliveryAdviceLineExtrasATMapperBase::setBranchNo(const basar::Int16 branchNo)
{
	m_DeliveryAdviceLineExtrasAT->m_BranchNo = branchNo;
	m_DeliveryAdviceLineExtrasAT->m_BranchNo.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setCustomerNo( const basar::Int32 customerNo )
{
	m_DeliveryAdviceLineExtrasAT->m_CustomerNo = customerNo;
	m_DeliveryAdviceLineExtrasAT->m_CustomerNo.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate )
{
	m_DeliveryAdviceLineExtrasAT->m_DeliveryAdviceDate = deliveryAdviceDate;
	m_DeliveryAdviceLineExtrasAT->m_DeliveryAdviceDate.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setPharmosOrderNo( const basar::Int32 pharmosOrderNo )
{
	m_DeliveryAdviceLineExtrasAT->m_PharmosOrderNo = pharmosOrderNo;
	m_DeliveryAdviceLineExtrasAT->m_PharmosOrderNo.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setPharmosOrderPosNo( const basar::Int32 pharmosOrderPosNo )
{
	m_DeliveryAdviceLineExtrasAT->m_PharmosOrderPosNo = pharmosOrderPosNo;
	m_DeliveryAdviceLineExtrasAT->m_PharmosOrderPosNo.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setDeliveryPosNo( const basar::Int32 deliveryPosNo )
{
	m_DeliveryAdviceLineExtrasAT->m_DeliveryPosNo = deliveryPosNo;
	m_DeliveryAdviceLineExtrasAT->m_DeliveryPosNo.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setIsNarcotic( const bool isNarcotic )
{
	m_DeliveryAdviceLineExtrasAT->m_IsNarcotic = isNarcotic;
	m_DeliveryAdviceLineExtrasAT->m_IsNarcotic.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setIsRX(const bool isRX)
{
	m_DeliveryAdviceLineExtrasAT->m_IsRX = isRX;
	m_DeliveryAdviceLineExtrasAT->m_IsRX.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setIsPsychotropic( const bool isPsychotropic)
{
	m_DeliveryAdviceLineExtrasAT->m_IsPsychotropic = isPsychotropic;
	m_DeliveryAdviceLineExtrasAT->m_IsPsychotropic.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setIsVeterinary( const bool isVeterinary )
{
	m_DeliveryAdviceLineExtrasAT->m_IsVeterinary = isVeterinary;
	m_DeliveryAdviceLineExtrasAT->m_IsVeterinary.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setIsHazardous( const bool isHazardous )
{
	m_DeliveryAdviceLineExtrasAT->m_IsHazardous = isHazardous;
	m_DeliveryAdviceLineExtrasAT->m_IsHazardous.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setIsReportable( const bool isReportable)
{
	m_DeliveryAdviceLineExtrasAT->m_IsReportable = isReportable;
	m_DeliveryAdviceLineExtrasAT->m_IsReportable.setClean();
}

void	DeliveryAdviceLineExtrasATMapperBase::setIsShortExpiry(const bool isShortExpiry)
{
	m_DeliveryAdviceLineExtrasAT->m_IsShortExpiry = isShortExpiry;
	m_DeliveryAdviceLineExtrasAT->m_IsShortExpiry.setClean();
}

} // end namespace document
} // end namespace libcsc
