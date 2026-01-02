// hDynSql.cpp : implementation file
//

#include "stdafx.h"

#include "hDynSql.h"

#include <libscsvoodoo/libscsvoodoo.h>
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// ChDynSql


#define DYNSQL_CANCEL         0
#define DYNSQL_SELECT         1
#define DYNSQL_NO_SELECT      2
#define DYNSQL_SELECT_ERROR   3

ChDynSql::ChDynSql()
{
	m_nSqlError = 0;
	m_nIsamError = 0;
	m_nSqlStatus = DYNSQL_CANCEL;
}

ChDynSql::~ChDynSql()
{
}

/* ---------------------------------------------------------------------- *
 *  Kein Select-Statement                                                 *
 * ---------------------------------------------------------------------- */

int ChDynSql::DynSql( char *sql, CString& cErrmld )
{
	long s;
	s = SqlExecuteImm( sql );
	m_nSqlError = s;
	if ( s != 0 )
	{
		cErrmld = DynErrmld();
		return 0;
	}
	return 1;
}


/* ---------------------------------------------------------------------- *
 *  Connect-Statement                                                     *
 * ---------------------------------------------------------------------- */

#define DYNSQL_NO_CONNECT  0
#define DYNSQL_CONNECT     1
#define DYNSQL_SETCONNECT  2
#define DYNSQL_DISCONNECT  3


char* ChDynSql::scan_muster( char *str, char *muster, int *s )
{
	char *sel;

	while ( *str && *str == ' ' ) str++;
	if ( *str )
	{
		sel = muster;
        while ( *str && *sel == (char) toupper( *str ) )
		{
            str++;
            sel++;
		}
        if ( *sel == '\0' && *str == ' ' )
		{
            while ( *str && *str == ' ') str++;
            *s = 0;
		}
        else
            *s = 1;
	}
    else
	{
        *s = 2;
	}
	return str;
}


char* ChDynSql::scan_connect( char *str, int *s )
{
    str = scan_muster( str, "DISCONNECT", s );
    if ( *s == 0 )
	{
        *s = DYNSQL_DISCONNECT;
        return str;
	}

    str = scan_muster( str, "SET", s );
    if ( *s == 0 )
	{
        str = scan_muster( str, "CONNECTION", s );
        if ( *s == 0 )
           *s = DYNSQL_SETCONNECT;
          else
           *s = DYNSQL_NO_CONNECT;
        return str;
	}

    str = scan_muster( str, "CONNECT", s );
    if ( *s == 0 )
	{
        str = scan_muster( str, "TO", s );
        if ( *s == 0 )
           *s = DYNSQL_CONNECT;
          else
           *s = DYNSQL_NO_CONNECT;
        return str;
	}
    *s = DYNSQL_NO_CONNECT;
    return str;
}


int ChDynSql::DynConnect( char *sql, CString& cErrmld )
{
    long s;
    int  stat;
    char db_umgeb[100];
    char verb_name[100];
    char user_id[100];
    char auth[100];
    int  with_ctrans;
    char *str;
    char *str1;
    char ze;

    s = 0;

    str = sql;
    while ( *str && *str != ' ' ) str++;
    ze = *str;
    *str = '\0';
    strcpy( db_umgeb, sql );
    *str = ze;

    strcpy( verb_name, "" );
    strcpy( user_id  , "" );
    strcpy( auth     , "" );
    with_ctrans = WITHOUT_CTRANS;


    str1 = scan_muster( str, "AS", &stat );
    if ( stat == 0 )
	{
        sql = str1;
        str = sql;
        while ( *str && *str != ' ' ) str++;
        ze = *str;
        *str = '\0';
        strcpy( verb_name, sql );
        *str = ze;
	}

    str1 = scan_muster( str, "USER", &stat );
    if ( stat == 0 )
	{
        s = 1;
        sql = str1;
        str = sql;
        while ( *str && *str != ' ' ) str++;
        ze = *str;
        *str = '\0';
        strcpy( user_id, sql );
        *str = ze;

        str1 = scan_muster( str, "USING", &stat );
        if ( stat == 0 )
		{
            s = 0;
            sql = str1;
            str = sql;
            while ( *str && *str != ' ' ) str++;
            ze = *str;
            *str = '\0';
            strcpy( auth, sql );
            *str = ze;
		}
	}

    if ( s != 0 )
	{
        cErrmld = "Syntaxfehler USER-Klausel";
        m_nSqlError = 0;
        return 1;
	}


    str = scan_muster( str, "WITH", &stat );
    if ( stat == 0 || stat == 1 )
	{
        s = 1;
        str = scan_muster( str, "CONCURRENT", &stat );
        if ( stat == 0 )
		{
            str = scan_muster( str, "TRANSACTION", &stat );
            if ( stat == 1 )
			{
               with_ctrans = WITH_CTRANS;
               s = 0;
			}
		}
	}

    if ( s != 0 )
	{
        cErrmld = "Syntaxfehler\nWITH CONCURRENT TRANSACTION Klausel";
        m_nSqlError = 0;
        return 1;
	}

    s = SqlConnectTo ( db_umgeb, verb_name, user_id, auth, with_ctrans );

    m_nSqlError = s;
    if ( s != 0 )
	{
        cErrmld = DynErrmld();
        return 0;
	}
    return 1;
}


int ChDynSql::DynDisconnect( char *sql, CString& cErrmld )
{
    long s;
    s = SqlDisconnect ( sql );
    m_nSqlError = s;
    if ( s != 0 )
	{
		cErrmld = DynErrmld();
        return 0;
	}
    return 1;
}

int ChDynSql::DynSetConnection( char *sql, CString& cErrmld )
{
    long s;
    s = SqlSetConnection( sql );
    m_nSqlError = s;
    if ( s != 0 )
	{
		cErrmld = DynErrmld();
        return 0;
	}
    return 1;
}

/* ---------------------------------------------------------------------- *
 *  Statement auf into temp scannen                                       *
 * ---------------------------------------------------------------------- */

int ChDynSql::test_begriff( char *str, char *begriff )
{
    int i;
    int lng;
    i = 0;
    lng = static_cast<int>(strlen( begriff ));
    while ( i < lng )
	{
       if ( *begriff != (char) toupper( *str ) ) return 0;
       begriff++;
       str++;
       i++;
	}
    return lng;
}


int ChDynSql::scan_into_temp( char *str )
{
    int lng;
    lng = 0;
    while ( *str && lng == 0 )
	{
        lng = test_begriff( str, "INTO" );
        if ( lng == 0 ) str++;
	}
    str += lng;
    if ( !(*str) || *str != ' ' ) return 0;

    lng = 0;
    while ( *str && lng == 0 )
	{
        lng = test_begriff( str, "TEMP" );
        if ( lng == 0 ) str++;
	}
    str += lng;
    if ( !(*str) || *str != ' ' ) return 0;
    return 1;
}


/* ---------------------------------------------------------------------- *
 *  Select-Anweisung                                                      *
 * ---------------------------------------------------------------------- */

int ChDynSql::DynSelectStmnt( char *sql, CString& cErrmld )
{
//	cErrmld = "nicht implementiert";
	return 1;
}

/* ---------------------------------------------------------------------- *
 *  Statement auf select scannen                                          *
 * ---------------------------------------------------------------------- */

int ChDynSql::scan_select( char *str )
{
    static char *select = "SELECT";
    char *sel;
    int  sql_status;

    while ( *str && *str == ' ' ) str++;
    if ( *str )
	{
        sel = select;
        while ( *str && *sel == (char) toupper( *str ) )
		{
            str++;
            sel++;
		}
        if ( *sel == '\0' && *str == ' ' )
		{
            while ( *str && *str == ' ') str++;
            if ( scan_into_temp( str ) == 0 )
               sql_status = DYNSQL_SELECT;
              else
               sql_status = DYNSQL_NO_SELECT;
		}
		else
            sql_status = DYNSQL_NO_SELECT;
	}
	else
	{
		sql_status = DYNSQL_CANCEL;
	}
    return sql_status;
}


int ChDynSql::ScanSql( CString cSql, bool bExecute, CString& cErrmld )
{
    int iOk;
    char sql[3000];

	iOk = 0;

	strcpy( sql, ( LPCTSTR ) cSql );

	m_nSqlStatus = scan_select( sql );
	if ( m_nSqlStatus == DYNSQL_NO_SELECT )
	{
		if ( bExecute )
		{
			char *str;
			int  s;
			str = scan_connect( sql, &s );
			if ( s == DYNSQL_CONNECT )
				iOk = DynConnect( str, cErrmld);
			else if ( s == DYNSQL_DISCONNECT )
				iOk = DynDisconnect( str, cErrmld );
			else if ( s == DYNSQL_SETCONNECT )
				iOk = DynSetConnection( str, cErrmld );
			else
				iOk = DynSql( sql, cErrmld );
		}
		else
			cErrmld = "Keine Select-Anweisung eingegeben";
	}
	else if ( m_nSqlStatus == DYNSQL_SELECT )
		iOk = DynSelectStmnt( sql, cErrmld );
	else if ( m_nSqlStatus == DYNSQL_SELECT_ERROR )
		cErrmld = "Fehler in der Select-Anweisung";
	else
		cErrmld = "Keine Anweisung eingegeben";
//	prog_stat = sql_status;
//	return sql_status;
	return iOk;
}

bool ChDynSql::IsSelectStmnt( )
{
	return m_nSqlStatus == DYNSQL_SELECT;
}