/*
 * findcallbacksrequest.cpp
 *
 *  Created on: 25.10.2016
 *  Author: sebastian.barth
 */

#include "findcallbacksrequest.h"
#include <boost/make_shared.hpp>

namespace libcsc {
namespace callback {
namespace repo {

FindCallbacksRequestPtr FindCallbacksRequest::create(
        basar::Int16 const& branchNo, bool const& onlyOwnBranch, basar::Int32 const& customerNo, basar::VarString const& title,
        basar::Int32 const& dateFrom, basar::Int32 const& dateTo, basar::Int16 const& divisionNo, basar::Int16 const& reasonNo,
        basar::Int32 const& maxResults, basar::Int16 const& statusNo)
{
    // In compiler C98 make_shared does not accept more than 9 parameters. So we have used struct findCallbacksParams as an intermediate to pass parameters.
    FindCallbacksParams findCallbacksParams(branchNo, onlyOwnBranch, customerNo, title, dateFrom, dateTo, divisionNo, reasonNo, maxResults, statusNo);
    return boost::make_shared<FindCallbacksRequest>(findCallbacksParams);
}

FindCallbacksRequest::FindCallbacksRequest(FindCallbacksParams const& findCallbacksRequestParams)
{
    BranchNo = findCallbacksRequestParams.branchNo;
    OnlyOwnBranch = findCallbacksRequestParams.onlyOwnBranch;
    CustomerNo = findCallbacksRequestParams.customerNo;
    Title = findCallbacksRequestParams.title;
    DateFrom = findCallbacksRequestParams.dateFrom;
    DateTo = findCallbacksRequestParams.dateTo;
    DivisionNo = findCallbacksRequestParams.divisionNo;
    ReasonNo = findCallbacksRequestParams.reasonNo;
    MaxResults = findCallbacksRequestParams.maxResults;
    StatusNo = findCallbacksRequestParams.statusNo;
}

FindCallbacksRequest::~FindCallbacksRequest()
{
}

} // end namespace repo
} // end namespace ibt
} // end namespace libcsc
