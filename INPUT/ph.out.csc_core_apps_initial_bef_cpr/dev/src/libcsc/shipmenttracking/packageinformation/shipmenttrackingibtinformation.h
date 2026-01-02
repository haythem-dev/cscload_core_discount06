#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATION_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATION_H

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

#include "shipmenttrackingibtinformationptr.h"
#include "shipmenttrackingpackageproperties.h"
#include "shipmenttracking/tourinformation/shipmenttrackingtourdata.h"


namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingIbtInformation
{
    friend class ShipmentTrackingIbtInformationMapperBase;

public:
    ShipmentTrackingIbtInformation();
    virtual ~ShipmentTrackingIbtInformation();

    const basar::Int16&     getBranchNo()   const { return m_BranchNo; }
    const basar::Int32&     getCustomerNo() const { return m_CustomerNo; }

    const ShipmentTrackingPackagePropertiesPtr getPackageProperties()   const { return m_PackagePropertiesPtr; }
    const ShipmentTrackingTourDataPtr          getTourData()            const { return m_TourData; }
    
    /*! \brief Redirected TO Tour Information, if this object represents the source of the Tour Redirection, i.e the tour promissed to customer during CSC ordering == m_TourData.
               This object (i.e. instance of ShipmentTrackingPackageInformation) is a "container", which is duplicated for a tour redirection.
               Both containers share the Properties, Lines and IBT Info and differ only in the Redirected FROM / TO properties! */
    const ShipmentTrackingTourDataPtr getRedirectedToTourData()         const { return m_RedirectedToTourData; }

    
    //NOTE: IBT EtaAndDeliveryData is neither needed, nor provided yet by any system, but possible in future:
    //const ShipmentTrackingEtaAndDeliveryDataPtr getEtaAndDeliveryData() const { return m_EtaAndDeliveryData; }

    friend std::ostream& ::operator<<(std::ostream& os, const ShipmentTrackingIbtInformation& shipmentTrackingIbtInformation);

private:
    // Fields with DB values:
    libcsc::Int16           m_BranchNo;
    libcsc::Int32           m_CustomerNo;

    ShipmentTrackingPackagePropertiesPtr    m_PackagePropertiesPtr;
    ShipmentTrackingTourDataPtr             m_TourData;


    /*! \brief Redirected TO Tour Information, if this object represents the source of the Tour Redirection, i.e the tour promissed to customer during CSC ordering == m_TourData.
               This object (i.e. instance of ShipmentTrackingPackageInformation) is a "container", which is duplicated for a tour redirection.
               Both containers share the Properties, Lines and IBT Info and differ only in the Redirected FROM / TO properties! */
    ShipmentTrackingTourDataPtr             m_RedirectedToTourData;

    //NOTE: IBT EtaAndDeliveryData is neither needed, nor provided yet by any system, but possible in future:
    //ShipmentTrackingEtaAndDeliveryDataPtr   m_EtaAndDeliveryData;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATION_H
