#ifndef GUARD_LIBCSC_IBT_I_IBTBRANCH_REPOSITORY_H
#define GUARD_LIBCSC_IBT_I_IBTBRANCH_REPOSITORY_H

#include <libbasar_definitions.h>
#include <ibt/ibtbranch/iibtbranchsettingptr.h>
#include <ibt/ibtbranch/iibtbranchsettingcollectionptr.h>

namespace libcsc {
namespace ibt {

class IIbtBranchRepository
{
public:
	virtual ~IIbtBranchRepository() {};

	virtual IIbtBranchSettingPtr findIbtBranchSetting(const basar::Int16& branchNo, const basar::Int16& ibtBranchNo) = 0;
	virtual IIbtBranchSettingCollectionPtr findIbtBranchSettings(const basar::Int16& branchNo) = 0;

};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUEST_REPOSITORY_H
