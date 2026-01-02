#include "shipmenttrackingdatafilter.h"
#include <ostream>


std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingDataFilter& shipmentTrackingDataFilter)
{
    os << "ST-DataFilter: {"
        << "ToteDeliveryDate: " << shipmentTrackingDataFilter.ToteDeliveryDate
        << ", PickingDate: " << shipmentTrackingDataFilter.PickingDate
        << ", CurrentDate: " << shipmentTrackingDataFilter.CurrentDate
        << ", DateFilterMode: " << shipmentTrackingDataFilter.getDateFilterMode()
        << ", DetailsDesired: " << shipmentTrackingDataFilter.DetailsDesired
        << ", SpecificTourID: " << shipmentTrackingDataFilter.SpecificTourID
        << ", SendPharmosOrderNumbers: " << shipmentTrackingDataFilter.SendPharmosOrderNumbers
        << ", SendPickingOrderNumbers: " << shipmentTrackingDataFilter.SendPickingOrderNumbers
        << ", SendPackagePosNos: " << shipmentTrackingDataFilter.SendPackagePosNos
        << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingDataFilter* shipmentTrackingDataFilter)
{
    if (shipmentTrackingDataFilter != NULL)
    {
        os << *shipmentTrackingDataFilter;
    }
    else
    {
        os << "ST-DataFilter: <null>";
    }
    return os;
}
