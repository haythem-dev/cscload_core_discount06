/*****************************************************************************/
/*                                                                           */
/*   header     : cdb.c                                                      */
/*   Author     : A. Schmidt-Rehschuh (644)                                  */
/*   made       : 07.04.97                                                   */
/*   language   : C/Esql                                                     */
/*                                                                           */
/*   declaration: standard-functions for database calls                      */
/*                                                                           */
/*****************************************************************************/

/*** INCLUDE *****************************************************************/

 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 exec sql include sqlca;
 #include "cdb.h" 

 #ifdef __S390IBM__
 #pragma linkage(dsnali, OS)       
 #endif
 
/*** OPEN-DB *****************************************************************/

 #ifndef __S390IBM__
 bool OpenDb( char *spDatabase )
 {
   exec sql begin declare section;
   char *sqlDb;
   exec sql end declare section;

   sqlDb = spDatabase;

   exec sql database :sqlDb;
   return BOOL( sqlca.sqlcode );
 }	 
 #else	 
 bool OpenDb( char *spDatabase, char *spSsid )
 {
   char    plan[9];
   char    ssid[5];
   char    open[13] = "OPEN        ";
   long    return_code = 0;
   long    reason_code = 0;
   long    retCode;

   sprintf( plan, "%-8.8s", spDatabase );
   sprintf( ssid, "%-4.4s", spSsid );

   if ( dsnali( open, ssid, plan, &return_code, &reason_code ) )
      dsnali( "TRANSLATE   ", &sqlca, &return_code, &reason_code );
   
   return BOOL( sqlca.sqlcode );
 }	 
 #endif	 

/*** CONNECT-DB **************************************************************/
 
 #ifndef __S390IBM__
 bool ConnectDb( char *spDatabase )
 {
   exec sql begin declare section;
   char *sqlDb;
   exec sql end declare section;

   sqlDb = spDatabase;

   exec sql connect to :sqlDb;
   return BOOL( sqlca.sqlcode );
 }	 
 #else
 bool ConnectDb( char *spDatabase, char *spSsid )
 {
   char    plan[9];
   char    ssid[5];
   char	   srdura[11] = "SRDURA(CD)";
   long    return_code = 0;
   long    reason_code = 0;
   long    tecb        = 0;
   long    secb        = 0;
   long    ribptr      = 0;
   long    eibptr      = 0;

   sprintf( plan, "%-8.8s", spDatabase );
   sprintf( ssid, "%-4.4s", spSsid );

   dsnali( "CONNECT      ", ssid, tecb, &secb, &ribptr,
	       &return_code, &reason_code, srdura, &eibptr);                                                        
   dsnali( "TRANSLATE   ", &sqlca, &return_code, &reason_code );

   return BOOL( sqlca.sqlcode );
 }	 
 #endif
 
/*** CLOSE-DB ****************************************************************/
	 
 #ifndef __S390IBM__
 bool CloseDb( void )
 {
   exec sql close database;	 
   return BOOL( sqlca.sqlcode );
 }	 
 #else	 
 bool CloseDb( char *spDatabase, char *spSsid )
 {
   char    plan[9];
   char    ssid[5];
   long    return_code = 0;
   long    reason_code = 0;

   sprintf( plan, "%-8.8s", spDatabase );
   sprintf( ssid, "%-4.4s", spSsid );

   dsnali( "CLOSE        ", ssid, plan, &return_code, &reason_code );
   dsnali( "TRANSLATE   ", &sqlca, &return_code, &reason_code );
   
   return BOOL( sqlca.sqlcode );
 }	 
 #endif	 
 
/*** SET-ISOLATION ***********************************************************/
	 
 #ifndef __S390IBM__
 bool SetIsolation( sqlread iSqlRead )
 {
   switch( iSqlRead )
   {
   case DIRTY_READ		: exec sql set isolation to dirty read; break;
   case COMMITTED_READ	: exec sql set isolation to committed read; break;
   case CURSOR_STABILITY: exec sql set isolation to cursor stability; break;
   case REPEATABLE_READ : exec sql set isolation to repeatable read; break;                      
   default              : return BOOL( -1 );
   }

   return BOOL( sqlca.sqlcode );
 }   
 #else
 bool SetIsolation( sqlread iSqlRead )
 {
   return BOOL( 0 );
 }   
 #endif

/*** SET-LOCK MODE ***********************************************************/

#ifndef __S390IBM__
 bool SetLockMode( int iSec )
 {
   exec sql begin declare section;
   char szPrepare[40]; 
   exec sql end declare section;
   
   if ( iSec <= 0 ) 
      strcpy( szPrepare, "set lock mode to not wait" );   
      else
      sprintf( szPrepare, "set lock mode to wait %d", iSec > 60 ? 60 : iSec );   
   
   exec sql prepare PlockMode from :szPrepare;             
   if ( sqlca.sqlcode == 0 )
      exec sql execute PlockMode; 
 
   return BOOL( sqlca.sqlcode );
 }   
 #endif

/*** SET-EXPLAIN-ON **********************************************************/

 #ifndef __S390IBM__
 bool SetExplainOn( void )
 {
   exec sql set explain on;
   return BOOL( sqlca.sqlcode );
 }   

/*** SET-EXPLAIN-OFF *********************************************************/

 bool SetExplainOff( void )
 {
   exec sql set explain off;
   return BOOL( sqlca.sqlcode );
 }   
 #endif

/*** COMMIT ******************************************************************/

 #ifndef __S390IBM__ 
 bool Commit( void )
 {
   exec sql commit work;
   return BOOL( sqlca.sqlcode );
 }
 #else
 bool Commit( void )
 {
   exec sql commit;
   return BOOL( 0 );
 }
 #endif

/*** BEGIN *******************************************************************/

 #ifndef __S390IBM__ 
 bool Begin( void )
 {
   exec sql begin work;
   return BOOL( sqlca.sqlcode );
 }
 #else
 bool Begin( void )
 { /* ansi-c */
   return BOOL( 0 );
 }
 #endif


/*** ROLLBACK ****************************************************************/

 #ifndef __S390IBM__ 
 bool Rollback( void )
 {
   exec sql rollback work;
   return BOOL( sqlca.sqlcode );
 }
 #else
 bool Rollback( void )
 {
   exec sql rollback;
   return BOOL( 0 );
 }
 #endif

/*** ROLLBACK ****************************************************************/

 bool GetNumberOfBranch( void *vBranchNo, dataTyp d )
 {
    exec sql begin declare section;
	short sBranchNo;
	exec sql end declare section;

    #ifdef _PHOSIX_
	exec sql select filialnr into:sBranchNo from filiale;
    #else
	sqlca.sqlcode = 0;

#ifdef UNSER_UEBERFLIEGER
	if ( ( sBranchNo = atoi( (char *)getenv( "BRANCH_NO" ) ) ) != 0 )
	   sqlca.sqlcode = -1;
#else
	{
	  char *str;
	  sBranchNo = 0;
	  sqlca.sqlcode = -1;

	  if ( ( str = getenv( "BRANCH_NO" ) ) != NULL )
	  {
	     if ( ( sBranchNo = atoi( str ) ) != 0 )
		sqlca.sqlcode = 0;
	  }
	}
#endif

    #endif	 

	if ( BOOL( sqlca.sqlcode ) ) 
	{
	   switch( (int)d )
	   {
		 case D_STRING: sprintf( (char *)vBranchNo, "%02d", sBranchNo ); break;
		 case D_SHORT : *(short *)vBranchNo = (short)sBranchNo; break;
         case D_INT   : *(int *)vBranchNo = (int)sBranchNo; break;
		 case D_LONG  : *(long *)vBranchNo = (long)sBranchNo; break;
	   	 default: vBranchNo = (void *)0;
	   }
	}
	return BOOL( sqlca.sqlcode );
 }


/*** END *********************************************************************/
