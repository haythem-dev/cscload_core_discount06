#ifndef GUARD_ORDERHANDLER_H
#define GUARD_ORDERHANDLER_H

#include <pxordertransmitptr.h>
#include "cscinquiry_types.h"
#include "csclibtothrifthandlerbase.h"

class pxOrderItem;

namespace csc {
namespace service {

class OrderHandler : public CscLibToThriftHandlerBase
{
public:
    OrderHandler();
    virtual ~OrderHandler();

    //void processPlaceNewOrder(
    //  order::PlaceOrderResponse& _return,
    //  const order::PlaceOrderRequest& request);

    void processOrderOpen(
        csc::order::OpenOrderResponse& _return,
        const csc::order::OpenOrderRequest& request);

    //void processOrderPosition(
    //  csc::order::OrderPositionResponse& response,
    //  const csc::order::OrderPositionRequest& request);

    void processOrderTextPosition(
        csc::order::OrderPositionResponse& response,
        const csc::order::OrderPositionRequest& request);

    void processOrderDispoPosition(
        csc::order::OrderPositionResponse& response,
        const csc::order::OrderPositionRequest& request);

    void processOrderProductPosition(
        csc::order::OrderPositionResponse& response,
        const csc::order::OrderPositionRequest& request);

    void processOrderClose(
        csc::order::PlaceOrderResponse& _return,
        const csc::order::CloseOrderRequest& request);

    void isArticleExportPermitted(
        csc::order::ArticleExportPermittedResponse& _return,
        const  csc::order::ArticleExportPermittedRequest& request);

private:
    void updateProforma(csc::order::OrderPositionResponseList& response);
    void setItemResponseValues(csc::order::OrderPositionResponse& response, pxOrderItem* item);
};

} // namespace service
} // namespace csc

#endif // GUARD_ORDERHANDLER_H
