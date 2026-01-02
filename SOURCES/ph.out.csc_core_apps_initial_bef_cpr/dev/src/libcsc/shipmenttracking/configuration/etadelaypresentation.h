#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYPRESENTATION_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYPRESENTATION_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>

#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_date.h>
#include <libbasar_definitions.h>
#include <iostream>

#include "etadelaypresentationptr.h"

namespace libcsc {
namespace shipmenttracking {

class EtaDelayPresentation
{
    friend class EtaDelayPresentationMapperBase;

public:
    EtaDelayPresentation();
    virtual ~EtaDelayPresentation();

    const basar::Int16&     getBranchNo() const                     { return m_BranchNo; }
    const basar::Int16&     getRoundingTo() const                   { return m_RoundingTo; }
    const basar::Int16&     getArrivalTimeFrameInMinutes() const    { return m_ArrivalTimeFrameInMinutes; }

    friend std::ostream& ::operator<<(std::ostream& os, const EtaDelayPresentation& etaDelayPresentation);

private:
    libcsc::Int16           m_BranchNo;
    libcsc::Int16           m_RoundingTo;
    libcsc::Int16           m_ArrivalTimeFrameInMinutes;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYPRESENTATION_H
