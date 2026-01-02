#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATIONMAPPER_BASE_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATIONMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "shipmenttrackingibtinformationptr.h"
#include "shipmenttracking/tourinformation/shipmenttrackingtourdataptr.h"


namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingIbtInformationMapperBase
{
public:
    ShipmentTrackingIbtInformationMapperBase(ShipmentTrackingIbtInformationPtr shipmentTrackingIbtInformation);

    const ShipmentTrackingIbtInformationPtr&     getIbtInformation()    const { return m_IbtInformation; }

protected:
    virtual ~ShipmentTrackingIbtInformationMapperBase();

    void setBranchNo(const basar::Int16 branchNo);
    void setCustomerNo(const basar::Int32 customerNo);

    ShipmentTrackingTourDataPtr getIbtInfoTourDataForWrite() const;
    void setTourData(ShipmentTrackingTourDataPtr tourData);
    void setRedirectedToTourData(const ShipmentTrackingTourDataPtr redirectedToTourData);

protected:
    ShipmentTrackingIbtInformationPtr m_IbtInformation;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATIONMAPPER_BASE_H
