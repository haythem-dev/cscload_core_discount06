#ifndef GUARD_DOMMOD_IBTRELEVANTPARAMETER_IIBTRELEVANTPARAMETERDM_H
#define GUARD_DOMMOD_IBTRELEVANTPARAMETER_IIBTRELEVANTPARAMETERDM_H

//-----------------------------------------------------------------------------------------

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

#include <libutil/accessor.h>

//-----------------------------------------------------------------------------------------

namespace ibtrelevantcalculator {
namespace domMod {
namespace ibtRelevantParameter {

class IIbtRelevantParameterDM
{
public:
	virtual ~IIbtRelevantParameterDM() {}

	virtual void                                                find				( ) = 0;
	virtual basar::db::aspect::AccessorPropertyTableRef         get					( ) = 0;

	virtual basar::Int16										getBranchNo			( ) = 0;
};

} 
} 
} 

#endif //end GUARD_DOMMOD_IBTRELEVANTPARAMETER_IIBTRELEVANTPARAMETERDM_H
