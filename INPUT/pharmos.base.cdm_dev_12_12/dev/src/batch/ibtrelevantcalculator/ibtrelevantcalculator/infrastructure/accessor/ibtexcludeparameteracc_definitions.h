#ifndef GUARD_IBTRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_IBTEXCLUDEPARAMETERACC_DEFINITIONS_H
#define GUARD_IBTRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_IBTEXCLUDEPARAMETERACC_DEFINITIONS_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil_parameterlist.h>
#include <libbasarproperty_propertydescription.h>

//----------------------------------------------------------------------------//
// lit definition section
//----------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace infrastructure
    {
        namespace accessor
        {
            namespace ibtexcludeparameter
            {
                namespace lit
                {
                    const basar::VarString IBT_EXCLUSION_CRITERIA_ACC			( "AccPuIbtExclusionCriteria"       );
                    const basar::VarString SELECT_IBT_EXCLUDE_PARAM_BY_BRANCH	( "SelectIbtExcludeParamByBranch"	);
                }
            }
        }
    }   // end namespace infrastructure
}

#endif //GUARD_IBTRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_IBTEXCLUDEPARAMETERACC_DEFINITIONS_H
