//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Steffen Heinlein
 *  \date       10.07.2012
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "cmndm.h"

#include "pxvbinitialization.h"

#include "pvhx04_includes.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace pxVerbund
{	

//--------------------------------------------------------------------------------------------------//
	PXVBInitialization::PXVBInitialization( pxOrderTransmitPtr xmit, pxOrderEntryParamPtr oeparam )
	: m_pxOrderTransmit( xmit ), m_pxOrderEntryParam( oeparam )
	{
	}

//--------------------------------------------------------------------------------------------------//
	PXVBInitialization::~PXVBInitialization()
	{
	}

//--------------------------------------------------------------------------------------------------//
	bool PXVBInitialization::isInitialized() const
	{
		return (m_pxOrderTransmit->IsGoodState() && m_pxOrderEntryParam->IsGoodState());
	}

//--------------------------------------------------------------------------------------------------//

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod
