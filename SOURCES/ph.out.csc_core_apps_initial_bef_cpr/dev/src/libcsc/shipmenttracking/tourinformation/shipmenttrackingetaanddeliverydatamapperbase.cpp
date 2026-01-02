#include "shipmenttrackingetaanddeliverydatamapperbase.h"
#include "shipmenttrackingetaanddeliverydata.h"


namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingEtaAndDeliveryDataMapperBase::ShipmentTrackingEtaAndDeliveryDataMapperBase(ShipmentTrackingEtaAndDeliveryDataPtr shipmentTrackingEtaAndDeliveryData)
    : m_EtaAndDeliveryData(shipmentTrackingEtaAndDeliveryData)
{
}


ShipmentTrackingEtaAndDeliveryDataMapperBase::~ShipmentTrackingEtaAndDeliveryDataMapperBase()
{
}

void ShipmentTrackingEtaAndDeliveryDataMapperBase::setEstimatedTimeOfArrival(const basar::DateTime& estimatedTimeOfArrival)
{
    m_EtaAndDeliveryData->m_EstimatedTimeOfArrival = estimatedTimeOfArrival;
    m_EtaAndDeliveryData->m_EstimatedTimeOfArrival.setClean();
}

void ShipmentTrackingEtaAndDeliveryDataMapperBase::setEstimatedTimeOfArrivalMin(const basar::DateTime& estimatedTimeOfArrivalMin)
{
    m_EtaAndDeliveryData->m_EstimatedTimeOfArrivalMin = estimatedTimeOfArrivalMin;
    m_EtaAndDeliveryData->m_EstimatedTimeOfArrivalMin.setClean();
}

void ShipmentTrackingEtaAndDeliveryDataMapperBase::setEstimatedTimeOfArrivalMax(const basar::DateTime& estimatedTimeOfArrivalMax)
{
    m_EtaAndDeliveryData->m_EstimatedTimeOfArrivalMax = estimatedTimeOfArrivalMax;
    m_EtaAndDeliveryData->m_EstimatedTimeOfArrivalMax.setClean();
}

void ShipmentTrackingEtaAndDeliveryDataMapperBase::setDeliveredAt(const basar::DateTime& deliveredAt)
{
    m_EtaAndDeliveryData->m_DeliveredAt = deliveredAt;
    m_EtaAndDeliveryData->m_DeliveredAt.setClean();
}

void ShipmentTrackingEtaAndDeliveryDataMapperBase::setDelayInfo(const basar::VarString& delayInfo)
{
    m_EtaAndDeliveryData->m_DelayInfo = delayInfo;
    m_EtaAndDeliveryData->m_DelayInfo.setClean();
}

void ShipmentTrackingEtaAndDeliveryDataMapperBase::setDelayInMinutes(const basar::Int32& delayInMinutes)
{
    m_EtaAndDeliveryData->m_DelayInMinutes = delayInMinutes;
    m_EtaAndDeliveryData->m_DelayInMinutes.setClean();
}


} // end namespace shipmenttracking
} // end namespace libcsc

