#define OHNE_SO 

/* ------------------------------------------------------ */
/*          srvzdpdruck.c                                 */
/* -------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>  
#include <ctype.h>  
#include <string.h>
#include <phodate.h>                    
#include <libscsvoodoo.h>        
//#include <konvbuf.h>  
#include <zartikel.h>
#include <herstel.h>
#include <zartwg.h>
#include <liefer.h>
#include "u_nwart.h"
#include "u_nwlie.h"
#include "u_ghaen.h"


/* 1.0.1 29.04.2003 : GH - Aenderungen  ( u_ghaen.c )  */
/* 1.0.2 11.05.2005 : Var. Db  */
/* 1.0.3 16.01.2006 : Hinz NEM Aenderungen neue Felder
/* 1.1.0 19.03.2013 : TH AIX build
*/

#include "../../../cdm_version.h"

static char *SCCSID =
       "@(#)PHOENIX Stand: " CDM_VERSION " - 1.1.0 : srvzdpdruck 19.03.2013 : Hajo Schmitt";





static void usage()
{
    printf( "_usage: zdpdruck mode datum_von datum_bis Database\n" \
            "                 mode = 1: Nem zartikel\n" \
            "                 mode = 2: Nem liefer\n"   \
            "                 mode = 3: GH Aenderung\n" );
}

static long getDatum( char *str )
{
    char *stra;
    stra = str;
    while ( *str && isdigit( *str ) ) str++;
    if ( *str != '\0' )
        return -1;
    return atol( stra );
}



static char GetNemAlt( long nr, char *cNem, long cNr[], int anz )
{
    int i; 
    i = 0;
    while ( i < anz && cNr[i] != nr ) i++;
    if ( i < anz )
        return cNem[i];
    else
        return ' ';
}


struct BUFF_NEMART
{
    long ARTIKEL_NR;
    char EINHEIT[L_ZARTIKEL_EINHEIT + 1];
    char ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME + 1];
    char NEM_NEU[L_ZARTIKEL_NAHRUNGSERGAENZUNG + 1];
    long DATUM_IFAAENDER;
    long HERSTELLER_NR;
    char NAME[L_HERSTEL_NAME + 1 ];
	char ZENTR_EKSPERRE[L_ZARTIKEL_ZENTR_EKSPERRE+1];
	char WARENGRUPPE[L_ZARTWG_WARENGRUPPE+1];
};


static long FetchArtikel( int iNr, char *cNem, long cNr[], int anz, char *buf )
{
    int fd;
    long s;
    char dat_str[12];
    struct BUFF_NEMART p;

    sprintf( buf, "#%d", iNr );
    s = SqlOpenCs( &fd, buf );
    if ( s != 0 )
    {
        strcpy( buf, DynErrmld() );
        return s;
    }
    while ( s == 0 )
    {
        s = SqlBufferedFetch( fd, 1, 0, &p, NULL );
        if ( s == 0 )
        {
            ConvFromPhoDate( dat_str, p.DATUM_IFAAENDER, "tt.mm.jjjj" );
    
            sprintf( buf, "%7.7ld %s %s %s  %s       %c       %5.5ld   %s %s %s",
                     p.ARTIKEL_NR,
                     p.EINHEIT,
                     p.ARTIKEL_NAME,
                     dat_str,
                     p.NEM_NEU,
                     GetNemAlt( p.ARTIKEL_NR, cNem, cNr, anz ),
                     p.HERSTELLER_NR,
                     p.NAME,  
					 p.ZENTR_EKSPERRE,
					 p.WARENGRUPPE);

            printf( "%s\n", buf );
        }
    }
    if ( s == 100 )
        s = 0;
    else
        strcpy( buf, DynErrmld() );
    SqlCloseCs( fd );
    return s;
}

/* ------------------------------------------------------ */

struct BUFF_NEMLIEF
{
    long LANT_NR;
    char LANT_NAME[L_LIEFER_LANT_NAME + 1];
    char ORT[L_LIEFER_ORT + 1];
    char NEM_NEU[L_LIEFER_NAHRUNGSERGAENZUNG + 1];
    long DATUM_IFAAENDER;
};

static long FetchLiefer( int iNr, char *cNem, long cNr[], int anz, char *buf )
{
    int fd;
    long s;
    char dat_str[12];
    struct BUFF_NEMLIEF p;

    sprintf( buf, "#%d", iNr );
    s = SqlOpenCs( &fd, buf );
    if ( s != 0 )
    {
        strcpy( buf, DynErrmld() );
        return s;
    }
    while ( s == 0 )
    {
        s = SqlBufferedFetch( fd, 1, 0, &p, NULL );
        if ( s == 0 )
        {
            ConvFromPhoDate( dat_str, p.DATUM_IFAAENDER, "tt.mm.jjjj" );
    
            sprintf( buf, "%5.5ld  %s %s %s  %s       %c",
                     p.LANT_NR,
                     p.LANT_NAME,
                     p.ORT,
                     dat_str,
                     p.NEM_NEU,
                     GetNemAlt( p.LANT_NR, cNem, cNr, anz ) ); 

            printf( "%s\n", buf );
        }
    }
    if ( s == 100 )
        s = 0;
    else
        strcpy( buf, DynErrmld() );
    SqlCloseCs( fd );

    return s;
}

/* -------------------------------------------------------------------- */

struct BUFF_GHAEN
{
    long ARTIKEL_NR;
    char EINHEIT[L_ZARTIKEL_EINHEIT + 1];
    char ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME + 1];
    char DARREICHFORM[L_ZARTIKEL_DARREICHFORM + 1];
    long DATUM_IFAAENDER;
/*
    long HERSTELLER_NR;
    char NAME[L_HERSTEL_NAME + 1 ];
*/
};


static long FetchGhaen( int iNr, char *cKenn, long cNr[], int anz, char *buf )
{
    int fd;
    long s;
    char dat_str[12];
    struct BUFF_GHAEN p;

    sprintf( buf, "#%d", iNr );
    s = SqlOpenCs( &fd, buf );
    if ( s != 0 )
    {
        strcpy( buf, DynErrmld() );
        return s;
    }
    while ( s == 0 )
    {
        s = SqlBufferedFetch( fd, 1, 0, &p, NULL );
        if ( s == 0 )
        {
            ConvFromPhoDate( dat_str, p.DATUM_IFAAENDER, "tt.mm.jjjj" );
    
            sprintf( buf, "%7.7ld %s %s %s   %s",
                     p.ARTIKEL_NR,
                     p.EINHEIT,
                     p.ARTIKEL_NAME,
                     p.DARREICHFORM, 
                     dat_str
                     );

            printf( "%s\n", buf );
        }
    }
    if ( s == 100 )
        s = 0;
    else
        strcpy( buf, DynErrmld() );
    SqlCloseCs( fd );
    return s;
}


/* -------------------------------------------------------------------- */


static long CallFunction( int fd, char *function, long nDatumVon, long nDatumBis, 
                          char *cNem, long cNr[], int *anz, int *inr, char *cErrmld, char mode)
{
    long s;
    long nr;
    char nem_before[2];
    int  r_lng;
    char w_buf[ 8000 + 81 ];
    char *buf;
    int  akt_anz;
    int  max_anz;
    int  i;

    buf = w_buf;
    buf = DtFieldConvert( FROM_STRUCT,  &nDatumVon, buf, DT_LONG, 1 );
    buf = DtFieldConvert( FROM_STRUCT,  &nDatumBis, buf, DT_LONG, 1 );


#ifdef OHNE_SO                                                                                                                      	
    if ( mode == '1' )
		s = Lese_Protinfo_Art( w_buf, strlen(w_buf), w_buf, &r_lng );
    else if ( mode == '2' )
		s = Lese_Protinfo_Lie( w_buf, strlen(w_buf), w_buf, &r_lng );
    else 
		s = Lese_Protinfo_Ghaen( w_buf, strlen(w_buf), w_buf, &r_lng );



#else
	s = UnxDlConv( fd, function,  
                   w_buf, strlen(w_buf), w_buf, &r_lng );  
#endif
    *anz = 0;
    if ( s == 0 )
    {
        buf = w_buf;
        buf = DtFieldConvert( TO_STRUCT,  &inr,     buf, DT_INT,  1 );
        buf = DtFieldConvert( TO_STRUCT,  &akt_anz, buf, DT_INT,  1 );
        buf = DtFieldConvert( TO_STRUCT,  &max_anz, buf, DT_INT,  1 );
        *anz = akt_anz;
        if ( akt_anz == 0 )
        {
            strcpy( cErrmld, "Keine Aenderung im angegebenen Zeitraum" );
            return -1;
        }
        if ( akt_anz <= max_anz )
        {
            for( i = 0; i < akt_anz; i++ )
            {
                buf = DtFieldConvert( TO_STRUCT,  nem_before, buf, DT_CHAR, 1 );
                cNem[i] = *nem_before;
            }
            for( i = 0; i < akt_anz; i++ )
            {
                buf = DtFieldConvert( TO_STRUCT, &nr, buf, DT_LONG, 1 );
                cNr[i] = nr;
            }
        }
        else
        {
/*
            CString Meld;
            Meld.Format( "NEM-alt kann nicht angezeigt werden,\n" \
                         "da die aktuelle Anzahl (%d) die maximale (%d) ueberschreitet",
                          akt_anz, max_anz );
            AfxMessageBox( Meld );
*/
        }
    }
    else
    {
/*
        w_buf[r_lng] = '\0',
        strcpy( cErrmld, w_buf );
*/
        sprintf( cErrmld, "UnxDlKonv: %ld", s );
    }
    return s;             
}

#define MAXNEM 2000


static long DoIt( char mode, long datum_von, long datum_bis, char *buf )
{
    int  fd = 0;
    long s;
    char *function;
    char cNem[MAXNEM + 1];
    long cNr [MAXNEM];
    int  anz;
    int  iNr;
#ifndef OHNE_SO
    s =  UnxGetenv( "WSS", buf );       
    if ( s != 0 )                         
    {                                     
        sprintf( buf, "%s\n", DynErrmld() );   
        return s;                            
    }                                     
    strcat( buf, "/bin/srvzdpdruck.so" );             
                                                                                  
    s = UnxDlConvOpen( &fd, buf, 0 );                     
    if ( s != 0 )                                           
    {                                                       
        sprintf( buf, "%s\n", DynErrmld() );                       
        return s;                                               
    } 
#endif    
                                                                  
    if ( mode == '1' )
        function = "Lese_Protinfo_Art";
    else if ( mode == '2' )
        function = "Lese_Protinfo_Lie";
    else 
        function = "Lese_Protinfo_Ghaen";

    s = CallFunction( fd, function, datum_von, datum_bis, cNem, cNr, &anz, &iNr, buf, mode ); 
#ifdef OHNE_SO                                                                                                                      
    UnxDlConvClose ( fd );  
#endif
    if ( s == 0 )
    {
        if ( mode == '1' )
            s = FetchArtikel( iNr, cNem, cNr, anz, buf );
        else if ( mode == '2' )
            s = FetchLiefer ( iNr, cNem, cNr, anz, buf );
        else 
            s = FetchGhaen ( iNr, cNem, cNr, anz, buf );

    }

    return s;
}

void main( int argc, char *argv[] )           
{                                        
   long s;     
   long datum_von;
   long datum_bis;
   char mode;

   char buf[300];

   if ( argc != 5 )
   {
       usage();
       exit(1);
   }
   mode = *argv[1];
   if ( !( mode == '1' || mode == '2' || mode == '3' ) )
   {
       usage();
       exit(1);
   }
   datum_von = getDatum( argv[2] );
   datum_bis = getDatum( argv[3] );
   if ( datum_von <= 0 || datum_bis <= 0 )
   {
       printf( "_Datum syntaktisch falsch\n" );
       exit(1);
   }
   if ( TestPhoDate( datum_von ) != 2 || TestPhoDate( datum_bis ) != 2 )
   {
       printf( "_Datum falsch" );
       exit(1);
   }
   if ( datum_bis > AddDayToPhoDate( datum_von, 20 ) ) 
   { 
       printf( "_Zeitraum <= 20 Tage" );
       exit(1);
   }

    
#ifdef WIN32
   {
        int handle;
        s = ViaEshuOpen( &handle, "zdev1", "uiserv" );    
        if ( s != 0 )
        {                                     
            printf( "%s\n", DynErrmld() );     
            exit(1);                           
        }
    }   
#endif

    strcpy( buf, "database " );  
    strcat( buf, argv[4] );  
    s = SqlExecuteImm( buf );
    if ( s == 0 )
    {
        s = DoIt( mode, datum_von, datum_bis, buf );
        SqlExecuteImm( "close database" );
    }
    else
        sprintf( buf, "%s", DynErrmld() );

    if ( s != 0 )                                                                                 
        printf( "_%s\n", buf );                       

    
#ifdef WIN32
    NmpClose( );  
#endif

    if ( s != 0 )                                               
        exit(1);                          
                                       
                                        
    exit( 0 );                           
}                                       
