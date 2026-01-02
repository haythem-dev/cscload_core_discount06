/*
 * findcustomersrequest.h
 *
 *  Created on: 19.10.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPO_FINDCUSTOMERSREQUEST_H
#define GUARD_LIBCSC_CALLBACK_REPO_FINDCUSTOMERSREQUEST_H

#include <boost/shared_ptr.hpp>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace callback {
namespace repo {

struct FindCustomersRequest;
typedef boost::shared_ptr<FindCustomersRequest> FindCustomersRequestPtr;

struct FindCustomersRequest
{
    static FindCustomersRequestPtr create(
        basar::Int16 const& branchNo, bool const& onlyOwnBranch, bool const& lockedCustomers, basar::Int32 const& customerNo, basar::VarString const& matchCode,
        basar::VarString const& ownerName, basar::VarString const& pharmacyName, basar::VarString const& city, basar::Int32 const& maxResults);

    FindCustomersRequest(
        basar::Int16 const& branchNo, bool const& onlyOwnBranch, bool const& lockedCustomers, basar::Int32 const& customerNo, basar::VarString const& matchCode,
        basar::VarString const& ownerName, basar::VarString const& pharmacyName, basar::VarString const& city, basar::Int32 const& maxResults);

    virtual ~FindCustomersRequest();

    basar::Int16 BranchNo;
    bool OnlyOwnBranch;
    bool LockedCustomers;
    basar::Int32 CustomerNo;
    basar::VarString MatchCode;
    basar::VarString OwnerName;
    basar::VarString PharmacyName;
    basar::VarString City;

    basar::Int32 MaxResults;
};

} // end namespace repo
} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPO_FINDCUSTOMERSREQUEST_H
