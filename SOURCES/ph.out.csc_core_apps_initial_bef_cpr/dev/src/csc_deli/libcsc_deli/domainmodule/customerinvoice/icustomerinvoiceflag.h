#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICEFLAG_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICEFLAG_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//


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
    class ICustomerInvoiceFlag
    {

    public:
        virtual ~ICustomerInvoiceFlag() {}

        virtual void                                  saveInvoicedFlag( basar::db::aspect::AccessorPropertyTable_YIterator ) = 0;
    };

} // end namespace customerInvoice
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICEFLAG_H
