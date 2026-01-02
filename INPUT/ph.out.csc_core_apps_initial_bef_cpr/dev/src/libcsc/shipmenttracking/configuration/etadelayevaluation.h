#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYEVALUATION_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYEVALUATION_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>

#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_date.h>
#include <libbasar_definitions.h>
#include <iostream>

#include "etadelayevaluationptr.h"

namespace libcsc {
namespace shipmenttracking {

class EtaDelayEvaluation
{
    friend class EtaDelayEvaluationMapperBase;

public:
    EtaDelayEvaluation();
    virtual ~EtaDelayEvaluation();

    const basar::Int32&        getUpToDelayedMinutes() const   { return m_UpToDelayedMinutes; }
    const basar::VarString&    getDelayText() const            { return m_DelayText; }

    friend std::ostream& ::operator<<(std::ostream& os, const EtaDelayEvaluation& etaDelayEvaluation);

private:
    libcsc::Int32           m_UpToDelayedMinutes;
    libcsc::VarString       m_DelayText;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_ETADELAYEVALUATION_H
