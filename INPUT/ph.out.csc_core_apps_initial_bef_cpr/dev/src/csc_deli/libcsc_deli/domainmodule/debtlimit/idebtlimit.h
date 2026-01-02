#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMIT_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMIT_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
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

//-------------------------------------------------------------------------------------------------//
// interface class definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace debtLimit
{
    class IDebtLimit
    {

    public:
        virtual ~IDebtLimit() {}

        virtual basar::db::aspect::AccessorPropertyTable_YIterator          get()     const   = 0;
        virtual basar::db::aspect::AccessorPropertyTable_YIterator          get()             = 0;

        virtual bool                                                        isChanged() const = 0;
        virtual bool                                                        isEmpty() const   = 0;

        virtual void                                                        erase()           = 0;
        virtual void                                                        save()            = 0;
    };

} // end namespace debtLimit
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMIT_H
