#include "tcawrap.h"

#include <tcaapi.h>
#include <stdio.h>
#include <time.h>
#ifndef WIN32
#include <unistd.h>
#else
#include <process.h>
 #endif

//------------------------------------------------------------------------------
void errorhandler(ErrorMsg errmsg)
{
	CHAR       buffer[sizeof(ErrorMsg)] = { 0 };
	BOOL       isCommError;
	ULONG      errorCode;

    tcACCESS_GetLastError(&isCommError, &errorCode, buffer, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

#ifdef WIN32
	_snprintf(
#else
	snprintf(
#endif
	errmsg, sizeof(ErrorMsg),
			 "%s error 0x%0lx: %s",
			 isCommError ? "communication" : "application",
			 errorCode,
			 buffer);
}

//------------------------------------------------------------------------------
static void getTimestamp(char * const stamp )
{
	time_t      lmSec = time(0);
	struct tm * ptrTm = localtime( &lmSec );

	sprintf( stamp, 
			"%04d-%02d-%02d %02d:%02d:%02d", 
			ptrTm->tm_year+1900,
			ptrTm->tm_mon + 1, 
			ptrTm->tm_mday, 
			ptrTm->tm_hour, 
			ptrTm->tm_min, 
			ptrTm->tm_sec );
}

//------------------------------------------------------------------------------
void logMsg	(const char * const msg,
		     int                enable)
{
	if (enable == 0)
		return;
	
	static const char * const logfile = "/tmp/tcawrap.log";
	
	FILE * pLog       = NULL;
	char   line[2048] = { 0 };

    if ( ( pLog = fopen( logfile, "a" ) ) == NULL )
      return;

	char timestamp[128] = { 0 };
	getTimestamp(timestamp);

#ifdef WIN32
	_snprintf(
#else
	snprintf(
#endif
			 line, sizeof(line), 
			 "%s pid=%05d: %s\n", 
             timestamp,
#ifdef WIN32
			_getpid(),
#else
             getpid(),
#endif
             msg);

    fprintf(pLog, line);

	fclose( pLog );
}

