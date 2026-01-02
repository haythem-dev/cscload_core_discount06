#ifndef __SQL_H__
#define  __SQL_H__ __SQL_H__


typedef enum 
{ 
	DIRTY_READ = 0, 
	COMMITTED_READ, CURSOR_STABILITY, 
    REPEATABLE_READ 
} sqlread;                        

typedef enum 
{ 
	IS_WARNING = -2, 
	IS_ERROR, 
	IS_OK, 
	IS_NOTFOUND,
	IS_FETCH_INTERRUPT, 
	IS_FASTFETCH, 
	IS_LOCKED,
	IS_EXISTS 
}  retClient;

typedef enum 
{ 
	SET_CLOSE = 0, 
	SET_FETCH, 
	SET_OPEN, 
	SET_MIRROR 
} fHandle;   

typedef struct 
{
	char spError[81]; /* errormessage */
	long lUpdateNo;   /* number of columns of update/delete/insert */
	long lSqlcode;	   /* sqlca.sqlcode: 0 = Success; 100 = No more data / not found; negative = Error Code */
	long lSqlcisam;   /* sqlca.sqlcisam[1]: if sqlcode contains an error, this field contains the ISAM error code */
	#if defined (__cplusplus)  || defined (__CPLUS__)  
		void init()
		{
			spError[0]	= '\0';
			lUpdateNo	= 0;
			lSqlcode	= 0;	
			lSqlcisam	= 0;
		}
	#endif
} tError;

#define SQLNOTFOUND 100
#define SQLEXISTS   -239

/*** Declaration *************************************************************/
#if defined (__cplusplus)  || defined (__CPLUS__)  
	extern "C" { 
#endif
	retClient OpenDb( const char *spDatabase, tError *stError );
	retClient CloseDb( tError *stError );
	retClient ConnectDb( const char *spDatabase, const char* spConnect, 
						 const char* spUser, const char* spPW, tError *stError );
	retClient DisconnectDB( const char* spConn, tError *stError );
	retClient SetIsolation( sqlread iSqlRead, tError *stError );
	retClient SetLockMode( int iSec, tError *stError );

	retClient Commit( const char *spFun, tError *stError );
	retClient Begin( const char *spFun, tError *stError );
	retClient Rollback( const char *spFun, tError *stError );
	retClient CheckSql( const char *spFun, tError *stError, char *spForm, ... );

/*
	retClient SetExplainOn( tError *stError );
	retClient SetExplainOff( tError *stError );
	retClient GetNumberOfBranch( void *vBranchNo, dataTyp d, tError *stError );
	int GetValueOfStream( char *spBuf, void *vValue, int iLen, dataTyp dTyp );    
	int GetValueOfStreamLen( char *spBuf, void *vValue, int iLen, int iByte, dataTyp dTyp, int iDec );    
	*/
#if defined (__cplusplus)  || defined (__CPLUS__)  
	}
#endif

#endif /* __SQL_H__ */
