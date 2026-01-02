#include "../mainwarehousearticlesrelevantcalculator/usecase/cmnuc.h"

#include "admissiongroups.h"
#include <libutil/misc/metaclassmacro_definitions.h> // libutil

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{

		bool AdmissionGroups::hasConditions() const
		{
			return !m_Conditions.empty();
		}

		basar::VarString AdmissionGroups::getSql(basar::Int32 artno, basar::Int32 branchno)
		{
			basar::VarString retStr;

			//retStr.format("UPDATE pumainwarehousebrancharticleconfig SET admissionparamgroupid = %d WHERE orderatmainwarehouseflag = 1 AND admissionparamgroupid = 0 AND ", Id());
			retStr.format("SELECT count(*) FROM zartikel WHERE artikel_nr = %d AND ", artno);

			retStr.append(m_Conditions.size(), '(');
			for (size_t i = 0; i < m_Conditions.size(); i++)
			{
				if (i > 0) {
					retStr.append(m_Conditions[i]->OperatorToPrevCondition());
				}
				retStr.append(" EXISTS (");
				retStr.append(m_Conditions[i]->getSql(artno, branchno));
				retStr.append(")) ");
			}

			return retStr;
		}
//}
}
}
}