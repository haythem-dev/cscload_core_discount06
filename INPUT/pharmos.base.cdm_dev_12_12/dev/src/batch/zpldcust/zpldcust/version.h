/*!
\page page24 zpldcust
___________________________________________________________________________
\version	01.01.00.01
\date		2013-08-19
\internal
- return 0 to start_process also if there is an info.
\endinternal
___________________________________________________________________________
\version	01.01.00.00
\date		2013-03-19
\internal
- AIX build.
\endinternal
___________________________________________________________________________
\version	01.00.00.03
\date		2012-08-15
\internal
- bugfix INC-030998: wenn VFIL gefüllt, dann Neuanlagen mit dieser branchno.
\endinternal
___________________________________________________________________________
\version	01.00.00.02
\date		2010-06-07
\internal
- bugfix in shell script "zpldcust.sh" (mode parameter not passed to binary).
- Log4cplus logging improved.
\endinternal
___________________________________________________________________________
\version	01.00.00.01
\date		2010-06-02
\internal
- Program exit code <> 0 when error occurs (for APX). Update to SSUK 01.08.01.00
\endinternal
___________________________________________________________________________
\version	01.00.00.00
\date		2010-04-30
\internal
- log4cplus logging improved.
- Login user changed from gi.batch to zdp.batch.
- Application key changed from CDM to ZDP.</LI>
- Bugfix: comparison cics plz <-> db plz (int32 <-> string).
- Initial version.
\endinternal

*/


/******************************************************************************************/
/*! \file   version.h
 *  \brief  Version file for zpldcust.
 *  \author Frank Naumann
 *  \date   25.03.2010

 ******************************************************************************************
 *  \version 01.01.00.01 - 2013-08-19
 *           <UL>
 *             <LI>return 0 to start_process also if there is an info.</LI>
 *           </UL>

 ******************************************************************************************
 *  \version 01.01.00.00 - 2013-03-19
 *           <UL>
 *             <LI>AIX build.</LI>
 *           </UL>

 ******************************************************************************************
 *  \version 01.00.00.03 - 2012-08-15
 *           <UL>
 *             <LI>bugfix INC-030998: wenn VFIL gefüllt, dann Neuanlagen mit dieser branchno.</LI>
 *           </UL>

 ******************************************************************************************
 *  \version 01.00.00.02 - 2010-06-07
 *           <UL>
 *             <LI>bugfix in shell script "zpldcust.sh" (mode parameter not passed to binary).</LI>
 *             <LI>log4cplus logging improved.</LI>
 *           </UL>

 ******************************************************************************************
 *  \version 01.00.00.01 - 2010-06-02
 *           <UL>
 *             <LI>program exit code <> 0 when error occurs (for APX).</LI>
 *             <LI>Update to SSUK 01.08.01.00</LI>
 *           </UL>

 ******************************************************************************************
 *  \version 01.00.00.00 - 2010-04-30
 *           <UL>
 *             <LI>log4cplus logging improved.</LI>
 *             <LI>Login user changed from gi.batch to zdp.batch.</LI>
 *             <LI>Application key changed from CDM to ZDP.</LI>
 *             <LI>Bugfix: comparison cics plz <-> db plz (int32 <-> string).</LI>
 *             <LI>Initial version.</LI>
 *           </UL>

 ******************************************************************************************/

#ifndef __VERSION_H
#define __VERSION_H

//---------------------------------------------------------------------------------------------------

#define APPLICATION_NAME "zpldcust" //!< The application name of zpldcust.

#define VERSION_MAJORNO   1        //!< The major version number of zpldcust.
#define VERSION_MINORNO   1        //!< The minor version number of zpldcust.
#define VERSION_EXTENSION 0        //!< The extension version number of zpldcust.
#define VERSION_BUILDNO   1        //!< The build version number of zpldcust.

//---------------------------------------------------------------------------------------------------

#endif // __VERSION_H

//---------------------------------------------------------------------------------------------------
