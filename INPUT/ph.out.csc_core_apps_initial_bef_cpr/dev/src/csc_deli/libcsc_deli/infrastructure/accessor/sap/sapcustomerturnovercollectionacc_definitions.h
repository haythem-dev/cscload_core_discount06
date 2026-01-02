#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPCUSTOMERTURNOVERCOLLECTIONACC_DEFINITIONS_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPCUSTOMERTURNOVERCOLLECTIONACC_DEFINITIONS_H

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
    // userAdm parameter for full file path like "/software/wss/at/ksc/batch/data/AT_KSC2SAP_TURNOVER.CSV"
    const basar::VarString CUSTOMER_TURNOVER_FILE                 = "CST_TURNOVER_FILE";

    const basar::VarString SAP_CUSTOMER_TURNOVER_COLLECTION_ACC   = "ACCSAPCustomerTurnoverCollection";
    const basar::VarString WRITE_SAP_CUSTOMER_TURNOVER_COLLECTION = "WriteSAPCustomerTurnoverCollection";
}

} // end namespace sap
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPCUSTOMERTURNOVERCOLLECTIONACC_DEFINITIONS_H
