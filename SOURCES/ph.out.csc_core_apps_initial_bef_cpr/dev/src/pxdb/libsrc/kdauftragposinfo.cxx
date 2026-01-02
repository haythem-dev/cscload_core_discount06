
#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include "pxrecord.h"       /* all record structures */
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "pxenv.h"
#include "tkdauftragpos.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxOriginPositionRead                                  */
/*                                                                   */
/*      Get one record           from remote database                */
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
int pxPositionInfoRead
(
    struct tKDAUFTRAGPOS* record,
    char  * computer
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAGPOS * recordp;
    char myquery[256];
    EXEC SQL END DECLARE SECTION;

    functionnr = F_KDAUFTRAGPOS * 10 + F_Read;
    recordp = (struct C_KDAUFTRAGPOS *) record;

#ifdef pxDATABASE_INFORMIX
    strcpy( myquery,"select ");
    strcat( myquery,"kdauftragnr,");
    strcat( myquery,"posnr,");
    strcat( myquery,"touridibt,");
    strcat( myquery,"ibttourweekday ");
    strcat( myquery,"from ");
    strcat( myquery,computer);
    strcat( myquery,":kdauftragpos ");
    strcat( myquery,"where kdauftragnr = ?");
    strcat( myquery,"and  posnr = ?");
    strcat ( myquery," ;");

    exec sql prepare thisquery from :myquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql declare kdauftragposinfo_u1 cursor with hold for thisquery;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql open kdauftragposinfo_u1 using :recordp->KDAUFTRAGNR, :recordp->POSNR;

    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    exec sql fetch kdauftragposinfo_u1 into
        :recordp->KDAUFTRAGNR,
        :recordp->POSNR,
        :recordp->TOURIDIBT,
        :recordp->IBTTOURWEEKDAY;
    if (SQLCODE != 0)
       return cDBXR_IOERROR;

    if (SQLCODE == 0)
    {
       exec sql close kdauftragposinfo_u1;
       exec sql free thisquery;
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          exec sql close kdauftragposinfo_u1;
          exec sql free thisquery;
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
       {
          exec sql close kdauftragposinfo_u1;
          exec sql free thisquery;
          return cDBXR_NOTFOUND;
       }
       exec sql close kdauftragposinfo_u1;
       exec sql free thisquery;
       return cDBXR_IOERROR;
    }
#endif

}
