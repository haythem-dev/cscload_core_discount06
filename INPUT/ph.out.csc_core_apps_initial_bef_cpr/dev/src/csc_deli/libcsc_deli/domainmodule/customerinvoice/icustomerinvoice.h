#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICE_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICE_H

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
    class ICustomerInvoice
    {

    public:
        virtual ~ICustomerInvoice() {}

        virtual basar::db::aspect::AccessorPropertyTable_YIterator          get()     const      = 0;

        virtual void                                                        resetSearchYit()     = 0;
        virtual basar::db::aspect::AccessorPropertyTable_YIterator          getSearchYit()       = 0;
        virtual void                                                        findByPattern( basar::db::aspect::AccessorPropertyTable_YIterator ) = 0;

        virtual void                                                        createEmptyInvoice() = 0;
        virtual bool                                                        isEmpty() const      = 0;

        virtual void                                                        save()               = 0;
    };

} // end namespace customerInvoice
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICE_H
