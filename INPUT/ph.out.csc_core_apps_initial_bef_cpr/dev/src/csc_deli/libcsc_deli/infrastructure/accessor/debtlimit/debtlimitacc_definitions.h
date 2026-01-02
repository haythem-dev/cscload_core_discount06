#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_DEBTLIMITACC_DEFINITIONS_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_DEBTLIMITACC_DEFINITIONS_H

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
namespace debtLimit
{
namespace lit
{
    const basar::VarString DEBTLIMIT_ACC    = "AccDebtLimit";
    const basar::VarString SELECT_DEBTLIMIT = "SelectDebtLimit";
    const basar::VarString SAVE_DEBTLIMIT   = "SaveDebtLimit";
    const basar::VarString DELETE_DEBTLIMIT = "DeleteDebtLimit";
}

} // end namespace debtLimit
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_DEBTLIMITACC_DEFINITIONS_H
