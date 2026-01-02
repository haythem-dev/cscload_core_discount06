/*****************************************************************************/
/*                                                                           */
/*   header     : DadeDb.cxx                                                 */
/*   Author     : A. Schmidt-Rehschuh (644)                                  */
/*   made       : 01.09.97                                                   */
/*   language   : C/Esql                                                     */
/*                                                                           */
/*   declaration: standard-functions for database calls. made for dade       */
/*                                                                           */
/*****************************************************************************/

/*** INCLUDE *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "dadedb.h"

exec sql include sqlca;

/*** SET-ISOLATION ***********************************************************/

retClient SetIsolation( sqlread iSqlRead, tError *stError )
{
    char *fun = "SetIsolation";
    char msg[20];

    *msg = '\0';
    switch( iSqlRead )
    {
    case DIRTY_READ     : exec sql set isolation to dirty read; break;
    case COMMITTED_READ : exec sql set isolation to committed read; break;
    case CURSOR_STABILITY: exec sql set isolation to cursor stability; break;
    case REPEATABLE_READ : exec sql set isolation to repeatable read; break;
    default              : sqlca.sqlcode = -1; strcpy( msg, "wrong parameter" );
    }

    return CheckSql( fun, stError, "Set Isolation %s", msg );
}

/*** BEGIN *******************************************************************/

retClient Begin( char *spFun, tError *stError )
{
    exec sql begin work;
    return CheckSql( spFun, stError, "begin" );
}

/*** COMMIT ******************************************************************/

retClient Commit( char *spFun, tError *stError )
{
    exec sql commit work;
    return CheckSql( spFun, stError, "commit" );
}

/*** ROLLBACK ****************************************************************/

retClient Rollback( char *spFun, tError *stError )
{
    exec sql rollback work;
    return CheckSql( spFun, stError, "rollback" );
}

/*** CHECK-SQL ***************************************************************/

retClient CheckSql( char *spFun, tError *stError, char *spForm, ... )
{
    va_list ptr_vaList;

    stError->lSqlcode  = sqlca.sqlcode;
    stError->lSqlcisam = sqlca.sqlerrd[1];
    stError->lUpdateNo = sqlca.sqlerrd[2];
    sprintf(stError->spErrm,"%47.47s",sqlca.sqlerrm);

    if ( sqlca.sqlcode == 0 )
        return IS_OK;
    else if ( sqlca.sqlcode == SQLNOTFOUND )
    {
        sprintf( stError->spError, "%s: SqlNotFound", spFun );
        return IS_NOTFOUND;
    }
    else if ( sqlca.sqlcode == SQLEXISTS )
    {
        sprintf( stError->spError, "%s: Record already exists", spFun );
        return IS_EXISTS;
    }
    else
    {
        va_start( ptr_vaList, spForm );
        sprintf( stError->spError, "%s %d/%d %47.47s",
            spFun,
            sqlca.sqlcode,
            sqlca.sqlerrd[1],
            sqlca.sqlerrm );
        vsprintf( stError->spError + strlen( stError->spError ), spForm, ptr_vaList );
        va_end( ptr_vaList );
        return IS_ERROR;
    }
}

/*** END *********************************************************************/
