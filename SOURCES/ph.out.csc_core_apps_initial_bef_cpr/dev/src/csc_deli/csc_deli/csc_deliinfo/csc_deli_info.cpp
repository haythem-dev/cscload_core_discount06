//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "csc_deli_info.h"

//-------------------------------------------------------------------------------------------------//
// functions definition section
//-------------------------------------------------------------------------------------------------//
namespace csc_deli
{
    const libutil::misc::Version& getCsc_deliVersion()
    {
        static libutil::misc::Version csc_deliVersion( 1, 1, 0, 0 );
        return csc_deliVersion;
    }

    const char* getCsc_deliName()
    {
        return "CSC_DELI";
    }

    const libutil::misc::ClassInfo& getCsc_deliClassInfo()
    {
        static libutil::misc::ClassInfo csc_deliClassInfo( getCsc_deliName(), getCsc_deliVersion() );
        return csc_deliClassInfo;
    }
}
