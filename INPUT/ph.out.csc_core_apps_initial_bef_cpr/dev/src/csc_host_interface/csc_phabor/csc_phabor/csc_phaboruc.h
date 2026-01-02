//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief csc_phabor's sole usecase
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_CSC_PHABOR_USECASE_CSC_PHABORUC_H
#define GUARD_CSC_PHABOR_USECASE_CSC_PHABORUC_H

#include <libbasarappl.h>
#include <iremoteprocedurecallerptr.h>
#include <icsc_loggerptr.h>
#include <isignalreceiver.h>
#include <iapplconfigurationptr.h>
#include <iremoteprocedureptr.h>

#include "appsessionptr.h"
#include "appsession.h"
#include "batchorderdmbaseptr.h"
#include "cicsbatchorderdmptr.h"
#include "batchorderdmptr.h"
#include "batchordertransformerptr.h"
#include "batchordercollectionptr.h"
#include "batchorderptr.h"
#include "itransferkeygetterptr.h"
#include "initparamsdmptr.h"
#include "cscbatchorderdmptr.h"
#include "icsc_heartbeatptr.h"

namespace csc_phabor
{
	namespace useCase
	{
		class CSC_PhaborUC : public libcsc_utils::ISignalReceiver
		{
			public:
				CSC_PhaborUC();
				~CSC_PhaborUC();

				void init();
				basar::appl::EventReturnStruct run();

				void flagExitGracefull();
				void flagTesting();
				void flagTransfer();
				void flagProcess();

				void receiveSignal(int signal);

                void injectPDX050Caller				(libcsc_utils::IRemoteProcedureCallerPtr				pdx050caller			);
				void injectCICSBatchOrderDMPtr		(domMod::batchOrder::preparation::CICSBatchOrderDMPtr	cicsBatchOrderDMPtr		);
				void injectIFXBatchOrderDMPtr		(domMod::batchOrder::processing::BatchOrderDMPtr		ifxBatchOrderDMPtr		);
				void injectCSCBatchOrderDMPtr		(domMod::batchOrder::processing::CSCBatchOrderDMPtr		cscBatchOrderDMPtr		);
				void injectTransferKeyGetterPtr		(domMod::batchOrder::util::ITransferKeyGetterPtr		transferKeyGetter		);
				void injectInitParamsDMPtr			(domMod::InitParamsDMPtr								initParamsDM			);
				void injectBatchOrderTransformer	(domMod::batchOrder::core::BatchOrderTransformerPtr	    batchOrderTransformer	);
				void injectICSC_LoggerPtr			(libcsc_utils::ICSC_LoggerPtr							csc_logger				);
			    void injectHeartBeat				(csc_phabor::ICSC_HeartBeatPtr							heartBeat				);
				void injectAppSession				(csc_phabor::AppSessionPtr								appSession				);
				void injectAppConfig				(libcsc_utils::IApplConfigurationPtr					appConfig				);
        
				
			private:

				void												checkInjections() const;
				basar::Int32										callRemoteProcedure();
				void												transferCICSBatchOrders();
				void												processCICSBatchOrders();
				void												logAccessors( const basar::VarString& logMsg );
				domMod::batchOrder::core::BatchOrderPtr				getEmptyIfxOrder();
				domMod::batchOrder::core::BatchOrderPtr				getEmptyPxvbOrder();
				basar::Int32										getLastKey();
				domMod::batchOrder::core::BatchOrderCollectionPtr	findOpenCicsOrders();
				domMod::batchOrder::core::BatchOrderCollectionPtr   findOpenIfxOrders();
				void												setCicsStatusTransfered( domMod::batchOrder::core::BatchOrderPtr cicsOrder );

				bool												 m_ExitGracefull;
				bool                                                 m_IsTesting;
				bool                                                 m_Transfer;
				bool                                                 m_Process;
				libcsc_utils::IRemoteProcedureCallerPtr				 m_pdx050caller;
				libcsc_utils::ICSC_LoggerPtr						 m_CSC_Logger;
				domMod::batchOrder::core::BatchOrderTransformerPtr   m_BatchOrderTransformer;
				domMod::batchOrder::preparation::CICSBatchOrderDMPtr m_CicsBatchOrderDMPtr;
				domMod::batchOrder::processing::BatchOrderDMPtr		 m_IfxBatchOrderDMPtr;
				domMod::batchOrder::processing::CSCBatchOrderDMPtr	 m_CscBatchOrderDMPtr;	
				domMod::batchOrder::util::ITransferKeyGetterPtr		 m_TransferKeyGetter;
				domMod::InitParamsDMPtr								 m_InitParamsDM;
				csc_phabor::ICSC_HeartBeatPtr						 m_HeartBeat;
				csc_phabor::AppSessionPtr							 m_AppSession;
				libcsc_utils::IApplConfigurationPtr					 m_ApplConfiguration;
		};
	} //namespace useCase
}//namespace csc_phabor

#endif //#ifndef GUARD_CSC_PHABOR_USECASE_CSC_PHABORUC_H
