#ifndef GUARD_LIBCSC_IBT_IBTBRANCHSETTING_SQLMAPPER_H
#define GUARD_LIBCSC_IBT_IBTBRANCHSETTING_SQLMAPPER_H

#include <ibt/ibtbranch/ibtbranchsettingmapperbase.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace ibt {

class IbtBranchSettingSqlMapper : public IbtBranchSettingMapperBase
{
public:
	IbtBranchSettingSqlMapper( IbtBranchSettingPtr ibtBranchSetting, const basar::db::sql::ResultsetRef resultSet );
    virtual ~IbtBranchSettingSqlMapper();

	static const basar::VarString getSingleSelectSQL(const basar::Int16& branchNo, const basar::Int16& ibtBranchNo);
	static const basar::VarString getBranchSelectSQL(const basar::Int16& branchNo);

protected:
    virtual void doMap();

private:
	IbtBranchSettingSqlMapper( const IbtBranchSettingSqlMapper & );
	IbtBranchSettingSqlMapper & operator=( const IbtBranchSettingSqlMapper & );

    const basar::db::sql::ResultsetRef m_ResultSet;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTBRANCHSETTING_SQLMAPPER_H
