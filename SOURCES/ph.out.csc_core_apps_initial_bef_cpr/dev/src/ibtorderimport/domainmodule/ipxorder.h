#ifndef GUARD_IBTORDERIMPORT_DOMMOD_IPXORDER_H
#define GUARD_IBTORDERIMPORT_DOMMOD_IPXORDER_H

#include <libbasar_definitions.h>
#include <ibt/ibtrequest/iibtrequestptr.h>
#include <ibt/ibtresponse/iibtresponseptr.h>
#include "ipxorderitemptr.h"

//-------------------------------------------------------------------------------------------------//

namespace ibtorderimport {
namespace domMod {

//-------------------------------------------------------------------------------------------------//

class IPxOrder
{
public:
	virtual ~IPxOrder() {};

	virtual bool isBatchWriting() const = 0;
	virtual void activateBatchWriting() = 0;
	virtual void determineIbtComment() = 0;
	virtual void setOriginBranchNo(const basar::Int16) = 0;
	virtual basar::Int32 getOrderNo() = 0;
    

	virtual IPxOrderItemPtr addPosition(const libcsc::ibt::IIbtRequestPtr) = 0;
	virtual void setOrderType(libcsc::ibt::IIbtRequestPtr) = 0;
	virtual void setPaymentTerm(basar::VarString const&) = 0;
	virtual void markAsNewSuivra() = 0;

};

//-------------------------------------------------------------------------------------------------//

} // namespace domMod
} // namespace ibtorderimport

//-------------------------------------------------------------------------------------------------//

#endif // GUARD_IBTORDERIMPORT_DOMMOD_IPXORDER_H

//-------------------------------------------------------------------------------------------------//
