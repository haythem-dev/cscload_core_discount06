#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYPRESENTATION_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYPRESENTATION_PTR_H

#include <boost/shared_ptr.hpp>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class EtaDelayPresentation;
typedef boost::shared_ptr<EtaDelayPresentation> EtaDelayPresentationPtr;

typedef std::map<const basar::Int16, EtaDelayPresentationPtr> EtaDelayPresentationMap;

} // namespace shipmenttracking
} // namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayPresentation& etaDelayPresentation);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayPresentation* etaDelayPresentation);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayPresentationPtr etaDelayPresentation);

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYPRESENTATION_PTR_H
