//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief csc_phatra's sole usecase
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_CSC_PHATRA_USECASE_CSC_PHATRAUC_H
#define GUARD_CSC_PHATRA_USECASE_CSC_PHATRAUC_H


//-------------------------------------------------------------------------------------------//

#include <libbasarappl.h>
#include "itransferuc.h"

#include "icsc_heartbeatptr.h"
#include <icsc_loggerptr.h>
#include <isignalreceiver.h>

//-------------------------------------------------------------------------------------------//

namespace csc_phatra {
namespace useCase {

//-------------------------------------------------------------------------------------------//

class CSC_PhatraUC : public libcsc_utils::ISignalReceiver
{
public:
	CSC_PhatraUC();
	virtual ~CSC_PhatraUC();

	void receiveSignal(int signal);
	void flagTesting();
				
	void injectICSC_LoggerPtr(libcsc_utils::ICSC_LoggerPtr csc_logger);
	void injectHeartBeat(csc_phatra::ICSC_HeartBeatPtr heartBeat);

	void injectTransferFromCicsUC(ITransferUCPtr uc);
	void injectTransferFromZdpUC(ITransferUCPtr uc);
	void injectTransferToCscUC(ITransferUCPtr uc);

	basar::appl::EventReturnStruct run();

private:
	void flagExitGracefull();
	void checkInjections() const;
			
	bool					m_ExitGracefull;
	bool                    m_IsTesting;

	libcsc_utils::ICSC_LoggerPtr	m_CSC_Logger;
	csc_phatra::ICSC_HeartBeatPtr	m_HeartBeat;

	ITransferUCPtr m_TransferFromCicsUC;
	ITransferUCPtr m_TransferFromZdpUC;
	ITransferUCPtr m_TransferToCscUC;
};

//-------------------------------------------------------------------------------------------//

} //namespace useCase
}//namespace csc_phatra

//-------------------------------------------------------------------------------------------//

#endif // GUARD_CSC_PHATRA_USECASE_CSC_PHATRAUC_H

//-------------------------------------------------------------------------------------------//
