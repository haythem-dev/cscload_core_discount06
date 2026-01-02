#ifndef GUARD_LIBCSC_IBT_IBTBRANCHSETTINGCOLLECTION_PTR_H
#define GUARD_LIBCSC_IBT_IBTBRANCHSETTINGCOLLECTION_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace ibt {

	class IbtBranchSettingCollection;
	typedef boost::shared_ptr<libcsc::ibt::IbtBranchSettingCollection> IbtBranchSettingCollectionPtr;
} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTBRANCHSETTINGCOLLECTION_PTR_H
