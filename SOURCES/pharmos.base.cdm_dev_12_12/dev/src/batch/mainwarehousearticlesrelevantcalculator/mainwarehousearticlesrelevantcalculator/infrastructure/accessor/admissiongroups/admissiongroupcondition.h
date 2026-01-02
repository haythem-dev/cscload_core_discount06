#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_ADMISSIONGROUPSCONDITION_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_ADMISSIONGROUPSCONDITION_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include "admissiongrouptable.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{

using namespace basar::cmnutil;

class AdmissionGroupCondition
{
public:
	AdmissionGroupCondition(basar::Int16 GroupId,
		basar::Int16 SequenceNo,
		basar::VarString OperatorToPrevCondition,
		basar::VarString TableName,
		basar::VarString ColumnName,
		basar::VarString Operator,
		basar::VarString ColumnType,
		basar::VarString CompareValue,
		basar::VarString StartCompareValue,
		basar::VarString EndCompareValue,
		AdmissionGroupTable& Table)
		:
		m_GroupId(GroupId),
		m_SequenceNo(SequenceNo),
		m_OperatorToPrevCondition(OperatorToPrevCondition),
		m_TableName(TableName),
		m_ColumnName(ColumnName),
		m_Operator(Operator),
		m_ColumnType(ColumnType),
		m_CompareValue(CompareValue),
		m_StartCompareValue(StartCompareValue),
		m_EndCompareValue(EndCompareValue),
		m_Table(Table)
	{}
	// properties
	basar::Int16 GroupId() const { return m_GroupId; }
	basar::Int16 SequenceNo() const { return m_SequenceNo; }
	const basar::VarString& OperatorToPrevCondition() const { return m_OperatorToPrevCondition; }
	const basar::VarString& TableName() const { return m_TableName; }
	const basar::VarString& ColumnName() const { return m_ColumnName; }
	const basar::VarString& Operator() const { return m_Operator; }
	const basar::VarString& ColumnType() const { return m_ColumnType; }
	const basar::VarString& CompareValue() const { return m_CompareValue; }
	const basar::VarString& StartCompareValue() const { return m_StartCompareValue; }
	const basar::VarString& EndCompareValue() const { return m_EndCompareValue; }
	basar::VarString FormatValueForSql(const basar::VarString&) const;
	basar::VarString FormatValueListForSql(const basar::VarString&) const;

	AdmissionGroupTable& Table() const { return m_Table; }
	// methods
	basar::VarString getSql(basar::Int32 artno, basar::Int32 branchno);

private:
	basar::VarString buildKeys(basar::Int32 artno, basar::Int32 branchno);
	basar::VarString buildCondition();

	//static basar::ConstString 
	//basar::VarString m_configKeys[2];

	basar::Int16 m_GroupId;
	basar::Int16 m_SequenceNo;
	basar::VarString m_OperatorToPrevCondition;
	basar::VarString m_TableName;
	basar::VarString m_ColumnName;
	basar::VarString m_Operator;
	basar::VarString m_ColumnType;
	basar::VarString m_CompareValue;
	basar::VarString m_StartCompareValue;
	basar::VarString m_EndCompareValue;
	AdmissionGroupTable&  m_Table;
};

typedef std::vector<boost::shared_ptr<AdmissionGroupCondition> > AdmissionGroupConditionVector;

}
}
}

#endif	// __LIBS_REMOVAL_GROUP_CONDITION_HEADER__