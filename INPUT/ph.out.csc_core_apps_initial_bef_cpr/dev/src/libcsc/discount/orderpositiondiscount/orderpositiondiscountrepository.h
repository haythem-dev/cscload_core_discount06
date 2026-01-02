#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_REPOSITORY_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_REPOSITORY_H

#include <discount/orderpositiondiscount/iorderpositiondiscountrepository.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountRepository : public IOrderPositionDiscountRepository
{
public:
	OrderPositionDiscountRepository();
	virtual ~OrderPositionDiscountRepository();

	void injectRebateInKindEntrySelectAccessor(persistence::IAccessorPtr accessor);
	void injectSingleArticleSelectAccessor( persistence::IAccessorPtr accessor );
	void injectOrderCompletionSelectAccessor( persistence::IAccessorPtr accessor );
	void injectInsertAccessor( persistence::IAccessorPtr accessor );
	void injectUpdateAccessor( persistence::IAccessorPtr accessor );
	void injectDeleteAccessor( persistence::IAccessorPtr accessor );
	void injectTransactionFactory( persistence::ITransactionFactoryPtr transactionFactory );

	virtual void reset();
	virtual OrderPositionDiscountPtr getOrderPositionDiscount( const basar::Int32 positionNo, const OrderPositionDiscountMode discountMode );
	virtual OrderPositionDiscountPtr getOrderPositionDiscount(const basar::Int32 positionNo, const OrderPositionDiscountMode discountMode, const basar::Int32 rebInKindPosNo, const basar::Int32 rebInKindOrderNo);
	virtual OrderPositionDiscountListPtr get();
	virtual void save();
	virtual void erase( OrderPositionDiscountPtr orderPositionDiscount );
	virtual OrderPositionDiscountListPtr findByID( const basar::Int32 orderNo, const basar::Int32 positionNo = 0 ) const;
	virtual OrderPositionDiscountListPtr findByIDBackward(const basar::Int32 rebateinkindorderNo, const basar::Int32 rebateinkindpositionNo ) const;

private:

	OrderPositionDiscountListPtr		m_OrderPositionDiscounts;
	persistence::IAccessorPtr			m_InsertAccessor;
	persistence::IAccessorPtr			m_UpdateAccessor;
	persistence::IAccessorPtr			m_DeleteAccessor;
	mutable persistence::IAccessorPtr	m_SingleArticleSelectAccessor;
	mutable persistence::IAccessorPtr	m_RebateInKindEntrySelectAccessor;
	mutable persistence::IAccessorPtr	m_AdditionalPosDiscSelectAccessor;
	mutable persistence::IAccessorPtr	m_OrderCompletionSelectAccessor;
	persistence::ITransactionFactoryPtr	m_TransactionFactory;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_REPOSITORY_H
