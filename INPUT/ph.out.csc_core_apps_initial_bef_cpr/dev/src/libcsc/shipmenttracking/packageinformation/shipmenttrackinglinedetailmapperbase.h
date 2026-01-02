#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAILMAPPER_BASE_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAILMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "shipmenttrackinglinedetail.h"
#include "shipmenttrackingpackageinformationsqlmapperptr.h"


namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingLineDetailMapperBase
{
public:
    ShipmentTrackingLineDetailMapperBase(ShipmentTrackingLineDetailPtr lineDetail);

    const ShipmentTrackingLineDetailPtr&     getLineDetail()    const { return m_LineDetail; }

protected:
    virtual ~ShipmentTrackingLineDetailMapperBase();

    void switchToOtherLineBatch(ShipmentTrackingLineDetailPtr lineDetail) { m_LineDetail = lineDetail; }

    void setOrderPosNo(const basar::Int32 orderPosNo);
    void setIbtOrderPosNo(const basar::Int32 ibtOrderPosNo);
    void setTotePosNo(const basar::Int32 totePosNo);
    void setExpectedDeliveryQuantity(const basar::Int32 expectedDeliveryQuantity);
    void setConfirmedDeliveryQuantity(const basar::Int32 confirmedDeliveryQuantity);
    void setArticleNr(const basar::Int32 articleNr);
    void setArticleCode(const basar::VarString& articleCode);
    void setArticleName(const basar::VarString& articleName);
    void setIsNarcotic(const bool isNarcotic);
    void setBatch(const basar::VarString& batch);
    
    void setHasWarehouseData(bool hasWarehouseData);

    void setOwnerPackageInfo(ShipmentTrackingPackageInformationPtr ownerPackageInfo);

private:
    ShipmentTrackingLineDetailPtr m_LineDetail;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAILMAPPER_BASE_H
