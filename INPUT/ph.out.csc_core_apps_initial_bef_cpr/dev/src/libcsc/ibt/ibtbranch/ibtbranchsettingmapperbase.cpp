#include "ibtbranchsettingmapperbase.h"
#include "ibtbranchsetting.h"

namespace libcsc {
namespace ibt {

IbtBranchSettingMapperBase::IbtBranchSettingMapperBase(IbtBranchSettingPtr ibtBranchSetting) :
	m_IbtBranchSetting(ibtBranchSetting)
{
}

IbtBranchSettingMapperBase::~IbtBranchSettingMapperBase()
{
}

void IbtBranchSettingMapperBase::map()
{
    doMap();
}

void IbtBranchSettingMapperBase::setBranchNo(const basar::Int16& branchNo)
{
	m_IbtBranchSetting->m_BranchNo = branchNo;
    m_IbtBranchSetting->m_BranchNo.setClean();
}

void IbtBranchSettingMapperBase::setIbtBranchNo(const basar::Int16& ibtBranchNo)
{
    m_IbtBranchSetting->m_IbtBranchNo = ibtBranchNo;
    m_IbtBranchSetting->m_IbtBranchNo.setClean();
}

void IbtBranchSettingMapperBase::setSplitToSingleOrder(const bool& splitToSingleOrder)
{
	m_IbtBranchSetting->m_SplitToSingleOrder = splitToSingleOrder;
    m_IbtBranchSetting->m_SplitToSingleOrder.setClean();
}

void IbtBranchSettingMapperBase::setWaitForPicking(const bool& waitForPicking)
{
	m_IbtBranchSetting->m_WaitForPicking = waitForPicking;
    m_IbtBranchSetting->m_WaitForPicking.setClean();
}

void IbtBranchSettingMapperBase::setReduceIBTQtyForIBTLacks(const bool& reduceIBTQtyForIBTLacks)
{
    m_IbtBranchSetting->m_ReduceIBTQtyForIBTLacks = reduceIBTQtyForIBTLacks;
    m_IbtBranchSetting->m_ReduceIBTQtyForIBTLacks.setClean();
}


} // end namespace ibt
} // end namespace libcsc
