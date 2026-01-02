#ifndef GUARD_LIBCSC_IBT_IBTBRANCHSETTINGCOLLECTION_H
#define GUARD_LIBCSC_IBT_IBTBRANCHSETTINGCOLLECTION_H

#include <ibt/ibtbranch/iibtbranchsettingptr.h>
#include <ibt/ibtbranch/iibtbranchsettingcollection.h>
#include <list>

namespace libcsc {
namespace ibt {

class IbtBranchSettingCollection : public IIbtBranchSettingCollection, public std::list<IIbtBranchSettingPtr>
{
public:
    IbtBranchSettingCollection();
    virtual ~IbtBranchSettingCollection();
	
	virtual IIbtBranchSettingPtr findBranchSetting(const basar::Int16 ibtBranchNo);
	virtual int count();

private:
	IbtBranchSettingCollection( const IbtBranchSettingCollection & );
	IbtBranchSettingCollection & operator=( const IbtBranchSettingCollection & );
};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTBRANCHSETTINGCOLLECTION_H
