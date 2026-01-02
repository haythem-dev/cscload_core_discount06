#ifndef GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_COLLECTION_FINDER_H
#define GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_COLLECTION_FINDER_H

#include <domainmodule/cicstransaction/icicstransactionptr.h>

namespace basar
{
namespace db
{
namespace aspect
{
	class AccessorPropertyTable_YIterator;
	class AccessorPropertyTableRef;
}
}
}

namespace csc_phadex
{
namespace domMod
{
namespace cicsTransaction
{
class ICICSTransactionCollectionFinder
{
public:
	virtual ~ICICSTransactionCollectionFinder() {}

	virtual void findByPattern( const basar::db::aspect::AccessorPropertyTable_YIterator ) = 0;
	virtual bool isEmpty() const = 0;
	virtual basar::db::aspect::AccessorPropertyTableRef get() = 0;
	virtual void resetSearchYit() = 0;
	virtual basar::db::aspect::AccessorPropertyTable_YIterator getSearchYit() const = 0;
	virtual ICICSTransactionPtr getCICSTransaction( const basar::db::aspect::AccessorPropertyTable_YIterator ) const = 0;
	virtual void saveCICSTransaction(const basar::db::aspect::AccessorPropertyTable_YIterator) const = 0;
};

} // end namespace cicsTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_COLLECTION_FINDER_H
