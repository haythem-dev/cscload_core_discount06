// hDynBuf.cpp : implementation file
//

#include "stdafx.h"

#include "hDynBuf.h"

#include <libscsvoodoo/libscsvoodoo.h>
#include <libscsvoodoo/calcpos.h>
//#include <dyntypes.h>
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// ChDynBuf

ChDynBuf::ChDynBuf()
{
	m_nColumnNameIndex = -1;
	m_nColumnIndex  = -1;
	m_StruDesc.buf  = NULL;
	m_StruDesc.sqld = 0;
	m_StruDesc.sqs  = NULL;
}

ChDynBuf::~ChDynBuf()
{
	FreeFetchBuf(  );
}


/* ---------------------------------------------------------------------- *
 *  Dynamische Puffer                                                     *
 * ---------------------------------------------------------------------- */

void ChDynBuf::InternFreeFetchBuf ( struct sqld_struct *sqldat )
{
	int i;

	for ( i = 0; i < sqldat->sqld; i++ )
	{
		free ( sqldat->sqs[i]->sqlcolumn );
		free ( sqldat->sqs[i] );
	}
	free( sqldat->sqs );
	if ( sqldat->buf != NULL ) free( sqldat->buf );
}

int ChDynBuf::sonlng( char *str, char son )
{
	int i;
	i = 0;
	while ( *str++ != son ) i++;
	return i;
}


int ChDynBuf::InternAllocFetchBuf( char *bas, struct sqld_struct *sqldat,
					  			   bool bAllocBuf )
{
    int  lng;
    int  bufpos;
    int  maxlng;
	int  number;
    int  size;
    int  i;
    int  ok;
    char type;
    char *str;
    char *ba;
    struct sqlv_struct *sq;

    /* Anzahl Felder zaehlen */
    ba = bas;
    i  = 0;
    while ( *ba )
	{
       type = *ba++;
       if ( type == DT_CHAR  || type == DT_VCHAR ||
            type == DT_NCHAR || type == DT_NVCHAR   )
           while ( *ba >= '0' && *ba <= '9' ) ba++;
       ba += sonlng( ba, DT_TRENNER ) + 1;
       i++;
	}
    sqldat->sqld = i;

    sqldat->buf = NULL;
    sqldat->sqs =
        ( struct sqlv_struct ** ) malloc( i*sizeof( struct sqlv_struct ** ) );
    if ( sqldat->sqs == NULL)  return 0;

    bufpos = 0;
    maxlng = 0;

    i  = 0;
    ok = 1;
    ba = bas;

    while ( *ba && ok )
	{
		type = *ba++;
		if ( type == DT_CHAR  || type == DT_VCHAR ||
			 type == DT_NCHAR || type == DT_NVCHAR   )
		{
			size = atoi( ba );			// Nettolaenge		   	
			number = size + 1;			// Nettolaenge + 1
			while ( *ba >= '0' && *ba <= '9' ) ba++;
		}
		else
		{
			size  = 11;		// bei long !!!!!!!!!!!!!!!    
			number = 1;		// ein Stueck des betreffenden Datentyps 
		}

		lng  = sonlng( ba, DT_TRENNER );
		if ( maxlng < lng ) maxlng = lng;
		sq   = ( struct sqlv_struct *) malloc( sizeof( struct sqlv_struct));
		if ( sq != NULL)
		{
			str = ( char *) malloc( lng + 1 );
			if ( str != NULL)
			{
				memcpy( str, ba, lng);
				str[lng] = '\0';
				ba += lng + 1;

				sq->sqlcolumn = str;
				sq->sqltype   = type;
				sq->sqlpos    = DtType_CalcStructPos( type, number, &bufpos );
				sq->sqldatasize = size;
				sqldat->sqs[i++] = sq;
			}
			else
			{
				free( sq );
				ok   = 0;
			}
		}
		else
		{
			ok = 0;
		}
	}

	if ( ok )
	{
		sqldat->maxcolnamesize = maxlng;

		i = sizeof ( void * );
		if ( bufpos % i != 0 )              /* Ausrichtung */
			bufpos += i - bufpos % i;
		sqldat->structsize = bufpos;

		if ( bAllocBuf )
		{
			sqldat->buf = malloc( bufpos );
			ok = ( sqldat->buf != NULL);
		}
	}
	else
	{
		sqldat->sqld = i;   /* !!! aktuelle Anzahl !!!!! */
	}

	if ( !ok ) InternFreeFetchBuf ( sqldat );

	return ok;
}



void ChDynBuf::FreeFetchBuf (  )
{
	InternFreeFetchBuf( &m_StruDesc );
	m_nColumnNameIndex = -1;
	m_nColumnIndex  = -1;
	m_StruDesc.buf  = NULL;
	m_StruDesc.sqld = 0;
	m_StruDesc.sqs  = NULL;
}

int  ChDynBuf::AllocFetchBuf( char *bas, bool bAllocBuf )
{
	return InternAllocFetchBuf( bas, &m_StruDesc, bAllocBuf );
}


long ChDynBuf::GetFetchBufferDesc( int nFd, CString& cErrmld )
{
	int  lng;
	long s;
	char *info;

    lng = 0;
    s = SqlColumns ( nFd, NULL, &lng );

    if ( lng <= 0 )
	{
		cErrmld = "SqlColumns: Tabellen-Info-Laenge kann nicht gelesen";
		return 1;
	}

    info = ( char *) malloc( lng );
    if ( info == NULL )
	{
		cErrmld = "Info kann nicht allokiert werden";
        return 1;
	}
	s = SqlColumns ( nFd, info, &lng );
	if ( s != 0 )
	{
		free( info );
		cErrmld = "SqlColumns: Tabellen-Info kann nicht gelesen";
        return s;
	}

	FreeFetchBuf(  );	// !!!!!!!!!!!!!!!!!!!!!

	if ( ! AllocFetchBuf( info, false ) )
	{
		free( info );
        cErrmld = "Fetch-Puffer-Beschreibung kann nicht allokiert werden";
        return 1;
	}
	
//	AfxMessageBox( info );
	free( info );
	return 0;
}


char* ChDynBuf::GetNextColumnName( int& size )
{
	if ( m_nColumnNameIndex >= 0 && m_nColumnNameIndex < m_StruDesc.sqld )
	{
		struct sqlv_struct *sq;
		sq = m_StruDesc.sqs[m_nColumnNameIndex++];
		size = sq->sqldatasize;
		return sq->sqlcolumn;
	}
	m_nColumnNameIndex = -1;
	size = 0;
	return NULL;
}


char* ChDynBuf::GetFirstColumnName( int& size )
{
	m_nColumnNameIndex = 0;
	return GetNextColumnName( size );
}

int ChDynBuf::GetColumnNumber( )
{
	return m_StruDesc.sqld;
}


void ChDynBuf::out_dbl( char *zeile, double d )
{
    int i;
    int j;
    char str[30];

    sprintf( str, "%.9f", d );

    j = 0;
    while ( str[j] && str[j] != '.' ) j++;
    if ( str[j] )
	{
        i = static_cast<int>(strlen( str )) - 1;
        while ( i >= j && str[i] == '0' ) i--;
        if ( i == j ) str[++i] = '0';
        str[++i] = '\0';
	}
    sprintf( zeile, "%s", str );
}



char* ChDynBuf::GetColumn( char *buf, struct sqlv_struct *sq )
{
    static char zeile[30];
    char *str;
	
	str = zeile;
	switch ( sq->sqltype )
	{
	case DT_CHAR:
	case DT_VCHAR:
	case DT_NCHAR:
	case DT_NVCHAR:
         str = &buf[sq->sqlpos];
         break;
	case DT_LONG:
	case DT_SERIAL:
		sprintf( zeile, "%ld",  *( long * )  &buf[sq->sqlpos] );
		break;
	case DT_DATE:
		sprintf( zeile, "%ld",  *( long * )  &buf[sq->sqlpos] );
//		Ifx_datestr( *( long * ) &buf[sq->sqlpos], zeile );
		break;
	case DT_SHORT:
		sprintf( zeile, "%d",   *( short * ) &buf[sq->sqlpos] );
		break;
	case DT_FLOAT:
		sprintf( zeile, "%f",   *( float *) &buf[sq->sqlpos] );
		break;
	case DT_DOUBLE:
	case DT_DECIMAL:
	case DT_MONEY:
//		sprintf( zeile, "%f",   *( double *) &buf[sq->sqlpos] );
		out_dbl( zeile, *( double *) &buf[sq->sqlpos] );
		break;
	}

    return str;
}


char* ChDynBuf::GetNextColumn( char *buf )
{
	if ( m_nColumnIndex >= 0 && m_nColumnIndex < m_StruDesc.sqld )
	{
		struct sqlv_struct *sq;
		sq = m_StruDesc.sqs[m_nColumnIndex++];
		return GetColumn( buf, sq );
	}
	m_nColumnIndex = -1;
	return NULL;
}


char* ChDynBuf::GetFirstColumn( char *buf )
{
	m_nColumnIndex = 0;
	return GetNextColumn( buf );
}

