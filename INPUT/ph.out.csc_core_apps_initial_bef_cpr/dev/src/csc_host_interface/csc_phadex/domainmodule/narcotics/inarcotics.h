#ifndef GUARD_CSC_PHADEX_DOMMOD_I_NARCOTICS_H
#define GUARD_CSC_PHADEX_DOMMOD_I_NARCOTICS_H

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
namespace narcotics
{
class INarcotics
{
public:
    virtual ~INarcotics() {}
    virtual void save( const basar::db::aspect::AccessorPropertyTable_YIterator ) = 0;
    virtual bool isEmpty() const = 0;
    virtual void resetSearchYit() = 0;
    virtual basar::db::aspect::AccessorPropertyTable_YIterator getSearchYit() const = 0;
    virtual basar::db::aspect::AccessorPropertyTableRef get() const = 0;
};

} // end namespace narcotics
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_NARCOTICS_H
