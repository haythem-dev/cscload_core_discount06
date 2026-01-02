/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-2000 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: rartikel.c (.sqc)

    Database functions for remote database




    FUNCTIONS:

        pxRArtikelReadLock     get one record with lock
        pxRArtikelUpdate       Update record


REVISION HISTORY

11 Jun 1999 V1.00 REV 00 written by Dietmar Schloetel

*/
/*  $History: rartikel.sqc.ksc $
 *  */

#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include "tartvza.h"

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRArtikelRead                                         */
/*                                                                   */
/*      Get one record from remote database                          */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*      computer name                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxRArtikelRead
(
    struct tFARTIKEL* record,
    char  * computer
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLOKAL * recordp;
    char myquery[256];
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLOKAL * 10 + F_ReadLock;
    recordp = (struct C_ARTIKELLOKAL *) record;

    strcpy(myquery,"select ");
    strcat(myquery,"bestand,");
    strcat(myquery,"bestandreserviert,");
    strcat(myquery,"artikelaktiv,");
    strcat(myquery,"verbundartikel,");
    strcat(myquery,"kontigentmenge ");
    strcat(myquery, "from ");
    strcat( myquery,computer);
    strcat( myquery,":artikellokal ");
    strcat( myquery,"where artikel_nr = ?");
    strcat( myquery," and filialnr = ?");
    strcat ( myquery," ;");

   exec sql prepare readquery from :myquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql declare rartikel_u2 cursor with hold for readquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql open rartikel_u2 using :recordp->ARTIKEL_NR,:recordp->FILIALNR;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql fetch rartikel_u2 into
		:recordp->BESTAND,
		:recordp->BESTANDRESERVIERT,
		:recordp->ARTIKELAKTIV,
		:recordp->VERBUNDARTIKEL,
		:recordp->KONTIGENTMENGE;

	if (SQLCODE != 0)
       return cDBXR_IOERROR;

    if (SQLCODE == 0)
    {
       /*exec sql close rartikel_u2;*/
       exec sql free readquery;
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          exec sql close rartikel_u2;
          exec sql free readquery;
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
       {
          exec sql close rartikel_u2;
          exec sql free readquery;
          return cDBXR_NOTFOUND;
       }
       exec sql close rartikel_u2;
       exec sql free readquery;
       return cDBXR_IOERROR;
    }
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRArtikelReadLock                                     */
/*                                                                   */
/*      Get one record with lock from remote database                */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*      computer name                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxRArtikelReadLock
(
    struct tFARTIKEL* record,
    char  * computer
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLOKAL * recordp;
    char myquery[256];
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLOKAL * 10 + F_ReadLock;
    recordp = (struct C_ARTIKELLOKAL *) record;

    strcpy(myquery,"select ");
    strcat(myquery,"bestand,");
    strcat(myquery,"bestandreserviert,");
    strcat(myquery,"artikelaktiv,");
    strcat(myquery,"verbundartikel,");
    strcat(myquery,"kontigentmenge ");
    strcat(myquery, "from ");
    strcat( myquery,computer);
    strcat( myquery,":artikellokal ");
    strcat( myquery,"where artikel_nr = ?");
    strcat( myquery," and filialnr = ?");
    strcat ( myquery," for update");
    strcat ( myquery," ;");

    exec sql prepare readlockquery from :myquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql declare rartikel_u1 cursor with hold for readlockquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql open rartikel_u1 using :recordp->ARTIKEL_NR,:recordp->FILIALNR;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql fetch rartikel_u1 into
		:recordp->BESTAND,
		:recordp->BESTANDRESERVIERT,
		:recordp->ARTIKELAKTIV,
		:recordp->VERBUNDARTIKEL,
		:recordp->KONTIGENTMENGE;

	if (SQLCODE != 0)
       return cDBXR_IOERROR;

    if (SQLCODE == 0)
    {
       /*exec sql close rartikel_u1;*/
       exec sql free readlockquery;
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          exec sql close rartikel_u1;
          exec sql free readlockquery;
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
       {
          exec sql close rartikel_u1;
          exec sql free readlockquery;
          return cDBXR_NOTFOUND;
       }
       exec sql close rartikel_u1;
       exec sql free readlockquery;
       return cDBXR_IOERROR;
    }
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRArtikelUpdate                                       */
/*                                                                   */
/*      Update  record  in remote database                           */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxRArtikelUpdate
(
    struct tFARTIKEL* record,
    char  * computer
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_ARTIKELLOKAL * recordp;
    char myquery[256];
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELLOKAL * 10 + F_Update;
    recordp = (struct C_ARTIKELLOKAL *) record;

    strcpy( myquery,"update ");
    strcat( myquery,computer);
    strcat( myquery,":artikellokal ");
    strcat( myquery,"set ");
    strcat( myquery,"bestand = ?, ");
    strcat( myquery,"bestandreserviert = ? ");
    strcat( myquery,"where artikel_nr = ? ");
    strcat( myquery,"and filialnr = ?");
    strcat( myquery," ;");

    exec sql prepare  updquery from :myquery;

	if (SQLCODE == 0)
	{
		exec sql execute  updquery using
			:recordp->BESTAND,
			:recordp->BESTANDRESERVIERT,
			:recordp->ARTIKEL_NR,
			:recordp->FILIALNR;
	}
    if (SQLCODE == 0)
    {
       exec sql close rartikel_u1;
       exec sql free  updquery;
       return 0;
    }
    else
    {
       exec sql close rartikel_u1;
       exec sql free  updquery;
       return cDBXR_IOERROR;
    }
}
