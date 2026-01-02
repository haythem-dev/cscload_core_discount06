#ifndef GUARD_LIBCSC_DELI_LIBCSC_DELI_VERSION_H
#define GUARD_LIBCSC_DELI_LIBCSC_DELI_VERSION_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/classinfo.h>
#include <libutil/version.h>

//-------------------------------------------------------------------------------------------------//
// functions declaration section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
     const libutil::misc::Version&   getLibCsc_deliVersion();
     const libutil::misc::ClassInfo& getLibCsc_deliClassInfo();
     const char*                     getLibCsc_deliName();
}

#endif
