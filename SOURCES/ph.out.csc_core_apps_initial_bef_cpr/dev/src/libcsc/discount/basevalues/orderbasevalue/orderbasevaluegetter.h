#ifndef GUARD_LIBCSC_ORDER_BASE_VALUE_GETTER_H
#define GUARD_LIBCSC_ORDER_BASE_VALUE_GETTER_H

#include "iorderbasevaluegetter.h"

namespace libcsc
{
namespace discount
{
class OrderBaseValueGetter : public IOrderBaseValueGetter
{
public:
	// TODO: pxOrder, pxOrderItem, pxKunde
	OrderBaseValueGetter();
	virtual ~OrderBaseValueGetter();

	virtual basar::Int16 getBranchNo() const;
	virtual basar::Int32 getCustomerNo() const;
	virtual basar::Int32 getOrderNo() const;
	virtual basar::Int32 getPositionNo() const;
	virtual basar::Int32 getArticleNo() const;
	virtual basar::Int32 getItemQty() const; // baseqty
	virtual const basar::Decimal getItemPrice() const; // baseprice
	virtual const basar::Decimal getItemValue() const; // baseprice * basqty
	virtual const basar::VarString getAllOrderItems() const; // komma seperated list of all articles in order

	// TODO: PZN (position-collection?), Artikelgruppen, Hersteller des Artikels, Herstellergruppen, zartikel.std_menge zum Vergleich gg. base_mult_std_qty
	// (kdgruppe, einkaufsgruppe sollten nicht nötig sein, da nur OrderBaseValues selektiert werden, die dazu passen!)
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_BASE_VALUE_GETTER_H
