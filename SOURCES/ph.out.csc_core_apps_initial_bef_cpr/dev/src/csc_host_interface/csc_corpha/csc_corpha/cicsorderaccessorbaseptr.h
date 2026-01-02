//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		27.05.2013
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORBASEPTR_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORBASEPTR_H

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
	class CICSOrderAccessorBase;
	typedef boost::shared_ptr< CICSOrderAccessorBase > CICSOrderAccessorBasePtr;    
}
}
}

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERACCESSORBASEPTR_H
