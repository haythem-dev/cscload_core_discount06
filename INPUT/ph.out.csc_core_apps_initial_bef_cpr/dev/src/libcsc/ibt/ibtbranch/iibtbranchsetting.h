#ifndef GUARD_LIBCSC_IBT_I_IBTBRANCHSETTING_H
#define GUARD_LIBCSC_IBT_I_IBTBRANCHSETTING_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace ibt {
#
class IIbtBranchSetting
{
public:
	virtual ~IIbtBranchSetting() {};

    virtual const basar::Int16& getBranchNo() const = 0;
    virtual const basar::Int16& getIbtBranchNo() const = 0;
    virtual const bool&         getSplitToSingleOrder() const = 0;
    virtual const bool&         getWaitForPicking() const = 0;
    virtual const bool&         getReduceIBTQtyForIBTLacks() const = 0;
};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTBRANCHSETTING_H

