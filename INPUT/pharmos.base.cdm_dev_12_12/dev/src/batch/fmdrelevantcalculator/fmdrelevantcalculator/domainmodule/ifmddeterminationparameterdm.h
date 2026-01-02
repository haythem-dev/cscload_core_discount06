#ifndef GUARD_DOMMOD_FMDDETERMINATIONPARAMETER_IFMDDETERMINATIONPARAMETERDM_H
#define GUARD_DOMMOD_FMDDETERMINATIONPARAMETER_IFMDDETERMINATIONPARAMETERDM_H

//-----------------------------------------------------------------------------------------

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

#include <libutil/accessor.h>

//-----------------------------------------------------------------------------------------

namespace fmdrelevantcalculator {
namespace domMod {
namespace fmddeterminationparameter {

class IFmdDeterminationParameterDM
{
public:
	virtual ~IFmdDeterminationParameterDM() {}

	virtual void                                                find				( ) = 0;
	virtual basar::db::aspect::AccessorPropertyTableRef         get					( ) = 0;
};

} 
} 
} 

#endif //end GUARD_DOMMOD_FMDDETERMINATIONPARAMETER_IFMDDETERMINATIONPARAMETERDM_H
