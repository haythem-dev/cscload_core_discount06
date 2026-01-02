//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		11.10.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERDMPTR_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERDMPTR_H

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
    class CICSOrderDM;
	typedef boost::shared_ptr< CICSOrderDM > CICSOrderDMPtr;    
}
}
}

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERDMPTR_H
