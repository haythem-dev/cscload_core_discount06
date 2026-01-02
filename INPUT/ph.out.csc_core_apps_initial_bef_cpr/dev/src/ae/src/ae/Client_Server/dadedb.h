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

 #include "cprztype.h"
 #include <stdlib.h>
 #include <string.h>

/*** Type-Declaration ********************************************************/

enum sqlread { DIRTY_READ = 0, COMMITTED_READ, CURSOR_STABILITY,
               REPEATABLE_READ };
enum retClient { IS_WARNING = -2, IS_ERROR, IS_OK, IS_NOTFOUND,
                 IS_FETCH_INTERRUPT, IS_FASTFETCH, IS_LOCKED,
                 IS_EXISTS };
enum fHandle { SET_CLOSE = 0, SET_FETCH, SET_OPEN, SET_MIRROR };

struct tError {
    char spError[81]; /* errormessage */
    long lUpdateNo;   /* number of columns of update/delete/insert */
    long lSqlcode;    /* sqlca.sqlcode */
    long lSqlcisam;   /* sqlca.sqlcisam[1] */
    char spErrm[48];  /* sqlca.sqlerrm */
#if defined (__cplusplus)  || defined (__CPLUS__)
    void Init()
    {
        spError[0] = '\0';
        lUpdateNo = 0;
        lSqlcode = 0;
        lSqlcisam = 0;
        spErrm[0] = '\0';
    }
#endif
};

/*** SQL-Standard-Define *****************************************************/

    #define SQLNOTFOUND 100
    #define SQLEXISTS   -239

/*** Declaration *************************************************************/

extern "C" {
  retClient OpenDb( char *spDatabase, tError *stError );
  retClient CloseDb( tError *stError );
  retClient ConnectDb( char *spDatabase, tError *stError );

  retClient SetIsolation( sqlread iSqlRead, tError *stError );
  retClient SetLockMode( int iSec, tError *stError );
  retClient SetExplainOn( tError *stError );
  retClient SetExplainOff( tError *stError );
  retClient Commit( char *spFun, tError *stError );
  retClient Begin( char *spFun, tError *stError );
  retClient Rollback( char *spFun, tError *stError );
  retClient GetNumberOfBranch( void *vBranchNo, dataTyp d, tError *stError );
  retClient CheckSql( char *spFun, tError *stError, char *spForm, ... );
  int GetValueOfStream( char *spBuf, void *vValue, int iLen, dataTyp dTyp );
  int GetValueOfStreamLen( char *spBuf, void *vValue, int iLen, int iByte,
                           dataTyp dTyp, int iDec );
}

#endif
