#ifndef GUARD_LIBCSC_ORDER_ITEM_BASE_VALUE_H
#define GUARD_LIBCSC_ORDER_ITEM_BASE_VALUE_H

#include <discount/basevalues/orderbasevalue/iorderbasevaluegetter.h>
#include <discount/basevalues/orderbasevalue/orderitembasevaluecollectionptr.h>
#include <discount/basevalues/orderbasevalue/orderitembasevaluecollectionptr.h>
#include <discount/basevalues/orderbasevalue/articleclassificationrepository.h>
#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedrepositoryptr.h>

class pxOrderItem;
class pxOrder;

namespace libcsc
{
namespace discount
{
class OrderItemBaseValue : public IOrderBaseValueGetter
{
public:
	OrderItemBaseValue( pxOrderItem * orderItem );	// TODO: const pxOrderItem * ?
	OrderItemBaseValue( pxOrder * order );	// TODO: const pxOrder * ?
	virtual ~OrderItemBaseValue();

	void injectArticleClassificationRepository( ArticleClassificationRepositoryPtr articleClassificationRepository );
	void injectOrderPositionDiscountProcessedRepository( OrderPositionDiscountProcessedRepositoryPtr orderPositionDiscountProcessedRepository );

	virtual void setOrderItem( pxOrderItem * orderItem );	// TODO: const pxOrderItem * ?

	virtual basar::Int16 getBranchNo() const;
	virtual basar::Int32 getCustomerNo() const;
	virtual basar::Int32 getOrderNo() const;
	virtual basar::Int32 getPositionNo() const;
	virtual basar::Int32 getArticleNo() const;
	virtual basar::Int32 getItemQty() const; // baseqty
	virtual const basar::Decimal getItemPrice() const; // baseprice
	virtual const basar::Decimal getItemValue() const; // baseprice * baseqty
	virtual const basar::Decimal getRiKValue() const; // baseprice * menge_natra
	virtual const IArticleClassificationGetterPtr getArticleClassification() const;
	virtual const OrderItemBaseValueCollectionPtr getOrderItemBaseValueCollection() const;

	//DEPricing
	virtual basar::VarString getOrderType() const;
	virtual const basar::Decimal getExFactoryPrice() const; // GEP
	virtual bool isTaxSpannenCheckNecessary() const;
	virtual bool isRezeptPflichtig() const;
	virtual bool isApothekenPflichtig() const;
	virtual bool isCalcNetPrice() const;
	virtual char getCustomerRXAFlag() const;
	//DEPricing

	virtual pxOrder * getOrderPtr() const;
	virtual pxOrderItem * getOrderItemPtr() const;

	std::ostream & toStream( std::ostream & strm = std::cout ) const;

private:
	pxOrderItem *								m_OrderItem;
	pxOrder *									m_Order;
	ArticleClassificationRepositoryPtr			m_ArticleClassificationRepository;
	mutable OrderItemBaseValueCollectionPtr		m_OrderItemBaseValueCollection;
	mutable IArticleClassificationGetterPtr		m_ArticleClassificationGetter;
	OrderPositionDiscountProcessedRepositoryPtr m_OrderPositionDiscountProcessedRepository;
};

} // end namespace discount
} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::discount::OrderItemBaseValue & r )
{
	r.toStream( strm );
	return strm;
}

#endif // GUARD_LIBCSC_ORDER_ITEM_BASE_VALUE_H
