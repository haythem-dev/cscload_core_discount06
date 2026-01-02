#ifndef GUARD_DOMMOD_INITPARAMSDM_H
#define GUARD_DOMMOD_INITPARAMSDM_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
//#include <libbasarcmnutil.h>


//--------------------------------------------------------------------------------------------------//
// class decl./ def. section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
    struct InitParamsDM
    {
	    basar::Int16      m_Branchno;
	    basar::VarString  m_Username;
        
        InitParamsDM()
        : m_Branchno( 0 ), m_Username( "" )
        {}
	    
        InitParamsDM( const basar::Int16 branchno, const basar::VarString & username ) 
	    : m_Branchno( branchno ), m_Username( username )
	    {
	    }
    };

} // end namespace domMod

#endif
