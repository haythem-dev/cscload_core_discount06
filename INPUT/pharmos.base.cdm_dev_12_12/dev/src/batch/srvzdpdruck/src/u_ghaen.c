
#include <stdio.h>                                
#include <stdlib.h>
#include <string.h>

#include <libscsvoodoo.h>
//#include <konvbuf.h>
#include <tabsqld.h>
#include <zartikel.h>

void GetDelimiter( char *info, char *delim );
char *GetNrFromSql( char *cNr, long *nr );
int NrInSql( char *cSqlAnf, char *strNr, int anz );

static long m_nDatumVon;
static long m_nDatumBis;

static int m_iNr = -1;

#define MAX_NEM 8000

#define MAX_UEB  780

static long Lese_Protinfo( char *cKennz, char *cSql, int *akt_anz, int max_anz, char *cErrmld )
{
    int  fd; 
    long s;
    long protokol_nr;
    long akt_protokol_nr;
    char akt_image;
    char image[10];
    char teil[10];
    char info[200];
    char buf_before[2000];
    char buf_after[2000];
    char delim_before;
    char delim_after;
    int  diff_before;
    int  diff_after;
    int  i;
    int  anz;
    char zart_before[2000];
    char zart_after[2000];
    char gh_before;
    char gh_after;

    char strNr[10];
    char *cSqlAnf;

    char errmld[100];
    struct sqltab_struct *tab_desc;

    *akt_anz = 0;

    cSqlAnf = &cSql[strlen( cSql )];

    sprintf( buf_before, 
             "select protokol_nr,image,teil,info from protinfo where " \
             "protokol_nr in (select protokol_nr from protokol where " \
             "relation='zartikel' and datum>=%ld and datum <=%ld and aenderungsart='2' and anwender='IFA') " \
             "order by protokol_nr,image,teil",
              m_nDatumVon, m_nDatumBis );

    s = SqlOpenCs( &fd, buf_before );
    if ( s != 0 )
    {
        strcpy( cErrmld, DynErrmld() );
        return s;
    }

    s = SqlFetch( fd, 1, &protokol_nr, image, teil, info, NULL ); 
    if ( s != 0 )
    {
        strcpy( cErrmld, DynErrmld() );
        SqlCloseCs( fd );
        if ( s == 100 )
            strcpy( cErrmld, "Keine IFA-Artikelaenderung im angegebenen Zeitraum" );
        return s;
    }

    s = SqlGetTabDesc( "zartikel", ( void ** ) &tab_desc, DESC_COLNAMES, cErrmld );
    if ( s != 0 )
    {
        SqlCloseCs( fd );
        return s;
    }

    anz = 0;
    do
    {
        akt_protokol_nr = protokol_nr;
        akt_image = *image;
        *buf_before = '\0';
        do
        {
            strcat( buf_before, info );
            s = SqlFetch( fd, 1, &protokol_nr, image, teil, info, NULL );  
        }   while ( s == 0 && protokol_nr == akt_protokol_nr && *image == akt_image );

        if ( s == 0 && protokol_nr == akt_protokol_nr )
        {
            akt_image = *image;
            *buf_after = '\0';
            do
            {
                strcat( buf_after, info );
                s = SqlFetch( fd, 1, &protokol_nr, image, teil, info, NULL );  
            }   while ( s == 0 && protokol_nr == akt_protokol_nr && *image == akt_image );

            GetDelimiter( buf_before, &delim_before );
            GetDelimiter( buf_after , &delim_after  ); 
            diff_before = SqlLoadTabBuf( buf_before, delim_before, zart_before, tab_desc, errmld );
            diff_after  = SqlLoadTabBuf( buf_after,  delim_after,  zart_after,  tab_desc, errmld );
            if ( diff_before != diff_after )
            {
                s = 4712;
                strcpy( cErrmld, "SqlLoadBuf: Konsistenz-Error" );
            }
            else
            {
                long nummer;
                nummer = (( struct ZARTIKEL *) zart_before )->ARTIKEL_NR;
                if ( nummer == (( struct ZARTIKEL *) zart_after )->ARTIKEL_NR ) 
                {
                    gh_before = *(( struct ZARTIKEL *) zart_before )->NICHTUEBERGH;
                    gh_after  = *(( struct ZARTIKEL *) zart_after  )->NICHTUEBERGH;
                    if ( gh_before != gh_after && gh_after == '1' )
                    {
                        sprintf( strNr, "%ld,", nummer );
                        i = NrInSql( cSqlAnf, strNr, anz );
                        if ( i != -1 )
                        {
                            cKennz[i] = gh_after;  
                        }
                        else
                        {
                            cKennz[anz] = gh_after;   
                            strcat( cSql, strNr );
                            anz++;
                        }
                    }
                }
                else
                {
                    s = 4713;
                    strcpy( cErrmld, "BufBefor, BufAfter: ungleiche Artikel-Nummern" );
                }
            } 
        } 
        else
        {
            s = 4711;
            strcpy( cErrmld, "Fehler in Protokolldatei" );
        }
    } while ( s == 0 && anz < max_anz );


    cSql[ strlen( cSql ) - 1 ] = '\0';  /* Komma am Ende entfernen */

    if ( s == 100 )
        s = 100;
    else if ( s < 0 )
        strcpy( cErrmld, DynErrmld() );
    else if ( s == 0 )
        sprintf( cErrmld , "maximale Anzahl ( %d ) erreicht", anz );

    SqlFreeTabDesc ( tab_desc );
    SqlCloseCs( fd );

    *akt_anz = anz;
    
    return s;
}


static long GetSelect( int *inr, int *akt_anz, char *cNem, char *sql, char *cErrmld )
{
    long s;

    strcpy( sql, "select artikel_nr,einheit,artikel_name,darreichform,datum_ifaaender "\
                 "from zartikel where artikel_nr in (" );


    s = Lese_Protinfo( cNem, sql, akt_anz, MAX_NEM, cErrmld );

    if ( s == 100 )
    {
        if ( *akt_anz > 0 )
        {
            strcat( sql, ") order by artikel_nr" );

            /*  printf( "%s\n", sql );    */
    
            *inr = m_iNr;   /* sonst Parameterfehler */
            s = SqlStoreInstruction( sql, inr );
            if ( s != 0 )
                strcpy( cErrmld, DynErrmld() ); 
            else
            {
                if ( m_iNr == -1 )
                    m_iNr = *inr;
            }
        }
        else
        {
            s = 0;
            *inr = -1;
        }
    }
    else if ( s == 0 )
        s = 1;


    return s;
}

long Lese_Protinfo_Ghaen(  char *w_buf, int w_lng, char *r_buf, int *r_lng )
{
    long  s;
    int   akt_anz;
    int   max_anz;
    int   i;
    int   inr;
    long  nr;
    char  *buf;
    char  nem_before[2];
    char  cNem[MAX_NEM+1];
    char  sql[8*MAX_NEM+200];
    char  *cNr;

    buf = w_buf;

    buf = DtFieldConvert( TO_STRUCT,  &m_nDatumVon, buf, DT_LONG, 1 );
    buf = DtFieldConvert( TO_STRUCT,  &m_nDatumBis, buf, DT_LONG, 1 );

    s = GetSelect( &inr, &akt_anz, cNem, sql, r_buf );

    if ( s == 0 )
    {
        max_anz = MAX_UEB;
        buf = r_buf;
        buf = DtFieldConvert( FROM_STRUCT,  &inr,     buf, DT_INT,  1 );
        buf = DtFieldConvert( FROM_STRUCT,  &akt_anz, buf, DT_INT,  1 );
        buf = DtFieldConvert( FROM_STRUCT,  &max_anz, buf, DT_INT,  1 );

        if ( akt_anz <= max_anz )
        {
            nem_before[1] = '\0';
            for( i = 0; i < akt_anz; i++ )
            {
                *nem_before = cNem[i];
                buf = DtFieldConvert( FROM_STRUCT, nem_before, buf, DT_CHAR, 1 );
            }
        
            cNr = sql;
            while ( *cNr != '(' ) cNr++;
            cNr++;
            for( i = 0; i < akt_anz; i++ )
            {
                cNr = GetNrFromSql( cNr, &nr );
                buf = DtFieldConvert( FROM_STRUCT, &nr, buf, DT_LONG, 1 );
            }
        }
    }
    *r_lng = strlen( r_buf );   
    return s;                                                   
}         
