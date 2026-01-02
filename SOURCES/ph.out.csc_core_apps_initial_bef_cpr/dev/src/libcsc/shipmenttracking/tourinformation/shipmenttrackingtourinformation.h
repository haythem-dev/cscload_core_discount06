#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATION_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATION_H

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

#include "shipmenttrackingtourinformationptr.h"
#include "shipmenttrackingtourdata.h"
#include "shipmenttrackingetaanddeliverydata.h"
#include "shipmenttracking/packageinformation/shipmenttrackingpackageinformation.h"

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingTourInformation
{
    friend class ShipmentTrackingTourInformationMapperBase;

public:
    ShipmentTrackingTourInformation();
    virtual ~ShipmentTrackingTourInformation();

    // Getters of DB values:
    const ShipmentTrackingTourDataPtr           getTourData() const { return m_TourData; }
    const ShipmentTrackingEtaAndDeliveryDataPtr getEtaAndDeliveryData() const { return m_EtaAndDeliveryData; }

    const ShipmentTrackingPackageInformationCollectionPtr& getPackageInformationCollection() const { return m_PackageInformations; }

    bool isSameTourAs(const ShipmentTrackingTourInformation* other) const { return getTourData()->isSameTourAs(other != NULL ? other->getTourData().get() : NULL); }
    bool isSameTourAs(const ShipmentTrackingTourInformationPtr& other) const { return isSameTourAs(other.get()); }

    std::string getMapKey() const { return m_TourData->getMapKey(); }

    //! \brief Collect PickingDates and Barcodes valid for this tour:
    void getValidPickingDateAndBarcodeList(std::list<basar::Int32>& pickingDateList, std::list<basar::VarString>& trackingBarcodeList);

    friend std::ostream& ::operator<<(std::ostream& os, const ShipmentTrackingTourInformation& shipmentTrackingTourInformation);

private:

    ShipmentTrackingTourDataPtr                     m_TourData;
    ShipmentTrackingEtaAndDeliveryDataPtr           m_EtaAndDeliveryData;

    ShipmentTrackingPackageInformationCollectionPtr m_PackageInformations;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATION_H
