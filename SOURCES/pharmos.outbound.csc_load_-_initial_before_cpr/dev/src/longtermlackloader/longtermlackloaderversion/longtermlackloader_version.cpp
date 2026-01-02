//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       02.07.2014
 *  \version    00.00.00.01 first version
 */
//-------------------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "longtermlackloader_version.h"

//-------------------------------------------------------------------------------------------------//
// functions definition section
//-------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    const libutil::misc::Version& getLongtermlackloaderVersion()
    {
        static libutil::misc::Version longtermlackloaderVersion( 1, 1, 0, 0 );
        return longtermlackloaderVersion;
    }

    const char* getLongtermlackloaderName()
    {
        return "LONGTERMLACKLOADER";
    }

    const libutil::misc::ClassInfo& getLongtermlackloaderClassInfo()
    {
        static libutil::misc::ClassInfo longtermlackloaderClassInfo( getLongtermlackloaderName(), getLongtermlackloaderVersion() );
        return longtermlackloaderClassInfo;
    }
}
