#ifndef GUARD_CSC_PHADEX_DOMMOD_CICS_TRANSACTION_COLLECTION_DM_H
#define GUARD_CSC_PHADEX_DOMMOD_CICS_TRANSACTION_COLLECTION_DM_H

#include "icicstransactioncollectionfinder.h"

#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>
#include <libutil/util.h>
#include <libutil/domainmodule.h>

namespace csc_phadex
{
namespace domMod
{
namespace cicsTransaction
{
class CICSTransactionCollectionDM : public ICICSTransactionCollectionFinder
{
public:
    CICSTransactionCollectionDM();
    virtual ~CICSTransactionCollectionDM();

	void injectCICSTransactionAccessor(libutil::infrastructure::accessor::IAccessorPtr);
	void injectCICSTransactionUpdateAccessor(libutil::infrastructure::accessor::IAccessorPtr);

    virtual void findByPattern( const basar::db::aspect::AccessorPropertyTable_YIterator );
    virtual bool isEmpty() const;
	virtual basar::db::aspect::AccessorPropertyTableRef get();
	virtual void resetSearchYit();
    virtual basar::db::aspect::AccessorPropertyTable_YIterator getSearchYit() const;
    virtual ICICSTransactionPtr getCICSTransaction( const basar::db::aspect::AccessorPropertyTable_YIterator ) const;
	virtual void saveCICSTransaction(const basar::db::aspect::AccessorPropertyTable_YIterator) const;

private:
    CICSTransactionCollectionDM( const CICSTransactionCollectionDM & );
    CICSTransactionCollectionDM & operator= ( const CICSTransactionCollectionDM & );

    libutil::domMod::SearchYIteratorPtr getSearchYIterator() const;
    libutil::infrastructure::accessor::IAccessorPtr getAccessor() const;

    mutable libutil::domMod::SearchYIteratorPtr			m_SearchYIterator;
	libutil::infrastructure::accessor::IAccessorPtr		m_Accessor;
	libutil::infrastructure::accessor::IAccessorPtr		m_UpdateAccessor;
	log4cplus::Logger									m_Logger;
};

} // end namespace cicsTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_CICS_TRANSACTION_COLLECTION_DM_H
