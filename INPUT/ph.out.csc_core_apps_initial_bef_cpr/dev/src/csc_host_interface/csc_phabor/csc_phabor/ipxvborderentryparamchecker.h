//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  IPXVBOrderEntryParamChecker
 *  \author Steffen Heinlein
 *  \date   10.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_IPXVBORDERENTRYPARAMCHECKER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_IPXVBORDERENTRYPARAMCHECKER_H

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
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
} // end namespace batchOrder
} // end namespace domMod

#endif 

