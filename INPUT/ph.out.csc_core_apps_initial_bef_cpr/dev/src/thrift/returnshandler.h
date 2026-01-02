#ifndef GUARD_RETURNSHANDLER_H
#define GUARD_RETURNSHANDLER_H

#include <pxordertransmitptr.h>
#include <boost/shared_ptr.hpp>
#include "returns_types.h"
#include "csclibtothrifthandlerbase.h"
#include <libbasarcmnutil_bstring.h>
#include <returns/returnannouncement/returnannouncementptr.h>
#include <returns/returnannouncement/returnannouncementhead/returnannouncementheadptr.h>
#include <returns/returnannouncement/returnannouncementpos/returnannouncementposptr.h>

namespace csc {
namespace service {

class ReturnsHandler : public CscLibToThriftHandlerBase
{
public:
	ReturnsHandler();
	virtual ~ReturnsHandler();

	void processReturnsRequest(
		::csc::returns::ReturnsResponse& _return,
		const ::csc::returns::ReturnsRequest& request);

private:
	void fillReturnStructure(
		::csc::returns::ReturnsResponse& _return,
		libcsc::returns::ReturnAnnouncementPtr returnAnnouncement);
	void fillReturnsResponseGroup(
		csc::returns::ReturnsResponseGroup& group,
		libcsc::returns::ReturnAnnouncementHeadPtr head,
		libcsc::returns::ReturnAnnouncementPtr returnAnnouncement);
	csc::order::ArticleInformation getArticleDetails(const basar::Int16 branchNo, const libcsc::returns::ReturnAnnouncementPosPtr pos);

	libcsc::returns::ReturnAnnouncementPtr getReturnAnnouncement(const csc::returns::ReturnsRequest& request);
	libcsc::returns::ReturnAnnouncementPosPtr getReturnAnnouncementPosition(const csc::returns::ReturnsRequestPosition& pos);

	basar::VarString getReturnReasonStringByEnum(const csc::types::ReturnReasonEnum::type r) const;
	csc::types::ReturnReasonEnum::type getReturnReasonEnumByString(const basar::VarString& r) const;
	csc::types::ReturnAcceptanceCheckResultEnum::type getCheckResultEnum(const basar::VarString& accCheckResult) const;
	bool containsWrongPickedItem(const csc::returns::ReturnsRequest& request) const;
};

} // namespace service
} // namespace csc

#endif // GUARD_RETURNSHANDLER_H
