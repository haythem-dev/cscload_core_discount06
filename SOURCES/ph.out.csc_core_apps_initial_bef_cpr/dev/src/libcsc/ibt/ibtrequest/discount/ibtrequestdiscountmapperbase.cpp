#include "ibtrequestdiscountmapperbase.h"
#include "ibtrequestdiscount.h"
#include <logger/loggerpool.h>

namespace libcsc
{
namespace ibt
{
IbtRequestDiscountMapperBase::IbtRequestDiscountMapperBase( IbtRequestDiscountPtr ibtRequestDiscount )
: m_IbtRequestDiscount( ibtRequestDiscount )
{
}

IbtRequestDiscountMapperBase::~IbtRequestDiscountMapperBase()
{
}

void IbtRequestDiscountMapperBase::map()
{
    doMap();

    std::stringstream ss;
    ss << "IbtRequestDiscountMapperBase::map(), m_IbtRequestDiscount: " << *m_IbtRequestDiscount << std::endl;
    BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
}

void IbtRequestDiscountMapperBase::setIbtRequestId( const basar::Int32 ibtRequestId )
{
    m_IbtRequestDiscount->m_IbtRequestId = ibtRequestId;
    m_IbtRequestDiscount->m_IbtRequestId.setClean();
}

void IbtRequestDiscountMapperBase::setDiscountType( const IbtRequestDiscountTypeEnum discountType )
{
    m_IbtRequestDiscount->m_DiscountType = discountType;
    m_IbtRequestDiscount->m_DiscountType.setClean();
}

void IbtRequestDiscountMapperBase::setPharmacyGroupId( const basar::VarString & pharmacyGroupId )
{
    m_IbtRequestDiscount->m_PharmacyGroupId = pharmacyGroupId;
    m_IbtRequestDiscount->m_PharmacyGroupId.setClean();
}

void IbtRequestDiscountMapperBase::setPaymentTargetNo( const basar::Int16 paymentTargetNo )
{
    m_IbtRequestDiscount->m_PaymentTargetNo = paymentTargetNo;
    m_IbtRequestDiscount->m_PaymentTargetNo.setClean();
}

void IbtRequestDiscountMapperBase::setDiscountValuePct( const basar::Decimal & discountValuePct )
{
    m_IbtRequestDiscount->m_DiscountValuePct = discountValuePct;
    m_IbtRequestDiscount->m_DiscountValuePct.setClean();
}

void IbtRequestDiscountMapperBase::setDiscountValuePctMan( const basar::Decimal & discountValuePctMan )
{
    m_IbtRequestDiscount->m_DiscountValuePctMan = discountValuePctMan;
    m_IbtRequestDiscount->m_DiscountValuePctMan.setClean();
}

void IbtRequestDiscountMapperBase::setFixedPrice(const basar::Decimal & fixedprice)
{
	m_IbtRequestDiscount->m_FixedPrice = fixedprice;
	m_IbtRequestDiscount->m_FixedPrice.setClean();
}

} // end namespace ibt
} // end namespace libcsc
