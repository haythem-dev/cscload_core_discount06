#ifndef GUARD_CSC_DELI_CSC_DELI_VERSION_H
#define GUARD_CSC_DELI_CSC_DELI_VERSION_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/classinfo.h>
#include <libutil/version.h>

//-------------------------------------------------------------------------------------------------//
// functions declaration section
//-------------------------------------------------------------------------------------------------//
namespace csc_deli
{
     const libutil::misc::Version&   getCsc_deliVersion();
     const char*                     getCsc_deliName();
     const libutil::misc::ClassInfo& getCsc_deliClassInfo();
}

#endif // GUARD_CSC_DELI_CSC_DELI_VERSION_H

