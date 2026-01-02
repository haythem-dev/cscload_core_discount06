#ifndef GUARD_CSC_PHADEX_DOMMOD_PHADEX_TRANSACTION_COLLECTION_DM_H
#define GUARD_CSC_PHADEX_DOMMOD_PHADEX_TRANSACTION_COLLECTION_DM_H

#include "iphadextransactioncollection.h"

#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>
#include <libutil/util.h>
#include <libutil/domainmodule.h>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
class PhadexTransactionCollectionDM : public IPhadexTransactionCollection
{
public:
    PhadexTransactionCollectionDM();
    virtual ~PhadexTransactionCollectionDM();

    void injectPhadexTransactionAccessor( libutil::infrastructure::accessor::IAccessorPtr );

    virtual void findPhadexTransByPattern( const basar::db::aspect::AccessorPropertyTable_YIterator );
    virtual void findLastPhadexTransByPattern( const basar::db::aspect::AccessorPropertyTable_YIterator );
    virtual void save( IPhadexTransactionPtr );
	virtual void clear();
    virtual bool isEmpty() const;
	virtual basar::db::aspect::AccessorPropertyTableRef get();
    virtual void resetSearchYit();
    virtual basar::db::aspect::AccessorPropertyTable_YIterator getSearchYit() const;
    virtual IPhadexTransactionPtr getPhadexTransaction( const basar::db::aspect::AccessorPropertyTable_YIterator ) const;
    virtual IPhadexTransactionPtr createPhadexTransaction();

private:
    PhadexTransactionCollectionDM( const PhadexTransactionCollectionDM & );
    PhadexTransactionCollectionDM & operator= ( const PhadexTransactionCollectionDM & );

    libutil::domMod::SearchYIteratorPtr getSearchYIterator() const;
    libutil::infrastructure::accessor::IAccessorPtr getPhadexTransactionAccessor() const;

    mutable libutil::domMod::SearchYIteratorPtr         m_SearchYIterator;
    libutil::infrastructure::accessor::IAccessorPtr     m_Accessor;
    log4cplus::Logger                                   m_Logger;

};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_PHADEX_TRANSACTION_COLLECTION_DM_H
