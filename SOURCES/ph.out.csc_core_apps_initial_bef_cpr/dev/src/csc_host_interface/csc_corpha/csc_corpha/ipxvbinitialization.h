//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBINITIALIZATION_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBINITIALIZATION_H

//----------------------------------------------------------------------------//
// class declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	

class IPXVBInitialization
{			
    public:		
        virtual ~IPXVBInitialization(){};
		virtual bool isInitialized() const = 0;
};

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod

#endif 
