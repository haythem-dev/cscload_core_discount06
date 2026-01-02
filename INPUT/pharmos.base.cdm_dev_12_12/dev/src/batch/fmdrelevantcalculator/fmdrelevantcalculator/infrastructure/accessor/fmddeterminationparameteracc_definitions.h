#ifndef GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_FMDDETERMINATIONPARAMETERACC_DEFINITIONS_H
#define GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_FMDDETERMINATIONPARAMETERACC_DEFINITIONS_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil_parameterlist.h>
#include <libbasarproperty_propertydescription.h>

//----------------------------------------------------------------------------//
// lit definition section
//----------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    namespace infrastructure
    {
        namespace accessor
        {
            namespace fmddeterminationparameter
            {
                namespace lit
                {
                    const basar::VarString FMD_DETERMINATION_CRITERIA_ACC			    ( "AccFmdDeterminationCriteria" );
                    const basar::VarString SELECT_FMD_DETERMINATION_PARAM				( "SelectFmdDeterminationParam"	);
                }
            }
        }
    }   // end namespace infrastructure
}

#endif //GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_FMDDETERMINATIONPARAMETERACC_DEFINITIONS_H
