#ifndef GUARD_CSC_PHADEX_DOMMOD_I_NARCOTICS_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_I_NARCOTICS_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace narcotics
{
    class INarcotics;
    typedef boost::shared_ptr< csc_phadex::domMod::narcotics::INarcotics > INarcoticsPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_I_NARCOTICS_PTR_H
