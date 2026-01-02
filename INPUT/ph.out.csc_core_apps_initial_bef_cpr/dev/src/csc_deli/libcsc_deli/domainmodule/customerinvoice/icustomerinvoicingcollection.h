#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICINGCOLLECTION_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICINGCOLLECTION_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "icustomerinvoiceptr.h"

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
namespace customerInvoice
{
    class ICustomerInvoicingCollection
    {

    public:
        virtual ~ICustomerInvoicingCollection() {}

        virtual basar::db::aspect::AccessorPropertyTableRef get()     const   = 0;
        virtual bool                                        isEmpty() const   = 0;

        virtual void                                        readCollection()  = 0;
        virtual void                                        save()            = 0;
    };

} // end namespace customerInvoice
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICINGCOLLECTION_H
