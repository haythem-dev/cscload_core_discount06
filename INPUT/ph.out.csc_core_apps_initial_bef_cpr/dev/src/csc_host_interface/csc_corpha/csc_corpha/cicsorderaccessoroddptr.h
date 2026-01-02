//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		27.05.2013
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORODDPTR_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORODDPTR_H

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
	class CICSOrderAccessorOdd;
	typedef boost::shared_ptr< CICSOrderAccessorOdd > CICSOrderAccessorOddPtr;    
}
}
}

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORODDPTR_H
