#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICEACC_DEFINITIONS_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICEACC_DEFINITIONS_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil_parameterlist.h>

//----------------------------------------------------------------------------//
// lit definition section
//----------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
namespace customerInvoice
{
namespace lit
{
    const basar::VarString CUSTOMER_INVOICE_ACC             = "AccCustomerInvoice";
    const basar::VarString FIND_CUSTOMER_INVOICE_BY_PATTERN = "FindCustomerInvoiceByPattern";
    const basar::VarString SAVE_CUSTOMER_INVOICE            = "SaveCustomerInvoiceCollection";
    const basar::VarString SET_INVOICED_FLAG                = "SetInvoicedFlag";
}

} // end namespace customerInvoice
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICEACC_DEFINITIONS_H
