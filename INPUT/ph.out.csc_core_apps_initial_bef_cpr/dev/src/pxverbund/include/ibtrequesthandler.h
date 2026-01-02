#ifndef IBTREQUESTHANDLER_H
#define IBTREQUESTHANDLER_H

#include <libbasar_definitions.h>

class pxSession;
class pxOrder;
class pxOrderItem;
class pxOrderItemList;


class IbtRequestHandler
{
public:
    IbtRequestHandler();
    virtual ~IbtRequestHandler();

    virtual void bookIbt(
        basar::Int16 const ibtBranchNo, pxOrderItem* item,
        basar::Int16 const nLevelIbtTypeId, basar::Long32 const ibtCustomerNo, basar::VarString const& custOrderRef, basar::Long32 const quantity);

    virtual void unbookIbt(basar::Int16 const ibtBranchNo, pxOrderItem* item);

    virtual void readAllIbtRequests(pxOrder* order);
    virtual void closeAllIbtRequests(pxOrder* order);

    virtual void readIbtRequest(pxOrder* order, pxOrderItem* item); // Krücke für corpha!

    virtual void setArticleCodeValues(pxOrderItem* item, basar::Int16 const articleCodeType, basar::VarString const& articleCode);
};

#endif // IBTREQUESTHANDLER_H
