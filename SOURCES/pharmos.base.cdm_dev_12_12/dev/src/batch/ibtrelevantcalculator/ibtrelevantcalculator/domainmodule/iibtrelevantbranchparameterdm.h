#ifndef GUARD_DOMMOD_IBTRELEVANTBRANCHPARAMETER_IIBTRELEVANTBRANCHPARAMETERDM_H
#define GUARD_DOMMOD_IBTRELEVANTBRANCHPARAMETER_IIBTRELEVANTBRANCHPARAMETERDM_H

//-----------------------------------------------------------------------------------------

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

#include <libutil/accessor.h>

//-----------------------------------------------------------------------------------------

namespace ibtrelevantcalculator {
namespace domMod {
namespace ibtRelevantBranchParameter {

class IIbtRelevantBranchParameterDM
{
public:
	virtual ~IIbtRelevantBranchParameterDM() {}

	virtual void                                                find				( ) = 0;
	virtual basar::db::aspect::AccessorPropertyTableRef         get					( ) = 0;

	virtual basar::Int16										getBranchNo			( ) = 0;
};

} 
} 
} 

#endif //end GUARD_DOMMOD_IBTRELEVANTBRANCHPARAMETER_IIBTRELEVANTBRANCHPARAMETERDM_H
