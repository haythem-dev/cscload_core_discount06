#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITMAILPROCESSOR_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITMAILPROCESSOR_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// interface declaration section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace debtLimit
{
    class IDebtLimitMailProcessor
    {
    public:
        virtual ~IDebtLimitMailProcessor() {}

        // from interface
        virtual void                                                processCremaMails( basar::Int32 partnerNo ) = 0;
    };

} // end namespace debtLimit
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITMAILPROCESSOR_H
