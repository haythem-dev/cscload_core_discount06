#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATAMAPPER_BASE_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATAMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "shipmenttrackingetaanddeliverydataptr.h"
#include "shipmenttracking/configuration/etadelayevaluation.h"
#include "shipmenttracking/configuration/etadelaypresentation.h"


namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingEtaAndDeliveryDataMapperBase
{
public:
    ShipmentTrackingEtaAndDeliveryDataMapperBase(ShipmentTrackingEtaAndDeliveryDataPtr shipmentTrackingEtaAndDeliveryData);

    void mapTimesAndComputeDelay(const basar::DateTime& plannedTimeOfArrival, EtaDelayPresentationPtr etaDelayPresentation, EtaDelayEvaluationCollection etaDelayEvaluationCollection) 
         { doMapTimesAndComputeDelay(plannedTimeOfArrival, etaDelayPresentation, etaDelayEvaluationCollection); }

    void setTimesAndDelayFallback(EtaDelayEvaluationCollection etaDelayEvaluationCollection)     { doSetTimesAndDelayFallback(etaDelayEvaluationCollection); }

protected:
    virtual ~ShipmentTrackingEtaAndDeliveryDataMapperBase();

    virtual void doMapTimesAndComputeDelay(const basar::DateTime& plannedTimeOfArrival, EtaDelayPresentationPtr etaDelayPresentation, EtaDelayEvaluationCollection etaDelayEvaluationCollection) = 0;
    virtual void doSetTimesAndDelayFallback(EtaDelayEvaluationCollection etaDelayEvaluationCollection) = 0;

    void setEstimatedTimeOfArrival(const basar::DateTime& estimatedTimeOfArrival);
    void setEstimatedTimeOfArrivalMin(const basar::DateTime& estimatedTimeOfArrivalMin);
    void setEstimatedTimeOfArrivalMax(const basar::DateTime& estimatedTimeOfArrivalMax);
    void setDeliveredAt(const basar::DateTime& deliveredAt);
    void setDelayInfo(const basar::VarString& delayInfo);
    void setDelayInMinutes(const basar::Int32& delayInMinutes);

protected:
    ShipmentTrackingEtaAndDeliveryDataPtr m_EtaAndDeliveryData;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATAMAPPER_BASE_H
