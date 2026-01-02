
/* ---------------------------------------------------------------------- *
 *                           N _ B A S I C . C                            *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   Sortiments-Pflege                                            *
 * Modul:    Sortiment tauschen                                           *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  18.10.1994                                                   *
 * Update :  18.10.1994                                                   *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo/libscsvoodoo.h> 

#include <hdatum/phodate.h>
#include <hdatum/phozeit.h>

/* -------  Spezielle includes ----------------------------------------- */

#include <eklibs/sqltabs/tabsqld.h>

#include <eklibs/wdbups/wpp_prot.h>

#include <voodoo_table_header/bliesort.h>
#include <voodoo_table_header/artnrbl.h>
#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zaneuhei.h>
#include <voodoo_table_header/pflege.h>

#include <voodoo_table_header/hneuheit.h>

#include "n_basic.h"

#define L_ARTIKEL_NR 7
#define L_BESLA_NR   5


static char anwender[10];

/* ------ Modus 01.09.2011 ----------------- */

static int isCdcAlone;		/* = 1 Zentrale Pflegedatenbank alleine*/
						    /* = 0 Zentrale Pflegedatenbank zusammen mit zu pflegenden Datenbanken*/

/* ---------------------------------------------------------------------- *
 * Funktion         Beschreibung pflege                                   *
 * ---------------------------------------------------------------------- */

static char  PflegeTab[] = "pflege";
static void *PflDesc  = NULL;

static long InitPflegeTab( char *errmld )
{
    static int alloc_status = 0;
    static long s;
    static char smeld[80];
    if ( alloc_status == 0 )
    {
        alloc_status = 1;
        s = SqlGetTabDesc( PflegeTab, &PflDesc, DESC_DEFAULT, smeld );
    }
    if ( s != 0 )
    {
        PflDesc = NULL;
        strcpy( errmld, smeld );
    }
    return s;
}


static long InsertPflegePhysically( struct PFLEGE *Buf_Pflege, char *errmld )	/*	01.09.2011 */

{
    long s;
	char sql[300];
	sprintf( sql, "insert into pflege " \
		          "(PFLEGE_NR, DATUM, UHRZEIT, ANWENDER, STATUS, FEHLERTEXT, FUNKTION, INFO) values " \
				  "(%ld, %ld, %ld, '%s', '%s', '%s', %d, '%s')",
				  Buf_Pflege->PFLEGE_NR,
				  Buf_Pflege->DATUM,
				  Buf_Pflege->UHRZEIT,
				  Buf_Pflege->ANWENDER,
				  Buf_Pflege->STATUS,
				  Buf_Pflege->FEHLERTEXT,
				  Buf_Pflege->FUNKTION,
				  Buf_Pflege->INFO );
	s = SqlExecuteImm( sql );
	if ( s != 0 )
	{
		strcpy( errmld, "insert into pflege\n" );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		long count;
		count = SqlRowsProcessed();
		if ( count != 1 )
		{
			sprintf( errmld, "insert into pflege\n%ld rows inserted", count );
			s = -1;
		}
	}
	return s;
}


long Insert_Pflege( long besla_nr, long artikel_nr, char *errmld )
{
    long s;
    struct PFLEGE  Buf_Pflege;
	char key_select[15];
	
    Buf_Pflege.PFLEGE_NR = 0;
    Buf_Pflege.DATUM     = GetPhoDate();
    Buf_Pflege.UHRZEIT   = GetPhoTime();
    strcpy( Buf_Pflege.ANWENDER, anwender );
    strcpy( Buf_Pflege.STATUS, "0" );
    strcpy( Buf_Pflege.FEHLERTEXT, " " );
    Buf_Pflege.FUNKTION = 1;
    sprintf( Buf_Pflege.INFO, "%ld %ld", artikel_nr, besla_nr );

    strcpy( key_select, "pflege_nr=0");

    s = Insert_Protokoll( P_INSERT, V_PROTO_VERTEIL, PflDesc,
                          &Buf_Pflege, &Buf_Pflege,
                          key_select, anwender, "", 0, errmld );

	if ( s == 0 && isCdcAlone == 0 )						/*	01.09.2011 */
		s = InsertPflegePhysically( &Buf_Pflege, errmld );	/*	01.09.2011 */

    return s;
}


static void ClosePflegeTab( void )
{
    if ( PflDesc != NULL )
    {
        SqlFreeTabDesc ( PflDesc );
        PflDesc = NULL;
    }
}

/* ---------------------------------------------------------------------- *
 * Funktion         Protokoll    bliesort                                 *
 * ---------------------------------------------------------------------- */

static char  BliesortTab[] = "bliesort";
static void *BliesortDesc  = NULL;

static long InitBliesortTab( char *errmld )
{
    static int alloc_status = 0;
    static long s;
    static char smeld[80];
    if ( alloc_status == 0 )
    {
        alloc_status = 1;
        s = SqlGetTabDesc( BliesortTab, &BliesortDesc, DESC_DEFAULT, smeld );
    }
    if ( s != 0 )
    {
        BliesortDesc = NULL;
        strcpy( errmld, smeld );
    }
    return s;
}

static long Bliesort_Protokoll( struct BLIESORT *buf_before,
                                struct BLIESORT *buf_after,
                                char *anwender, char *errmld, char mode )
{
    int s;
    char key_select[60];
    char format[60];
    sprintf( format, "BESLA_NR=%c%d.ld and ARTIKEL_NR=%c%d.ld",
                     '%', L_BESLA_NR,
                     '%', L_ARTIKEL_NR );
    sprintf( key_select, format,
             buf_before->BESLA_NR,
             buf_before->ARTIKEL_NR );

    s = Insert_Protokoll( mode, V_PROTO_VERTEIL, BliesortDesc,
                          buf_before, buf_after,
                          key_select, anwender, "", 0, errmld );
    return s;
}

static void CloseBliesortTab( void )
{
    if ( BliesortDesc != NULL )
    {
        SqlFreeTabDesc ( BliesortDesc );
        BliesortDesc = NULL;
    }
}

/* ---------------------------------------------------------------------- *
 * Funktion         Protokoll    artnrbl                                  *
 * ---------------------------------------------------------------------- */

static char  ArtnrblTab[] = "artnrbl";
static void *ArtnrblDesc  = NULL;

static long InitArtnrblTab( char *errmld )
{
    static int alloc_status = 0;
    static long s;
    static char smeld[80];
    if ( alloc_status == 0 )
    {
        alloc_status = 1;
        s = SqlGetTabDesc( ArtnrblTab, &ArtnrblDesc, DESC_DEFAULT, smeld );
    }
    if ( s != 0 )
    {
        ArtnrblDesc = NULL;
        strcpy( errmld, smeld );
    }
    return s;
}

static long Artnrbl_Protokoll( struct ARTNRBL  *buf_before,
                               struct ARTNRBL  *buf_after,
                               char *anwender, char *errmld, char mode )
{
    int s;
    char key_select[60];
    char format[60];
    sprintf( format, "BESLA_NR=%c%d.ld and ARTIKEL_NR=%c%d.ld",
                     '%', L_BESLA_NR,
                     '%', L_ARTIKEL_NR );
    sprintf( key_select, format,
             buf_before->BESLA_NR,
             buf_before->ARTIKEL_NR );

    s = Insert_Protokoll( mode, V_PROTO_VERTEIL, ArtnrblDesc,
                          buf_before, buf_after,
                          key_select, anwender, "", 0, errmld );
    return s;
}

static void CloseArtnrblTab( void )
{
    if ( ArtnrblDesc != NULL )
    {
        SqlFreeTabDesc ( ArtnrblDesc );
        ArtnrblDesc = NULL;
    }
}

#ifdef MIT_NEM

/* ---------------------------------------------------------------------- *
 * Funktion         Protokoll    zartikel                                 *
 * ---------------------------------------------------------------------- */

static char  ZartikelTab[] = "zartikel";
static void *ZartikelDesc  = NULL;

static long InitZartikelTab( char *errmld )
{
    static int alloc_status = 0;
    static long s;
    static char smeld[80];
    if ( alloc_status == 0 )
    {
        alloc_status = 1;
        s = SqlGetTabDesc( ZartikelTab, &ZartikelDesc, DESC_DEFAULT, smeld );
    }
    if ( s != 0 )
    {
        ZartikelDesc = NULL;
        strcpy( errmld, smeld );
    }
    return s;
}

static long Zartikel_Protokoll( struct ZARTIKEL  *buf_before,
                                struct ZARTIKEL  *buf_after,
                                char *anwender, char *errmld, char mode )
{
    int s;
    char key_select[60];
    char format[60];
    sprintf( format, "ARTIKEL_NR=%c%d.ld",
                     '%', L_ARTIKEL_NR );
    sprintf( key_select, format,
             buf_before->ARTIKEL_NR );

    s = Insert_Protokoll( mode, V_PROTO_VERTEIL, ZartikelDesc,
                          buf_before, buf_after,
                          key_select, anwender, "", 0, errmld );
    return s;
}

static void CloseZartikelTab( void )
{
    if ( ZartikelDesc != NULL )
    {
        SqlFreeTabDesc ( ZartikelDesc );
        ZartikelDesc = NULL;
    }
}

#endif

static void CloseProtokol( void )
{
    CloseBliesortTab( );
    CloseArtnrblTab( );
    ClosePflegeTab( );
#ifdef MIT_NEM
    CloseZartikelTab( );
#endif
    Free_Protokoll();
}


/* ---------------------------------------------------------------------- *
 *      Bliesort lesen                                                    *
 * ---------------------------------------------------------------------- */

static int fd_rdbliesort = -2;

static long Declare_Bliesort( char *errmld )
{
    static long s;
    static char smeld[80];
    if ( fd_rdbliesort == -2 )
    {
        s = SqlDeclareCsWh( &fd_rdbliesort,
                            "select artikel_nr from bliesort " \
                            "where besla_nr=? and artikel_nr=?",
                            "bliesort.besla_nr",
                            "bliesort.artikel_nr",
                            NULL );
        if ( s != 0 ) strcpy( smeld, DynErrmld() );
    }
    if ( s != 0 )
    {
        fd_rdbliesort = -1;
        strcpy( errmld, smeld );
    }
    return s;
}

long Lese_Bliesort( long besla_nr, long artikel_nr, char *errmld )
{
    long s;
    s = SqlReadDeclCs( fd_rdbliesort, &artikel_nr,
                                      NULL,
                                      &besla_nr,
                                      &artikel_nr,
                                      NULL );
    if ( s != 0 ) strcpy( errmld, DynErrmld() );
    return s;
}

static void CloseCs_Bliesort(  )
{
    if ( fd_rdbliesort >= 0 )
       SqlCloseCs( fd_rdbliesort );
    fd_rdbliesort = -2;
}

/* ---------------------------------------------------------------------- *
 *      Bliesort einfuegen                                                *
 * ---------------------------------------------------------------------- */

static int fd_ins_bliesort = -2;

static long Prepare_Ins_Bliesort( char *errmld )
{
    static long s;
    static char smeld[80];
    if ( fd_ins_bliesort == -2 )
    {
       s = SqlPrepareStmnt( &fd_ins_bliesort,
                            "insert into bliesort (besla_nr, artikel_nr) values(?,?)",
                            "bliesort.besla_nr",
                            "bliesort.artikel_nr",
                            NULL );
       if ( s != 0 ) strcpy( smeld, DynErrmld() );
    }
    if ( s != 0 )
    {
        fd_ins_bliesort = -1;
        strcpy( errmld, smeld );
    }
    return s;
}

long Insert_Bliesort( long besla_nr, long artikel_nr, char *errmld )
{
    long s;
    struct BLIESORT buf;

    s = SqlExecutePrepare( fd_ins_bliesort, &besla_nr, &artikel_nr, NULL );
    if ( s != 0 )
    {
       strcpy( errmld, DynErrmld() );
       return s;
    }
    if ( SqlRowsProcessed() == 1 )
    {
       buf.BESLA_NR   = besla_nr;
       buf.ARTIKEL_NR = artikel_nr;
       s = Bliesort_Protokoll( &buf, &buf, anwender, errmld, P_INSERT );
    }
    return s;
}


static void Free_Ins_Bliesort(  )
{
    if ( fd_ins_bliesort >= 0 )
        SqlFreePrepare( fd_ins_bliesort );
    fd_ins_bliesort = -2;
}


/* ---------------------------------------------------------------------- *
 *      Bliesort loeschen                                                 *
 * ---------------------------------------------------------------------- */

static int fd_del_bliesort = -2;

static long Prepare_Del_Bliesort( char *errmld )
{
    static long s;
    static char smeld[80];
    if ( fd_del_bliesort == -2 )
    {
       s = SqlPrepareStmnt( &fd_del_bliesort,
                            "delete from bliesort where " \
                            "besla_nr=? and artikel_nr=?",
                            "bliesort.besla_nr",
                            "bliesort.artikel_nr",
                            NULL );
       if ( s != 0 ) strcpy( smeld, DynErrmld() );
    }
    if ( s != 0 )
    {
        fd_del_bliesort = -1;
        strcpy( errmld, smeld );
    }
    return s;
}

long Delete_Bliesort( long besla_nr, long artikel_nr, char *errmld )
{
    long s;
    struct BLIESORT buf;
    buf.BESLA_NR   = besla_nr;
    buf.ARTIKEL_NR = artikel_nr;

    s = SqlExecutePrepare( fd_del_bliesort, &besla_nr, &artikel_nr, NULL );
    if ( s != 0 )
    {
       strcpy( errmld, DynErrmld() );
       return s;
    }
    if ( SqlRowsProcessed() == 1 )
    {
       buf.BESLA_NR   = besla_nr;
       buf.ARTIKEL_NR = artikel_nr;
       s = Bliesort_Protokoll( &buf, &buf, anwender, errmld, P_DELETE );
    }
    return s;
}


static void Free_Del_Bliesort(  )
{
    if ( fd_del_bliesort >= 0 )
        SqlFreePrepare( fd_del_bliesort );
    fd_del_bliesort = -2;
}


/* ---------------------------------------------------------------------- *
 *      Artnrbl  lesen                                                    *
 * ---------------------------------------------------------------------- */

static struct ARTNRBL  Buf_Artnrbl;

static int fd_rdartnrbl = -2;

static long Declare_Artnrbl( char *errmld )
{
    static long s;
    static char smeld[80];
    if ( fd_rdartnrbl == -2 )
    {
        char *sql;
        sql =  "select artikel_nr_bliefer from artnrbl "\
               "where artikel_nr=? and besla_nr=?";

        s = SqlDeclareCsWh( &fd_rdartnrbl, sql,
                            "bliesort.artikel_nr",
                            "bliesort.besla_nr",
                            NULL );
        if ( s != 0 ) strcpy( smeld, DynErrmld() );
    }
    if ( s != 0 )
    {
        fd_rdartnrbl = -1;
        strcpy( errmld, smeld );
    }
    return s;
}

long Lese_Artnrbl( long besla_nr, long artikel_nr, char *artikel_nr_bliefer,
                   char *errmld )
{
    long s;
    s = SqlReadDeclCs( fd_rdartnrbl, artikel_nr_bliefer,
                                     NULL,
                                     &artikel_nr,
                                     &besla_nr,
                                     NULL );
    if ( s != 0 ) strcpy( errmld, DynErrmld() );
    return s;
}

static void CloseCs_Artnrbl(  )
{
    if ( fd_rdartnrbl >= 0 )
       SqlCloseCs( fd_rdartnrbl );
    fd_rdartnrbl = -2;
}

/* ---------------------------------------------------------------------- *
 *      Artnrbl  einfuegen                                                *
 * ---------------------------------------------------------------------- */

static int fd_ins_artnrbl = -2;

static long Prepare_Ins_Artnrbl( char *errmld )
{
    static long s;
    static char smeld[80];
    if ( fd_ins_artnrbl == -2 )
    {
       s = SqlPrepareStmnt( &fd_ins_artnrbl,
                            "insert into artnrbl values(?,?,?)",
                            "artnrbl.artikel_nr",
                            "artnrbl.besla_nr",
                            "artnrbl.artikel_nr_bliefer",
                            NULL );
       if ( s != 0 ) strcpy( smeld, DynErrmld() );
    }
    if ( s != 0 )
    {
        fd_ins_artnrbl = -1;
        strcpy( errmld, smeld );
    }
    return s;
}

long Insert_Artnrbl( long besla_nr, long artikel_nr, char *artikel_nr_bliefer,
                     char *errmld )
{
    long s;
    struct ARTNRBL buf;

    s = SqlExecutePrepare( fd_ins_artnrbl,
                           &artikel_nr ,&besla_nr, artikel_nr_bliefer, NULL );
    if ( s != 0 )
    {
       strcpy( errmld, DynErrmld() );
       return s;
    }
    if ( SqlRowsProcessed() == 1 )
    {
       buf.BESLA_NR   = besla_nr;
       buf.ARTIKEL_NR = artikel_nr;
       strcpy( buf.ARTIKEL_NR_BLIEFER, artikel_nr_bliefer );
       s = Artnrbl_Protokoll( &buf, &buf, anwender, errmld, P_INSERT );
    }
    return s;
}


static void Free_Ins_Artnrbl(  )
{
    if ( fd_ins_artnrbl >= 0 )
        SqlFreePrepare( fd_ins_artnrbl );
    fd_ins_artnrbl = -2;
}

/* ---------------------------------------------------------------------- *
 *      Artnrbl  loeschen                                                 *
 * ---------------------------------------------------------------------- */

static int fd_del_artnrbl = -2;

static long Prepare_Del_Artnrbl( char *errmld )
{
    static long s;
    static char smeld[80];
    if ( fd_del_artnrbl == -2 )
    {
       s = SqlPrepareStmnt( &fd_del_artnrbl,
                            "delete from artnrbl where " \
                            "artikel_nr=? and besla_nr=?",
                            "artnrbl.artikel_nr",
                            "artnrbl.besla_nr",
                            NULL );
       if ( s != 0 ) strcpy( smeld, DynErrmld() );
    }
    if ( s != 0 )
    {
        fd_del_artnrbl = -1;
        strcpy( errmld, smeld );
    }
    return s;
}

long Delete_Artnrbl( long besla_nr, long artikel_nr, char *artikel_nr_bliefer,
                     char *errmld )
{
    long s;
    struct ARTNRBL buf;

    s = SqlExecutePrepare( fd_del_artnrbl, &artikel_nr, &besla_nr, NULL );
    if ( s != 0 )
    {
       strcpy( errmld, DynErrmld() );
       return s;
    }
    if ( SqlRowsProcessed() == 1 )
    {
       buf.BESLA_NR   = besla_nr;
       buf.ARTIKEL_NR = artikel_nr;
       strcpy( buf.ARTIKEL_NR_BLIEFER, artikel_nr_bliefer );
       s = Artnrbl_Protokoll( &buf, &buf, anwender, errmld, P_DELETE );
    }
    return s;
}


static void Free_Del_Artnrbl(  )
{
    if ( fd_del_artnrbl >= 0 )
        SqlFreePrepare( fd_del_artnrbl );
    fd_del_artnrbl = -2;
}


static char SaveArtnrBl[L_ARTNRBL_ARTIKEL_NR_BLIEFER + 1];

void StoreArtnrBl( void )
{
  strcpy( SaveArtnrBl, Buf_Artnrbl.ARTIKEL_NR_BLIEFER );
}

void ReStoreArtnrBl( void )
{
  strcpy( Buf_Artnrbl.ARTIKEL_NR_BLIEFER, SaveArtnrBl );
}

/* ---------------------------------------------------------------------- *
 *      Neuheit loeschen                                                  *
 * ---------------------------------------------------------------------- */

static int fd_del_zaneuheit = -2;

static long Prepare_Zaneuheit( char *errmld )
{
    static long s;
    static char smeld[80];
    if ( fd_del_zaneuheit == -2 )
    {
       s = SqlPrepareStmnt( &fd_del_zaneuheit,
                            "delete from zaneuheit where " \
                            "pflegeprogramm=? and artikel_nr=?",
                            "zaneuheit.pflegeprogramm",
                            "zaneuheit.artikel_nr",
                            NULL );
       if ( s != 0 ) strcpy( smeld, DynErrmld() );
    }
    if ( s != 0 )
    {
        fd_del_zaneuheit = -1;
        strcpy( errmld, smeld );
    }
    return s;
}

long DeleteRecord_Zaneuheit( char programm, long artikel_nr, char *errmld )
{
    long s;
    char prog[2];
    prog[0] = programm;
    prog[1] = '\0';
    s = SqlExecutePrepare( fd_del_zaneuheit, prog, &artikel_nr, NULL );
    if ( s != 0 ) strcpy( errmld, DynErrmld() );
    return s;
}


static void Free_Zaneuheit(  )
{
    if ( fd_del_zaneuheit >= 0 )
        SqlFreePrepare( fd_del_zaneuheit );
    fd_del_zaneuheit = -2;
}


#ifdef MIT_NEM

/* ---------------------------------------------------------------------- *
 *      Neuheit einfuegen                                                 *
 * ---------------------------------------------------------------------- */

#define DOUBLE_INDEX -239

static int fd_ins_zaneuheit = -2;

static long Prepare_Ins_Zaneuheit( char *errmld )
{
    static long s;
    static char smeld[80];
    if ( fd_ins_zaneuheit == -2 )
    {
		s = SqlPrepareStmnt( &fd_ins_zaneuheit,
                             "insert into zaneuheit values (?,?,?,?,?)",
							 "zaneuheit.pflegeprogramm",
							 "zaneuheit.artikel_nr",
							 "zaneuheit.artikel_mc",
							 "zaneuheit.hersteller_nr",
							 "zaneuheit.datum",
                             NULL );
       if ( s != 0 ) strcpy( smeld, DynErrmld() );
    }
    if ( s != 0 )
    {
        fd_ins_zaneuheit = -1;
        strcpy( errmld, smeld );
    }
    return s;
}

static long StoreRecord_Zaneuheit( char programm, 
	 				               long artikel_nr, char *artikel_mc, long nr, long datum,
					               char *errmld )
{
    long s;
    char prog[2];

    prog[0] = programm;
    prog[1] = '\0';

    s = SqlExecutePrepare( fd_ins_zaneuheit,
                           prog, &artikel_nr, artikel_mc, &nr, &datum, NULL );
    if ( s != 0 )
       strcpy( errmld, DynErrmld() );
    return s;
}


static void Free_Ins_Zaneuheit(  )
{
    if ( fd_ins_zaneuheit >= 0 )
        SqlFreePrepare( fd_ins_zaneuheit );
    fd_ins_zaneuheit = -2;
}

/*
long InsertRecord_Zaneuheit( char programm, 
							 long artikel_nr, char *artikel_mc, long nr, long datum,
							 char *errmld )
{
    long s;
    char prog[2];
	char sql[100];
    prog[0] = programm;
    prog[1] = '\0';

    sprintf( sql, "insert into zaneuheit values ('%s',%ld,'%s',%ld,%ld)",
                  prog, artikel_nr, artikel_mc,nr, datum);

    s = SqlExecuteImm( sql );
    if ( s != 0 ) strcpy( errmld, DynErrmld() );
    return s;
}
*/

/* -----  Zapflege  ------------------------- */

static int fd_ins_zapflege = -2;

static long Prepare_Ins_Zapflege( char *errmld )
{
    static long s;
    static char smeld[80];
    if ( fd_ins_zapflege == -2 )
    {
		s = SqlPrepareStmnt( &fd_ins_zapflege,
                             "insert into zapflege values (?,?)",
							 "zapflege.artikel_nr",
							 "zapflege.datum",
                             NULL );
       if ( s != 0 ) strcpy( smeld, DynErrmld() );
    }
    if ( s != 0 )
    {
        fd_ins_zapflege = -1;
        strcpy( errmld, smeld );
    }
    return s;
}

static long StoreRecord_Zapflege( long artikel_nr, long datum, char *errmld )
{
    long s;

    s = SqlExecutePrepare( fd_ins_zapflege, &artikel_nr, &datum, NULL );
    if ( s != 0 )
       strcpy( errmld, DynErrmld() );
    return s;
}


static void Free_Ins_Zapflege(  )
{
    if ( fd_ins_zapflege >= 0 )
        SqlFreePrepare( fd_ins_zapflege );
    fd_ins_zapflege = -2;
}


/* ---------------------------------------------------------------------- *
 *      Zartikel updaten                                                  *
 * ---------------------------------------------------------------------- */


static void ReadLieferNem( long besla_nr, long *lant_nr, char *nem )
{
	char  sql[200];

	sprintf( sql, "select lant_nr,nahrungsergaenzung from liefer where lant_nr=" \
		          "(select lant_nr from bliefer where besla_nr=%ld)",
		          besla_nr );
	if ( SqlRead( sql, lant_nr, nem, NULL ) != 0 )
		strcpy( nem, "N" );
}

long StoreRecord_Zartikel(  long artikel_nr, long besla_nr, char *errmld  )
{
	int  fd;
	int  bNeuheit;
	long lStatus = 0;
	char sql[5000];

	struct ZARTIKEL m_Buf;
	struct ZARTIKEL m_BufOld;

	long datum;
	long lant_nr;

	datum = GetPhoDate();

/*	sprintf( sql, "select * from zartikel where artikel_nr=%ld for update", artikel_nr ); */
	sprintf( sql, "select %s from zartikel where artikel_nr=%ld for update", PROJECTION_ZARTIKEL, artikel_nr );

    lStatus = SqlOpenCs( &fd, sql ); 

	if ( lStatus != 0 )
    {
		strcpy( errmld, DynErrmld() );
		return lStatus;
	}

	lStatus = SqlFetch( fd, 1, &m_Buf, NULL ); 
	if ( lStatus == 100 )
	{
		SqlCloseCs( fd ); 
		return 0;   /* ???????????????????? */
	}

	if ( lStatus != 0 )
	{
		strcpy( errmld, DynErrmld() );
		SqlCloseCs( fd ); 
		return lStatus;  
	}

	if ( *m_Buf.NAHRUNGSTEST == ' ' )
	{
		SqlCloseCs( fd ); 
		return 0;   
	}

    m_BufOld = m_Buf;	

	ReadLieferNem( besla_nr, &lant_nr, m_Buf.NAHRUNGSERGAENZUNG );

	bNeuheit = 0;
	if ( *m_Buf.NAHRUNGSERGAENZUNG == 'N' )
	{
		bNeuheit = 1;
		*m_Buf.NAHRUNGSERGAENZUNG = 'G';
	}

	if ( *m_Buf.NAHRUNGSERGAENZUNG == 'V' || 
		 *m_Buf.NAHRUNGSERGAENZUNG == 'B' ||
		 *m_Buf.NAHRUNGSERGAENZUNG == 'A' )
		*m_Buf.ZENTR_EKSPERRE = '0';
	else if ( *m_Buf.NAHRUNGSERGAENZUNG == 'G' )
		*m_Buf.ZENTR_EKSPERRE = '1';

	/* wenn nix geaendert dann nix machen */
	if (!( *m_Buf.NAHRUNGSERGAENZUNG == *m_BufOld.NAHRUNGSERGAENZUNG &&
		   *m_Buf.ZENTR_EKSPERRE     == *m_BufOld.ZENTR_EKSPERRE         ) )
	{

		strcpy( m_Buf.BEARBEITER, anwender );
		m_Buf.DATUM_AENDER = datum;

		lStatus = SqlUpdateCur( fd, &m_Buf, NULL );

		if ( lStatus == 0 )
			lStatus = Zartikel_Protokoll( &m_BufOld, &m_Buf, anwender, errmld, P_UPDATE );
		else
			strcpy( errmld, DynErrmld() );
	
		if ( lStatus == 0 )
		{
			lStatus = StoreRecord_Zapflege( artikel_nr, datum, errmld );
			if ( lStatus == DOUBLE_INDEX ) lStatus = 0;
		}

	}

	if ( bNeuheit && lStatus == 0 )
	{
		/* Liste fuer Wuest */
		lStatus = StoreRecord_Zaneuheit( NH_NEM_ARTRIKEL, 
			                             artikel_nr, m_Buf.ARTIKEL_MC, 
										 lant_nr, datum, errmld );
		if ( lStatus == DOUBLE_INDEX ) lStatus = 0;
	}

	SqlCloseCs( fd ); 

	return lStatus;
}

#endif


/* ------------------------------------------------------ */

long StartTransaction( char *errmld )
{
   long s;
   s = SqlBeginWork( );
   if ( s != 0 )
     strcpy( errmld, DynErrmld() );
   return s;
}

long CommitTransaction( char *errmld )
{
   long s;
   s = SqlCommitWork( );
   if ( s != 0 )
     strcpy( errmld, DynErrmld() );
   return s;
}

void CancelTransaction( )
{
   SqlRollbackWork( );
}

/* ------------------------------------------------------ */

static long SetLockMode( char *errmld )
{
    long s;
    s = SqlExecuteImm( "SET LOCK MODE TO WAIT 5" );
    if ( s == -554 ) s = 0;     /* wenn Standard-Engine */
    if ( s != 0 )
      {
        strcpy( errmld, DynErrmld( ) );
        strcat( errmld, " :: LOCK MODE" );
       }
    return s;
}

/* ------------------------------------------------------ */

static int i_first = -1;

long OnFirst( char *user, char *errmld  )
{
  long s;
  char wert[300];	/*	01.09.2011 */

  if ( i_first >= 0 ) return 0;

  strcpy( anwender, user );

  s = SetLockMode( errmld );
  if ( s != 0 ) return s;

  if ( UnxGetenv( "CDC_ALONE", wert ) == 0 )	/*	01.09.2011 */ /* central data care alone */
	isCdcAlone = 1;	
  else
    isCdcAlone = 0;	

  i_first = 0;
  return 0;
}


long OpenForUmlisten( char *errmld  )
{
  long s;

#ifdef MIT_NEM
  s = Prepare_Ins_Zaneuheit( errmld );
  if ( s != 0 ) return s;

  s = Prepare_Ins_Zapflege( errmld );
  if ( s != 0 ) return s;

#endif

  s = Declare_Bliesort( errmld );
  if ( s != 0 ) return s;

  s = Declare_Artnrbl( errmld );
  if ( s != 0 ) return s;

  s = Prepare_Ins_Bliesort( errmld );
  if ( s != 0 ) return s;

  s = Prepare_Del_Bliesort( errmld );
  if ( s != 0 ) return s;

  s = Prepare_Ins_Artnrbl( errmld );
  if ( s != 0 ) return s;

/*
  s = Prepare_Del_Artnrbl( errmld );
  if ( s != 0 ) return s;
*/

  s = InitBliesortTab( errmld );
  if ( s != 0 ) return s;

  s = InitArtnrblTab( errmld );
  if ( s != 0 ) return s;

#ifdef MIT_NEM
  s = InitZartikelTab( errmld );
  if ( s != 0 ) return s;
#endif

  s = InitPflegeTab( errmld );
  if ( s != 0 ) return s;

  return 0;
}

long OpenForHerwechsel( char *errmld  )
{
  long s;

#ifdef MIT_NEM
  s = Prepare_Ins_Zaneuheit( errmld );
  if ( s != 0 ) return s;

  s = Prepare_Ins_Zapflege( errmld );
  if ( s != 0 ) return s;

#endif

  s = Prepare_Zaneuheit( errmld );
  if ( s != 0 ) return s;

  s = Declare_Bliesort( errmld );
  if ( s != 0 ) return s;

  s = Declare_Artnrbl( errmld );
  if ( s != 0 ) return s;

  s = Prepare_Ins_Bliesort( errmld );
  if ( s != 0 ) return s;

  s = Prepare_Del_Bliesort( errmld );
  if ( s != 0 ) return s;

  s = Prepare_Ins_Artnrbl( errmld );
  if ( s != 0 ) return s;

  s = Prepare_Del_Artnrbl( errmld );
  if ( s != 0 ) return s;

  s = InitBliesortTab( errmld );
  if ( s != 0 ) return s;

  s = InitArtnrblTab( errmld );
  if ( s != 0 ) return s;

#ifdef MIT_NEM
  s = InitZartikelTab( errmld );
  if ( s != 0 ) return s;
#endif

  s = InitPflegeTab( errmld );
  if ( s != 0 ) return s;

  return 0;
}

void OnLast( void )
{
    CloseCs_Bliesort( );
    CloseCs_Artnrbl( );
    Free_Ins_Bliesort( );
    Free_Del_Bliesort( );
    Free_Ins_Artnrbl( );
    Free_Del_Artnrbl( );
    Free_Zaneuheit( );

#ifdef MIT_NEM
	Free_Ins_Zaneuheit(  );
	Free_Ins_Zapflege(  );
#endif

    CloseProtokol( );

    i_first      = -1;
}
