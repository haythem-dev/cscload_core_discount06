#include "etadelayevaluationmapperbase.h"
#include "etadelayevaluation.h"


namespace libcsc {
namespace shipmenttracking {


EtaDelayEvaluationMapperBase::EtaDelayEvaluationMapperBase(EtaDelayEvaluationPtr etaDelayEvaluation)
    : m_EtaDelayEvaluation(etaDelayEvaluation)
{
}


EtaDelayEvaluationMapperBase::~EtaDelayEvaluationMapperBase()
{
}

void EtaDelayEvaluationMapperBase::setUpToDelayedMinutes(const basar::Int32 upToDelayedMinutes)
{
    m_EtaDelayEvaluation->m_UpToDelayedMinutes = upToDelayedMinutes;
    m_EtaDelayEvaluation->m_UpToDelayedMinutes.setClean();
}

void EtaDelayEvaluationMapperBase::setDelayText(const basar::VarString& delayText)
{
    m_EtaDelayEvaluation->m_DelayText = delayText;
    m_EtaDelayEvaluation->m_DelayText.setClean();
}


} // end namespace shipmenttracking
} // end namespace libcsc

