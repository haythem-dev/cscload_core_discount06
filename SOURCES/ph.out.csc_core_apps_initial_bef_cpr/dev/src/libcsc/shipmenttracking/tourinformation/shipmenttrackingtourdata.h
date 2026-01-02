#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATA_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATA_H

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

#include "shipmenttrackingtourdataptr.h"

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingTourData
{
    friend class ShipmentTrackingTourDataMapperBase;

public:
    ShipmentTrackingTourData();
    virtual ~ShipmentTrackingTourData();

    //! \brief The final Tour, which could have been changed for some totes in Warehouse during picking via Tote state '8' (Wannenstatus: DKTSV.TSV-W-STATUS)
    const basar::VarString&     getTourId() const               { return m_TourId; }
    const basar::Int32&         getDeliveryDate() const         { return m_DeliveryDate; }

    //! \brief The final Arrival, which could have been changed for some totes in Warehouse during picking via Tote state '8' (Wannenstatus: DKTSV.TSV-W-STATUS)
    const basar::DateTime&      getPlannedTimeOfArrival() const { return m_PlannedTimeOfArrival; }

    bool isSameTourAs(const ShipmentTrackingTourData* other) const;
    bool isSameTourAs(const ShipmentTrackingTourDataPtr& other) const { return isSameTourAs(other.get()); }

    std::string getMapKey() const;

    friend std::ostream& ::operator<<(std::ostream& os, const ShipmentTrackingTourData& shipmentTrackingTourData);

private:
    //! \brief The final Tour, which could have been changed for some totes in Warehouse during picking via Tote state '8' (Wannenstatus: DKTSV.TSV-W-STATUS)
    libcsc::VarString           m_TourId;
    libcsc::Int32               m_DeliveryDate;

    //! \brief The final Arrival, which could have been changed for some totes in Warehouse during picking via Tote state '8' (Wannenstatus: DKTSV.TSV-W-STATUS)
    libcsc::DateTime            m_PlannedTimeOfArrival;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATA_H
