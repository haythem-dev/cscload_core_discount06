#include <customer/customercondition/customercondition.h>

namespace libcsc {
namespace customer {

CustomerCondition::CustomerCondition()
{
}

CustomerCondition::~CustomerCondition()
{
}

basar::Int16 CustomerCondition::getBranchNo() const
{
	return m_BranchNo;
}

basar::Int32 CustomerCondition::getCustomerNo() const
{
	return m_CustomerNo;
}

basar::Int32 CustomerCondition::getArticleNo() const
{
	return m_ArticleNo;
}

basar::Int32 CustomerCondition::getBaseQuantity() const
{
	return m_BaseQuantity;
}

basar::Decimal CustomerCondition::getPharmacyPurchasePrice() const
{
	return m_PharmacyPurchasePrice;
}

basar::Decimal CustomerCondition::getDiscountPercentage() const
{
	return m_DiscountPercentage;
}

basar::Decimal CustomerCondition::getDiscountPrice() const
{
	return m_DiscountPrice;
}

basar::Int16 CustomerCondition::getPTPaymentDays1() const
{
	return m_PTPaymentDays1;
}

basar::Decimal CustomerCondition::getPTDiscountPercentage1() const
{
	return m_PTDiscountPercentage1;
}

basar::Decimal CustomerCondition::getPTDiscountPrice1() const
{
	return m_PTDiscountPrice1;
}

basar::Int16 CustomerCondition::getPTPaymentDays2() const
{
	return m_PTPaymentDays2;
}

basar::Decimal CustomerCondition::getPTDiscountPercentage2() const
{
	return m_PTDiscountPercentage2;
}

basar::Decimal CustomerCondition::getPTDiscountPrice2() const
{
	return m_PTDiscountPrice2;
}

basar::Int16 CustomerCondition::getPTPaymentDays3() const
{
	return m_PTPaymentDays3;
}

basar::Decimal CustomerCondition::getPTDiscountPercentage3() const
{
	return m_PTDiscountPercentage3;
}

basar::Decimal CustomerCondition::getPTDiscountPrice3() const
{
	return m_PTDiscountPrice3;
}

basar::Int16 CustomerCondition::getPTPaymentDays4() const
{
	return m_PTPaymentDays4;
}

basar::Decimal CustomerCondition::getPTDiscountPercentage4() const
{
	return m_PTDiscountPercentage4;
}

basar::Decimal CustomerCondition::getPTDiscountPrice4() const
{
	return m_PTDiscountPrice4;
}

basar::Int16 CustomerCondition::getPTPaymentDays5() const
{
	return m_PTPaymentDays5;
}

basar::Decimal CustomerCondition::getPTDiscountPercentage5() const
{
	return m_PTDiscountPercentage5;
}

basar::Decimal CustomerCondition::getPTDiscountPrice5() const
{
	return m_PTDiscountPrice5;
}

basar::Int16 CustomerCondition::getPTPaymentDays6() const
{
	return m_PTPaymentDays6;
}

basar::Decimal CustomerCondition::getPTDiscountPercentage6() const
{
	return m_PTDiscountPercentage6;
}

basar::Decimal CustomerCondition::getPTDiscountPrice6() const
{
	return m_PTDiscountPrice6;
}

} // end namespace customer
} // end namespace libcsc

