#ifndef GUARD_CSC_SERVICE_INQUIRYBULKHANDLER_H
#define GUARD_CSC_SERVICE_INQUIRYBULKHANDLER_H

#include <pxordertransmitptr.h>
#include "cscinquiry_types.h"
#include "csclibtothrifthandlerbase.h"

namespace csc {
namespace service {

class InquiryBulkHandler : public CscLibToThriftHandlerBase
{
public:
	InquiryBulkHandler();
	virtual ~InquiryBulkHandler();

	void processArticleAvailabilityBulk(
		csc::inquiry::ArticleAvailabilityBulkResponse& _return,
		const csc::inquiry::ArticleAvailabilityBulkRequest& request);

	void processArticleAvailabilityBulkRange(
		csc::inquiry::ArticleAvailabilityBulkRangeResponse& _return,
		const csc::inquiry::ArticleAvailabilityBulkRangeRequest& request);

	void processArticleStockBulk(
		csc::inquiry::ArticleStockBulkResponse& _return,
		const csc::inquiry::ArticleStockBulkRequest& request);

	void processArticleStockDetails(
		::csc::inquiry::ArticleStockDetailsResponse& _return,
		const  ::csc::inquiry::ArticleStockDetailsRequest& request);

private:
	void processArticleStockBulkRange(
		csc::inquiry::ArticleStockBulkResponse& _return,
		const csc::inquiry::ArticleStockBulkRequest& request);

};

} // namespace service
} // namespace csc

#endif // GUARD_CSC_SERVICE_INQUIRYBULKHANDLER_H
