#include "ibtbranchsettingsqlmapper.h"
#include "ibtbranchsetting.h"

namespace libcsc {
namespace ibt {

IbtBranchSettingSqlMapper::IbtBranchSettingSqlMapper(IbtBranchSettingPtr ibtBranchSetting, const basar::db::sql::ResultsetRef resultSet) :
	IbtBranchSettingMapperBase( ibtBranchSetting), m_ResultSet( resultSet )
{
}

IbtBranchSettingSqlMapper::~IbtBranchSettingSqlMapper()
{
}

void IbtBranchSettingSqlMapper::doMap()
{
    // TODO: check ResultSet
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setBranchNo				    (m_ResultSet.getInt16("branchno"));
	setIbtBranchNo			    (m_ResultSet.getInt16("ibtbranchno"));
    setSplitToSingleOrder	    (m_ResultSet.getInt16("splittosingleorder") == 1);
    setWaitForPicking		    (m_ResultSet.getInt16("waitforpicking") == 1);
    setReduceIBTQtyForIBTLacks  (m_ResultSet.getInt16("reduceibtqtyforibtlacks") == 1);
}

const basar::VarString IbtBranchSettingSqlMapper::getSingleSelectSQL(const basar::Int16& branchNo, const basar::Int16& ibtBranchNo)
{
	std::stringstream ss;
	ss <<
		"SELECT "
		"branchno, "
		"ibtbranchno, "
		"splittosingleorder, "
		"waitforpicking, "
        "reduceibtqtyforibtlacks "
		"FROM ibtbranchsetting "
		"WHERE branchno = " << branchNo << " " <<
		"AND ibtbranchno = " << ibtBranchNo;
	return ss.str();
}

const basar::VarString IbtBranchSettingSqlMapper::getBranchSelectSQL(const basar::Int16& branchNo)
{
	std::stringstream ss;
	ss <<
		"SELECT "
		"branchno, "
		"ibtbranchno, "
		"splittosingleorder, "
		"waitforpicking, "
        "reduceibtqtyforibtlacks "
		"FROM ibtbranchsetting "
		"WHERE branchno = " << branchNo << " " <<
		"ORDER BY ibtbranchno";

	return ss.str();
}


} // end namespace ibt
} // end namespace libcsc
