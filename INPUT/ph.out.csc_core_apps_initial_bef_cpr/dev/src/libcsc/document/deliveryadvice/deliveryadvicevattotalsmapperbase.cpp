#include "deliveryadvicevattotalsmapperbase.h"
#include "deliveryadvicevattotals.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace document {

DeliveryAdviceVatTotalsMapperBase::DeliveryAdviceVatTotalsMapperBase( DeliveryAdviceVatTotalsPtr deliveryAdviceVatTotals ) :
	m_DeliveryAdviceVatTotals( deliveryAdviceVatTotals )
{
}

DeliveryAdviceVatTotalsMapperBase::~DeliveryAdviceVatTotalsMapperBase()
{
}

void DeliveryAdviceVatTotalsMapperBase::map()
{
	doMap();
}

void DeliveryAdviceVatTotalsMapperBase::setBranchNo( const basar::Int16 branchNo )
{
	m_DeliveryAdviceVatTotals->m_BranchNo = branchNo;
	m_DeliveryAdviceVatTotals->m_BranchNo.setClean();
}

void DeliveryAdviceVatTotalsMapperBase::setCustomerNo( const basar::Int32 customerNo )
{
	m_DeliveryAdviceVatTotals->m_CustomerNo = customerNo;
	m_DeliveryAdviceVatTotals->m_CustomerNo.setClean();
}

void DeliveryAdviceVatTotalsMapperBase::setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate )
{
	m_DeliveryAdviceVatTotals->m_DeliveryAdviceDate = deliveryAdviceDate;
	m_DeliveryAdviceVatTotals->m_DeliveryAdviceDate.setClean();
}

void DeliveryAdviceVatTotalsMapperBase::setDeliveryAdviceNo( const basar::VarString & deliveryAdviceNo )
{
	m_DeliveryAdviceVatTotals->m_DeliveryAdviceNo = deliveryAdviceNo;
	m_DeliveryAdviceVatTotals->m_DeliveryAdviceNo.setClean();
}

void DeliveryAdviceVatTotalsMapperBase::setVat( const basar::VarString & vat )
{
	m_DeliveryAdviceVatTotals->m_Vat = vat;
	m_DeliveryAdviceVatTotals->m_Vat.setClean();
}


void DeliveryAdviceVatTotalsMapperBase::setVatPercentage( const basar::Decimal & vatPercentage )
{
	m_DeliveryAdviceVatTotals->m_VatPercentage = vatPercentage;
	m_DeliveryAdviceVatTotals->m_VatPercentage.setClean();
}

void DeliveryAdviceVatTotalsMapperBase::setNetValue( const basar::Decimal & netValue )
{
	m_DeliveryAdviceVatTotals->m_NetValue = netValue;
	m_DeliveryAdviceVatTotals->m_NetValue.setClean();
}

void DeliveryAdviceVatTotalsMapperBase::setVatValue( const basar::Decimal & vatValue )
{
	m_DeliveryAdviceVatTotals->m_VatValue = vatValue;
	m_DeliveryAdviceVatTotals->m_VatValue.setClean();
}

void DeliveryAdviceVatTotalsMapperBase::setSumLineFee(const basar::Decimal & sumLineFee)
{
    m_DeliveryAdviceVatTotals->m_SumLineFee = sumLineFee;
    m_DeliveryAdviceVatTotals->m_SumLineFee.setClean();
}

void DeliveryAdviceVatTotalsMapperBase::setSumPackageFee(const basar::Decimal & sumPackageFee)
{
    m_DeliveryAdviceVatTotals->m_SumPackageFee = sumPackageFee;
    m_DeliveryAdviceVatTotals->m_SumPackageFee.setClean();
}

} // end namespace document
} // end namespace libcsc
