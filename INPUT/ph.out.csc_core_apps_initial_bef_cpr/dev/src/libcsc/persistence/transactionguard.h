#ifndef GUARD_LIBCSC_PERSISTENCE_TRANSACTION_GUARD_H
#define GUARD_LIBCSC_PERSISTENCE_TRANSACTION_GUARD_H

#include <database.hpp>

namespace libcsc
{
namespace persistence
{
class TransactionGuard
{
public:
	TransactionGuard( nDataBase * transactionHandler );
	~TransactionGuard();
						
	void begin();
	void commit();
	void rollback();
	bool isInTransaction() const;
						
private:
	nDataBase *							m_TransactionHandler;
	bool								m_OwnTransaction;
};
				
} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_TRANSACTION_GUARD_H
