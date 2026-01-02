#ifndef GUARD_LIBCSC_I_BRANCH_PARAMETER_GETTER_H
#define GUARD_LIBCSC_I_BRANCH_PARAMETER_GETTER_H

#include <libbasar_definitions.h>

namespace libcsc
{
namespace parameter
{
class IBranchParameterGetter
{
public:
    virtual ~IBranchParameterGetter() {}

    virtual const basar::VarString getDatabaseName( const basar::Int16 branchNo ) const = 0;
    virtual const basar::VarString getDatabaseNameWarehouse( const basar::Int16 branchno ) const = 0;
    virtual basar::Int32 getOMGDuration( const basar::Int16 branchNo ) const = 0;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_BRANCH_PARAMETER_GETTER_H
