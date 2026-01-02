#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATAMAPPER_BASE_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATAMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "shipmenttrackingtourdataptr.h"


namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingTourDataMapperBase
{
public:
    ShipmentTrackingTourDataMapperBase(ShipmentTrackingTourDataPtr tourData);

    const ShipmentTrackingTourDataPtr&     getTourData()    const { return m_TourData; }

protected:
    virtual ~ShipmentTrackingTourDataMapperBase();

    void setTourId(const basar::VarString& tourId);
    void setDeliveryDate(const basar::Int32 deliveryDate);
    void setPlannedTimeOfArrival(const basar::DateTime& plannedTimeOfArrival);

protected:
    ShipmentTrackingTourDataPtr m_TourData;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATAMAPPER_BASE_H
