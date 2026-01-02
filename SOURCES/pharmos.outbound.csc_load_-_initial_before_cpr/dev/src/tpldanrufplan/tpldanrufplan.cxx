	/******************************************************************************/
/*     Hauptmodul: tpldanrufplan.c                                            */
/*         Source: tpldanrufplan.c                                            */
/*          Autor: A. Schmidt-Rehschuh                                        */
/*       Erstellt: 25.10.2000                                                 */
/*        Sprache: C                                                          */
/*        Erzeugt: manuell                                                    */
/*        Aufgabe: taegliches laden des gesmaten Anrufplanes aus Masterplan   */
/*         Aufruf: tpldanrufplan                                              */
/*                                                                            */
/******************************************************************************/

/*** VERSION ******************************************************************/

#include "csc_load_version.h"

#define PROJECTNAME	 "tpldanrufplan"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/*** INCLUDE ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "libtpld/logfile.h"
#include "libtpld/dadedb.h"
#include "callplanundertake.h"
#include "callplanmaintenance.h"

/*** DEFINE *******************************************************************/

#define DATABASE "phosix"
#define LOGFILE "wws.log"		 

/*** OPEN-DATABASE ************************************************************/

static	bool OpenDatabase( char* spDatabase, tError* spError, short* sBranchNo )
{
   int iBranchNo = 0;
   char *fun = "OpenDatabase";

   if ( OpenDb( spDatabase, spError ) != IS_OK )
   {
      WriteLog( fun, -1, "Datenbank konnte nicht geöffnet werden" );
	  return FALSE;
   }
   else if ( SetIsolation( DIRTY_READ, spError ) != IS_OK )
   {
      WriteLog( fun, -1, "Set Isolation konnte nicht gesetzt werden" );
      return FALSE;
   }
   else if ( SetLockMode( 20, spError ) != IS_OK )
   {
      WriteLog( fun, -1, "Set Lock Mode To Wait konnte nicht gesetzt werden" );
	  return FALSE;
   } 
   else if ( GetNumberOfBranch( &iBranchNo, D_INT, spError ) != IS_OK )
   {
      WriteLog( fun, 1, "FilialNr nicht lokalisiert" );
   }
   SetNumberOfBranch( iBranchNo );            /* set branche for logging     */  
   *sBranchNo = iBranchNo;
   return TRUE;
}

/*** OPEN-LOGFILE *************************************************************/

static bool OpenLogfile( char *spProg )
{
    SetProgramName( spProg );
	if ( SetDirName( (char *)0 ) == (char *)0 ||
	   SetFileName( LOGFILE ) == (char *)0 )                                                 
	{
	  return FALSE;	
	}
	return TRUE;
}

/*** CloseLogfile *************************************************************/

static bool CloseLogfile( void )
{
/*	EndLog();	*/
	return TRUE;
}

/*** CheckEntriesPhon *********************************************************/

static bool CheckEntriesPhon(long* lCount,
							 mcallplanundertakeS* d,
							 tError* stError,
							 const short sBranchNo,
							 long* lLoadDate)
{
	retClient rc;
	long lDate;

	d->VERTRIEBSZENTRUMNR = sBranchNo;

	lDate = d->DATUM;
	
	if ( (rc=(retClient)Mcallplanundertake_CheckAvailableEntriesPhon(d, stError, FALSE)) == IS_ERROR )
	   return FALSE;
 	else if ( rc == IS_NOTFOUND )
	   d->KUNDENNR = 0;

	*lLoadDate = d->DATUM;
	d->DATUM = lDate;

	*lCount = d->KUNDENNR;
	return TRUE;
} 

static bool	DeletePhon( mcallplanundertakeS* d, const short sBranchNo, const long lDate, tError* stError )
{
	d->VERTRIEBSZENTRUMNR = sBranchNo;
	d->DATUM = lDate;

	if ( Mcallplanundertake_DelAllPhonOlder(d, stError, TRUE) == IS_ERROR )
	   return FALSE;
	else if ( Mcallplanundertake_DelEventsPhonOlder(d, stError, TRUE) == IS_ERROR )
	   return FALSE;
	
	return TRUE;
}

/*** MAIN *********************************************************************/

int main( int argc, char **argv )
{
	tError stError;
	long lEntriesSera = 0;
	long lEntriesPhon = 0;
	long lLoadDate = 0;
	short sBranchNo = 0;
	char cError[81];
	mcallplanundertakeS	srvUndertake;	
	mcallplanloadS      srvLadeAnrufplan;
	int i, skip;
	char *schalter;
	long lDelDate;
	char szDatabase[128];
	char* fun = "main";

	skip = 0;
	srvUndertake.DATUM = 0;
    strcpy( szDatabase, DATABASE); 
	for ( i = 1; i < argc; i++ )
	{
      if ( skip )
	  {
         skip = 0;
         continue;
	  }
      schalter = argv[i];
      if ( !strcmp( schalter, "-ld" ) )
      { 
		 srvUndertake.DATUM = atol(argv[i+1]); /*wegen der ladedatum-ermittlung!*/
		 skip = 1;
	  }
      else if ( !strcmp( schalter, "-db" ) )
      { 
		 strcpy( szDatabase, argv[i+1]); 
		 skip = 1;
	  }
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;
		}
      else
      {
      printf( "  usage: %s\n\t{ -ld <yyyymmdd> -db <database>]\n\t", argv[0] );
      return 2;
      }
    }                                            
   
    if ( !OpenLogfile( "tpldanru" ) )
    {
	   printf( "can't open the specified logfile\n" );
	   return 1;
    }
    else if ( !WriteLog(fun, 0, "Programm gestartet") )    /* always true */
    {
	  return 2;
    }
    else if ( !OpenDatabase(szDatabase, &stError, &sBranchNo) )
    {
      printf( "Datenbank konnte nicht geöffnetet werden!\n" );
	  WriteLog( fun, -1, "Programm-Abbruch" );
 	  return 3;
    }
	else if ( !CheckEntriesPhon(&lEntriesPhon, &srvUndertake, &stError, sBranchNo, &lLoadDate)	)
	{
		sprintf(cError,"%s (%ld)", stError.spError, stError.lSqlcode );
       WriteLog( fun, -1, cError );  
 	   return 3;
	}

	if ( lEntriesPhon > 0 )
	{
		sprintf(cError,"Es sind fuer den %ld schon %ld Phon-Sätze geladen!", lLoadDate, lEntriesPhon );  
       WriteLog( fun, 0, cError );  
	}
	if ( lEntriesPhon == 0 )
	{
   	   long lDate = srvUndertake.DATUM;
	   if ( Mcallplanundertake_UndertakeCallplanPhon(&srvUndertake, &stError, TRUE) != IS_OK )
	   {
			sprintf(cError,"%s (%ld)", stError.spError, stError.lSqlcode );
			WriteLog( fun, -1, cError );  
 	      return 3;
	   }

	   srvUndertake.DATUM = lDate;
	   if ( !CheckEntriesPhon(&lEntriesPhon, &srvUndertake, &stError, sBranchNo, &lLoadDate) )
	   {
			sprintf(cError,"%s (%ld)", stError.spError, stError.lSqlcode );
			WriteLog( fun, -1, cError );  
 	      return 3;
	   }

       WriteLog( fun, 0, "Es wurden %ld Phon-Saetze fuer Datum %ld geladen", lEntriesPhon, lLoadDate );  
	}

	lDelDate = SubToDate(GetMachineDate(), 7);

	if ( DeletePhon( &srvUndertake, sBranchNo, lDelDate, &stError ) ) 
	{
		sprintf(cError,"Phon-Saetze aelter als Datum %ld geloescht", lDelDate );  
		WriteLog( fun, 0, cError );  
	}
	else
	{
		sprintf(cError,"%s: %ld/%ld Phon-Saetze loeschen", stError.spError, stError.lSqlcode, stError.lSqlcisam );  
		WriteLog( fun, -1, cError );  
	}

	srvLadeAnrufplan.VERTRIEBSZENTRUMNR = sBranchNo;
	srvLadeAnrufplan.LADEDATUM = SubToDate(GetMachineDate(), 1 ); 

	if ( Mcallplanload_DelCallPlanLoadOlder( &srvLadeAnrufplan, &stError, TRUE ) != IS_OK )
	{
		sprintf(cError,"%s: %ld/%ld Ladeanrufplan konnte nicht bereinigt werden", stError.spError, stError.lSqlcode, stError.lSqlcisam );
		WriteLog( fun, 0, cError );  
	} 

//    CloseDb(&stError);
	WriteLog(fun, 0, "Programm beendet");
	CloseLogfile();
	return 0;
}

