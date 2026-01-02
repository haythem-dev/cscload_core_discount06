#ifndef GUARD_LIBCSC_DOCUMENT_ETADELAYEVALUATIONMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_ETADELAYEVALUATIONMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "etadelayevaluationptr.h"


namespace libcsc {
namespace shipmenttracking {

class EtaDelayEvaluationMapperBase
{
public:
    EtaDelayEvaluationMapperBase(EtaDelayEvaluationPtr etaDelayEvaluation);

    void            map() { doMap(); }

protected:
    virtual ~EtaDelayEvaluationMapperBase();

    virtual void    doMap() = 0;

    void setUpToDelayedMinutes(const basar::Int32 upToDelayedMinutes);
    void setDelayText(const basar::VarString& delayText);

private:
    EtaDelayEvaluationPtr m_EtaDelayEvaluation;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_ETADELAYEVALUATIONMAPPER_BASE_H
