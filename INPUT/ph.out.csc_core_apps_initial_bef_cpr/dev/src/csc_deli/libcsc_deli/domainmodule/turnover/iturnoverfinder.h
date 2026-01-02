#ifndef GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ITURNOVERFINDER_H
#define GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ITURNOVERFINDER_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
            class AccessorPropertyTableRef;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// interface class definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace turnover
{
    class ITurnoverFinder
    {
    public:
        virtual ~ITurnoverFinder() {}

        virtual void                                                findByPartnerNo( basar::Int32 partnerNo ) = 0;

        virtual basar::Decimal                                      getTurnoverDay()     const = 0;
        virtual basar::Decimal                                      getTurnoverMonth()   const = 0;
        virtual basar::Decimal                                      getSumReclamations() const = 0;
        virtual basar::Decimal                                      getSumReturns()      const = 0;
    };

} // end namespace turnover
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ITURNOVERFINDER_H
