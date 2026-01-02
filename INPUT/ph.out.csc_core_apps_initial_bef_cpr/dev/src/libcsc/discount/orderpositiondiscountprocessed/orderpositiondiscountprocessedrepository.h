#ifndef GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_H
#define GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_H

#include <discount/orderpositiondiscountprocessed/iorderpositiondiscountprocessedrepository.h>
#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedcollectionptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>

namespace libcsc
{
namespace discount
{
class OrderPositionDiscountProcessedRepository : public IOrderPositionDiscountProcessedRepository
{
public:
	OrderPositionDiscountProcessedRepository();
	virtual ~OrderPositionDiscountProcessedRepository();

	void injectSelectAccessor( persistence::IAccessorPtr accessor );
	void injectInsertAccessor( persistence::IAccessorPtr accessor );
	void injectTransactionFactory( persistence::ITransactionFactoryPtr transactionFactory );

	virtual IOrderPositionDiscountProcessedCollectionPtr get() const;
	virtual IOrderPositionDiscountProcessedCollectionPtr findByID( const libcsc::Int32 orderNo ) const;
	virtual void save();

private:
	OrderPositionDiscountProcessedCollectionPtr		m_OrderPositionDiscountProcessedList;
	persistence::IAccessorPtr						m_InsertAccessor;
	mutable persistence::IAccessorPtr				m_SelectAccessor;
	persistence::ITransactionFactoryPtr				m_TransactionFactory;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_POSITION_DISCOUNT_PROCESSED_REPOSITORY_H
