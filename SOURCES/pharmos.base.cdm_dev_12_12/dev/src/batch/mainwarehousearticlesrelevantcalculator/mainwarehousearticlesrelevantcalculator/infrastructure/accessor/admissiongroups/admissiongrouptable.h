#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_ADMISSIONGROUPTABLE_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_ADMISSIONGROUPTABLE_H

#include <vector>
#include <boost/optional.hpp>
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include "../mainwarehousearticlesrelevantcalculator/usecase/cmnuc.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{

class AdmissionGroupTable
{
public:
	AdmissionGroupTable(basar::VarString Name,
		std::vector<basar::VarString> Keys,
		boost::optional<basar::VarString> ExtraSelect)
		:
		m_Name(Name), m_Keys(Keys), m_ExtraSelect(ExtraSelect)
	{}
	// properties
	const basar::VarString& Name() const { return m_Name; }
	const std::vector<basar::VarString>& Keys() const { return m_Keys; }
	const boost::optional<basar::VarString>& ExtraSelect() const { return m_ExtraSelect; }

	//methods
//	AdmissionGroupTable() {}

private:
	basar::VarString m_Name;
	std::vector<basar::VarString> m_Keys;
	boost::optional<basar::VarString> m_ExtraSelect;
};

}
}
}
#endif	// GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_ADMISSIONGROUPTABLE_H