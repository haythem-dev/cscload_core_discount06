#include "etadelaypresentationmapperbase.h"
#include "etadelaypresentation.h"


namespace libcsc {
namespace shipmenttracking {


EtaDelayPresentationMapperBase::EtaDelayPresentationMapperBase(EtaDelayPresentationPtr etaDelayPresentation)
    : m_EtaDelayPresentation(etaDelayPresentation)
{
}


EtaDelayPresentationMapperBase::~EtaDelayPresentationMapperBase()
{
}

void EtaDelayPresentationMapperBase::setFallback(const basar::Int16& branchNo)
{
    setBranchNo                 (branchNo);
    setRoundingTo               (0);
    setArrivalTimeFrameInMinutes(0);
}

void EtaDelayPresentationMapperBase::setBranchNo(const basar::Int16 branchNo)
{
    m_EtaDelayPresentation->m_BranchNo = branchNo;
    m_EtaDelayPresentation->m_BranchNo.setClean();
}

void EtaDelayPresentationMapperBase::setRoundingTo(const basar::Int16 roundingTo)
{
    m_EtaDelayPresentation->m_RoundingTo = roundingTo;
    m_EtaDelayPresentation->m_RoundingTo.setClean();
}

void EtaDelayPresentationMapperBase::setArrivalTimeFrameInMinutes(const basar::Int16 arrivalTimeFrameInMinutes)
{
    m_EtaDelayPresentation->m_ArrivalTimeFrameInMinutes = arrivalTimeFrameInMinutes;
    m_EtaDelayPresentation->m_ArrivalTimeFrameInMinutes.setClean();
}


} // end namespace shipmenttracking
} // end namespace libcsc

