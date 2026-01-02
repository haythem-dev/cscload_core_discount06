#include <datatypes/boolean.h>
#include "cscorderflagsmapperbase.h"
#include "cscorder/cscorderflags/cscorderflags.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCOrderFlagsMapperBase::CSCOrderFlagsMapperBase(domMod::CSCOrderFlagsPtr cscOrderFlags)
	: m_CSCOrderFlags(cscOrderFlags)
{
}

CSCOrderFlagsMapperBase::~CSCOrderFlagsMapperBase()
{
}

void CSCOrderFlagsMapperBase::map()
{
    doMap();
}

void CSCOrderFlagsMapperBase::setCscOrderNo(basar::Int32 const cscOrderNo)
{
    m_CSCOrderFlags->m_CscOrderNo = cscOrderNo;
    m_CSCOrderFlags->m_CscOrderNo.setClean();
}

void CSCOrderFlagsMapperBase::setNoDelayedDelivery( bool const noDelayedDelivery)
{
    m_CSCOrderFlags->m_NoDelayedDelivery = noDelayedDelivery;
    m_CSCOrderFlags->m_NoDelayedDelivery.setClean();
}

void CSCOrderFlagsMapperBase::setWaitForIbtPicking(bool const waitforibtpicking)
{
    m_CSCOrderFlags->m_WaitForIbtPicking = waitforibtpicking;
    m_CSCOrderFlags->m_WaitForIbtPicking.setClean();
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
