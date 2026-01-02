/*****************************************************************************/
/*                                                                           */
/*   header     : errorinternlog.c                                           */
/*   Author     : A. Schmidt-Rehschuh (644)                                  */
/*   made       : 22.08.2001                                                 */
/*   language   : c                                                          */
/*                                                                           */
/*   only needed for dade-batch (different using of WriteLog + WriteLogInfo) */
/*                                                                           */
/*****************************************************************************/

/*** include *****************************************************************/

#include "errorlog.h"
#include "libtpld/logfile.h"
#include <stdio.h>

/*** WriteLogInfo ************************************************************/

void WriteLogInfo( char *error_msg, int rc, int errno )
{
    WriteLog( " ", rc, "%s (%d)", error_msg, errno);
	return;
}
