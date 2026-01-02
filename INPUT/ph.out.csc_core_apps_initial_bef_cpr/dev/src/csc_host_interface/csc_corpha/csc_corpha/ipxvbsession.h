//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBSESSION_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBSESSION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
class pxSession;

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	

class IPXVBSession
{			
    public:		
        virtual ~IPXVBSession(){};             			
		virtual pxSession* get() = 0;
};

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod

#endif 
