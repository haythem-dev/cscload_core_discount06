/******************************************************************************/
/*                                                                            */
/* header  : MCheckProcess.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:00:03 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "processcheck.h"

/* MCheckProcess: Select ******************************************************/

/* MCheckProcess::SelProcess **************************************************/

retClient Mcheckprocess_SelProcess(mcheckprocessS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcheckprocess_SelProcess";
    exec sql begin declare section;
    mcheckprocessS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select aktiveprozesse.ProgrammName,
                     aktiveprozesse.ProgrammPartner,
                     aktiveprozesse.pid
                into :d->PROGRAMMNAME,
                     :d->PROGRAMMPARTNER,
                     :d->PID
                from AKTIVEPROZESSE
              where AktiveProzesse.ProgrammName = :d->PROGRAMMNAME and
                    AktiveProzesse.ProgrammPartner = :d->PROGRAMMPARTNER;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MCheckProcess: Insert ******************************************************/

/* MCheckProcess::Insert ******************************************************/

retClient Mcheckprocess_Insert(mcheckprocessS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Mcheckprocess_Insert";
    exec sql begin declare section;
    mcheckprocessS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into aktiveprozesse (ProgrammName,
                     ProgrammPartner,
                     pid)
        values (:d->PROGRAMMNAME,
                     :d->PROGRAMMPARTNER,
                     :d->PID);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert aktiveprozesse" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Commit( fun, stError ) ) != IS_OK )
            return rc;
    }
    return rc;
}



/* MCheckProcess: Update ******************************************************/

/* MCheckProcess::UpdProcess **************************************************/

retClient Mcheckprocess_UpdProcess(mcheckprocessS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcheckprocess_UpdProcess";
    exec sql begin declare section;
    mcheckprocessS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdProcess1 cursor with hold for
              select ProgrammName,
                     ProgrammPartner,
                     pid
               from AKTIVEPROZESSE
              where AktiveProzesse.ProgrammName = :d->PROGRAMMNAME and
                    AktiveProzesse.ProgrammPartner = :d->PROGRAMMPARTNER
              for update;
    exec sql open CUpdProcess1;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdProcess1" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdProcess1;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdProcess1" ) ) != IS_OK )
            break;
        exec sql update aktiveprozesse set ProgrammName = :d->PROGRAMMNAME,
                     ProgrammPartner = :d->PROGRAMMPARTNER,
                     pid = :d->PID where current of CUpdProcess1;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdProcess1" ) ) != IS_OK )
            break;
        break;
    }

    if ( bIsTrans && rc < 0 )
    {
        exec sql rollback work;
        return rc;
    }
    else if ( bIsTrans )
    {
        if ( bIsTrans )
        {
            if ( bInTrans )
            {
                if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                    return rc;
            }
        }
    }
    return rc;
}



/* MCheckProcess: Select ******************************************************/

/* MCheckProcess::DelProcess **************************************************/

retClient Mcheckprocess_DelProcess(mcheckprocessS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Mcheckprocess_DelProcess";
    exec sql begin declare section;
    mcheckprocessS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelProcess2 cursor with hold for
              select ProgrammName,
                     ProgrammPartner,
                     pid
               from AKTIVEPROZESSE
              where AktiveProzesse.ProgrammName = :d->PROGRAMMNAME and
                    AktiveProzesse.ProgrammPartner = :d->PROGRAMMPARTNER
              for update;
    exec sql open CDelProcess2;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelProcess2" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelProcess2;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelProcess2" ) ) != IS_OK )
            break;
        exec sql delete from aktiveprozesse where current of CDelProcess2;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelProcess2" ) ) != IS_OK )
            break;
        break;
    }

    if ( bIsTrans && rc < 0 )
    {
        exec sql rollback work;
        return rc;
    }
    else if ( bIsTrans )
    {
        if ( bIsTrans )
        {
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc;
}



/* MCheckProcess: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MUmkProcesses.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:00:08 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "processcheck.h"

/* MUmkProcesses: Select ******************************************************/



/* MUmkProcesses: Insert ******************************************************/



/* MUmkProcesses: Update ******************************************************/



/* MUmkProcesses: Select ******************************************************/



/* MUmkProcesses: Other *******************************************************/

/* MUmkProcesses::SelList *****************************************************/

retClient Mumkprocesses_SelList(mumkprocessesS *a, tError *stError, bool bIsTrans)
{
/* don't change this lines!!!!!! */
char *fun = "Mumkprocesses_SelList";
static FILE *fp;

if ( a->FETCH_REL == SET_OPEN )
{
   char filename[80];
   char szBefehl[156];
   int PID = getpid();

   sprintf( filename, "/tmp/status.%ld", PID );
   sprintf( szBefehl,
           "umkstatusall -branchno %02d > %s",
           a->UMKFILIALNR,
           filename );
   system( szBefehl );    
   
   if((fp = fopen( filename, "r" )) == NULL)
     return 1;
}

if ((fgets(a->UMKRETURNSTATUS , L_MUMKPROCESSES_UMKRETURNSTATUS , fp)) == (char *)0)
{
   char filename[80];
   char szBefehl[156];
   int PID = getpid();

   fclose( fp );
   sprintf( filename, "/tmp/status.%ld", PID );   
   sprintf( szBefehl, "rm %s", filename );
   system( szBefehl ); 
   return 1;
}

//a->UMKRETURNSTATUS[strlen(a->UMKRETURNSTATUS)-1] = '\0';
return 0;
}

/* MUmkProcesses::StartCallplan ***********************************************/

retClient Mumkprocesses_StartCallplan(mumkprocessesS *a, tError *stError, bool bIsTrans)
{
  retClient rc = IS_OK;
  char szBuf[156];
  exec sql begin declare section;
  mumkprocessesS *d = a;
  exec sql end declare section;

  char *fun = "Mumkprocesses_StartCallplan";

  if ( bIsTrans ); /*only because preprozessor*/

  exec sql select count(*) into :d->UMKANZAHL from umkverwaltung
            where filialnr = :d->UMKFILIALNR;
  if ( CheckSql( fun, stError, "%s", "select count(*)" ) == IS_ERROR )
     d->UMKANZAHL = 0; 

  if ( d->UMKANZAHL > 0 )
  {  
     sprintf( szBuf, "callplan_start -branchno %02d", a->UMKFILIALNR );
     d->UMKRETURNSTATUS[0] = system(szBuf) == 0 ? '1' : '0';  
  }
 
  return (retClient)IS_OK;
}

/* MUmkProcesses::StartUmkAll *************************************************/

retClient Mumkprocesses_StartUmkAll(mumkprocessesS *a, tError *stError, bool bIsTrans)
{
  retClient rc = IS_OK;
  char szBuf[156];
  exec sql begin declare section;
  mumkprocessesS *d = a;
  exec sql end declare section;

  
  char *fun = "Mumkprocesses_StartUmkAll";

  if ( bIsTrans ); /*only because preprozessor*/

  exec sql select count(*) into :d->UMKANZAHL from umkverwaltung
            where filialnr = :d->UMKFILIALNR;
  if ( CheckSql( fun, stError, "%s", "select count(*)" ) == IS_ERROR )
     d->UMKANZAHL = 0; 

  if ( d->UMKANZAHL > 0 )
  {  
     sprintf( szBuf, "umk_start_all -branchno %02d", a->UMKFILIALNR );
     d->UMKRETURNSTATUS[0] = system(szBuf) == 0 ? '1' : '0';  
  }
 
  return (retClient)IS_OK;
}

/* MUmkProcesses::StartUmkUnique **********************************************/

retClient Mumkprocesses_StartUmkUnique(mumkprocessesS *a, tError *stError, bool bIsTrans)
{
  retClient rc = IS_OK;
  char szBuf[156];
  exec sql begin declare section;
  mumkprocessesS *d = a;
  short sUmkNO = d->UMKANZAHL;
  exec sql end declare section;

  
  char *fun = "Mumkprocesses_StartUmkUnique";

  if ( bIsTrans ); /*only because preprozessor*/

  exec sql select count(*) into :d->UMKANZAHL from umkverwaltung
            where filialnr = :d->UMKFILIALNR;
  if ( CheckSql( fun, stError, "%s", "select count(*)" ) == IS_ERROR )
     d->UMKANZAHL = 0; 

  if ( d->UMKANZAHL > 0 )
  {  
     sprintf( szBuf, "umk%d_start -branchno %02d", sUmkNO, a->UMKFILIALNR );
     d->UMKRETURNSTATUS[0] = system(szBuf) == 0 ? '1' : '0';  
  }
 
  return (retClient)IS_OK;
}

/* MUmkProcesses::StopCallplan ************************************************/

retClient Mumkprocesses_StopCallplan(mumkprocessesS *a, tError *stError, bool bIsTrans)
{
  retClient rc = IS_OK;
  char szBuf[156];
  exec sql begin declare section;
  mumkprocessesS *d = a;
  exec sql end declare section;

  char *fun = "Mumkprocesses_StopCallplan";

  if ( bIsTrans ); /*only because preprozessor*/

  exec sql select count(*) into :d->UMKANZAHL from umkverwaltung
            where filialnr = :d->UMKFILIALNR;
  if ( CheckSql( fun, stError, "%s", "select count(*)" ) == IS_ERROR )
     d->UMKANZAHL = 0; 

  if ( d->UMKANZAHL > 0 )
  {  
     sprintf( szBuf, "callplan_stop -branchno %02d", a->UMKFILIALNR );
     d->UMKRETURNSTATUS[0] = system(szBuf) == 0 ? '1' : '0';  
  }
 
  return (retClient)IS_OK;
}

/* MUmkProcesses::StopUmkAll **************************************************/

retClient Mumkprocesses_StopUmkAll(mumkprocessesS *a, tError *stError, bool bIsTrans)
{
  retClient rc = IS_OK;
  char szBuf[156];
 
  exec sql begin declare section;
  mumkprocessesS *d = a;
  exec sql end declare section;
  
  char *fun = "Mumkprocesses_StartUmkAll";

  if ( bIsTrans ); /*only because preprozessor*/

  exec sql select count(*) into :d->UMKANZAHL from umkverwaltung
            where filialnr = :d->UMKFILIALNR;
  if ( CheckSql( fun, stError, "%s", "select count(*)" ) == IS_ERROR )
     d->UMKANZAHL = 0; 

  sprintf( szBuf, "callplan_stop -branchno %02d", a->UMKFILIALNR );
  d->UMKRETURNSTATUS[0] = system(szBuf) == 0 ? '1' : '0';

  if ( d->UMKANZAHL > 0 )
  {    
     sprintf( szBuf, "umk1_stop -branchno %02d", a->UMKFILIALNR );
     d->UMKRETURNSTATUS[0] = system(szBuf) == 0 ? '1' : '0';
  }
 
  if ( d->UMKANZAHL > 1 )
  {    
     sprintf( szBuf, "umk2_stop -branchno %02d", a->UMKFILIALNR );
     d->UMKRETURNSTATUS[1] = system(szBuf) == 0 ? '1' : '0';
  }

  if ( d->UMKANZAHL > 2 )
  {    
     sprintf( szBuf, "umk3_stop -branchno %02d", a->UMKFILIALNR );
     d->UMKRETURNSTATUS[2] = system(szBuf) == 0 ? '1' : '0';
  }

  return (retClient)IS_OK;
}

/* MUmkProcesses::StopUmkUnique ***********************************************/

retClient Mumkprocesses_StopUmkUnique(mumkprocessesS *a, tError *stError, bool bIsTrans)
{
 retClient rc = IS_OK;
  char szBuf[156];
  exec sql begin declare section;
  mumkprocessesS *d = a;
  short sUmkNO = d->UMKANZAHL;
  exec sql end declare section;

  
  char *fun = "Mumkprocesses_StopUmkUnique";

  if ( bIsTrans ); /*only because preprozessor*/

  exec sql select count(*) into :d->UMKANZAHL from umkverwaltung
            where filialnr = :d->UMKFILIALNR;
  if ( CheckSql( fun, stError, "%s", "select count(*)" ) == IS_ERROR )
     d->UMKANZAHL = 0; 

  if ( d->UMKANZAHL > 0 )
  {  
     sprintf( szBuf, "umk%d_stop -branchno %02d", sUmkNO, a->UMKFILIALNR );
     d->UMKRETURNSTATUS[0] = system(szBuf) == 0 ? '1' : '0';  
  }
 
  return (retClient)IS_OK;
}



