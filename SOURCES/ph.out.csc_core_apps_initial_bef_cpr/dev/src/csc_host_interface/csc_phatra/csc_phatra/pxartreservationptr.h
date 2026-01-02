
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTRESERVATIONPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTRESERVATIONPTR_H
//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
class pxArtReservation;

namespace domMod
{
    namespace pharmosTransaction
    {
		namespace processing
        {
			typedef boost::shared_ptr< ::pxArtReservation > pxArtReservationPtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTRESERVATIONPTR_H

