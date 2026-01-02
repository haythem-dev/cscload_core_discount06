#ifndef GUARD_DOMMOD_EXPORTEXCLUSIONPARAMETER_IEXPORTEXCLUSIONPARAMETERDM_H
#define GUARD_DOMMOD_EXPORTEXCLUSIONPARAMETER_IEXPORTEXCLUSIONPARAMETERDM_H

//-----------------------------------------------------------------------------------------

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

#include <libutil/accessor.h>

//-----------------------------------------------------------------------------------------

namespace exportarticlecalculator {
namespace domMod {
namespace exportexclusionparameter {

class IExportExclusionParameterDM
{
public:
	virtual ~IExportExclusionParameterDM() {}

	virtual void                                                find				( ) = 0;
	virtual basar::db::aspect::AccessorPropertyTableRef         get					( ) = 0;

	virtual basar::Int16										getBranchNo			( ) = 0;
	virtual basar::VarString									getCountry			( ) = 0;
};

} 
} 
} 

#endif //end GUARD_DOMMOD_EXPORTEXCLUSIONPARAMETER_IEXPORTEXCLUSIONPARAMETERDM_H
