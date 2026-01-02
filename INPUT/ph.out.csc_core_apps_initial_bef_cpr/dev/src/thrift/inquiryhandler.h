#ifndef GUARD_INQUIRYHANDLER_H
#define GUARD_INQUIRYHANDLER_H

#include <pxordertransmitptr.h>
#include "cscinquiry_types.h"
#include "csclibtothrifthandlerbase.h"
#include <libbasar_definitions.h>

class pxOrderItem;

namespace csc {
namespace service {

class InquiryHandler : public CscLibToThriftHandlerBase
{
public:
    InquiryHandler();
    virtual ~InquiryHandler();

    void processArticleInquiryOpen(
        inquiry::ArticleInquiryResponse& response,
        const inquiry::ArticleInquiryRequest& request);

    void processArticleInquiryPosition(
        inquiry::ArticleInquiryPositionResponse& response,
        const inquiry::ArticleInquiryPositionRequest request);

    void processArticleInquiryClose(
        inquiry::ArticleInquiryResponse& response,
        const inquiry::ArticleInquiryRequest& request);

    std::vector<basar::Int32> findArticleNosByPeriodHR(const inquiry::ArticleInquiryHRRequest& request);

private:
    void setArticleDelivered(pxOrderItem* orderitem, std::string requestedArticleCode, inquiry::ArticleInquiryPositionResponse& response);
};

} // namespace service
} // namespace csc

#endif // GUARD_INQUIRYHANDLER_H
