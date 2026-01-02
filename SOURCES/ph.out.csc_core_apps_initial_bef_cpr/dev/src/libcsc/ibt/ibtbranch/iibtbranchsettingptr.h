#ifndef GUARD_LIBCSC_IBT_I_IBTBRANCHSETTING_PTR_H
#define GUARD_LIBCSC_IBT_I_IBTBRANCHSETTING_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace ibt {

	class IIbtBranchSetting;
	typedef boost::shared_ptr<libcsc::ibt::IIbtBranchSetting> IIbtBranchSettingPtr;

//	typedef std::list<libcsc::ibt::IIbtBranchSettingPtr> IIbtBranchSettingCollection;

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTBRANCHSETTING_PTR_H
