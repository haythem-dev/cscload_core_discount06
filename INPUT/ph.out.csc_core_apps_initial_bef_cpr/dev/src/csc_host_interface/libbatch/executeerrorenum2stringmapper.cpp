//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author Bjoern Bischof
 *  \date   22.03.2011
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "executeerrorenum2stringmapper.h"

//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace domMod
{

const basar::VarString ExecuteErrorEnum2StringMapper::map( const basar::db::aspect::ExecuteErrorEnum executeErrorEnum )
{
    basar::VarString result;
    using namespace basar::db::aspect;

    if( SUCCESS == executeErrorEnum ){
            result = "SUCCESS";
    } else if( SQL_ERROR == executeErrorEnum || SQL_ERROR_UNKNOWN == executeErrorEnum ){
            result = "SQL_ERROR[_UNKNOWN]";
    } else if( NOT_EXECUTABLE == executeErrorEnum ){
            result = "NOT_EXECUTABLE";
    } else if( SQL_ERROR_NONSPECIFIC == executeErrorEnum ){
            result = "SQL_ERROR_NONSPECIFIC";
    } else if( SQL_ERROR_DUPL_INSERT == executeErrorEnum ){
            result = "SQL_ERROR_DUPL_INSERT";
    }  else {
        std::stringstream ss; ss << "No Mapping of value<" << executeErrorEnum << ">";
        result = ss.str().c_str();
    }

    return result;
}

} // end namespace domMod
