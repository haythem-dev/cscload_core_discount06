#include "orderbasevaluegetter.h"

namespace libcsc
{
namespace discount
{
OrderBaseValueGetter::OrderBaseValueGetter()
{
}

OrderBaseValueGetter::~OrderBaseValueGetter()
{
}

basar::Int16 OrderBaseValueGetter::getBranchNo() const
{
	return 5;
}

basar::Int32 OrderBaseValueGetter::getCustomerNo() const
{
	return 4711;
}

basar::Int32 OrderBaseValueGetter::getOrderNo() const
{
	return 700009;
}

basar::Int32 OrderBaseValueGetter::getPositionNo() const
{
	return 1;
}

basar::Int32 OrderBaseValueGetter::getArticleNo() const
{
	return 78597;
}

basar::Int32 OrderBaseValueGetter::getItemQty() const
{
	return 22;
}

const basar::Decimal OrderBaseValueGetter::getItemPrice() const
{
	return basar::Decimal(123.45);
}

const basar::Decimal OrderBaseValueGetter::getItemValue() const
{
	return getItemPrice() * getItemQty();
}

const basar::VarString OrderBaseValueGetter::getAllOrderItems() const // komma seperated list of all articles in order
{
	return "112, 78597, 78605";
}

} // end namespace discount
} // end namespace libcsc
