#ifndef GUARD_LIBCSC_IBT_IIBTBRANCHSETTINGCOLLECTION_H
#define GUARD_LIBCSC_IBT_IIBTBRANCHSETTINGCOLLECTION_H

#include <ibt/ibtbranch/iibtbranchsetting.h>
#include <list>
#include <libbasar_definitions.h>

namespace libcsc {
namespace ibt {

class IIbtBranchSettingCollection
{
public:
    virtual ~IIbtBranchSettingCollection() {}

	virtual IIbtBranchSettingPtr findBranchSetting(const basar::Int16 ibtBranchNo) = 0;
	virtual int count() = 0;
};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IIBTBRANCHSETTINGCOLLECTION_H
