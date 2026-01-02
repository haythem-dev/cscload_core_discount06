//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBSESSION_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_NULLPXVBSESSION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "ipxvbsession.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
//class pxSession;

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace pxVerbund
{	

class NullPXVBSession : public IPXVBSession
{			
    public:		
        NullPXVBSession();
        ~NullPXVBSession();             			

		virtual pxSession* get();
};

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod

#endif 

