#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYEVALUATION_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYEVALUATION_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace shipmenttracking {

class EtaDelayEvaluation;
typedef boost::shared_ptr<EtaDelayEvaluation> EtaDelayEvaluationPtr;

typedef std::list<EtaDelayEvaluationPtr> EtaDelayEvaluationCollection;

} // namespace shipmenttracking
} // namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayEvaluation& etaDelayEvaluation);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayEvaluation* etaDelayEvaluation);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayEvaluationPtr etaDelayEvaluation);

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYEVALUATION_PTR_H
