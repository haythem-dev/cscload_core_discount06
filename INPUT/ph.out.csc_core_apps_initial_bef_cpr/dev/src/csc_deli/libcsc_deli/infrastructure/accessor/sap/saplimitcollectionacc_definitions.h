#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPLIMITCOLLECTIONACC_DEFINITIONS_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPLIMITCOLLECTIONACC_DEFINITIONS_H

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
    // userAdm parameter for full file path like "/transfer/ksc/CLIMIT_BUK_S001"
    const basar::VarString SAP_LIMIT_FILE             = "SAP_LIMIT_FILE";

    const basar::VarString SAP_LIMIT_COLLECTION_ACC   = "ACCSAPLimitCollection";
    const basar::VarString READ_SAP_LIMIT_COLLECTION  = "ReadSAPLimitCollection";
    const basar::VarString BACKUP_SAP_LIMIT           = "BackupSAPLimit";
}

} // end namespace sap
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPLIMITCOLLECTIONACC_DEFINITIONS_H
