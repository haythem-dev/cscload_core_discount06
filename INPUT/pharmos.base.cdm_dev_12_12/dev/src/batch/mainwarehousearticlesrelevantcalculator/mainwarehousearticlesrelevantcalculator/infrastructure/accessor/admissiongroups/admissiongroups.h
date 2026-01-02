#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_ADMISSIONGROUPS_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_ADMISSIONGROUPS_H
#include <vector>
#include <boost/shared_ptr.hpp>
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include "admissiongroupcondition.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{
//namespace admissiongroups
//{

class AdmissionGroups
{
public:
	AdmissionGroups(basar::Int16 Id, basar::Int16 Priority, basar::ConstString Name, bool ActivationFlag
		, AdmissionGroupConditionVector conditions)
		: m_Id(Id), m_Priority(Priority), m_Name(Name), m_ActivationFlag(ActivationFlag), m_Conditions(conditions)
	{}

	// properties
	basar::Int16 Id() const { return m_Id; }
	basar::Int16 Priority() const { return m_Priority; }
	basar::ConstBuffer Name() const { return m_Name.c_str(); }
	bool ActivationFlag() const { return m_ActivationFlag; }

	//methods
	bool hasConditions() const;
	basar::VarString getSql(basar::Int32 artno, basar::Int32 branchno);

private:
	AdmissionGroups();

	basar::Int16 m_Id;
	basar::Int16 m_Priority;
	basar::VarString m_Name;
	bool m_ActivationFlag;

	AdmissionGroupConditionVector m_Conditions;
};

typedef std::vector<boost::shared_ptr<AdmissionGroups> > AdmissionGroupsVector;

//}
}
}
}

#endif	// GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_ADMISSIONCONSIDERGROUPS_H