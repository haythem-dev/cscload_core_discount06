#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATA_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATA_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/datetime.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>

#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_datetime.h>
#include <libbasar_definitions.h>
#include <iostream>

#include "shipmenttrackingetaanddeliverydataptr.h"

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingEtaAndDeliveryData
{
    friend class ShipmentTrackingEtaAndDeliveryDataMapperBase;

public:
    ShipmentTrackingEtaAndDeliveryData();
    virtual ~ShipmentTrackingEtaAndDeliveryData();

    // ETA Getters:
    const basar::DateTime&     getEstimatedTimeOfArrival() const { return m_EstimatedTimeOfArrival; }
    const basar::DateTime&     getEstimatedTimeOfArrivalMin() const { return m_EstimatedTimeOfArrivalMin; }
    const basar::DateTime&     getEstimatedTimeOfArrivalMax() const { return m_EstimatedTimeOfArrivalMax; }

    // DeliveredAt Getter:
    const basar::DateTime&     getDeliveredAt()               const { return m_DeliveredAt; }

    // Getters of derived values:
    const basar::VarString&    getDelayInfo() const { return m_DelayInfo; }
    const basar::Int32&        getDelayInMinutes() const { return m_DelayInMinutes; }


    friend std::ostream& ::operator<<(std::ostream& os, const ShipmentTrackingEtaAndDeliveryData& shipmentTrackingEtaAndDeliveryData);

private:
    // ETA Fields:
    libcsc::DateTime             m_EstimatedTimeOfArrival;
    libcsc::DateTime             m_EstimatedTimeOfArrivalMin;
    libcsc::DateTime             m_EstimatedTimeOfArrivalMax;

    // DeliveredAt Field:
    libcsc::DateTime             m_DeliveredAt;

    // Fields with values derived from other values:
    libcsc::VarString            m_DelayInfo;
    libcsc::Int32                m_DelayInMinutes;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATA_H
