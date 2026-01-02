#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_BINLOCATIONRANGE_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_BINLOCATIONRANGE_H

#include "irelevantrule.h"

#include "infrastructure/interval/interval.hpp"
#include <libbasarcmnutil_bstring.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    class BinLocationRange : public IRelevantRule
    {
    public:
        typedef Interval< basar::VarString > StringInterval;

        BinLocationRange( const StringInterval& );
        ~BinLocationRange();

        // from IRelevantRule interface
        RuleDescription                                 getDescription() const;
        infrastructure::dataType::Trilean               isRelevant( infrastructure::dataProvider::IDataProviderPtr ) const;

    private:
        // forbidden
        BinLocationRange();

    private:
        StringInterval                                  m_BinLocationRange;
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_BINLOCATIONRANGE_H
