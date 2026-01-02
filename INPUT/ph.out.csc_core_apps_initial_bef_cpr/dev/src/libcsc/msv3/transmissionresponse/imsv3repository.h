#ifndef GUARD_LIBCSC_MSV3_IMSV3REPOSITORY_H
#define GUARD_LIBCSC_MSV3_IMSV3REPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasar_definitions.h>
//#include "callback/domainmodule/callbackdivisioncollectionptr.h"
//#include "callback/domainmodule/callbackreasoncollectionptr.h"
#include "msv3/domainmodule/imsv3transmissionresponseptr.h"
//#include "callback/domainmodule/icallbackcustomerptr.h"
//#include "callback/domainmodule/icallbackitemptr.h"
//#include "callback/domainmodule/icallbackreasonptr.h"
//#include "callback/domainmodule/icritposptr.h"
//#include "callback/domainmodule/icritptr.h"

namespace libcsc {
namespace msv3 {
namespace repo {

class IMSV3Repository
{
public:
	virtual ~IMSV3Repository() {}

	virtual void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory) = 0;
	virtual void injectFindAccessor(persistence::IAccessorPtr accessor) = 0;
	virtual void injectInsertAccessor(persistence::IAccessorPtr accessor) = 0;
	virtual void injectUpdateAccessor(persistence::IAccessorPtr accessor) = 0;

	virtual domMod::IMSV3TransmissionResponsePtr findMSV3TransmissionResponse(const basar::VarString& transmissionUuid) const = 0;

	//virtual bool hasCallback(basar::Int32 const callbackNo) const = 0;
	//virtual bool tryGetCallback(basar::Int32 const callbackNo, domMod::ICallbackPtr& callback) const = 0;

	//virtual void writeNewCritPos(basar::Int32 const callbackNo, domMod::ICritPosPtr critPos) = 0;


	//virtual domMod::ICallbackReasonPtr findCallbackReason(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo) const = 0;
	//virtual basar::Int32 writeNewCallback(domMod::ICallbackItemPtr callback, domMod::ICritPtr crit, domMod::ICritPosPtr critPos) = 0;
	//virtual basar::VarString getCallbackMailingList(short const branchNo, short const divisionNo, short const reasonNo) const = 0;

	//virtual domMod::ICallbackCustomerPtr findCustomer(basar::Int16 const branchNo, basar::Int32 const customerNo) const = 0;
};

} // end namespace repo
} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_IMSV3REPOSITORY_H
