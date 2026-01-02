#ifndef GUARD_LIBCSC_PERSISTENCE_I_TRANSACTION_FACTORY_H
#define GUARD_LIBCSC_PERSISTENCE_I_TRANSACTION_FACTORY_H

#include <persistence/transactionguard.h>

namespace libcsc
{
namespace persistence
{
class ITransactionFactory
{
public:
	virtual ~ITransactionFactory() {}

	virtual libcsc::persistence::TransactionGuard createTransaction() const = 0;
};

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_I_TRANSACTION_FACTORY_H
