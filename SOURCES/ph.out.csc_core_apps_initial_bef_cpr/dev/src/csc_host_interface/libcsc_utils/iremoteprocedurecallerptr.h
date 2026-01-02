//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_IREMOTEPROCEDURECALLERPTR_H
#define GUARD_LIBCSC_UTILS_IREMOTEPROCEDURECALLERPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

namespace libcsc_utils
{
	class IRemoteProcedureCaller;
	typedef boost::shared_ptr<libcsc_utils::IRemoteProcedureCaller> IRemoteProcedureCallerPtr;
}//end namespace util


#endif//#ifndef GUARD_LIBCSC_UTILS_IREMOTEPROCEDURECALLERPTR_H
