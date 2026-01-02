//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_IPXVBSESSION_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_IPXVBSESSION_H

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
namespace pharmosTransaction
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
} // end namespace pharmosTransaction
} // end namespace domMod

#endif 

