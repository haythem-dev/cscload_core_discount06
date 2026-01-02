/*
 * callbackhandler.h
 *
 *  Created on: 17.10.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_CSC_SERVICE_CALLBACKHANDLER_H
#define GUARD_CSC_SERVICE_CALLBACKHANDLER_H

#include <libbasar_definitions.h>
#include <pxordertransmitptr.h>
#include <callback/domainmodule/callbackoverviewcollectionptr.h>
#include <callback/domainmodule/callbackposcollectionptr.h>
#include <callback/domainmodule/callbackcustomercollectionptr.h>
#include <callback/domainmodule/callbackdivisioncollectionptr.h>
#include <callback/domainmodule/callbackreasoncollectionptr.h>
#include <callback/domainmodule/callbackstatuscollectionptr.h>
#include <callback/domainmodule/icallbackptr.h>
#include <callback/domainmodule/inewcallbackcritposptr.h>
#include <callback/domainmodule/inewcallbackptr.h>
#include <callback/repository/findcallbacksrequest.h>

#include "csccallback_types.h"
#include "csclibtothrifthandlerbase.h"

namespace csc {
namespace service {

class CallbackHandler : public CscLibToThriftHandlerBase
{
public:
    CallbackHandler();
    virtual ~CallbackHandler();

    void processGetCallback(callback::GetCallbackResponse& _return, callback::GetCallbackRequest const& request);

    void processGetCallbackDivisions(callback::CallbackDivisionInquiryResponse& _return, callback::CallbackDivisionInquiryRequest const& request);

    void processGetCallbackReasons(callback::CallbackReasonInquiryResponse& _return, callback::CallbackReasonInquiryRequest const& request);

    void processGetCallbackStatuses(callback::CallbackStatusInquiryResponse& _return, callback::CallbackStatusInquiryRequest const& request);

	void processGetCallbackStatusVisibility(callback::CallbackStatusVisibilityInquiryResponse& _return, callback::CallbackStatusVisibilityInquiryRequest const& request);

    void processFindCustomers(callback::FindCustomersResponse& _return, callback::FindCustomersRequest const& request);

    void processWriteNewCallbackCritPos(callback::NewCallbackCritPosResponse& _return, callback::NewCallbackCritPosRequest const& request);

    void processWriteNewCallback(callback::NewCallbackResponse& _return, callback::NewCallbackRequest const& request);

    void processFindCallbacks(callback::FindCallbacksResponse& _return, callback::FindCallbacksRequest const& request);

    void processGetCallbackDivisionAndReasonName(callback::GetCallbackDivisionAndReasonNameResponse& _return, callback::GetCallbackDivisionAndReasonNameRequest const& request);

private:
    void copyToCscGetCallbackResponse(libcsc::callback::domMod::ICallbackPtr const callback, libcsc::callback::domMod::CallbackPosCollectionPtr const callbackPos, callback::GetCallbackResponse& _return);
    bool hasCallback(int32_t const callbackNo, int16_t const branchNo);
    libcsc::callback::domMod::INewCallbackCritPosPtr createNewCallbackCritPos(callback::NewCallbackCritPosRequest const& request);
    libcsc::callback::domMod::INewCallbackPtr createNewCallback(callback::NewCallbackRequest const& request);
    void copyToCscFindCallbacksResponse(libcsc::callback::domMod::CallbackOverviewCollectionPtr callbacks, callback::FindCallbacksResponse& _return);
    void copyToCscFindCustomersResponse(libcsc::callback::domMod::CallbackCustomerCollectionPtr customers, callback::FindCustomersResponse& _return);
    void copyToCscGetCallbackDivisionsResponse(libcsc::callback::domMod::CallbackDivisionCollectionPtr divisions, callback::CallbackDivisionInquiryResponse& _return);
    void copyToCscGetCallbackReasonsResponse(libcsc::callback::domMod::CallbackReasonCollectionPtr reasons, callback::CallbackReasonInquiryResponse& _return);
    void copyToCscGetCallbackStatusesResponse(libcsc::callback::domMod::CallbackStatusCollectionPtr statuses, callback::CallbackStatusInquiryResponse& _return);

    base::ReturnStruct getReturnStructFromMiscExceptionMessage(std::string const& message);
    base::ReturnStruct getReturnStructForCallbackNotFound();
    base::ReturnStruct getReturnStructForCallbackLockedException();
    base::ReturnStruct getReturnStructForCustomerNotFoundException();

    std::string blogException(basar::Exception const& ex, std::string const& methodName);
};

} // namespace service
} // namespace csc

#endif // GUARD_CSC_SERVICE_CALLBACKHANDLER_H
