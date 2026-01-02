/*
06 Oct 1995 V1.00 REV 00 written by Dietmar Schloetel
*/
//#include <stddef.h>         /* standard C run-time header */
//#include <stdio.h>          /* standard C run-time header */
//#include <string.h>
//#include <pxrecord.h>       /* all record structures */
//#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include "tnummer.h"

/* Global variables */
extern int  functionnr;

int pxNummerSequence ( struct tNUMMERSEQUENCE* record)
{
    EXEC SQL BEGIN DECLARE SECTION;
	struct tNUMMERSEQUENCE* recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NUMMER*10+F_Read;
    recordp = record;

	switch (recordp->SequenceType)
	{
	case cSEQUENCE_ORDERNO:
		EXEC SQL
			SELECT CSCORDERNO.NEXTVAL
			INTO :recordp->NextVal
			FROM SYSTABLES
			WHERE TABID = 1;
        break;
	case cSEQUENCE_BATCHORDERNO:
		EXEC SQL
			SELECT BATCHORDERNO.NEXTVAL
			INTO :recordp->NextVal
			FROM SYSTABLES
			WHERE TABID = 1;
        break;
	case cSEQUENCE_BATCHORDERNO2:
		EXEC SQL
			SELECT BATCHORDERNO2.NEXTVAL
			INTO :recordp->NextVal
			FROM SYSTABLES
			WHERE TABID = 1;
        break;
	default:
		break;
	}
	if (SQLCODE == 0)
    {
		return cDBXR_NORMAL;
    }
    if (SQLCODE == 1)                /* found, but more than 1 exists */
    {
        return cDBXR_ISDUPLICATE;
    }
    if (SQLCODE == 100)
    {
        return cDBXR_NOTFOUND;
    }
    return cDBXR_IOERROR;
}


/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxNummerRead                                           */
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

int pxNummerRead
(
    struct tNUMMER* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tNUMMER* recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NUMMER*10+F_Read;
    recordp = record;

    EXEC SQL SELECT
		 NUMMER.NUMMERTYP,
         NUMMER.NUMMERWERT,
         NUMMER.NUMMERMINDEST,
         NUMMER.NUMMERHOECHST,
         NUMMER.NUMMERINKREMENT,
         NUMMER.NUMMERMODUS
    INTO :recordp->NummerTyp,
         :recordp->NummerWert,
         :recordp->NummerMindest,
         :recordp->NummerHoechst,
         :recordp->NummerInkrement,
         :recordp->NummerModus
     FROM NUMMER
     WHERE
         NUMMERTYP = :recordp->NummerTyp;

    if (SQLCODE == 0)
    {
       return cDBXR_NORMAL;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
          return cDBXR_NOTFOUND;
    }
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxNummerReadLock                                       */
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
int pxNummerReadLock
(
    struct tNUMMER* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tNUMMER* recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NUMMER*10+F_ReadLock;
    recordp = record;

    EXEC SQL DECLARE TNUMMER_U1 CURSOR WITH HOLD FOR
        SELECT
   	     NUMMER.NUMMERTYP,
         NUMMER.NUMMERWERT,
         NUMMER.NUMMERMINDEST,
         NUMMER.NUMMERHOECHST,
         NUMMER.NUMMERINKREMENT,
         NUMMER.NUMMERMODUS
    FROM NUMMER
    WHERE NUMMERTYP = :recordp->NummerTyp
    FOR UPDATE;
    EXEC SQL OPEN TNUMMER_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TNUMMER_U1
        INTO :recordp->NummerTyp,
             :recordp->NummerWert,
             :recordp->NummerMindest,
             :recordp->NummerHoechst,
             :recordp->NummerInkrement,
             :recordp->NummerModus;
    }

    if (SQLCODE == 0)
    {
       return cDBXR_NORMAL;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
          return cDBXR_NOTFOUND;
    }
    return cDBXR_IOERROR;
}

	/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxNummerUpdate                                         */
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

int pxNummerUpdate
(
    struct tNUMMER* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct tNUMMER* recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NUMMER*10+F_Update;
    recordp = record;

    EXEC SQL UPDATE
    NUMMER
    SET
        NUMMER.NUMMERTYP       = :recordp->NummerTyp,
        NUMMER.NUMMERWERT      = :recordp->NummerWert,
        NUMMER.NUMMERMINDEST   = :recordp->NummerMindest,
        NUMMER.NUMMERHOECHST   = :recordp->NummerHoechst,
        NUMMER.NUMMERINKREMENT = :recordp->NummerInkrement,
        NUMMER.NUMMERMODUS     = :recordp->NummerModus
    WHERE CURRENT OF TNUMMER_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TNUMMER_U1;
    }

    if (SQLCODE == 0)
    {
       return cDBXR_NORMAL;
    }
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxNummerInsert                                         */
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
int pxNummerInsert
(
    struct tNUMMER* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct tNUMMER * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_NUMMER*10+F_Insert;
    recordp = record;

    EXEC SQL INSERT INTO
    NUMMER
    (
	    NUMMER.NUMMERTYP,
        NUMMER.NUMMERWERT,
        NUMMER.NUMMERMINDEST,
        NUMMER.NUMMERHOECHST,
        NUMMER.NUMMERINKREMENT,
        NUMMER.NUMMERMODUS
    )
    VALUES
	(
        :recordp->NummerTyp,
        :recordp->NummerWert,
        :recordp->NummerMindest,
        :recordp->NummerHoechst,
        :recordp->NummerInkrement,
        :recordp->NummerModus
	);

    if (SQLCODE == 0)
    {
       return cDBXR_NORMAL;
    }
    if (SQLCODE == -2601)
    {
       return cDBXR_ISDUPLICATE;
    }
    return cDBXR_IOERROR;
}
