#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPBALANCECOLLECTIONACC_DEFINITIONS_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPBALANCECOLLECTIONACC_DEFINITIONS_H

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
namespace sap
{
namespace lit
{
    // userAdm parameter for full file path like "/transfer/ksc/DEBTORBALANCE_A001"
    const basar::VarString SAP_BALANCE_FILE             = "SAP_BALANCE_FILE";

    const basar::VarString SAP_BALANCE_COLLECTION_ACC   = "ACCSAPBalaceCollection";
    const basar::VarString READ_SAP_BALANCE_COLLECTION  = "ReadSAPBalanceCollection";
    const basar::VarString BACKUP_SAP_BALANCE           = "BackupSapBalanceFile";
}

} // end namespace sap
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPBALANCECOLLECTIONACC_DEFINITIONS_H
