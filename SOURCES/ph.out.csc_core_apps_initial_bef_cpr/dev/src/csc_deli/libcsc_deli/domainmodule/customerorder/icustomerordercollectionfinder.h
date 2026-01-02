#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_ICUSTOMERORDERCOLLECTIONFINDER_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_ICUSTOMERORDERCOLLECTIONFINDER_H

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
namespace customerOrder
{
    class ICustomerOrderCollectionFinder
    {

    public:
        virtual ~ICustomerOrderCollectionFinder() {}

        virtual basar::db::aspect::AccessorPropertyTableRef                 get()     const                 = 0;
        virtual bool                                                        isEmpty() const                 = 0;

        virtual void                                                        findByPartnerNo( basar::Int32 ) = 0;
        virtual basar::Decimal                                              getDeliveryValue()              = 0;
    };

} // end namespace customerOrder
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_ICUSTOMERORDERCOLLECTIONFINDER_H
