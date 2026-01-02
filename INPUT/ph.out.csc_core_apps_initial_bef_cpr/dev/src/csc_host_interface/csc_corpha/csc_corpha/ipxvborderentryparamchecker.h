//----------------------------------------------------------------------------//
/*! \file	
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBORDERENTRYPARAMCHECKER_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_IPXVBORDERENTRYPARAMCHECKER_H

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	

class IPXVBOrderEntryParamChecker 
{				
    public:		
        virtual ~IPXVBOrderEntryParamChecker(){};             						
		virtual bool checkNarcoticsTransfer() const = 0;
};

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod

#endif 

