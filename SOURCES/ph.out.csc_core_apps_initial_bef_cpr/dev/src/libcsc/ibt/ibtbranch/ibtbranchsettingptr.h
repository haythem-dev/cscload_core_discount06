#ifndef GUARD_LIBCSC_IBT_IBTBRANCHSETTING_PTR_H
#define GUARD_LIBCSC_IBT_IBTBRANCHSETTING_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace ibt {

	class IbtBranchSetting;
	typedef boost::shared_ptr<libcsc::ibt::IbtBranchSetting> IbtBranchSettingPtr;

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTBRANCHSETTING_PTR_H
