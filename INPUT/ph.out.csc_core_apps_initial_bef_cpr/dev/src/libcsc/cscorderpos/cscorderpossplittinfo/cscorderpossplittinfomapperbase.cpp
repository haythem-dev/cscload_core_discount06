#include <datatypes/boolean.h>
#include "logger/loggerpool.h"
#include "cscorderpossplittinfomapperbase.h"

namespace libcsc {
namespace cscorderpos {
namespace repo {

CSCOrderposSplittinfoMapperBase::CSCOrderposSplittinfoMapperBase(domMod::ICSCOrderposSplittinfoPtr splittinfo)
    : m_Splittinfo(*dynamic_cast<domMod::CSCOrderposSplittinfo*>(splittinfo.get()))
{
}

CSCOrderposSplittinfoMapperBase::~CSCOrderposSplittinfoMapperBase()
{
}

void CSCOrderposSplittinfoMapperBase::map()
{
    doMap();
}

void CSCOrderposSplittinfoMapperBase::setClean(domMod::CSCOrderposSplittinfoPtr splittinfo)
{
    splittinfo->m_CscOrderNo.setClean();
    splittinfo->m_CscOrderPosNo.setClean();
    splittinfo->m_SplittType.setClean();
    splittinfo->m_Original.setClean();
    splittinfo->m_OrderNo.setClean();
    splittinfo->m_OrderNo.setClean();
}

void CSCOrderposSplittinfoMapperBase::setCscOrderNo(basar::Int32 const cscorderno)
{
    m_Splittinfo.m_CscOrderNo = cscorderno;
    m_Splittinfo.m_CscOrderNo.setClean();
}

void CSCOrderposSplittinfoMapperBase::setCscOrderPosNo(basar::Int32 const cscorderposno)
{
    m_Splittinfo.m_CscOrderPosNo = cscorderposno;
    m_Splittinfo.m_CscOrderPosNo.setClean();
}

void CSCOrderposSplittinfoMapperBase::setSplittType(SplittTypeEnum const splittype)
{
    m_Splittinfo.m_SplittType = splittype;
    m_Splittinfo.m_SplittType.setClean();
}

void CSCOrderposSplittinfoMapperBase::setOriginal(SplittOriginTypeEnum const original)
{
    m_Splittinfo.m_Original = original;
    m_Splittinfo.m_Original.setClean();
}

void CSCOrderposSplittinfoMapperBase::setOrderNo(basar::Int32 const orderno)
{
    m_Splittinfo.m_OrderNo = orderno;
    m_Splittinfo.m_OrderNo.setClean();
}

void CSCOrderposSplittinfoMapperBase::setOrderPosNo(basar::Int32 const orderposno)
{
    m_Splittinfo.m_OrderPosNo = orderposno;
    m_Splittinfo.m_OrderPosNo.setClean();
}

} // end namespace repo
} // end namespace cscorderpos
} // end namespace libcsc
