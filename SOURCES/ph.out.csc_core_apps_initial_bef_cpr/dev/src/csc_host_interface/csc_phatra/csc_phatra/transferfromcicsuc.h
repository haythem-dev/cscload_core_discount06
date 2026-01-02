//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//

#ifndef GUARD_TRANSFERFROMCICSUC_H
#define GUARD_TRANSFERFROMCICSUC_H

//-------------------------------------------------------------------------------------------//

#include "transferbaseuc.h"
#include <iremoteprocedurecallerptr.h>
#include "cicspharmostransactiondmptr.h"

//-------------------------------------------------------------------------------------------//

namespace csc_phatra {
namespace useCase {

//-------------------------------------------------------------------------------------------//

class TransferFromCicsUC : public TransferBaseUC
{
public:
	TransferFromCicsUC();
	virtual ~TransferFromCicsUC();

	void injectPDX010Caller(libcsc_utils::IRemoteProcedureCallerPtr pdx010caller);
	void injectCICSPharmosTransactionDMPtr(domMod::pharmosTransaction::preparation::CICSPharmosTransactionDMPtr cicsPharmosTransactionDM);
	
	basar::Int32 getRecordsProcessed();

protected:
	virtual basar::appl::EventReturnStruct doRun();
	virtual void doCheckInjections() const;

private:
	basar::Int32 callRemoteProcedure();
	void transferCICSPharmosTransactions();

	libcsc_utils::IRemoteProcedureCallerPtr 								m_pdx010caller;
	domMod::pharmosTransaction::preparation::CICSPharmosTransactionDMPtr	m_cicsPharmosTransactionDM;
};

//-------------------------------------------------------------------------------------------//

typedef boost::shared_ptr<TransferFromCicsUC> TransferFromCicsUCPtr;

//-------------------------------------------------------------------------------------------//

} //namespace useCase
} //namespace csc_phatra

//-------------------------------------------------------------------------------------------//

#endif // GUARD_TRANSFERFROMCICSUC_H

//-------------------------------------------------------------------------------------------//

