#ifndef GUARD_LIBCSC_DISCOUNT_LOG_POSITION_REPOSITORY_H
#define GUARD_LIBCSC_DISCOUNT_LOG_POSITION_REPOSITORY_H

#include <discount/logger/discountlogger/idiscountlogpositionrepository.h>
#include <discount/logger/discountlogger/discountlogpositioncollection.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>

namespace libcsc
{
namespace discount
{
class DiscountLogPositionRepository : public IDiscountLogPositionRepository
{
public:
	DiscountLogPositionRepository();
	virtual ~DiscountLogPositionRepository();

	void injectInsertAccessor( persistence::IAccessorPtr accessor );
	void injectDeleteAccessor( persistence::IAccessorPtr accessor );
	void injectTransactionFactory( persistence::ITransactionFactoryPtr transactionFactory );

	virtual DiscountLogPositionCollectionPtr get();
	virtual void save();

private:
	DiscountLogPositionCollectionPtr	m_DiscountLogPositions;
	persistence::IAccessorPtr			m_InsertAccessor;
	persistence::IAccessorPtr			m_DeleteAccessor;
	persistence::ITransactionFactoryPtr	m_TransactionFactory;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_LOG_POSITION_REPOSITORY_H