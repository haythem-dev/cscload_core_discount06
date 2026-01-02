//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		27.05.2013
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORRESPONSEPTR_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORRESPONSEPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//

namespace domMod 
{		
namespace corpha
{    
namespace processOrder
{
	class CICSOrderAccessorResponse;
	typedef boost::shared_ptr< CICSOrderAccessorResponse > CICSOrderAccessorResponsePtr;    
}
}
}

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORRESPONSEPTR_H
