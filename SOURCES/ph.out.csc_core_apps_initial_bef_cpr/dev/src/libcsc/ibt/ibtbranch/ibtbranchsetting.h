#ifndef GUARD_LIBCSC_IBT_IBTBRANCHSETTING_H
#define GUARD_LIBCSC_IBT_IBTBRANCHSETTING_H

#include <ibt/ibtbranch/iibtbranchsetting.h>
#include <datatypes/int16.h>
#include <datatypes/boolean.h>

namespace libcsc
{
namespace ibt
{
class IbtBranchSetting : public IIbtBranchSetting
{
	// because of OR mapping
    friend class IbtBranchSettingMapperBase;
    friend class IbtBranchSettingRepository;

public:
    IbtBranchSetting();
    virtual ~IbtBranchSetting();

    virtual const basar::Int16& getBranchNo() const;
    virtual const basar::Int16& getIbtBranchNo() const;
    virtual const bool&         getSplitToSingleOrder() const;
    virtual const bool&         getWaitForPicking() const;
    virtual const bool&         getReduceIBTQtyForIBTLacks() const;

private:
	IbtBranchSetting( const IbtBranchSetting & );
	IbtBranchSetting & operator=( const IbtBranchSetting & );

	libcsc::Int16 m_BranchNo;
	libcsc::Int16 m_IbtBranchNo;
	libcsc::Bool  m_SplitToSingleOrder;
	libcsc::Bool  m_WaitForPicking;
    libcsc::Bool  m_ReduceIBTQtyForIBTLacks;
};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTBRANCHSETTING_H
