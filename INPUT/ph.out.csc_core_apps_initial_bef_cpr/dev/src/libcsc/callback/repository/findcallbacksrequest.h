/*
 * findcallbacksrequest.h
 *
 *  Created on: 25.10.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPO_FINDCALLBACKSREQUEST_H
#define GUARD_LIBCSC_CALLBACK_REPO_FINDCALLBACKSREQUEST_H

#include <boost/shared_ptr.hpp>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace callback {
namespace repo {

struct FindCallbacksRequest;
typedef boost::shared_ptr<FindCallbacksRequest> FindCallbacksRequestPtr;

struct FindCallbacksParams {
    basar::Int16 branchNo;
    bool onlyOwnBranch;
    basar::Int32 customerNo;
    basar::VarString title;
    basar::Int32 dateFrom;
    basar::Int32 dateTo;
    basar::Int16 divisionNo;
    basar::Int16 reasonNo;
    basar::Int16 statusNo;

    basar::Int32 maxResults;

    // Constructor for easy initialization
    FindCallbacksParams(basar::Int16 const& bNo, bool const& ownBranch, basar::Int32 const& custNo, basar::VarString const& _title, basar::Int32 const& dFrom,
        basar::Int32 const& dTo, basar::Int16 const& divNo, basar::Int16 const& reasNo, basar::Int32 const& maxRes, basar::Int16 const& statNo)
        : branchNo(bNo), onlyOwnBranch(ownBranch), customerNo(custNo),
        title(_title), dateFrom(dFrom), dateTo(dTo),
        divisionNo(divNo), reasonNo(reasNo),
        statusNo(statNo), maxResults(maxRes) {}
};

struct FindCallbacksRequest
{
    static FindCallbacksRequestPtr create(
        basar::Int16 const& branchNo, bool const& onlyOwnBranch, basar::Int32 const& customerNo, basar::VarString const& title,
        basar::Int32 const& dateFrom, basar::Int32 const& dateTo, basar::Int16 const& divisionNo, basar::Int16 const& reasonNo,
        basar::Int32 const& maxResults, basar::Int16 const& statusNo);

    FindCallbacksRequest(FindCallbacksParams const& findCallbacksRequestParams);
    
    virtual ~FindCallbacksRequest();

    basar::Int16 BranchNo;
    bool OnlyOwnBranch;
    basar::Int32 CustomerNo;
    basar::VarString Title;
    basar::Int32 DateFrom;
    basar::Int32 DateTo;
    basar::Int16 DivisionNo;
    basar::Int16 ReasonNo;
    basar::Int16 StatusNo;

    basar::Int32 MaxResults;
};

} // end namespace repo
} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPO_FINDCALLBACKSREQUEST_H
