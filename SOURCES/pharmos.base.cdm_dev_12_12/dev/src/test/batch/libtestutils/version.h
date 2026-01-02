//----------------------------------------------------------------------------
/*! \file
 *  \brief   version  
 *  \author  Anke Klink
 *  \date    2009
 *
 *  \version 01.00.00.00   
 */
//----------------------------------------------------------------------------

#ifndef GUARD_LIBTESTUTILS_VERSION_H
#define GUARD_LIBTESTUTILS_VERSION_H

//----------------------------------------------------------------------------
//! major version number
#define VERSION_MAJORNO				"01"

//! minor version number
#define VERSION_MINORNO				"00"

//! sprint version number
#define VERSION_EXTENSION			"01"

//! revision version number
#define VERSION_BUILDNO				"00"

//! compound version string
#define VERSIONNO					VERSION_MAJORNO   "." \
									VERSION_MINORNO   "." \
									VERSION_EXTENSION "." \
									VERSION_BUILDNO

//! component name
#define PROGRAM_NAME				"libtestutils"

//! component description
#define FILEDESCRIPTION				"the library consists of main utility classes for unittest."

//----------------------------------------------------------------------------
/*! \ingroup DIFF_DBG_REL */  
#ifdef NDEBUG
//! release version number
#define VERSION_NUMBER				VERSIONNO" rel"
#else
//! debug version number   
#define VERSION_NUMBER				VERSIONNO" dbg"
#endif

/*! \ingroup DIFF_WIN_UNIX */  
#ifdef WIN32
//! windows file name
#define FILE_NAME					PROGRAM_NAME ".lib"
#else
//! unix file name
#define FILE_NAME					PROGRAM_NAME ".a"
#endif


//----------------------------------------------------------------------------
#endif	// GUARD
