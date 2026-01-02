#ifndef GUARD_LIBCSC_BRANCH_PARAMETER_GETTER_H
#define GUARD_LIBCSC_BRANCH_PARAMETER_GETTER_H

#include <parameter/ibranchparametergetter.h>

class pxSession;

namespace libcsc
{
namespace parameter
{
class BranchParameterGetter : public IBranchParameterGetter
{
public:
    BranchParameterGetter( pxSession * session );
    virtual ~BranchParameterGetter();

    virtual const basar::VarString getDatabaseName( const basar::Int16 branchNo ) const;
    virtual const basar::VarString getDatabaseNameWarehouse(const basar::Int16 branchno) const;
    virtual basar::Int32 getOMGDuration( const basar::Int16 branchNo ) const;

private:
    pxSession *	m_Session;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_BRANCH_PARAMETER_GETTER_H
