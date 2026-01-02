#ifndef GUARD_LIBCSC_UNITTEST_ORDER_BASE_VALUE_STUB_H
#define GUARD_LIBCSC_UNITTEST_ORDER_BASE_VALUE_STUB_H

#include <discount/basevalues/orderbasevalue/iorderbasevaluegetter.h>

namespace libcscUnitTest
{
namespace discount
{
class OrderBaseValueStub : public libcsc::discount::IOrderBaseValueGetter
{
public:
	OrderBaseValueStub(
		const basar::Int16 branchno,
		const basar::Int32 customerno,
		const basar::Int32 orderno,
		const basar::VarString& orderType,
		const basar::Int32 positionno,
		const basar::Int32 articleno,
		const basar::Int32 itemqty,
		const basar::Decimal & itemprice,
		const basar::Decimal & itemvalue,
		const basar::Decimal & rikvalue,
		const basar::VarString & itemlist
			);
	virtual ~OrderBaseValueStub();

	virtual void setOrderItem( pxOrderItem * orderItem );

	virtual basar::Int16 getBranchNo() const;
	virtual basar::Int32 getCustomerNo() const;
	virtual basar::Int32 getOrderNo() const;
	virtual basar::Int32 getPositionNo() const;
	virtual basar::Int32 getArticleNo() const;
	virtual basar::Int32 getItemQty() const;
	virtual const basar::Decimal getItemPrice() const;
	virtual const basar::Decimal getItemValue() const;
	virtual const basar::Decimal getRiKValue() const;
	virtual const libcsc::discount::IArticleClassificationGetterPtr getArticleClassification() const;
	virtual const libcsc::discount::OrderItemBaseValueCollectionPtr getOrderItemBaseValueCollection() const;
	virtual pxOrder * getOrderPtr() const;
	virtual pxOrderItem * getOrderItemPtr() const;
	virtual std::ostream & toStream( std::ostream & strm = std::cout ) const;

	//DEPricing
	virtual basar::VarString getOrderType() const;
	virtual const basar::Decimal getExFactoryPrice() const; // GEP
	virtual bool isTaxSpannenCheckNecessary() const;
	virtual bool isRezeptPflichtig() const;
	virtual bool isApothekenPflichtig() const;
	virtual bool isCalcNetPrice() const;
	virtual char getCustomerRXAFlag() const;
	//DEPricing

private:
	OrderBaseValueStub( const OrderBaseValueStub & );
	OrderBaseValueStub & operator=( const OrderBaseValueStub & );

	basar::Int16	m_BranchNo;
	basar::Int32	m_CustomerNo;
	basar::Int32	m_OrderNo;
	basar::VarString m_OrderType;
	basar::Int32	m_PositionNo;
	basar::Int32	m_ArticleNo;
	basar::Int32	m_ItemQty;
	basar::Decimal	m_ItemPrice;
	basar::Decimal	m_ItemValue;
	basar::Decimal	m_RiKValue;
	basar::VarString m_ItemList;
};

} // end namespace discount
} // end namespace libcscUnitTest

#endif // GUARD_LIBCSC_UNITTEST_ORDER_BASE_VALUE_STUB_H
