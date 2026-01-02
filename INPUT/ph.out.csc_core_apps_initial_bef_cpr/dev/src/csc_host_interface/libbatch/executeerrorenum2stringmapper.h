//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author Bjoern Bischof
 *  \date   22.03.2011
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_EXECUTE_ERROR_ENUM_2_STRING_MAPPER_H
#define GUARD_DOMMOD_EXECUTE_ERROR_ENUM_2_STRING_MAPPER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil_bstring.h> 
#include <libbasardbaspect_definitions.h>

//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace domMod
{

class ExecuteErrorEnum2StringMapper
{
    public:
        static const basar::VarString map( const basar::db::aspect::ExecuteErrorEnum );
};

} // end namespace domMod

#endif	// GUARD_DOMMOD_EXECUTE_ERROR_ENUM_2_STRING_MAPPER_H
