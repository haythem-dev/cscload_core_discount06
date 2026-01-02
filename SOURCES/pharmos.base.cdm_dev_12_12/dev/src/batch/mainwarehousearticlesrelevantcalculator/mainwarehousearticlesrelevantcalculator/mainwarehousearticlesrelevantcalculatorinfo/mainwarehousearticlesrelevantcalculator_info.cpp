//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "mainwarehousearticlesrelevantcalculator_info.h"

/*******************************************************************************************/
/*!
\page page36 mainwarehousearticlesrelevantcalculator

________________________________________________________________________________________
\version 01.01.00.00
\date 2021-10-20
\internal
- (WH) second shot \_/ :) -> added new rules undeliveryquota, regionalarticle
\endinternal
\version 01.00.00.00
\date 2016-12-31
\internal
- (MM) first shot
\endinternal

*/

//-------------------------------------------------------------------------------------------------//
// functions definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
    const libutil::misc::Version& getMainwarehousearticlesrelevantcalculatorVersion()
    {
        static libutil::misc::Version mainwarehousearticlesrelevantcalculatorVersion( 1, 1, 0, 0 );
        return mainwarehousearticlesrelevantcalculatorVersion;
    }

    const char* getMainwarehousearticlesrelevantcalculatorName()
    {
        return "MAINWAREHOUSEARTICLESRELEVCALC";
    }

    const libutil::misc::ClassInfo& getMainwarehousearticlesrelevantcalculatorClassInfo()
    {
        static libutil::misc::ClassInfo mainwarehousearticlesrelevantcalculatorClassInfo( getMainwarehousearticlesrelevantcalculatorName(), getMainwarehousearticlesrelevantcalculatorVersion() );
        return mainwarehousearticlesrelevantcalculatorClassInfo;
    }
}
