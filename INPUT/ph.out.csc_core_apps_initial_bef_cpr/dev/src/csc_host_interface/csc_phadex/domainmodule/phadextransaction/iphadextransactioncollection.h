#ifndef GUARD_CSC_PHADEX_DOMMOD_I_PHADEX_TRANSACTION_COLLECTION_H
#define GUARD_CSC_PHADEX_DOMMOD_I_PHADEX_TRANSACTION_COLLECTION_H

#include <domainmodule/phadextransaction/iphadextransactionptr.h>

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
namespace phadexTransaction
{
class IPhadexTransactionCollection
{
public:
    virtual ~IPhadexTransactionCollection() {}

    virtual void findPhadexTransByPattern( const basar::db::aspect::AccessorPropertyTable_YIterator ) = 0;
    virtual void findLastPhadexTransByPattern( const basar::db::aspect::AccessorPropertyTable_YIterator ) = 0;
    virtual void save( IPhadexTransactionPtr ) = 0;
	virtual void clear() = 0;
    virtual bool isEmpty() const = 0;
	virtual basar::db::aspect::AccessorPropertyTableRef get() = 0;
    virtual void resetSearchYit() = 0;
    virtual basar::db::aspect::AccessorPropertyTable_YIterator getSearchYit() const = 0;
    virtual IPhadexTransactionPtr getPhadexTransaction( const basar::db::aspect::AccessorPropertyTable_YIterator ) const = 0;
    virtual IPhadexTransactionPtr createPhadexTransaction() = 0;
};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_PHADEX_TRANSACTION_COLLECTION_H
