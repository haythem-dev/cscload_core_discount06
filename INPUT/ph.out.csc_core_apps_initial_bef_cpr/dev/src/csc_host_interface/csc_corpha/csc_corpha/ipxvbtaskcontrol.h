//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBTASKCONTROL_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBTASKCONTROL_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	

class IPXVBTaskControl
{			
    public:		
        virtual ~IPXVBTaskControl(){};

		virtual void setHeartBeat() = 0;		
};

}
}
}

#endif  // GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBTASKCONTROL_H
