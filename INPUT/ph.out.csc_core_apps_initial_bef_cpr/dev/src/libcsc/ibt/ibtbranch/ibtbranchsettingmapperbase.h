#ifndef GUARD_LIBCSC_IBT_IBTBRANCHSETTING_MAPPERBASE_H
#define GUARD_LIBCSC_IBT_IBTBRANCHSETTING_MAPPERBASE_H

#include <libbasar_definitions.h>
#include <ibt/ibtbranch/ibtbranchsettingptr.h>

namespace libcsc {
namespace ibt {

class IbtBranchSettingMapperBase
{
public:
    IbtBranchSettingMapperBase( IbtBranchSettingPtr ibtBranchSetting );

    void map();

protected:
    virtual ~IbtBranchSettingMapperBase();

    virtual void doMap() = 0;

    void setBranchNo(const basar::Int16& branchNo);
    void setIbtBranchNo(const basar::Int16& ibtBranchNo);
    void setSplitToSingleOrder(const bool& splitToSingleOrder);
    void setWaitForPicking(const bool& waitForPicking);
    void setReduceIBTQtyForIBTLacks(const bool& reduceIBTQtyForIBTLacks);

private:
    IbtBranchSettingPtr	m_IbtBranchSetting;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTBRANCHSETTING_MAPPERBASE_H
