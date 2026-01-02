//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_ICSC_CMDLINEOPTIONPTR_H
#define GUARD_LIBCSC_UTILS_ICSC_CMDLINEOPTIONPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	class ICSC_CmdLineOption;
	typedef boost::shared_ptr<libcsc_utils::ICSC_CmdLineOption> ICSC_CmdLineOptionPtr;
}

#endif // end GUARD_LIBCSC_UTILS_ICSC_CMDLINEOPTIONPTR_H
