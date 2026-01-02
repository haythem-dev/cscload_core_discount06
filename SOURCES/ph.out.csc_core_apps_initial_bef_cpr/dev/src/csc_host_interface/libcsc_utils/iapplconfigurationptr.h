//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_IAPPLCONFIGURATIONPTR_H
#define GUARD_LIBCSC_UTILS_IAPPLCONFIGURATIONPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	class IApplConfiguration;
	typedef boost::shared_ptr<libcsc_utils::IApplConfiguration> IApplConfigurationPtr;    
}


#endif // GUARD_LIBCSC_UTILS_IAPPLCONFIGURATIONPTR_H
