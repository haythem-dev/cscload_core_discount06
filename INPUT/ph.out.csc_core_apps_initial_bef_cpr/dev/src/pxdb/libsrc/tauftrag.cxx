/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

    Embedded SQL for C application


    FILE: tauftrag.c (.sqc)

    Database functions







    FUNCTIONS:

        pxAuftragStartBrowse  declare and open Cursor
        pxAuftragGetNext      get next record
        pxAuftragEndBrowse    close cursor
        pxAuftragRead         get one record
        pxAuftragReadLock     get one record with lock
        pxAuftragInsert       Insert record
        pxAuftragUpdate       Update record
        pxAuftragDelete       Delete record


REVISION HISTORY

06 Oct 1995 V1.00 REV 00 written by Dietmar Schloetel

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include "tauftrag.h"
#include "keys.h"


typedef int (* tCRSFP) (struct tKDAUFTRAG* record, int mode);

extern int tasbc0 (struct tKDAUFTRAG* record, int mode);
extern int tasbc1 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc2 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc3 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc4 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc5 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc6 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc7 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc8 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc9 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc10 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc11 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc12 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc13 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc14 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc15 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc16 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc17 (struct tKDAUFTRAG* record, int mode);
extern int tasbc18 (struct tKDAUFTRAG* record, int mode);
extern int tasbc19 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc20 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc21 (struct tKDAUFTRAG* record, int mode);
extern int tasbc22 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc23 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc24 (struct tKDAUFTRAG* record, int mode);
extern int tasbc25 (struct tKDAUFTRAG* record, int mode);
extern int tasbc26 (struct tKDAUFTRAG* record, int mode);
extern int tasbc27 (struct tKDAUFTRAG* record, int mode);
extern int tasbc28 (struct tKDAUFTRAG* record, int mode);
extern int tasbc29 (struct tKDAUFTRAG* record, int mode);
extern int tasbc30 (struct tKDAUFTRAG* record, int mode);
extern int tasbc31 (struct tKDAUFTRAG* record, int mode);
extern int tasbc32 (struct tKDAUFTRAG* record, int mode);
extern int tasbc33 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc34 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc35 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc36 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc37 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc38 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc39 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc40 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc41 (struct tKDAUFTRAG* record, int mode);
extern int tasbc42 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc43 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc44 (struct tKDAUFTRAG* record, int mode);
extern int tasbc45 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc46 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc47 (struct tKDAUFTRAG* record, int mode);
extern int tasbc48 (struct tKDAUFTRAG* record, int mode);
extern int tasbc49 (struct tKDAUFTRAG* record, int mode);
extern int tasbc50 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc51 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc52 (struct tKDAUFTRAG* record, int mode);
extern int tasbc53 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc54 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc55 (struct tKDAUFTRAG* record, int mode);
extern int tasbc56 (struct tKDAUFTRAG* record, int mode);
extern int tasbc57 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc58 (struct tKDAUFTRAG* record, int mode);
//extern int tasbc59 (struct tKDAUFTRAG* record, int mode);
extern int tasbc60 (struct tKDAUFTRAG* record, int mode);
extern int tasbc61 (struct tKDAUFTRAG* record, int mode);
extern int tasbc62 (struct tKDAUFTRAG* record, int mode);
extern int tasbc63 (struct tKDAUFTRAG* record, int mode);
extern int tasbc64 (struct tKDAUFTRAG* record, int mode);
extern int tasbc65 (struct tKDAUFTRAG* record, int mode);
extern int tasbc66 (struct tKDAUFTRAG* record, int mode);
extern int tasbc67 (struct tKDAUFTRAG* record, int mode);
extern int tasbc68 (struct tKDAUFTRAG* record, int mode);
extern int tasbc69 (struct tKDAUFTRAG* record, int mode);
extern int tasbc70 (struct tKDAUFTRAG* record, int mode);
extern int tasbc71 (struct tKDAUFTRAG* record, int mode);
extern int tasbc72 (struct tKDAUFTRAG* record, int mode);
extern int tasbc73 (struct tKDAUFTRAG* record, int mode);

typedef struct sbcfunc_struct           /* browseid - function table               */
{
    int            cursor;              /* browseid */
    tCRSFP         cursfp;              /* ptr to function processing*/
}   tCRSFT, *tCRSFTP;

/* define a table of all possible cursors */
tCRSFT cursfunc[] =
{
   { cCRS_NOWHERE                                                                                                , &tasbc0},  /*     0 */
   { cCRSORD_IDFNr                                                                                               , &tasbc1},  /*     1 */
   { cCRSORD_IDFNr+cCRSORD_TourId                                                                                , &tasbc18}, /*     5 */
   { cCRSORD_IDFNr+cCRSORD_TourId+cCRSORD_FilialNr                                                               , &tasbc19}, /*    13 */
   { cCRSORD_IDFNr+cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_KdAuftragStat                                         , &tasbc22}, /*    45 */
   { cCRSORD_IDFNr+cCRSORD_TourId+cCRSORD_KdAuftragStat                                                          , &tasbc25}, /*    37 */
   { cCRSORD_IDFNr+cCRSORD_FilialNr                                                                              , &tasbc26}, /*     9 */
   { cCRSORD_IDFNr+cCRSORD_FilialNr+cCRSORD_PersonalNr                                                           , &tasbc27}, /*    25 */
   { cCRSORD_IDFNr+cCRSORD_FilialNr+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                                     , &tasbc28}, /*    57 */
   { cCRSORD_IDFNr+cCRSORD_FilialNr+cCRSORD_KdAuftragStat                                                        , &tasbc29}, /*    41 */
   { cCRSORD_IDFNr+cCRSORD_PersonalNr                                                                            , &tasbc30}, /*    17 */
   { cCRSORD_IDFNr+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                                                      , &tasbc31}, /*    49 */
   { cCRSORD_IDFNr+cCRSORD_KdAuftragStat                                                                         , &tasbc32}, /*    33 */
   { cCRSORD_GeraetName                                                                                          , &tasbc33}, /*     2 */
   { cCRSORD_GeraetName+cCRSORD_FilialNr                                                                         , &tasbc42}, /*    10 */
   { cCRSORD_GeraetName+cCRSORD_FilialNr+cCRSORD_KdAuftragStat                                                   , &tasbc45}, /*    42 */
   { cCRSORD_GeraetName+cCRSORD_KdAuftragStat                                                                    , &tasbc48}, /*    34 */
   { cCRSORD_TourId                                                                                              , &tasbc49}, /*     4 */
   { cCRSORD_TourId+cCRSORD_FilialNr                                                                             , &tasbc50}, /*    12 */
   { cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_KdAuftragStat                                                       , &tasbc53}, /*    44 */
   { cCRSORD_TourId+cCRSORD_KdAuftragStat                                                                        , &tasbc56}, /*    36 */
   { cCRSORD_FilialNr                                                                                            , &tasbc57}, /*     8 */
   { cCRSORD_FilialNr+cCRSORD_KdAuftragStat                                                                      , &tasbc60}, /*    40 */
   { cCRSORD_PersonalNr                                                                                          , &tasbc61}, /*    16 */
   { cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                                                                    , &tasbc62}, /*    48 */
   { cCRSORD_KdAuftragStat                                                                                       , &tasbc63}, /*    32 */
   { cCRSORD_VertriebszentrumNr                                                                                  , &tasbc64}, /*   128 */
   { cCRSORD_KundenNr                                                                                            , &tasbc65}, /*    64 */
   { cCRSORD_VertriebszentrumNr+cCRSORD_KundenNr                                                                 , &tasbc66}, /*   192 */
   { cCRSORD_VertriebszentrumNr+cCRSORD_KundenNr+cCRSORD_KdAuftragStat                                           , &tasbc67}, /*   224 */
   { cCRSORD_FilialNr+cCRSORD_KdAuftragStat+cCRSORD_SelectModeOdd                                                , &tasbc68}, /*   552 */
   { cCRSORD_FilialNr+cCRSORD_KdAuftragStat+cCRSORD_SelectModeEven                                               , &tasbc69}, /*   296 */
   { cCRSORD_FilialNr+cCRSORD_KdAuftragStat+cCRSORD_ZuGrund                                                      , &tasbc70}, /*  1064 */
   { cCRSORD_VertriebszentrumNr+cCRSORD_KundenNr+cCRSORD_KdAuftragStat+cCRSORD_ZuGrund+cCRSORD_BatchAuftragNr    , &tasbc71}, /*  3296 */
   { cCRSORD_FilialNr+cCRSORD_IDFNr+cCRSORD_KdAuftragArt+cCRSORD_OrderPeriodID                                   , &tasbc72}, /* 12297 */
   { cCRSORD_AUTOMATICCLOSURE                                                                                    , &tasbc73}, /* 16384 */
};

// { cCRSORD_IDFNr+cCRSORD_GeraetName                                                                            , &tasbc2},  /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_TourId                                                             , &tasbc3},  /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_FilialNr                                            , &tasbc4},  /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_PersonalNr                         , &tasbc5},  /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat   , &tasbc6},  /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_KdAuftragStat                      , &tasbc7},  /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_PersonalNr                                          , &tasbc8},  /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                    , &tasbc9},  /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_KdAuftragStat                                       , &tasbc10}, /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_FilialNr                                                           , &tasbc11}, /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_FilialNr+cCRSORD_PersonalNr                                        , &tasbc12}, /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_FilialNr+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                  , &tasbc13}, /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_FilialNr+cCRSORD_KdAuftragStat                                     , &tasbc14}, /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_PersonalNr                                                         , &tasbc15}, /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                                   , &tasbc16}, /**/
// { cCRSORD_IDFNr+cCRSORD_GeraetName+cCRSORD_KdAuftragStat                                                      , &tasbc17}, /**/


// { cCRSORD_IDFNr+cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_PersonalNr                                            , &tasbc20}, /**/
// { cCRSORD_IDFNr+cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                      , &tasbc21}, /**/

// { cCRSORD_IDFNr+cCRSORD_TourId+cCRSORD_PersonalNr                                                             , &tasbc23}, /**/
// { cCRSORD_IDFNr+cCRSORD_TourId+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                                       , &tasbc24}, /**/


// { cCRSORD_GeraetName+cCRSORD_TourId                                                                           , &tasbc34}, /**/
// { cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_FilialNr                                                          , &tasbc35}, /**/
// { cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_PersonalNr                                       , &tasbc36}, /**/
// { cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                 , &tasbc37}, /**/
// { cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_KdAuftragStat                                    , &tasbc38}, /**/
// { cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_PersonalNr                                                        , &tasbc39}, /**/
// { cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                                  , &tasbc40}, /**/
// { cCRSORD_GeraetName+cCRSORD_TourId+cCRSORD_KdAuftragStat                                                     , &tasbc41}, /**/
// { cCRSORD_GeraetName+cCRSORD_FilialNr+cCRSORD_PersonalNr                                                      , &tasbc43}, /**/
// { cCRSORD_GeraetName+cCRSORD_FilialNr+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                                , &tasbc44}, /**/
// { cCRSORD_GeraetName+cCRSORD_PersonalNr                                                                       , &tasbc46}, /**/
// { cCRSORD_GeraetName+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                                                 , &tasbc47}, /**/
// { cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_PersonalNr                                                          , &tasbc51}, /**/
// { cCRSORD_TourId+cCRSORD_FilialNr+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                                    , &tasbc52}, /**/
// { cCRSORD_TourId+cCRSORD_PersonalNr                                                                           , &tasbc54}, /**/
// { cCRSORD_TourId+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                                                     , &tasbc55}, /**/
// { cCRSORD_FilialNr+cCRSORD_PersonalNr                                                                         , &tasbc58}, /**/
// { cCRSORD_FilialNr+cCRSORD_PersonalNr+cCRSORD_KdAuftragStat                                                   , &tasbc59}, /**/



extern int   functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragStartBrowse                                   */
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

int pxAuftragStartBrowse
(
     struct tKDAUFTRAG* record,
     int browseid
)
{
    tCRSFTP functab;

    functionnr = F_KDAUFTRAG*10+F_StartBrowse;

    for (functab = cursfunc;functab->cursor != browseid;functab++);
    return functab->cursfp(record,1);
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragGetNext                                       */
/*                                                                   */
/*      Fetch for a Cursor   (general)                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*      record buffer                                                */
/*                                                                   */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxAuftragGetNext
(
    struct tKDAUFTRAG* record,
    int browseid
)
{
    tCRSFTP functab;

    functionnr = F_KDAUFTRAG*10+F_GetNext;

    for (functab = cursfunc;functab->cursor != browseid;functab++);
    return functab->cursfp(record,2);
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragEndBrowse                                     */
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

int pxAuftragEndBrowse
(
    int browseid
)
{
    tCRSFTP functab;

    functionnr = F_KDAUFTRAG*10+F_EndBrowse;

    for (functab = cursfunc;functab->cursor != browseid;functab++);
    return functab->cursfp((struct tKDAUFTRAG*) 0,3);
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragRead                                          */
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

int pxAuftragRead
(
    struct tKDAUFTRAG* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAG * rp;
    EXEC SQL END DECLARE SECTION;

    rp = (struct C_KDAUFTRAG *) record;
    functionnr = F_KDAUFTRAG*10+F_Read;

    EXEC SQL SELECT
        KDAUFTRAG_LISTE
     into KDAUFTRAG_ZEIGER(rp)
     from KDAUFTRAG
     where PKtauftrag;

    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
          return cDBXR_NOTFOUND;
       return cDBXR_IOERROR;
    }

}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragReadLock                                      */
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
int pxAuftragReadLock
(
    struct tKDAUFTRAG* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAG * rp;
    EXEC SQL END DECLARE SECTION;

    rp = (struct C_KDAUFTRAG *) record;
    functionnr = F_KDAUFTRAG*10+F_ReadLock;

#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE TAUFART_U1 CURSOR WITH HOLD FOR
        SELECT
        KDAUFTRAG_LISTE
    from KDAUFTRAG
    where PKtauftrag
    FOR UPDATE;
    EXEC SQL OPEN TAUFART_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH TAUFART_U1
      into KDAUFTRAG_ZEIGER(rp)
      ;
    }
#else
    EXEC SQL SELECT
         KDAUFTRAG_LISTE
    into KDAUFTRAG_ZEIGER(rp)
    from KDAUFTRAG    HOLDLOCK
    where PKtauftrag;
#endif
    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
          return cDBXR_NOTFOUND;
       return cDBXR_IOERROR;
    }

}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragUpdate                                        */
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

int pxAuftragUpdate
(
    struct tKDAUFTRAG* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAG * rp;
    EXEC SQL END DECLARE SECTION;

    rp = (struct C_KDAUFTRAG *) record;
    functionnr = F_KDAUFTRAG*10+F_Update;

#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    KDAUFTRAG
    SET
    KDAUFTRAG_UPDATE(rp)
    where current of TAUFART_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE TAUFART_U1;
    }
#else
    EXEC SQL UPDATE
    KDAUFTRAG
    SET
    KDAUFTRAG_UPDATE(rp)
    where PKtauftrag;
#endif
    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       return cDBXR_IOERROR;
    }
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragInsert                                       */
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
int pxAuftragInsert
(
    struct tKDAUFTRAG* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAG * rp;
    EXEC SQL END DECLARE SECTION;

    rp = (struct C_KDAUFTRAG *) record;
    functionnr = F_KDAUFTRAG*10+F_Insert;

#ifdef pxDATABASE_INFORMIX
    EXEC SQL INSERT INTO
    KDAUFTRAG
    (KDAUFTRAG_LISTE)
    VALUES ( KDAUFTRAG_ZEIGER(rp) );
#else
    EXEC SQL INSERT INTO
    KDAUFTRAG
    VALUES ( KDAUFTRAG_ZEIGER(rp) );
#endif


    if (SQLCODE == 0)
    {
       return 0;
    }
    if (SQLCODE == -2601)
    {
       return cDBXR_ISDUPLICATE;
    }
    return cDBXR_IOERROR;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxAuftragDelete                                        */
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

int pxAuftragDelete
(
    struct tKDAUFTRAG* record
)
{

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAG * rp;
    EXEC SQL END DECLARE SECTION;

    rp = (struct C_KDAUFTRAG *) record;
    functionnr = F_KDAUFTRAG*10+F_Delete;

    EXEC SQL DELETE FROM
    KDAUFTRAG
    where PKtauftrag;

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
