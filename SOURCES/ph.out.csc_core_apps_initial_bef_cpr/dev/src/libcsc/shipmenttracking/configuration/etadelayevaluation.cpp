#include "etadelayevaluation.h"


namespace libcsc {
namespace shipmenttracking {

EtaDelayEvaluation::EtaDelayEvaluation()
{
}


EtaDelayEvaluation::~EtaDelayEvaluation()
{
}

} // end namespace shipmenttracking
} // end namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayEvaluation& etaDelayEvaluation)
{
    os << "EtaDelayEvaluation: {"
        << "UpToDelayedMinutes: " << etaDelayEvaluation.getUpToDelayedMinutes() 
        << ", DelayText: " << etaDelayEvaluation.getDelayText() 
        << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayEvaluation* etaDelayEvaluation)
{
    if (etaDelayEvaluation != NULL)
    {
        os << *etaDelayEvaluation;
    }
    else
    {
        os << "EtaDelayEvaluation: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayEvaluationPtr etaDelayEvaluation)
{
    os << etaDelayEvaluation.get();
    return os;
}
