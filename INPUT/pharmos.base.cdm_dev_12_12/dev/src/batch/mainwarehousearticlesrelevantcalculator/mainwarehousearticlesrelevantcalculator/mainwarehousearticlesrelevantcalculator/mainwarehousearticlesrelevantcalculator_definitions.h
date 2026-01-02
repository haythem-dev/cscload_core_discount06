//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       14.02.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DEFINITIONS_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DEFINITIONS_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <libutil/classinfo.h>
#include <libutil/version.h>

#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
    static const char* const MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_APPLICATION_NAME = "MAINWAREHOUSEARTICLESRELEVANTCALCULATOR";
    static const libutil::misc::Version MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_APPLICATION_VERSION( 1, 0, 0, 0 );
    static const libutil::misc::ClassInfo APPLICATION_INFO( MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_APPLICATION_NAME, MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_APPLICATION_VERSION );

    namespace version
    {
        static const libutil::misc::Version BASAR_VERSION      ( 1, 9, 0, 0 );      // should be offered by the lib BASAR itself
    }

}

#endif
