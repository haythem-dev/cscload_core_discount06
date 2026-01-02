#include "etadelaypresentation.h"


namespace libcsc {
namespace shipmenttracking {

EtaDelayPresentation::EtaDelayPresentation()
{
}


EtaDelayPresentation::~EtaDelayPresentation()
{
}

} // end namespace shipmenttracking
} // end namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayPresentation& etaDelayPresentation)
{
    os << "EtaDelayPresentation: {"
        << "Branch: " << etaDelayPresentation.getBranchNo() 
        << ", ReoundingTo: " << etaDelayPresentation.getRoundingTo() 
        << ", ArrivalTimeFrameInMinutes: " << etaDelayPresentation.getArrivalTimeFrameInMinutes() 
        << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayPresentation* etaDelayPresentation)
{
    if (etaDelayPresentation != NULL)
    {
        os << *etaDelayPresentation;
    }
    else
    {
        os << "EtaDelayPresentation: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::EtaDelayPresentationPtr etaDelayPresentation)
{
    os << etaDelayPresentation.get();
    return os;
}
