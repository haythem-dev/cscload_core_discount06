//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr for IRemoteProcedure 
 *  \author		Steffen Heinlein
 *  \date		20.06.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_IREMOTEPROCEDUREPTR_H
#define GUARD_LIBCSC_UTILS_IREMOTEPROCEDUREPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//

namespace libcsc_utils
{

	class IRemoteProcedure;
	typedef boost::shared_ptr<libcsc_utils::IRemoteProcedure> IRemoteProcedurePtr;    

}

#endif // GUARD_LIBCSC_UTILS_IREMOTEPROCEDUREPTR_H
