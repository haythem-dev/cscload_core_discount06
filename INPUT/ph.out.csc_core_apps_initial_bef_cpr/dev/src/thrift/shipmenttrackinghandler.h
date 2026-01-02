#ifndef GUARD_CSC_SERVICE_SHIPMENTTRACKING_H
#define GUARD_CSC_SERVICE_SHIPMENTTRACKING_H

#include "csclibtothrifthandlerbase.h"
#include "shipmenttracking_types.h"
#include <shipmenttracking/shipmenttrackingdatafilter.h>
#include <shipmenttracking/tourinformation/shipmenttrackingtourdata.h>
#include <shipmenttracking/tourinformation/shipmenttrackingetaanddeliverydata.h>
#include <shipmenttracking/tourinformation/shipmenttrackingtourinformation.h>
#include <shipmenttracking/packageinformation/shipmenttrackingpackageinformation.h>
#include <shipmenttracking/packageinformation/shipmenttrackinglinedetail.h>

namespace csc {
namespace service {

class ShipmentTrackingHandler : public CscLibToThriftHandlerBase
{
public:
    ShipmentTrackingHandler();
    virtual ~ShipmentTrackingHandler();

    void getShipmentTracking(
        warehouse::shipmenttracking::ShipmentTrackingResponse& _return,
        const warehouse::shipmenttracking::ShipmentTrackingRequest & request);

private:
    void convertDataFilter(
        libcsc::shipmenttracking::ShipmentTrackingDataFilter& libcscfilter,
        const warehouse::shipmenttracking::ShipmentTrackingDataFilter& thriftFilter
    ) const;

    void convertTourInformationCollection(
        warehouse::shipmenttracking::ShipmentTrackingTourInformationList& thriftList,
        const libcsc::shipmenttracking::ShipmentTrackingTourInformationCollection& libcscColl
    );

    bool convertTourData(
        warehouse::shipmenttracking::ShipmentTrackingTourData& thriftTourData,
        const libcsc::shipmenttracking::ShipmentTrackingTourDataPtr libcscTourData
    );

    void convertEtaAndDeliveryData(
        bool planedTimeIsValid,
        warehouse::shipmenttracking::ShipmentTrackingEtaAndDeliveryData& thriftEtaAndDeliveryData,
        const libcsc::shipmenttracking::ShipmentTrackingEtaAndDeliveryDataPtr libcscEtaAndDeliveryData
    );

    void convertTourPackageInformationCollection(
        warehouse::shipmenttracking::ShipmentTrackingPackageInformationList& thriftList,
        const libcsc::shipmenttracking::ShipmentTrackingPackageInformationCollection& libcscColl,
        int packageInformationPositionNumber
    );

    void convertPackageProperties(
        warehouse::shipmenttracking::ShipmentTrackingPackageProperties& thriftPackageProperties,
        const libcsc::shipmenttracking::ShipmentTrackingPackagePropertiesPtr libcscPackageProperties,
        const basar::VarString& redirectedFromTourId,
        const basar::VarString& redirectedToTourId
    );

    void convertIbtInformation(
        warehouse::shipmenttracking::ShipmentTrackingIbtInformationList& thriftIbtInformationList,
        const libcsc::shipmenttracking::ShipmentTrackingIbtInformationPtr libcscIbtInformation
    );

    void convertTourLineDetailCollection(
        warehouse::shipmenttracking::ShipmentTrackingLineDetailList& thriftList,
        const libcsc::shipmenttracking::ShipmentTrackingLineDetailCollection& libcscColl,
        int lineDetailPositionNumber
    );

    libcsc::shipmenttracking::ShipmentTrackingDataFilter m_Filter;
};

} // namespace service
} // namespace csc

#endif // GUARD_CSC_SERVICE_SHIPMENTTRACKING_H
