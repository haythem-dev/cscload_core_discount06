#include "cscorderflags.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace cscorder {
namespace domMod {

// ------------------------------------------------------------------------------------------------------------------------------------------------------
CSCOrderFlags::CSCOrderFlags()
{
    m_CscOrderNo = 0;
    m_NoDelayedDelivery = false;
    m_WaitForIbtPicking = false;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
CSCOrderFlags::~CSCOrderFlags()
{
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CSCOrderFlags::setClean()
{
    m_CscOrderNo.setClean();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CSCOrderFlags::setCscOrderNo(Int32 const& cscOrderNo)
{	
    m_CscOrderNo = cscOrderNo;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
Int32 const& CSCOrderFlags::getCscOrderNo() const
{
    return m_CscOrderNo;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CSCOrderFlags::setNoDelayedDelivery(bool const& nodelayeddelivery)
{
    m_NoDelayedDelivery = nodelayeddelivery;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CSCOrderFlags::setWaitForIbtPicking(bool const& waitforibtpicking)
{
    m_WaitForIbtPicking = waitforibtpicking;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
bool const& CSCOrderFlags::isNoDelayedDelivery() const
{
    return m_NoDelayedDelivery;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------
bool const& CSCOrderFlags::isWaitForIbtPicking() const
{
    return m_WaitForIbtPicking;
}

} // namespace domMod
} // namespace cscorder
} // namespace libcsc
