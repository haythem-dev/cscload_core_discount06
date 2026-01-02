#ifndef GUARD_LIBCSC_I_ORDER_BASE_VALUE_GETTER_H
#define GUARD_LIBCSC_I_ORDER_BASE_VALUE_GETTER_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_decimal.h>
#include <discount/basevalues/orderbasevalue/iarticleclassificationgetterptr.h>
#include <discount/basevalues/orderbasevalue/orderitembasevaluecollectionptr.h>
#include <iostream>

class pxOrder;
class pxOrderItem;

namespace libcsc
{
namespace discount
{
class IOrderBaseValueGetter
{
public:
	virtual ~IOrderBaseValueGetter() {}

	virtual void setOrderItem( pxOrderItem * orderItem ) = 0;

	virtual basar::Int16 getBranchNo() const = 0;
	virtual basar::Int32 getCustomerNo() const = 0;
	virtual basar::Int32 getOrderNo() const = 0;
	virtual basar::Int32 getPositionNo() const = 0;
	virtual basar::Int32 getArticleNo() const = 0;
	virtual basar::Int32 getItemQty() const = 0; // baseqty
	virtual const basar::Decimal getItemPrice() const = 0; // baseprice
	virtual const basar::Decimal getItemValue() const = 0; // baseprice * basqty
	virtual const basar::Decimal getRiKValue() const = 0; // baseprice * menge_natra
	virtual const IArticleClassificationGetterPtr getArticleClassification() const = 0;
	virtual const OrderItemBaseValueCollectionPtr getOrderItemBaseValueCollection() const = 0;

	//DEPricing
	virtual basar::VarString getOrderType() const = 0;
	virtual const basar::Decimal getExFactoryPrice() const = 0; // GEP
	virtual bool isTaxSpannenCheckNecessary() const = 0;
	virtual bool isRezeptPflichtig() const = 0;
	virtual bool isApothekenPflichtig() const = 0;
	virtual bool isCalcNetPrice() const = 0;
	virtual char getCustomerRXAFlag() const = 0;
	//DEPricing

	virtual pxOrder * getOrderPtr() const = 0;
	virtual pxOrderItem * getOrderItemPtr() const = 0;

	virtual std::ostream & toStream( std::ostream & strm = std::cout ) const = 0;
};

} // end namespace discount
} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::discount::IOrderBaseValueGetter & r )
{
	r.toStream( strm );
	return strm;
}

#endif // GUARD_LIBCSC_I_ORDER_BASE_VALUE_GETTER_H
