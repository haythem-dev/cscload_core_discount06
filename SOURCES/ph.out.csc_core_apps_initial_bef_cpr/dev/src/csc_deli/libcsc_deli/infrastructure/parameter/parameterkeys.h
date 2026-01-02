#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_PARAMETERKEYS_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_PARAMETERKEYS_H

namespace libcsc_deli
{
namespace infrastructure
{
namespace parameter
{
    // params used for getting values from usrAdm
    basar::ConstString MSG_FILE		           = "MESSAGE_FILE";
    // other parameters are defined in their own accessor specific definition files
    // CUSTOMER_INVOICING_FILE -> customerinvoicingcollectionacc_definitions.h
    // SAP_BALANCE_FILE        -> sapbalancecollectionacc_definitions.h
    // CUSTOMER_TURNOVER_FILE  -> sapcustomerturnovercollectionacc_definitions.h
    // SAP_LIMIT_FILE          -> saplimitcollectionacc_definitions.h

    // other params
    basar::ConstString DEVICENAME		       = "CSC_DELI";

} // end namespace parameter
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_PARAMETERKEYS_H
