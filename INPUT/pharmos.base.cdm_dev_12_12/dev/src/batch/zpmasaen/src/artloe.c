/* ---------------------------------------------------------------------- *
 *                         A R T L O E . C                                *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Artikel loeschen                                             *
 * ---------------------------------------------------------------------- *
 * Autor  :  R. Erkens                                                    *
 * Anfang :  09.08.2023                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "logfile.h"
#include "wpp_prot.h"
#include "libscsvoodoo/libscsvoodoo.h"

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartprei.h>
#include <voodoo_table_header/zartwg.h>
#include <voodoo_table_header/artve.h>
#include <voodoo_table_header/ccpvalidityperiod.h>
#include <voodoo_table_header/csafetydatasheet.h>
#include <voodoo_table_header/artnrbl.h>
#include <voodoo_table_header/zartverk.h>
#include <voodoo_table_header/bliesort.h>
#include <voodoo_table_header/ean.h>
#include <voodoo_table_header/zartsekb.h>
#include <voodoo_table_header/zartaustria.h>
#include <voodoo_table_header/zartswitzerland.h>
#include <voodoo_table_header/zartcroatia.h>
#include <voodoo_table_header/zartfrance.h>
#include <voodoo_table_header/zartbulgaria.h>
#include <voodoo_table_header/zartserbia.h>
#include <voodoo_table_header/carticlelang.h>
#include <voodoo_table_header/cartcompack.h>
#include <voodoo_table_header/cdiscount.h>
#include <voodoo_table_header/carticlecodes.h>
#include <voodoo_table_header/zchargenrueckruf.h>
#include <voodoo_table_header/carticleext.h>
#include <voodoo_table_header/cartrefundfrance.h>
#include <voodoo_table_header/cartpriceext.h>
#include <voodoo_table_header/cimexblock.h>
#include <voodoo_table_header/clppr2article.h>
#include <voodoo_table_header/cexportarticle.h>
#include <voodoo_table_header/artaltrn.h>
#include <voodoo_table_header/zartfeb2.h>
#include <voodoo_table_header/zifaoart.h>
#include <voodoo_table_header/zpreiserhoehung.h>
#include <voodoo_table_header/zpreissenkung.h>
#include <voodoo_table_header/artautidem.h>
#include <voodoo_table_header/cartforeigncurr.h>
#include <voodoo_table_header/cartfreetext.h>
#include <voodoo_table_header/cdiscgrpmem.h>
#include <voodoo_table_header/cgibatchentry.h>
#include <voodoo_table_header/cibt.h>
#include <voodoo_table_header/fmdexceptionarticles.h>
#include <voodoo_table_header/zadgoreimp.h>
#include <voodoo_table_header/zautidemsperre.h>
#include <voodoo_table_header/zifaoabschlag.h>
#include <voodoo_table_header/zifaokbs.h>
#include <voodoo_table_header/zlifestyle.h>

/* ----------------- Prototype ------------------------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ---------------------------------------------- */

void ArtLoeUsage( char *buf )
{
   strcat( buf, "- zpmasaen 2 Database User Landeskürzel [PZN]\n" );
   strcat( buf, "  1. ohne PZN: alle Artikel mit Loeschkennzeichen loeschen\n" );
   strcat( buf, "  2. mit  PZN: Artikel mit PZN loeschen wenn mit Loeschkennzeichen\n" );
}

/* ---------------------------------------------------------------------- */

#define SPECIAL_HANDLING_1  1
#define SPECIAL_NEXT_ONE    2

struct LOESCH_RELATION
{
    int   fd;
    char *rel;
    char *pk;
    long  anz;
    int   special;
    void *buf_before;
    char *projection;
};

struct LOESCH_RELATION loeschrel[] =
{
    { -1, "zartikel",             "artikel_nr",         0, 0, NULL, PROJECTION_ZARTIKEL},
    { -1, "zartpreis",            "artikel_nr",         0, 0, NULL, PROJECTION_ZARTPREIS},
    { -1, "zartwg",               "artikel_nr",         0, 0, NULL, PROJECTION_ZARTWG},
    { -1, "artve",                "artikel_nr",         0, 0, NULL, PROJECTION_ARTVE},
    { -1, "ccpvalidityperiod",    "article_no_pack",    0, 0, NULL, PROJECTION_CCPVALIDITYPERIOD},
    { -1, "csafetydatasheet",     "articleno",          0, 0, NULL, PROJECTION_CSAFETYDATASHEET},
    { -1, "artnrbl",              "artikel_nr",         0, 0, NULL, PROJECTION_ARTNRBL},
    { -1, "zartverk",             "artikel_nr_bas",     0, 0, NULL, PROJECTION_ZARTVERK},
    { -1, "zartverk",             "artikel_nr_verk",    0, SPECIAL_HANDLING_1, NULL, PROJECTION_ZARTVERK},
    { -1, "bliesort",             "artikel_nr",         0, 0, NULL, PROJECTION_BLIESORT},
    { -1, "ean",                  "artikel_nr",         0, 0, NULL, PROJECTION_EAN},
    { -1, "zartsekbez",           "artikel_nr",         0, 0, NULL, PROJECTION_ZARTSEKBEZ},
    { -1, "zartaustria",          "artikel_nr",         0, 0, NULL, PROJECTION_ZARTAUSTRIA},
    { -1, "zartswitzerland",      "artikel_nr",         0, 0, NULL, PROJECTION_ZARTSWITZERLAND},
    { -1, "zartcroatia",          "articleno",          0, 0, NULL, PROJECTION_ZARTCROATIA},
    { -1, "zartfrance",           "articleno",          0, 0, NULL, PROJECTION_ZARTFRANCE},
    { -1, "zartbulgaria",         "articleno",          0, 0, NULL, PROJECTION_ZARTBULGARIA},
    { -1, "zartserbia",           "articleno",          0, 0, NULL, PROJECTION_ZARTSERBIA},
    { -1, "carticlelang",         "articleno",          0, 0, NULL, PROJECTION_CARTICLELANG},
    { -1, "cartcompack",          "article_no_pack",    0, 0, NULL, PROJECTION_CARTCOMPACK},
    { -1, "cartcompack",          "article_no_element", 0, 0, NULL, PROJECTION_CARTCOMPACK},
    { -1, "cdiscount",            "articleno",          0, 0, NULL, PROJECTION_CDISCOUNT},
    { -1, "carticlecodes",        "articleno",          0, 0, NULL, PROJECTION_CARTICLECODES},
    { -1, "zchargenrueckruf",     "artikel_nr",         0, 0, NULL, PROJECTION_ZCHARGENRUECKRUF},
    { -1, "carticleext",          "articleno",          0, 0, NULL, PROJECTION_CARTICLEEXT},
    { -1, "cartrefundfrance",     "articleno",          0, 0, NULL, PROJECTION_CARTREFUNDFRANCE},
    { -1, "cartpriceext",         "articleno",          0, 0, NULL, PROJECTION_CARTPRICEEXT},
    { -1, "cimexblock",           "articleno",          0, 0, NULL, PROJECTION_CIMEXBLOCK},
    { -1, "clppr2article",        "articleno",          0, 0, NULL, PROJECTION_CLPPR2ARTICLE},
    { -1, "cexportarticle",       "articleno",          0, 0, NULL, PROJECTION_CEXPORTARTICLE},

    // Thomas Arnold
    { -1, "artikelaltern",        "artikel_nr",         0, 0, NULL, PROJECTION_ARTIKELALTERN},
    { -1, "artikelaltern",        "artikel_nr_altern",  0, 0, NULL, PROJECTION_ARTIKELALTERN},
    { -1, "zartfeb2",             "artikel_nr",         0, 0, NULL, PROJECTION_ZARTFEB2},
    { -1, "zifaoart",             "a00pzn",             0, 0, NULL, PROJECTION_ZIFAOART},
    { -1, "zpreiserhoehung",      "artikel_nr",         0, 0, NULL, PROJECTION_ZPREISERHOEHUNG},
    { -1, "zpreissenkung",        "artikel_nr",         0, 0, NULL, PROJECTION_ZPREISSENKUNG},

    // Klaus Tischhoefer
    { -1, "artautidem",           "pzn",                0, 0, NULL, PROJECTION_ARTAUTIDEM},
    { -1, "cartforeigncurr",      "articleno",          0, 0, NULL, PROJECTION_CARTFOREIGNCURR},
    { -1, "cartfreetext",         "articleno",          0, 0, NULL, PROJECTION_CARTFREETEXT},
    { -1, "cdiscgrpmem",          "articleno",          0, 0, NULL, PROJECTION_CDISCGRPMEM},
    { -1, "cgibatchentry",        "articleno",          0, 0, NULL, PROJECTION_CGIBATCHENTRY},
    { -1, "cibt",                 "articleno",          0, 0, NULL, PROJECTION_CIBT},
    { -1, "fmdexceptionarticles", "articleno",          0, 0, NULL, PROJECTION_FMDEXCEPTIONARTICLES},
    { -1, "zadgoreimp",           "artikel_nr_orig",    0, 0, NULL, PROJECTION_ZADGOREIMP},
    { -1, "zadgoreimp",           "artikel_nr_reimp",   0, 0, NULL, PROJECTION_ZADGOREIMP},
    { -1, "zautidemsperre",       "artikel_nr",         0, 0, NULL, PROJECTION_ZAUTIDEMSPERRE},
    { -1, "zifaoabschlag",        "c02pznabs",          0, 0, NULL, PROJECTION_ZIFAOABSCHLAG},
    { -1, "zifaokbs",             "a00pzn",             0, 0, NULL, PROJECTION_ZIFAOKBS},
    { -1, "zlifestyle",           "artikel_nr",         0, 0, NULL, PROJECTION_ZLIFESTYLE},
};

/* ----------------- Buffer --------------------------------------------- */

struct ZARTIKEL              BufZArtikel;
struct ZARTPREIS             BufZArtPreis;
struct ZARTWG                BufZArtwg;
struct ARTVE                 BufArtve;
struct CCPVALIDITYPERIOD     BufCCPValidityPeriod;
struct CSAFETYDATASHEET      BufCSafetyDataSheet;
struct ARTNRBL               BufArtNrBl;
struct ZARTVERK              BufZartVerk;
struct BLIESORT              BufBlieSort;
struct EAN                   BufEan;
struct ZARTSEKBEZ            BufZartSekBez;
struct ZARTAUSTRIA           BufZartAustria;
struct ZARTSWITZERLAND       BufZartSwitzerland;
struct ZARTCROATIA           BufZartCroatia;
struct ZARTFRANCE            BufZartFrance;
struct ZARTBULGARIA          BufZartBulgaria;
struct ZARTSERBIA            BufZartSerbia;
struct CARTICLELANG          BufCArticleLang;
struct CARTCOMPACK           BufCArtCompack;
struct CDISCOUNT             BufCDiscount;
struct CARTICLECODES         BufCArticleCodes;
struct ZCHARGENRUECKRUF      BufZChargenRueckruf;
struct CARTICLEEXT           BufCArticleExt;
struct CARTREFUNDFRANCE      BufCArtRefundFrance;
struct CARTPRICEEXT          BufcArtPriceExt;
struct CIMEXBLOCK            BufCImexBlock;
struct CLPPR2ARTICLE         BufClppr2Article;
struct CEXPORTARTICLE        BufCExportArticle;
struct ARTIKELALTERN         BufArtikelAltern;
struct ZARTFEB2              BufZArtFeb2;
struct ZIFAOART              BufZIfaoArt;
struct ZPREISERHOEHUNG       BufZPreisErhoehung;
struct ZPREISSENKUNG         BufZPreisSenkung;
struct ARTAUTIDEM            BufArtAutIdem;
struct CARTFOREIGNCURR       BufCArtForeignCurr;
struct CARTFREETEXT          BufCArtFreetext;
struct CDISCGRPMEM           BufCDiscGrpMem;
struct CGIBATCHENTRY         BufCgiBatchEntry;
struct CIBT                  BufCibt;
struct FMDEXCEPTIONARTICLES  BufFmdExceptionArticles;
struct ZADGOREIMP            BufZAdGoreImp;
struct ZAUTIDEMSPERRE        BufZAutiDemSperre;
struct ZIFAOABSCHLAG         BufZIfaoAbschlag;
struct ZIFAOKBS              BufZIfaoKbs;
struct ZLIFESTYLE            BufZLifeStyle;

/* ---------------------------------------------------------------------- */

#define ANZ_TABELLEN ( sizeof( loeschrel ) / sizeof( struct LOESCH_RELATION ) )

#define SQL_TABLENOTFOUND_ERROR   (-206)
#define SQL_DUP_INSERT_ERROR      (-239)

static int fd_zartloe    = -1;

/* ---------------------------------------------------------------------- */

static long Init_Loeschen_Db( char                   *db, 
                              int                     anz, 
                              struct LOESCH_RELATION *loerel, 
                              char                   *errmld )
{
    long s = 0;
    int  i = 0;
    char sql [256+1];
    char desc[128+1];

    while ( i < anz && s == 0 )
    {
        sprintf( desc, "%s:%s.%s", db, loerel[i].rel, loerel[i].pk );
        sprintf(  sql, "delete from %s:%s where %s=?", db, loerel[i].rel, loerel[i].pk );

        s = SqlPrepareStmnt( &loerel[i].fd, sql, desc, NULL );

        if ( s == SQL_TABLENOTFOUND_ERROR )
        {
            s = 0;
            loerel[i].fd = -2;
        }

        if ( s == 0 )
            i++;
    }

    if ( s != 0 )
        sprintf( errmld, "SqlPrepareStmnt %s:%s\n%s", db, loerel[i].rel, DynErrmld() );

    if (s == 0)
    {
        s = SqlPrepareInsert ( &fd_zartloe, "ZARTLOESCH", "ARTIKEL_NR,DATUM_GELOESCHT,DATUM_RESTLOESCH" );

        if ( s != 0 )
        {
            strcpy( errmld, "SqlPrepareInsert ZARTLOESCH\n" );
            strcat( errmld, DynErrmld() );
            return s;
        }
    }

    loerel [0].buf_before = &BufZArtikel;
    loerel [1].buf_before = &BufZArtPreis;
    loerel [2].buf_before = &BufZArtwg;
    loerel [3].buf_before = &BufArtve;
    loerel [4].buf_before = &BufCCPValidityPeriod;
    loerel [5].buf_before = &BufCSafetyDataSheet;
    loerel [6].buf_before = &BufArtNrBl;
    loerel [7].buf_before = &BufZartVerk;
    loerel [8].buf_before = &BufZartVerk;
    loerel [9].buf_before = &BufBlieSort;
    loerel[10].buf_before = &BufEan;
    loerel[11].buf_before = &BufZartSekBez;
    loerel[12].buf_before = &BufZartAustria;
    loerel[13].buf_before = &BufZartSwitzerland;
    loerel[14].buf_before = &BufZartCroatia;
    loerel[15].buf_before = &BufZartFrance;
    loerel[16].buf_before = &BufZartBulgaria;
    loerel[17].buf_before = &BufZartSerbia;
    loerel[18].buf_before = &BufCArticleLang;
    loerel[19].buf_before = &BufCArtCompack;
    loerel[20].buf_before = &BufCArtCompack;
    loerel[21].buf_before = &BufCDiscount;
    loerel[22].buf_before = &BufCArticleCodes;
    loerel[23].buf_before = &BufZChargenRueckruf;
    loerel[24].buf_before = &BufCArticleExt;
    loerel[25].buf_before = &BufCArtRefundFrance;
    loerel[26].buf_before = &BufcArtPriceExt;
    loerel[27].buf_before = &BufCImexBlock;
    loerel[28].buf_before = &BufClppr2Article;
    loerel[29].buf_before = &BufCExportArticle;

    loerel[30].buf_before = &BufArtikelAltern;
    loerel[31].buf_before = &BufArtikelAltern;
    loerel[32].buf_before = &BufZArtFeb2;
    loerel[33].buf_before = &BufZIfaoArt;
    loerel[34].buf_before = &BufZPreisErhoehung;
    loerel[35].buf_before = &BufZPreisSenkung;

    loerel[36].buf_before = &BufArtAutIdem;;
    loerel[37].buf_before = &BufCArtForeignCurr;
    loerel[38].buf_before = &BufCArtFreetext;
    loerel[39].buf_before = &BufCDiscGrpMem;
    loerel[40].buf_before = &BufCgiBatchEntry;
    loerel[41].buf_before = &BufCibt;
    loerel[42].buf_before = &BufFmdExceptionArticles;
    loerel[43].buf_before = &BufZAdGoreImp;
    loerel[44].buf_before = &BufZAdGoreImp;
    loerel[45].buf_before = &BufZAutiDemSperre;
    loerel[46].buf_before = &BufZIfaoAbschlag;
    loerel[47].buf_before = &BufZIfaoKbs;
    loerel[48].buf_before = &BufZLifeStyle;

    return s;
}


static long Init_Loeschen( char *db, 
                           char *user, 
                           char *errmld )
{
    return Init_Loeschen_Db( db, ANZ_TABELLEN, loeschrel, errmld );
}


static long PrepareSpecialHandling( long  artikel_nr,
                                    int   special, 
                                    char *errmld )
{
    long s = 0;

    char sql[512+1];
    char text[64+1];

    switch( special )
    {
        case SPECIAL_HANDLING_1:

            // Für Sonderfallbehandlung werden hier alle 'artikel_nr_bas' benötigt, für die 
            // 'artikel_nr_verk' gelöscht wird. Danach müssen für diese 'artikel_nr_bas' je-
            // weils die 'prioritaet' korrigiert werden.
            sprintf( sql, "select artikel_nr_bas, artikel_nr_verk, prioritaet, idfnr "
                          "  from zartverk "
                          " where artikel_nr_bas in (select distinct(artikel_nr_bas) "
                          "                            from zartverk "
                          "                           where artikel_nr_verk = %ld) "
                          "   and artikel_nr_verk <> %ld "
                          "  into TEMP tmp_zartverk",
                           artikel_nr,
                           artikel_nr );

            s = SqlExecuteImm( sql );

            if ( s != 0 )
            {
                strcpy( errmld, "Create tmp_zartverk\n" );
                strcat( errmld, DynErrmld() );
            }

            break;

        case SPECIAL_NEXT_ONE:

            break;

        default:

            break;
    }

    return s;
}


static long ExecuteSpecialHandling( int   special,
                                    char *errmld )
{
    long s  = 0;
    int  fd =-1;

    char sql[512+1];
    char buf[512+1];
    char text[128+1];

    struct ZARTVERK  BufZartVerkOld;
    struct ZARTVERK  BufZartVerkNew;

    long tmp_artikel_nr_bas  = 0;
    long tmp_artikel_nr_verk = 0;
    long tmp_idfnr           = 0;
    long akt_artikel_nr_bas  = 0;
    int  akt_prioritaet      = 0;

    static void *tab_desc   = NULL;

    strcpy( errmld, "");

    switch( special )
    {
        case SPECIAL_HANDLING_1:

            /* With hold oeffnen */
            s = SqlOpenCsWh( &fd, "select artikel_nr_bas, artikel_nr_verk, idfnr "
                                  "  from tmp_zartverk "
                                  " order by artikel_nr_bas asc, prioritaet asc" );

            if ( s != 0 )
            {
                strcpy( errmld, "SELECT tmp_zartverk\n" );
                strcat( errmld, DynErrmld() );
                return s;
            }

            while ( s == 0 )
            {
                if ( s == 0 )
                    s = SqlFetch( fd, 1, &tmp_artikel_nr_bas, &tmp_artikel_nr_verk, &tmp_idfnr, NULL );

                if ( s != 100 && s != 0)
                {
                    strcpy( errmld, "FETCH tmp_zartverk\n" );
                    strcat( errmld, DynErrmld() );
                    return s;
                }

                if ( s == 0 )
                {
                    if ( tmp_artikel_nr_bas != akt_artikel_nr_bas )
                    {
                        akt_prioritaet = 1;
                        akt_artikel_nr_bas = tmp_artikel_nr_bas;
                    }
                    else
                    {
                        akt_prioritaet++;
                    }

                    sprintf( buf, "select %s from zartverk"
                                  " where artikel_nr_bas=%ld"
                                    " and artikel_nr_verk=%ld"
                                    " and idfnr=%ld",
                                   PROJECTION_ZARTVERK,
                                   tmp_artikel_nr_bas,
                                   tmp_artikel_nr_verk,
                                   tmp_idfnr);

                    s = SqlRead( buf, &BufZartVerkOld, NULL );

                    if ( s != 0)
                    {
                        strcpy( errmld, "SELECT 1 zartverk\n" );
                        strcat( errmld, DynErrmld() );
                        return s;
                    }

                    sprintf(sql, "update zartverk set prioritaet=%d"
                                 " where artikel_nr_bas=%ld"
                                   " and artikel_nr_verk=%ld"
                                   " and idfnr=%ld",
                                  akt_prioritaet,
                                  tmp_artikel_nr_bas,
                                  tmp_artikel_nr_verk,
                                  tmp_idfnr);

                    s = SqlExecuteImm( sql );

                    if ( s != 0)
                    {
                        strcpy( errmld, "UPDATE zartverk\n" );
                        strcat( errmld, DynErrmld() );
                        return s;
                    }

                    s = SqlRead( buf, &BufZartVerkNew, NULL );

                    if ( s != 0)
                    {
                        strcpy( errmld, "SELECT 2 zartverk\n" );
                        strcat( errmld, DynErrmld() );
                        return s;
                    }

                    s = SqlGetTabDesc( "zartverk", &tab_desc, 0, errmld );

                    if ( s != 0 )
                    {
                        return s;
                    }

                    if (memcmp(&BufZartVerkOld, &BufZartVerkNew, sizeof(BufZartVerkNew)) != 0)
                    {
                        char tab_key_select[100+1];

                        sprintf(tab_key_select, "artikel_nr_bas=%ld"
                                                " and artikel_nr_verk=%ld"
                                                " and idfnr=%ld",
                                                 tmp_artikel_nr_bas,
                                                 tmp_artikel_nr_verk,
                                                 tmp_idfnr);

                        s = Insert_Protokoll( P_UPDATE,
                                              V_PROTO_VERTEIL,
                                              tab_desc,
                                             &BufZartVerkOld,
                                             &BufZartVerkNew,
                                              tab_key_select,
                                              "zpmasaen",
                                              "",
                                              0,
                                              errmld );
                    }
                }
            }

            SqlCloseCs( fd );

            s = SqlExecuteImm( "drop table tmp_zartverk" );

            if ( s != 0)
            {
                strcpy( errmld, "DROP TABLE tmp_zartverk\n" );
                strcat( errmld, DynErrmld() );
            }

            break;

        case SPECIAL_NEXT_ONE:

            break;

        default:

            break;
    }

    return s;
}


static long Execute_Loeschen_E( char                   *db,
                                int                     anz,
                                struct LOESCH_RELATION *loerel,
                                long                    artikel_nr,
                                char                   *errmld )
{
    int  i      = 0;
    long s      = 0;
    int  fd     =-1;
    long lCount = 0;

    char sql[4096+1];
    char text1[128+1];
    char text2[128+1];

    void        *buf_before = NULL;
    void        *buf_after  = NULL;
    static void *tab_desc   = NULL;

    char tab_key_select[100+1];

    sprintf(text1,"Loesche Artikel                         : %ld", artikel_nr);
    LogOut( S_HINWEIS, text1 );

    while ( i < anz && s == 0 )
    {
        if ( -2 == loerel[i].fd )
        {
            i++;
            continue;
        }

        sprintf( sql, "select CAST(count(*) as INTEGER) from %s where %s = %ld",
                       loerel[i].rel,
                       loerel[i].pk,
                       artikel_nr );

        s = SqlRead( sql, &lCount, NULL );

        if ( s == 0 )
        {
            if ( lCount > 0 )
            {
                sprintf(text1, "%s (%s)", loerel[i].rel, loerel[i].pk);
                sprintf(text2, "%-40s: %5ld", text1, lCount);
                LogOut( S_HINWEIS, text2 );
                loerel[i].anz += lCount;
            }

            if ( (loerel[i].special > 0) && (lCount > 0) )
            {
                s = PrepareSpecialHandling( artikel_nr, loerel[i].special, errmld );

                if ( s != 0 )
                {
                    return s;
                }
            }

            /* Protokollierung */
            if ( (loerel[i].buf_before != NULL)  && (lCount > 0) )
            {
                buf_before = loerel[i].buf_before;

                s = SqlGetTabDesc( loerel[i].rel, &tab_desc, 0, errmld );

                if ( s != 0 )
                {
                    return s;
                }

                sprintf(tab_key_select, "%s=%ld", loerel[i].pk, artikel_nr);

                sprintf( sql, "select %s from %s where %s = %ld",
                               loerel[i].projection,
                               loerel[i].rel,
                               loerel[i].pk,
                               artikel_nr );

                /* With hold oeffnen */
                s = SqlOpenCsWh( &fd, sql );

                if ( s != 0 )
                {
                    strcpy( errmld, "SELECT\n" );
                    strcat( errmld, DynErrmld() );
                    return s;
                }

                while ( s == 0 )
                {
                    if ( s == 0 )
                        s = SqlFetch( fd, 1, buf_before, NULL );

                    if ( s != 100 && s != 0)
                    {
                        strcpy( errmld, "FETCH\n" );
                        strcat( errmld, DynErrmld() );
                        return s;
                    }

                    if ( s == 0 )
                    {
                        s = Insert_Protokoll( P_DELETE,
                                              V_PROTO_VERTEIL,
                                              tab_desc,
                                              buf_before,
                                              buf_after,
                                              tab_key_select,
                                              "zpmasaen",
                                              "",
                                              0,
                                              errmld );
                        if ( s != 0 )
                        {
                            SqlCloseCs( fd );
                            return s;
                        }
                    }
                }

                SqlCloseCs( fd );
            }

            /* Loeschen aus der Tabelle */
            s = SqlExecutePrepare( loerel[i].fd, &artikel_nr, NULL );

            if ( s == 0 )
            {
                if ( (loerel[i].special > 0) && (lCount > 0) )
                {
                    s = ExecuteSpecialHandling( loerel[i].special, errmld );

                    if ( s != 0 )
                    {
                        return s;
                    }
                }
            }
        }

        if ( s == 0 )
            i++;
    }

    if ( s != 0 )
        sprintf( errmld, "SqlRead %s:%s\n%s", db, loerel[i].rel, DynErrmld() );

    return s;
}


static long Execute_Loeschen( char *db, 
                              char *user, 
                              long  artikel_nr, 
                              char *errmld )
{
    return Execute_Loeschen_E( db, ANZ_TABELLEN, loeschrel, artikel_nr, errmld );
}


static void Free_Loeschen_E( int                     anz, 
                             struct LOESCH_RELATION *loerel )
{
    int i = 0;

    for ( i = 0; i < anz; i++ )
    {
        if ( loerel[i].fd >= 0 )
        {
            SqlFreePrepare( loerel[i].fd );
        }

        loerel[i].fd = -1;
    }

    if ( fd_zartloe != -1 )
    {
        SqlFreePrepare( fd_zartloe );
    }
}


static void Free_Loeschen( )
{
    Free_Loeschen_E( ANZ_TABELLEN, loeschrel );
}


static long LoescheAll( char *db, 
                        char *user, 
                        long  artikel_nr, 
                        char *buf )
{
    long s = 0;

    s = Execute_Loeschen( db, user, artikel_nr, buf );

    if ( s == 0 )
    {
        s = SqlCommitWork();

        if ( s != 0 )
        {
            strcpy( buf, DynErrmld() );
        }
    }
    else
    {
        SqlRollbackWork();
    }

    return s;
}


static long LoescheArtikel_E( char *db, 
                              char *user, 
                              char *buf )
{
    long tagesdatum    = 0;
    long datum_restloe = 0;
    long artikel_nr    = 0;

    int  i   = 0;
    long s   = 0;
    long anz = 0;
    int  fd  =-1;

    char sql[32+1];
    char z_buf[64+1];
    char text[128+1];

    sprintf(text,"SQL-Statement: (%s)", buf);
    LogOut( S_HINWEIS, text );

    tagesdatum = GetPhoDate();

    /* With hold oeffnen */
    s = SqlOpenCsWh( &fd, buf );

    if ( s != 0 )
    {
        strcat( buf, "\n" );
        strcat( buf, DynErrmld() );
        return s;
    }

    s = Init_Loeschen( db, user, buf );

    if ( s != 0 )
    {
        Free_Loeschen( );
        SqlCloseCs( fd );
        return s;
    }

    while ( s == 0 )
    {
        s = SqlBeginWork();

        if ( s != 0 )
            strcpy( buf, DynErrmld() );

        if ( s == 0 )
            s = SqlFetch( fd, 1, &artikel_nr, NULL );

        if ( s == 0 )
        {
            if ( s == 0 )
            {
                s = LoescheAll( db, user, artikel_nr, buf );
            }

            if ( s == 0 )
            {
                s = SqlExecutePrepare( fd_zartloe, &artikel_nr, &tagesdatum, &datum_restloe, NULL );

                if ( s != 0 )
                {
                    strcpy( buf, "ZARTLOESCH\n" );
                    strcat( buf, DynErrmld() );
                }
            }
        }
        else
        {
            if ( s != 100 )
            {
                strcpy( buf, "SqlFetch ZARTIKEL\n" );
                strcat( buf, DynErrmld() );
            }
        }

        if ( s == 0 )
            anz++;
    }

    Free_Loeschen( );

    SqlCloseCs( fd );

    if ( 1 == anz)
    {
        sprintf( z_buf, "\nEs wurde %ld Artikel geloescht", anz );
    }
    else
    {
        sprintf( z_buf, "\nEs wurden %ld Artikel geloescht", anz );
    }

    if ( s == 100 )
    {
        s = 0;

        if ( anz == 0 )
        {
            strcpy( buf, "Keine zu loeschenden Artikel vorhanden" );
        }
        else
        {
            strcpy( buf, "Loeschen erfolgreich" );
        }
    }

    strcat( buf, z_buf );

    if ( s == 0 )
    {
        LogOut( S_HINWEIS, "--------------------------------------------------" );

        while ( i < ANZ_TABELLEN )
        {
            if ( loeschrel[i].anz > 0 )
            {
                char text1[128+1];
                char text2[128+1];
                sprintf(text1, "%s (%s)", loeschrel[i].rel, loeschrel[i].pk);
                sprintf(text2, "%-40s: %5ld", text1, loeschrel[i].anz);
                LogOut( S_HINWEIS, text2 );

                strcat( buf, "\n");
                strcat( buf, text2 );
            }

            i++;
        }
    }

    return s;
}


static long LoescheEinzelArtikel( char *db, 
                                  char *user,
                                  char *lkz,
                                  long  artikel_nr, 
                                  char *buf )
{
    long pruefdatum = 0;
    long s = 0;

    char artikel_geloescht[1+1];
    long datum_ifaloesch = 0;
    long datum_ah = 0;
    long prismaewoche = 0;

    sprintf( buf, "select ARTIKEL_GELOESCHT, DATUM_IFALOESCH, DATUM_AH, PRISMAEWOCHE from ZARTIKEL where ARTIKEL_NR=%ld",
                   artikel_nr );

    s = SqlRead( buf, artikel_geloescht, &datum_ifaloesch, &datum_ah, &prismaewoche, NULL );

    if ( s == 100 )
    {
        strcpy( buf, "Artikel nicht vorhanden" );
        return 0;
    }

    if ( s != 0 )
    {
        strcat( buf, "\n");
        strcat( buf, DynErrmld() );
        return s;
    }

    if ( *artikel_geloescht != '1' )
    {
        strcpy( buf, "Artikel hat kein Loeschkennzeichen" );
        return 0;
    }

    if (( strcmp(lkz, "D") == 0 ) || ( strcmp(lkz, "AT") == 0 ))
    {
        if (( datum_ah == 0 ) && ( prismaewoche != 88 ))
        {
            strcpy( buf, "Artikel hat leeres AH-Datum" );
            return 0;
        }

        if (( datum_ifaloesch == 0 ) && ( prismaewoche != 88 ))
        {
            strcpy( buf, "Artikel hat leeres IFA-Lösch-Datum" );
            return 0;
        }

        pruefdatum = GetPhoDate() - 100001;  // -10 Jahre -1 Tag

        if (( datum_ah > pruefdatum ) && ( prismaewoche != 88 ))
        {
            strcpy( buf, "AH-Datum ist nicht älter als 10 Jahre" );
            return 0;
        }

        if (( datum_ifaloesch > pruefdatum ) && ( prismaewoche != 88 ))
        {
            strcpy( buf, "IFA-Lösch-Datum ist nicht älter als 10 Jahre" );
            return 0;
        }
    }

    sprintf( buf, "select artikel_nr " \
                    "from zartikel " \
                   "where artikel_nr=%ld", artikel_nr );

    return LoescheArtikel_E( db, user, buf );
}


static long LoescheArtikel( char *db, 
                            char *user, 
                            char *lkz,
                            char *buf )
{
    long pruefdatum      = 0;
    long s               = 0;
    long lCount          = 0;
    long artikel_nr      = 0;
    long datum_ifaloesch = 0;
    long datum_ah        = 0;

    char sql[128+1];
    char text[256+1];

    int fd = -1;

    if (( strcmp(lkz, "D") == 0 ) || ( strcmp(lkz, "AT") == 0 ))
    {
        pruefdatum = GetPhoDate() - 100000;

        sprintf( buf, "select artikel_nr " \
                        "from zartikel " \
                       "where (artikel_geloescht = 1 " \
                         "and datum_ah > 0 " \
                         "and datum_ifaloesch > 0 " \
                         "and datum_ah < %ld " \
                         "and datum_ifaloesch < %ld)" \
                         " or (artikel_geloescht = 1" \
                         "and prismaewoche = 88)",
                        pruefdatum,
                        pruefdatum);
    }
    else
    {
        sprintf( buf, "select artikel_nr " \
                        "from zartikel " \
                       "where artikel_geloescht = 1" );
    }

    s = LoescheArtikel_E( db, user, buf );

    if (( strcmp(lkz, "D") == 0 ) || ( strcmp(lkz, "AT") == 0 ))
    {
        sprintf( sql, "select CAST(count(*) as INTEGER) from zartikel where artikel_geloescht = 1");

        s = SqlRead( sql, &lCount, NULL );

        if ( s == 0 )
        {
            if ( lCount > 0 )
            {
                if ( lCount == 1 )
                {
                    sprintf(text, "\n\nEs wurde 1 Artikel mit Löschkennzeichen gefunden, der die sonstigen Bedingungen nicht erfüllt!\n");
                }
                else
                {
                    sprintf(text, "\n\nEs wurden %ld Artikel mit Löschkennzeichen gefunden, die die sonstigen Bedingungen nicht erfüllen!\n", lCount);
                }

                strcat( buf, text);
                LogOut( S_HINWEIS, text );

                if ( lCount < 10 )
                {
                    s = SqlOpenCsWh( &fd, "select artikel_nr, datum_ifaloesch, datum_ah"
                                          "  from zartikel"
                                          " where artikel_geloescht = 1" );

                    if ( s != 0 )
                    {
                        strcat( buf, "SqlOpenCsWh ZARTIKEL\n" );
                        strcat( buf, DynErrmld() );
                        return s;
                    }

                    while ( s == 0 )
                    {
                        if ( s == 0 )
                            s = SqlFetch( fd, 1, &artikel_nr, &datum_ifaloesch, &datum_ah, NULL );

                        if ( s != 100 && s != 0 )
                        {
                            strcat( buf, "FETCH ZARTIKEL\n" );
                            strcat( buf, DynErrmld() );
                            return s;
                        }

                        if ( s == 0 )
                        {
                            sprintf(text, "\nArtikelnr.: %ld; Dat-IFA: %ld; Dat-AH: %ld",
                                           artikel_nr, datum_ifaloesch, datum_ah);
                            strcat( buf, text);
                            LogOut( S_HINWEIS, text );
                        }
                    }
                }

            }
        }
        else
        {
            strcat( buf, "\n");
            strcat( buf, DynErrmld() );
            return s;
        }
    }

    return s;
}


long ArtLoeLoop ( char *db, 
                  char *user, 
                  char *lkz,
                  char *cArtNr, 
                  char *buf )
{
    int  i = 0;
    long s = 0;

    long artikel_nr = 0;

    if ( cArtNr != NULL )
    {
        while ( isdigit(cArtNr[i]) )
        {
            i++;
        }

        if ( cArtNr[i] != '\0' )
        {
            strcpy( buf, "PZN nicht numerisch" );
            return 1;
        }

        artikel_nr = atol( cArtNr );

        if ( artikel_nr <= 0 )
        {
            strcpy( buf, "PZN falsch" );
            return 1;
        }
    }

    s = OpenBase( db, buf );

    if ( s == 0 )
    {
        if ( cArtNr == NULL )
        {
            s = LoescheArtikel( db, user, lkz, buf );
        }
        else
        {
            s = LoescheEinzelArtikel( db, user, lkz, artikel_nr, buf );
        }

        CloseBase();
    }
    else
    {
        strcpy( buf, "Open Database\n" );
        strcat( buf, DynErrmld() );
    }

    return s;
}
