#include "ibtbranchsetting.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace ibt {

IbtBranchSetting::IbtBranchSetting()
{
}

IbtBranchSetting::~IbtBranchSetting()
{
}

const basar::Int16& IbtBranchSetting::getBranchNo() const
{
    return m_BranchNo;
}

const basar::Int16& IbtBranchSetting::getIbtBranchNo() const
{
    return m_IbtBranchNo;
}

const bool& IbtBranchSetting::getSplitToSingleOrder() const
{
    return m_SplitToSingleOrder;
}

const bool& IbtBranchSetting::getWaitForPicking() const
{
    return m_WaitForPicking;
}

const bool& IbtBranchSetting::getReduceIBTQtyForIBTLacks() const
{
    return m_ReduceIBTQtyForIBTLacks;
}

} // namespace ibt
} // namespace libcsc
