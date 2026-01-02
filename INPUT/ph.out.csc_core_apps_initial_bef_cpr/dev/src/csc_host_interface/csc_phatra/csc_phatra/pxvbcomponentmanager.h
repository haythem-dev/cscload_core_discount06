//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  PXVBComponentManager
 *  \author Steffen Heinlein
 *  \date   09.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBCOMPONENTMANAGER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBCOMPONENTMANAGER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "ipxvbservicelocator.h"

#include "ipxvbsessionptr.h"
#include "ipxvbdbconnectionptr.h"
#include "ipxvbinitializationptr.h"
#include "ipxvborderentryparamcheckerptr.h"
#include <iapplconfigurationptr.h>
#include <icsc_loggerptr.h>
#include <dbconnectionbaseptr.h>

#include "pvhx01_includes.h"

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace pxVerbund
{	

class PXVBComponentManager : public IPXVBServiceLocator
{			
    public:		
		PXVBComponentManager( libcsc_utils::IApplConfigurationPtr, libcsc_utils::ICSC_LoggerPtr );
        ~PXVBComponentManager();             		

        void                                        injectIFXConnection( libBatch::dbConnection::DBConnectionBasePtr );

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
        // real pxverbund
		::pxOrderTransmitPtr						m_pxOrderTransmit;
		::pxOrderEntryParamPtr						m_pxOrderEntryParam;

        // pxverbund wrappers (csc_phatra specific)
		IPXVBSessionPtr								m_PXVBSession;
		IPXVBDBConnectionPtr						m_PXVBDBConnection;
        IPXVBInitializationPtr				        m_PXVBInitialization;
		IPXVBOrderEntryParamCheckerPtr		        m_PXVBOrderEntryParamChecker;

        // configuration & logger
		libcsc_utils::IApplConfigurationPtr			m_IApplConfiguration;
		libcsc_utils::ICSC_LoggerPtr				m_CSC_Logger;
        libBatch::dbConnection::DBConnectionBasePtr m_IFXConnection;
};

} // end namespace pxVerbund
} // end namespace pharmosTransaction
} // end namespace domMod

#endif 
