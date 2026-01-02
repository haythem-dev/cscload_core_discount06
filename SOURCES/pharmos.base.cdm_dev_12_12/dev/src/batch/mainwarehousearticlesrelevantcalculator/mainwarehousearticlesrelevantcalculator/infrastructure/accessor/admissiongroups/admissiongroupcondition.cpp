#include "../mainwarehousearticlesrelevantcalculator/usecase/cmnuc.h"

#include "admissiongroupcondition.h"
#include <string>
#include <sstream>
#include <boost/io/detail/quoted_manip.hpp>
#include <libutil/misc/metaclassmacro_definitions.h> // libutil

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{
/*
basar::VarString AdmissionGroupCondition::getSql()
{
	basar::VarString retStr;

	//if (Table().ExtraSelect()) {
	//	retStr.format("SELECT 1 FROM %s WHERE %s AND %s AND %s", 
	//		Table().Name().c_str(), buildKeys().c_str(), Table().ExtraSelect().value().c_str(), buildCondition().c_str());
	//}
	//else {
		retStr.format("SELECT 1 FROM %s WHERE %s AND %s", Table().Name().c_str(), buildKeys().c_str(), buildCondition().c_str());
	//}
	
	return retStr;
}
*/

basar::VarString AdmissionGroupCondition::getSql(basar::Int32 artno, basar::Int32 branchno)
{
	basar::VarString retStr;

	if (Table().ExtraSelect())
	{
		if (0 == Table().Keys().size())
		{
			retStr.format("SELECT 1 FROM %s WHERE %s AND %s",
				Table().Name().c_str(), Table().ExtraSelect().value().c_str(), buildCondition().c_str());
		}
		else
		{
			retStr.format("SELECT 1 FROM %s WHERE %s AND %s AND %s",
				Table().Name().c_str(), buildKeys(artno, branchno).c_str(), Table().ExtraSelect().value().c_str(), buildCondition().c_str());
		}
	}
	else
	{
		if (0 == Table().Keys().size())
		{
			retStr.format("SELECT 1 FROM %s WHERE %s", Table().Name().c_str(), buildCondition().c_str());
		}
		else
		{
			retStr.format("SELECT 1 FROM %s WHERE %s AND %s", Table().Name().c_str(), buildKeys(artno, branchno).c_str(), buildCondition().c_str());
		}
	}

	return retStr;
}

//basar::ConstString AdmissionGroupCondition::m_configKeys[] = {"pumainwarehousebrancharticleconfig.articleno", "pumainwarehousebrancharticleconfig.branchno"};

basar::VarString AdmissionGroupCondition::buildKeys(basar::Int32 artno, basar::Int32 branchno)
{
	const std::vector<basar::VarString>& keys = Table().Keys();
	if (keys.size() < 1 || keys.size() > 2) {
		throw basar::OutOfRangeIndexException(
			basar::cmnutil::ExceptionInfoStruct("AsmissionGroupCondition::buildKeys", 
				"Condition table must have 1 or 2 keys", __FILE__, __LINE__));
	}

	basar::VarString configKeys[2];
	configKeys[0].itos(artno);
	configKeys[1].itos(branchno);

	basar::VarString tmpStr;
	basar::VarString retStr;
	for (size_t i = 0; i < keys.size(); i++)
	{
		if (i > 0) {
			retStr.append(" AND ");
		}
		tmpStr.format("%s.%s=%s", Table().Name().c_str(), keys[i].c_str(), configKeys[i].c_str());
		retStr.append(tmpStr);
	}

	return retStr;
}

basar::VarString AdmissionGroupCondition::buildCondition()
{
	basar::VarString retStr;

	if (Operator() == "between") {
		retStr.format("%s BETWEEN %s AND %s", ColumnName().c_str(), FormatValueForSql(StartCompareValue()).c_str(), FormatValueForSql(EndCompareValue()).c_str());
	}
	else if (Operator() == "in") {
		retStr.format("%s IN (%s)", ColumnName().c_str(), FormatValueListForSql(CompareValue()).c_str());
	}
	else if (Operator() == "like") {
		retStr.format("%s LIKE '%s'", ColumnName().c_str(), CompareValue().c_str());
	}
	else {
		retStr.format("%s %s %s", ColumnName().c_str(), Operator().c_str(), FormatValueForSql(CompareValue()).c_str());
	}
	return retStr;
}

basar::VarString AdmissionGroupCondition::FormatValueForSql(const basar::VarString& val) const
{
	if (ColumnType() == "string") {
		// Append and escape quotes 
		std::stringstream	ss;
		ss << boost::io::quoted(val, '\'', '\'');
		return ss.str();
	}

	// Return original value
	return val;
}

basar::VarString AdmissionGroupCondition::FormatValueListForSql(const basar::VarString& val) const
{
	if (ColumnType() == "string") {
		// Tokenize the value list and append quotes to each of the values
		basar::cmnutil::CollBString values = val.tokenize(",");

		std::stringstream	ss;
		for (size_t i = 0; i < values.size(); ++i) {
			values[i].trim(basar::cmnutil::BString::FIRST_END);
			if (i > 0) {
				ss << ",";
			}
			ss << boost::io::quoted(values[i], '\'', '\'');
		}
		return ss.str();
	}

	// Return original value
	return val;
}


}
}
}