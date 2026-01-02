#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_ICUSTOMERFINDER_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_ICUSTOMERFINDER_H

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
namespace customer
{
    class ICustomerFinder
    {

    public:
        virtual ~ICustomerFinder() {}

        virtual basar::db::aspect::AccessorPropertyTable_YIterator          get()     const                 = 0;
        virtual bool                                                        isEmpty() const                 = 0;

        virtual void                                                        findByPartnerNo( basar::Int32 ) = 0;
    };

} // end namespace customer
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_ICUSTOMERFINDER_H
