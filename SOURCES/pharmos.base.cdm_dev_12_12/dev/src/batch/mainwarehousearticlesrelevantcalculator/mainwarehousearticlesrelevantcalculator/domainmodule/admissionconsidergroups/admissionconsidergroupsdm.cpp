
#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "admissionconsidergroupsdm.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace admissionconsidergroups
{

// SQL Statements
basar::ConstString sqlGroupConditions = 
	"SELECT paramgroupid,"
	"sequenceno, operatortopreviouscondition,"
	"tablename, columnname,"
	"operator, columntype,"
	"comparevalue, startcomparevalue, endcomparevalue"
	" FROM pumainwarehouseadmissioncondition WHERE paramgroupid = ? ORDER BY sequenceno";

//basar::ConstString sqlUpdatePuibtbrancharticleconfig = "UPDATE pumainwarehousebrancharticleconfig SET admissionparamgroupid = 0 WHERE orderatmainwarehouseflag = 1 and branchno = 5";

basar::ConstString sqlSelectGroups = "SELECT paramgroupid, priority, name, activationflag FROM pumainwarehouseadmissionconditiongroup WHERE paramgroupid > 0 AND activationflag <> 0 ORDER BY priority DESC";

basar::ConstString sqlSelectKeysByTableName = "SELECT columnname FROM pumainwarehouseadmissionconditiontablecolumns WHERE tablename = ? AND iskeyflag <> 0 ORDER BY iskeyflag";

basar::ConstString sqlSelectExtraSelectByTableName = "SELECT extraselectstatement FROM puibtremovalparamgrouptableextraselect WHERE tablename = ?";

/////////////////////////////////////////////////////////////////////////////////////////
AdmissionConsiderGroupsDM::AdmissionConsiderGroupsDM(basar::db::aspect::ConnectionRef connection)
	: m_Logger(mainwarehousearticlesrelevantcalculator::LoggerPool::getLoggerMainwarehouseArticlesRelevantCalculator()), m_SqlConn(connection.getSqlConnection())
{
	m_SqlStatement = m_SqlConn.createStatement();
	m_SqlGroupConditions = m_SqlConn.createPreparedStatement(sqlGroupConditions);
	m_SqlSelectKeys = m_SqlConn.createPreparedStatement(sqlSelectKeysByTableName);
	m_SqlSelectExtraSelect = m_SqlConn.createPreparedStatement(sqlSelectExtraSelectByTableName);
}

AdmissionConsiderGroupsDM::~AdmissionConsiderGroupsDM()
{
}

void AdmissionConsiderGroupsDM::execute(basar::VarString sql)
{
	m_SqlStatement.execute(sql);
}

basar::db::sql::ResultsetRef AdmissionConsiderGroupsDM::executeqry(basar::VarString sql)
{
	return m_SqlStatement.executeQuery(sql);
}

const log4cplus::Logger& AdmissionConsiderGroupsDM::getLogger() const
{
	return m_Logger;
}

AdmissionGroupsVector AdmissionConsiderGroupsDM::getActiveGroups()
{
	AdmissionGroupsVector ret;

	std::ostringstream oss1;
	oss1 << "getActiveGroups..." << sqlSelectGroups;
	BLOG_TRACE(getLogger(), oss1.str());

	basar::db::sql::ResultsetRef resultSet = m_SqlStatement.executeQuery(sqlSelectGroups);
	while (resultSet.next())
	{
		basar::Int16 id = static_cast<basar::Int16>(resultSet.getInt32(0));
		ret.push_back(boost::shared_ptr<AdmissionGroups>(
			new AdmissionGroups(id						// Id
			, resultSet.getInt16(1)							// Priority
			, resultSet.getString(2)						// Name	
			, resultSet.getInt16(3) == 0 ? false : true		// ActivationFlag
			, getAdmissionGroupConditionsByGroupId(id))));		// Conditions
	}

	return ret;
}

AdmissionGroupConditionVector AdmissionConsiderGroupsDM::getAdmissionGroupConditionsByGroupId(basar::Int16 groupId)
{
	AdmissionGroupConditionVector ret;

	m_SqlGroupConditions.setInt16(0, groupId);
	basar::db::sql::ResultsetRef resultSet = m_SqlGroupConditions.executeQuery();
	while (resultSet.next())
	{
		basar::ConstString tableName = resultSet.getString(3);
		ret.push_back(boost::shared_ptr<AdmissionGroupCondition>(
		new AdmissionGroupCondition(resultSet.getInt16(0), resultSet.getInt16(1), resultSet.getString(2)	// GroupId, SequenceNo, OperatorToPrevCondition
			, tableName, resultSet.getString(4), resultSet.getString(5), resultSet.getString(6)			// TableName, ColumnName, Operator, ColumnType
			, resultSet.getString(7), resultSet.getString(8), resultSet.getString(9)						// CompareValue, StartCompareValue, EndCompareValue
			, getAdmissionGroupTableByTableName(tableName)												// RemovalGroupTable
		)));
	}

	return ret;
}

AdmissionGroupTable& AdmissionConsiderGroupsDM::getAdmissionGroupTableByTableName(basar::ConstString tableName)
{
	AdmissionGroupTableMap::iterator it = m_Tables.find(tableName);
	if (it == m_Tables.end())
	{
		AdmissionGroupTable tab(tableName, getKeysByTableName(tableName), getExtraSelectByTableName(tableName));
		std::pair<AdmissionGroupTableMap::iterator, bool> pair = m_Tables.insert(std::make_pair(tableName, tab));
		it = pair.first;
	}
	return it->second;
}

std::vector<basar::VarString> AdmissionConsiderGroupsDM::getKeysByTableName(basar::ConstString tableName)
{
	std::vector<basar::VarString> ret;

	m_SqlSelectKeys.setString(0, tableName);
	basar::db::sql::ResultsetRef resultSet = m_SqlSelectKeys.executeQuery();
	while (resultSet.next())
	{
		ret.push_back(resultSet.getString(0));
	}
	return ret;
}

boost::optional<basar::VarString> AdmissionConsiderGroupsDM::getExtraSelectByTableName(basar::ConstString tableName)
{
	m_SqlSelectExtraSelect.setString(0, tableName);
	basar::db::sql::ResultsetRef resultSet = m_SqlSelectExtraSelect.executeQuery();
	if (resultSet.next())
	{
		return boost::optional<basar::VarString>(resultSet.getString(0));
	}
	else
	{
		return boost::optional<basar::VarString>();
	}
}

}
}
}