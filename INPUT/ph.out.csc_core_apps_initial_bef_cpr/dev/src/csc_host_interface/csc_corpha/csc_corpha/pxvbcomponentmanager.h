//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBCOMPONENTMANAGER_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBCOMPONENTMANAGER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "ipxvbservicelocatorptr.h"
#include "ipxvbservicelocator.h"
#include "ipxvbsessionptr.h"
#include "ipxvbdbconnectionptr.h"
#include "ipxvbinitializationptr.h"
#include "ipxvborderentryparamcheckerptr.h"
#include "pxordertransmitptr.h"
#include "pxorderentryparamptr.h"

#include <iapplconfigurationptr.h>
#include <icsc_loggerptr.h>

#include "pvhx04_includes.h"

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	

class PXVBComponentManager : public domMod::corpha::pxVerbund::IPXVBServiceLocator
{			
    public:		
		PXVBComponentManager( libcsc_utils::IApplConfigurationPtr, libcsc_utils::ICSC_LoggerPtr );
        ~PXVBComponentManager();             		

		virtual IPXVBSessionPtr						getPXVBSession();
        virtual IPXVBDBConnectionPtr				getPXVBDBConnection();
        virtual IPXVBInitializationPtr				getPXVBInitialization();
		virtual IPXVBOrderEntryParamCheckerPtr		getPXVBOrderEntryParamChecker();

    private:
        ///////////////////////////////////////////////////////////////////////////////////
        // member methods
        ///////////////////////////////////////////////////////////////////////////////////
        PXVBComponentManager( const PXVBComponentManager& );
		PXVBComponentManager& operator= ( const PXVBComponentManager& );        		
		
		pxOrderTransmitPtr							getPXOrderTransmit();
		pxOrderEntryParamPtr						getPXOrderEntryParam();

        ///////////////////////////////////////////////////////////////////////////////////
        // member variables
        ///////////////////////////////////////////////////////////////////////////////////
        // real pxVerbund
		::pxOrderTransmitPtr						m_pxOrderTransmit;
		::pxOrderEntryParamPtr						m_pxOrderEntryParam;

        // pxVerbund wrappers (csc_phatra specific)
		IPXVBSessionPtr								m_PXVBSession;
		IPXVBDBConnectionPtr						m_PXVBDBConnection;
        IPXVBInitializationPtr				        m_PXVBInitialization;
		IPXVBOrderEntryParamCheckerPtr		        m_PXVBOrderEntryParamChecker;

        // configuration & logger
		libcsc_utils::IApplConfigurationPtr			m_IApplConfiguration;
		libcsc_utils::ICSC_LoggerPtr				m_CSC_Logger;
};

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod

#endif 

