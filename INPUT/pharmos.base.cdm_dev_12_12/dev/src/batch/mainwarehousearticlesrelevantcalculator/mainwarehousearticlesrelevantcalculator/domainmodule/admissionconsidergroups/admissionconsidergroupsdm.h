#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ADMISSION_CONSIDERGROUPDM_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ADMISSION_CONSIDERGROUPDM_H

#include <vector>
#include <boost/unordered_map.hpp>

#include "../mainwarehousearticlesrelevantcalculator/infrastructure/accessor/admissiongroups/admissiongroups.h"
#include "../mainwarehousearticlesrelevantcalculator/infrastructure/accessor/admissiongroups/admissiongroupcondition.h"
#include "../mainwarehousearticlesrelevantcalculator/infrastructure/accessor/admissiongroups/admissiongrouptable.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace admissionconsidergroups
{
	using namespace mainwarehousearticlesrelevantcalculator::infrastructure::accessor;

class AdmissionConsiderGroupsDM
{
public:
	AdmissionConsiderGroupsDM(basar::db::aspect::ConnectionRef connection);
	~AdmissionConsiderGroupsDM();

	void execute(basar::VarString sql);
	//void clearRemovalGroups();
	AdmissionGroupsVector getActiveGroups();

	AdmissionGroupConditionVector getAdmissionGroupConditionsByGroupId(basar::Int16 groupId);
	AdmissionGroupTable& getAdmissionGroupTableByTableName(basar::ConstString tableName);
	std::vector<basar::VarString> getKeysByTableName(basar::ConstString tableName);
	boost::optional<basar::VarString> getExtraSelectByTableName(basar::ConstString tableName);
	basar::db::sql::ResultsetRef executeqry(basar::VarString sql);

private:
	const log4cplus::Logger& getLogger()   const;
	const log4cplus::Logger& m_Logger;

	basar::db::sql::ConnectionRef	m_SqlConn;
	basar::db::sql::StatementRef	m_SqlStatement;
	basar::db::sql::PreparedStatementRef m_SqlGroupConditions;
	basar::db::sql::PreparedStatementRef m_SqlSelectKeys;
	basar::db::sql::PreparedStatementRef m_SqlSelectExtraSelect;

	typedef boost::unordered_map< basar::VarString, AdmissionGroupTable> AdmissionGroupTableMap;
	AdmissionGroupTableMap m_Tables;
};

}
}
}
#endif	// GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ADMISSION_CONSIDERGROUPDM_H