#include "branchparametergetter.h"

#ifdef WIN32
    #pragma warning (push)
    #pragma warning(disable: 4244 4430 4806 4996)
#endif

#ifdef __GNUC__
    //#pragma GCC diagnostic push
    //#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <pxsess.hpp>
#include <pxparameterdef.h>
#include <pxparameter.hpp>

#ifdef __GNUC__
    //#pragma GCC diagnostic pop
#endif

#ifdef WIN32
    #pragma warning (pop)
#endif

namespace libcsc
{
namespace parameter
{
BranchParameterGetter::BranchParameterGetter( pxSession * session )
: m_Session( session )
{
}

BranchParameterGetter::~BranchParameterGetter()
{
}

const basar::VarString BranchParameterGetter::getDatabaseName( const basar::Int16 branchNo ) const
{
    return m_Session->getDatabaseName( branchNo );
}

const basar::VarString BranchParameterGetter::getDatabaseNameWarehouse(const basar::Int16 branchNo) const
{
    return m_Session->getDatabaseNameWarehouse( branchNo );
}

basar::Int32 BranchParameterGetter::getOMGDuration( const basar::Int16 branchNo ) const
{
    pxParameter param( m_Session, branchNo, cPAR_KSC_GROUP, cPAR_KSCSERVER_PURPOSE_TENDER, cPAR_KSCSERVER_PARAMNAME_OMGDURATION );
    param.Get();

    return param.Wert();
}

} // end namespace parameter
} // end namespace libcsc
