#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIESMAPPER_BASE_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIESMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "shipmenttrackingpackagepropertiesptr.h"


namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingPackagePropertiesMapperBase
{
    friend class ShipmentTrackingPackageInformationSQLMapper;

public:
    ShipmentTrackingPackagePropertiesMapperBase(ShipmentTrackingPackagePropertiesPtr shipmentTrackingPackageProperties);

    const ShipmentTrackingPackagePropertiesPtr&     getPackageProperties()    const { return m_PackageProperties; }

protected:
    virtual ~ShipmentTrackingPackagePropertiesMapperBase();

    void setPackageId(const basar::Int32 packageId);                                // Thrift:  1
    void setPackageType(const basar::VarString& packageType);                       // Thrift: 15
    void setCscOrderNo(const basar::Int32 cscOrderNo);                              // Thrift:  2
    void setPharmosOrderNo(const basar::Int32 pharmosOrderNo);                      // Thrift:  3
    void setDeliveryAdviceNo(const basar::Int32 deliveryAdviceNo);                  // Thrift:  4
    void setPickingOrderNo(const basar::Int32 pickingOrderNo);                      // Thrift:  5
    void setPickingOrderPageNo(const basar::Int16 pickingOrderPageNo);              // Thrift:  6
    void setTrackingBarcode(const basar::VarString& trackingBarcode);               // Thrift: 10
    void setOrderClosedAt(const basar::DateTime& orderClosedAt);                    // Thrift:  7, 8 - The date part is used also as PickingDate for further data joins
    void setPickingDoneAt(const basar::DateTime& pickingDoneAt);                    // Thrift:  9

    void setRedirectedFromTourId(const basar::VarString& redirectedFromTourId);     // DKTSV.tsv_vsw_rtour
    void setContentChangedAt(const basar::DateTime& contentChangedAt);              // Thrift: 11 & 9 => 11 (DKTSV.tsv_status = 1) is an indicator / trigger, wherease 9 (DKTSV.insertdatetime) is content
    void setTourRedirectedAt(const basar::DateTime& tourRedirectedAt);              // Thrift: 12, 13 D & E - part.
    void setToteDeletedAt(const basar::DateTime& toteDeletedAt);                    // Thrift: 14

    void setIsNarcotic(const bool isNarcotic);
    void setIsContainer(const bool isContainer);
    void setIsAdditionalTote(const bool isAdditionalTote);
    void setHasWarehouseData(bool hasWarehouseData);
    void addTotalExpectedDeliveryQuantity(const basar::Int32 expectedDeliveryQuantity);
    void addTotalConfirmedDeliveryQuantity(const basar::Int32 confirmedDeliveryQuantity);
    void addTotalRelatedConfirmedDeliveryQuantity(const basar::Int32 confirmedDeliveryQuantity);

private:
    ShipmentTrackingPackagePropertiesPtr m_PackageProperties;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIESMAPPER_BASE_H
