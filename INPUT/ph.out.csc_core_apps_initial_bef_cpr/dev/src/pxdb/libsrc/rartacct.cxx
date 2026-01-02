
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include "tartacct.h"
#include "pxdbfunc.h"
#include <ndefs.h>

/* Global variables */
extern int  functionnr;


/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRArtikelKontoRead                                    */
/*                                                                   */
/*      Get one record                                               */
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

int pxRArtikelKontoRead
(
    struct tARTIKELKONTO* record,
    const char* computer
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tARTIKELKONTO* recordp;
    char myquery[256];
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELKONTO * 10 + F_Read;
    recordp = record;

    strcpy( myquery,"SELECT ");
    strcat( myquery,"LFDNR, FILIALNR, ARTIKEL_NR, BEWEGUNGSART, MENGE, "
                    "BELEGNR, UID, IDFNR, MENGENEU, ZEITUNIX, BEWEGUNGSCHLUESSEL, STOCKRESERVED, MOVETYPE, POSNR, BELEGART");
    strcat( myquery," FROM ");
    strcat( myquery,computer);
    strcat( myquery,":ARTIKELKONTO ");
    strcat( myquery,"WHERE LFDNR = ?");
    strcat( myquery," ;");

    exec sql prepare thisquery from :myquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql declare rartacct_r1 cursor for thisquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql open rartacct_r1 using :recordp->LfdNr;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql fetch rartacct_r1 into
		:recordp->LfdNr,
        :recordp->FilialNr,
        :recordp->ArtikelNr,
        :recordp->BewegungsArt,
        :recordp->Menge,
        :recordp->BelegNr,
        :recordp->Uid,
        :recordp->IDFNr,
        :recordp->MengeNeu,
        :recordp->ZeitUnix,
        :recordp->BewegungSchluessel,
        :recordp->StockReserved,
        :recordp->MoveType,
        :recordp->PosNr,
        :recordp->BelegArt;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    if (SQLCODE == 0)
    {
       exec sql close rartacct_r1;
       exec sql free thisquery;
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          exec sql close rartacct_r1;
          exec sql free thisquery;
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
       {
          exec sql close rartacct_r1;
          exec sql free thisquery;
          return cDBXR_NOTFOUND;
       }
       exec sql close rartacct_r1;
       exec sql free thisquery;
       return cDBXR_IOERROR;
    }
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRArtikelKontoReadLock                                */
/*                                                                   */
/*      Get one record with lock                                     */
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
int pxRArtikelKontoReadLock
(
    struct tARTIKELKONTO* record,
    const char* computer
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tARTIKELKONTO * recordp;
    char myquery[256];
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELKONTO * 10 + F_ReadLock;
    recordp = record;

    strcpy( myquery,"select ");
    strcat( myquery,"LFDNR, FILIALNR, ARTIKEL_NR, BEWEGUNGSART, MENGE, "
                    "BELEGNR, UID, IDFNR, MENGENEU, ZEITUNIX, BEWEGUNGSCHLUESSEL, STOCKRESERVED, MOVETYPE, POSNR, BELEGART");
    strcat( myquery," from ");
    strcat( myquery,computer);
    strcat( myquery,":artikelkonto ");
    strcat( myquery,"where LFDNR = ?");
    strcat( myquery," for update");
    strcat( myquery," ;");

    exec sql prepare thisquery1 from :myquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql declare rartacct_r2 cursor           for thisquery1;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql open rartacct_r2 using :recordp->LfdNr;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql fetch rartacct_r2 into
		:recordp->LfdNr,
        :recordp->FilialNr,
        :recordp->ArtikelNr,
        :recordp->BewegungsArt,
        :recordp->Menge,
        :recordp->BelegNr,
        :recordp->Uid,
        :recordp->IDFNr,
        :recordp->MengeNeu,
        :recordp->ZeitUnix,
        :recordp->BewegungSchluessel,
        :recordp->StockReserved,
        :recordp->MoveType,
        :recordp->PosNr,
        :recordp->BelegArt;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    if (SQLCODE == 0)
    {
       /*exec sql close rartacct_r2;*/
       exec sql free thisquery1;
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          exec sql close rartacct_r2;
          exec sql free thisquery1;
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
       {
          exec sql close rartacct_r2;
          exec sql free thisquery1;
          return cDBXR_NOTFOUND;
       }
       exec sql close rartacct_r2;
       exec sql free thisquery1;
       return cDBXR_IOERROR;
    }
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRArtikelKontoUpdate                                  */
/*                                                                   */
/*      Update  record                                               */
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

int pxRArtikelKontoUpdate
(
    struct tARTIKELKONTO* record,
    const char* computer
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tARTIKELKONTO * recordp;
    char myquery[256];
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELKONTO * 10 + F_Update;
    recordp = record;

    strcpy( myquery,"UPDATE ");
    strcat( myquery,computer);
    strcat( myquery,":ARTIKELKONTO ");
    strcat( myquery," SET ");
    strcat( myquery,"LFDNR = ?,");
    strcat( myquery,"FILIALNR = ?,");
    strcat( myquery,"ARTIKEL_NR = ?,");
    strcat( myquery,"BEWEGUNGSART = ?,");
    strcat( myquery,"MENGE = ?,");
    strcat( myquery,"BELEGNR = ?,");
    strcat( myquery,"UID = ?,");
    strcat( myquery,"IDFNR = ?,");
    strcat( myquery,"MENGENEU = ?,");
    strcat( myquery,"ZEITUNIX = ?,");
    strcat( myquery,"BEWEGUNGSCHLUESSEL = ?,");
    strcat( myquery,"STOCKRESERVED = ?,");
    strcat( myquery,"MOVETYPE = ?,");
    strcat( myquery,"POSNR = ?,");
    strcat(myquery, "BELEGART = ? ");
    strcat( myquery,"WHERE LFDNR = ?");

    exec sql prepare thisquery2 from :myquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql execute thisquery2 using
		:recordp->LfdNr,
        :recordp->FilialNr,
        :recordp->ArtikelNr,
        :recordp->BewegungsArt,
        :recordp->Menge,
        :recordp->BelegNr,
        :recordp->Uid,
        :recordp->IDFNr,
        :recordp->MengeNeu,
        :recordp->ZeitUnix,
        :recordp->BewegungSchluessel,
        :recordp->StockReserved,
        :recordp->MoveType,
        :recordp->PosNr,
        :recordp->BelegArt;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    if (SQLCODE == 0)
    {
       exec sql close rartacct_r2;
       exec sql free thisquery2;
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          exec sql close rartacct_r2;
          exec sql free thisquery2;
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
       {
          exec sql close rartacct_r2;
          exec sql free thisquery2;
          return cDBXR_NOTFOUND;
       }
       exec sql close rartacct_r2;
       exec sql free thisquery2;
       return cDBXR_IOERROR;
    }
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRArtikelKontoInsert                                  */
/*                                                                   */
/*      Insert  record                                               */
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
int pxRArtikelKontoInsert
(
    struct tARTIKELKONTO* record,
    const char* computer
)
{
	int retval = cDBXR_NORMAL;

    EXEC SQL BEGIN DECLARE SECTION;
    struct tARTIKELKONTO * recordp;
    char sql[1024];
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELKONTO * 10 + F_Insert;
    recordp = record;

    sprintf(sql, "INSERT INTO %s:ARTIKELKONTO ("
			"FILIALNR, ARTIKEL_NR, BEWEGUNGSART, MENGE, "
			"BELEGNR, UID, IDFNR, MENGENEU, ZEITUNIX, BEWEGUNGSCHLUESSEL, STOCKRESERVED, MOVETYPE, POSNR, BELEGART) "
		"VALUES ("
			"?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )", computer);

    EXEC SQL PREPARE artikelkonto_ins_stmt FROM :sql;

    if (SQLCODE == 0)
	{
	    EXEC SQL EXECUTE artikelkonto_ins_stmt USING
		:recordp->FilialNr,
        :recordp->ArtikelNr,
        :recordp->BewegungsArt,
        :recordp->Menge,
        :recordp->BelegNr,
        :recordp->Uid,
        :recordp->IDFNr,
        :recordp->MengeNeu,
        :recordp->ZeitUnix,
        :recordp->BewegungSchluessel,
        :recordp->StockReserved,
        :recordp->MoveType,
        :recordp->PosNr,
        :recordp->BelegArt;
	}

	if (SQLCODE == 0)
	{
		retval = cDBXR_NORMAL;
	}
	else if (SQLCODE == -2601)
	{
		retval = cDBXR_ISDUPLICATE;
	}
	else
	{
		retval = cDBXR_IOERROR;
	}
    EXEC SQL FREE artikelkonto_ins_stmt;

	return retval;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRArtikelKontoDelete                                  */
/*                                                                   */
/*      delete  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, else error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxRArtikelKontoDelete
(
    struct tARTIKELKONTO* record,
    const char* computer
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tARTIKELKONTO * recordp;
    char myquery[256];
    EXEC SQL END DECLARE SECTION;

    functionnr = F_ARTIKELKONTO * 10 + F_Delete;
    recordp = record;

    strcpy(myquery,"Delete from ");
    strcat( myquery,computer);
    strcat( myquery,":artikelkonto ");
    strcat( myquery," where LFDNR = ?");

    exec sql prepare thisquery4 from :myquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql execute thisquery4 using :recordp->LfdNr;

    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       if (SQLCODE == 100)
          return cDBXR_NOTFOUND;
       return cDBXR_IOERROR;
    }
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRArtikelKontoStartBrowse                             */
/*                                                                   */
/*      Declare and Open a Cursor   (general)                        */
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
int pxRArtikelKontoStartBrowse
(
     struct tARTIKELKONTO* record,
	 const char* computer,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tARTIKELKONTO * recordp;
    char myquery[256];
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELKONTO*10+F_StartBrowse;
    recordp = record;

    strcpy( myquery,"select ");
    strcat( myquery,"LFDNR, FILIALNR, ARTIKEL_NR, BEWEGUNGSART, MENGE, "
                    "BELEGNR, UID, IDFNR, MENGENEU, ZEITUNIX, BEWEGUNGSCHLUESSEL, STOCKRESERVED, MOVETYPE");
    strcat( myquery," from ");
    strcat( myquery,computer);
    strcat( myquery,":artikelkonto ");

    switch (browseid)
    {
       case cCRSARTIKELKONTO_Default:
          break;
	   case cCRSARTIKELKONTO_Beleg:
       default:
	      strcat(myquery, "where BELEGNR = ? and IDFNR = ?");
          break;
    }

    EXEC SQL PREPARE browsequery FROM :myquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    EXEC SQL DECLARE rartacct_browsecur CURSOR FOR thisquery1;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    switch (browseid)
    {
       case cCRSARTIKELKONTO_Default:
          EXEC SQL OPEN rartacct_browsecur;
          break;
	   case cCRSARTIKELKONTO_Beleg:
       default:
          EXEC SQL OPEN rartacct_browsecur USING
    		:recordp->BelegNr,
	    	:recordp->IDFNr;
          break;
    }

    if (SQLCODE == 0)        return 0;
    if (SQLCODE == 100)      return cDBXR_NOTFOUND;
    return cDBXR_IOERROR;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRArtikelKontoGetNext                                 */
/*                                                                   */
/*      Fetch for a Cursor   (general)                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxRArtikelKontoGetNext
(
    struct tARTIKELKONTO* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tARTIKELKONTO * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_ARTIKELKONTO*10+F_GetNext;
    recordp = record;

    EXEC SQL FETCH rartacct_browsecur INTO
		:recordp->LfdNr,
        :recordp->FilialNr,
        :recordp->ArtikelNr,
        :recordp->BewegungsArt,
        :recordp->Menge,
        :recordp->BelegNr,
        :recordp->Uid,
        :recordp->IDFNr,
        :recordp->MengeNeu,
        :recordp->ZeitUnix,
        :recordp->BewegungSchluessel,
        :recordp->StockReserved,
        :recordp->MoveType,
        :recordp->PosNr,
        :recordp->BelegArt;

    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRArtikelKontoEndBrowse                               */
/*                                                                   */
/*      Close a Cursor   (general)                                   */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxRArtikelKontoEndBrowse
(
)
{
    functionnr = F_ARTIKELKONTO*10+F_EndBrowse;

    /* close the cursor */
    EXEC SQL CLOSE rartacct_browsecur;
    return 0;
}
