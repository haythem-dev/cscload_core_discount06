//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief csc_corpha's sole usecase
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_CSC_Corpha_USECASE_CSC_CorphaUC_H
#define GUARD_CSC_Corpha_USECASE_CSC_CorphaUC_H

#include <libbasarappl.h>
#include <icsc_loggerptr.h>
#include <iapplconfigurationptr.h>

#include "ipxvbtaskcontrolptr.h"
#include "ipxvbservicelocatorptr.h"
#include "ipxvbordercollectionptr.h"
#include "icicsorderdmptr.h"
#include "iremoteprocedureservicelocatorptr.h"
#include "pxvbordercollectiondm_definitions.h"
#include "pxvborderdmptr.h"

namespace csc_corpha
{
	namespace useCase
	{
		class CSC_CorphaUC
		{			
			public:
				CSC_CorphaUC();
				~CSC_CorphaUC();

			public:				
				void								flagExitGracefull();				

				basar::appl::EventReturnStruct		run();

				void								injectICSC_LoggerPtr( libcsc_utils::ICSC_LoggerPtr );
				void								injectApplConfiguration( libcsc_utils::IApplConfigurationPtr );
				void								injectPXVBServiceLocatorPtr( domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr );
				void								injectPXVBOrderCollectionPtr( domMod::corpha::pxVerbund::IPXVBOrderCollectionPtr );
				void								injectCICSOrderDM( domMod::corpha::processOrder::ICICSOrderDMPtr );				
				void								injectRemoteProcedureServiceLocatorPtr( domMod::corpha::IRemoteProcedureServiceLocatorPtr );
				void								injectPXVBTaskControl( domMod::corpha::pxVerbund::IPXVBTaskControlPtr );
				
			private:
				void								checkInjections() const;								

				bool								lockOrder4Transfer( domMod::corpha::pxVerbund::PXVBOrderDMPtr );
				void								unlockOrder4Transfer( domMod::corpha::pxVerbund::PXVBOrderDMPtr );
				bool								hasToBeTransferred( domMod::corpha::pxVerbund::PXVBOrderDMPtr );
				void								startOrderTransfer( domMod::corpha::pxVerbund::PXVBOrderDMPtr );
				void								sendOrder2Pharmos( domMod::corpha::pxVerbund::PXVBOrderDMPtr );
				void								finishOrderTransfer( domMod::corpha::pxVerbund::PXVBOrderDMPtr );
				void								finishOrderWithoutTransfer( domMod::corpha::pxVerbund::PXVBOrderDMPtr );
				void								callRemoteOrderProcessing( basar::Long64 orderno, basar::Long64 time );
				basar::VarString					getInstanceDetails() const;

				domMod::corpha::pxVerbund::OrderSelectionMode	getOrderSelectionMode() const;

			private:				
				basar::Long64										m_CurrentOrder;
				bool												m_ExitGracefull;
				bool												m_PDX040Result;
				libcsc_utils::ICSC_LoggerPtr						m_CSC_Logger;				
				libcsc_utils::IApplConfigurationPtr					m_ApplConfiguration;
				domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr	m_PXVBServiceLocator;	
				domMod::corpha::pxVerbund::IPXVBOrderCollectionPtr  m_PXVBOrderCollection;
				domMod::corpha::processOrder::ICICSOrderDMPtr		m_CICSOrderDM;				
				domMod::corpha::IRemoteProcedureServiceLocatorPtr	m_RemoteProcedureServiceLocator;												
				domMod::corpha::pxVerbund::IPXVBTaskControlPtr		m_PXVBTaskControl;
		};
	} //namespace useCase
}//namespace csc_corpha

#endif //#ifndef GUARD_CSC_Corpha_USECASE_CSC_CorphaUC_H
