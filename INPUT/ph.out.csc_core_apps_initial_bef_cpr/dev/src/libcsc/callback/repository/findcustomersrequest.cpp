/*
 * findcustomersrequest.cpp
 *
 *  Created on: 19.10.2016
 *  Author: sebastian.barth
 */

#include "findcustomersrequest.h"
#include <boost/make_shared.hpp>

namespace libcsc {
namespace callback {
namespace repo {

FindCustomersRequestPtr FindCustomersRequest::create(
    basar::Int16 const& branchNo, bool const& onlyOwnBranch, bool const& lockedCustomers, basar::Int32 const& customerNo, basar::VarString const& matchCode,
    basar::VarString const& ownerName, basar::VarString const& pharmacyName, basar::VarString const& city, basar::Int32 const& maxResults)
{
    return boost::make_shared<FindCustomersRequest>(branchNo, onlyOwnBranch, lockedCustomers, customerNo, matchCode, ownerName, pharmacyName, city, maxResults);
}

FindCustomersRequest::FindCustomersRequest(
    basar::Int16 const& branchNo, bool const& onlyOwnBranch, bool const& lockedCustomers, basar::Int32 const& customerNo, basar::VarString const& matchCode,
    basar::VarString const& ownerName, basar::VarString const& pharmacyName, basar::VarString const& city, basar::Int32 const& maxResults)
{
    BranchNo = branchNo;
    OnlyOwnBranch = onlyOwnBranch;
    LockedCustomers = lockedCustomers;
    CustomerNo = customerNo;
    MatchCode = matchCode;
    OwnerName = ownerName;
    PharmacyName = pharmacyName;
    City = city;
    MaxResults = maxResults;
}

FindCustomersRequest::~FindCustomersRequest()
{
}

} // end namespace repo
} // end namespace ibt
} // end namespace libcsc
