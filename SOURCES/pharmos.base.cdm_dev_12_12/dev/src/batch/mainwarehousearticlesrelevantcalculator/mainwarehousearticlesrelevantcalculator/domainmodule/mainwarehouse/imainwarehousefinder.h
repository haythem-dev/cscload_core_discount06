#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_MAINWAREHOUSE_IMAINWAREHOUSEFINDER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_MAINWAREHOUSE_IMAINWAREHOUSEFINDER_H

#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace mainwarehouse
{
    class IMainwarehouseFinder
    {
    public:
        virtual ~IMainwarehouseFinder() {}

        virtual void         findByBranchNo( basar::Int16 ) = 0;
        virtual basar::Int16 getMainwarehouseBranch() const = 0;
    };

} // end namespace mainwarehouse
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_MAINWAREHOUSE_IMAINWAREHOUSEFINDER_H
