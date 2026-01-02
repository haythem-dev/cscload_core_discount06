#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIES_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIES_H

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

#include "shipmenttrackingpackagepropertiesptr.h"

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingPackageProperties
{
    friend class ShipmentTrackingPackagePropertiesMapperBase;
    friend class ShipmentTrackingPackageInformation;

public:
    ShipmentTrackingPackageProperties();
    virtual ~ShipmentTrackingPackageProperties();

    // -----------------
    // Tote common data:
    const basar::Int32&         getPackageId()          const { return m_PackageId; }                   // Thrift:  1
    const basar::VarString&     getPackageType()        const { return m_PackageType; }                 // Thrift: 15
    const basar::Int32&         getCscOrderNo()         const { return m_CscOrderNo; }                  // Thrift:  2
    const basar::Int32&         getPharmosOrderNo()     const { return m_PharmosOrderNo; }              // Thrift:  3
    const basar::Int32&         getDeliveryAdviceNo()   const { return m_DeliveryAdviceNo; }            // Thrift:  4
    const basar::Int32&         getPickingOrderNo()     const { return m_PickingOrderNo; }              // Thrift:  5
    const basar::Int16&         getPickingOrderPageNo() const { return m_PickingOrderPageNo; }          // Thrift:  6
    const basar::VarString&     getTrackingBarcode()    const { return m_TrackingBarcode; }             // Thrift: 10

    //! \brief The date part is used also as PickingDate for further data joins
    const basar::DateTime&      getOrderClosedAt()      const { return m_OrderClosedAt; }               // Thrift:  7, 8 - The date part is used also as PickingDate for further data joins
    const basar::DateTime&      getPickingDoneAt()      const { return m_PickingDoneAt; }               // Thrift:  9

    // -----------------
    // Common Tote status data: (the redirection info is in the specific container part: ShipmentTrackingPackageInformation)
    bool                        isToteContentChanged()      const { return m_IsContentChanged || (m_HasWarehouseData && m_TotalExpectedDeliveryQuantity > (m_TotalConfirmedDeliveryQuantity + m_TotalRelatedConfirmedDeliveryQuantity)); } // Thrift: 11
    const basar::VarString&     getRedirectedFromTourId()   const { return m_RedirectedFromTourId; }    // DKTSV.tsv_vsw_rtour

    //! \brief == PickingDoneAt but from the other content changed (DKTSV.tsv_status = 1) line ! Valid only if this tote content was changed
    const basar::DateTime&      getContentChangedAt()       const { return m_ContentChangedAt; }        // Thrift: 11 & 9 => 11 (DKTSV.tsv_status = 1) is an indicator / trigger, wherease 9 (DKTSV.insertdatetime) is content

    //! \brief == PickingDoneAt but from the other redirected (DKTSV.tsv_vsw_rtour != '') line ! Valid only if this tote was redirected
    const basar::DateTime&      getTourRedirectedAt()       const { return m_TourRedirectedAt; }        // Thrift: 12, 13 D & E - part.

    //! \brief == PickingDoneAt but from the other redirected (DKTSV.tsv_status = 9) line ! Valid only if this tote was deleted
    const basar::DateTime&      getToteDeletedAt()          const { return m_ToteDeletedAt; }           // Thrift: 14

    // -----------------
    // Derived Tote Status props:

    bool                        isContainer()               const { return m_IsContainer; }
    bool                        isNarcotic()                const { return m_IsNarcotic; }
    bool                        isAdditionalTote()          const { return m_IsAdditionalTote; }

    bool                        isOrderClosed()             const { return m_IsOrderClosed; }

    bool                        isContentChanged()          const { return m_IsContentChanged; }
    bool                        isTourRedirected()          const { return m_IsTourRedirected; }
    bool                        isDeleted()                 const { return m_IsDeleted; }

    bool                        hasWarehouseData()          const { return m_HasWarehouseData; }

    int                         getTotalExpectedDeliveryQuantity()  const { return m_TotalExpectedDeliveryQuantity; }
    int                         getTotalConfirmedDeliveryQuantity() const { return m_TotalConfirmedDeliveryQuantity; }

    //! \brief Necessary because of: Order-Position Split to more then 1 Tote
    int                         getTotalRelatedConfirmedDeliveryQuantity() const { return m_TotalRelatedConfirmedDeliveryQuantity; }

    bool isSamePackageAs(const ShipmentTrackingPackageProperties* other) const;
    bool isSamePackageAs(const ShipmentTrackingPackagePropertiesPtr& other) const { return isSamePackageAs(other.get()); }

    //! \brief CscOrderNo + PackageType -> for logging
    std::string getOutboundMapKey() const;

    //! \brief Barcode + PackageId -> for identifying from inside of ShipmentTrackingRepositoryBuilder
    std::string getWarehouseMapKey() const;

    friend std::ostream& ::operator<<(std::ostream& os, const ShipmentTrackingPackageProperties& shipmentTrackingPackageProperties);

private:
    // -----------------
    // Tote common data:
    libcsc::Int32           m_PackageId;                // Thrift:  1
    libcsc::VarString       m_PackageType;              // Thrift: 15
    libcsc::Int32           m_CscOrderNo;               // Thrift:  2
    libcsc::Int32           m_PharmosOrderNo;           // Thrift:  3
    libcsc::Int32           m_DeliveryAdviceNo;         // Thrift:  4
    libcsc::Int32           m_PickingOrderNo;           // Thrift:  5
    libcsc::Int16           m_PickingOrderPageNo;       // Thrift:  6
    libcsc::VarString       m_TrackingBarcode;          // Thrift: 10
    libcsc::DateTime        m_OrderClosedAt;            // Thrift:  7, 8 - The date part is used also as PickingDate for further data joins
    libcsc::DateTime        m_PickingDoneAt;            // Thrift:  9

    // -----------------
    // Common Tote status data: (the redirection info is in the specific container part: ShipmentTrackingPackageInformation)
    libcsc::VarString       m_RedirectedFromTourId;

    //! \brief == PickingDoneAt but from the other content changed (DKTSV.tsv_status = 1) line ! Valid only if this tote content was changed
    basar::DateTime         m_ContentChangedAt;         // Thrift: 11 & 9 => 11 (DKTSV.tsv_status = 1) is an indicator / trigger, wherease 9 (DKTSV.insertdatetime) is content
    
    //! \brief == PickingDoneAt but from the other redirected (DKTSV.tsv_vsw_rtour != '') line ! Valid only if this tote was redirected
    basar::DateTime         m_TourRedirectedAt;         // Thrift: 12, 13 D & E - part.

    //! \brief == PickingDoneAt but from the other redirected (DKTSV.tsv_status = 9) line ! Valid only if this tote was deleted
    libcsc::DateTime        m_ToteDeletedAt;            // Thrift: 14

    // -----------------
    // Derived Tote Status props:
    bool                    m_IsContainer;
    bool                    m_IsNarcotic;
    bool                    m_IsAdditionalTote;

    bool                    m_IsOrderClosed;

    bool                    m_IsContentChanged;
    bool                    m_IsTourRedirected;
    bool                    m_IsDeleted;

    bool                    m_HasWarehouseData;

    int                     m_TotalExpectedDeliveryQuantity;
    int                     m_TotalConfirmedDeliveryQuantity;

    //! \brief Necessary because of: Order-Position Split to more then 1 Tote
    int                     m_TotalRelatedConfirmedDeliveryQuantity;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEPROPERTIES_H
