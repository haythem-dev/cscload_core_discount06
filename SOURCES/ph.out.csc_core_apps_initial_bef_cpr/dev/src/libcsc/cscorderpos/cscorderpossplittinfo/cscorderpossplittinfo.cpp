#include "logger/loggerpool.h"
#include "cscorderpossplittinfo.h"

namespace libcsc {
namespace cscorderpos {
namespace domMod {

CSCOrderposSplittinfo::CSCOrderposSplittinfo()
{
}

CSCOrderposSplittinfo::~CSCOrderposSplittinfo()
{
}

Int32 const& CSCOrderposSplittinfo::getCscOrderNo() const
{
    return m_CscOrderNo;
}

Int32 const& CSCOrderposSplittinfo::getCscOrderPosNo() const
{
    return m_CscOrderPosNo;
}

SplittTypeEnum const& CSCOrderposSplittinfo::getSplittType() const
{
    return m_SplittType;
}

SplittOriginTypeEnum const& CSCOrderposSplittinfo::getOriginal() const
{
    return m_Original;
}

Int32 const& CSCOrderposSplittinfo::getOrderNo() const
{
    return m_OrderNo;
}

Int32 const& CSCOrderposSplittinfo::getOrderPosNo() const
{
    return m_OrderPosNo;
}

void CSCOrderposSplittinfo::setCscOrderNo(Int32 const& cscorderno)
{
    m_CscOrderNo = cscorderno;
}

void CSCOrderposSplittinfo::setCscOrderPosNo(Int32 const& cscorderposno)
{
    m_CscOrderPosNo = cscorderposno;
}

void CSCOrderposSplittinfo::setSplittType(SplittTypeEnum const& splittype)
{
    m_SplittType = splittype;
}

void CSCOrderposSplittinfo::setOriginal(SplittOriginTypeEnum const& original)
{
    m_Original = original;
}

void CSCOrderposSplittinfo::setOrderNo(Int32 const& orderno)
{
    m_OrderNo = orderno;
}

void CSCOrderposSplittinfo::setOrderPosNo(Int32 const& orderposno)
{
    m_OrderPosNo = orderposno;
}

} // namespace domMod
} // namespace cscorderpos
} // namespace libcsc
