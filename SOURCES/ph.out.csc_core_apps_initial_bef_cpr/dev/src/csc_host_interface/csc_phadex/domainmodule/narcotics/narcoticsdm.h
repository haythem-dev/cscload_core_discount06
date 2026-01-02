#ifndef GUARD_CSC_PHADEX_DOMMOD_NARCOTICS_DM_H
#define GUARD_CSC_PHADEX_DOMMOD_NARCOTICS_DM_H

#include "inarcotics.h"

namespace csc_phadex
{
namespace domMod
{
namespace narcotics
{
class NarcoticsDM : public INarcotics
{
public:
    NarcoticsDM();
    virtual ~NarcoticsDM();

    void injectNarcoticsAccessor( libutil::infrastructure::accessor::IAccessorPtr );

    virtual void save( const basar::db::aspect::AccessorPropertyTable_YIterator );
    virtual bool isEmpty() const;
    virtual void resetSearchYit();
    virtual basar::db::aspect::AccessorPropertyTable_YIterator getSearchYit() const;
    virtual basar::db::aspect::AccessorPropertyTableRef get() const;
private:
    NarcoticsDM( const NarcoticsDM & );
    NarcoticsDM & operator= ( const NarcoticsDM & );

    libutil::domMod::SearchYIteratorPtr getSearchYIterator() const;
    libutil::infrastructure::accessor::IAccessorPtr getNarcoticsAccessor() const;

    mutable libutil::domMod::SearchYIteratorPtr         m_SearchYIterator;
    libutil::infrastructure::accessor::IAccessorPtr     m_Accessor;
    log4cplus::Logger                                   m_Logger;

};

} // end namespace narcotics
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_NARCOTICS_DM_H
