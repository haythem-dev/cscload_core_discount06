#include "tcawrap.h"

#include <stdio.h>
#include <string.h>

#include <tcaapi.h>

#include "error.h"

//------------------------------------------------------------------------------
static const long noslot = -2;

// is logging enabled?
static int        logging
#ifdef NDEBUG	
						 = 0;
#else
						 = 1;
#endif

//------------------------------------------------------------------------------
static int isSession (long     slot,
		              ErrorMsg errmsg)
{
	LONG status;
	
	if (FALSE == tcACCESS_GetSessionStatus(&status, slot))
	{
		errorhandler(errmsg);
		return -1;
	}

	return (TCASS_SESSION_WITH_VM <= status) ? 1 : 0;	
}

//------------------------------------------------------------------------------
static int openSession(struct CicsConnParam * const pConnParam,
		               long * const                 pSlot     ,
		               ErrorMsg                     errmsg    )
 {
	BOOL     commError	   = FALSE;
	ULONG    errorCode	   = 0;
	char     custconn[128] = { 0 };
    ErrorMsg buf           = { 0 };

	// if values exist
	if ( pConnParam->ipaddr     && strlen(pConnParam->ipaddr    ) &&
		 pConnParam->port       && strlen(pConnParam->port      ) &&
		 pConnParam->starttrans && strlen(pConnParam->starttrans)    )
	{
		sprintf(custconn,
				"%s,%s,%s", 
				pConnParam->ipaddr,
				pConnParam->port,
				pConnParam->starttrans);
	}

	if (FALSE == TcaAllocateSession(
                    pSlot,						// slot
                    NULL,                       // parent
                    pConnParam->user,			// user ID
                    pConnParam->passwd,			// password 
                    NULL,						// password new 
                    ASF_FORCE_NO_LOGON_DIALOG | 
					ASF_ATTACH_SILENT         | 
					ASF_GET_HOST_APPLID,		// flags
				    pConnParam->config,			// connect configuration
					custconn,					// custom connect: ip, port, start transaction (VSE)
					&commError,					// communication error
					&errorCode,					// error code
					buf,						// error message
					sizeof(ErrorMsg)))			// buffer size of error message
	{
#ifndef WIN32
        snprintf(
#else
        _snprintf(
#endif
				 errmsg, sizeof(ErrorMsg) - 1,
                 "%s error 0x%0lx: %s",
			     commError ? "communication" : "application",
			     errorCode,
			     buf);
		return 0;
	}

	return 1;
}

//------------------------------------------------------------------------------
static int closeSession(struct CicsConnParam * const pConnParam,
		                ErrorMsg                     errmsg    )
{
    if (1 != isSession(pConnParam->slot, errmsg))
        return 1;

	if (FALSE == tcACCESS_DeallocateSession(pConnParam->slot,
				                            TCADS_ERROR_MESSAGES_ON_SCREEN,
											NULL))
	{
		errorhandler(errmsg);
		return 0;
	}

	return 1;
}

//------------------------------------------------------------------------------
void resetConnParam(struct CicsConnParam * const pConnParam)
{
	const char * const empty = "";
	
	strcpy(pConnParam->config    , empty);
	strcpy(pConnParam->ipaddr    , empty);
	strcpy(pConnParam->port      , empty);
	strcpy(pConnParam->starttrans, empty);
	strcpy(pConnParam->user      , empty);
	strcpy(pConnParam->passwd    , empty);
	strcpy(pConnParam->cicsname  , empty);

	pConnParam->slot = noslot;
	pConnParam->open = 0;
}

//------------------------------------------------------------------------------
void setConnParam (const char * const           config    ,
				   const char * const           ipaddr    ,
				   const char * const           port      ,
				   const char * const           starttrans,
				   const char * const           user      ,
				   const char * const           passwd    ,
				   struct CicsConnParam * const pConnParam)
{
	resetConnParam(pConnParam);

	strcpy(pConnParam->config    , config    );
	strcpy(pConnParam->ipaddr    , ipaddr    );
	strcpy(pConnParam->port      , port      );
	strcpy(pConnParam->starttrans, starttrans);
	strcpy(pConnParam->user      , user      );
	strcpy(pConnParam->passwd    , passwd    );
}

//------------------------------------------------------------------------------
long getConnSlot (const struct CicsConnParam * const pConnParam)
{
	return pConnParam->slot;
}

//------------------------------------------------------------------------------
const char * getConnCicsName (const struct CicsConnParam * const pConnParam)
{
	return pConnParam->cicsname;
}

//------------------------------------------------------------------------------
int	isConnOpen (const struct CicsConnParam * const pConnParam)
{
	return pConnParam->open;
}

//------------------------------------------------------------------------------
int openConn (struct CicsConnParam * const pConnParam,
		      ErrorMsg                     errmsg    )
{
	char msg[sizeof(ErrorMsg) + 256] = { 0 };
	long slot                        = noslot;
	
	strcpy(errmsg, "");

	logMsg("openConn(): enter", logging);
	
	if (isConnOpen(pConnParam))
	{
		sprintf(errmsg, "connection already opened, please close!"); 
		logMsg("openConn(): called isConnOpen() - failure: connection "
			   "already opened, please close", 
			   logging);
		
		return 0;
	}
	
	logMsg("openConn(): called isConnOpen() - success: connection is not opened", 
		   logging);

    if ( !openSession(pConnParam, &slot, errmsg) )
	{
		sprintf(msg, "openConn(): called openSession() - failure: %s",
				errmsg);
		logMsg(msg, logging);
		
		return 0;
	}

	logMsg("openConn(): called openSession() - success", logging);
	
	strcpy(pConnParam->cicsname, TcaGetHostApplId(slot));
	pConnParam->slot = slot;
	pConnParam->open = 1;

	sprintf(msg, 
			"openConn(): exit - success: connected to CICS %s via slot %ld "
			"(%s, %s, %s)",
			pConnParam->cicsname,
			pConnParam->slot,
			pConnParam->ipaddr,
			pConnParam->port,
			pConnParam->starttrans);
	logMsg(msg, logging);
	
	return 1;
}

//------------------------------------------------------------------------------
int closeConn (struct CicsConnParam * const pConnParam,
		       ErrorMsg                     errmsg    )
{
	char msg[sizeof(ErrorMsg) + 256] = { 0 };
	
	strcpy(errmsg, "");
	
	logMsg("closeConn(): enter", logging);
	
	if ( !isConnOpen(pConnParam) )
	{
		strcpy(errmsg, "connection not opened!"); 
		sprintf(msg   , "closeConn(): called isConnOpen() - failure: %s",
		        errmsg);
		logMsg(msg, logging);

		return 0;
	}

	logMsg("closeConn(): called isConnOpen() - success", logging);
		
	if ( !closeSession(pConnParam, errmsg) )
	{
		sprintf(msg, "closeConn(): called closeSession() - failure: %s",
				errmsg);
		logMsg(msg, logging);
		
		return 0;
	}
			
	logMsg("closeConn(): called closeSession() - success", logging);

	strcpy(pConnParam->cicsname, "");
	pConnParam->slot = noslot;
	pConnParam->open = 0;

	logMsg("closeConn(): exit - success", logging);
	
	return 1;
}

