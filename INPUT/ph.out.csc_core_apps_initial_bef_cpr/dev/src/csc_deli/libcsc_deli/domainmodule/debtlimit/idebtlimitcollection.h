#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITCOLLECTION_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITCOLLECTION_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "idebtlimitptr.h"

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
    class IDebtLimitCollection
    {

    public:
        virtual ~IDebtLimitCollection() {}

        virtual basar::db::aspect::AccessorPropertyTableRef                 get()     const                        = 0;
        virtual IDebtLimitPtr                                               getDebtLimit( basar::Int32 partnerNo ) = 0;

        virtual bool                                                        isEmpty() const                        = 0;

        virtual void                                                        load()                                 = 0;

        virtual IDebtLimitPtr                                               appendEmptyItem( basar::Int32 partnerNo ) = 0;
        virtual basar::db::aspect::AccessorPropertyTable_YIterator          erase( IDebtLimitPtr )                  = 0;
    };

} // end namespace debtLimit
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITCOLLECTION_H
