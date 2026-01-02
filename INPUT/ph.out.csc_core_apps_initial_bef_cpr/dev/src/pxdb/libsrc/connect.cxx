/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: connect.sqc


    FUNCTIONS:

        long     pxSQLCode()     get current SQL Errorcode
        char   * pxSQLMessage()  get current SQL Message
        int      pxFunctionNr()  get number of most recent Function
        pxConnect()    Connect to SQL-Server DATABASE


REVISION HISTORY

07 Jun 1995 V1.00 REV 00 written by Dietmar Schloetel

*/

#include <pxenv.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "pxdbfunc.h"

/* GLOBAL VARIABLES */

int   functionnr = 0;       /* Number of the most recent SQL table access */
#define HOST_VAR_LEN		128

long pxSQLCode()
{
    functionnr = F_SQLCode;
    return SQLCODE;
}

long pxISAMCode()
{
    long  isamcode;
	functionnr = F_SQLCode;
	isamcode   = sqlca.sqlerrd[1];
    return isamcode;
}

char errmsg[200];
char * pxSQLMessage()
{
    char errmsg1[80];
    int msg_len;

    functionnr = F_SQLMessage;          /* Store function number */

    rgetlmsg(SQLCODE,errmsg1,sizeof(errmsg1),&msg_len);
    sprintf(errmsg,errmsg1,sqlca.sqlerrm);
    return errmsg;
}


int   pxFunctionNr()
{
    return functionnr;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxConnect()                                            */
/*                                                                   */
/*      Connect to database                                          */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      database - server.database name                              */
/*      user     - user.password                                     */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxConnect()
{
	functionnr = F_Connect;
	return 0;
}
	
void pxSetCurrentDb (const char * const pConnId)
{
	EXEC SQL begin declare section;
	char h_ConnId[HOST_VAR_LEN];
	EXEC SQL end declare section;
	
	assert(strlen(pConnId) < HOST_VAR_LEN);
	assert(strlen(pConnId) > 0);
	
	strcpy(h_ConnId, pConnId);

	EXEC SQL set connection :h_ConnId;
}
