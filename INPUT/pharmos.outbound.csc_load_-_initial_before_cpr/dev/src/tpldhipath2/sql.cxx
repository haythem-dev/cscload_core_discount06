#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "sql.h" 

exec sql include sqlca;


static void DecimalPoint( char *spBuf );
static long Exp10( int iExp );


/*** OPEN-DB *****************************************************************/
retClient OpenDb( const char *spDatabase, tError *stError )
{
	exec sql begin declare section;
		char *sqlDb = (char*)spDatabase;
	exec sql end declare section;
	
	char *fun = "OpenDb"; 
	exec sql database :sqlDb;
	return CheckSql( fun, stError, "open %s", spDatabase );
}
/*** CONNECT-DB **************************************************************/
retClient ConnectDb( const char* spDatabase, const char* spConnect, const char* spUser, const char* spPW, tError *stError )
{
	exec sql begin declare section;
		char szSQL[1024];
		char* sqlDb		= (char*) spDatabase;
		char* sqConn	= (char*) spConnect;
		char* spUsr		= (char*) spUser;
		char* spPass	= (char*) spPW;
	exec sql end declare section;
	
	char *fun = "ConnectDb";
	strcpy( szSQL, spDatabase );
	strcat( szSQL, " as '" );
	strcat( szSQL, spConnect );
	strcat( szSQL, "' user '" );
	strcat( szSQL, spUser );
	strcat( szSQL, "' ");
	strcat( szSQL, "using ");
	strcat( szSQL, "'");
	strcat( szSQL, spPW);
	strcat( szSQL, "'");
	/* exec sql connect to :szSQL using :spPW; */
	/* exec sql connect to 'rrcustom@ol_tkwsma9' as 'con1' user 'vksc' using :_szPW; */

	exec sql connect to :sqlDb as :sqConn user :spUsr using :spPass;

	return CheckSql( fun, stError, "connect %s", spDatabase );
}	 
/*****************************************************************************/
/* retClient Disconnect( const char* spConn) */ 
/*****************************************************************************/
retClient DisconnectDB( const char* spConn, tError *stError  )
{
	exec sql begin declare section;
		char* spConnection = (char*) spConn;
	exec sql end declare section;
		
	char *fun = "Disconnect";
	
	exec sql disconnect :spConnection;
	return CheckSql( fun, stError, "disconnect %s", spConnection );
}
/*** CLOSE-DB ****************************************************************/ 
retClient CloseDb( tError *stError )
{
	char *fun = "CloseDb"; 
	exec sql close database;	 
	return CheckSql( fun, stError, "close Database" );
}	 

/*** SET-ISOLATION ***********************************************************/
retClient SetIsolation( sqlread iSqlRead, tError *stError )
{
	char *fun = "SetIsolation"; 
	char msg[20];

	*msg = '\0';
	switch( iSqlRead )
	{
		case DIRTY_READ:		exec sql set isolation to dirty read; 
								break;
		case COMMITTED_READ:	exec sql set isolation to committed read; 
								break;
		case CURSOR_STABILITY:	exec sql set isolation to cursor stability; 
								break;
		case REPEATABLE_READ:	exec sql set isolation to repeatable read; 
								break;                      
		default:				sqlca.sqlcode = -1; strcpy( msg, "wrong parameter" );
	}

	return CheckSql( fun, stError, "Set Isolation %s", msg );
}   

/*** SET-LOCK MODE ***********************************************************/
retClient SetLockMode( int iSec, tError *stError )
{
	exec sql begin declare section;
		char szPrepare[40]; 
	exec sql end declare section;
	
	char *fun = "SetLockMode"; 

	if( iSec <= 0 ){ 
		strcpy( szPrepare, "set lock mode to not wait" );   
	} else {
		sprintf( szPrepare, "set lock mode to wait %d", iSec > 60 ? 60 : iSec );   
	}

	exec sql prepare PlockMode from :szPrepare;             
	if( sqlca.sqlcode == 0 )
		exec sql execute PlockMode; 

	return CheckSql( fun, stError, "set lock mode to wait %d", iSec );
}   

/*** SET-EXPLAIN-ON **********************************************************/
/*
#if !defined (__S390IBM__) && !defined (__ORACLE__)
retClient SetExplainOn( tError *stError )
{
char *fun = "SetExplainOn"; 
exec sql set explain on;
return CheckSql( fun, stError, "explain on" );
}   
#endif
*/

/*** SET-EXPLAIN-OFF *********************************************************/
/*
#if !defined  (__S390IBM__) && !defined (__ORACLE__)
retClient SetExplainOff( tError *stError )
{
char *fun = "SetExplainOff"; 
exec sql set explain off;
return CheckSql( fun, stError, "explain off" );
}   
#endif
*/

/*** BEGIN *******************************************************************/
retClient Begin( const char *spFun, tError *stError )
{
	exec sql begin work;
	return CheckSql( spFun, stError, "begin" );
}

/*** COMMIT ******************************************************************/
retClient Commit( const char *spFun, tError *stError )
{
	exec sql commit work;
	return CheckSql( spFun, stError, "commit" );
}

/*** ROLLBACK ****************************************************************/
retClient Rollback( const char *spFun, tError *stError )
{
	exec sql rollback work;
	return CheckSql( spFun, stError, "rollback" );
}

/*** GET-NUMBER-OF-BRANCH ****************************************************/
/*
retClient GetNumberOfBranch( void *vBranchNo, dataTyp d, tError *stError )
{
exec sql begin declare section;
short sBranchNo;
exec sql end declare section;
char *fun = "GetNumberOfBranch";

#ifdef _PHOSIX_
exec sql select filialnr into :sBranchNo from filiale;
#else
sqlca.sqlcode = 0;
if ( getenv( "BRANCH_NO" ) == NULL )
	sqlca.sqlcode = -1; 
else if ( ( sBranchNo = (short)atoi( (char *)getenv( "BRANCH_NO" ) ) ) == 0 )
   sqlca.sqlcode = -1;
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

return CheckSql( fun, stError, "select from filiale" );
}
*/
/*** GetValueOfStream ********************************************************/
/*
int GetValueOfStream( char *spBuf, void *vValue, int iLen, dataTyp dTyp )    
{                                                             
char *pPtr;                                                 
char *pCop;                                                 
char szConv[256];                                            
int iCount;                                                     
                                                          
pPtr = spBuf + iLen;                                          
pCop = pPtr;                                                 
                                                          
for( iCount=0; *pPtr != '|' && *pPtr != '\0'; pPtr++, iCount++  );      

if ( iCount )
{
   memcpy( szConv, pCop, iCount );                                    
   szConv[iCount] = '\0';                                            

   switch( (int)dTyp )                                                           
   {                                                                          
     case D_STRING: strcpy( (char *)vValue, szConv ); break;                     
     case D_INT   : *(int *)vValue = (int)atoi( szConv ); break;                 
     case D_LONG  : *(long *)vValue = (long)atol( szConv ); break;               
     case D_SHORT : *(short *)vValue = (short)atoi( szConv ); break;             
     case D_CHAR  : *(char *)vValue = (char)szConv[0]; break;                    
     case D_DOUBLE: DecimalPoint( szConv ); *(double *)vValue = atof( szConv ); break;
     case D_FLOAT : DecimalPoint( szConv ); *(float *)vValue = (float)atof( szConv ); break;
     default      : vValue = (void *)0;                            
   }
}
else
{
*/
	/* while null-value! */
/*  
 switch( (int)dTyp )                                                           
   {                                                                          
     case D_STRING: strcpy( (char *)vValue, " " ); break;                     
     case D_INT   : *(int *)vValue = (int)0; break;                 
     case D_LONG  : *(long *)vValue = (long)0; break;               
     case D_SHORT : *(short *)vValue = (short)0; break;             
     case D_CHAR  : *(char *)vValue = ' '; break;                    
     case D_DOUBLE: *(double *)vValue = (double)0; break;
     case D_FLOAT : *(float *)vValue = (float)0; break;
     default      : vValue = (void *)0;                            
   }
}

if ( *pPtr == '\0' || *(pPtr+1) == '\0' || *(pPtr+1) == '\n' )              
   return 0;                                                             
return iCount + iLen + 1;                                                     
}
*/

/*** GetValueOfStreamLen *****************************************************/
/*
int GetValueOfStreamLen( char *spBuf, void *vValue, int iLen, int iByte,
	                  dataTyp dTyp, int iDec )    
{                                                             
char szConv[256];                                            

if ( iByte > 255 )
   return 0;

memcpy( szConv, spBuf + iLen, iByte );                                    
szConv[iByte] = '\0';                                            

switch( (int)dTyp )                                                           
{                                                                        
  case D_STRING: strcpy( (char *)vValue, szConv ); break;                     
  case D_INT   : *(int *)vValue = (int)atoi( szConv ); break;                 
  case D_LONG  : *(long *)vValue = (long)atol( szConv ); break;               
  case D_SHORT : *(short *)vValue = (short)atoi( szConv ); break;             
  case D_CHAR  : *(char *)vValue = (char)szConv[0]; break;                    
  case D_DOUBLE: DecimalPoint( szConv );
		         if ( iDec )
		            *(double *)vValue = (double)((double)atol( szConv ) /
						                Exp10( iDec ) );
				 else
					*(double *)vValue = atof( szConv );
				 break;
  case D_FLOAT : DecimalPoint( szConv );
		         if ( iDec )
		            *(float *)vValue = (float)((float)atol( szConv ) /
						                Exp10( iDec ) );
				 else
					*(float *)vValue = (float)atof( szConv );
				 break;
  default      : vValue = (void *)0;                            
}                                                                        
return iByte + iLen;                                                     
}
*/

/*** CHECK-SQL ***************************************************************/
retClient CheckSql( const char *spFun, tError *stError, char *spForm, ... )
{
	va_list ptr_vaList;

	stError->lSqlcode  = sqlca.sqlcode;
	stError->lSqlcisam = sqlca.sqlerrd[1];
	stError->lUpdateNo = sqlca.sqlerrd[2];

	if( sqlca.sqlcode == 0 ){
		return IS_OK;      
	} else if ( sqlca.sqlcode == SQLNOTFOUND ){
		sprintf( stError->spError, "%s: SqlNotFound", spFun );
		return IS_NOTFOUND;
	} else if ( sqlca.sqlcode == SQLEXISTS ){
		sprintf( stError->spError, "%s: Record already exists", spFun );
		return IS_EXISTS;
	} else {    
		va_start( ptr_vaList, spForm );
		sprintf( stError->spError, "%s %ld/%ld ", spFun, sqlca.sqlcode, sqlca.sqlerrd[1] );
		vsprintf( stError->spError + strlen( stError->spError ), spForm, ptr_vaList );
		va_end( ptr_vaList );
		return IS_ERROR;
	}      
}

/*** private *****************************************************************/
/*** DecimalPoint ************************************************************/
static void DecimalPoint( char *spBuf )
{
	int i;
	int iLen;

	for( i = 0, iLen = strlen( spBuf ); i < iLen; i++ )
	{
		if( spBuf[i] == ',' ){
			spBuf[i] = '.';
			break;
		}
	}
	return;
}

/*** DecimalPoint ************************************************************/
static long Exp10( int iExp )
{
	long lValue = 1;                  
	int i;                         
                        
	for( i = 0; i < iExp; i++ )   
		lValue = lValue * 10;            
	
	return lValue;                    
}
/*** END *********************************************************************/
