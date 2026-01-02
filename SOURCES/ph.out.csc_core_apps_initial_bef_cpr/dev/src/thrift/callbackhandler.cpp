/*
 * callbackhandler.cpp
 *
 *  Created on: 17.10.2016
 *  Author: sebastian.barth
 */

#include "callbackhandler.h"

#include <boost/make_shared.hpp>
#include <logger/loggerpool.h>
#include <pxxmit.hpp>
#include "cscservicehelper.h"
#include "csccallback_types.h"

// Callback
#include <callback/domainmodule/icallback.h>
#include <callback/domainmodule/icallbackoverviewitem.h>
#include <callback/domainmodule/callbackoverviewcollection.h>
#include <callback/domainmodule/icallbackpos.h>
#include <callback/domainmodule/icallbackposptr.h>
#include <callback/domainmodule/callbackcustomerdm.h>
#include <callback/domainmodule/callbackcustomercollection.h>
#include <callback/domainmodule/callbackdivisiondm.h>
#include <callback/domainmodule/callbackdivisioncollection.h>
#include <callback/domainmodule/callbackreasondm.h>
#include <callback/domainmodule/callbackreasoncollection.h>
#include <callback/domainmodule/callbackstatusdm.h>
#include <callback/domainmodule/callbackstatuscollection.h>
#include <callback/domainmodule/newcallbackcritposdm.h>
#include <callback/domainmodule/newcallbackdm.h>
#include <callback/exceptions/callbacklockedexception.h>
#include <callback/exceptions/callbacknotfoundexception.h>
#include <callback/exceptions/customernotfoundexception.h>
#include <callback/repository/findcallbacksrequest.h>
#include <callback/repository/findcustomersrequest.h>
#include <types/messagecodeenum.inc>
#include <base/iint32result.h>
#include <base/irunnable.h>

namespace csc {
namespace service {

CallbackHandler::CallbackHandler()
{
}

CallbackHandler::~CallbackHandler()
{
}

void CallbackHandler::processGetCallback(callback::GetCallbackResponse& _return, callback::GetCallbackRequest const& request)
{
    libcsc::callback::domMod::ICallbackPtr callback;
    libcsc::callback::domMod::CallbackPosCollectionPtr callbackPos;
    try
    {
        bool result = getSession()->getCallbackComponentManager()->tryGetCallback(request.CallbackNo, request.BranchNo, callback, callbackPos);
        if (!result)
        {
            _return.__set_RetValue(getReturnStructForCallbackNotFound());
            return;
        }
    }
    catch (basar::Exception const& ex)
    {
        std::string message = blogException(ex, "processGetCallback");
        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }
    catch (...)
    {
        std::string message("CallbackHandler::processGetCallback() unknown exception 1");
        BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), message);

        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }

    try
    {
        copyToCscGetCallbackResponse(callback, callbackPos, _return);
    }
    catch (...)
    {
        std::string message("CallbackHandler::processGetCallback() unknown exception 2");
        BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), message);

        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
    }
}

void CallbackHandler::copyToCscGetCallbackResponse(
    libcsc::callback::domMod::ICallbackPtr const callback, libcsc::callback::domMod::CallbackPosCollectionPtr const callbackPos, callback::GetCallbackResponse& _return)
{
    _return.__set_CritLevel(static_cast<types::CritLevelEnum::type>(static_cast<basar::Int16>(callback->getCritLevel())));
    _return.__set_BranchNo(callback->getBranchNo());
    _return.__set_CallbackDateTime(Helper::getCscDateTimeFromInt(callback->getCallbackDate(), callback->getCallbackTime()));
    _return.__set_Title(callback->getTitle());
    _return.__set_CustomerNo(callback->getCustomerNo());
    _return.__set_CustomerClassTag(callback->getCustomerClassTag());
    _return.__set_PharmacyName(callback->getPharmacyName());
    _return.__set_OwnerName(callback->getOwnerName());
    _return.__set_ZipCode(callback->getZipCode());
    _return.__set_City(callback->getCity());
    _return.__set_Street(callback->getStreet());
    _return.__set_TelefonNo(callback->getTelefonNo());
    _return.__set_SpeedDialNo(callback->getSpeedDialNo());
    _return.__set_FaxNo(callback->getFaxNo());
    _return.__set_StatusNo(callback->getCallbackStatus());
    _return.__set_Reference(callback->getReference());


    callback::CallbackPosItemList callbackPosList;
    for (libcsc::callback::domMod::CallbackPosCollection::Iterator iter = callbackPos->begin(); iter != callbackPos->end(); ++iter)
    {
        libcsc::callback::domMod::ICallbackPosPtr libcscPos = *iter;
        callback::CallbackPosItem pos;
        pos.__set_Text(libcscPos->getText());
        pos.__set_CreationDateTime(Helper::getCscDateTimeFromInt(libcscPos->getCreationDate(), libcscPos->getCreationTime()));
        pos.__set_UserName(libcscPos->getUserName());
        pos.__set_CallbackNo(libcscPos->getCallbackNo());
        pos.__set_CallbackPosNo(libcscPos->getCallbackPosNo());
        pos.__set_CallbackPosNoDone(libcscPos->getCallbackPosNoDone());
        pos.__set_CallbackDateTimeWished(Helper::getCscDateTimeFromInt(libcscPos->getCallbackDateWished(), libcscPos->getCallbackTimeWished()));
        pos.__set_DivisionName(libcscPos->getDivisionName());
        callbackPosList.push_back(pos);
    }
    _return.__set_CallbackPositions(callbackPosList);
}

void CallbackHandler::processGetCallbackDivisions(callback::CallbackDivisionInquiryResponse& _return, callback::CallbackDivisionInquiryRequest const& request)
{
    libcsc::callback::domMod::CallbackDivisionCollectionPtr divisions;
    try
    {
        divisions = getSession()->getCallbackComponentManager()->getCallbackDivisions(request.BranchNo);
    }
    catch (basar::Exception const& ex)
    {
        std::string message = blogException(ex, "processGetCallbackDivisions");
        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }
    catch (...)
    {
        std::string message("CallbackHandler::processGetCallbackDivisions() unknown exception");
        BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), message);

        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }

    copyToCscGetCallbackDivisionsResponse(divisions, _return);
}

void CallbackHandler::copyToCscGetCallbackDivisionsResponse(libcsc::callback::domMod::CallbackDivisionCollectionPtr divisions, callback::CallbackDivisionInquiryResponse& _return)
{
    _return.Divisions.clear();
    _return.__isset.Divisions = true;
    for (libcsc::callback::domMod::CallbackDivisionCollection::Iterator iter = divisions->begin(); iter != divisions->end(); ++iter)
    {
        libcsc::callback::domMod::ICallbackDivisionPtr item = *iter;
        csc::callback::CallbackDivisionInquiryResponseItem responseItem;
        responseItem.__set_DivisionNo(item->getDivisionNo());
        responseItem.__set_DivisionName(item->getDivisionName());
        _return.Divisions.push_back(responseItem);
    }
}

void CallbackHandler::processGetCallbackReasons(callback::CallbackReasonInquiryResponse& _return, callback::CallbackReasonInquiryRequest const& request)
{
    libcsc::callback::domMod::CallbackReasonCollectionPtr reasons;
    try
    {
        reasons = getSession()->getCallbackComponentManager()->getCallbackReasons(request.BranchNo, request.DivisionNo);
    }
    catch (basar::Exception const& ex)
    {
        std::string message = blogException(ex, "processGetCallbackReasons");
        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }
    catch (...)
    {
        std::string message("CallbackHandler::processGetCallbackReasons() unknown exception");
        BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), message);

        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }

    copyToCscGetCallbackReasonsResponse(reasons, _return);
}

void CallbackHandler::processGetCallbackStatuses(callback::CallbackStatusInquiryResponse& _return, callback::CallbackStatusInquiryRequest const& request)
{
	libcsc::callback::domMod::CallbackStatusCollectionPtr statuses;
	try
	{
        statuses = getSession()->getCallbackComponentManager()->getCallbackStatuses(request.BranchNo);
	}
	catch (basar::Exception const& ex)
	{
		std::string message = blogException(ex, "processGetCallbackStatuses");
		_return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
		return;
	}
	catch (...)
	{
		std::string message("CallbackHandler::processGetCallbackStatuses() unknown exception");
		BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), message);

		_return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
		return;
	}

	copyToCscGetCallbackStatusesResponse(statuses, _return);
}

void CallbackHandler::processGetCallbackStatusVisibility(callback::CallbackStatusVisibilityInquiryResponse& _return, callback::CallbackStatusVisibilityInquiryRequest const& request)
{
	try
	{
		bool visible = getSession()->getCallbackComponentManager()->isCallbackStatusVisibile(request.BranchNo);
		_return.__set_Visible(visible);
	}
	catch (basar::Exception const& ex)
	{
		std::string message = blogException(ex, "processGetCallbackStatusVisibility");
		_return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
	}
	catch (...)
	{
		std::string message("CallbackHandler::processGetCallbackStatusVisibility() unknown exception");
		BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), message);
		_return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
	}
}

void CallbackHandler::copyToCscGetCallbackReasonsResponse(libcsc::callback::domMod::CallbackReasonCollectionPtr reasons, callback::CallbackReasonInquiryResponse& _return)
{
    _return.Reasons.clear();
    _return.__isset.Reasons = true;
    for (libcsc::callback::domMod::CallbackReasonCollection::Iterator iter = reasons->begin(); iter != reasons->end(); ++iter)
    {
        libcsc::callback::domMod::ICallbackReasonPtr item = *iter;
        csc::callback::CallbackReasonInquiryResponseItem responseItem;
        responseItem.__set_ReasonNo(item->getReasonNo());
        responseItem.__set_Reason(item->getReasonName());
        _return.Reasons.push_back(responseItem);
    }
}

void CallbackHandler::copyToCscGetCallbackStatusesResponse(libcsc::callback::domMod::CallbackStatusCollectionPtr statuses, callback::CallbackStatusInquiryResponse& _return)
{
	_return.CallbackStatuses.clear();
	_return.__isset.CallbackStatuses = true;
    for (libcsc::callback::domMod::CallbackStatusCollection::Iterator iter = statuses->begin(); iter != statuses->end(); ++iter)
    {
		libcsc::callback::domMod::ICallbackStatusPtr item = *iter;
		csc::callback::CallbackStatusInquiryResponseItem responseItem;
		responseItem.__set_CallbackStatusNo(item->getCallbackStatusNo());
		responseItem.__set_CallbackStatusName(item->getCallbackStatusName());
        responseItem.__set_CallbackStatusFlag(item->getCallbackStatusFlag());
		_return.CallbackStatuses.push_back(responseItem);
	}
}
void CallbackHandler::processFindCustomers(callback::FindCustomersResponse& _return, callback::FindCustomersRequest const& request)
{
    libcsc::callback::domMod::CallbackCustomerCollectionPtr customers;
    libcsc::callback::repo::FindCustomersRequestPtr findCustomersRequest = libcsc::callback::repo::FindCustomersRequest::create(
        request.BranchNo, request.OnlyOwnBranch, request.LockedCustomers,
        request.CustomerNo, request.MatchCode, request.OwnerName, request.PharmacyName, request.City, request.MaxResults);

    try
    {
        customers = getSession()->getCallbackComponentManager()->findCustomers(findCustomersRequest);
        basar::Int32 resultCount = customers->count();
        if (resultCount == findCustomersRequest->MaxResults)
        {
            resultCount = getSession()->getCallbackComponentManager()->getFindCustomersCount(findCustomersRequest);
        }
        _return.__set_CompleteResultCount(resultCount);
    }
    catch (basar::Exception const& ex)
    {
        std::string message = blogException(ex, "processFindCustomers");
        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }
    catch (...)
    {
        std::string message("CallbackHandler::processFindCustomers() unknown exception");
        BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), message);

        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }

    copyToCscFindCustomersResponse(customers, _return);
}

void CallbackHandler::copyToCscFindCustomersResponse(libcsc::callback::domMod::CallbackCustomerCollectionPtr customers, callback::FindCustomersResponse& _return)
{
    _return.Customers.clear();
    _return.__isset.Customers = true;
    for (libcsc::callback::domMod::CallbackCustomerCollection::Iterator iter = customers->begin(); iter != customers->end(); ++iter)
    {
        libcsc::callback::domMod::ICallbackCustomerPtr item = *iter;
        csc::callback::FindCustomersResponseItem responseItem;
        responseItem.__set_BranchNo(item->getBranchNo());
        responseItem.__set_OrigBranchNo(item->getOrigBranchNo());
        responseItem.__set_CustomerNo(item->getCustomerNo());
        responseItem.__set_CstBranchNo(item->getCstBranchNo());
        responseItem.__set_PharmacyName(item->getPharmacyName());
        responseItem.__set_OwnerName(item->getOwnerName());
        responseItem.__set_City(item->getCity());
        responseItem.__set_Street(item->getStreet());
        responseItem.__set_SpeedDialNo(item->getSpeedDialNo());
        _return.Customers.push_back(responseItem);
    }
}

void CallbackHandler::processWriteNewCallbackCritPos(callback::NewCallbackCritPosResponse& _return, callback::NewCallbackCritPosRequest const& request)
{
    try
    {
        if (!hasCallback(request.CallbackNo, request.BranchNo))
        {
            _return.__set_RetValue(getReturnStructForCallbackNotFound());
        }
        else
        {
            libcsc::callback::domMod::INewCallbackCritPosPtr newCallbackCritPos = createNewCallbackCritPos(request);
            libcsc::base::IRunnablePtr useCase = getSession()->getCallbackComponentManager()->getWriteNewCallbackCritPosUC(newCallbackCritPos);
            useCase->run();
        }
    }
    catch (libcsc::callback::exceptions::CallbackNotFoundException const& ex)
    {
        blogException(ex, "processWriteNewCallbackCritPos");
        _return.__set_RetValue(getReturnStructForCallbackNotFound());
    }
    catch (libcsc::callback::exceptions::CallbackLockedException const& ex)
    {
        blogException(ex, "processWriteNewCallbackCritPos");
        _return.__set_RetValue(getReturnStructForCallbackLockedException());
    }
    catch (basar::Exception const& ex)
    {
        std::string message = blogException(ex, "processWriteNewCallbackCritPos");
        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
    }
    catch (...)
    {
        std::string message("CallbackHandler::processWriteNewCallbackCritPos() unknown exception");
        BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), message);

        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
    }
}

bool CallbackHandler::hasCallback(int32_t const callbackNo, int16_t const branchNo)
{
    bool hasCallback;
    try
    {
        hasCallback = getSession()->getCallbackComponentManager()->hasCallback(callbackNo, branchNo);
    }
    catch (...)
    {
        BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), "CallbackHandler::hasCallback() unknown exception");

        throw;
    }

    return hasCallback;
}

libcsc::callback::domMod::INewCallbackCritPosPtr CallbackHandler::createNewCallbackCritPos(callback::NewCallbackCritPosRequest const& request)
{
    libcsc::callback::domMod::INewCallbackCritPosPtr newCallbackCritPos(libcsc::callback::domMod::NewCallbackCritPosDM::create());
    newCallbackCritPos->setCallbackNo(request.CallbackNo);
    newCallbackCritPos->setBranchNo(request.BranchNo);
    newCallbackCritPos->setUId(request.UId);
    newCallbackCritPos->setText(request.Text);
    newCallbackCritPos->setWindowsUser(request.WindowsUser);
    newCallbackCritPos->setSourceApplication(request.SourceApplication);
    newCallbackCritPos->setCallbackStatus(request.StatusNo);
    return newCallbackCritPos;
}

void CallbackHandler::processWriteNewCallback(callback::NewCallbackResponse& _return, callback::NewCallbackRequest const& request)
{
    try
    {
        libcsc::callback::domMod::INewCallbackPtr newCallback = createNewCallback(request);
        libcsc::base::IRunnablePtr useCase = getSession()->getCallbackComponentManager()->getWriteNewCallbackUC(newCallback);
        useCase->run();
        libcsc::base::IInt32Result* result = dynamic_cast<libcsc::base::IInt32Result*>(useCase.get());
        _return.__set_BranchNo(request.BranchNo);
        _return.__set_CallbackNo(result->getInt32Result());
    }
    catch (libcsc::callback::exceptions::CustomerNotFoundException const& ex)
    {
        blogException(ex, "processWriteNewCallback");
        _return.__set_RetValue(getReturnStructForCustomerNotFoundException());
    }
    catch (basar::Exception const& ex)
    {
        std::string message = blogException(ex, "processWriteNewCallback");
        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
    }
    catch (...)
    {
        std::string message("CallbackHandler::processWriteNewCallback() unknown exception");
        BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), message);

        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
    }
}

libcsc::callback::domMod::INewCallbackPtr CallbackHandler::createNewCallback(callback::NewCallbackRequest const& request)
{
    libcsc::callback::domMod::INewCallbackPtr newCallback(libcsc::callback::domMod::NewCallbackDM::create());
    newCallback->setBranchNo(request.BranchNo);
    newCallback->setCustomerNo(request.CustomerNo);
    newCallback->setCstBranchNo(request.CstBranchNo);
    newCallback->setDivisionNo(request.DivisionNo);
    newCallback->setReasonNo(request.ReasonNo);
    newCallback->setCritText(request.CritText);
    newCallback->setCritLevel(request.CritLevel);
    newCallback->setCallbackDateWished(Helper::getIntDateFromCscDateTime(request.CallbackDateTimeWished));
    newCallback->setCallbackTimeWished(Helper::getIntTimeFromCscDateTime(request.CallbackDateTimeWished));
    newCallback->setState(request.State);
    newCallback->setCallbackWantedText(request.CallbackWantedText);
    newCallback->setContactPerson(request.ContactPerson);
    newCallback->setUserName(request.WindowsUser);
    newCallback->setWebSiteBaseUrl(request.WebSiteBaseUrl);
    newCallback->setWindowsUser(request.WindowsUser);
    newCallback->setSourceApplication(request.SourceApplication);
    newCallback->setUId(request.UId);
    newCallback->setSendEmail(request.SendEmail);
    newCallback->setCallbackStatus(request.StatusNo);
    newCallback->setReference(request.Reference);
    return newCallback;
}

void CallbackHandler::processFindCallbacks(callback::FindCallbacksResponse& _return, callback::FindCallbacksRequest const& request)
{
    libcsc::callback::repo::FindCallbacksRequestPtr findCallbacksRequest = libcsc::callback::repo::FindCallbacksRequest::create(
        request.BranchNo, request.OnlyOwnBranch, request.CustomerNo, request.Title,
        csc::service::Helper::getIntDateFromCscDate(request.DateFrom), csc::service::Helper::getIntDateFromCscDate(request.DateTo),
        request.DivisionNo, request.ReasonNo, request.MaxResults, request.StatusNo);

    libcsc::callback::domMod::CallbackOverviewCollectionPtr callbacks;

    try
    {
        callbacks = getSession()->getCallbackComponentManager()->findCallbacks(findCallbacksRequest);
        basar::Int32 resultCount = callbacks->count();
        if (resultCount == findCallbacksRequest->MaxResults)
        {
            resultCount = getSession()->getCallbackComponentManager()->getFindCallbacksCount(findCallbacksRequest);
        }
        _return.__set_CompleteResultCount(resultCount);
    }
    catch (basar::Exception const& ex)
    {
        std::string message = blogException(ex, "processFindCallbacks");
        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }
    catch (...)
    {
        std::string message("CallbackHandler::processFindCallbacks() unknown exception");
        BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), message);

        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }

    copyToCscFindCallbacksResponse(callbacks, _return);
}

void CallbackHandler::copyToCscFindCallbacksResponse(libcsc::callback::domMod::CallbackOverviewCollectionPtr callbacks, callback::FindCallbacksResponse& _return)
{
    _return.Callbacks.clear();
    _return.__isset.Callbacks = true;

    for (libcsc::callback::domMod::CallbackOverviewCollection::Iterator iter = callbacks->begin(); iter != callbacks->end(); ++iter)
    {
        libcsc::callback::domMod::ICallbackOverviewItemPtr item = *iter;
        csc::callback::FindCallbacksResponseItem responseItem;
        responseItem.__set_CallbackNo(item->getCallbackNo());
        responseItem.__set_BranchNo(item->getBranchNo());
        responseItem.__set_CallbackDateTime(Helper::getCscDateTimeFromInt(item->getCallbackDate(), item->getCallbackTime()));
        responseItem.__set_ReasonName(item->getReasonName());
        responseItem.__set_PharmacyName(item->getPharmacyName());
        responseItem.__set_City(item->getCity());
        responseItem.__set_CritLevel(static_cast<types::CritLevelEnum::type>(static_cast<basar::Int16>(item->getCritLevel())));
        responseItem.__set_CallbackStatus(item->getCallbackStatus());
        responseItem.__set_DivisionName(item->getDivisionName());
        responseItem.__set_Reference(item->getReference());
        _return.Callbacks.push_back(responseItem);
    }
}

void CallbackHandler::processGetCallbackDivisionAndReasonName(
    callback::GetCallbackDivisionAndReasonNameResponse& _return, callback::GetCallbackDivisionAndReasonNameRequest const& request)
{
    try
    {
        basar::VarString divisionName;
        basar::VarString reasonName;
        getSession()->getCallbackComponentManager()->getGetCallbackDivisionAndReasonName(request.BranchNo, request.DivisionNo, request.ReasonNo, divisionName, reasonName);

        _return.__set_DivisionName(divisionName);
        _return.__set_ReasonName(reasonName);
    }
    catch (basar::Exception const& ex)
    {
        std::string message = blogException(ex, "processGetCallbackDivisionAndReasonName");
        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }
    catch (...)
    {
        std::string message = "CallbackHandler::processGetCallbackDivisionAndReasonName() unknown exception";
        BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), message);

        _return.__set_RetValue(getReturnStructFromMiscExceptionMessage(message));
        return;
    }
}

base::ReturnStruct CallbackHandler::getReturnStructFromMiscExceptionMessage(std::string const& message)
{
    nError error;
    error.ExternalError(getSession()->CMsgStream(), CMSG_MISC_EXCEPTION, message.c_str());
    return Helper::getReturnStructFromError(error);
}

base::ReturnStruct CallbackHandler::getReturnStructForCallbackNotFound()
{
    nError error;
    error.ExternalError(getSession()->CMsgStream(), CMSG_LIBCSC_CALLBACK_NOTFOUND);
    return Helper::getReturnStructFromError(error);
}

base::ReturnStruct CallbackHandler::getReturnStructForCallbackLockedException()
{
    nError error;
    error.ExternalError(getSession()->CMsgStream(), CMSG_LIBCSC_CALLBACK_LOCKED);
    return Helper::getReturnStructFromError(error);
}

base::ReturnStruct CallbackHandler::getReturnStructForCustomerNotFoundException()
{
    nError error;
    error.ExternalError(getSession()->CMsgStream(), CMSG_LIBCSC_CALLBACK_CUSTOMERNOTFOUND);
    return Helper::getReturnStructFromError(error);
}

std::string CallbackHandler::blogException(basar::Exception const& ex, std::string const& methodName)
{
    std::stringstream ss;
    ss << "CallbackHandler::" << methodName << "() exception: " << ex.what() << std::endl << ex.stackTrace();
    BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), ss.str());
    return ss.str();
}

} // namespace service
} // namespace csc
