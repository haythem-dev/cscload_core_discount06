#ifndef GUARD_LIBCSC_IBT_IBTBRANCH_REPOSITORY_H
#define GUARD_LIBCSC_IBT_IBTBRANCH_REPOSITORY_H

#include <ibt/ibtbranch/iibtbranchrepository.h>
#include <persistence/iaccessorptr.h>

namespace libcsc {
namespace ibt {

class IbtBranchRepository : public IIbtBranchRepository
{
public:
	IbtBranchRepository();
    virtual ~IbtBranchRepository();

    void injectBranchSettingAccessor( persistence::IAccessorPtr accessor );

	virtual IIbtBranchSettingPtr findIbtBranchSetting(const basar::Int16& branchNo, const basar::Int16& ibtBranchNo);
	virtual IIbtBranchSettingCollectionPtr findIbtBranchSettings(const basar::Int16& branchNo);

private:
    persistence::IAccessorPtr				m_BranchSettingAccessor;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTBRANCH_REPOSITORY_H
