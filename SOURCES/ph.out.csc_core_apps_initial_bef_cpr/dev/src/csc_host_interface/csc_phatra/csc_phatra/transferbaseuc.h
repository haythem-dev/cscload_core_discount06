//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_TRANSFERBASEUC_H
#define GUARD_TRANSFERBASEUC_H

//-------------------------------------------------------------------------------------------//

#include "itransferuc.h"
#include "pharmostransactiondmptr.h"
#include "recordtypefactoryptr.h"
#include <icsc_loggerptr.h>

//-------------------------------------------------------------------------------------------//

namespace csc_phatra {
namespace useCase {

//-------------------------------------------------------------------------------------------//

class TransferBaseUC : public ITransferUC
{
public:
	TransferBaseUC();
	virtual ~TransferBaseUC();

	void injectPharmosTransactionDMPtr(domMod::pharmosTransaction::core::PharmosTransactionDMPtr pharmosTransactionDM);
	void injectRecordTypeFactoryPtr(domMod::pharmosTransaction::core::RecordTypeFactoryPtr recordTypeFactory);
	void injectICSC_LoggerPtr(libcsc_utils::ICSC_LoggerPtr csc_logger);

	virtual basar::appl::EventReturnStruct run();
	virtual basar::Int32 getRecordsProcessed();

protected:
	virtual basar::appl::EventReturnStruct	doRun() = 0;
	virtual void							doCheckInjections() const = 0;

private:
	void checkInjections() const;

protected:
	libcsc_utils::ICSC_LoggerPtr								m_CSC_Logger;
	domMod::pharmosTransaction::core::PharmosTransactionDMPtr	m_pharmosTransactionDM;
	domMod::pharmosTransaction::core::RecordTypeFactoryPtr		m_RecordTypeFactory;
	basar::Int32												m_RecordsProcessed;
};

//-------------------------------------------------------------------------------------------//

} //namespace useCase
} //namespace csc_phatra

//-------------------------------------------------------------------------------------------//

#endif // GUARD_TRANSFERBASEUC_H

//-------------------------------------------------------------------------------------------//
