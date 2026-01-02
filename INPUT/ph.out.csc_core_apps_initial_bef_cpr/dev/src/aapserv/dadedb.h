/*****************************************************************************/
/*                                                                           */
/*   header     : DadeDb.h                                                   */
/*   Author     : A. Schmidt-Rehschuh (644)                                  */
/*   made       : 01.09.97                                                   */
/*   language   : C/Esql                                                     */
/*                                                                           */
/*   declaration: standard-functions for database calls. made for dade       */
/*                                                                           */
/*****************************************************************************/

#ifndef __DADEDB__1234
#define __DADEDB__1234

/*** Include *****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*** Type-Declaration ********************************************************/

typedef enum { DIRTY_READ = 0, COMMITTED_READ, CURSOR_STABILITY, 
	REPEATABLE_READ } sqlread;                        
typedef enum { IS_NOTUPDATED = -3, IS_WARNING = -2, IS_ERROR, IS_OK, IS_NOTFOUND,
	IS_FETCH_INTERRUPT, IS_FASTFETCH, IS_LOCKED,
	IS_EXISTS }  retClient;
typedef enum { SET_CLOSE = 0, SET_FETCH, SET_OPEN, SET_MIRROR } fHandle;   
typedef struct {
	char spError[81]; /* errormessage */
	long lUpdateNo;   /* number of columns of update/delete/insert */
	long lSqlcode;	   /* sqlca.sqlcode */
	long lSqlcisam;   /* sqlca.sqlcisam[1] */
	char spErrm[48];  /* sqlca.sqlerrm */
#if defined (__cplusplus)
	void Init()
	{
		spError[0] = '\0';
		lUpdateNo = 0;
		lSqlcode = 0;	
		lSqlcisam = 0;
		spErrm[0] = '\0';
	}
#endif
} tError;

/*** SQL-Standard-Define *****************************************************/

#define SQLNOTFOUND 100
#define SQLEXISTS   -239

/*** Declaration *************************************************************/

#if defined (__cplusplus)
extern "C" {
#endif
	retClient SetIsolation( sqlread iSqlRead, tError *stError );
	retClient Commit( char *spFun, tError *stError );
	retClient Begin( char *spFun, tError *stError );
	retClient Rollback( char *spFun, tError *stError );
	retClient CheckSql( char *spFun, tError *stError, char *spForm, ... );
#if defined (__cplusplus)
}
#endif

#endif

