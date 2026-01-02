//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       02.07.2014
 *  \version    00.00.00.01 first version
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_LONGTERMLACKLOADER_LONGTERMLACKLOADER_VERSION_H
#define GUARD_LONGTERMLACKLOADER_LONGTERMLACKLOADER_VERSION_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/classinfo.h>
#include <libutil/version.h>

//-------------------------------------------------------------------------------------------------//
// functions declaration section
//-------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
     const libutil::misc::Version&   getLongtermlackloaderVersion();
     const char*                     getLongtermlackloaderName();
     const libutil::misc::ClassInfo& getLongtermlackloaderClassInfo();
}

#endif
