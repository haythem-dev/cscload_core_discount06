#include <customer/customercondition/customerconditionmapperbase.h>
#include <customer/customercondition/customercondition.h>

namespace libcsc {
namespace customer {

CustomerConditionMapperBase::CustomerConditionMapperBase(CustomerConditionPtr cuco)
: m_CustomerCondition(cuco)
{
}

CustomerConditionMapperBase::~CustomerConditionMapperBase()
{
}

void CustomerConditionMapperBase::map()
{
    doMap();
}

void CustomerConditionMapperBase::setBranchNo( const basar::Int16 branchNo )
{
	m_CustomerCondition->m_BranchNo = branchNo;
	m_CustomerCondition->m_BranchNo.setClean();
}

void CustomerConditionMapperBase::setCustomerNo(const basar::Int32 customerNo)
{
	m_CustomerCondition->m_CustomerNo = customerNo;
	m_CustomerCondition->m_CustomerNo.setClean();
}

void CustomerConditionMapperBase::setArticleNo(const basar::Int32 articleNo)
{
	m_CustomerCondition->m_ArticleNo = articleNo;
	m_CustomerCondition->m_ArticleNo.setClean();
}

void CustomerConditionMapperBase::setBaseQuantity(const basar::Int32 baseQuantity)
{
	m_CustomerCondition->m_BaseQuantity = baseQuantity;
	m_CustomerCondition->m_BaseQuantity.setClean();
}

void CustomerConditionMapperBase::setPharmacyPurchasePrice(const basar::Decimal& PharmacyPurchasePrice)
{
	m_CustomerCondition->m_PharmacyPurchasePrice = PharmacyPurchasePrice;
	m_CustomerCondition->m_PharmacyPurchasePrice.setClean();
}

void CustomerConditionMapperBase::setDiscountPercentage(const basar::Decimal& discountPercentage)
{
	m_CustomerCondition->m_DiscountPercentage = discountPercentage;
	m_CustomerCondition->m_DiscountPercentage.setClean();
}

void CustomerConditionMapperBase::setDiscountPrice(const basar::Decimal& discountPrice)
{
	m_CustomerCondition->m_DiscountPrice = discountPrice;
	m_CustomerCondition->m_DiscountPrice.setClean();
}

void CustomerConditionMapperBase::setPTPaymentDays1(const basar::Int16 paymentDays)
{
	m_CustomerCondition->m_PTPaymentDays1 = paymentDays;
	m_CustomerCondition->m_PTPaymentDays1.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPercentage1(const basar::Decimal& discountPct)
{
	m_CustomerCondition->m_PTDiscountPercentage1 = discountPct;
	m_CustomerCondition->m_PTDiscountPercentage1.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPrice1(const basar::Decimal& discountPrice)
{
	m_CustomerCondition->m_PTDiscountPrice1 = discountPrice;
	m_CustomerCondition->m_PTDiscountPrice1.setClean();
}

void CustomerConditionMapperBase::setPTPaymentDays2(const basar::Int16 paymentDays)
{
	m_CustomerCondition->m_PTPaymentDays2 = paymentDays;
	m_CustomerCondition->m_PTPaymentDays2.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPercentage2(const basar::Decimal& discountPct)
{
	m_CustomerCondition->m_PTDiscountPercentage2 = discountPct;
	m_CustomerCondition->m_PTDiscountPercentage2.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPrice2(const basar::Decimal& discountPrice)
{
	m_CustomerCondition->m_PTDiscountPrice2 = discountPrice;
	m_CustomerCondition->m_PTDiscountPrice2.setClean();
}

void CustomerConditionMapperBase::setPTPaymentDays3(const basar::Int16 paymentDays)
{
	m_CustomerCondition->m_PTPaymentDays3 = paymentDays;
	m_CustomerCondition->m_PTPaymentDays3.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPercentage3(const basar::Decimal& discountPct)
{
	m_CustomerCondition->m_PTDiscountPercentage3 = discountPct;
	m_CustomerCondition->m_PTDiscountPercentage3.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPrice3(const basar::Decimal& discountPrice)
{
	m_CustomerCondition->m_PTDiscountPrice3 = discountPrice;
	m_CustomerCondition->m_PTDiscountPrice3.setClean();
}

void CustomerConditionMapperBase::setPTPaymentDays4(const basar::Int16 paymentDays)
{
	m_CustomerCondition->m_PTPaymentDays4 = paymentDays;
	m_CustomerCondition->m_PTPaymentDays4.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPercentage4(const basar::Decimal& discountPct)
{
	m_CustomerCondition->m_PTDiscountPercentage4 = discountPct;
	m_CustomerCondition->m_PTDiscountPercentage4.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPrice4(const basar::Decimal& discountPrice)
{
	m_CustomerCondition->m_PTDiscountPrice4 = discountPrice;
	m_CustomerCondition->m_PTDiscountPrice4.setClean();
}

void CustomerConditionMapperBase::setPTPaymentDays5(const basar::Int16 paymentDays)
{
	m_CustomerCondition->m_PTPaymentDays5 = paymentDays;
	m_CustomerCondition->m_PTPaymentDays5.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPercentage5(const basar::Decimal& discountPct)
{
	m_CustomerCondition->m_PTDiscountPercentage5 = discountPct;
	m_CustomerCondition->m_PTDiscountPercentage5.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPrice5(const basar::Decimal& discountPrice)
{
	m_CustomerCondition->m_PTDiscountPrice5 = discountPrice;
	m_CustomerCondition->m_PTDiscountPrice5.setClean();
}

void CustomerConditionMapperBase::setPTPaymentDays6(const basar::Int16 paymentDays)
{
	m_CustomerCondition->m_PTPaymentDays6 = paymentDays;
	m_CustomerCondition->m_PTPaymentDays6.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPercentage6(const basar::Decimal& discountPct)
{
	m_CustomerCondition->m_PTDiscountPercentage6 = discountPct;
	m_CustomerCondition->m_PTDiscountPercentage6.setClean();
}

void CustomerConditionMapperBase::setPTDiscountPrice6(const basar::Decimal& discountPrice)
{
	m_CustomerCondition->m_PTDiscountPrice6 = discountPrice;
	m_CustomerCondition->m_PTDiscountPrice6.setClean();
}


} // end namespace customer
} // end namespace libcsc

