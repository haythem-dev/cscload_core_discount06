#ifndef GUARD_LIBCSC_DELI_DOMMOD_TURNOVERDM_DEFINITIONS_H
#define GUARD_LIBCSC_DELI_DOMMOD_TURNOVERDM_DEFINITIONS_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasar_definitions.h>

//----------------------------------------------------------------------------//
// namespace section
//----------------------------------------------------------------------------//
namespace libcsc_deli
{
    namespace domMod
    {
        namespace turnover
        {
            // a few text key combinations (properties::TEXT_KEY)
            const basar::VarString keyReturns      = "20";
            const basar::VarString keyReclamations = "21";

            // doctype
            const basar::Int16 docTypeTurnover     = 1;
            const basar::Int16 docTypeReturns      = 2;
        }
    }
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_TURNOVERDM_DEFINITIONS_H
