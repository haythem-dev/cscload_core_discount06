//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "libcsc_deli_info.h"

//-------------------------------------------------------------------------------------------------//
// functions definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
    const libutil::misc::Version& getLibCsc_deliVersion()
    {
        static libutil::misc::Version libCsc_deliVersion( 1, 0, 0, 0 );
        return libCsc_deliVersion;
    }

    const char* getLibCsc_deliName()
    {
        return "Library LIBCSC_DELI";
    }

    const libutil::misc::ClassInfo& getLibCsc_deliClassInfo()
    {
        static libutil::misc::ClassInfo libCsc_deliClassInfo( getLibCsc_deliName(), getLibCsc_deliVersion() );
        return libCsc_deliClassInfo;
    }
}
