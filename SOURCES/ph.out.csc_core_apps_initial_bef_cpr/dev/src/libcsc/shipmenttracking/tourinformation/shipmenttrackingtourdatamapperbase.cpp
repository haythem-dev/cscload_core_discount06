#include "shipmenttrackingtourdatamapperbase.h"
#include "shipmenttrackingtourdata.h"


namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingTourDataMapperBase::ShipmentTrackingTourDataMapperBase(ShipmentTrackingTourDataPtr tourData)
    : m_TourData(tourData)
{
}


ShipmentTrackingTourDataMapperBase::~ShipmentTrackingTourDataMapperBase()
{
}

void ShipmentTrackingTourDataMapperBase::setTourId(const basar::VarString& tourId)
{
    m_TourData->m_TourId = tourId;
    m_TourData->m_TourId.setClean();
}

void ShipmentTrackingTourDataMapperBase::setDeliveryDate(const basar::Int32 deliveryDate)
{
    m_TourData->m_DeliveryDate = deliveryDate;
    m_TourData->m_DeliveryDate.setClean();
}

void ShipmentTrackingTourDataMapperBase::setPlannedTimeOfArrival(const basar::DateTime& plannedTimeOfArrival)
{
    m_TourData->m_PlannedTimeOfArrival = plannedTimeOfArrival;
    m_TourData->m_PlannedTimeOfArrival.setClean();
}


} // end namespace shipmenttracking
} // end namespace libcsc

