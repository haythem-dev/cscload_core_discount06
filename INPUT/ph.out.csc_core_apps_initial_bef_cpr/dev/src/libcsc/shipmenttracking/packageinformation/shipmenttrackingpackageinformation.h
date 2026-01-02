#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATION_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATION_H

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

#include "shipmenttrackingpackageinformationptr.h"
#include "shipmenttrackingpackageproperties.h"
#include "shipmenttrackingibtinformation.h"
#include "shipmenttrackinglinedetail.h"
#include "shipmenttracking/tourinformation/shipmenttrackingtourdataptr.h"

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingPackageInformation
{
    friend class ShipmentTrackingPackageInformationMapperBase;

public:
    ShipmentTrackingPackageInformation(ShipmentTrackingTourDataPtr tourData);
    virtual ~ShipmentTrackingPackageInformation();

    const ShipmentTrackingPackagePropertiesPtr      getPackageProperties()      const { return m_PackageProperties; }
    const ShipmentTrackingIbtInformationPtr         getIbtInformation()         const { return m_IbtInformation; }
    const ShipmentTrackingLineDetailCollectionPtr   getLineDetailCollection()   const { return m_LineDetails; }

    // -----------------
    // Tote Redirecting data: (the common redirection info is in the: ShipmentTrackingPackageProperties; Here is stored just the redirection info of the specific "container" part. The container is: ShipmentTrackingPackageInformation)

    //! \brief Original CSC planned Tour Information or Redirected TO Tour Information. See description of m_RedirectedFromTourData and m_RedirectedToTourData.
    const ShipmentTrackingTourDataPtr   getTourData()                           const { return m_TourData; }

    /*! \brief Redirected FROM Tour Information, if this object represents the target of the Tour Redirection, i.e.  m_TourData == the real delivery / redirected tour.
               This object (i.e. instance of ShipmentTrackingPackageInformation) is a "container", which is duplicated for a tour redirection.
               Both containers share the Properties, Lines and IBT Info and differ only in the Redirected FROM / TO properties! */
    const ShipmentTrackingTourDataPtr   getRedirectedFromTourData()             const { return m_RedirectedFromTourData; }

    /*! \brief Redirected TO Tour Information, if this object represents the source of the Tour Redirection, i.e the tour promissed to customer during CSC ordering == m_TourData.
               This object (i.e. instance of ShipmentTrackingPackageInformation) is a "container", which is duplicated for a tour redirection.
               Both containers share the Properties, Lines and IBT Info and differ only in the Redirected FROM / TO properties! */
    const ShipmentTrackingTourDataPtr   getRedirectedToTourData()               const { return m_RedirectedToTourData; }

    bool isSamePackageAs(const ShipmentTrackingPackageInformation* other)       const { return getPackageProperties()->isSamePackageAs(other != NULL ? other->getPackageProperties().get() : NULL); }
    bool isSamePackageAs(const ShipmentTrackingPackageInformationPtr& other)    const { return isSamePackageAs(other.get()); }

    //! \brief CscOrderNo + PackageType -> for logging
    std::string getOutboundMapKey()                                             const { return getPackageProperties()->getOutboundMapKey(); }

    //! \brief Barcode + PackageId -> for identifying from inside of ShipmentTrackingRepositoryBuilder
    std::string getWarehouseMapKey()                                            const { return getPackageProperties()->getWarehouseMapKey(); }

    friend std::ostream& ::operator<<(std::ostream& os, const ShipmentTrackingPackageInformation& shipmentTrackingPackageInformation);

private:
    ShipmentTrackingPackagePropertiesPtr        m_PackageProperties;
    ShipmentTrackingIbtInformationPtr           m_IbtInformation;
    ShipmentTrackingLineDetailCollectionPtr     m_LineDetails;

    // -----------------
    // Tote Redirecting data: (the common redirection info is in the: ShipmentTrackingPackageProperties; Here is stored just the redirection info of the specific "container" part. The container is: ShipmentTrackingPackageInformation)

    //! \brief Original CSC planned Tour Information or Redirected TO Tour Information. See description of m_RedirectedFromTourData and m_RedirectedToTourData.
    ShipmentTrackingTourDataPtr          m_TourData;
    
    /*! \brief Redirected FROM Tour Information, if this object represents the target of the Tour Redirection, i.e.  m_TourData == the real delivery / redirected tour.
               This object (i.e. instance of ShipmentTrackingPackageInformation) is a "container", which is duplicated for a tour redirection.
               Both containers share the Properties, Lines and IBT Info and differ only in the Redirected FROM / TO properties! */
    ShipmentTrackingTourDataPtr          m_RedirectedFromTourData;

    /*! \brief Redirected TO Tour Information, if this object represents the source of the Tour Redirection, i.e the tour promissed to customer during CSC ordering == m_TourData.
               This object (i.e. instance of ShipmentTrackingPackageInformation) is a "container", which is duplicated for a tour redirection.
               Both containers share the Properties, Lines and IBT Info and differ only in the Redirected FROM / TO properties! */
    ShipmentTrackingTourDataPtr          m_RedirectedToTourData;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATION_H
