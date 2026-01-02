#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICINGCOLLECTIONACC_DEFINITIONS_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICINGCOLLECTIONACC_DEFINITIONS_H

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
    // userAdm parameter for full file path like "/transfer/ksc/KSCFKL61.TXT"
    const basar::VarString CUSTOMER_INVOICING_FILE            = "CST_INVOICING_FILE";

    const basar::VarString CUSTOMER_INVOICING_COLLECTION_ACC  = "ACCCustomerInvoicingCollection";
    const basar::VarString READ_CUSTOMER_INVOICING_COLLECTION = "ReadCustomerInvoicingCollection";
    const basar::VarString BACKUP_INVOICING                   = "BackupInvoicingFiles";
}

} // end namespace customerInvoice
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICINGCOLLECTIONACC_DEFINITIONS_H
