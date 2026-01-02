#ifndef GUARD_LIBCSC_DOCUMENT_ETADELAYPRESENTATIONMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_ETADELAYPRESENTATIONMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "etadelaypresentationptr.h"


namespace libcsc {
namespace shipmenttracking {

class EtaDelayPresentationMapperBase
{
public:
    EtaDelayPresentationMapperBase(EtaDelayPresentationPtr etaDelayPresentation);

    void            map() { doMap(); }
    void            setFallback(const basar::Int16& branchNo);

protected:
    virtual ~EtaDelayPresentationMapperBase();

    virtual void    doMap() = 0;

    void setBranchNo(const basar::Int16 branchNo);
    void setRoundingTo(const basar::Int16 roundingTo);
    void setArrivalTimeFrameInMinutes(const basar::Int16 arrivalTimeFrameInMinutes);

private:
    EtaDelayPresentationPtr m_EtaDelayPresentation;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_ETADELAYPRESENTATIONMAPPER_BASE_H
