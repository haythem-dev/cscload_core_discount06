#ifndef GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_ACCESSOR_EXPORTEXCLUSIONPARAMETERACC_DEFINITIONS_H
#define GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_ACCESSOR_EXPORTEXCLUSIONPARAMETERACC_DEFINITIONS_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil_parameterlist.h>
#include <libbasarproperty_propertydescription.h>

//----------------------------------------------------------------------------//
// lit definition section
//----------------------------------------------------------------------------//
namespace exportarticlecalculator
{
    namespace infrastructure
    {
        namespace accessor
        {
            namespace exportexclusionparameter
            {
                namespace lit
                {
                    const basar::VarString EXPORT_EXCLUSION_CRITERIA_ACC			( "AccExportExclusionCriteria"       );
                    const basar::VarString SELECT_EXPORT_EXCLUSION_PARAM_BY_COUNTRY	( "SelectExportExclusionParamByCountryBranch"	);
                }
            }
        }
    }   // end namespace infrastructure
}

#endif //GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_ACCESSOR_EXPORTEXCLUSIONPARAMETERACC_DEFINITIONS_H
