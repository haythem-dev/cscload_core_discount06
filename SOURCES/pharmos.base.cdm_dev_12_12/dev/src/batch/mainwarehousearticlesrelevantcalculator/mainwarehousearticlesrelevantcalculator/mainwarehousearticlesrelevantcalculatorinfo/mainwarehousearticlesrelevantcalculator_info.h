#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_VERSION_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_VERSION_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/classinfo.h>
#include <libutil/version.h>

//-------------------------------------------------------------------------------------------------//
// functions declaration section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
     const libutil::misc::Version&   getMainwarehousearticlesrelevantcalculatorVersion();
     const char*                     getMainwarehousearticlesrelevantcalculatorName();
     const libutil::misc::ClassInfo& getMainwarehousearticlesrelevantcalculatorClassInfo();
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_VERSION_H
