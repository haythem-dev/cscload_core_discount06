/*****************************************************************************/
/*                                                                           */
/*   header     : tpldregiodata.c                                            */
/*   Author     : A. Schmidt-Rehschuh (644)                                  */
/*   made       : 08.02.99                                                   */
/*   language   : C                                                          */
/*                                                                           */
/*   declaration: loads articledata from a file into db-table artikelf       */
/*                                                                           */
/*****************************************************************************/

/*** Version *****************************************************************/
#include "csc_load_version.h"

#define PROJECTNAME	 "tpldregiodata"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

//static char *SCCSID=
//"@(#)PRZ GmbH Stand: 2.0.1 $Header: /prj/df/unix/tpldregiodata/tpldregiodata.c 47    8/23/01 5:15p 66aeersc $";

/*** include *****************************************************************/
 
 #include <stdio.h>
 #include <unistd.h>
 #include "libtpld/cstdio.h"
 #include "libtpld/dadedb.h"
 #include "libtpld/logfile.h"
 #include "regiodata.h"

/*** define ******************************************************************/

 #define D_LOGFILE         "wws.log"
 #define D_DATABASE	       "phosix"
 #define LOCK_MODE	       20
 #define ONE_MINUTE	       60  /* seconds */
 #define DAY_IN_SECOND     86400
 #define MAX_TRANS_INSERT  50
 #define L_DRARK           50  /* length of row */		
 #define D_HOMEDIR 		   "."

 /************************************************************/
 /* Unfortunately, I must handle the record locks themselves */
 /* it as long as I do not know, which program a 			 */
 /*	record lock holds to relation!							 */
 /************************************************************/

 #define SQLISAMDEADLOCK -143 
 #define SQLDEADLOCK     -243

/*****************************************************************************/
/*** functions ***************************************************************/
/*****************************************************************************/

extern int h_system( char *prstr );

/*** pCheckEntry *************************************************************/
 
 static bool pCheckEntry( int argc, char **argv, tInit *tInitData )
 {
   int i;
   bool bSkip;
   
   if ( argc == 1 )
	  return FALSE;

   tInitData->lDate = 0; /* here: switched for compress or uncompress */
   tInitData->spFile = (char *)0;

   bSkip = FALSE;
   for( i = 1; i < argc; i++ )
   {
	  if ( bSkip )
	  {
		 bSkip = FALSE;
		 continue;
	  }

	  if ( !strcmp( argv[i], "-db" ) )
	  {
		 tInitData->spDatabase = argv[i+1];
		 bSkip = TRUE;
	  }
	  else if ( !strcmp( argv[i], "-log" ) )
	  {
		 tInitData->spLogFile = argv[i+1];
 		 bSkip = TRUE;
	  }
      else if ( !strcmp( argv[i], "-file" ) )
	  {
         tInitData->spFile = argv[i+1];
		 bSkip = TRUE;
	  }
      else if ( !strcmp( argv[i], "-dir" ) )
	  {
         tInitData->spRemoteDir = argv[i+1];
		 bSkip = TRUE;
	  }
      else if ( !strcmp( argv[i], "-branch" ) )
	  {
         tInitData->sBranchNo = (short)atoi(argv[i+1]);
		 bSkip = TRUE;
	  }
      else if ( !strcmp( argv[i], "-compress" ) )
	  {
         tInitData->lDate = 1;
	  }
      else if ( !strcmp( argv[i], "-version" ) )
      {
         printVersion(versioninfo);
         return FALSE;
      }
	  else
		 return FALSE;
   }

   return TRUE;
 }  

/*** pCheckAgainAnStart ******************************************************/

 static bool pCheckAgainAnStart( const tError* dbError)
 {
   char *fun = "pCheckAgainAnStart";
   long lError = dbError->lSqlcode;

   if ( lError < -25000 || lError == -404 || lError == -934 || lError == -908 )
   {
      WriteLog( fun, lError, "%s: %s %ld/%ld", "Database is not available", dbError->spError, dbError->lSqlcode,  dbError->lSqlcisam ); 
      sleep( ONE_MINUTE * 5 );
	  return TRUE;
   }
   return FALSE;
 }

/*** pGetFile ***************************************************************/

 static bool pGetFile( FILE **fp, const char *spFile )
 {
   if ( spFile == (char *)0 )
	  return FALSE;
   else if ( (*fp = fopen( spFile, "r" )) == (FILE*)0)
	  return FALSE;
	return TRUE;
 }

/*** pGetFileRow ************************************************************/

 static bool pGetFileRow( const FILE *fp, regiodataS *d, const int iLen,
	                      int *iGoBack )
 {
	if ( *iGoBack )	/*start again!*/
	{
	    fseek( (FILE*)fp, (long)(*iGoBack * sizeof(regiodataS) * -1), SEEK_CUR);    
	   *iGoBack = 0;
	}

	if ( fread( (regiodataS *)d, iLen, 1, (FILE*) fp ) <= 0 )
	   return FALSE;	 
	return TRUE;
 }

 /*** Connect *****************************************************************/

 static bool Connect( tInit *tInitData, tError *dbError )
 {
    char *fun = "Connect";
	for(;;)
	{
       if ( OpenDb( tInitData->spDatabase, dbError ) != IS_OK )
	   {						      
          if ( pCheckAgainAnStart( dbError) )
			 continue;
	      WriteLog( fun, IS_ERROR, "OpenDb %ld %ld", dbError->lSqlcode, dbError->lSqlcisam );
 	      return FALSE;
	   }
       else if ( SetIsolation( DIRTY_READ, dbError ) != IS_OK )
	   { 
          if ( pCheckAgainAnStart( dbError) )
			 continue;
          WriteLog( fun, IS_ERROR, "SetIsolation %ld %ld", dbError->lSqlcode, dbError->lSqlcisam );
          return FALSE;
	   }
       else if ( SetLockMode( LOCK_MODE, dbError ) != IS_OK )
	   { 
          if ( pCheckAgainAnStart( dbError) )
			 continue;
          WriteLog( fun, IS_ERROR, "SetLockMode %ld %ld", dbError->lSqlcode, dbError->lSqlcisam );
          return FALSE;
	   }
       else if ( !DBStartBrowse( dbError, tInitData->sBranchNo )  )
	   {
          WriteLog( fun, IS_ERROR, "%s %s %ld %ld",
                   "DBStartDataWarehouse", 
                   dbError->spError, dbError->lSqlcode, dbError->lSqlcisam );
          return FALSE;
	   }
	   break;
	}
    return TRUE;
 }

/*** Uncompress *******+*******************************************************/
   
 static bool Uncompress( const tInit *tInitData )
 {
	 char szCommand[512];
	 int  rc;
	 char *fun = "Uncompress";

	 if ( tInitData->lDate == 0 ) /* file is uncompressed */
		return TRUE;

     WriteLog( fun, IS_OK, "Start uncompresse file %s", tInitData->spFile );
	 sprintf( szCommand, "uncompress %s.Z", tInitData->spFile );
	 if ( (rc = h_system( szCommand )) < 0 )
	 {
        WriteLog( fun, rc, "error in %s", szCommand );
		return FALSE;
	 }

     WriteLog( fun, IS_OK, "End rcp compressed file %s", tInitData->spFile );
	 return TRUE;
 }

/*** main *********************************************************************/

 int main( int argc, char **argv )
 {
   char *fun = "main";
   int iReturn;                               /* signal error handling */
   tError dbError;		                      /* db errorhandling */
   tInit tInitData;		                      /* initializing data */
   bool bIsError = FALSE;			          /* if an error occured */
   long lCount    = 0;							  /* row counter */
   long lCountDel = 0;                      /* deleted rows */
   long lCountIns = 0;                     /* inserted rows */
   long lCountUpd = 0;                     /* inserted rows */
   long lCountMinStock = 0;                /* updated minstock */
   int iGoBack = 0;						      /* back to a restart point */
   int iRowCount = 0;						  /* row counter per transaction */
   FILE *fp;							      /* filpointer to loading-file */
   regiodataS dataIn;
   const int iLen = sizeof(regiodataS);

   SetProgramName( "tpldregi" );		     
   tInitData.spLogFile	= D_LOGFILE;
   tInitData.spDatabase = D_DATABASE;
   tInitData.spRemoteDir = D_HOMEDIR;

   if ( !pCheckEntry( argc, argv, &tInitData ) )
   {
      printf( "tpldregiodata -db <database> /* connect to given db (standard = phosix)\n"
			  "\t\t\t-log <logfiledir> /* outputdir for logfile */\n"
			  "\t\t\t-file <load> /* loadfile from vse */\n" 
			  "\t\t\t-rcp <remotesystem> /* remotesystem */\n"
			  "\t\t\t-rdir <remotedir> /* remotedir */\n" );
	  return 1;
   }
   else if ( SetDirName( (char *)getenv("LOG_PATH" ) ) == (char *)0 )
   {
	  printf( "no logfiledir set!\n" );
	  return 2;
   }
   else if ( SetFileName( tInitData.spLogFile ) == (char *)0 )
   {
	  printf( "no logfile set!\n" );
	  return 3;
   }
   else if ( WriteLog( fun, IS_OK, "programm started (file:%s)", tInitData.spFile ) == -1 )
   {
	  printf( "can't open logfile\n" );
	  return 4;
   }		   
   else if ( ( iReturn = Signal() ) != 0 )
   {
   	  WriteLog( fun, iReturn, "%s", "Fehler in Signalbehandlung" );
 	  return 5;
   }
   else if ( !Connect( &tInitData, &dbError ) )
   {						      
 	  bIsError = TRUE;
   }
   else if ( !Uncompress( &tInitData ) )
   {
	  return 11;
   }
   else if ( !pGetFile( &fp, tInitData.spFile ) )
   {
      WriteLog( fun, IS_ERROR, "can't open file:%s", tInitData.spFile );
      return 9;
   }
   else if ( !DBInitialize( &dbError ) )
   {
      WriteLog( fun, IS_ERROR, "%s %s %ld %ld",
                "DBInitialize", 
                dbError.spError, dbError.lSqlcode, dbError.lSqlcisam );
      return 12;
   } 
   else if ( Begin( fun, &dbError ) != IS_OK )
   {
	  WriteLog( fun, IS_ERROR, "Begin %s %ld %ld",
                dbError.spError, dbError.lSqlcode, dbError.lSqlcisam );
      return 12;
   }

   /* start update in table */
   while ( !bIsError && pGetFileRow( fp, &dataIn, iLen, &iGoBack ) )
   {
	  if ( ++lCount % MAX_TRANS_INSERT == 0 )
	  {
		 if ( Commit( fun, &dbError ) != IS_OK  )
		 {
			bIsError = TRUE;
			break;
		 }
		 if ( Interrupt( 0 ) ) /* signalhandling (kill -15) */
		    break; 
	     if ( Begin( fun, &dbError ) != IS_OK )
		 {
			bIsError = TRUE;
			break;
		 }
         iRowCount = 0;
	  }

	  iRowCount++;
     
      if ( !DBGetNextRow( &dataIn, &dbError ) && dbError.lSqlcode < 0 )
	  {
		 bIsError = TRUE;
	  }
	  else if ( dbError.lSqlcode == SQLNOTFOUND )
	  {
	    if ( !DBPutData( &dataIn, &dbError ) )
		{
	       bIsError = TRUE;
		}
        else
		   lCountIns++;
	  }
	  else 
	  {
	    if ( !DBUpdData( &dataIn, &dbError ) )
		{
	       bIsError = TRUE;
		}
		else
		   lCountUpd++;
	  }
	  
	  if ( bIsError && pCheckAgainAnStart(&dbError) )
	  {  
         iGoBack = iRowCount;
	     Commit( fun, &dbError );
         if ( !Connect( &tInitData, &dbError ) )
		 {
	        bIsError = TRUE;
			break;
		 }
		 else if ( Begin( fun, &dbError ) != IS_OK )
		 {
			bIsError = TRUE;
			break;
		 }	 
		 bIsError = FALSE;
	  }
	  else if ( bIsError && (dbError.lSqlcode == SQLDEADLOCK || dbError.lSqlcisam == SQLISAMDEADLOCK) )
	  {
         iGoBack = iRowCount;		  /* rollback in the file to the last starting point */
         WriteLog( fun, 1, "Deadlock detected: %s %ld %ld",
         		   dbError.spError, dbError.lSqlcode, dbError.lSqlcisam );
		 Rollback( fun, &dbError );	  /* rollback the transaction in database */
         sleep( ONE_MINUTE * 5 );	  /* wait 5 minutes (what a long time! */
		 bIsError = FALSE;	
         if ( !Connect( &tInitData, &dbError ) )
		 {
	        bIsError = TRUE;
			break;
		 }
		 else if ( Begin( fun, &dbError ) != IS_OK )
		 {
			bIsError = TRUE;
			break;
		 }	 
	  }
	  else if ( bIsError )
		 break;
   } /* end while */

   if ( bIsError )
   {
      WriteLog( fun, IS_ERROR, "%s %ld %ld",
				dbError.spError, dbError.lSqlcode, dbError.lSqlcisam );
	  Rollback( fun, &dbError );
   }
   else if ( Commit( fun, &dbError ) != IS_OK )
   {
      bIsError = TRUE;
   }
   else if ( !DBPostprocessing( &lCountDel, &dbError ) ) /*set not touched articles to inactive*/
   {
      bIsError = TRUE;
   }
   else if ( !DBMinStockUpd( &lCountMinStock, &dbError ) ) /*set not touched articles to inactive*/
   {
      bIsError = TRUE;
   }

   if ( !DBEndBrowse( &dbError ) )
   {
      WriteLog( fun, IS_ERROR, "%s %s %ld %ld",
                "DBEndBrowse",
				dbError.spError, dbError.lSqlcode, dbError.lSqlcisam );
   }

   if ( CloseDb( &dbError ) != IS_OK )
   {
      WriteLog( fun, IS_ERROR, "%s %ld %ld",
                dbError.spError, dbError.lSqlcode, dbError.lSqlcisam );
   }

   if ( bIsError )
      WriteLog( fun, IS_ERROR, "%s loaded %ld", "programm stopped with error", lCount );
   else
   {
	   remove(tInitData.spFile);

      WriteLog ( fun
               , IS_OK
               , "%s loaded %ld deleted %ld inserted %ld updated %ld MinStock updated %ld"
               , "programm ended"
               , lCount
               , lCountDel
               , lCountIns
			   , lCountUpd
			   , lCountMinStock
               );
   }

   return 0;
 }
