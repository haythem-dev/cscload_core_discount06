#include <ibt/ibtbranch/ibtbranchsettingcollection.h>
#include <ibt/ibtbranch/ibtbranchsettingptr.h>

namespace libcsc {
namespace ibt {

IbtBranchSettingCollection::IbtBranchSettingCollection()
{
}

IbtBranchSettingCollection::~IbtBranchSettingCollection()
{
}

IIbtBranchSettingPtr IbtBranchSettingCollection::findBranchSetting(const basar::Int16 ibtBranchNo)
{
    IbtBranchSettingCollection::const_iterator it = begin();
    while (it != end())
    {
        if ((*it)->getIbtBranchNo() == ibtBranchNo)
            return (*it);
        ++it;
    }
    return IIbtBranchSettingPtr();
}

int IbtBranchSettingCollection::count()
{
    return static_cast<int>(this->std::list<IIbtBranchSettingPtr>::size());
}


} // namespace ibt
} // namespace libcsc

