#include <stdio.h>
#include <string.h>
#include "auftrag.h"
#include "nachlief.h"
#include "nachlart.h"
#include "nachlprot.h"
#include "aeorderstat.h"
#include <time.h>
#include <allg.h>
#include <ppgeneric.h>
#include <texte.h>
#include "aasrv.h"
#include "vblief.h"
#include "vbbuch.h"
#include "vbcount.h"
#include "artsel.h"
#include "fcorderssel.h"

int AatartSel_Preferred(struct ARTAESEL* d, char* error_msg);
void WriteLogInfo(const char* err_str, int err_num, int fehler_art);
int Aaauft_GetArtKennz(long artikelnr, char* ArtKZ, char* error_msg);
void updateZeitEndePM(struct AUSTINF* austinf);

#define UNUSED(x) (void)(x)

enum DeviceType
{
    DVC_UNDEFINED,                    /* undefined device type                  */
    DVC_VIDEO,                        /* Generic video device                   */
    DVC_VIDEO_WORKSTATION,            /* Video workstation                      */
    DVC_VIDEO_TERMINAL,               /* Video terminal                         */
    DVC_DCT,                          /* Generic data communication terminal    */
    DVC_DCT_SERIAL,                   /* Data Communication terminal, serial    */
    DVC_DCT_PARALLEL,                 /* Data Communication terminal, parallel  */
    DVC_FILE                          /* Binary file                            */
};

#define AENDTYP_DELETE 1
#define AENDTYP_MENGENAENDERUNG 2
#define AENDTYP_LIEFERMOEGLICHKEIT 3
#define AENDTYP_FOLGE 4

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

int AaauftGetfirstordertime(struct AUSTINF* d, char* error_msg);
long GetTimeForCall( rufArt iFunction, int long lRealTime );

/*  externeGLOBALE C-VARIABLEN  */

extern int FREMDSPRACHE;
extern char cCountry[3];

/*** GLOBALE *****************************************************************/

EXEC SQL BEGIN DECLARE SECTION;
char str[4096];
static long datum;
static long auftragnr;
static long nachliefbestand;
extern short FilialNr;
extern short sUserVz;
extern char ARTIKELZENTRAL_SPRACHE[20];
EXEC SQL END DECLARE SECTION;

static long sdatum;
static long sauftragnr;

/*** DEFINE ******************************************************************/

#define C_PHON    'PH'
#define C_PARA    'DP'
#define C_SERA    'DS'     /* ? */

#define ZEIT_WECHSEL_AM_UND_PM  140000      /* 14:00 Uhr */
#define SCODE            sqlca.sqlcode
#define SISAM            sqlca.sqlerrd[1]
#define SQLERROR(x,y) if ( SCODE < 0 ) { fst = 1;\
                      sprintf( error_msg, "%s: %s %ld/%ld", x, y, SCODE, SISAM );\
                      return -1; }
#define SQLERR(x,y) if (sqlca.sqlcode < 0 ){ \
                    sprintf(error_msg, "%s %s %ld %ld", x, y, SCODE, SISAM ); return -1; }

/*** DECLARATION *************************************************************/

static long CheckTimeToNull( long lTime );
static int  GetTimeDiffInMin( long lTimeHigh, long lTimeLow );

/*** AAAUFT-ANZ-ZUR-KND ******************************************************/

int AaauftAnz_zur_knd(struct AUSTINF* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    long lDatum;
    long batch_von;
    long batch_bis;
    short sOrderlabeltyp;
    EXEC SQL END DECLARE SECTION;

    a = d;

    sOrderlabeltyp = a->SENDESTATUS;

    lDatum = AllgGetDate();
    if (a->BATCHSCHREIBEN != 0) /* nase alle VZs */
    {
        batch_von = 0;
        batch_bis = 99;
    }
    else
    {
        batch_von = 0;
        batch_bis = 0;
    }
    ppGStripLast(a->KDAUFTRAGSTAT);
    ppGStripLast(a->ZUGRUND);
    if (a->ZUGRUND[0] == '\0')
    {
        a->ZUGRUND[0] = '%';
        a->ZUGRUND[1] = '\0';
    }

    strcpy(str, "select count(*) ");
//  strcat(str, "into ? ");
    strcat(str, "from kdauftrag ");
    strcat(str, "inner join cscorderflags ");
    strcat(str, "on cscorderflags.cscorderno = kdauftrag.kdauftragnr and cscorderflags.waitforibtpicking != 1 ");
    strcat(str, "left join auftragartkd ");
    strcat(str, "on auftragartkd.vertriebszentrumnr = kdauftrag.vertriebszentrumnr ");
    strcat(str, "and auftragartkd.kundennr = kdauftrag.kundennr ");
    strcat(str, "and auftragartkd.kdauftragart = kdauftrag.kdauftragart ");
    strcat(str, "where kdauftrag.kdauftragstat like ? and ");
    strcat(str, "kdauftrag.kundennr = ? and ");
    strcat(str, "kdauftrag.batchschreiben >= ? and ");
    strcat(str, "kdauftrag.batchschreiben <= ? and ");
    strcat(str, "(kdauftrag.datumauslieferung <= ? or ");
    strcat(str, "kdauftrag.datumauslieferung = 0 ) and ");
    strcat(str, "kdauftrag.zugrund like ? ");
    if (sOrderlabeltyp == 0)
    {
        strcat(str, "and kdauftrag.orderlabel = '' ");
    }
    else if (sOrderlabeltyp == 1)
    {
        strcat(str, "and (kdauftrag.orderlabel = auftragartkd.orderidentificatio ");
        strcat(str, "or kdauftrag.orderlabel = '') ");
    }
    strcat(str, "and kdauftrag.vertriebszentrumnr = ? ;");

    EXEC SQL PREPARE sel_Anz_zur_knd FROM :str;
//  EXEC SQL EXECUTE sel_Anz_zur_knd using :a->FETCH_REL, :a->KDAUFTRAGSTAT, :a->KUNDENNR, :batch_von, :batch_bis, :lDatum, :a->ZUGRUND, :a->VERTRIEBSZENTRUMNR;
    EXEC SQL EXECUTE sel_Anz_zur_knd into :a->FETCH_REL using :a->KDAUFTRAGSTAT, :a->KUNDENNR, :batch_von, :batch_bis, :lDatum, :a->ZUGRUND, :a->VERTRIEBSZENTRUMNR;

    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftAnz_zur_knd select %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    /* select count(*) liefert bei richtiger abfrage immer sqlca.sqlcode = 0 */
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
        return -2;
    }
    return 0;
}

int AaauftAnz_zur_geraet(struct AUSTINF* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    long lDatum;
    EXEC SQL END DECLARE SECTION;

    a = d;
    lDatum = AllgGetDate();
    ppGStripLast(a->KDAUFTRAGSTAT);
    ppGStripLast(a->ZUGRUND);
    if (a->ZUGRUND[0] == '\0')
    {
        EXEC SQL select count(*) into :a->FETCH_REL from kdauftrag
        inner join cscorderflags
            on cscorderflags.cscorderno = kdauftrag.kdauftragnr and cscorderflags.waitforibtpicking != 1
        where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT and
            kdauftrag.geraetname = :a->GERAETNAME and
            (kdauftrag.datumauslieferung    <=  :lDatum    or
            kdauftrag.datumauslieferung    =    0      )    and
            kdauftrag.kdauftragstat[16] != '1'; /* 1= zurueckgestellt wegen Auftragszusammenfuehrung */
    }
    else
    {
        EXEC SQL select count(*) into :a->FETCH_REL from kdauftrag
        inner join cscorderflags
            on cscorderflags.cscorderno = kdauftrag.kdauftragnr and cscorderflags.waitforibtpicking != 1
        where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT and
            kdauftrag.geraetname = :a->GERAETNAME and
            kdauftrag.zugrund like :a->ZUGRUND and
            (kdauftrag.datumauslieferung    <=  :lDatum    or
            kdauftrag.datumauslieferung    =    0      )    and
            kdauftrag.kdauftragstat[16] != '1'; /* 1= zurueckgestellt wegen Auftragszusammenfuehrung */
    }

    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftAnz_zur_geraet select %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
        return -2;
    }
    return 0;
}

int AaauftSelzurauft(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    long MIN_RECHNR;
    long MAX_RECHNR;
    char MIN_INVOICE[16];
    char MAX_INVOICE[16];
    short Vz_von;
    short Vz_bis;
    long lDatum;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        lDatum = AllgGetDate();
        sdatum = a->DATUM;     /* spaeter extra feld in view */
        datum = a->DATUM;      /* spaeter extra feld in view */
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        ppGStripLast(a->TOURID);
        ppGStripLast(a->KDAUFTRAGART);
        ppGStripLast(a->SORTFIELD);
        ppGStripLast(a->INVOICENUMBER);
        if (a->SORTFIELD[0] == '\0') strcpy(a->SORTFIELD, "kdauftragnr");
        if (a->ANZPOS == 0) /* nase keine Rechnungsnummer mitgegeben */
        {
            MIN_RECHNR = 0;
            MAX_RECHNR = 2147483647;
        }
        else
        {
            MIN_RECHNR = a->ANZPOS;
            MAX_RECHNR = a->ANZPOS;
        }
        if (a->INVOICENUMBER[0] == '\0') /* nase keine Rechnungsnummer mitgegeben */
        {
            strcpy(MIN_INVOICE, " ");
            strcpy(MAX_INVOICE, "999999999999999");
        }
        else
        {
            strcpy(MIN_INVOICE, a->INVOICENUMBER);
            strcpy(MAX_INVOICE, a->INVOICENUMBER);
        }
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        if (a->DATUM == 0)
        {
            strcpy(str, "select ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "KDAUFTRAG.IDFNR, ");
            strcat(str, "KDAUFTRAG.GERAETNAME, ");
            strcat(str, "KDAUFTRAG.TOURID, ");
            strcat(str, "KDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "KDAUFTRAG.KOART, ");
            strcat(str, "KDAUFTRAG.BUCHART, ");
            strcat(str, "KDAUFTRAG.ANZPOS, ");
            strcat(str, "KDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "KDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "KDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "KDAUFTRAG.ANZPOSOB, ");
            strcat(str, "KDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "KDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "KDAUFTRAG.SENDESTATUS, ");
            strcat(str, "KDAUFTRAG.ZUGRUND, ");
            strcat(str, "KDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "KDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "KDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "KDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "KDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "KDAUFTRAG.ORDERLABEL, ");
            strcat(str, "KDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "CSCORDERFLAGS.WAITFORIBTPICKING, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "from kdauftrag, kunde, cscorderflags ");
            strcat(str, "where kdauftrag.kdauftragstat like ? and ");
            strcat(str, "kdauftrag.geraetname like ? and ");
            strcat(str, "kdauftrag.tourid like ? and ");
            strcat(str, "kdauftrag.kdauftragart like ? and ");
            strcat(str, "kdauftrag.kdauftragnr >= ? and ");
            strcat(str, "kdauftrag.vertriebszentrumnr >= ? and ");
            strcat(str, "kdauftrag.vertriebszentrumnr <= ? and ");
            if (!strncmp(cCountry, "BG", 2))
            {
                strcat(str, "kdauftrag.invoicenumber >= ? and ");
                strcat(str, "kdauftrag.invoicenumber <= ? and ");
            }
            else
            {
                strcat(str, "kdauftrag.rechnungnr >= ? and ");
                strcat(str, "kdauftrag.rechnungnr <= ? and ");
            }
            strcat(str, "(kdauftrag.datumauslieferung <= ? or ");
            strcat(str, "kdauftrag.datumauslieferung = 0 ) and ");
            strcat(str, "kunde.kundennr = kdauftrag.kundennr and ");
            strcat(str, "cscorderflags.cscorderno = kdauftrag.kdauftragnr and ");
            if (a->WAITFORIBTPICKING == 1)
            {
                strcat(str, "cscorderflags.waitforibtpicking != 1 and ");   /* keine Auftraege mit dem Kennzeichen - Abfrage kommt aus F9 */
            }
            strcat(str, "kunde.vertriebszentrumnr = kdauftrag.vertriebszentrumnr and ");
            strcat(str, "kdauftrag.vertriebszentrumnr in ( ");
            strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
            strcat(str, "where  RegionArten.RegionNr= ? and  ");
            strcat(str, "RegionArten.RegionenTyp=1) ");
            strcat(str, "and kdauftrag.zugrund like ? ");
            strcat(str, "order by ");
            strcat(str, a->SORTFIELD);
            EXEC SQL prepare dec_Selzurauft from :str;
            EXEC SQL declare Selzurauft scroll cursor with hold for dec_Selzurauft;

            if (!strncmp(cCountry, "BG", 2))
            {
                EXEC SQL open Selzurauft using
                     :a->KDAUFTRAGSTAT,
                     :a->GERAETNAME,
                     :a->TOURID,
                     :a->KDAUFTRAGART,
                     :a->KDAUFTRAGNR,
                     :Vz_von,
                     :Vz_bis,
                     :MIN_INVOICE,
                     :MAX_INVOICE,
                     :lDatum,
                     :a->REGIONNR,
                     :a->ZUGRUND;
            }
            else
            {
                EXEC SQL open Selzurauft using
                     :a->KDAUFTRAGSTAT,
                     :a->GERAETNAME,
                     :a->TOURID,
                     :a->KDAUFTRAGART,
                     :a->KDAUFTRAGNR,
                     :Vz_von,
                     :Vz_bis,
                     :MIN_RECHNR,
                     :MAX_RECHNR,
                     :lDatum,
                     :a->REGIONNR,
                     :a->ZUGRUND;
            }
        }
        else
        {
            strcpy(str, "select ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "AKDAUFTRAG.IDFNR, ");
            strcat(str, "AKDAUFTRAG.GERAETNAME, ");
            strcat(str, "AKDAUFTRAG.TOURID, ");
            strcat(str, "AKDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "AKDAUFTRAG.KOART, ");
            strcat(str, "AKDAUFTRAG.BUCHART, ");
            strcat(str, "AKDAUFTRAG.ANZPOS, ");
            strcat(str, "AKDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "AKDAUFTRAG.ANZPOSOB, ");
            strcat(str, "AKDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "AKDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "AKDAUFTRAG.SENDESTATUS, ");
            strcat(str, "AKDAUFTRAG.ZUGRUND, ");
            strcat(str, "AKDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "AKDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "AKDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "AKDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "AKDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "AKDAUFTRAG.ORDERLABEL, ");
            strcat(str, "AKDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "ACSCORDERFLAGS.WAITFORIBTPICKING, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "from akdauftrag, kunde, acscorderflags ");
            strcat(str, "where akdauftrag.kdauftragstat like ? and ");
            strcat(str, "akdauftrag.datum = ? and ");
            strcat(str, "akdauftrag.geraetname like ? and ");
            strcat(str, "akdauftrag.tourid like ? and ");
            strcat(str, "akdauftrag.kdauftragart like ? and ");
            strcat(str, "akdauftrag.kdauftragnr >= ? and ");
            strcat(str, "akdauftrag.vertriebszentrumnr >= ? and ");
            strcat(str, "akdauftrag.vertriebszentrumnr <= ? and ");
            if (!strncmp(cCountry, "BG", 2))
            {
                strcat(str, "akdauftrag.invoicenumber >= ? and ");
                strcat(str, "akdauftrag.invoicenumber <= ? and ");
            }
            else
            {
                strcat(str, "akdauftrag.rechnungnr >= ? and ");
                strcat(str, "akdauftrag.rechnungnr <= ? and ");
            }
            strcat(str, "kunde.kundennr = akdauftrag.kundennr and ");
            strcat(str, "kunde.vertriebszentrumnr = akdauftrag.vertriebszentrumnr and ");
            strcat(str, "acscorderflags.cscorderno = akdauftrag.kdauftragnr and ");
            strcat(str, "acscorderflags.datum = akdauftrag.datum and ");
            strcat(str, "akdauftrag.vertriebszentrumnr in ( ");
            strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
            strcat(str, "where  RegionArten.RegionNr= ? and  ");
            strcat(str, "RegionArten.RegionenTyp=1) ");
            strcat(str, "order by ");
            strcat(str, a->SORTFIELD);
            EXEC SQL prepare dec_Selzurauft2 from :str;
            EXEC SQL declare Selzurauft2 scroll cursor with hold for dec_Selzurauft2;

            if (!strncmp(cCountry, "BG", 2))
            {
                EXEC SQL open Selzurauft2 using
                     :a->KDAUFTRAGSTAT,
                     :a->DATUM,
                     :a->GERAETNAME,
                     :a->TOURID,
                     :a->KDAUFTRAGART,
                     :a->KDAUFTRAGNR,
                     :Vz_von,
                     :Vz_bis,
                     :MIN_INVOICE,
                     :MAX_INVOICE,
                     :a->REGIONNR;
            }
            else
            {
                EXEC SQL open Selzurauft2 using
                     :a->KDAUFTRAGSTAT,
                     :a->DATUM,
                     :a->GERAETNAME,
                     :a->TOURID,
                     :a->KDAUFTRAGART,
                     :a->KDAUFTRAGNR,
                     :Vz_von,
                     :Vz_bis,
                     :MIN_RECHNR,
                     :MAX_RECHNR,
                     :a->REGIONNR;
            }
        }
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauft: open Selzurauft %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        if (sdatum == 0) EXEC SQL close Selzurauft;
        else EXEC SQL close Selzurauft2;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelzurauft: close Selzurauft %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    if (sdatum == 0) EXEC SQL fetch relative :a->FETCH_REL Selzurauft
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->WAITFORIBTPICKING,
            :a->NAMEINHABER;
    else EXEC SQL fetch relative :a->FETCH_REL Selzurauft2
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->WAITFORIBTPICKING,
            :a->NAMEINHABER;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelzurauft: fetch Selzurauft %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Selzurauft;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    if (AaauftGetfirstordertime(d, error_msg) < 0) return -1;
    return 0;
}

int AaauftSelzurauft_o_tour(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short Vz_von;
    short Vz_bis;
    long lDatum;
    short sOrderlabeltyp;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        lDatum = AllgGetDate();
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        sOrderlabeltyp = a->SENDESTATUS;
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        EXEC SQL declare Selzurauft_o_tour scroll cursor with hold for
            select
                KDAUFTRAG.KDAUFTRAGNR,
                KDAUFTRAG.KDAUFTRAGSTAT,
                KDAUFTRAG.IDFNR,
                KDAUFTRAG.GERAETNAME,
                KDAUFTRAG.TOURID,
                KDAUFTRAG.ETAUFTRAGSCHALTER2,
                KDAUFTRAG.KDAUFTRAGART,
                KDAUFTRAG.KOART,
                KDAUFTRAG.BUCHART,
                KDAUFTRAG.ANZPOS,
                KDAUFTRAG.ANZPOSDAFUE,
                KDAUFTRAG.ZEITENDEAM,
                KDAUFTRAG.ZEITENDEPM,
                KUNDE.NAMEAPO,
                KUNDE.KZKDKLASSE,
                KDAUFTRAG.ANZPOSOB,
                KDAUFTRAG.ANZALPHATEXT,
                KUNDE.ORT,
                KDAUFTRAG.VERTRIEBSZENTRUMNR,
                KDAUFTRAG.KDAUFTRAGNRFILIALE,
                KDAUFTRAG.SENDESTATUS,
                KDAUFTRAG.ZUGRUND,
                KDAUFTRAG.DATUMAUSLIEFERUNG,
                KDAUFTRAG.RECHNUNGNR,
                KDAUFTRAG.INVOICENUMBER,
                KDAUFTRAG.PAYMENTDATE,
                KDAUFTRAG.PAYMENTTYPE,
                KDAUFTRAG.ORDERLABEL,
                KDAUFTRAG.ORDERPERIODID,
                KUNDE.NAMEINHABER
            from kdauftrag, kunde, cscorderflags
            where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT and
                    kdauftrag.geraetname            like :a->GERAETNAME and
                    kdauftrag.vertriebszentrumnr    >=   :Vz_von   and
                    kdauftrag.vertriebszentrumnr    <=   :Vz_bis   and
                    (kdauftrag.datumauslieferung    <=  :lDatum    or
                    kdauftrag.datumauslieferung     =   0      )    and
                    kunde.kundennr                  =   kdauftrag.kundennr and
                    kunde.vertriebszentrumnr        =   kdauftrag.vertriebszentrumnr and
                    cscorderflags.cscorderno        =   kdauftrag.kdauftragnr and
                    cscorderflags.waitforibtpicking !=  1 and
                    kdauftrag.vertriebszentrumnr in (
                        select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr= :a->REGIONNR and
                               RegionArten.RegionenTyp=1)
                               and kdauftrag.zugrund like :a->ZUGRUND
            order by tourid;

        EXEC SQL open Selzurauft_o_tour;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauft_o_tour: open Selzurauft_o_tour %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Selzurauft_o_tour;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelzurauft_o_tour: close Selzurauft_o_tour %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Selzurauft_o_tour
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->NAMEINHABER;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelzurauft_o_tour: fetch Selzurauft_o_tour %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Selzurauft_o_tour;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    return 0;
}

int AaauftSelzurauft_o_aart(struct AUSTINF* d, char* error_msg)
{
    static int fst = 0;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short Vz_von;
    short Vz_bis;
    long lDatum;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst == 0) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 1;
        lDatum = AllgGetDate();
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        EXEC SQL declare Selzurauft_o_aart1 scroll cursor with hold for
            select
                KDAUFTRAG.KDAUFTRAGNR,
                KDAUFTRAG.KDAUFTRAGSTAT,
                KDAUFTRAG.IDFNR,
                KDAUFTRAG.GERAETNAME,
                KDAUFTRAG.TOURID,
                KDAUFTRAG.ETAUFTRAGSCHALTER2,
                KDAUFTRAG.KDAUFTRAGART,
                KDAUFTRAG.KOART,
                KDAUFTRAG.BUCHART,
                KDAUFTRAG.ANZPOS,
                KDAUFTRAG.ANZPOSDAFUE,
                KDAUFTRAG.ZEITENDEAM,
                KDAUFTRAG.ZEITENDEPM,
                KUNDE.NAMEAPO,
                KUNDE.KZKDKLASSE,
                KDAUFTRAG.ANZPOSOB,
                KDAUFTRAG.ANZALPHATEXT,
                KUNDE.ORT,
                KDAUFTRAG.VERTRIEBSZENTRUMNR,
                KDAUFTRAG.KDAUFTRAGNRFILIALE,
                KDAUFTRAG.SENDESTATUS,
                KDAUFTRAG.ZUGRUND,
                KDAUFTRAG.DATUMAUSLIEFERUNG,
                KDAUFTRAG.RECHNUNGNR,
                KDAUFTRAG.INVOICENUMBER,
                KDAUFTRAG.PAYMENTDATE,
                KDAUFTRAG.PAYMENTTYPE,
                KDAUFTRAG.ORDERLABEL,
                KDAUFTRAG.ORDERPERIODID,
                KUNDE.NAMEINHABER
            from kdauftrag, kunde, cscorderflags
            where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT and
            kdauftrag.kdauftragart          =    :a->KDAUFTRAGART and
            kdauftrag.geraetname            like :a->GERAETNAME and
            kdauftrag.vertriebszentrumnr    >=   :Vz_von   and
            kdauftrag.vertriebszentrumnr    <=   :Vz_bis   and
            (kdauftrag.datumauslieferung    <=  :lDatum    or
            kdauftrag.datumauslieferung    =    0      )    and
            kunde.kundennr                  =    kdauftrag.kundennr and
            kunde.vertriebszentrumnr        =    kdauftrag.vertriebszentrumnr and
            cscorderflags.cscorderno = kdauftrag.kdauftragnr and
            cscorderflags.waitforibtpicking != 1 and
            kdauftrag.vertriebszentrumnr in (
                select RegionArten.RegionTeilNr from RegionArten
                where  RegionArten.RegionNr= :a->REGIONNR and
                       RegionArten.RegionenTyp=1)
            and kdauftrag.zugrund like :a->ZUGRUND
            order by kdauftragart, koart, buchart;

        EXEC SQL declare Selzurauft_o_aart2 scroll cursor with hold for
            select
                KDAUFTRAG.KDAUFTRAGNR,
                KDAUFTRAG.KDAUFTRAGSTAT,
                KDAUFTRAG.IDFNR,
                KDAUFTRAG.GERAETNAME,
                KDAUFTRAG.TOURID,
                KDAUFTRAG.ETAUFTRAGSCHALTER2,
                KDAUFTRAG.KDAUFTRAGART,
                KDAUFTRAG.KOART,
                KDAUFTRAG.BUCHART,
                KDAUFTRAG.ANZPOS,
                KDAUFTRAG.ANZPOSDAFUE,
                KDAUFTRAG.ZEITENDEAM,
                KDAUFTRAG.ZEITENDEPM,
                KUNDE.NAMEAPO,
                KUNDE.KZKDKLASSE,
                KDAUFTRAG.ANZPOSOB,
                KDAUFTRAG.ANZALPHATEXT,
                KUNDE.ORT,
                KDAUFTRAG.VERTRIEBSZENTRUMNR,
                KDAUFTRAG.KDAUFTRAGNRFILIALE,
                KDAUFTRAG.SENDESTATUS,
                KDAUFTRAG.ZUGRUND,
                KDAUFTRAG.DATUMAUSLIEFERUNG,
                KDAUFTRAG.RECHNUNGNR,
                KDAUFTRAG.INVOICENUMBER,
                KDAUFTRAG.PAYMENTDATE,
                KDAUFTRAG.PAYMENTTYPE,
                KDAUFTRAG.ORDERLABEL,
                KDAUFTRAG.ORDERPERIODID,
                KUNDE.NAMEINHABER
            from kdauftrag, kunde, cscorderflags
            where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT and
                    kdauftrag.kdauftragart          !=   :a->KDAUFTRAGART and
                    kdauftrag.geraetname            like :a->GERAETNAME and
                    kdauftrag.vertriebszentrumnr    >=   :Vz_von   and
                    kdauftrag.vertriebszentrumnr    <=   :Vz_bis   and
                    (kdauftrag.datumauslieferung    <=  :lDatum    or
                    kdauftrag.datumauslieferung    =    0      )    and
                    kunde.kundennr                  =    kdauftrag.kundennr and
                    kunde.vertriebszentrumnr        =    kdauftrag.vertriebszentrumnr and
                    cscorderflags.cscorderno = kdauftrag.kdauftragnr and
                    cscorderflags.waitforibtpicking != 1 and
                    kdauftrag.vertriebszentrumnr in (
                        select RegionArten.RegionTeilNr from RegionArten
                        where RegionArten.RegionNr= :a->REGIONNR and
                              RegionArten.RegionenTyp=1)
            and kdauftrag.zugrund like :a->ZUGRUND
            order by kdauftragart, koart, buchart;

        EXEC SQL open Selzurauft_o_aart1;
        if (sqlca.sqlcode < 0 )
        {
            fst = 0;
            sprintf(error_msg, " AaauftSelzurauft_o_aart: open Selzurauft_o_aart1 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        if (fst == 0)    return 0;
        if (fst == 1)
        {
            fst = 0;
            EXEC SQL close Selzurauft_o_aart1;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSelzurauft_o_aart: close Selzurauft_o_aart1 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
        if (fst == 2)
        {
            fst = 0;
            EXEC SQL close Selzurauft_o_aart2;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSelzurauft_o_aart: close Selzurauft_o_aart2 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
    }

    if (fst == 1)
    {
        EXEC SQL fetch relative :a->FETCH_REL Selzurauft_o_aart1
            into
                :a->KDAUFTRAGNR,
                :a->KDAUFTRAGSTAT,
                :a->IDFNR,
                :a->GERAETNAME,
                :a->TOURID,
                :a->ETAUFTRAGSCHALTER2,
                :a->KDAUFTRAGART,
                :a->KOART,
                :a->BUCHART,
                :a->ANZPOS,
                :a->ANZPOSDAFUE,
                :a->ZEITENDEAM,
                :a->ZEITENDEPM,
                :a->NAMEAPO,
                :a->KZKDKLASSE,
                :a->ANZPOSOB,
                :a->ANZALPHATEXT,
                :a->ORT,
                :a->VERTRIEBSZENTRUMNR,
                :a->KDAUFTRAGNRFILIALE,
                :a->SENDESTATUS,
                :a->ZUGRUND,
                :a->DATUMAUSLIEFERUNG,
                :a->RECHNUNGNR,
                :a->INVOICENUMBER,
                :a->PAYMENTDATE,
                :a->PAYMENTTYPE,
                :a->ORDERLABEL,
                :a->ORDERPERIODID,
                :a->NAMEINHABER;
        if (sqlca.sqlcode < 0 )
        {
            fst = 0;
            sprintf(error_msg, " AaauftSelzurauft_o_aart: fetch Selzurauft_o_aart2 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);

            EXEC SQL close Selzurauft_o_aart1;
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            EXEC SQL close Selzurauft_o_aart1;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSelzurauft_o_aart: close Selzurauft_o_aart1 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL open Selzurauft_o_aart2;
            if (sqlca.sqlcode < 0 )
            {
                fst = 0;
                sprintf(error_msg, " AaauftSelzurauft_o_aart: open Selzurauft_o_aart2 %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            fst = 2;
        }
    }

    if (fst == 2)
    {
        EXEC SQL fetch relative :a->FETCH_REL Selzurauft_o_aart2
            into
                :a->KDAUFTRAGNR,
                :a->KDAUFTRAGSTAT,
                :a->IDFNR,
                :a->GERAETNAME,
                :a->TOURID,
                :a->ETAUFTRAGSCHALTER2,
                :a->KDAUFTRAGART,
                :a->KOART,
                :a->BUCHART,
                :a->ANZPOS,
                :a->ANZPOSDAFUE,
                :a->ZEITENDEAM,
                :a->ZEITENDEPM,
                :a->NAMEAPO,
                :a->KZKDKLASSE,
                :a->ANZPOSOB,
                :a->ANZALPHATEXT,
                :a->ORT,
                :a->VERTRIEBSZENTRUMNR,
                :a->KDAUFTRAGNRFILIALE,
                :a->SENDESTATUS,
                :a->ZUGRUND,
                :a->DATUMAUSLIEFERUNG,
                :a->RECHNUNGNR,
                :a->INVOICENUMBER,
                :a->PAYMENTDATE,
                :a->PAYMENTTYPE,
                :a->ORDERLABEL,
                :a->ORDERPERIODID,
                :a->NAMEINHABER;
        if (sqlca.sqlcode < 0 )
        {
            fst = 0;
            sprintf(error_msg, " AaauftSelzurauft_o_aart: fetch Selzurauft_o_aart2 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);

            EXEC SQL close Selzurauft_o_aart2;
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            return 1;
        }
    }

    updateZeitEndePM(d);
    return 0;
}

int AaauftSelzurauft_o_branch(struct AUSTINF* d, char* error_msg)
{
    static int fst = 0;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short Vz_von;
    short Vz_bis;
    long lDatum;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst == 0) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 1;
        lDatum = AllgGetDate();
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        EXEC SQL declare Selzurauft_o_branch1 scroll cursor with hold for
            select
                KDAUFTRAG.KDAUFTRAGNR,
                KDAUFTRAG.KDAUFTRAGSTAT,
                KDAUFTRAG.IDFNR,
                KDAUFTRAG.GERAETNAME,
                KDAUFTRAG.TOURID,
                KDAUFTRAG.ETAUFTRAGSCHALTER2,
                KDAUFTRAG.KDAUFTRAGART,
                KDAUFTRAG.KOART,
                KDAUFTRAG.BUCHART,
                KDAUFTRAG.ANZPOS,
                KDAUFTRAG.ANZPOSDAFUE,
                KDAUFTRAG.ZEITENDEAM,
                KDAUFTRAG.ZEITENDEPM,
                KUNDE.NAMEAPO,
                KUNDE.KZKDKLASSE,
                KDAUFTRAG.ANZPOSOB,
                KDAUFTRAG.ANZALPHATEXT,
                KUNDE.ORT,
                KDAUFTRAG.VERTRIEBSZENTRUMNR,
                KDAUFTRAG.KDAUFTRAGNRFILIALE,
                KDAUFTRAG.SENDESTATUS,
                KDAUFTRAG.ZUGRUND,
                KDAUFTRAG.DATUMAUSLIEFERUNG,
                KDAUFTRAG.RECHNUNGNR,
                KDAUFTRAG.INVOICENUMBER,
                KDAUFTRAG.PAYMENTDATE,
                KDAUFTRAG.PAYMENTTYPE,
                KDAUFTRAG.ORDERLABEL,
                KDAUFTRAG.ORDERPERIODID,
                KUNDE.NAMEINHABER
            from kdauftrag, kunde
            where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT and
                    kdauftrag.kdauftragart          =    :a->KDAUFTRAGART and
                    kdauftrag.geraetname            like :a->GERAETNAME and
                    kdauftrag.vertriebszentrumnr    >=   :Vz_von   and
                    kdauftrag.vertriebszentrumnr    <=   :Vz_bis   and
                    (kdauftrag.datumauslieferung    <=  :lDatum    or
                    kdauftrag.datumauslieferung    =    0      )    and
                    kunde.kundennr                  =    kdauftrag.kundennr and
                    kunde.vertriebszentrumnr        =    kdauftrag.vertriebszentrumnr and
                    cscorderflags.cscorderno = kdauftrag.kdauftragnr and
                    cscorderflags.waitforibtpicking != 1 and
                    kdauftrag.vertriebszentrumnr in (
                        select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr= :a->REGIONNR and
                               RegionArten.RegionenTyp=1)
            and kdauftrag.zugrund like :a->ZUGRUND
            order by VERTRIEBSZENTRUMNR;

        EXEC SQL declare Selzurauft_o_branch2 scroll cursor with hold for
            select
                KDAUFTRAG.KDAUFTRAGNR,
                KDAUFTRAG.KDAUFTRAGSTAT,
                KDAUFTRAG.IDFNR,
                KDAUFTRAG.GERAETNAME,
                KDAUFTRAG.TOURID,
                KDAUFTRAG.ETAUFTRAGSCHALTER2,
                KDAUFTRAG.KDAUFTRAGART,
                KDAUFTRAG.KOART,
                KDAUFTRAG.BUCHART,
                KDAUFTRAG.ANZPOS,
                KDAUFTRAG.ANZPOSDAFUE,
                KDAUFTRAG.ZEITENDEAM,
                KDAUFTRAG.ZEITENDEPM,
                KUNDE.NAMEAPO,
                KUNDE.KZKDKLASSE,
                KDAUFTRAG.ANZPOSOB,
                KDAUFTRAG.ANZALPHATEXT,
                KUNDE.ORT,
                KDAUFTRAG.VERTRIEBSZENTRUMNR,
                KDAUFTRAG.KDAUFTRAGNRFILIALE,
                KDAUFTRAG.SENDESTATUS,
                KDAUFTRAG.ZUGRUND,
                KDAUFTRAG.DATUMAUSLIEFERUNG,
                KDAUFTRAG.RECHNUNGNR,
                KDAUFTRAG.INVOICENUMBER,
                KDAUFTRAG.PAYMENTDATE,
                KDAUFTRAG.PAYMENTTYPE,
                KDAUFTRAG.ORDERLABEL,
                KDAUFTRAG.ORDERPERIODID,
                KUNDE.NAMEINHABER
            from kdauftrag, kunde, cscorderflags
            where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT and
                    kdauftrag.kdauftragart          !=   :a->KDAUFTRAGART and
                    kdauftrag.geraetname            like :a->GERAETNAME and
                    kdauftrag.vertriebszentrumnr    >=   :Vz_von   and
                    kdauftrag.vertriebszentrumnr    <=   :Vz_bis   and
                    (kdauftrag.datumauslieferung    <=  :lDatum    or
                    kdauftrag.datumauslieferung    =    0      )    and
                    kunde.kundennr                  =    kdauftrag.kundennr and
                    kunde.vertriebszentrumnr        =    kdauftrag.vertriebszentrumnr and
                    cscorderflags.cscorderno = kdauftrag.kdauftragnr and
                    cscorderflags.waitforibtpicking != 1 and
                    kdauftrag.vertriebszentrumnr in (
                        select RegionArten.RegionTeilNr from RegionArten
                        where RegionArten.RegionNr= :a->REGIONNR and
                              RegionArten.RegionenTyp=1)
            and kdauftrag.zugrund like :a->ZUGRUND
            order by VERTRIEBSZENTRUMNR;

        EXEC SQL open Selzurauft_o_branch1;
        if (sqlca.sqlcode < 0 )
        {
            fst = 0;
            sprintf(error_msg, " AaauftSelzurauft_o_branch: open Selzurauft_o_branch1 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        if (fst == 0)    return 0;
        if (fst == 1)
        {
            fst = 0;
            EXEC SQL close Selzurauft_o_branch1;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSelzurauft_o_branch: close Selzurauft_o_branch1 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
        if (fst == 2)
        {
            fst = 0;
            EXEC SQL close Selzurauft_o_branch2;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSelzurauft_o_branch: close Selzurauft_o_branch2 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
    }

    if (fst == 1)
    {
        EXEC SQL fetch relative :a->FETCH_REL Selzurauft_o_branch1
            into
                :a->KDAUFTRAGNR,
                :a->KDAUFTRAGSTAT,
                :a->IDFNR,
                :a->GERAETNAME,
                :a->TOURID,
                :a->ETAUFTRAGSCHALTER2,
                :a->KDAUFTRAGART,
                :a->KOART,
                :a->BUCHART,
                :a->ANZPOS,
                :a->ANZPOSDAFUE,
                :a->ZEITENDEAM,
                :a->ZEITENDEPM,
                :a->NAMEAPO,
                :a->KZKDKLASSE,
                :a->ANZPOSOB,
                :a->ANZALPHATEXT,
                :a->ORT,
                :a->VERTRIEBSZENTRUMNR,
                :a->KDAUFTRAGNRFILIALE,
                :a->SENDESTATUS,
                :a->ZUGRUND,
                :a->DATUMAUSLIEFERUNG,
                :a->RECHNUNGNR,
                :a->INVOICENUMBER,
                :a->PAYMENTDATE,
                :a->PAYMENTTYPE,
                :a->ORDERLABEL,
                :a->ORDERPERIODID,
                :a->NAMEINHABER;
        if (sqlca.sqlcode < 0 )
        {
            fst = 0;
            sprintf(error_msg, " AaauftSelzurauft_o_branch: fetch Selzurauft_o_branch2 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);

            EXEC SQL close Selzurauft_o_branch1;
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            EXEC SQL close Selzurauft_o_branch1;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSelzurauft_o_branch: close Selzurauft_o_branch1 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL open Selzurauft_o_branch2;
            if (sqlca.sqlcode < 0 )
            {
                fst = 0;
                sprintf(error_msg, " AaauftSelzurauft_o_branch: open Selzurauft_o_branch2 %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            fst = 2;
        }
    }

    if (fst == 2)
    {
        EXEC SQL fetch relative :a->FETCH_REL Selzurauft_o_branch2
            into
                :a->KDAUFTRAGNR,
                :a->KDAUFTRAGSTAT,
                :a->IDFNR,
                :a->GERAETNAME,
                :a->TOURID,
                :a->ETAUFTRAGSCHALTER2,
                :a->KDAUFTRAGART,
                :a->KOART,
                :a->BUCHART,
                :a->ANZPOS,
                :a->ANZPOSDAFUE,
                :a->ZEITENDEAM,
                :a->ZEITENDEPM,
                :a->NAMEAPO,
                :a->KZKDKLASSE,
                :a->ANZPOSOB,
                :a->ANZALPHATEXT,
                :a->ORT,
                :a->VERTRIEBSZENTRUMNR,
                :a->KDAUFTRAGNRFILIALE,
                :a->SENDESTATUS,
                :a->ZUGRUND,
                :a->DATUMAUSLIEFERUNG,
                :a->RECHNUNGNR,
                :a->INVOICENUMBER,
                :a->PAYMENTDATE,
                :a->PAYMENTTYPE,
                :a->ORDERLABEL,
                :a->ORDERPERIODID,
                :a->NAMEINHABER;
        if (sqlca.sqlcode < 0 )
        {
            fst = 0;
            sprintf(error_msg, " AaauftSelzurauft_o_branch: fetch Selzurauft_o_branch2 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);

            EXEC SQL close Selzurauft_o_branch2;
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            return 1;
        }
    }

    updateZeitEndePM(d);
    return 0;
}

int AaauftSelzurauft_o_idf(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short Vz_von;
    short Vz_bis;
    long lDatum;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        lDatum = AllgGetDate();
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        EXEC SQL declare Selzurauft_o_idf scroll cursor with hold for
        select
            KDAUFTRAG.KDAUFTRAGNR,
            KDAUFTRAG.KDAUFTRAGSTAT,
            KDAUFTRAG.IDFNR,
            KDAUFTRAG.GERAETNAME,
            KDAUFTRAG.TOURID,
            KDAUFTRAG.ETAUFTRAGSCHALTER2,
            KDAUFTRAG.KDAUFTRAGART,
            KDAUFTRAG.KOART,
            KDAUFTRAG.BUCHART,
            KDAUFTRAG.ANZPOS,
            KDAUFTRAG.ANZPOSDAFUE,
            KDAUFTRAG.ZEITENDEAM,
            KDAUFTRAG.ZEITENDEPM,
            KUNDE.NAMEAPO,
            KUNDE.KZKDKLASSE,
            KDAUFTRAG.ANZPOSOB,
            KDAUFTRAG.ANZALPHATEXT,
            KUNDE.ORT,
            KDAUFTRAG.VERTRIEBSZENTRUMNR,
            KDAUFTRAG.KDAUFTRAGNRFILIALE,
            KDAUFTRAG.SENDESTATUS,
            KDAUFTRAG.ZUGRUND,
            KDAUFTRAG.DATUMAUSLIEFERUNG,
            KDAUFTRAG.RECHNUNGNR,
            KDAUFTRAG.INVOICENUMBER,
            KDAUFTRAG.PAYMENTDATE,
            KDAUFTRAG.PAYMENTTYPE,
            KDAUFTRAG.ORDERLABEL,
            KDAUFTRAG.ORDERPERIODID,
            KUNDE.NAMEINHABER
            from kdauftrag, kunde, cscorderflags
            where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT and
                    kdauftrag.geraetname                like :a->GERAETNAME and
                    kdauftrag.vertriebszentrumnr    >=   :Vz_von   and
                    kdauftrag.vertriebszentrumnr    <=   :Vz_bis   and
                    (kdauftrag.datumauslieferung    <=  :lDatum    or
                    kdauftrag.datumauslieferung     =   0      )    and
                    kunde.kundennr                  =    kdauftrag.kundennr and
                    kunde.vertriebszentrumnr        =    kdauftrag.vertriebszentrumnr and
                    cscorderflags.cscorderno = kdauftrag.kdauftragnr and
                    cscorderflags.waitforibtpicking != 1 and
                    kdauftrag.vertriebszentrumnr in (
                        select RegionArten.RegionTeilNr from RegionArten
                        where RegionArten.RegionNr= :a->REGIONNR and
                              RegionArten.RegionenTyp=1)
            and kdauftrag.zugrund like :a->ZUGRUND
            order by idfnr;

        EXEC SQL open Selzurauft_o_idf;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauft_o_idf: open Selzurauft_o_idf %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Selzurauft_o_idf;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelzurauft_o_idf: close Selzurauft_o_idf %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Selzurauft_o_idf
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->NAMEINHABER;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelzurauft_o_idf: fetch Selzurauft_o_idf %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Selzurauft_o_idf;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    return 0;
}

static int Sel_o_endeAM(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short Vz_von;
    short Vz_bis;
    long lDatum;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        lDatum = AllgGetDate();
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        EXEC SQL declare Selzurauft_o_ende scroll cursor with hold for
            select
                KDAUFTRAG.KDAUFTRAGNR,
                KDAUFTRAG.KDAUFTRAGSTAT,
                KDAUFTRAG.IDFNR,
                KDAUFTRAG.GERAETNAME,
                KDAUFTRAG.TOURID,
                KDAUFTRAG.ETAUFTRAGSCHALTER2,
                KDAUFTRAG.KDAUFTRAGART,
                KDAUFTRAG.KOART,
                KDAUFTRAG.BUCHART,
                KDAUFTRAG.ANZPOS,
                KDAUFTRAG.ANZPOSDAFUE,
                KDAUFTRAG.ZEITENDEAM,
                KDAUFTRAG.ZEITENDEPM,
                KUNDE.NAMEAPO,
                KUNDE.KZKDKLASSE,
                KDAUFTRAG.ANZPOSOB,
                KDAUFTRAG.ANZALPHATEXT,
                KUNDE.ORT,
                KDAUFTRAG.VERTRIEBSZENTRUMNR,
                KDAUFTRAG.KDAUFTRAGNRFILIALE,
                KDAUFTRAG.SENDESTATUS,
                KDAUFTRAG.ZUGRUND,
                KDAUFTRAG.DATUMAUSLIEFERUNG,
                KDAUFTRAG.RECHNUNGNR,
                KDAUFTRAG.INVOICENUMBER,
                KDAUFTRAG.PAYMENTDATE,
                KDAUFTRAG.PAYMENTTYPE,
                KDAUFTRAG.ORDERLABEL,
                KDAUFTRAG.ORDERPERIODID,
                KUNDE.NAMEINHABER
                from kdauftrag, kunde, cscorderflags
                where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT  and
                        kdauftrag.geraetname    like :a->GERAETNAME     and
                        kdauftrag.vertriebszentrumnr    >=   :Vz_von   and
                        kdauftrag.vertriebszentrumnr    <=   :Vz_bis   and
                        (kdauftrag.datumauslieferung    <=  :lDatum    or
                                kdauftrag.datumauslieferung    =    0      )    and
                        kunde.kundennr                  =    kdauftrag.kundennr and
                        kunde.vertriebszentrumnr        =    kdauftrag.vertriebszentrumnr and
                        cscorderflags.cscorderno = kdauftrag.kdauftragnr and
                        cscorderflags.waitforibtpicking != 1 and
                        kdauftrag.vertriebszentrumnr in (
                            select RegionArten.RegionTeilNr from RegionArten
                            where RegionArten.RegionNr= :a->REGIONNR and
                                  RegionArten.RegionenTyp=1)
                and kdauftrag.zugrund like :a->ZUGRUND
                order by zeitendeam;

        EXEC SQL open Selzurauft_o_ende;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauft_o_ende: open Selzurauft_o_ende %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Selzurauft_o_ende;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelzurauft_o_ende: close Selzurauft_o_ende %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Selzurauft_o_ende
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->NAMEINHABER;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelzurauft_o_ende: fetch Selzurauft_o_ende %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Selzurauft_o_ende;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    return 0;
}

static int Sel_o_endePM(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short Vz_von;
    short Vz_bis;
    long lDatum;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        lDatum = AllgGetDate();
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        EXEC SQL declare Sel_o_endePM scroll cursor with hold for
        select
            KDAUFTRAG.KDAUFTRAGNR,
            KDAUFTRAG.KDAUFTRAGSTAT,
            KDAUFTRAG.IDFNR,
            KDAUFTRAG.GERAETNAME,
            KDAUFTRAG.TOURID,
            KDAUFTRAG.ETAUFTRAGSCHALTER2,
            KDAUFTRAG.KDAUFTRAGART,
            KDAUFTRAG.KOART,
            KDAUFTRAG.BUCHART,
            KDAUFTRAG.ANZPOS,
            KDAUFTRAG.ANZPOSDAFUE,
            KDAUFTRAG.ZEITENDEAM,
            KDAUFTRAG.ZEITENDEPM,
            KUNDE.NAMEAPO,
            KUNDE.KZKDKLASSE,
            KDAUFTRAG.ANZPOSOB,
            KDAUFTRAG.ANZALPHATEXT,
            KUNDE.ORT,
            KDAUFTRAG.VERTRIEBSZENTRUMNR,
            KDAUFTRAG.KDAUFTRAGNRFILIALE,
            KDAUFTRAG.SENDESTATUS,
            KDAUFTRAG.ZUGRUND,
            KDAUFTRAG.DATUMAUSLIEFERUNG,
            KDAUFTRAG.RECHNUNGNR,
            KDAUFTRAG.INVOICENUMBER,
            KDAUFTRAG.PAYMENTDATE,
            KDAUFTRAG.PAYMENTTYPE,
            KDAUFTRAG.ORDERLABEL,
            KDAUFTRAG.ORDERPERIODID,
            KUNDE.NAMEINHABER
        from kdauftrag, kunde
        where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT  and
                kdauftrag.geraetname    like :a->GERAETNAME     and
                kdauftrag.vertriebszentrumnr    >=   :Vz_von   and
                kdauftrag.vertriebszentrumnr    <=   :Vz_bis   and
                (kdauftrag.datumauslieferung    <=  :lDatum    or
                        kdauftrag.datumauslieferung    =    0      )    and
                kunde.kundennr                  =    kdauftrag.kundennr and
                kunde.vertriebszentrumnr        =    kdauftrag.vertriebszentrumnr and
                kdauftrag.vertriebszentrumnr in (
                    select RegionArten.RegionTeilNr from RegionArten
                    where RegionArten.RegionNr= :a->REGIONNR and
                          RegionArten.RegionenTyp=1)
        and kdauftrag.zugrund like :a->ZUGRUND
        order by zeitendepm;

        EXEC SQL open Sel_o_endePM;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_o_endePM: open Sel_o_endePM %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Sel_o_endePM;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_o_endePM: close Sel_o_endePM %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_o_endePM
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->NAMEINHABER;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSel_o_endePM: fetch Sel_o_endePM %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Sel_o_endePM;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    return 0;
}

int AaauftSelzurauft_o_ende(struct AUSTINF* d, char* error_msg)
{
    int rc;
    static int Funktion = 0;
    if (Funktion == 0)
    {
        if (AllgGetTime() < ZEIT_WECHSEL_AM_UND_PM) Funktion = 1;
        else                                        Funktion = 2;
    }
    if (Funktion == 1)
    {
        if (d->FETCH_REL == 0) Funktion = 0;
        rc = Sel_o_endeAM(d, error_msg);
    }
    else
    {
        if (d->FETCH_REL == 0) Funktion = 0;
        rc = Sel_o_endePM(d, error_msg);
    }
    return rc;
}

int AaauftSelzurauftknde(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    long MIN_RECHNR;
    long MAX_RECHNR;
    char MIN_INVOICE[16];
    char MAX_INVOICE[16];
    short Vz_von;
    short Vz_bis;
    long lDatum;
    long batch_von;
    long batch_bis;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        lDatum = AllgGetDate();
        sdatum = a->DATUM;
        datum = a->DATUM;
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        ppGStripLast(a->TOURID);
        ppGStripLast(a->KDAUFTRAGART);
        ppGStripLast(a->SORTFIELD);
        ppGStripLast(a->INVOICENUMBER);
        if (a->SORTFIELD[0] == '\0') strcpy(a->SORTFIELD, "kdauftragnr");
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        if (a->BATCHSCHREIBEN != 0) /* nase alle VZs */
        {
            batch_von = 0;
            batch_bis = 99;
        }
        else
        {
            batch_von = 0;
            batch_bis = 0;
        }
        if (a->ANZPOS == 0) /* nase keine Rechnungsnummer mitgegeben */
        {
            MIN_RECHNR = 0;
            MAX_RECHNR = 2147483647;
        }
        else
        {
            MIN_RECHNR = a->ANZPOS;
            MAX_RECHNR = a->ANZPOS;
        }
        if (a->INVOICENUMBER[0] == '\0') /* nase keine Rechnungsnummer mitgegeben */
        {
            strcpy(MIN_INVOICE, " ");
            strcpy(MAX_INVOICE, "999999999999999");
        }
        else
        {
            strcpy(MIN_INVOICE, a->INVOICENUMBER);
            strcpy(MAX_INVOICE, a->INVOICENUMBER);
        }
        if (a->DATUM == 0)
        {
            strcpy(str, "select ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "KDAUFTRAG.IDFNR, ");
            strcat(str, "KDAUFTRAG.GERAETNAME, ");
            strcat(str, "KDAUFTRAG.TOURID, ");
            strcat(str, "KDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "KDAUFTRAG.KOART, ");
            strcat(str, "KDAUFTRAG.BUCHART, ");
            strcat(str, "KDAUFTRAG.ANZPOS, ");
            strcat(str, "KDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "KDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "KDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "KDAUFTRAG.ANZPOSOB, ");
            strcat(str, "KDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "KDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "KDAUFTRAG.SENDESTATUS, ");
            strcat(str, "KDAUFTRAG.ZUGRUND, ");
            strcat(str, "KDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "KDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "KDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "KDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "KDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "KDAUFTRAG.ORDERLABEL, ");
            strcat(str, "KDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "CSCORDERFLAGS.WAITFORIBTPICKING, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "from kdauftrag, kunde, cscorderflags ");
            strcat(str, "where kdauftrag.kdauftragstat like ? and ");
            strcat(str, "kdauftrag.vertriebszentrumnr >= ? and ");
            strcat(str, "kdauftrag.vertriebszentrumnr <= ? and ");
            strcat(str, "kdauftrag.kundennr = ? and ");
            strcat(str, "kdauftrag.geraetname like ? and ");
            strcat(str, "kdauftrag.tourid like ? and ");
            strcat(str, "kdauftrag.kdauftragart like ? and ");
            strcat(str, "kdauftrag.kdauftragnr >= ? and ");
            if (!strncmp(cCountry, "BG", 2))
            {
                strcat(str, "kdauftrag.invoicenumber >= ? and ");
                strcat(str, "kdauftrag.invoicenumber <= ? and ");
            }
            else
            {
                strcat(str, "kdauftrag.rechnungnr >= ? and ");
                strcat(str, "kdauftrag.rechnungnr <= ? and ");
            }
            strcat(str, "(kdauftrag.datumauslieferung <= ? or ");
            strcat(str, "kdauftrag.datumauslieferung = 0 ) and ");
            strcat(str, "kunde.kundennr = kdauftrag.kundennr and ");
            strcat(str, "kunde.vertriebszentrumnr = kdauftrag.vertriebszentrumnr and ");
            strcat(str, "kdauftrag.batchschreiben >= ? and ");
            strcat(str, "kdauftrag.batchschreiben <= ? and ");
            strcat(str, "cscorderflags.cscorderno = kdauftrag.kdauftragnr and ");
            strcat(str, "kdauftrag.vertriebszentrumnr in ( ");
            strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
            strcat(str, "where RegionArten.RegionNr= ? and ");
            strcat(str, "RegionArten.RegionenTyp=1) ");
            strcat(str, "and kdauftrag.zugrund like ? ");
            strcat(str, "order by ");
            strcat(str, a->SORTFIELD);
            EXEC SQL prepare dec_Selzurauftknde from :str;
            EXEC SQL declare Selzurauftknde scroll cursor with hold for dec_Selzurauftknde;

            if (!strncmp(cCountry, "BG", 2))
            {
                EXEC SQL open Selzurauftknde using
                     :a->KDAUFTRAGSTAT,
                     :Vz_von,
                     :Vz_bis,
                     :a->KUNDENNR,
                     :a->GERAETNAME,
                     :a->TOURID,
                     :a->KDAUFTRAGART,
                     :a->KDAUFTRAGNR,
                     :MIN_INVOICE,
                     :MAX_INVOICE,
                     :lDatum,
                     :batch_von,
                     :batch_bis,
                     :a->REGIONNR,
                     :a->ZUGRUND;
            }
            else
            {
                EXEC SQL open Selzurauftknde using
                     :a->KDAUFTRAGSTAT,
                     :Vz_von,
                     :Vz_bis,
                     :a->KUNDENNR,
                     :a->GERAETNAME,
                     :a->TOURID,
                     :a->KDAUFTRAGART,
                     :a->KDAUFTRAGNR,
                     :MIN_RECHNR,
                     :MAX_RECHNR,
                     :lDatum,
                     :batch_von,
                     :batch_bis,
                     :a->REGIONNR,
                     :a->ZUGRUND;
            }
        }
        else
        {
            strcpy(str, "select ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "AKDAUFTRAG.IDFNR, ");
            strcat(str, "AKDAUFTRAG.GERAETNAME, ");
            strcat(str, "AKDAUFTRAG.TOURID, ");
            strcat(str, "AKDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "AKDAUFTRAG.KOART, ");
            strcat(str, "AKDAUFTRAG.BUCHART, ");
            strcat(str, "AKDAUFTRAG.ANZPOS, ");
            strcat(str, "AKDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "AKDAUFTRAG.ANZPOSOB, ");
            strcat(str, "AKDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "AKDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "AKDAUFTRAG.SENDESTATUS, ");
            strcat(str, "AKDAUFTRAG.ZUGRUND, ");
            strcat(str, "AKDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "AKDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "AKDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "AKDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "AKDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "AKDAUFTRAG.ORDERLABEL, ");
            strcat(str, "AKDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "ACSCORDERFLAGS.WAITFORIBTPICKING, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "from akdauftrag, kunde, acscorderflags ");
            strcat(str, "where akdauftrag.kdauftragstat like ? and ");
            strcat(str, "akdauftrag.datum = ? and ");
            strcat(str, "akdauftrag.vertriebszentrumnr >= ? and ");
            strcat(str, "akdauftrag.vertriebszentrumnr <= ? and ");
            strcat(str, "akdauftrag.kundennr = ? and ");
            strcat(str, "akdauftrag.geraetname like ? and ");
            strcat(str, "akdauftrag.tourid like ? and ");
            strcat(str, "akdauftrag.kdauftragart like ? and ");
            strcat(str, "akdauftrag.kdauftragnr >= ? and ");
            if (!strncmp(cCountry, "BG", 2))
            {
                strcat(str, "akdauftrag.invoicenumber >= ? and ");
                strcat(str, "akdauftrag.invoicenumber <= ? and ");
            }
            else
            {
                strcat(str, "akdauftrag.rechnungnr >= ? and ");
                strcat(str, "akdauftrag.rechnungnr <= ? and ");
            }
            strcat(str, "kunde.kundennr = akdauftrag.kundennr and ");
            strcat(str, "kunde.vertriebszentrumnr = akdauftrag.vertriebszentrumnr and ");
            strcat(str, "acscorderflags.cscorderno = akdauftrag.kdauftragnr and ");
            strcat(str, "acscorderflags.datum = akdauftrag.datum and ");
            strcat(str, "akdauftrag.vertriebszentrumnr in ( ");
            strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
            strcat(str, "where RegionArten.RegionNr = ? and ");
            strcat(str, "RegionArten.RegionenTyp=1) ");
            strcat(str, "order by ");
            strcat(str, a->SORTFIELD);
            EXEC SQL prepare dec_Selzurauftknd2 from :str;
            EXEC SQL declare Selzurauftknd2 scroll cursor with hold for dec_Selzurauftknd2;

            if (!strncmp(cCountry, "BG", 2))
            {
                EXEC SQL open Selzurauftknd2 using
                    :a->KDAUFTRAGSTAT,
                    :a->DATUM,
                    :Vz_von,
                    :Vz_bis,
                    :a->KUNDENNR,
                    :a->GERAETNAME,
                    :a->TOURID,
                    :a->KDAUFTRAGART,
                    :a->KDAUFTRAGNR,
                    :MIN_INVOICE,
                    :MAX_INVOICE,
                    :a->REGIONNR;
            }
            else
            {
                EXEC SQL open Selzurauftknd2 using
                    :a->KDAUFTRAGSTAT,
                    :a->DATUM,
                    :Vz_von,
                    :Vz_bis,
                    :a->KUNDENNR,
                    :a->GERAETNAME,
                    :a->TOURID,
                    :a->KDAUFTRAGART,
                    :a->KDAUFTRAGNR,
                    :MIN_RECHNR,
                    :MAX_RECHNR,
                    :a->REGIONNR;
            }
        }
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauftknde: open Selzurauftknde %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        if (sdatum == 0) EXEC SQL close Selzurauftknde;
        else EXEC SQL close Selzurauftknd2;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelzurauftknde: close Selzurauftknde %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    if (sdatum == 0) EXEC SQL fetch relative :a->FETCH_REL Selzurauftknde
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->WAITFORIBTPICKING,
            :a->NAMEINHABER;

    else EXEC SQL fetch relative :a->FETCH_REL Selzurauftknd2
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->WAITFORIBTPICKING,
            :a->NAMEINHABER;

    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelzurauftknde: fetch Selzurauftknde %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Selzurauftknde;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    if (AaauftGetfirstordertime(d, error_msg) < 0) return -1;
    return 0;
}

int AaauftAusg_auft_ereig(struct AUFEREIG* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUFEREIG* a;
    static long datum;
    short ind;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        if (a->DATUM == AllgGetDate() || a->DATUM == 0) datum = 0;
        else datum = a->DATUM;
        if (datum == 0)
        {
            EXEC SQL declare Ausg_auft_ereig scroll cursor with hold for
            select AUFEREIG_LISTE
            from kdauftragereignis, kdauftrag, outer passwd
            where
            kdauftragereignis.kdauftragnr = :a->KDAUFTRAGNR and
            kdauftrag.kdauftragnr = kdauftragereignis.kdauftragnr and
            passwd.filialnr = kdauftragereignis.filialnr and
            passwd.uid = kdauftragereignis.personalnr
            order by kdauftragereignis.datum, kdauftragereignis.zeit;

            EXEC SQL open Ausg_auft_ereig;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftAusg_auft_ereig: open Ausg_auft_ereig %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        else
        {
            EXEC SQL declare Ausg_auft_ereig2 scroll cursor with hold for
                select
                    AKDAUFTRAGEREIGNIS.KDAUFTRAGNR,
                    AKDAUFTRAGEREIGNIS.DATUM,
                    AKDAUFTRAGEREIGNIS.ZEIT,
                    AKDAUFTRAGEREIGNIS.EREIGNISART,
                    AKDAUFTRAGEREIGNIS.GERAETNAME,
                    PASSWD.USERNAME,
                    AKDAUFTRAGEREIGNIS.PERSONALNR,
                    AKDAUFTRAGEREIGNIS.EVENTCODE
                from akdauftragereignis, akdauftrag, outer passwd
                where
                    akdauftragereignis.kdauftragnr = :a->KDAUFTRAGNR and
                    akdauftragereignis.datum_rechnung = :datum and
                    akdauftrag.kdauftragnr = akdauftragereignis.kdauftragnr and
                    akdauftrag.datum = akdauftragereignis.datum_rechnung and
                    passwd.filialnr = akdauftragereignis.filialnr and
                    passwd.uid = akdauftragereignis.personalnr
                order by akdauftragereignis.datum, akdauftragereignis.zeit;

            EXEC SQL open Ausg_auft_ereig2;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftAusg_auft_ereig: open Ausg_auft_ereig2 %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        if (datum == 0)
        {
            EXEC SQL close Ausg_auft_ereig;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftAusg_auft_ereig: close Ausg_auft_ereig %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        else
        {
            EXEC SQL close Ausg_auft_ereig2;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftAusg_auft_ereig2: close Ausg_auft_ereig %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        return 1;
    }

    if (datum == 0) EXEC SQL fetch relative :a->FETCH_REL Ausg_auft_ereig into :a->KDAUFTRAGNR, :a->DATUM, :a->ZEIT, :a->EREIGNISART, :a->GERAETNAME, :a->USERNAME, :a->PERSONALNR indicator :ind, :a->EVENTCODE;
    else EXEC SQL fetch relative :a->FETCH_REL Ausg_auft_ereig2 into :a->KDAUFTRAGNR, :a->DATUM, :a->ZEIT, :a->EREIGNISART, :a->GERAETNAME, :a->USERNAME, :a->PERSONALNR indicator :ind, :a->EVENTCODE;
    if (ind < 0) strcpy(a->USERNAME, " ");
    if (sqlca.sqlcode < 0)
    {
        fst = 1;
        sprintf(error_msg, " AaauftAusg_auft_ereig: fetch Ausg_auft_ereig %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        if (datum == 0) EXEC SQL close Ausg_auft_ereig;
        else EXEC SQL close Ausg_auft_ereig2;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

/*** AAAUFT-STATUS-AE ********************************************************/

int AaauftStatusae(struct AUFSTATUS* d, char* error_msg)
{
    double faktur_wert = 0;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUFSTATUS* a;
    double WERT_LIEF;
    long ANZPOS;
    long ANZBEHAELT;
    char KDAUFTRAGSTAT[L_AUFTRAG_KDAUFTRAGSTAT+1];
    long lTime;
    long lTimePhon;
    long lTimePara;
    long lDate;
    short ind;
    short Vz_von;
    short Vz_bis;
    long lDateDelivery;
    EXEC SQL END DECLARE SECTION;

    char* fun = "AaauftStatusae";

    a = d;

    lTime = AllgGetTime() / 100;
    lDate = AllgGetDate();

    if (a->ANZ_ER == 0) /* nase alle VZs , ANZ_ER zweckentfremdet*/
    {
        Vz_von = 0;
        Vz_bis = 99;
    }
    else
    {
        Vz_von = a->ANZ_ER;
        Vz_bis = a->ANZ_ER;
    }

    a->ANZ_ER = 0;
    a->ANZ_BF = 0;
    a->ANZ_FA = 0;
    a->ANZ_ZU = 0;
    a->ANZ_IK = 0;
    a->ANZ_GD = 0;
    a->ANZ_ST = 0;
    a->ANZ_IE = 0;
    a->ANZ_IAEN = 0;
    a->ANZ_DD = 0;
    a->ANZ_UNBEKANNT = 0;
    a->FAKTUR_ZEILEN = 0;
    a->FAKTUR_WERT = 0;
    a->WERT_AND_NL = 0;     /* nase spaeter */
    a->ANZ_WANNEN = 0;

    EXEC SQL declare Statusae scroll cursor with hold for
        select
            kdauftragstat,
            wertlieferung,
            anzpos,
            anzbehaelt,
            datumauslieferung
        from kdauftrag
        where
            kdauftrag.vertriebszentrumnr    >=   :Vz_von   and
            kdauftrag.vertriebszentrumnr    <=   :Vz_bis;

    EXEC SQL open Statusae;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftStatusae: open Statusae %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    for (;;)
    {
        EXEC SQL fetch  Statusae
            into
                :KDAUFTRAGSTAT,
                :WERT_LIEF,
                :ANZPOS,
                :ANZBEHAELT,
                :lDateDelivery;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftStatusae: fetch Statusae %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Statusae;
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            break;
        }

        /* Reihenfolge ist wichtig */
        if      (KDAUFTRAGSTAT[AEORD_POS_STORNIERT]         == '1' ) a->ANZ_ST++;
        else if (KDAUFTRAGSTAT[AEORD_POS_FAKTUR_ENDE]       == '1' ) a->ANZ_FA++;
        else if (KDAUFTRAGSTAT[AEORD_POS_BEREIT_ZUR_FAKTUR] == '1' ) a->ANZ_BF++;
        else if (KDAUFTRAGSTAT[AEORD_POS_KOMMI_ENDE]        == '1' ) a->ANZ_BF++; /* nase */
        else if (KDAUFTRAGSTAT[AEORD_POS_IN_KOMMI]          == '1' ) a->ANZ_IK++;
        else if (KDAUFTRAGSTAT[AEORD_POS_ERFASST]           == '1' ) a->ANZ_ER++;
        else if (KDAUFTRAGSTAT[AEORD_POS_IN_AENDERUNG]      == '1' ) a->ANZ_IAEN++;
        else if (KDAUFTRAGSTAT[AEORD_POS_IN_ERFASSUNG]      == '1' ) a->ANZ_IE++;
        else if (KDAUFTRAGSTAT[AEORD_POS_ZURUECKGEST_DAFUE] == '1' )
        {
            if (lDateDelivery > lDate)                               a->ANZ_DD++;
            else                                                     a->ANZ_ZU++;
        }
        else if (KDAUFTRAGSTAT[AEORD_POS_ZURUECKGESTELLT]   == '1' )
        {
            if (lDateDelivery > lDate)                               a->ANZ_DD++;
            else                                                     a->ANZ_ZU++;
        }
        else                                                         a->ANZ_UNBEKANNT++;

        if (KDAUFTRAGSTAT[AEORD_POS_FAKTUR_ENDE] == '1')
        {
            a->FAKTUR_ZEILEN += ANZPOS;
            a->ANZ_WANNEN += ANZBEHAELT;
            faktur_wert  += WERT_LIEF;
            a->FAKTUR_WERT = faktur_wert;
        }
    }

    EXEC SQL select count(*) into :a->ANZ_GD from koauftrag
            where arechdruckpuffer = '1'    /*oracle == "1" nase??? */;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftStatusae: select count %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }


    /* summenbildung für rufplanstatus anzeige ************************/


    lTimePhon = GetTimeForCall( F_PHON, lTime );
    /* exec sql select count(*) into :lMax from tagplan
              where rufzeit  <= :lTimePhon
                and datum     = :lDate
                and anrufart  = C_PHON;
    SQLERR( fun, "sel count tagplan" )
    */
    exec sql select count(*), min( tagplanereignis.rufzeitgeaendert )
        into :a->PHONANZ, :a->PHONMIN  indicator :ind
        from tagplan, tagplanereignis
        where tagplan.idfnr     = tagplanereignis.idfnr
          and tagplan.filialnr  >= :Vz_von
          and tagplan.filialnr  <= :Vz_bis
          and tagplan.filialnr  = tagplanereignis.filialnr
          and tagplan.rufzeit   = tagplanereignis.rufzeit
          and tagplan.datum     = tagplanereignis.datum
          and tagplan.lfdaktion = tagplanereignis.lfdaktion
          and tagplanereignis.rufzeitgeaendert <= :lTimePhon
          and tagplan.datum = :lDate
          and ( tagplanereignis.status = 7
              or tagplanereignis.status = 6 )
          and tagplan.anrufart = C_PHON;
    if (ind < 0) a->PHONMIN = 0;
    SQLERR( fun, "sel count phonetik" )

    a->PHONANZ = CheckTimeToNull( a->PHONANZ );
    a->PHONMIN = CheckTimeToNull( a->PHONMIN ) ?
                 GetTimeDiffInMin( lTimePhon, a->PHONMIN ) : 0;

    lTimePara = GetTimeForCall( F_PARA, lTime );
    /* exec sql select count(*) into :lMax from tagplan
              where rufzeit  <= :lTimePara
                and datum     = :lDate
                and anrufart  = C_PARA;
    SQLERR( fun, "sel count tagplan" )
    */
    exec sql select count(*), min( tagplanereignis.rufzeitgeaendert )
        into :a->PARAANZ, :a->PARAMIN  indicator :ind
        from tagplan, tagplanereignis
        where tagplan.idfnr     = tagplanereignis.idfnr
          and tagplan.filialnr  >= :Vz_von
          and tagplan.filialnr  <= :Vz_bis
          and tagplan.filialnr  = tagplanereignis.filialnr
          and tagplan.rufzeit   = tagplanereignis.rufzeit
          and tagplan.datum     = tagplanereignis.datum
          and tagplan.lfdaktion = tagplanereignis.lfdaktion
          and tagplanereignis.rufzeitgeaendert <= :lTimePara
          and tagplan.datum = :lDate
          and ( tagplanereignis.status = 7
              or tagplanereignis.status = 6 )
          and tagplan.anrufart = C_PARA;
    if (ind < 0) a->PARAMIN = 0;
    SQLERR( fun, "sel count phonetik" )

    a->PARAANZ = CheckTimeToNull( a->PARAANZ );
    a->PARAMIN = CheckTimeToNull( a->PARAMIN ) ?
                 GetTimeDiffInMin( lTimePara, a->PARAMIN ) : 0;

    return 0;
}

/*** AAAUFT-STAT-PLAN-SEL ****************************************************/

int AaauftStatplan_sel( struct AUFSTPLAN* a, char* error_msg )
{
    exec SQL begin declare section;
    struct AUFSTPLAN* d;
    long lDate;
    int  iChangeTime;
    short ind;
    short Vz_von;
    short Vz_bis;
    exec sql end declare section;

    static int fst = 1;
    char* fun = "AaauftStatplan_sel";

    d = a;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        if (a->RUFZEITGEAENDERT == 0) /* nase alle VZs , RUFZEITGEAENDERT zweckentfremdet*/
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->RUFZEITGEAENDERT;
            Vz_bis = a->RUFZEITGEAENDERT;
        }
        lDate = AllgGetDate();
        exec sql declare Statplan_sel cursor for
            select tagplan.anrufart,
                   tagplanereignis.idfnr,
                   tagplanereignis.rufzeit,
                   max( tagplanereignis.rufzeitgeaendert )
            from tagplan,tagplanereignis
            where tagplan.rufzeit = tagplanereignis.rufzeit
              and tagplan.datum = tagplanereignis.datum
              and tagplan.lfdaktion = tagplanereignis.lfdaktion
              and tagplan.idfnr = tagplanereignis.idfnr
              and tagplan.filialnr  >= :Vz_von
              and tagplan.filialnr  <= :Vz_bis
              and tagplan.filialnr  = tagplanereignis.filialnr
              and tagplan.datum = :lDate
              and status = 6              /* verschobe Aufträge */
            group by tagplan.anrufart,
                     tagplanereignis.idfnr,
                     tagplanereignis.rufzeit;

        exec sql open Statplan_sel;
        SQLERROR( fun, "open Statplan_sel" )
    }

    if (d->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        exec sql close Statplan_sel;
        SQLERROR( fun, "close Statplan_sel" )
        return 1;
    }


    exec sql fetch Statplan_sel into AUFSTPLAN_ZEIGER( d), :iChangeTime  indicator :ind;
    SQLERROR( fun, "fetch Statplan_sel" )

    if (ind < 0) iChangeTime = 0;
    if (SCODE == SQLNOTFOUND)
        return 1;

    iChangeTime = CheckTimeToNull( iChangeTime );
    d->RUFZEITGEAENDERT = GetTimeDiffInMin( iChangeTime, d->RUFZEITGEAENDERT );

    return 0;
}


int AaauftZeilenstatistik(struct AUFZLNSTAT* d, char* error_msg)
{
    static int fst = 1;
    static int altrel = 0;
    static int endfetch = 0;
    static long intervallzeit;
    static long startzeit;
    static long endzeit;
    static int wert;
    static int zeilen;
    static int zeilendaf;
    static int zeilenalph;
    static int auftraege;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUFZLNSTAT* a;
    long nr;
    long beginzeit;
    long endingzeit;
    long aufzeit;
    long aufwert;
    long aufzeil;
    long aufzeildaf;
    long aufzeilalph;
    char KDAUFTRAGSTAT[L_AUFTRAG_KDAUFTRAGSTAT+1];
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (endfetch)
    {
        endfetch = 0;
        return 1;
    }

    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        wert = 0;
        zeilen = 0;
        zeilendaf = 0;
        zeilenalph = 0;
        auftraege = 0;
        beginzeit = a->ZEIT_VON * 1000;
        endingzeit = a->ZEIT_BIS * 1000;
        if (a->DATUM == 0)
        {
            datum = AllgGetDate();
            altrel = 0;
        }
        else
        {
            datum = a->DATUM;
            altrel = 1;
        }
        if (altrel == 0)
        {
            EXEC SQL declare Zeilenstatistik cursor with hold for
            select kdauftragereignis.kdauftragnr, kdauftragereignis.zeit
            from kdauftragereignis, kdauftrag
            where   kdauftragereignis.zeit >= :beginzeit
            and     kdauftragereignis.zeit <= :endingzeit
            and     kdauftragereignis.datum = :datum
    /*      and     kdauftragereignis.ereignisart = AEORD_POS_ERFASST       */
    /*      and     kdauftragereignis.ereignisart = AEORD_POS_FAKTUR_ENDE   */
            and     kdauftragereignis.ereignisart = AEORD_POS_TRANSMITTED
            and     kdauftrag.vertriebszentrumnr = :a-> WERT
            and     kdauftrag.kdauftragnr = kdauftragereignis.kdauftragnr
            order by kdauftragereignis.zeit;
        }
        else
        {
            EXEC SQL declare Zeilenstatistika cursor with hold for
            select akdauftragereignis.kdauftragnr, akdauftragereignis.zeit
            from akdauftragereignis, akdauftrag
            where   akdauftragereignis.zeit >= :beginzeit
            and     akdauftragereignis.zeit <= :endingzeit
            and     akdauftragereignis.datum = :datum
    /*      and     akdauftragereignis.ereignisart = AEORD_POS_ERFASST      */
    /*      and     akdauftragereignis.ereignisart = AEORD_POS_FAKTUR_ENDE  */
            and     akdauftragereignis.ereignisart = AEORD_POS_TRANSMITTED
            and     akdauftrag.vertriebszentrumnr = :a-> WERT
            and     akdauftrag.kdauftragnr = akdauftragereignis.kdauftragnr
            and     akdauftrag.datum = akdauftragereignis.datum
            order by akdauftragereignis.zeit;
        }

        if (altrel == 0) EXEC SQL open Zeilenstatistik;
        else EXEC SQL open Zeilenstatistika;

         if (sqlca.sqlcode < 0 )
         {
            fst = 1;
            sprintf(error_msg, " AaauftZeilenstatistik: open Zeilenstatistik %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        intervallzeit = a->ANZAHL;
        startzeit = a->ZEIT_VON;
        AllgAddTime(startzeit, intervallzeit, &endzeit);
    }

    for (;;)
    {
        if (altrel == 0) EXEC SQL fetch Zeilenstatistik into :nr, :aufzeit;
        else EXEC SQL fetch Zeilenstatistika  into :nr, :aufzeit;
        aufzeit = aufzeit/1000;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftZeilenstatistik: fetch Zeilenstatistik %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            if (altrel == 0) EXEC SQL close Zeilenstatistik;
            else EXEC SQL close Zeilenstatistika;
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            fst = 1;
            if (altrel == 0) EXEC SQL close Zeilenstatistik;
            else EXEC SQL close Zeilenstatistika;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftZeilenstatistik: close Zeilenstatistik %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            if (auftraege == 0) return 1;
            a->ZEIT_VON = startzeit;
            AllgAddTime(endzeit, -100, &a->ZEIT_BIS);
            a->ANZAHL = zeilen;
            a->WERT = wert;
            a->ANZAHL_DAFUE = zeilendaf;
            a->ANZAHL_ALPHA = zeilenalph;
            a->ANZAHL_AUFTRAG = auftraege;
            a->DATUM = datum;
            endfetch = 1;
            return 0;
        }
        if (altrel == 0)
        {
            EXEC SQL select anzpos,
                wertlieferung,
                anzposdafue,
                anzalphatext,
                kdauftragstat
                into
                    :aufzeil ,
                    :aufwert ,
                    :aufzeildaf ,
                    :aufzeilalph,
                    :KDAUFTRAGSTAT
                from kdauftrag
                where kdauftragnr = :nr;
        }
        else
        {
            EXEC SQL select anzpos,
                wertlieferung,
                anzposdafue,
                anzalphatext,
                kdauftragstat
                into
                    :aufzeil ,
                    :aufwert ,
                    :aufzeildaf ,
                    :aufzeilalph,
                    :KDAUFTRAGSTAT
                from akdauftrag
                where kdauftragnr = :nr
                  and datum = :datum;
        }
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftZeilenstatistik: select kdauftragnr %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND) continue;
        if (KDAUFTRAGSTAT[AEORD_POS_STORNIERT] != '1')
        {
            if (aufzeit > endzeit)
            {
                if (zeilen == 0)  /* beim ersten mal auf entsprechende Zeit */
                {                 /* ohne Wertausgabe */
                    for (; aufzeit > endzeit;)
                    {
                        startzeit = endzeit;
                        AllgAddTime(startzeit, intervallzeit, &endzeit);
                    }
                    zeilen = aufzeil;
                    zeilendaf = aufzeildaf;
                    zeilenalph = aufzeilalph;
                    auftraege = 1;
                    wert = aufwert;
                }
                else
                {
                    a->ZEIT_VON = startzeit;
                    AllgAddTime(endzeit, -100, &a->ZEIT_BIS);
                    a->ANZAHL = zeilen;
                    a->WERT = wert;
                    a->ANZAHL_DAFUE = zeilendaf;
                    a->ANZAHL_ALPHA = zeilenalph;
                    a->ANZAHL_AUFTRAG = auftraege;
                    a->DATUM = datum;
                    zeilen = aufzeil;
                    zeilendaf = aufzeildaf;
                    zeilenalph = aufzeilalph;
                    wert = aufwert;
                    auftraege = 1;
                    for (; aufzeit > endzeit;) /* auf entsprechende Zeit */
                    {
                        startzeit = endzeit;
                        AllgAddTime(startzeit, intervallzeit, &endzeit);
                    }
                    break;
                }
            }
            else
            {
                auftraege ++;
                zeilen = zeilen + aufzeil;
                zeilendaf = zeilendaf + aufzeildaf;
                zeilenalph = zeilenalph + aufzeilalph;
                wert = wert + aufwert;
            }
        }
    }

    return 0;
}

int AaauftSel_alt_kopf(struct AUFTEXTE* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUFTEXTE* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    datum = sdatum;
    auftragnr = sauftragnr;
    if (a->BEMERKUNGSART == AUF_TEXT_KOPF_INFO) a->BEMERKUNGSART = AUF_TEXT_KOPF;
    else if (a->BEMERKUNGSART == AUF_TEXT_FUSS_INFO) a->BEMERKUNGSART = AUF_TEXT_KOPF_INFO;

    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        EXEC SQL declare Sel_alt_kopf scroll cursor with hold for
            select
                AKDAUFTRAGBEM.BEMERKUNGSART,
                AKDAUFTRAGBEM.BEMERKUNGSNR,
                AKDAUFTRAGBEM.BEMERKUNGEN
            from akdauftragbem
            where datum = :datum
              and kdauftragnr = :auftragnr
              and bemerkungsart = :a->BEMERKUNGSART
            order by bemerkungsnr  ;

        EXEC SQL open Sel_alt_kopf;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_alt_kopf: open Sel_alt_kopf %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Sel_alt_kopf;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_alt_kopf: close Sel_alt_kopf %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_alt_kopf into AUFTEXTE_ZEIGER(a);
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSel_alt_kopf: fetch Sel_alt_kopf %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Sel_alt_kopf;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

int AaauftSel_alt_auft(struct AUFTRAG* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct AUFTRAG* a;
    EXEC SQL END DECLARE SECTION;

    a = d;

    sdatum = a->ANZPOS;     /* dient zur uebergabe des Datums */
    sauftragnr = a->KDAUFTRAGNR;
    datum = a->ANZPOS;      /* dient zur uebergabe des Datums */
    auftragnr = a->KDAUFTRAGNR;

    EXEC SQL select first 1
        akdauftrag.KDAUFTRAGNR,
        akdauftrag.IDFNR,
        akdauftrag.TOURID,
        akdauftrag.KDAUFTRAGART,
        akdauftrag.KOART,
        akdauftrag.BUCHART,
        akdauftrag.WERTAUFTRAG,
        akdauftrag.WERTLIEFERUNG,
        akdauftrag.WERTZEILEN,
        akdauftrag.ANZPOS,
        akdauftrag.BEMERKUNGEN,
        akdauftrag.RECHNUNGNR,
        akdauftrag.DATUMVALUTA,
        akdauftrag.KUNDENNR,
        akdauftrag.VERTRIEBSZENTRUMNR,
        akdauftrag.KDAUFTRAGNRFILIALE,
        akdauftrag.SENDESTATUS,
        akdauftrag.PAYMENTDATE,
        akdauftrag.PAYMENTTYPE,
        akdauftrag.TENDERNO,
        akdauftrag.WERTNETTO,
        nvl(LEFT(aorderremarks.REMARKTEXT, 10), '')
    into
        :a->KDAUFTRAGNR,
        :a->IDFNR,
        :a->TOURID,
        :a->KDAUFTRAGART,
        :a->KOART,
        :a->BUCHART,
        :a->WERTAUFTRAG,
        :a->WERTLIEFERUNG,
        :a->WERTZEILEN,
        :a->ANZPOS,
        :a->BEMERKUNGEN,
        :a->RECHNUNGNR,
        :a->DATUMVALUTA,
        :a->KUNDENNR,
        :a->VERTRIEBSZENTRUMNR,
        :a->KDAUFTRAGNRFILIALE,
        :a->SENDESTATUS,
        :a->PAYMENTDATE,
        :a->PAYMENTTYPE,
        :a->TENDERNO,
        :a->WERTNETTO,
        :a->SAP_REFERENCENO
    from akdauftrag
    left join aorderremarks on aorderremarks.cscorderno = akdauftrag.kdauftragnr and aorderremarks.datum = akdauftrag.datum
          and aorderremarks.remarktype = 21
    where akdauftrag.datum = :datum
      and kdauftragnr = :auftragnr  ;

    if (a->DATUMVALUTA == 0) a->VALUTAMONATE = 0;
    else
    {
        a->VALUTAMONATE = (a->DATUMVALUTA - datum) / 100;
        if (a->VALUTAMONATE > 87) a->VALUTAMONATE -= 88;
    }

    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSel_alt_auft select %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
        return -2;
    }

    EXEC SQL select
        ORDVALFTAXFSDISC + ORDVALLTAXFSDISC + ORDVALNTAXFSDISC,
        ORDVALFTAXFS + ORDVALLTAXFS + ORDVALNTAXFS - ORDVALFTAXFSDISC - ORDVALLTAXFSDISC - ORDVALNTAXFSDISC,
        ORDVALFTAXHFDISC + ORDVALLTAXHFDISC + ORDVALNTAXHFDISC,
        ORDVALFTAXHF + ORDVALLTAXHF + ORDVALNTAXHF - ORDVALFTAXHFDISC - ORDVALLTAXHFDISC - ORDVALNTAXHFDISC,
        ORDVALFTAXRSDISC + ORDVALLTAXRSDISC + ORDVALNTAXRSDISC,
        ORDVALFTAXRS + ORDVALLTAXRS + ORDVALNTAXRS - ORDVALFTAXRSDISC - ORDVALLTAXRSDISC - ORDVALNTAXRSDISC
    into
        :a->WERTNETTO_FV,
        :a->WERTTAX_FV,
        :a->WERTNETTO_KK,
        :a->WERTTAX_KK,
        :a->WERTNETTO_EH,
        :a->WERTTAX_EH
    from akdauftragwerte
    where datum = :datum
      and kdauftragnr = :auftragnr  ;

    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        a->WERTNETTO_FV = 0;
        a->WERTTAX_FV = 0;
        a->WERTNETTO_KK = 0;
        a->WERTTAX_KK = 0;
        a->WERTNETTO_EH = 0;
        a->WERTTAX_EH = 0;
    }

    return 0;
}

int AaauftSel_alt_pos(struct AUFPOSBUCH* d, char* error_msg)
{
    static int fst = 1;
    static int FREMDSPRACHE_ALT = 2;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUFPOSBUCH* a;
    int etposschalter1;
    int etposschalter2;
    int etposschalter6;
    int etartklasse1;
    int etartschalter2;
    short geraetetyp;
    double preisekaponetto;
    long DatumVon;
    short ind1;
    short ind2;
    EXEC SQL END DECLARE SECTION;

    a = d;
    datum = sdatum;
    auftragnr = sauftragnr;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        EXEC SQL select min(datum) into :DatumVon
            from akdauftragereignis
            where datum_rechnung = :datum
              and kdauftragnr = :auftragnr
              and EREIGNISART = 1;

         EXEC SQL declare Sel_alt_pos scroll cursor with hold for
            select unique
                p.POSNR,
                p.ARTIKEL_NR,
                p.ETPOSSCHALTER1,
                p.ETPOSSCHALTER2,
                p.ETPOSSCHALTER6,
                p.MENGEBESTELLT,
                p.MENGENATRA,
                p.BEMERKUNGEN,
                p.MENGEBESTAETIGT,
                p.MENGEGELIEFERT,
                p.LAGERBEREICHNR,
                p.ETARTSCHALTER2,
                p.geraettyp,
                p.SENDESTATUS,
                p.preisekapo,
                p.preisekaponetto,
                p.PREISFAKTUR,
                p.preisvkapo,
                p.code_type,
                p.article_code,
                p.PROMOTION_NO,
                p.PROMOTYP,
                p.PREIS_TYP,
                p.IBTTYPE,
                p.IBTTYPEID,
                p.PREISEKAPOFREE,
                p.ETARTKLASSE1,
                p.ETARTSCHALTER1
            from akdauftragpos p
            where p.datum = :datum
              and p.kdauftragnr = :auftragnr;
    /*        and p.datum = t.datum
              and p.kdauftragnr = t.kdauftragnr
              and p.posnr = t.posnr;
    */
        EXEC SQL open Sel_alt_pos;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_alt_pos: open Sel_alt_pos %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Sel_alt_pos;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_alt_pos: close Sel_alt_pos %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_alt_pos
        into
            :a->POSNR,
            :a->ARTIKEL_NR,
            :etposschalter1,
            :etposschalter2,
            :etposschalter6,
            :a->MENGEBESTELLT,
            :a->MENGENATRA,
            :a->BEMERKUNG,
            :a->MENGEABGEBUCHT,
            :a->MENGEGELIEFERT,
            :a->LAGERBEREICHNR,
            :a->ETARTSCHALTER2,
            :geraetetyp,
            :a->SENDESTATUS,
            :a->PREISEKAPO,
            :preisekaponetto,
            :a->PREISFAKTUR,
            :a->PREISVKAPO,
            :a->CODE_TYPE,
            :a->ARTICLE_CODE,
            :a->PROMOTION_NO,
            :a->PROMOTYP,
            :a->PREIS_TYP,
            :a->IBTTYPE,
            :a->IBTTYPEID,
            :a->PREISEKAPOFREE,
            :a->ETARTKLASSE1,
            :a->ETARTSCHALTER1;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSel_alt_pos: fetch Sel_alt_pos %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Sel_alt_pos;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
    a->ETPOSSCHALTER2 = etposschalter2;

    EXEC SQL select
        t.DELIVERYDATE,
        t.DELIVERYTIME
    into
        :a->DELIVERYDATE,
        :a->DELIVERYTIME
    from akdauftragpostour t, akdauftragpostour ta
    where t.datum = :datum
      and t.kdauftragnr = :auftragnr
      and t.posnr = :a->POSNR
      and ta.datum = t.datum
      and ta.kdauftragnr = t.kdauftragnr
      and ta.posnr = 0
      and (ta.deliverydate != t.deliverydate
            or ta.deliverytime != t.deliverytime);
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        a->DELIVERYDATE = 0;
        a->DELIVERYTIME = 0;
    }

    if (preisekaponetto > 0) a->PREISEKAPO = preisekaponetto;
    if (AllgBitleisteN(etposschalter2, 0)) a->STATUS = ITEM_STAT_DISPO;
    else if (AllgBitleisteN(etposschalter2, 1)) a->STATUS = ITEM_STAT_ZUGESAGT;
    else if (AllgBitleisteN(etposschalter2, 2)) a->STATUS = ITEM_STAT_NACHLIEFERN;
    else a->STATUS = ITEM_STAT_NORMAL;

    if (AllgBitleisteN(etposschalter6, 12)) a->KZINFOTEXT[0] = '1';
    else a->KZINFOTEXT[0] = '0';
    a->KZINFOTEXT[1] = '\0';

    /* 1.Position */
    a->POSART[0] = '*';
    if ( geraetetyp == DVC_VIDEO_WORKSTATION ||
         geraetetyp == DVC_VIDEO_TERMINAL    ||
         geraetetyp == DVC_VIDEO )
    {
        a->POSART[0] = '0';
    }
    if ( geraetetyp == DVC_DCT_PARALLEL        ||
         geraetetyp == DVC_DCT )
    {
        a->POSART[0] = '1';
    }
    if (   (geraetetyp != DVC_DCT_SERIAL && AllgBitleisteN(etposschalter1, 1))
        || AllgBitleisteN(etposschalter1, 10) )
    {
        a->POSART[0] = '2';
    }
    if (AllgBitleisteN(etposschalter1, 2))
    {
        a->POSART[0] = '3';
    }
    if (geraetetyp == DVC_DCT_SERIAL && !AllgBitleisteN(etposschalter1, 1))
    {
        a->POSART[0] = '5';
    }
    if (geraetetyp == DVC_DCT_SERIAL && AllgBitleisteN(etposschalter1, 1))
    {
        a->POSART[0] = '6';
    }

    /* 2.Position */
    AllgEntfSpaces(a->BEMERKUNG);
    if (AllgBitleisteN(etposschalter1, 9))
    {
        a->POSART[1] = '2';
    }
    else if (AllgBitleisteN(etposschalter1, 1) || (AllgBitleisteN(etposschalter1, 10) && !AllgBitleisteN(etposschalter1, 9)))
    {
        a->POSART[1] = '3';
    }
    else if (strlen(a->BEMERKUNG) != 0)
    {
        a->POSART[1] = '4';
    }
    else
    {
        a->POSART[1] = '0';
    }
    a->POSART[2] = '\0';

    a->DARREICHFORM[0] = '\0';
    a->EINHEIT[0] = '\0';
    a->ARTIKEL_NAME[0] = '\0';

    if (a->ARTIKEL_NR != 0)
    {
        if (FREMDSPRACHE != FREMDSPRACHE_ALT)
        {
            FREMDSPRACHE_ALT = FREMDSPRACHE;
            EXEC SQL free sel_artdata;
            if (FREMDSPRACHE)
            {
                strcpy(str, "select ");
                strcat(str, "nvl(c.DARREICHFORM, z.DARREICHFORM), ");
                strcat(str, "nvl(c.EINHEIT, z.EINHEIT), ");
                strcat(str, "nvl(c.ARTIKEL_NAME, z.ARTIKEL_NAME), ");
                strcat(str, "z.etartklasse1, ");
                strcat(str, "(z.ETARTSCHALTER2 + ARTIKELLOKAL.ETARTSCHALTER2), ");
                strcat(str, "z.ARTIKEL_LANGNAME, ");
                strcat(str, "z.PRODUSERQUOTA ");
                strcat(str, "from ");
                strcat(str, "artikelzentral z, ");
                strcat(str, "outer artikellokal, outer ");
                strcat(str, ARTIKELZENTRAL_SPRACHE);
                strcat(str, " c ");
                strcat(str, "where z.artikel_nr = ? ");
                strcat(str, "and c.artikel_nr = z.artikel_nr ");
                strcat(str, "and artikellokal.artikel_nr = z.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
            }
            else
            {
                strcpy(str, "select ");
                strcat(str, "DARREICHFORM, ");
                strcat(str, "EINHEIT, ");
                strcat(str, "ARTIKEL_NAME, ");
                strcat(str, "etartklasse1, ");
                strcat(str, "(ARTIKELZENTRAL.ETARTSCHALTER2 + ARTIKELLOKAL.ETARTSCHALTER2), ");
                strcat(str, "ARTIKEL_LANGNAME, ");
                strcat(str, "PRODUSERQUOTA ");
                strcat(str, "from artikelzentral, ");
                strcat(str, "outer artikellokal ");
                strcat(str, "where artikelzentral.artikel_nr = ? ");
                strcat(str, "and artikellokal.artikel_nr = artikelzentral.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
            }
            EXEC SQL PREPARE sel_artdata FROM :str;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_alt_pos: prepare sel_artdata %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                EXEC SQL close Sel_alt_pos;
                return -1;
            }
        }
        EXEC SQL EXECUTE sel_artdata into
            :a->DARREICHFORM,
            :a->EINHEIT,
            :a->ARTIKEL_NAME,
            :etartklasse1,
            :etartschalter2,
            :a->ARTIKEL_LANGNAME
        using
            :a->ARTIKEL_NR,
            :FilialNr;
        if (!strncmp(cCountry, "BG", 2))
        {
            EXEC SQL select
                CALCAVP
            into
                :a->PREISVKAPO
            from akdauftrposrechart
            where datum = :datum
              and kdauftragnr = :auftragnr
              and posnr = :a->POSNR;
        }

        EXEC SQL select first 1
            DISCOUNTVALUEPCT,
            DISCOUNTVALPCTMAN
        into
            :a->DISCOUNTVALUEPCT,
            :a->DISCOUNTVALPCTMAN
        from akdauftragposrab
        where datum = :datum
          and kdauftragnr = :auftragnr
          and discountvaluepct > 0
          and posnr = :a->POSNR;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_alt_pos: select akdauftragposrab %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_alt_pos;
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            /* wenn keine Rabatt nach alter Rabattierung -> Pruefen neue Rabattlogik */
            a->DISCOUNTVALPCTMAN = 0;
    /*      EXEC SQL select first 1
                discountpercent
            into
                :a->DISCOUNTVALUEPCT
            from aorderpositiondiscount
            where orderdate = :datum
            and orderno = :auftragnr
            and discountpercent > 0
            and posno = :a->POSNR;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_alt_pos: select aorderposition %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                EXEC SQL close Sel_alt_pos;
                return -1;
            }
            if (sqlca.sqlcode == SQLNOTFOUND)
            {
                a->DISCOUNTVALUEPCT = 0;
            }
            */
            EXEC SQL select nvl(sum(discountpercent), 0)
            into
            :a->DISCOUNTVALUEPCT
            from aorderpositiondiscount
            where orderdate = :datum
            and orderno = :auftragnr
            and discountpercent > 0
            and posno = :a->POSNR;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_alt_pos: select aorderposition %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                EXEC SQL close Sel_alt_pos;
                return -1;
            }
        }
    }
    else
    {
        EXEC SQL select
            DARREICHFORM,
            PREISEKAPO,
            PREISEKGROSSO,
            RABATTFESTDM,
            RABATTFEST,
            RABATTFAEHIG,
            EINHEIT,
            BEZEICHNUNG,
            etartklasse1,
            etartschalter2,
            BEZEICHNUNG
        into
            :a->DARREICHFORM,
            :a->PREISEKAPO,
            :a->PREISEKGROSSO,
            :a->RABATTFESTDM,
            :a->RABATTFEST,
            :a->RABATTFAEHIG,
            :a->EINHEIT,
            :a->ARTIKEL_NAME,
            :etartklasse1,
            :etartschalter2,
            :a->ARTIKEL_LANGNAME,
            :a->PRODUSERQUOTA
        from adispoartikel
        where datum = :datum
          and kdauftragnr = :auftragnr
          and posnr = :a->POSNR;
    }
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSel_alt_pos: select artikel %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Sel_alt_pos;
        return -1;
    }

    if (AllgBitleisteN(etartschalter2, 5))
            a->MWSTSCHLUESSEL[0] = 2;
    else    a->MWSTSCHLUESSEL[0] = 1;

    if (AllgBitleisteN(etartklasse1, 6))
            a->TAXPFLICHTIG[0] = 1;
    else    a->TAXPFLICHTIG[0] = 0;

    if (a->ARTIKEL_NR != 0)
    {
        EXEC SQL select ibtrequest.QUANTITY, ibtrequest.IBTBRANCHNO
        into :a->MENGE, :a->FILIALNR1
        from ibtrequest
        where ibtrequest.cscorderno = :auftragnr
        and ibtrequest.cscorderposno = :a->POSNR
//        and ibtrequest.branchno = :FilialNr
        and TO_CHAR(ibtrequest.creationdatetime, '%Y%m%d')::integer between :DatumVon and :datum;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_alt_pos: select NewIBT %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_alt_pos;
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            a->MENGE = 0;
        }
    }
    return 0;
}

int AaauftSel_nachl(struct NACHLIEF* d, char* error_msg)
{
    static int fst = 1;
    int writeswitch;

    EXEC SQL BEGIN DECLARE SECTION;
    struct NACHLIEF* a;
    struct NACHLIEF  dat, *les;
    int vonidf, bisidf;
    int vonpzn, bispzn;
    int vontyp, bistyp;
    short vonVz;
    short bisVz;
    int vondatum;
    long bestellnr;
    char status[2];
    char cBuf[256];
    char cSel[2048];
    EXEC SQL END DECLARE SECTION;

    a = d;
    les = &dat;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        if (a->VERTRIEBSZENTRUMNR == 0)
        {
            vonVz = 0;
            bisVz = 99;
        }
        else vonVz = bisVz = a->VERTRIEBSZENTRUMNR;
        if (a->IDFNR == 0)
        {
            vonidf = 0;
            bisidf = 9999999;
        }
        else vonidf = bisidf = a->IDFNR;
        if (a->ARTIKEL_NR == 0)
        {
            vonpzn = 0;
            bispzn = 9999999;
        }
        else
        {
            vonpzn = bispzn = a->ARTIKEL_NR;
        }
        if (a->POSTYP == 0)
        {
            vontyp = 2;
            bistyp = 3;
        }
        else vontyp = bistyp = a->POSTYP;
        if (a->DATUM == 0) a->DATUM = 25000000;
        vondatum = a->POSNR;
        if (a->STATUS == 0)
        {
            EXEC SQL free dec_nachl;
            strcpy(cSel, "select ");
            strcat(cSel, NACHLIEF_PLISTE);
            strcat(cSel, " from nachlieferpos, artikelzentral, artikellokal, outer kunde ");
            strcat(cSel, " where nachlieferpos.idfnr >= ");
            sprintf(cBuf, "%d", vonidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.idfnr <= ");
            sprintf(cBuf, "%d", bisidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum <= ");
            sprintf(cBuf, "%d", a->DATUM);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum >= ");
            sprintf(cBuf, "%d", vondatum);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp >= ");
            sprintf(cBuf, "%d", vontyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp <= ");
            sprintf(cBuf, "%d", bistyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr >= ");
            sprintf(cBuf, "%d", vonpzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr <= ");
            sprintf(cBuf, "%d", bispzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.status <  2");
            if (a->KDAUFTRAGART[0] != ' ')
            {
                strcat(cSel, " and nachlieferpos.kdauftragart = ");
                sprintf(cBuf, "'%2.2s'", a->KDAUFTRAGART);
                strcat(cSel, cBuf);
            }
            strcat(cSel, " and kunde.kundennr = nachlieferpos.kundennr");
            strcat(cSel, " and kunde.vertriebszentrumnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikelzentral.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr >= ");
            sprintf(cBuf, "%d", vonVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr <= ");
            sprintf(cBuf, "%d", bisVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr in (");
            strcat(cSel, "  select RegionArten.RegionTeilNr from RegionArten");
            strcat(cSel, "  where  RegionArten.RegionNr = ");
            sprintf(cBuf, "%d", a->REGIONNR);
            strcat(cSel, cBuf);
            strcat(cSel, "  and RegionArten.RegionenTyp = 1)");
            strcat(cSel, "  and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, "  and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " order by nachlieferpos.datum, nachlieferpos.idfnr;");
            EXEC SQL prepare dec_nachl FROM :cSel;
            EXEC SQL declare Sel_nachl scroll cursor with hold for dec_nachl;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_nachl %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL open Sel_nachl;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_nachl %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        if (a->STATUS == 1)
        {
            EXEC SQL free dec_nachl1;
            strcpy(cSel, "select ");
            strcat(cSel, NACHLIEF_PLISTE);
            strcat(cSel, "from nachlieferpos, artikelzentral, outer artikellokal, outer kunde ");
            strcat(cSel, " where nachlieferpos.idfnr >= ");
            sprintf(cBuf, "%d", vonidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.idfnr <= ");
            sprintf(cBuf, "%d", bisidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum <= ");
            sprintf(cBuf, "%d", a->DATUM);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum >= ");
            sprintf(cBuf, "%d", vondatum);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp >= ");
            sprintf(cBuf, "%d", vontyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp <= ");
            sprintf(cBuf, "%d", bistyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr >= ");
            sprintf(cBuf, "%d", vonpzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr <= ");
            sprintf(cBuf, "%d", bispzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.status < 2");
            if (a->KDAUFTRAGART[0] != ' ')
            {
                strcat(cSel, " and nachlieferpos.kdauftragart = ");
                sprintf(cBuf, "'%2.2s'", a->KDAUFTRAGART);
                strcat(cSel, cBuf);
            }
            strcat(cSel, " and kunde.kundennr = nachlieferpos.kundennr");
            strcat(cSel, " and kunde.vertriebszentrumnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikelzentral.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.bestand = 0");
            strcat(cSel, " and artikellokal.filialnr = ");
            sprintf(cBuf, "%d", FilialNr);
            strcat(cSel, cBuf);
            strcat(cSel, " and trunc( artikelzentral.etartschalter1/4096 ) - 2 ");
            strcat(cSel, " * trunc( artikelzentral.etartschalter1/(4096*2)) = 1");
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr >= ");
            sprintf(cBuf, "%d", vonVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr <= ");
            sprintf(cBuf, "%d", bisVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr in (");
            strcat(cSel, " select RegionArten.RegionTeilNr from RegionArten");
            strcat(cSel, "  where RegionArten.RegionNr = ");
            sprintf(cBuf, "%d", a->REGIONNR);
            strcat(cSel, cBuf);
            strcat(cSel, " and RegionArten.RegionenTyp = 1)");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " order by nachlieferpos.datum, nachlieferpos.idfnr;");
            EXEC SQL prepare dec_nachl1 FROM :cSel;
            EXEC SQL declare Sel_nachl1 scroll cursor with hold for dec_nachl1;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_nachl1 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL open Sel_nachl1;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_nachl1 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        if (a->STATUS == 2)
        {
            EXEC SQL free dec_nachl2;
            strcpy(cSel, "select ");
            strcat(cSel, NACHLIEF_PLISTE);
            strcat(cSel, "from nachlieferpos, artikelzentral, artikellokal, outer kunde ");
            strcat(cSel, " where nachlieferpos.idfnr >= ");
            sprintf(cBuf, "%d", vonidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.idfnr <= ");
            sprintf(cBuf, "%d", bisidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum <= ");
            sprintf(cBuf, "%d", a->DATUM);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum >= ");
            sprintf(cBuf, "%d", vondatum);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp >= ");
            sprintf(cBuf, "%d", vontyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp <= ");
            sprintf(cBuf, "%d", bistyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr >= ");
            sprintf(cBuf, "%d", vonpzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr <= ");
            sprintf(cBuf, "%d", bispzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.status < 2");
            if (a->KDAUFTRAGART[0] != ' ')
            {
                strcat(cSel, " and nachlieferpos.kdauftragart = ");
                sprintf(cBuf, "'%2.2s'", a->KDAUFTRAGART);
                strcat(cSel, cBuf);
            }
            strcat(cSel, " and kunde.kundennr = nachlieferpos.kundennr");
            strcat(cSel, " and kunde.vertriebszentrumnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikelzentral.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.bestand = 0");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and trunc( artikellokal.etartschalter2/1 ) - 2 * trunc( artikellokal.etartschalter2/(1*2)) = 0");
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr >= ");
            sprintf(cBuf, "%d", vonVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr <= ");
            sprintf(cBuf, "%d", bisVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr in (");
            strcat(cSel, " select RegionArten.RegionTeilNr from RegionArten");
            strcat(cSel, "  where  RegionArten.RegionNr = ");
            sprintf(cBuf, "%d", a->REGIONNR);
            strcat(cSel, cBuf);
            strcat(cSel, " and RegionArten.RegionenTyp = 1)");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " order by nachlieferpos.datum, nachlieferpos.idfnr;");
            EXEC SQL prepare dec_nachl2 FROM :cSel;
            EXEC SQL declare Sel_nachl2 scroll cursor with hold for dec_nachl2;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_nachl2 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL open Sel_nachl2;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_nachl2 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        if (a->STATUS == 3)
        {
            EXEC SQL free dec_nachl3;
            strcpy(cSel, "select ");
            strcat(cSel, NACHLIEF_PLISTE);
            strcat(cSel, "from nachlieferpos, artikelzentral, artikellokal, articlequota, outer kunde ");
            strcat(cSel, " where nachlieferpos.idfnr >= ");
            sprintf(cBuf, "%d", vonidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.idfnr <= ");
            sprintf(cBuf, "%d", bisidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum <= ");
            sprintf(cBuf, "%d", a->DATUM);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum >= ");
            sprintf(cBuf, "%d", vondatum);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp >= ");
            sprintf(cBuf, "%d", vontyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp <= ");
            sprintf(cBuf, "%d", bistyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr >= ");
            sprintf(cBuf, "%d", vonpzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr <= ");
            sprintf(cBuf, "%d", bispzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.status < 2");
            if (a->KDAUFTRAGART[0] != ' ')
            {
                strcat(cSel, " and nachlieferpos.kdauftragart = ");
                sprintf(cBuf, "'%2.2s'", a->KDAUFTRAGART);
                strcat(cSel, cBuf);
            }
            strcat(cSel, " and kunde.kundennr = nachlieferpos.kundennr");
            strcat(cSel, " and kunde.vertriebszentrumnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikelzentral.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and articlequota.articleno = nachlieferpos.artikel_nr");
            strcat(cSel, " and articlequota.branchno = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and articlequota.customerno = nachlieferpos.kundennr");
            strcat(cSel, " and (articlequota.kumqty-articlequota.quota)  <=  0");
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr >= ");
            sprintf(cBuf, "%d", vonVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr <= ");
            sprintf(cBuf, "%d", bisVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr in (");
            strcat(cSel, "  select RegionArten.RegionTeilNr from RegionArten");
            strcat(cSel, "  where RegionArten.RegionNr = ");
            sprintf(cBuf, "%d", a->REGIONNR);
            strcat(cSel, cBuf);
            strcat(cSel, " and RegionArten.RegionenTyp=1)");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " order by nachlieferpos.datum, nachlieferpos.idfnr;");
            EXEC SQL prepare dec_nachl3 FROM :cSel;
            EXEC SQL declare Sel_nachl3 scroll cursor with hold for dec_nachl3;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_nachl3 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL open Sel_nachl3;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_nachl3 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        if (a->STATUS == 10)
        {
            EXEC SQL free dec_nachl10;
            strcpy(cSel, "select ");
            strcat(cSel, NACHLIEF_PLISTE);
            strcat(cSel, " from nachlieferpos, artikelzentral, artikellokal, outer kunde");
            strcat(cSel, " where nachlieferpos.idfnr >= ");
            sprintf(cBuf, "%d", vonidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.idfnr <= ");
            sprintf(cBuf, "%d", bisidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum <= ");
            sprintf(cBuf, "%d", a->DATUM);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum >= ");
            sprintf(cBuf, "%d", vondatum);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp >= ");
            sprintf(cBuf, "%d", vontyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp <= ");
            sprintf(cBuf, "%d", bistyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr >= ");
            sprintf(cBuf, "%d", vonpzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr <= ");
            sprintf(cBuf, "%d", bispzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.status < 2");
            if (a->KDAUFTRAGART[0] != ' ')
            {
                strcat(cSel, " and nachlieferpos.kdauftragart = ");
                sprintf(cBuf, "'%2.2s'", a->KDAUFTRAGART);
                strcat(cSel, cBuf);
            }
            strcat(cSel, " and kunde.kundennr = nachlieferpos.kundennr");
            strcat(cSel, " and kunde.vertriebszentrumnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikelzentral.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.bestand = 0");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and trunc( artikellokal.etartschalter1/16384 ) - 2 ");
            strcat(cSel, "  * trunc( artikellokal.etartschalter1/(16384*2)) = 1");
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr >= ");
            sprintf(cBuf, "%d", vonVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr <= ");
            sprintf(cBuf, "%d", bisVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr in (");
            strcat(cSel, " select RegionArten.RegionTeilNr from RegionArten");
            strcat(cSel, " where RegionArten.RegionNr = ");
            sprintf(cBuf, "%d", a->REGIONNR);
            strcat(cSel, cBuf);
            strcat(cSel, " and RegionArten.RegionenTyp = 1)");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " order by nachlieferpos.datum, nachlieferpos.idfnr;");
            EXEC SQL prepare dec_nachl10 FROM :cSel;
            EXEC SQL declare Sel_nachl10 scroll cursor with hold for dec_nachl10;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_nachl10 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL open Sel_nachl10;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_nachl10 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        if (a->STATUS == 11)
        {
            EXEC SQL free dec_nachl11;
            strcpy(cSel, "select ");
            strcat(cSel, NACHLIEF_PLISTE);
            strcat(cSel, " from nachlieferpos, artikelzentral, artikellokal, outer kunde");
            strcat(cSel, " where nachlieferpos.idfnr >= ");
            sprintf(cBuf, "%d", vonidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.idfnr <= ");
            sprintf(cBuf, "%d", bisidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum <= ");
            sprintf(cBuf, "%d", a->DATUM);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum >= ");
            sprintf(cBuf, "%d", vondatum);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp >= ");
            sprintf(cBuf, "%d", vontyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp <= ");
            sprintf(cBuf, "%d", bistyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr >= ");
            sprintf(cBuf, "%d", vonpzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr <= ");
            sprintf(cBuf, "%d", bispzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.status < 2");
            if (a->KDAUFTRAGART[0] != ' ')
            {
                strcat(cSel, " and nachlieferpos.kdauftragart = ");
                sprintf(cBuf, "'%2.2s'", a->KDAUFTRAGART);
                strcat(cSel, cBuf);
            }
            strcat(cSel, " and kunde.kundennr = nachlieferpos.kundennr");
            strcat(cSel, " and kunde.vertriebszentrumnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikelzentral.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
//          strcat(cSel, " and artikellokal.bestand = 0");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and trunc( artikelzentral.etartschalter1/4096 ) - 2 ");
            strcat(cSel, " * trunc( artikelzentral.etartschalter1/(4096*2)) = 1");
            strcat(cSel, " and trunc( artikellokal.etartschalter1/16384 ) - 2 ");
            strcat(cSel, " * trunc( artikellokal.etartschalter1/(16384*2)) = 1");
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr >= ");
            sprintf(cBuf, "%d", vonVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr <= ");
            sprintf(cBuf, "%d", bisVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr in (");
            strcat(cSel, " select RegionArten.RegionTeilNr from RegionArten");
            strcat(cSel, " where RegionArten.RegionNr = ");
            sprintf(cBuf, "%d", a->REGIONNR);
            strcat(cSel, cBuf);
            strcat(cSel, " and RegionArten.RegionenTyp = 1)");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " order by nachlieferpos.datum, nachlieferpos.idfnr;");
            EXEC SQL prepare dec_nachl11 FROM :cSel;
            EXEC SQL declare Sel_nachl11 scroll cursor with hold for dec_nachl11;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_nachl11 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL open Sel_nachl11;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_nachl11 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        if (a->STATUS == 100)
        {
            EXEC SQL drop table tmpoffbes;
            EXEC SQL create temp table tmpoffbes (
                 KDAUFTRAGNR INTEGER,
                 POSNR INTEGER,
                 DATUM INTEGER,
                 POSTYP SMALLINT,
                 IDFNR INTEGER,
                 ARTIKEL_NR INTEGER,
                 MENGE INTEGER,
                 FILIALNR1 SMALLINT,
                 FILIALNR2 SMALLINT,
                 FILIALNR3 SMALLINT,
                 STATUS SMALLINT,
                 MATCHCODE CHAR(12),
                 KZKDKLASSE CHAR(3),
                 KUNDENNR INTEGER,
                 VERTRIEBSZENTRUMNR SMALLINT,
                 REGIONNR SMALLINT,
                 EINHEIT CHAR(9),
                 ARTIKEL_NAME CHAR(30),
                 KDAUFTRAGART CHAR(2),
                 BEMERKUNGEN CHAR(240),
                 BESTAND INTEGER);
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: create temp table tmpoffbes %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL free dec_nachl100;
            strcpy(cSel, "select ");
            strcat(cSel, NACHLIEF_PLISTE);
            strcat(cSel, " from nachlieferpos, artikelzentral, outer artikellokal, outer kunde");
            strcat(cSel, " where nachlieferpos.idfnr >= ");
            sprintf(cBuf, "%d", vonidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.idfnr <= ");
            sprintf(cBuf, "%d", bisidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum <= ");
            sprintf(cBuf, "%d", a->DATUM);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum >= ");
            sprintf(cBuf, "%d", vondatum);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp >= ");
            sprintf(cBuf, "%d", vontyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp <= ");
            sprintf(cBuf, "%d", bistyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr >= ");
            sprintf(cBuf, "%d", vonpzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr <= ");
            sprintf(cBuf, "%d", bispzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.status < 2");
            if (a->KDAUFTRAGART[0] != ' ')
            {
                strcat(cSel, " and nachlieferpos.kdauftragart = ");
                sprintf(cBuf, "'%2.2s'", a->KDAUFTRAGART);
                strcat(cSel, cBuf);
            }
            strcat(cSel, " and kunde.kundennr = nachlieferpos.kundennr");
            strcat(cSel, " and kunde.vertriebszentrumnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikelzentral.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
//          strcat(cSel, " and artikellokal.bestand = 0");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr ");
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr >= ");
            sprintf(cBuf, "%d", vonVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr <= ");
            sprintf(cBuf, "%d", bisVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr in (");
            strcat(cSel, " select RegionArten.RegionTeilNr from RegionArten");
            strcat(cSel, " where RegionArten.RegionNr = ");
            sprintf(cBuf, "%d", a->REGIONNR);
            strcat(cSel, cBuf);
            strcat(cSel, " and RegionArten.RegionenTyp = 1)");
//          strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
//          strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " order by nachlieferpos.datum, nachlieferpos.idfnr;");
            EXEC SQL prepare dec_nachl100 FROM :cSel;
            EXEC SQL declare Sel_nachl100 scroll cursor with hold for dec_nachl100;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_nachl100 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL declare Sel_bespo100 scroll cursor with hold for
                select besposi.bestell_nr into :bestellnr from besposi
                where artikel_nr = :les->ARTIKEL_NR
                and filialnr = :les->VERTRIEBSZENTRUMNR ;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_bespo100 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL open Sel_nachl100;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_nachl100 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            for (;;)
            {
                EXEC SQL fetch relative :a->FETCH_REL Sel_nachl100 into NACHLIEF_ZEIGER(les);
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: fetch Sel_nachl100 %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl100;
                    return -1;
                }
                if (sqlca.sqlcode == SQLNOTFOUND) break;
                EXEC SQL open Sel_bespo100;
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: open Sel_bespo100 %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl100;
                    return -1;
                }
                writeswitch = 0;
                for (;;)
                {
                    EXEC SQL fetch Sel_bespo100;
                    if (sqlca.sqlcode < 0 )
                    {
                        fst = 1;
                        sprintf(error_msg, " AaauftSel_nachl: fetch Sel_bespo100 %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                        EXEC SQL close Sel_nachl100;
                        EXEC SQL close Sel_bespo100;
                        return -1;
                    }
                    if (sqlca.sqlcode == SQLNOTFOUND) break;
                    EXEC SQL select status_akt  into :status from beskopf
                        where bestell_nr = :bestellnr
                        and filialnr = :les->VERTRIEBSZENTRUMNR;
                    if (sqlca.sqlcode < 0 )
                    {
                        fst = 1;
                        sprintf(error_msg, " AaauftSel_nachl: select status_akt %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                        EXEC SQL close Sel_nachl100;
                        EXEC SQL close Sel_bespo100;
                        return -1;
                    }
                    if (sqlca.sqlcode == SQLNOTFOUND) continue;
                    if (status[0] == 'A' || status[0] == 'E')
                    {
                        writeswitch = 1;
                        break;
                    }
                }
                if (writeswitch == 0)
                {
                    EXEC SQL insert into tmpoffbes
                        values (NACHLIEF_ZEIGER(les));
                }
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: insert into tmpoffbes %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl100;
                    EXEC SQL close Sel_bespo100;
                    return -1;
                }
            }
            EXEC SQL close Sel_nachl100;
            EXEC SQL close Sel_bespo100;
            EXEC SQL declare Sel_tmp100 scroll cursor with hold for
            select
                 KDAUFTRAGNR,
                 POSNR,
                 DATUM,
                 POSTYP,
                 IDFNR,
                 ARTIKEL_NR,
                 MENGE,
                 FILIALNR1,
                 FILIALNR2,
                 FILIALNR3,
                 STATUS,
                 MATCHCODE,
                 KZKDKLASSE,
                 KUNDENNR,
                 VERTRIEBSZENTRUMNR,
                 REGIONNR,
                 EINHEIT,
                 ARTIKEL_NAME,
                 KDAUFTRAGART,
                 BEMERKUNGEN,
                 BESTAND
            from tmpoffbes
            order by ARTIKEL_NR;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_tmp100 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL open Sel_tmp100;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_tmp100 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        if (a->STATUS == 101)
        {
            EXEC SQL drop table tmpoffbes;
            EXEC SQL create temp table tmpoffbes (
                 KDAUFTRAGNR INTEGER,
                 POSNR INTEGER,
                 DATUM INTEGER,
                 POSTYP SMALLINT,
                 IDFNR INTEGER,
                 ARTIKEL_NR INTEGER,
                 MENGE INTEGER,
                 FILIALNR1 SMALLINT,
                 FILIALNR2 SMALLINT,
                 FILIALNR3 SMALLINT,
                 STATUS SMALLINT,
                 MATCHCODE CHAR(12),
                 KZKDKLASSE CHAR(3),
                 KUNDENNR INTEGER,
                 VERTRIEBSZENTRUMNR SMALLINT,
                 REGIONNR SMALLINT,
                 EINHEIT CHAR(9),
                 ARTIKEL_NAME CHAR(30),
                 KDAUFTRAGART CHAR(2),
                 BEMERKUNGEN CHAR(240),
                 BESTAND INTEGER);
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: create temp table tmpoffbes %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL free dec_nachl101;
            strcpy(cSel, "select ");
            strcat(cSel, NACHLIEF_PLISTE);
            strcat(cSel, " from nachlieferpos, artikelzentral, outer artikellokal, outer kunde");
            strcat(cSel, " where nachlieferpos.idfnr >= ");
            sprintf(cBuf, "%d", vonidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.idfnr <= ");
            sprintf(cBuf, "%d", bisidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum <= ");
            sprintf(cBuf, "%d", a->DATUM);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum >= ");
            sprintf(cBuf, "%d", vondatum);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp >= ");
            sprintf(cBuf, "%d", vontyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp <= ");
            sprintf(cBuf, "%d", bistyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr >= ");
            sprintf(cBuf, "%d", vonpzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr <= ");
            sprintf(cBuf, "%d", bispzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.status < 2");
            if (a->KDAUFTRAGART[0] != ' ')
            {
                strcat(cSel, " and nachlieferpos.kdauftragart = ");
                sprintf(cBuf, "'%2.2s'", a->KDAUFTRAGART);
                strcat(cSel, cBuf);
            }
            strcat(cSel, " and kunde.kundennr = nachlieferpos.kundennr");
            strcat(cSel, " and kunde.vertriebszentrumnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikelzentral.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
//          strcat(cSel, " and artikellokal.bestand = 0");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and trunc( artikelzentral.etartschalter1/4096 ) - 2 ");
            strcat(cSel, " * trunc( artikelzentral.etartschalter1/(4096*2)) = 1");
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr >= ");
            sprintf(cBuf, "%d", vonVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr <= ");
            sprintf(cBuf, "%d", bisVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr in (");
            strcat(cSel, " select RegionArten.RegionTeilNr from RegionArten");
            strcat(cSel, " where  RegionArten.RegionNr = ");
            sprintf(cBuf, "%d", a->REGIONNR);
            strcat(cSel, cBuf);
            strcat(cSel, " and RegionArten.RegionenTyp = 1)");
//          strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
//          strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " order by nachlieferpos.datum, nachlieferpos.idfnr;");
            EXEC SQL prepare dec_nachl101 FROM :cSel;
            EXEC SQL declare Sel_nachl101 scroll cursor with hold for dec_nachl101;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_nachl101 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL open Sel_nachl101;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_nachl101 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL declare Sel_bespo101 scroll cursor with hold for
                select besposi.bestell_nr into :bestellnr from besposi
                where artikel_nr = :les->ARTIKEL_NR
                and filialnr = :les->VERTRIEBSZENTRUMNR ;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_bespo101 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            for (;;)
            {
                EXEC SQL fetch relative :a->FETCH_REL Sel_nachl101 into NACHLIEF_ZEIGER(les);
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: fetch Sel_nachl101 %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl101;
                    return -1;
                }
                if (sqlca.sqlcode == SQLNOTFOUND) break;
                EXEC SQL open Sel_bespo101;
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: open Sel_bespo101 %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl101;
                    return -1;
                }
                writeswitch = 0;
                for (;;)
                {
                    EXEC SQL fetch Sel_bespo101;
                    if (sqlca.sqlcode < 0 )
                    {
                        fst = 1;
                        sprintf(error_msg, " AaauftSel_nachl: fetch Sel_bespo101 %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                        EXEC SQL close Sel_nachl101;
                        EXEC SQL close Sel_bespo101;
                        return -1;
                    }
                    if (sqlca.sqlcode == SQLNOTFOUND) break;
                    EXEC SQL select status_akt  into :status from beskopf
                        where bestell_nr = :bestellnr
                        and filialnr = :les->VERTRIEBSZENTRUMNR;
                    if (sqlca.sqlcode < 0 )
                    {
                        fst = 1;
                        sprintf(error_msg, " AaauftSel_nachl: select status_akt %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                        EXEC SQL close Sel_nachl101;
                        EXEC SQL close Sel_bespo101;
                        return -1;
                    }
                    if (sqlca.sqlcode == SQLNOTFOUND) continue;
                    if (status[0] == 'A' || status[0] == 'E')
                    {
                        writeswitch = 1;
                        break;
                    }
                }
                if (writeswitch == 0)
                {
                    EXEC SQL insert into tmpoffbes
                        values (NACHLIEF_ZEIGER(les));
                }
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: insert into tmpoffbes %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl101;
                    EXEC SQL close Sel_bespo101;
                    return -1;
                }
            }
            EXEC SQL close Sel_nachl101;
            EXEC SQL close Sel_bespo101;
            EXEC SQL declare Sel_tmp101 scroll cursor with hold for
            select
                 KDAUFTRAGNR,
                 POSNR,
                 DATUM,
                 POSTYP,
                 IDFNR,
                 ARTIKEL_NR,
                 MENGE,
                 FILIALNR1,
                 FILIALNR2,
                 FILIALNR3,
                 STATUS,
                 MATCHCODE,
                 KZKDKLASSE,
                 KUNDENNR,
                 VERTRIEBSZENTRUMNR,
                 REGIONNR,
                 EINHEIT,
                 ARTIKEL_NAME,
                 KDAUFTRAGART,
                 BEMERKUNGEN,
                 BESTAND
            from tmpoffbes
            order by ARTIKEL_NR;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_tmp101 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL open Sel_tmp101;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_tmp101 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        if (a->STATUS == 110)
        {
            EXEC SQL drop table tmpoffbes;
            EXEC SQL create temp table tmpoffbes (
                 KDAUFTRAGNR INTEGER,
                 POSNR INTEGER,
                 DATUM INTEGER,
                 POSTYP SMALLINT,
                 IDFNR INTEGER,
                 ARTIKEL_NR INTEGER,
                 MENGE INTEGER,
                 FILIALNR1 SMALLINT,
                 FILIALNR2 SMALLINT,
                 FILIALNR3 SMALLINT,
                 STATUS SMALLINT,
                 MATCHCODE CHAR(12),
                 KZKDKLASSE CHAR(3),
                 KUNDENNR INTEGER,
                 VERTRIEBSZENTRUMNR SMALLINT,
                 REGIONNR SMALLINT,
                 EINHEIT CHAR(9),
                 ARTIKEL_NAME CHAR(30),
                 KDAUFTRAGART CHAR(2),
                 BEMERKUNGEN CHAR(240),
                 BESTAND INTEGER);
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: create temp table tmpoffbes %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL free dec_nachl110;
            strcpy(cSel, "select ");
            strcat(cSel, NACHLIEF_PLISTE);
            strcat(cSel, " from nachlieferpos, artikelzentral, artikellokal, outer kunde");
            strcat(cSel, " where nachlieferpos.idfnr >= ");
            sprintf(cBuf, "%d", vonidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.idfnr <= ");
            sprintf(cBuf, "%d", bisidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum <= ");
            sprintf(cBuf, "%d", a->DATUM);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum >= ");
            sprintf(cBuf, "%d", vondatum);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp >= ");
            sprintf(cBuf, "%d", vontyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp <= ");
            sprintf(cBuf, "%d", bistyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr >= ");
            sprintf(cBuf, "%d", vonpzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr <= ");
            sprintf(cBuf, "%d", bispzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.status < 2");
            if (a->KDAUFTRAGART[0] != ' ')
            {
                strcat(cSel, " and nachlieferpos.kdauftragart = ");
                sprintf(cBuf, "'%2.2s'", a->KDAUFTRAGART);
                strcat(cSel, cBuf);
            }
            strcat(cSel, " and kunde.kundennr = nachlieferpos.kundennr");
            strcat(cSel, " and kunde.vertriebszentrumnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikelzentral.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.bestand = 0");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and trunc( artikellokal.etartschalter1/16384 ) - 2 ");
            strcat(cSel, " * trunc( artikellokal.etartschalter1/(16384*2)) = 1");
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr >= ");
            sprintf(cBuf, "%d", vonVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr <= ");
            sprintf(cBuf, "%d", bisVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr in (");
            strcat(cSel, " select RegionArten.RegionTeilNr from RegionArten");
            strcat(cSel, " where RegionArten.RegionNr = ");
            sprintf(cBuf, "%d", a->REGIONNR);
            strcat(cSel, cBuf);
            strcat(cSel, " and RegionArten.RegionenTyp = 1)");
//          strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
//          strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " order by nachlieferpos.datum, nachlieferpos.idfnr;");
            EXEC SQL prepare dec_nachl110 FROM :cSel;
            EXEC SQL declare Sel_nachl110 scroll cursor with hold for dec_nachl110;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_nachl110 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL open Sel_nachl110;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_nachl110 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL declare Sel_bespo110 scroll cursor with hold for
                select besposi.bestell_nr into :bestellnr from besposi
                where artikel_nr = :les->ARTIKEL_NR
                and filialnr = :les->VERTRIEBSZENTRUMNR ;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_bespo110 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            for (;;)
            {
                EXEC SQL fetch relative :a->FETCH_REL Sel_nachl110 into NACHLIEF_ZEIGER(les);
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: fetch Sel_nachl110 %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl110;
                    return -1;
                }
                if (sqlca.sqlcode == SQLNOTFOUND) break;
                EXEC SQL open Sel_bespo110;
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: open Sel_bespo110 %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl110;
                    return -1;
                }
                writeswitch = 0;
                for (;;)
                {
                    EXEC SQL fetch Sel_bespo110;
                    if (sqlca.sqlcode < 0 )
                    {
                        fst = 1;
                        sprintf(error_msg, " AaauftSel_nachl: fetch Sel_bespo110 %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                        EXEC SQL close Sel_nachl110;
                        EXEC SQL close Sel_bespo110;
                        return -1;
                    }
                    if (sqlca.sqlcode == SQLNOTFOUND) break;
                    EXEC SQL select status_akt  into :status from beskopf
                        where bestell_nr = :bestellnr
                        and filialnr = :les->VERTRIEBSZENTRUMNR;
                    if (sqlca.sqlcode < 0 )
                    {
                        fst = 1;
                        sprintf(error_msg, " AaauftSel_nachl: select status_akt %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                        EXEC SQL close Sel_nachl110;
                        EXEC SQL close Sel_bespo110;
                        return -1;
                    }
                    if (sqlca.sqlcode == SQLNOTFOUND) continue;
                    if (status[0] == 'A' || status[0] == 'E')
                    {
                        writeswitch = 1;
                        break;
                    }
                }
                if (writeswitch == 0)
                {
                    EXEC SQL insert into tmpoffbes
                        values (NACHLIEF_ZEIGER(les));
                }
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: insert into tmpoffbes %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl110;
                    EXEC SQL close Sel_bespo110;
                    return -1;
                }
            }
            EXEC SQL close Sel_nachl110;
            EXEC SQL close Sel_bespo110;
            EXEC SQL declare Sel_tmp110 scroll cursor with hold for
            select
                 KDAUFTRAGNR,
                 POSNR,
                 DATUM,
                 POSTYP,
                 IDFNR,
                 ARTIKEL_NR,
                 MENGE,
                 FILIALNR1,
                 FILIALNR2,
                 FILIALNR3,
                 STATUS,
                 MATCHCODE,
                 KZKDKLASSE,
                 KUNDENNR,
                 VERTRIEBSZENTRUMNR,
                 VERTRIEBSZENTRUMNR,
                 EINHEIT,
                 ARTIKEL_NAME
                 KUNDENNR,
                 VERTRIEBSZENTRUMNR,
                 REGIONNR,
                 EINHEIT,
                 ARTIKEL_NAME,
                 KDAUFTRAGART,
                 BEMERKUNGEN,
                 BESTAND
            from tmpoffbes
            order by ARTIKEL_NR;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_tmp110 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL open Sel_tmp110;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_tmp110 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
        if (a->STATUS == 111)
        {
            EXEC SQL drop table tmpoffbes;
            EXEC SQL create temp table tmpoffbes (
                 KDAUFTRAGNR INTEGER,
                 POSNR INTEGER,
                 DATUM INTEGER,
                 POSTYP SMALLINT,
                 IDFNR INTEGER,
                 ARTIKEL_NR INTEGER,
                 MENGE INTEGER,
                 FILIALNR1 SMALLINT,
                 FILIALNR2 SMALLINT,
                 FILIALNR3 SMALLINT,
                 STATUS SMALLINT,
                 MATCHCODE CHAR(12),
                 KZKDKLASSE CHAR(3),
                 KUNDENNR INTEGER,
                 VERTRIEBSZENTRUMNR SMALLINT,
                 REGIONNR SMALLINT,
                 EINHEIT CHAR(9),
                 ARTIKEL_NAME CHAR(30),
                 KDAUFTRAGART CHAR(2),
                 BEMERKUNGEN CHAR(240),
                 BESTAND INTEGER);
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: create temp table tmpoffbes %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL free dec_nachl111;
            strcpy(cSel, "select ");
            strcat(cSel, NACHLIEF_PLISTE);
            strcat(cSel, " from nachlieferpos, artikelzentral, artikellokal, outer kunde");
            strcat(cSel, " where nachlieferpos.idfnr >= ");
            sprintf(cBuf, "%d", vonidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.idfnr <= ");
            sprintf(cBuf, "%d", bisidf);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum <= ");
            sprintf(cBuf, "%d", a->DATUM);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.datum >= ");
            sprintf(cBuf, "%d", vondatum);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp >= ");
            sprintf(cBuf, "%d", vontyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.postyp <= ");
            sprintf(cBuf, "%d", bistyp);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr >= ");
            sprintf(cBuf, "%d", vonpzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.artikel_nr <= ");
            sprintf(cBuf, "%d", bispzn);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.status < 2");
            if (a->KDAUFTRAGART[0] != ' ')
            {
                strcat(cSel, " and nachlieferpos.kdauftragart = ");
                sprintf(cBuf, "'%2.2s'", a->KDAUFTRAGART);
                strcat(cSel, cBuf);
            }
            strcat(cSel, " and kunde.kundennr = nachlieferpos.kundennr");
            strcat(cSel, " and kunde.vertriebszentrumnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikelzentral.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " and artikellokal.bestand = 0");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and trunc( artikelzentral.etartschalter1/4096 ) - 2 ");
            strcat(cSel, " * trunc( artikelzentral.etartschalter1/(4096*2)) = 1");
            strcat(cSel, " and trunc( artikellokal.etartschalter1/16384 ) - 2 ");
            strcat(cSel, " * trunc( artikellokal.etartschalter1/(16384*2)) = 1");
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr >= ");
            sprintf(cBuf, "%d", vonVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr <= ");
            sprintf(cBuf, "%d", bisVz);
            strcat(cSel, cBuf);
            strcat(cSel, " and nachlieferpos.vertriebszentrumnr in (");
            strcat(cSel, " select RegionArten.RegionTeilNr from RegionArten");
            strcat(cSel, " where  RegionArten.RegionNr = ");
            sprintf(cBuf, "%d", a->REGIONNR);
            strcat(cSel, cBuf);
            strcat(cSel, " and RegionArten.RegionenTyp = 1)");
            strcat(cSel, " and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr");
            strcat(cSel, " and artikellokal.artikel_nr = nachlieferpos.artikel_nr");
            strcat(cSel, " order by nachlieferpos.datum, nachlieferpos.idfnr;");
            EXEC SQL prepare dec_nachl111 FROM :cSel;
            EXEC SQL declare Sel_nachl111 scroll cursor with hold for dec_nachl111;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_nachl111 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL open Sel_nachl111;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_nachl111 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL declare Sel_bespo111 scroll cursor with hold for
                select besposi.bestell_nr into :bestellnr from besposi
                where artikel_nr = :les->ARTIKEL_NR
                and filialnr = :les->VERTRIEBSZENTRUMNR ;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_bespo111 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            for (;;)
            {
                EXEC SQL fetch relative :a->FETCH_REL Sel_nachl111 into NACHLIEF_ZEIGER(les);
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: fetch Sel_nachl111 %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl111;
                    return -1;
                }
                if (sqlca.sqlcode == SQLNOTFOUND) break;
                EXEC SQL open Sel_bespo111;
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: open Sel_bespo111 %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl111;
                    return -1;
                }
                writeswitch = 0;
                for (;;)
                {
                    EXEC SQL fetch Sel_bespo111;
                    if (sqlca.sqlcode < 0 )
                    {
                        fst = 1;
                        sprintf(error_msg, " AaauftSel_nachl: fetch Sel_bespo111 %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                        EXEC SQL close Sel_nachl111;
                        EXEC SQL close Sel_bespo111;
                        return -1;
                    }
                    if (sqlca.sqlcode == SQLNOTFOUND) break;
                    EXEC SQL select status_akt  into :status from beskopf
                        where bestell_nr = :bestellnr
                        and filialnr = :les->VERTRIEBSZENTRUMNR;
                    if (sqlca.sqlcode < 0 )
                    {
                        fst = 1;
                        sprintf(error_msg, " AaauftSel_nachl: select status_akt %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                        EXEC SQL close Sel_nachl111;
                        EXEC SQL close Sel_bespo111;
                        return -1;
                    }
                    if (sqlca.sqlcode == SQLNOTFOUND) continue;
                    if (status[0] == 'A' || status[0] == 'E')
                    {
                        writeswitch = 1;
                        break;
                    }
                }
                if (writeswitch == 0)
                {
                    EXEC SQL insert into tmpoffbes
                        values (NACHLIEF_ZEIGER(les));
                }
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSel_nachl: insert into tmpoffbes %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
                    EXEC SQL close Sel_nachl111;
                    EXEC SQL close Sel_bespo111;
                    return -1;
                }
            }
            EXEC SQL close Sel_nachl111;
            EXEC SQL close Sel_bespo111;
            EXEC SQL declare Sel_tmp111 scroll cursor with hold for
            select
                 KDAUFTRAGNR,
                 POSNR,
                 DATUM,
                 POSTYP,
                 IDFNR,
                 ARTIKEL_NR,
                 MENGE,
                 FILIALNR1,
                 FILIALNR2,
                 FILIALNR3,
                 STATUS,
                 MATCHCODE,
                 KZKDKLASSE,
                 KUNDENNR,
                 VERTRIEBSZENTRUMNR,
                 REGIONNR,
                 EINHEIT,
                 ARTIKEL_NAME,
                 KDAUFTRAGART,
                 BEMERKUNGEN,
                 BESTAND
            from tmpoffbes
            order by ARTIKEL_NR;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: declare Sel_tmp111 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL open Sel_tmp111;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachl: open Sel_tmp111 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        EXEC SQL drop table tmpoffbes;
        fst = 1;
        if (a->STATUS == 0)
        {
            EXEC SQL close Sel_nachl;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSel_nachl: close Sel_nachl %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
        if (a->STATUS == 1)
        {
            EXEC SQL close Sel_nachl1;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSel_nachl: close Sel_nachl1 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
        if (a->STATUS == 2)
        {
            EXEC SQL close Sel_nachl2;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSel_nachl: close Sel_nachl2 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
        if (a->STATUS == 3)
        {
            EXEC SQL close Sel_nachl3;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSel_nachl: close Sel_nachl3 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
        if (a->STATUS == 10)
        {
            EXEC SQL close Sel_nachl10;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSel_nachl: close Sel_nachl10 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
        if (a->STATUS == 11)
        {
            EXEC SQL close Sel_nachl11;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSel_nachl: close Sel_nachl11 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
        if (a->STATUS == 100)
        {
            EXEC SQL drop table tmpoffbes;
            EXEC SQL close Sel_tmp100;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSel_nachl: close Sel_tmp100 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
        if (a->STATUS == 101)
        {
            EXEC SQL drop table tmpoffbes;
            EXEC SQL close Sel_tmp101;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSel_nachl: close Sel_tmp101 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
        if (a->STATUS == 110)
        {
            EXEC SQL drop table tmpoffbes;
            EXEC SQL close Sel_tmp110;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSel_nachl: close Sel_tmp110 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
        if (a->STATUS == 111)
        {
            EXEC SQL drop table tmpoffbes;
            EXEC SQL close Sel_tmp111;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSel_nachl: close Sel_tmp111 %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            return 1;
        }
    }

    if (a->STATUS == 0)
    {
        EXEC SQL fetch relative :a->FETCH_REL Sel_nachl into NACHLIEF_ZEIGER(a);
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachl: fetch Sel_nachl %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_nachl;
            return -1;
        }
    }
    else if (a->STATUS == 1)
    {
        EXEC SQL fetch relative :a->FETCH_REL Sel_nachl1 into NACHLIEF_ZEIGER(a);
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachl: fetch Sel_nachl1 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_nachl1;
            return -1;
        }
    }
    else if (a->STATUS == 2)
    {
        EXEC SQL fetch relative :a->FETCH_REL Sel_nachl2 into NACHLIEF_ZEIGER(a);
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachl: fetch Sel_nachl2 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_nachl2;
            return -1;
        }
    }
    else if (a->STATUS == 3)
    {
        EXEC SQL fetch relative :a->FETCH_REL Sel_nachl3 into NACHLIEF_ZEIGER(a);
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachl: fetch Sel_nachl3 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_nachl3;
            return -1;
        }
    }
    else if (a->STATUS == 10)
    {
        EXEC SQL fetch relative :a->FETCH_REL Sel_nachl10 into NACHLIEF_ZEIGER(a);
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachl: fetch Sel_nachl10 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_nachl10;
            return -1;
        }
    }
    else if (a->STATUS == 11)
    {
        EXEC SQL fetch relative :a->FETCH_REL Sel_nachl11 into NACHLIEF_ZEIGER(a);
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachl: fetch Sel_nachl11 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_nachl11;
            return -1;
        }
    }
    else if (a->STATUS == 100)
    {
        EXEC SQL fetch relative :a->FETCH_REL Sel_tmp100 into NACHLIEF_ZEIGER(a);
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachl: fetch Sel_tmp100 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_tmp100;
            return -1;
        }
    }
    else if (a->STATUS == 101)
    {
        EXEC SQL fetch relative :a->FETCH_REL Sel_tmp101 into NACHLIEF_ZEIGER(a);
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachl: fetch Sel_tmp101 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_tmp101;
            return -1;
        }
    }
    else if (a->STATUS == 110)
    {
        EXEC SQL fetch relative :a->FETCH_REL Sel_tmp110 into NACHLIEF_ZEIGER(a);
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachl: fetch Sel_tmp110 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_tmp110;
            return -1;
        }
    }
    else if (a->STATUS == 111)
    {
        EXEC SQL fetch relative :a->FETCH_REL Sel_tmp111 into NACHLIEF_ZEIGER(a);
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachl: fetch Sel_tmp111 %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_tmp111;
            return -1;
        }
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

int AaauftLoe_nachl(struct NACHLIEF* d, char* error_msg)
{
    static int fst = 1;

    long lDiff;

    EXEC SQL BEGIN DECLARE SECTION;
    struct NACHLIEF* a;
    long lMenge;
    long lBest;
    long lReserv;
    short sFili;
    long lArt;
    short sStatus;
    char cNachlTyp[2];
    long lActDatum;
    long acttime;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* nur beim ersten mal deklarieren */
    {
        fst = 0;
        strcpy(str, "select menge, vertriebszentrumnr, artikel_nr, status from nachlieferpos ");
        strcat(str, " where kdauftragnr = ? ");
        strcat(str, " and posnr = ? ");
        strcat(str, " and datum = ? ");
        strcat(str, " and postyp = ? ");
        strcat(str, " for update");

        EXEC SQL PREPARE sel_nachlloe FROM :str;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftLoe_nachl:PREPARE sel_nachlloe %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        exec sql declare CNachlloe Cursor with hold for sel_nachlloe;
    }

    exec sql open CNachlloe
        using
        :a->KDAUFTRAGNR,
        :a->POSNR,
        :a->DATUM,
        :a->POSTYP;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftLoe_nachl:open CNachlloe %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    exec sql fetch CNachlloe into :lMenge, :sFili, :lArt, :sStatus;
    if (sqlca.sqlcode == 100) return 0;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftLoe_nachl:fetch CNachlloe %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    if (sStatus == 1)
    {
        EXEC SQL update nachlieferpos
        set status = 2
        where current of CNachlloe;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftLoe_nachl:update Status CNachlloe %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }
    else
    {
        EXEC SQL delete from nachlieferpos
        where current of CNachlloe;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftLoe_nachl:delete CNachlloe %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }
    if (!strncmp(cCountry, "DE", 2))
    {
        EXEC SQL select nachliefertyp into :cNachlTyp
            from kunde
            where vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
            and kundennr = :a->KUNDENNR;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftLoe_nachl:select Kunde %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        if (cNachlTyp[0] < '4' || cNachlTyp[0] > '7')
            return 0;
        lActDatum = AllgGetDate();
        if (a->DATUM < lActDatum)
        {
            EXEC SQL insert into clearwafo
                (orderdate
                ,kdauftragnr
                ,articleno
                ,menge
                ,solutiondate
                ,posnr
                ,vertriebszentrumnr
                )
                values
                (:a->DATUM
                ,:a->KDAUFTRAGNR
                ,:lArt
                ,:lMenge
                ,:lActDatum
                ,:a->POSNR
                ,:sFili
                );
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftLoe_nachl:insert clearwafo %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

        }
        else
        {
            time_t long_time;
            time( &long_time );
            acttime = long_time;
            EXEC SQL insert into artikelkonto
                (FILIALNR
                ,ARTIKEL_NR
                ,BEWEGUNGSART
                ,MENGE
                ,BELEGNR
                ,UID
                ,IDFNR
                ,MENGENEU
                ,ZEITUNIX
                ,BEWEGUNGSCHLUESSEL
                )
                values
                (:sFili
                ,:lArt
                ,'S'
                ,:lMenge
                ,:a->KDAUFTRAGNR
                ,'0'
                ,:a->KUNDENNR
                ,'0'
                ,:acttime
                ,'3000020'
                );
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftLoe_nachl:insert artikelkonto %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
        }

    }
    return 0;
}

int AaauftUpd_nachl(struct NACHLIEF* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct NACHLIEF* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    EXEC SQL update nachlieferpos
    set menge = :a->MENGE
    where   kdauftragnr = :a->KDAUFTRAGNR
    and     posnr       = :a->POSNR
    and     datum       = :a->DATUM;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftUpd_nachl update %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    return 0;
}

int AaauftIns_nachl(struct NACHLIEF* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct NACHLIEF* a;
    struct ARTAESEL   f;
    EXEC SQL END DECLARE SECTION;

    a = d;
    f.ARTIKEL_NR = a->ARTIKEL_NR;
    AatartSel_Preferred(&f, error_msg);

    EXEC SQL update nachlieferpos
    set menge = :a->MENGE,
        preisekaponetto = 0,
        preisekapo = 0,
        preisvkapo = 0,
        preisagp = 0,
        artikel_nr = :a->ARTIKEL_NR,
        code_type = :f.CODE_TYPE,
        article_code = :f.ARTICLE_CODE
    where   kdauftragnr = :a->KDAUFTRAGNR
    and     posnr       = :a->POSNR
    and     datum       = :a->DATUM;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftIns_nachl update %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    return 0;
}

/*** CHECK-TIME-TO-NULL ******************************************************/

static long CheckTimeToNull( long lTime )
{
    return lTime < 0 || lTime > 2400 ? 0 : lTime;
}

/*** GET-TIME-DIFF-IN-MIN ****************************************************/

static int GetTimeDiffInMin( long lTimeHigh, long lTimeLow )
{
    int iMinHigh;
    int iMinLow;

    iMinHigh = ( lTimeHigh % 100 ) + ( ( ( lTimeHigh / 100 ) % 100 ) * 60 );
    iMinLow  = ( lTimeLow % 100 ) + ( ( ( lTimeLow / 100 ) % 100 ) * 60 );

    return ( iMinHigh - iMinLow );
}

int AaauftIns_auft_ereig(struct AUFEREIG* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct AUFEREIG* a;
    long lDate, lTime;
    EXEC SQL END DECLARE SECTION;

    a = d;
    lDate = ppGGetDate();
    lTime = ppGGetTime()*1000;

    EXEC SQL begin work;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftIns_auft_ereig begin work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    EXEC SQL insert into kdauftragereignis (
        KDAUFTRAGNR,
        DATUM,
        ZEIT,
        EREIGNISART,
        PERSONALNR,
        GERAETNAME,
        FILIALNR)
    values (
        :a->KDAUFTRAGNR,
        :lDate,
        :lTime,
        :a->EREIGNISART,
        :a->PERSONALNR,
        :a->GERAETNAME,
        :FilialNr);
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftIns_auft_ereig insert %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    EXEC SQL commit work;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftIns_auft_ereig commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    return 0;
}

int AaauftSel_nachlart(struct NACHLART* d, char* error_msg)
{
    static int fst = 1;
    static int FREMDSPRACHE_ALT = 2;

    EXEC SQL BEGIN DECLARE SECTION;
    struct NACHLART* a;
    long lquota;
    long lkumqty;
    long lrest;
    char cAufart[3];
    static short orgfiliale;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        orgfiliale = a->FILIALNR1;
        cAufart[0] = a->KDAUFTRAGART[0];
        cAufart[1] = a->KDAUFTRAGART[1];
        cAufart[2] = '\0';
        if (a->KDAUFTRAGART[0] == ' ')
        {
            a->KDAUFTRAGART[0] = 'N';
            a->KDAUFTRAGART[1] = 'O';
        }
        if (FREMDSPRACHE != FREMDSPRACHE_ALT)
        {
            FREMDSPRACHE_ALT = FREMDSPRACHE;
            EXEC SQL free dec_quota;
            EXEC SQL free Sel_quota;
            EXEC SQL free dec_nachlart;
            EXEC SQL free Sel_nachlart;
            if (FREMDSPRACHE)
            {
                strcpy(str, "select ");
                strcat(str, "NACHLIEFERPOS.KDAUFTRAGNR, ");
                strcat(str, "NACHLIEFERPOS.POSNR, ");
                strcat(str, "NACHLIEFERPOS.DATUM, ");
                strcat(str, "NACHLIEFERPOS.POSTYP, ");
                strcat(str, "NACHLIEFERPOS.IDFNR, ");
                strcat(str, "NACHLIEFERPOS.ARTIKEL_NR, ");
                strcat(str, "NACHLIEFERPOS.MENGE, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR1, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR2, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR3, ");
                strcat(str, "NACHLIEFERPOS.STATUS, ");
                strcat(str, "nvl(c.DARREICHFORM, z.DARREICHFORM), ");
                strcat(str, "nvl(c.EINHEIT, z.EINHEIT), ");
                strcat(str, "nvl(c.ARTIKEL_NAME, z.ARTIKEL_NAME), ");
                strcat(str, "ARTIKELLOKAL.BESTAND, ");
                strcat(str, "NACHLIEFERPOS.VERTRIEBSZENTRUMNR, ");
                strcat(str, "NACHLIEFERPOS.PREISEKAPONETTO, ");
                strcat(str, "NACHLIEFERPOS.KDAUFTRAGART, ");
                strcat(str, "NACHLIEFERPOS.CODE_TYPE, ");
                strcat(str, "NACHLIEFERPOS.ARTICLE_CODE, ");
                strcat(str, "NACHLIEFERPOS.DISCOUNTVALUEPCT, ");
                strcat(str, "NACHLIEFERPOS.MENGEBESTELLT, ");
                strcat(str, "NACHLIEFERPOS.PREIS_TYP ");
                strcat(str, "from ");
                strcat(str, "nachlieferpos, ");
                strcat(str, "artikelzentral z, ");
                strcat(str, "artikellokal, outer ");
                strcat(str, ARTIKELZENTRAL_SPRACHE);
                strcat(str, " c ");
                strcat(str, "where ");
                strcat(str, "idfnr = ? ");
                strcat(str, "and postyp = 3 ");
                strcat(str, "and (nachlieferpos.kdauftragart = ? ");
                strcat(str, "or nachlieferpos.kdauftragart = ? ) ");
                strcat(str, "and artikellokal.bestand != 0 ");
                strcat(str, "and artikellokal.artikelaktiv = '1' ");
                strcat(str, "and z.artikel_nr = nachlieferpos.artikel_nr ");
                strcat(str, "and c.artikel_nr = nachlieferpos.artikel_nr ");
                strcat(str, "and artikellokal.artikel_nr = nachlieferpos.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
                strcat(str, "and nachlieferpos.vertriebszentrumnr = ? ");
                strcat(str, "and nachlieferpos.status <= ? ");
                strcat(str, "union ");
                strcat(str, "select ");
                strcat(str, "NACHLIEFERPOS.KDAUFTRAGNR, ");
                strcat(str, "NACHLIEFERPOS.POSNR, ");
                strcat(str, "NACHLIEFERPOS.DATUM, ");
                strcat(str, "NACHLIEFERPOS.POSTYP, ");
                strcat(str, "NACHLIEFERPOS.IDFNR, ");
                strcat(str, "NACHLIEFERPOS.ARTIKEL_NR, ");
                strcat(str, "NACHLIEFERPOS.MENGE, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR1, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR2, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR3, ");
                strcat(str, "NACHLIEFERPOS.STATUS, ");
                strcat(str, "nvl(c.DARREICHFORM, z.DARREICHFORM), ");
                strcat(str, "nvl(c.EINHEIT, z.EINHEIT), ");
                strcat(str, "nvl(c.ARTIKEL_NAME, z.ARTIKEL_NAME), ");
                strcat(str, "ARTIKELLOKAL.BESTAND, ");
                strcat(str, "NACHLIEFERPOS.VERTRIEBSZENTRUMNR, ");
                strcat(str, "NACHLIEFERPOS.PREISEKAPONETTO, ");
                strcat(str, "NACHLIEFERPOS.KDAUFTRAGART, ");
                strcat(str, "NACHLIEFERPOS.CODE_TYPE, ");
                strcat(str, "NACHLIEFERPOS.ARTICLE_CODE, ");
                strcat(str, "NACHLIEFERPOS.DISCOUNTVALUEPCT, ");
                strcat(str, "NACHLIEFERPOS.MENGEBESTELLT, ");
                strcat(str, "NACHLIEFERPOS.PREIS_TYP ");
                strcat(str, "from ");
                strcat(str, "nachlieferpos, ");
                strcat(str, "artikelzentral z, ");
                strcat(str, "artikellokal, outer ");
                strcat(str, ARTIKELZENTRAL_SPRACHE);
                strcat(str, " c ");
                strcat(str, "where ");
                strcat(str, "idfnr = ? ");
                strcat(str, "and postyp = 5 ");
                strcat(str, "and (nachlieferpos.kdauftragart = ? ");
                strcat(str, "or nachlieferpos.kdauftragart = ? ) ");
                strcat(str, "and z.artikel_nr = nachlieferpos.artikel_nr ");
                strcat(str, "and c.artikel_nr = nachlieferpos.artikel_nr ");
                strcat(str, "and artikellokal.artikel_nr = nachlieferpos.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
                strcat(str, "and nachlieferpos.vertriebszentrumnr = ? ");
                strcat(str, "and nachlieferpos.status <= ? ");
                strcat(str, "order by 6, 4 desc");
            }
            else
            {
                strcpy(str, "select ");
                strcat(str, "NACHLIEFERPOS.KDAUFTRAGNR, ");
                strcat(str, "NACHLIEFERPOS.POSNR, ");
                strcat(str, "NACHLIEFERPOS.DATUM, ");
                strcat(str, "NACHLIEFERPOS.POSTYP, ");
                strcat(str, "NACHLIEFERPOS.IDFNR, ");
                strcat(str, "NACHLIEFERPOS.ARTIKEL_NR, ");
                strcat(str, "NACHLIEFERPOS.MENGE, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR1, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR2, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR3, ");
                strcat(str, "NACHLIEFERPOS.STATUS, ");
                strcat(str, "ARTIKELZENTRAL.DARREICHFORM, ");
                strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
                strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
                strcat(str, "ARTIKELLOKAL.BESTAND, ");
                strcat(str, "NACHLIEFERPOS.VERTRIEBSZENTRUMNR, ");
                strcat(str, "NACHLIEFERPOS.PREISEKAPONETTO, ");
                strcat(str, "NACHLIEFERPOS.KDAUFTRAGART, ");
                strcat(str, "NACHLIEFERPOS.CODE_TYPE, ");
                strcat(str, "NACHLIEFERPOS.ARTICLE_CODE, ");
                strcat(str, "NACHLIEFERPOS.DISCOUNTVALUEPCT, ");
                strcat(str, "NACHLIEFERPOS.MENGEBESTELLT, ");
                strcat(str, "NACHLIEFERPOS.PREIS_TYP ");
                strcat(str, "from ");
                strcat(str, "nachlieferpos, ");
                strcat(str, "artikelzentral, ");
                strcat(str, "artikellokal ");
                strcat(str, "where ");
                strcat(str, "idfnr = ? ");
                strcat(str, "and postyp = 3 ");
                strcat(str, "and (nachlieferpos.kdauftragart = ? ");
                strcat(str, "or nachlieferpos.kdauftragart = ? ) ");
                strcat(str, "and artikellokal.bestand != 0 ");
                strcat(str, "and artikellokal.artikelaktiv = '1' ");
                strcat(str, "and artikelzentral.artikel_nr = nachlieferpos.artikel_nr ");
                strcat(str, "and artikellokal.artikel_nr = nachlieferpos.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
                strcat(str, "and nachlieferpos.vertriebszentrumnr = ? ");
                strcat(str, "and nachlieferpos.status <= ? ");
                strcat(str, "union ");
                strcat(str, "select ");
                strcat(str, "NACHLIEFERPOS.KDAUFTRAGNR, ");
                strcat(str, "NACHLIEFERPOS.POSNR, ");
                strcat(str, "NACHLIEFERPOS.DATUM, ");
                strcat(str, "NACHLIEFERPOS.POSTYP, ");
                strcat(str, "NACHLIEFERPOS.IDFNR, ");
                strcat(str, "NACHLIEFERPOS.ARTIKEL_NR, ");
                strcat(str, "NACHLIEFERPOS.MENGE, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR1, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR2, ");
                strcat(str, "NACHLIEFERPOS.FILIALNR3, ");
                strcat(str, "NACHLIEFERPOS.STATUS, ");
                strcat(str, "ARTIKELZENTRAL.DARREICHFORM, ");
                strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
                strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
                strcat(str, "ARTIKELLOKAL.BESTAND, ");
                strcat(str, "NACHLIEFERPOS.VERTRIEBSZENTRUMNR, ");
                strcat(str, "NACHLIEFERPOS.PREISEKAPONETTO, ");
                strcat(str, "NACHLIEFERPOS.KDAUFTRAGART, ");
                strcat(str, "NACHLIEFERPOS.CODE_TYPE, ");
                strcat(str, "NACHLIEFERPOS.ARTICLE_CODE, ");
                strcat(str, "NACHLIEFERPOS.DISCOUNTVALUEPCT, ");
                strcat(str, "NACHLIEFERPOS.MENGEBESTELLT, ");
                strcat(str, "NACHLIEFERPOS.PREIS_TYP ");
                strcat(str, "from ");
                strcat(str, "nachlieferpos, ");
                strcat(str, "artikelzentral, ");
                strcat(str, "artikellokal ");
                strcat(str, "where ");
                strcat(str, "idfnr = ? ");
                strcat(str, "and postyp = 5 ");
                strcat(str, "and (nachlieferpos.kdauftragart = ? ");
                strcat(str, "or nachlieferpos.kdauftragart = ? ) ");
                strcat(str, "and artikelzentral.artikel_nr = nachlieferpos.artikel_nr ");
                strcat(str, "and artikellokal.artikel_nr = nachlieferpos.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
                strcat(str, "and nachlieferpos.vertriebszentrumnr = ? ");
                strcat(str, "and nachlieferpos.status <= ? ");
                strcat(str, "order by 6, 4 desc");
            }
            EXEC SQL PREPARE dec_nachlart FROM :str;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachlart: declare dec_nachlart %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL declare Sel_nachlart scroll cursor with hold for dec_nachlart;

            strcpy(str, "select ");
            strcat(str, "QUOTA, ");
            strcat(str, "KUMQTY ");
            strcat(str, "from ");
            strcat(str, "articlequota ");
            strcat(str, "where ");
            strcat(str, "branchno = ? ");
            strcat(str, "and articleno = ? ");
            strcat(str, "and customerno = ? ");
            strcat(str, "union ");
            strcat(str, "select ");
            strcat(str, "QUOTA, ");
            strcat(str, "KUMQTY ");
            strcat(str, "from ");
            strcat(str, "articlequota ");
            strcat(str, "where ");
            strcat(str, "branchno = ? ");
            strcat(str, "and articleno = ? ");
            strcat(str, "and pharmacygroupid in ");
            strcat(str, "(select pharmacygroupid ");
            strcat(str, "from customerpharmacygr ");
            strcat(str, "where ");
            strcat(str, "branchno = ? ");
            strcat(str, "and customerno = ? )");
            EXEC SQL PREPARE dec_quota FROM :str;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachlart: declare dec_quota %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL declare Sel_quota scroll cursor with hold for dec_quota;
        }

        EXEC SQL open Sel_nachlart using
            :a->IDFNR, :a->KDAUFTRAGART, :cAufart, :FilialNr, :a->VERTRIEBSZENTRUMNR, :a->STATUS,
            :a->IDFNR, :a->KDAUFTRAGART, :cAufart, :FilialNr, :a->VERTRIEBSZENTRUMNR, :a->STATUS;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachlart: open Sel_nachlart %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
    /*       return -1; */
            WriteLogInfo(error_msg, -1 , -1);
            return 1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Sel_nachlart;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_nachlart: close Sel_nachlart %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    for (;;)
    {
        EXEC SQL fetch relative :a->FETCH_REL Sel_nachlart into NACHLART_ZEIGER(a);
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachlart: fetch Sel_nachlart %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_nachlart;
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            return 1;
        }
        if (a->POSTYP == 5) break;       /* schon in pvhx01 abgefragt */
        EXEC SQL open Sel_quota using
            :orgfiliale,
            :a->ARTIKEL_NR,
            :a->IDFNR,
            :orgfiliale,
            :a->ARTIKEL_NR,
            :orgfiliale,
            :a->IDFNR;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachlart: open Sel_quota %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
    /*       return -1; */
            WriteLogInfo(error_msg, -1 , -1);
            return 1;
        }
        EXEC SQL fetch Sel_quota into :lquota, :lkumqty;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_nachlart: fetch Sel_quota %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Sel_quota;
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            break;
        }
        lrest = lquota-lkumqty;
        if (lrest > 0)
        {
            if (a->BESTAND > lrest) a->BESTAND = lrest;
            break;
        }
    }

    return 0;
}

int AaauftSel_frt(struct AUFPOSBUCH* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct AUFPOSBUCH* a;
    int etposschalter1;
    int etposschalter2;
    int etartklasse1;
    int etartschalter2;
    short geraetetyp;
    short sTAXLEVEL;
    EXEC SQL END DECLARE SECTION;
    static int FREMDSPRACHE_ALT = 2;

    a = d;
    datum = a->STATUS;      /* wird zur Uebergabe des Datums missbraucht */

    if (datum == 0)
    {
        EXEC SQL select
            ARTIKEL_NR,
            ETPOSSCHALTER1,
            ETPOSSCHALTER2,
            MENGEBESTELLT,
            MENGENATRA,
            BEMERKUNGEN,
            MENGEBESTAETIGT,
            LAGERBEREICHNR,
            ETARTSCHALTER2,
            geraettyp,
            SENDESTATUS
        into
            :a->ARTIKEL_NR,
            :etposschalter1,
            :etposschalter2,
            :a->MENGEBESTELLT,
            :a->MENGENATRA,
            :a->BEMERKUNG,
            :a->MENGEABGEBUCHT,
            :a->LAGERBEREICHNR,
            :a->ETARTSCHALTER2,
            :geraetetyp,
            :a->SENDESTATUS
        from kdauftragpos
        where kdauftragnr = :a->KDAUFTRAGNR
          and posnr = :a->POSNR  ;
    }
    else
    {
        EXEC SQL select
            ARTIKEL_NR,
            ETPOSSCHALTER1,
            ETPOSSCHALTER2,
            MENGEBESTELLT,
            MENGENATRA,
            BEMERKUNGEN,
            MENGEBESTAETIGT,
            LAGERBEREICHNR,
            ETARTSCHALTER2,
            geraettyp,
            SENDESTATUS
        into
            :a->ARTIKEL_NR,
            :etposschalter1,
            :etposschalter2,
            :a->MENGEBESTELLT,
            :a->MENGENATRA,
            :a->BEMERKUNG,
            :a->MENGEABGEBUCHT,
            :a->LAGERBEREICHNR,
            :a->ETARTSCHALTER2,
            :geraetetyp,
            :a->SENDESTATUS
        from akdauftragpos
        where datum = :datum
          and kdauftragnr = :a->KDAUFTRAGNR
          and posnr = :a->POSNR  ;
    }

    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSel_frt: select pos %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    if (AllgBitleisteN(etposschalter2, 0)) a->STATUS = ITEM_STAT_DISPO;
    else if (AllgBitleisteN(etposschalter2, 1)) a->STATUS = ITEM_STAT_ZUGESAGT;
    else if (AllgBitleisteN(etposschalter2, 2)) a->STATUS = ITEM_STAT_NACHLIEFERN;
    else a->STATUS = ITEM_STAT_NORMAL;

    /* 1.Position */
    a->POSART[0] = '*';
    if ( geraetetyp == DVC_VIDEO_WORKSTATION ||
         geraetetyp == DVC_VIDEO_TERMINAL    ||
         geraetetyp == DVC_VIDEO )
    {
        a->POSART[0] = '0';
    }
    if ( geraetetyp == DVC_DCT_PARALLEL        ||
         geraetetyp == DVC_DCT )
    {
        a->POSART[0] = '1';
    }
    if (   (geraetetyp != DVC_DCT_SERIAL && AllgBitleisteN(etposschalter1, 1))
        || AllgBitleisteN(etposschalter1, 10) )
    {
        a->POSART[0] = '2';
    }
    if (AllgBitleisteN(etposschalter1, 2))
    {
        a->POSART[0] = '3';
    }
    if (geraetetyp == DVC_DCT_SERIAL && !AllgBitleisteN(etposschalter1, 1))
    {
        a->POSART[0] = '5';
    }
    if (geraetetyp == DVC_DCT_SERIAL && AllgBitleisteN(etposschalter1, 1))
    {
        a->POSART[0] = '6';
    }

    /* 2.Position */
    AllgEntfSpaces(a->BEMERKUNG);
    if (AllgBitleisteN(etposschalter1, 9))
    {
        a->POSART[1] = '2';
    }
    else if (AllgBitleisteN(etposschalter1, 1) || (AllgBitleisteN(etposschalter1, 10) && !AllgBitleisteN(etposschalter1, 9)))
    {
        a->POSART[1] = '3';
    }
    else if (strlen(a->BEMERKUNG) != 0)
    {
        a->POSART[1] = '4';
    }
    else
    {
        a->POSART[1] = '0';
    }
    a->POSART[2] = '\0';

    a->DARREICHFORM[0] = '\0';
    a->EINHEIT[0] = '\0';
    a->ARTIKEL_NAME[0] = '\0';

    if (a->ARTIKEL_NR != 0)
    {
        if (FREMDSPRACHE != FREMDSPRACHE_ALT)
        {
            FREMDSPRACHE_ALT = FREMDSPRACHE;
            EXEC SQL free sel_arttxt;
            if (FREMDSPRACHE)
            {
                strcpy(str, "select ");
                strcat(str, "nvl(c.DARREICHFORM, z.DARREICHFORM), ");
                strcat(str, "nvl(c.EINHEIT, z.EINHEIT), ");
                strcat(str, "nvl(c.ARTIKEL_NAME, z.ARTIKEL_NAME), ");
                strcat(str, "etartklasse1, ");
                strcat(str, "(ARTIKELZENTRAL.ETARTSCHALTER2 + ARTIKELLOKAL.ETARTSCHALTER2) ");
                strcat(str, "into ");
                strcat(str, "?, ?, ?, ?, ? ");
                strcat(str, "from ");
                strcat(str, "artikelzentral z, ");
                strcat(str, "outer artikellokal, outer ");
                strcat(str, ARTIKELZENTRAL_SPRACHE);
                strcat(str, " c ");
                strcat(str, "where z.artikel_nr = ? ");
                strcat(str, "and c.artikel_nr = z.artikel_nr ");
                strcat(str, "and artikellokal.artikel_nr = z.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
            }
            else
            {
                strcpy(str, "select ");
                strcat(str, "DARREICHFORM, ");
                strcat(str, "EINHEIT, ");
                strcat(str, "ARTIKEL_NAME, ");
                strcat(str, "etartklasse1, ");
                strcat(str, "(ARTIKELZENTRAL.ETARTSCHALTER2 + ARTIKELLOKAL.ETARTSCHALTER2) ");
                strcat(str, "into ");
                strcat(str, "?, ?, ?, ?, ? ");
                strcat(str, "from artikelzentral, ");
                strcat(str, "outer artikellokal ");
                strcat(str, "where ");
                strcat(str, "where artikelzentral.artikel_nr = ? ");
                strcat(str, "and artikellokal.artikel_nr = artikelzentral.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
            }
            EXEC SQL PREPARE sel_arttxt FROM :str;
            if (sqlca.sqlcode < 0 )
            {
                sprintf(error_msg, " AaauftSel_frt: declare sel_arttxt %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                EXEC SQL close Sel_alt_pos;
                return -1;
            }
        }
        EXEC SQL EXECUTE sel_arttxt USING
            :a->DARREICHFORM,
            :a->EINHEIT,
            :a->ARTIKEL_NAME,
            :etartklasse1,
            :etartschalter2,
            :a->ARTIKEL_NR,
            :FilialNr;

        sTAXLEVEL = 0; // dummy against C4701
    }

    else if (datum == 0)
    {
        EXEC SQL select
            DARREICHFORM,
            PREISEKAPO,
            PREISEKGROSSO,
            RABATTFESTDM,
            RABATTFEST,
            RABATTFAEHIG,
            EINHEIT,
            BEZEICHNUNG,
            etartklasse1,
            etartschalter2,
            TAXLEVEL
        into
            :a->DARREICHFORM,
            :a->PREISEKAPO,
            :a->PREISEKGROSSO,
            :a->RABATTFESTDM,
            :a->RABATTFEST,
            :a->RABATTFAEHIG,
            :a->EINHEIT,
            :a->ARTIKEL_NAME,
            :etartklasse1,
            :etartschalter2,
            :sTAXLEVEL
        from dispoartikel
        where kdauftragnr = :a->KDAUFTRAGNR
          and posnr = :a->POSNR;
    }
    else
    {
        EXEC SQL select
            DARREICHFORM,
            PREISEKAPO,
            PREISEKGROSSO,
            RABATTFESTDM,
            RABATTFEST,
            RABATTFAEHIG,
            EINHEIT,
            BEZEICHNUNG,
            etartklasse1,
            etartschalter2,
            TAXLEVEL
        into
            :a->DARREICHFORM,
            :a->PREISEKAPO,
            :a->PREISEKGROSSO,
            :a->RABATTFESTDM,
            :a->RABATTFEST,
            :a->RABATTFAEHIG,
            :a->EINHEIT,
            :a->ARTIKEL_NAME,
            :etartklasse1,
            :etartschalter2,
            :sTAXLEVEL
        from adispoartikel
        where datum = :datum
          and kdauftragnr = :a->KDAUFTRAGNR
          and posnr = :a->POSNR;
    }
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSel_frt: select artikel %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    sprintf(a->MWSTSCHLUESSEL, "%d", sTAXLEVEL);

    if (AllgBitleisteN(etartklasse1, 5))
            a->TAXPFLICHTIG[0] = '1';
    else    a->TAXPFLICHTIG[0] = '0';

    return 0;
}

/*** AAAUFT-SEL-END-KOPF *****************************************************/

int AaauftSel_end_kopf( struct AUFENDKOPF* a, char* error_msg )
{
    UNUSED(a);
    UNUSED(error_msg);
    /* referenced table koeinheit not in use anymore */
    return 1;
}

/*** AAAUFT-SEL-END-POS ******************************************************/

int AaauftSel_end_pos( struct AUFENDPOS* a, char* error_msg )
{
    exec sql begin declare section;
    struct AUFENDPOS* d;
    char szpBlockvon[3];
    char szpBlockbis[3];
    exec sql end declare section;
    static int fst = 1;
    static int FREMDSPRACHE_ALT = 2;
    char* fun = "AaauftSel_end_kopf";

    d = a;

    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        sprintf( szpBlockvon, "%2.2s", d->LAGERFACHNR );
        sprintf( szpBlockbis, "%2.2s", d->LAGERFACHNR + 2 );
        /* Lagerort bs2 ist 7stellig feld aber 8stellig */
        /* lagerfachnr wird rechtsbuendig geschrieben   */

        if (FREMDSPRACHE != FREMDSPRACHE_ALT)
        {
            FREMDSPRACHE_ALT = FREMDSPRACHE;
            EXEC SQL free dec_posart;
            EXEC SQL free Sel_posart;
            if (FREMDSPRACHE)
            {
                strcpy(str, "select ");
                strcat(str, "z.NORMPACKUNG, ");
                strcat(str, "nvl(c.EINHEIT, z.EINHEIT), ");
                strcat(str, "nvl(c.ARTIKEL_NAME, z.ARTIKEL_NAME), ");
                strcat(str, "KDAUFTRAGPOS.KDAUFTRAGNR, ");
                strcat(str, "KDAUFTRAGPOS.ARTIKEL_NR, ");
                strcat(str, "KDAUFTRAGPOS.MENGEBESTELLT, ");
                strcat(str, "KDAUFTRAGPOS.MENGEGELIEFERT, ");
                strcat(str, "KDAUFTRAGPOS.KOBEHAELTNR, ");
                strcat(str, "KDAUFTRAGPOS.LAGERBEREICHNR, ");
                strcat(str, "KDAUFTRAGPOS.STATIONNR, ");
                strcat(str, "KDAUFTRAGPOS.LAGERFACHNR ");
                strcat(str, "from kdauftragpos, artikelzentral z, outer ");
                strcat(str, ARTIKELZENTRAL_SPRACHE);
                strcat(str, " c ");
                strcat(str, "where kdauftragpos.kdauftragnr = ? ");
                strcat(str, "and kdauftragpos.posnr > 0 ");
                strcat(str, "and kdauftragpos.mengegeliefert > 0 ");
                strcat(str, "and kdauftragpos.kobehaeltnr = ? ");
                strcat(str, "and kdauftragpos.artikel_nr = z.artikel_nr ");
                strcat(str, "and kdauftragpos.artikel_nr = c.artikel_nr ");
                strcat(str, "and kdauftragpos.lagerfachnr[2,3] >= ? ");
                strcat(str, "and kdauftragpos.lagerfachnr[2,3] <= ? ");
                strcat(str, "and trunc( kdauftragpos.etartschalter2/512)-2 * ");
                strcat(str, "trunc( kdauftragpos.etartschalter2/(512*2)) = 0 ");
                strcat(str, "order by kdauftragpos.lagerfachnr[2,8] ");
            }
            else
            {
                strcpy(str, "select ");
                strcat(str, "ARTIKELZENTRAL.NORMPACKUNG, ");
                strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
                strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
                strcat(str, "KDAUFTRAGPOS.KDAUFTRAGNR, ");
                strcat(str, "KDAUFTRAGPOS.ARTIKEL_NR, ");
                strcat(str, "KDAUFTRAGPOS.MENGEBESTELLT, ");
                strcat(str, "KDAUFTRAGPOS.MENGEGELIEFERT, ");
                strcat(str, "KDAUFTRAGPOS.KOBEHAELTNR, ");
                strcat(str, "KDAUFTRAGPOS.LAGERBEREICHNR, ");
                strcat(str, "KDAUFTRAGPOS.STATIONNR, ");
                strcat(str, "KDAUFTRAGPOS.LAGERFACHNR ");
                strcat(str, "from kdauftragpos, artikelzentral ");
                strcat(str, "where kdauftragpos.kdauftragnr = ? ");
                strcat(str, "and kdauftragpos.posnr > 0 ");
                strcat(str, "and kdauftragpos.mengegeliefert > 0 ");
                strcat(str, "and kdauftragpos.kobehaeltnr = ? ");
                strcat(str, "and kdauftragpos.artikel_nr = artikelzentral.artikel_nr ");
                strcat(str, "and kdauftragpos.lagerfachnr[2,3] >= ? ");
                strcat(str, "and kdauftragpos.lagerfachnr[2,3] <= ? ");
                strcat(str, "and trunc( kdauftragpos.etartschalter2/512)-2 * ");
                strcat(str, "trunc( kdauftragpos.etartschalter2/(512*2)) = 0 ");
                strcat(str, "order by kdauftragpos.lagerfachnr[2,8] ");
            }
            EXEC SQL PREPARE dec_posart FROM :str;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_nachlart: declare dec_posart %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            /* Containerartikel werden nicht angezeigt (trunc(6.bit auf et2)! */
            EXEC SQL declare Sel_end_pos scroll cursor with hold for dec_posart;
        }

        exec sql open Sel_end_pos using :d->KDAUFTRAGNR, :d->KOBEHAELTNR, :szpBlockvon, :szpBlockbis;
        SQLERROR( fun, "open Sel_end_pos" )
    }

    if (d->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        exec sql close Sel_end_pos;
        SQLERROR( fun, "close Sel_end_pos" )
        return 1;
    }

    exec sql fetch relative :d->FETCH_REL Sel_end_pos into AUFENDPOS_ZEIGER(d);
    SQLERROR( fun, "fetch Sel_end_pos" )
    if (sqlca.sqlcode == SQLNOTFOUND)
        return 1;

    return 0;
}

/*** AAAUFT-SEL-EAN-UNI ******************************************************/

int AaauftSel_ean_uni( struct AUFEAN* a, char* error_msg )
{
    exec sql begin declare section;
    struct AUFEAN* d;
    exec sql end declare section;
    char* fun = "AaauftSel_ean_uni";

    d = a;
    exec sql select artikel_nr into :d->ARTIKEL_NR
        from artikelnummern
        where ean = :d->EAN_NR;
    SQLERR( fun, "select ean" )

    if (sqlca.sqlcode == SQLNOTFOUND)
        return 1;

    return 0;
}

/*** AAAUFT-SEL-ART-POS ******************************************************/

int AaauftSel_art_pos( struct AUFENDPOS* a, char* error_msg )
{
    exec sql begin declare section;
    struct AUFENDPOS* d;
    short ind1;
    short ind2;
    exec sql end declare section;
    char* fun = "AaauftSel_art_pos";
    static int FREMDSPRACHE_ALT = 2;

    d = a;

    if (FREMDSPRACHE != FREMDSPRACHE_ALT)
    {
        FREMDSPRACHE_ALT = FREMDSPRACHE;
        EXEC SQL free sel_artpos;
        if (FREMDSPRACHE)
        {
            strcpy(str, "select ");
            strcat(str, "ARTIKELZENTRAL.NORMPACKUNG, ");
            strcat(str, "nvl(c.EINHEIT, z.EINHEIT), ");
            strcat(str, "nvl(c.ARTIKEL_NAME, z.ARTIKEL_NAME), ");
            strcat(str, "KDAUFTRAGPOS.KDAUFTRAGNR, ");
            strcat(str, "z.ARTIKEL_NR, ");
            strcat(str, "sum(KDAUFTRAGPOS.MENGEBESTELLT), ");
            strcat(str, "sum(KDAUFTRAGPOS.MENGEGELIEFERT), ");
            strcat(str, "KDAUFTRAGPOS.KOBEHAELTNR, ");
            strcat(str, "KDAUFTRAGPOS.LAGERBEREICHNR, ");
            strcat(str, "KDAUFTRAGPOS.STATIONNR, ");
            strcat(str, "KDAUFTRAGPOS.LAGERFACHNR ");
            strcat(str, "from ");
            strcat(str, "kdauftragpos, ");
            strcat(str, "artikelzentral z, ");
            strcat(str, "outer ");
            strcat(str, ARTIKELZENTRAL_SPRACHE);
            strcat(str, " c ");
            strcat(str, "where kdauftragpos.kdauftragnr = ? ");
            strcat(str, "and z.artikel_nr = ? ");
            strcat(str, "and kdauftragpos.kobehaeltnr = ? ");
            strcat(str, "and kdauftragpos.artikel_nr  = z.artikel_nr ");
            strcat(str, "and c.artikel_nr  = z.artikel_nr ");
            strcat(str, "group by 1, 2, 3, 4, 5, 8, 9, 10, 11");
        }
        else
        {
            strcpy(str, "select ");
            strcat(str, "ARTIKELZENTRAL.NORMPACKUNG, ");
            strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
            strcat(str, "KDAUFTRAGPOS.KDAUFTRAGNR, ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_NR, ");
            strcat(str, "sum(KDAUFTRAGPOS.MENGEBESTELLT), ");
            strcat(str, "sum(KDAUFTRAGPOS.MENGEGELIEFERT), ");
            strcat(str, "KDAUFTRAGPOS.KOBEHAELTNR, ");
            strcat(str, "KDAUFTRAGPOS.LAGERBEREICHNR, ");
            strcat(str, "KDAUFTRAGPOS.STATIONNR, ");
            strcat(str, "KDAUFTRAGPOS.LAGERFACHNR ");
            strcat(str, "from ");
            strcat(str, "kdauftragpos, ");
            strcat(str, "artikelzentral ");
            strcat(str, "where kdauftragpos.kdauftragnr = ? ");
            strcat(str, "and artikelzentral.artikel_nr  = ? ");
            strcat(str, "and kdauftragpos.kobehaeltnr = ? ");
            strcat(str, "and kdauftragpos.artikel_nr  = artikelzentral.artikel_nr ");
            strcat(str, "group by 1, 2, 3, 4, 5, 8, 9, 10, 11");
        }

        EXEC SQL PREPARE sel_artpos FROM :str;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_art_pos: declare sel_artpos %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }
    EXEC SQL EXECUTE sel_artpos into
        :d->NORMPACKUNG,
        :d->EINHEIT,
        :d->ARTIKEL_NAME,
        :d->KDAUFTRAGNR,
        :d->ARTIKEL_NR,
        :d->MENGEBESTELLT indicator :ind1,
        :d->MENGEGELIEFERT indicator :ind2,
        :d->KOBEHAELTNR,
        :d->LAGERBEREICHNR,
        :d->STATIONNR,
        :d->LAGERFACHNR
    using
        :d->KDAUFTRAGNR,
        :d->ARTIKEL_NR,
        :d->KOBEHAELTNR;

    if (ind1 < 0) d->MENGEBESTELLT = 0;
    if (ind2 < 0) d->MENGEGELIEFERT = 0;
    SQLERR( fun, "select aufendpos_liste" )
    if (sqlca.sqlcode == SQLNOTFOUND)
        return 1;
    return 0;
}

/*** AAAUFT-SEL-END-ART ******************************************************/

int AaauftSel_end_art( struct AUFENDART* a, char* error_msg )
{
    exec sql begin declare section;
    struct AUFENDART* d;
    exec sql end declare section;
    char* fun = "AaauftSel_end_art";
    static int FREMDSPRACHE_ALT = 2;

    d = a;
    if (FREMDSPRACHE != FREMDSPRACHE_ALT)
    {
        FREMDSPRACHE_ALT = FREMDSPRACHE;
        EXEC SQL free sel_artend;
        if (FREMDSPRACHE)
        {
            strcpy(str, "select ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_NR, ");
            strcat(str, "ARTIKELZENTRAL.NORMPACKUNG, ");
            strcat(str, "nvl(c.EINHEIT, ARTIKELZENTRAL.EINHEIT), ");
            strcat(str, "nvl(c.ARTIKEL_NAME, ARTIKELZENTRAL.ARTIKEL_NAME), ");
            strcat(str, "ARTIKELLOKAL.BESTAND, ");
            strcat(str, "ARTIKELLOKAL.LAGERBEREICHNR, ");
            strcat(str, "ARTIKELLOKAL.STATIONNR, ");
            strcat(str, "ARTIKELLOKAL.LAGERFACHNR ");
            strcat(str, "from artikelzentral, outer artikellokal ");
            strcat(str, "where artikelzentral.artikel_nr = ? ");
            strcat(str, "and artikellokal.artikel_nr = artikelzentral.artikel_nr ");
            strcat(str, "and artikellokal.filialnr = ? ");
        }
        else
        {
            strcpy(str, "select ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_NR, ");
            strcat(str, "ARTIKELZENTRAL.NORMPACKUNG, ");
            strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
            strcat(str, "ARTIKELLOKAL.BESTAND, ");
            strcat(str, "ARTIKELLOKAL.LAGERBEREICHNR, ");
            strcat(str, "ARTIKELLOKAL.STATIONNR, ");
            strcat(str, "ARTIKELLOKAL.LAGERFACHNR ");
            strcat(str, "from artikelzentral, outer artikellokal ");
            strcat(str, "where artikelzentral.artikel_nr = ? ");
            strcat(str, "and artikellokal.artikel_nr = artikelzentral.artikel_nr ");
            strcat(str, "and artikellokal.filialnr = ? ");
        }

        EXEC SQL PREPARE sel_artend FROM :str;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_end_art: declare sel_artend %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }
    EXEC SQL EXECUTE sel_artend into AUFENDART_ZEIGER(d)
    using
        :d->ARTIKEL_NR,
        :FilialNr;
    SQLERR( fun, "select aufendart_liste" )

    if (sqlca.sqlcode == SQLNOTFOUND)
        return 1;

    return 0;
}

/*** AAAUFT-DEL-KNDNL ********************************************************/

int AaauftSel_kndnl(struct NACHLIEF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct NACHLIEF* a;
    long vonnr;
    long bisnr;
    char cAufart[3];
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        cAufart[0] = a->KDAUFTRAGART[0];
        cAufart[1] = a->KDAUFTRAGART[1];
        cAufart[2] = '\0';
        if (a->KDAUFTRAGART[0] == ' ')
        {
            a->KDAUFTRAGART[0] = 'N';
            a->KDAUFTRAGART[1] = 'O';
        }
        if (a->ARTIKEL_NR == 0)
        {
            vonnr=0;
            bisnr=9999999;
        }
        else
        {
            vonnr = bisnr = a->ARTIKEL_NR;
        }
        EXEC SQL declare Sel_kndnl scroll cursor with hold for
            select NACHLIEF_LISTE
            from nachlieferpos, artikelzentral, kunde, artikellokal
            where nachlieferpos.artikel_nr >= :vonnr
              and nachlieferpos.artikel_nr <= :bisnr
              and (postyp = 3
                   or postyp = 5)
              and (nachlieferpos.kdauftragart = :a->KDAUFTRAGART
                   or nachlieferpos.kdauftragart = :cAufart)
              and artikellokal.artikel_nr = nachlieferpos.artikel_nr
              and artikelzentral.artikel_nr = nachlieferpos.artikel_nr
              and nachlieferpos.kundennr = kunde.kundennr
              and kunde.vertriebszentrumnr = nachlieferpos.vertriebszentrumnr
              and artikellokal.bestand != 0
              and artikellokal.filialnr = nachlieferpos.vertriebszentrumnr
              and nachlieferpos.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
            order by nachlieferpos.datum , nachlieferpos.idfnr ;

        EXEC SQL open Sel_kndnl;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_kndnl: open Sel_kndnl %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Sel_kndnl;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_kndnl: close Sel_kndnl %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_kndnl into NACHLIEF_ZEIGER(a);
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSel_kndnl: fetch Sel_kndnl %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Sel_kndnl;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

int AaauftSel_kndnlprio(struct NACHLIEF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct NACHLIEF* a;
    char cAufart[3];
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        cAufart[0] = a->KDAUFTRAGART[0];
        cAufart[1] = a->KDAUFTRAGART[1];
        cAufart[2] = '\0';
        if (a->KDAUFTRAGART[0] == ' ')
        {
            a->KDAUFTRAGART[0] = 'N';
            a->KDAUFTRAGART[1] = 'O';
        }
        exec sql select bestand, artikellokal.artikel_nr
            into :nachliefbestand, :a->ARTIKEL_NR
            from artikelzentral, outer artikellokal
            where artikelzentral.artikel_nr = :a->ARTIKEL_NR
              and artikellokal.artikel_nr = artikelzentral.artikel_nr
              and artikellokal.bestand != 0
              and artikellokal.filialnr = :FilialNr;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_kndnlprio: select bestand %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        EXEC SQL declare Sel_kndprio scroll cursor with hold for
        select
            NACHLIEFERPOS.KDAUFTRAGNR,
            NACHLIEFERPOS.POSNR,
            NACHLIEFERPOS.DATUM,
            NACHLIEFERPOS.POSTYP,
            NACHLIEFERPOS.IDFNR,
            NACHLIEFERPOS.ARTIKEL_NR,
            NACHLIEFERPOS.MENGE,
            NACHLIEFERPOS.FILIALNR1,
            NACHLIEFERPOS.FILIALNR2,
            NACHLIEFERPOS.FILIALNR3,
            NACHLIEFERPOS.STATUS,
            KUNDE.MATCHCODE,
            KUNDE.KZKDKLASSE,
            NACHLIEFERPOS.KUNDENNR,
            NACHLIEFERPOS.VERTRIEBSZENTRUMNR,
            NACHLIEFERPOS.VERTRIEBSZENTRUMNR,
            ARTIKELZENTRAL.EINHEIT,
            ARTIKELZENTRAL.ARTIKEL_NAME,
            NACHLIEFERPOS.KDAUFTRAGART,
            NACHLIEFERPOS.BEMERKUNGEN
        from nachlieferpos, artikelzentral, kunde
        where nachlieferpos.artikel_nr = :a->ARTIKEL_NR
          and (postyp = 3
               or postyp = 5)
          and (nachlieferpos.kdauftragart = :a->KDAUFTRAGART
               or nachlieferpos.kdauftragart = :cAufart)
          and nachlieferpos.kundennr = kunde.kundennr
          and kunde.vertriebszentrumnr = nachlieferpos.filialnr1
          and nachlieferpos.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR
          and artikelzentral.artikel_nr = nachlieferpos.artikel_nr
        order by kunde.kzkdklasse , nachlieferpos.datum , nachlieferpos.idfnr ;

        EXEC SQL open Sel_kndprio;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_kndnlprio: open Sel_kndprio %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Sel_kndprio;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_kndnlprio: close Sel_kndprio %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    if (nachliefbestand <= 0) return 1;

    EXEC SQL fetch relative :a->FETCH_REL Sel_kndprio into NACHLIEF_ZEIGER(a);
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSel_kndnlprio: fetch Sel_kndprio %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Sel_kndnl;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
    nachliefbestand = nachliefbestand - a->MENGE;

    return 0;
}

int AaauftIns_prot(struct NACHLPROT* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct NACHLPROT* a;
    EXEC SQL END DECLARE SECTION;
    struct NACHLIEF n;

    a = d;
    a->ZEIT_NEU  = AllgGetTime();
    a->DATUM_NEU = AllgGetDate();

    n.KDAUFTRAGNR   = a->KDAUFTRAGNR;
    n.POSNR         = a->POSNR;
    n.DATUM         = a->DATUM;
    n.POSTYP        = a->POSTYP;
    n.MENGE         = a->NL_MENGE_AKTUELL;
    n.VERTRIEBSZENTRUMNR = a->VERTRIEBSZENTRUMNR;
    n.IDFNR = a->IDFNR;
    n.KUNDENNR = a->IDFNR;
    if (a->AENDTYP == AENDTYP_FOLGE)
    {
        n.ARTIKEL_NR            = a->NL_MENGE_GELIEFER;
        a->NL_MENGE_GELIEFER    = 0;
    }

    EXEC SQL begin work;

    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftIns_prot begin work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    EXEC SQL insert into nachliefprot (NACHLPROT_LISTE, userbranchno) values (NACHLPROT_ZEIGER(a), :sUserVz);
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftIns_prot insert %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL rollback work;
        return -1;
    }

    if (a->AENDTYP == AENDTYP_LIEFERMOEGLICHKEIT || a->AENDTYP == AENDTYP_DELETE)
    {
        if (AaauftLoe_nachl(&n, error_msg) == -1)
        {
            EXEC SQL rollback work;
            return -1;
        }
    }
    else if (a->AENDTYP == AENDTYP_FOLGE)
    {
        if (AaauftIns_nachl(&n, error_msg) == -1)
        {
            EXEC SQL rollback work;
            return -1;
        }
    }
    else
    {
        if (AaauftUpd_nachl(&n, error_msg) == -1)
        {
            EXEC SQL rollback work;
            return -1;
        }
    }

    EXEC SQL commit work;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftIns_prot begin work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    return 0;
}

int AaauftGet_prot_nl(struct NACHLPROTV* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct NACHLPROTV* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        EXEC SQL declare Get_prot_nl scroll cursor with hold for
            select NACHLPROTV_LISTE
            from
                NACHLIEFPROT, PASSWD, ARTIKELZENTRAL
            where
                ARTIKELZENTRAL.ARTIKEL_NR = :a->ARTIKEL_NR  and
                NACHLIEFPROT.ARTIKEL_NR = ARTIKELZENTRAL.ARTIKEL_NR and
                NACHLIEFPROT.IDFNR      = :a->IDFNR         and
                PASSWD.UID = NACHLIEFPROT.UID   and
                PASSWD.FILIALNR = NACHLIEFPROT.USERBRANCHNO
            order by
                NACHLIEFPROT.DATUM_NEU, NACHLIEFPROT.ZEIT_NEU ;

        EXEC SQL open Get_prot_nl;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftGet_prot_nl: open Get_prot_nl %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Get_prot_nl;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftGet_prot_nl: close Get_prot_nl %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Get_prot_nl into NACHLPROTV_ZEIGER(a);
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftGet_prot_nl: fetch Get_prot_nl %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Get_prot_nl;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

int AaauftGetfirstordertime(struct AUSTINF* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short dbnull;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (!a->DATUM)
    {
        a->DATUM = AllgGetDate();
        EXEC SQL select MAX(zeit) into :a->ZEITERSTEGUELTIGK indicator :dbnull
        from    kdauftragereignis
        where   kdauftragnr = :a->KDAUFTRAGNR and
                datum       = :a->DATUM; /* and
                ( ereignisart = 3 or ereignisart = 4);  */
        a->DATUM = 0;
    }
    else if (a->DATUM == AllgGetDate())
    {
        EXEC SQL select MAX(zeit) into :a->ZEITERSTEGUELTIGK indicator :dbnull
        from    kdauftragereignis
        where   kdauftragnr = :a->KDAUFTRAGNR and
                datum       = :a->DATUM; /* and
                ( ereignisart = 3 or ereignisart = 4);  */
    }
    else
    {
        EXEC SQL select MAX(zeit) into :a->ZEITERSTEGUELTIGK indicator :dbnull
        from    akdauftragereignis
        where   kdauftragnr = :a->KDAUFTRAGNR and
                datum       = :a->DATUM; /* and
                ( ereignisart = 3 or ereignisart = 4);  */
    }

    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AaauftGetfirstordertime: select %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    if (dbnull < 0 )
    {
        a->ZEITERSTEGUELTIGK = 0 ;
    }
    return 0;
}

int AaauftSel_tub_pos(struct AUFWANNEN* a, char* error_msg)
{
    exec sql begin declare section;
    struct AUFWANNEN* d;
    exec sql end declare section;
    char* fun = "AaauftSel_tub_pos";

    d = a;
    if (d->DATUM == 0)
    {
        exec sql select KDAUFTRAGNR,
                        POSNR,
                        KOBEHAELTNR,
                        LAGERFACHNR
            into        :d->KDAUFTRAGNR,
                        :d->POSNR,
                        :d->KOBEHAELTNR,
                        :d->LAGERFACHNR
            from kdauftragpos
            where kdauftragnr = :d->KDAUFTRAGNR
            and posnr = :d->POSNR;
    }
    else
    {
        exec sql select KDAUFTRAGNR,
                        POSNR,
                        KOBEHAELTNR,
                        LAGERFACHNR
            into        :d->KDAUFTRAGNR,
                        :d->POSNR,
                        :d->KOBEHAELTNR,
                        :d->LAGERFACHNR
            from akdauftragpos
            where kdauftragnr = :d->KDAUFTRAGNR
            and posnr = :d->POSNR
            and datum = :d->DATUM;
    }
    SQLERR( fun, "select tub_pos" )

    if (sqlca.sqlcode == SQLNOTFOUND)
        return 1;
    return 0;
}

int AaauftSel_lager_auft_nr(struct AUSTINF* d, char* error_msg)
{
    UNUSED(d);
    UNUSED(error_msg);
    /* referenced table koeinheit not in use anymore */
    return 1;
}

/*** AAAUFT-SEL-LAUFTNR ******************************************************/

int AaauftSel_lauftnr(struct AUFLAGER* a, char* error_msg)
{
    UNUSED(a);
    UNUSED(error_msg);
    /* referenced table koeinheit not in use anymore */
    return 1;
}

/*** AAAUFT-SEL-VBLIEF ******************************************************/

int Aaauft_Sel_vblief(struct VBLIEF* d, char* error_msg)
{
    static int fst = 1;
    static int FREMDSPRACHE_ALT = 2;

    exec sql begin declare section;
    struct VBLIEF* a;
    long datum;
    long hausvon;
    long hausbis;
    exec sql end declare section;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        if (a->IDFNR == 0)
        {
            hausvon = 0;
            hausbis = 99;
        }
        else
        {
            hausvon = a->IDFNR;
            hausbis = a->IDFNR;
        }
        if (a->DATUM == 0) a->DATUM = AllgGetDate();
        datum = a->DATUM;
        fst = 0;
        if (FREMDSPRACHE != FREMDSPRACHE_ALT)
        {
            FREMDSPRACHE_ALT = FREMDSPRACHE;
            EXEC SQL free dec_vblief;
            if (FREMDSPRACHE)
            {
                strcpy(str, "select ");
                strcat(str, "KUNDE.IDFNR, ");
                strcat(str, "TO_CHAR(ibtrequest.creationdatetime, '%Y%m%d')::integer, ");
                strcat(str, "IBTREQUEST.ARTICLENO, ");
                strcat(str, "nvl(c.EINHEIT, z.EINHEIT), ");
                strcat(str, "IBTREQUEST.QUANTITY, ");
                strcat(str, "nvl(c.ARTIKEL_NAME, z.ARTIKEL_NAME), ");
                strcat(str, "KUNDE.NAMEAPO, ");
                strcat(str, "KUNDE.TELNR, ");
                strcat(str, "KUNDE.TELKURZWAHL ");
                strcat(str, "from kunde, ibtrequest, artikelzentral z, outer ");
                strcat(str, ARTIKELZENTRAL_SPRACHE);
                strcat(str, " c ");
                strcat(str, "where  TO_CHAR(ibtrequest.creationdatetime, '%Y%m%d')::integer = ? ");
                strcat(str, "and ibtrequest.articleno = z.artikel_nr ");
                strcat(str, "and ibtrequest.articleno = c.artikel_nr ");
                strcat(str, "and kunde.kundennr = ibtrequest.customerno ");
                strcat(str, "and kunde.vertriebszentrumnr = ibtrequest.branchno ");
                strcat(str, "and ibtrequest.branchno = ? ");
                strcat(str, "and ibtrequest.ibtbranchno >= ? ");
                strcat(str, "and ibtrequest.ibtbranchno <= ? ");
                strcat(str, "order by kunde.idfnr, ibtrequest.articleno ");
            }
            else
            {
                strcpy(str, "select ");
                strcat(str, "KUNDE.IDFNR, ");
                strcat(str, "TO_CHAR(ibtrequest.creationdatetime, '%Y%m%d')::integer, ");
                strcat(str, "IBTREQUEST.ARTICLENO, ");
                strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
                strcat(str, "IBTREQUEST.QUANTITY, ");
                strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
                strcat(str, "KUNDE.NAMEAPO, ");
                strcat(str, "KUNDE.TELNR, ");
                strcat(str, "KUNDE.TELKURZWAHL ");
                strcat(str, "from kunde, ibtrequest, artikelzentral ");
                strcat(str, "where TO_CHAR(ibtrequest.creationdatetime, '%Y%m%d')::integer = ? ");
                strcat(str, "and ibtrequest.articleno = artikelzentral.artikel_nr ");
                strcat(str, "and kunde.kundennr = ibtrequest.customerno ");
                strcat(str, "and kunde.vertriebszentrumnr = ibtrequest.branchno ");
                strcat(str, "and ibtrequest.branchno = ? ");
                strcat(str, "and ibtrequest.ibtbranchno >= ? ");
                strcat(str, "and ibtrequest.ibtbranchno <= ? ");
                strcat(str, "order by kunde.idfnr, ibtrequest.articleno ");
            }

            EXEC SQL PREPARE dec_vblief FROM :str;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " Aaauft_Sel_vblief: declare dec_vblief %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL declare Sel_vblief scroll cursor with hold for dec_vblief;
        }

        EXEC SQL open Sel_vblief
        using
            :datum,
            :a->MENGE,
            :hausvon,
            :hausbis;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_vlief: open Sel_vblief %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            WriteLogInfo(error_msg, -1 , -1);
            return 1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Sel_vblief;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_vblief: close Sel_vblief %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_vblief into VBLIEF_ZEIGER(a);
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSel_vblief: fetch Sel_vblief %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Sel_vblief;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}


int AaauftSel_vbcount(struct VBCOUNT* d, char* error_msg)
{
    exec sql begin declare section;
    struct VBCOUNT* a;
    short Vz_von;
    short Vz_bis;
//    int anz;
    exec sql end declare section;

    a = d;
    if (a->ANZ_IE == 0)
    {
        Vz_von = 0;
        Vz_bis = 99;
    }
    else
    {
        Vz_von = a->ANZ_IE;
        Vz_bis = a->ANZ_IE;
    }
    a->ANZ_ST = 0;

    EXEC SQL select count(*) into :a->ANZ_IE from ibtrequest i
        inner join kdauftrag k on i.branchno = k.filialnr and i.cscorderno = k.kdauftragnr
        where i.processingstate = 0
        and i.branchno >= :Vz_von
        and i.branchno <= :Vz_bis;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSel_vbcount: Select IE %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    EXEC SQL select count(*) into :a->ANZ_ER from ibtrequest i
        inner join kdauftrag k on i.branchno = k.filialnr and i.cscorderno = k.kdauftragnr
        where i.processingstate = 1
        and i.branchno >= :Vz_von
        and i.branchno <= :Vz_bis;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSel_vbcount: Select ER %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    EXEC SQL select count(*) into :a->ANZ_GD from ibtrequest i
        inner join kdauftrag k on i.branchno = k.filialnr and i.cscorderno = k.kdauftragnr
        where i.processingstate = 2
        and i.branchno >= :Vz_von
        and i.branchno <= :Vz_bis;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSel_vbcount: Select GD %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    return 0;
}

/*** AAAUFT-SEL-DEFEKTE ******************************************************/

int AaauftSel_defekte(struct N_VBBUCH* d, char* error_msg)
{
    static int fst = 1;
    static int FREMDSPRACHE_ALT = 2;

    exec sql begin declare section;
    struct N_VBBUCH* a;
    exec sql end declare section;
    char* fun = "AaauftSel_defekte";

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        if (FREMDSPRACHE != FREMDSPRACHE_ALT)
        {
            FREMDSPRACHE_ALT = FREMDSPRACHE;
            EXEC SQL free dec_defekt;
            EXEC SQL free CSelDefekte;
            if (FREMDSPRACHE)
            {
                strcpy(str, "select ");
                strcat(str, "KDAUFTRAGPOS.MENGEBESTELLT, ");
                strcat(str, "KDAUFTRAGPOS.MENGEBESTAETIGT, ");
                strcat(str, "KDAUFTRAGPOS.MENGENATRA, ");
                strcat(str, "KDAUFTRAGPOS.BEMERKUNGEN, ");
                strcat(str, "z.ARTIKEL_NR, ");
                strcat(str, "nvl(c.DARREICHFORM, z.DARREICHFORM), ");
                strcat(str, "nvl(c.EINHEIT, z.EINHEIT), ");
                strcat(str, "nvl(c.ARTIKEL_NAME, z.ARTIKEL_NAME), ");
                strcat(str, "z.PRODUSERQUOTA ");
                strcat(str, "from ");
                strcat(str, "ARTIKELZENTRAL z, ");
                strcat(str, "KDAUFTRAG, ");
                strcat(str, "KDAUFTRAGPOS, ");
                strcat(str, "outer ");
                strcat(str, ARTIKELZENTRAL_SPRACHE);
                strcat(str, " c ");
                strcat(str, "where ");
                strcat(str, "kdauftrag.kundennr = ? and ");
                strcat(str, "kdauftrag.vertriebszentrumnr = ? and ");
                strcat(str, "kdauftragstat[10] = '0' and ");
                strcat(str, "kdauftragpos.kdauftragnr = kdauftrag.kdauftragnr and ");
                strcat(str, "trunc( kdauftragpos.etposschalter2/256)-2 * ");
                strcat(str, "trunc( kdauftragpos.etposschalter2/(256*2)) = 0 and ");
                strcat(str, "trunc( kdauftragpos.etposschalter2/32)-2 * ");
                strcat(str, "trunc( kdauftragpos.etposschalter2/(32*2)) = 0 and ");
                strcat(str, "kdauftragpos.mengebestellt > kdauftragpos.mengebestaetigt and ");
                strcat(str, "kdauftragpos.artikel_nr = z.artikel_nr and ");
                strcat(str, "kdauftragpos.artikel_nr = c.artikel_nr and ");
                strcat(str, "order by z.artikel_nr, kdauftragpos.mengebestellt desc ");
            }
            else
            {
                strcpy(str, "select ");
                strcat(str, "KDAUFTRAGPOS.MENGEBESTELLT, ");
                strcat(str, "KDAUFTRAGPOS.MENGEBESTAETIGT, ");
                strcat(str, "KDAUFTRAGPOS.MENGENATRA, ");
                strcat(str, "KDAUFTRAGPOS.BEMERKUNGEN, ");
                strcat(str, "ARTIKELZENTRAL.ARTIKEL_NR, ");
                strcat(str, "ARTIKELZENTRAL.DARREICHFORM, ");
                strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
                strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
                strcat(str, "ARTIKELZENTRAL.PRODUSERQUOTA ");
                strcat(str, "from ");
                strcat(str, "ARTIKELZENTRAL, ");
                strcat(str, "KDAUFTRAG, ");
                strcat(str, "KDAUFTRAGPOS ");
                strcat(str, "where ");
                strcat(str, "kdauftrag.kundennr = ? and ");
                strcat(str, "kdauftrag.vertriebszentrumnr = ? and ");
                strcat(str, "kdauftragstat[10] = '0' and ");
                strcat(str, "kdauftragpos.kdauftragnr = kdauftrag.kdauftragnr and ");
                strcat(str, "trunc( kdauftragpos.etposschalter2/256)-2 * ");
                strcat(str, "trunc( kdauftragpos.etposschalter2/(256*2)) = 0 and ");
                strcat(str, "trunc( kdauftragpos.etposschalter2/32)-2 * ");
                strcat(str, "trunc( kdauftragpos.etposschalter2/(32*2)) = 0 and ");
                strcat(str, "kdauftragpos.mengebestellt > kdauftragpos.mengebestaetigt and ");
                strcat(str, "kdauftragpos.artikel_nr = artikelzentral.artikel_nr ");
                strcat(str, "order by artikelzentral.artikel_nr, kdauftragpos.mengebestellt desc ");
            }

            EXEC SQL PREPARE dec_defekt FROM :str;
            if (sqlca.sqlcode < 0 )
            {
                fst = 1;
                sprintf(error_msg, " AaauftSel_defekte: declare dec_defekt %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            exec sql declare CSelDefekte scroll cursor with hold for dec_defekt;
        }
        exec sql open CSelDefekte
        using
            :a->ARTIKEL_NR,
            :a->FILIALNR;
        SQLERR( fun, "open CSelDefekte" )
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close CSelDefekte;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_defekte: close CSelDefekte %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch CSelDefekte into
            :a->MENGEBESTELLT,
            :a->MENGEBESTAETIGT,
            :a->MENGENATRA,
            :a->BEMERKUNGEN,
            :a->ARTIKEL_NR,
            :a->DARREICHFORM,
            :a->EINHEIT,
            :a->ARTIKEL_NAME,
            :a->PRODUSERQUOTA;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSel_defekte: fetch CSelDefekte %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close CSelDefekte;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
    a->FILIALNR = 0;
    a->BESTAND = 0;
    Aaauft_GetArtKennz(a->ARTIKEL_NR, a->KURZBEZKONDI, error_msg);

    return 0;
}

int AaauftSperr_auft(struct AUFIE* d, char* error_msg)
{
    exec sql begin declare section;
    struct AUFIE* a;
    exec sql end declare section;

    a = d;
    EXEC SQL begin work;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSperr_auft commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    exec sql update werte set zahl = :a->ANZ_IE where  bezeichner = "AA_NEW_ORD"
        and vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSperr_auft: Sperre %d Auftraege %ld %ld", a->ANZ_IE,
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    EXEC SQL commit work;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSperr_auft commit work %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    EXEC SQL select count(*) into :a->ANZ_IE from kdauftrag
        where   kdauftrag.kdauftragstat like AEORD_IN_ERFASSUNG
        and     kdauftrag.vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSperr_auft: Select IE %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    return 0;
}

int AaauftSel_valutaauto(struct AUFARTES* d, char* error_msg)
{
    exec sql begin declare section;
    struct AUFARTES* a;
    long lTag;
    long lTagNull;
    exec sql end declare section;

    a = d;
    lTag = (AllgGetDate()%100);

    /* Bei UW oder MD immer automatische Valuta */
    if (!strcmp(a->KDAUFTRAGART, "UW") || !strcmp(a->KDAUFTRAGART, "MD") )
        lTagNull = 99;
    else
        lTagNull = 0;

    EXEC SQL select valutamonauto into :a->VALUTAMONATE from auftragartkd, kundekondi
        where   auftragartkd.kundennr           =   :a->KUNDENNR
        and     auftragartkd.vertriebszentrumnr =   :a->VERTRIEBSZENTRUMNR
        and     kundekondi.kundennr             =   auftragartkd.kundennr
        and     kundekondi.vertriebszentrumnr   =   auftragartkd.vertriebszentrumnr
        and     kundekondi.tagautovaluta        <=  :lTag
        and     kundekondi.tagautovaluta        !=  :lTagNull
        and     auftragartkd.kdauftragart       =   :a->KDAUFTRAGART;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSel_valutaauto: Select valutamonauto %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

int AaauftSelzurauftpzn(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    long MIN_RECHNR;
    long MAX_RECHNR;
    char MIN_INVOICE[16];
    char MAX_INVOICE[16];
    short Vz_von;
    short Vz_bis;
    long MIN_KND;
    long MAX_KND;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        sdatum = a->DATUM;     /* spaeter extra feld in view */
        datum = a->DATUM;      /* spaeter extra feld in view */
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        ppGStripLast(a->TOURID);
        ppGStripLast(a->KDAUFTRAGART);
        ppGStripLast(a->SORTFIELD);
        ppGStripLast(a->INVOICENUMBER);
        if (a->SORTFIELD[0] == '\0') strcpy(a->SORTFIELD, "kdauftragnr");
        if (a->ANZPOS == 0) /* nase keine Rechnungsnummer mitgegeben */
        {
            MIN_RECHNR = 0;
            MAX_RECHNR = 2147483647;
        }
        else
        {
            MIN_RECHNR = a->ANZPOS;
            MAX_RECHNR = a->ANZPOS;
        }
        if (a->INVOICENUMBER[0] == '\0') /* nase keine Rechnungsnummer mitgegeben */
        {
            strcpy(MIN_INVOICE, " ");
            strcpy(MAX_INVOICE, "999999999999999");
        }
        else
        {
            strcpy(MIN_INVOICE, a->INVOICENUMBER);
            strcpy(MAX_INVOICE, a->INVOICENUMBER);
        }
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        if (a->KUNDENNR == 0) /* nase alle VZs */
        {
            MIN_KND = 0;
            MAX_KND = 9999999;
        }
        else
        {
            MIN_KND = a->KUNDENNR;
            MAX_KND = a->KUNDENNR;
        }
        if (a->DATUM == 0)
        {
            strcpy(str, "select ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "KDAUFTRAG.IDFNR, ");
            strcat(str, "KDAUFTRAG.GERAETNAME, ");
            strcat(str, "KDAUFTRAG.TOURID, ");
            strcat(str, "KDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "KDAUFTRAG.KOART, ");
            strcat(str, "KDAUFTRAG.BUCHART, ");
            strcat(str, "KDAUFTRAG.ANZPOS, ");
            strcat(str, "KDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "KDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "KDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "KDAUFTRAG.ANZPOSOB, ");
            strcat(str, "KDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "KDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "KDAUFTRAG.SENDESTATUS, ");
            strcat(str, "KDAUFTRAG.ZUGRUND, ");
            strcat(str, "KDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "KDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "KDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "KDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "KDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "KDAUFTRAG.ORDERLABEL, ");
            strcat(str, "KDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "CSCORDERFLAGS.WAITFORIBTPICKING, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "from kdauftrag, kunde, kdauftragpos, artikelzentral, cscorderflags ");
            strcat(str, "where artikelzentral.artikel_nr = ? and ");
            strcat(str, "kdauftragpos.artikel_nr = artikelzentral.artikel_nr and ");
            strcat(str, "kdauftrag.kdauftragnr = kdauftragpos.kdauftragnr and ");
            strcat(str, "kdauftrag.kdauftragstat like ? and ");
            strcat(str, "kdauftrag.geraetname like ? and ");
            strcat(str, "kdauftrag.tourid like ? and ");
            strcat(str, "kdauftrag.kdauftragart like ? and ");
            strcat(str, "kdauftrag.kdauftragnr >= ? and ");
            if (!strncmp(cCountry, "BG", 2))
            {
                strcat(str, "kdauftrag.invoicenumber >= ? and ");
                strcat(str, "kdauftrag.invoicenumber <= ? and ");
            }
            else
            {
                strcat(str, "kdauftrag.rechnungnr >= ? and ");
                strcat(str, "kdauftrag.rechnungnr <= ? and ");
            }
            strcat(str, "kunde.kundennr = kdauftrag.kundennr and ");
            strcat(str, "kunde.vertriebszentrumnr = kdauftrag.vertriebszentrumnr and ");
            strcat(str, "kdauftrag.vertriebszentrumnr >= ? and ");
            strcat(str, "kdauftrag.vertriebszentrumnr <= ? and ");
            strcat(str, "cscorderflags.cscorderno = kdauftrag.kdauftragnr and ");
            strcat(str, "kdauftrag.vertriebszentrumnr in ( ");
            strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
            strcat(str, "where  RegionArten.RegionNr = ? and ");
            strcat(str, "RegionArten.RegionenTyp=1) and ");
            strcat(str, "kdauftrag.kundennr >= ? and ");
            strcat(str, "kdauftrag.kundennr <= ? ");
            strcat(str, "group by ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "KDAUFTRAG.IDFNR, ");
            strcat(str, "KDAUFTRAG.GERAETNAME, ");
            strcat(str, "KDAUFTRAG.TOURID, ");
            strcat(str, "KDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "KDAUFTRAG.KOART, ");
            strcat(str, "KDAUFTRAG.BUCHART, ");
            strcat(str, "KDAUFTRAG.ANZPOS, ");
            strcat(str, "KDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "KDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "KDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "KDAUFTRAG.ANZPOSOB, ");
            strcat(str, "KDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "KDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "KDAUFTRAG.SENDESTATUS, ");
            strcat(str, "KDAUFTRAG.ZUGRUND, ");
            strcat(str, "KDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "KDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "KDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "KDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "KDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "KDAUFTRAG.ORDERLABEL, ");
            strcat(str, "KDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "CSCORDERFLAGS.WAITFORIBTPICKING, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "order by ");
            if (!strcmp(a->SORTFIELD, "kdauftragnr")) strcat(str, "kdauftrag.");
            strcat(str, a->SORTFIELD);
            EXEC SQL prepare dec_Selauftpzn from :str;
            EXEC SQL declare Selauftpzn scroll cursor with hold for dec_Selauftpzn;

            if (!strncmp(cCountry, "BG", 2))
            {
                EXEC SQL open Selauftpzn using
                     :a->ZEITENDEAM,
                     :a->KDAUFTRAGSTAT,
                     :a->GERAETNAME,
                     :a->TOURID,
                     :a->KDAUFTRAGART,
                     :a->KDAUFTRAGNR,
                     :MIN_INVOICE,
                     :MAX_INVOICE,
                     :Vz_von,
                     :Vz_bis,
                     :a->REGIONNR,
                     :MIN_KND,
                     :MAX_KND;
            }
            else
            {
                EXEC SQL open Selauftpzn using
                     :a->ZEITENDEAM,
                     :a->KDAUFTRAGSTAT,
                     :a->GERAETNAME,
                     :a->TOURID,
                     :a->KDAUFTRAGART,
                     :a->KDAUFTRAGNR,
                     :MIN_RECHNR,
                     :MAX_RECHNR,
                     :Vz_von,
                     :Vz_bis,
                     :a->REGIONNR,
                     :MIN_KND,
                     :MAX_KND;
            }
        }
        else
        {
            strcpy(str, "select ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "AKDAUFTRAG.IDFNR, ");
            strcat(str, "AKDAUFTRAG.GERAETNAME, ");
            strcat(str, "AKDAUFTRAG.TOURID, ");
            strcat(str, "AKDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "AKDAUFTRAG.KOART, ");
            strcat(str, "AKDAUFTRAG.BUCHART, ");
            strcat(str, "AKDAUFTRAG.ANZPOS, ");
            strcat(str, "AKDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "AKDAUFTRAG.ANZPOSOB, ");
            strcat(str, "AKDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "AKDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "AKDAUFTRAG.SENDESTATUS, ");
            strcat(str, "AKDAUFTRAG.ZUGRUND, ");
            strcat(str, "AKDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "AKDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "AKDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "AKDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "AKDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "AKDAUFTRAG.ORDERLABEL, ");
            strcat(str, "AKDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "ACSCORDERFLAGS.WAITFORIBTPICKING, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "from akdauftrag, kunde, akdauftragpos, artikelzentral, acscorderflags ");
            strcat(str, "where artikelzentral.artikel_nr = ? and ");
            strcat(str, "akdauftragpos.artikel_nr = artikelzentral.artikel_nr and ");
            strcat(str, "akdauftragpos.datum = ? and ");
            strcat(str, "akdauftrag.kdauftragnr = akdauftragpos.kdauftragnr and ");
            strcat(str, "akdauftrag.datum = akdauftragpos.datum and ");
            strcat(str, "akdauftrag.kdauftragstat like ? and ");
            strcat(str, "akdauftrag.geraetname like ? and ");
            strcat(str, "akdauftrag.tourid like ? and ");
            strcat(str, "akdauftrag.kdauftragart like ? and ");
            strcat(str, "akdauftrag.kdauftragnr >= ? and ");
            if (!strncmp(cCountry, "BG", 2))
            {
                strcat(str, "akdauftrag.invoicenumber >= ? and ");
                strcat(str, "akdauftrag.invoicenumber <= ? and ");
            }
            else
            {
                strcat(str, "akdauftrag.rechnungnr >= ? and ");
                strcat(str, "akdauftrag.rechnungnr <= ? and ");
            }
            strcat(str, "kunde.kundennr = akdauftrag.kundennr and ");
            strcat(str, "kunde.vertriebszentrumnr = akdauftrag.vertriebszentrumnr and ");
            strcat(str, "akdauftrag.vertriebszentrumnr >= ? and ");
            strcat(str, "akdauftrag.vertriebszentrumnr <= ? and ");
            strcat(str, "acscorderflags.cscorderno = akdauftrag.kdauftragnr and ");
            strcat(str, "acscorderflags.datum = akdauftrag.datum and ");
            strcat(str, "akdauftrag.vertriebszentrumnr in ( ");
            strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
            strcat(str, "where RegionArten.RegionNr = ? and ");
            strcat(str, "RegionArten.RegionenTyp=1) and ");
            strcat(str, "akdauftrag.kundennr >= ? and ");
            strcat(str, "akdauftrag.kundennr <= ? ");
            strcat(str, "group by ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "AKDAUFTRAG.IDFNR, ");
            strcat(str, "AKDAUFTRAG.GERAETNAME, ");
            strcat(str, "AKDAUFTRAG.TOURID, ");
            strcat(str, "AKDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "AKDAUFTRAG.KOART, ");
            strcat(str, "AKDAUFTRAG.BUCHART, ");
            strcat(str, "AKDAUFTRAG.ANZPOS, ");
            strcat(str, "AKDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "AKDAUFTRAG.ANZPOSOB, ");
            strcat(str, "AKDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "AKDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "AKDAUFTRAG.SENDESTATUS, ");
            strcat(str, "AKDAUFTRAG.ZUGRUND, ");
            strcat(str, "AKDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "AKDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "AKDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "AKDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "AKDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "AKDAUFTRAG.ORDERLABEL, ");
            strcat(str, "AKDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "ACSCORDERFLAGS.WAITFORIBTPICKING, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "order by ");
            if (!strcmp(a->SORTFIELD, "kdauftragnr")) strcat(str, "akdauftrag.");
            strcat(str, a->SORTFIELD);
            EXEC SQL prepare dec_Selauftpzn2 from :str;
            EXEC SQL declare Selauftpzn2 scroll cursor with hold for dec_Selauftpzn2;

            if (!strncmp(cCountry, "BG", 2))
            {
                EXEC SQL open Selauftpzn2 using
                    :a->ZEITENDEAM,
                    :a->DATUM,
                    :a->KDAUFTRAGSTAT,
                    :a->GERAETNAME,
                    :a->TOURID,
                    :a->KDAUFTRAGART,
                    :a->KDAUFTRAGNR,
                    :MIN_INVOICE,
                    :MAX_INVOICE,
                    :Vz_von,
                    :Vz_bis,
                    :a->REGIONNR,
                    :MIN_KND,
                    :MAX_KND;
            }
            else
            {
                EXEC SQL open Selauftpzn2 using
                    :a->ZEITENDEAM,
                    :a->DATUM,
                    :a->KDAUFTRAGSTAT,
                    :a->GERAETNAME,
                    :a->TOURID,
                    :a->KDAUFTRAGART,
                    :a->KDAUFTRAGNR,
                    :MIN_RECHNR,
                    :MAX_RECHNR,
                    :Vz_von,
                    :Vz_bis,
                    :a->REGIONNR,
                    :MIN_KND,
                    :MAX_KND;
            }
        }
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauftpzn: open Selauftpzn %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        if (sdatum == 0) EXEC SQL close Selauftpzn;
        else EXEC SQL close Selauftpzn2;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelzurauft: close Selauftpzn %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    if (sdatum == 0) EXEC SQL fetch relative :a->FETCH_REL Selauftpzn
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->WAITFORIBTPICKING,
            :a->NAMEINHABER;
    else EXEC SQL fetch relative :a->FETCH_REL Selauftpzn2
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->WAITFORIBTPICKING,
            :a->NAMEINHABER;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelzurauft: fetch Selauftpzn %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        if (sdatum == 0) EXEC SQL close Selauftpzn;
        else EXEC SQL close Selauftpzn2;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    if (AaauftGetfirstordertime(d, error_msg) < 0) return -1;
    return 0;
}


/*** AAAUFT-GET-ARTKENNZ ******************************************************/

int Aaauft_GetArtKennz(long artikelnr, char* ArtKZ, char* error_msg)
{
    exec sql begin declare section;
    long ETARTSCHALTER1;
    long ETARTSCHALTER2;
    long ETARTSCHALTER3;
    long ETARTSCHALTER4;
    long ETARTSCHALTER5;
    char PRISOART[2];
    long BESTAND;
    long ARTIKELNR;
    exec sql end declare section;
    char* fun = "Aaauft_GetArtKennz";
    int pos;

    ARTIKELNR = artikelnr;
    pos = 0;
    if (ARTIKELNR == 0)
    {
        ArtKZ[pos] = '\0';
        return 0;
    }

    EXEC SQL select
        (ARTIKELZENTRAL.ETARTSCHALTER1 + ARTIKELLOKAL.ETARTSCHALTER1),
        (ARTIKELZENTRAL.ETARTSCHALTER2 + ARTIKELLOKAL.ETARTSCHALTER2),
        (ARTIKELZENTRAL.ETARTSCHALTER3 + ARTIKELLOKAL.ETARTSCHALTER3),
        (ARTIKELZENTRAL.ETARTSCHALTER4 + ARTIKELLOKAL.ETARTSCHALTER4),
        (ARTIKELZENTRAL.ETARTSCHALTER5 + ARTIKELLOKAL.ETARTSCHALTER5),
        ARTIKELLOKAL.PRISOART,
        ARTIKELLOKAL.BESTAND
    into
        :ETARTSCHALTER1,
        :ETARTSCHALTER2,
        :ETARTSCHALTER3,
        :ETARTSCHALTER4,
        :ETARTSCHALTER5,
        :PRISOART,
        :BESTAND
    from artikelzentral, artikellokal
    where   artikelzentral.artikel_nr = :ARTIKELNR
    and artikellokal.artikel_nr = artikelzentral.artikel_nr
    and artikellokal.filialnr = :FilialNr
    ;
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        ArtKZ[pos] = '\0';
        return 0;
    }
    SQLERR( fun, "select etartschalter" )

    for (;;)
    {
        if (AllgBitleisteN((Bitleiste)ETARTSCHALTER1, 0))
        {
            ArtKZ[pos] = '9';       /* Sekundaerbezeichner */
            if (++pos > 5) break;
        }
        if (AllgBitleisteN((Bitleiste)ETARTSCHALTER1, 1))
        {
            ArtKZ[pos] = 'E';       /* Nachfolgeartikel */
            if (++pos > 5) break;
        }
        if (PRISOART[0] != '0')
        {
            if      (PRISOART[0] == '1')
            {
                ArtKZ[pos] = 'S';
                if (++pos > 5) break;
                ArtKZ[pos] = 'L';
                if (++pos > 5) break;
            }
            else if (PRISOART[0] == '2')
            {
                ArtKZ[pos] = 'S';
                if (++pos > 5) break;
                ArtKZ[pos] = 'Z';
                if (++pos > 5) break;
            }
            else if (PRISOART[0] == '3')
            {
                ArtKZ[pos] = 'S';
                if (++pos > 5) break;
                ArtKZ[pos] = 'B';
                if (++pos > 5) break;
            }
        }
        if (AllgBitleisteN((Bitleiste)ETARTSCHALTER1, 3))
        {
            ArtKZ[pos] = 'A';       /* ausser Handel */
            if (++pos > 5) break;
        }
        if (AllgBitleisteN((Bitleiste)ETARTSCHALTER1, 13))
        {
            ArtKZ[pos] = 'G';       /* nicht ueber Grosshandel */
            if (++pos > 5) break;
        }
        if (AllgBitleisteN((Bitleiste)ETARTSCHALTER1, 12))
        {
            ArtKZ[pos] = 'H';       /* vom Hersteller nicht geliefert */
            if (++pos > 5) break;
        }
        if (AllgBitleisteN((Bitleiste)ETARTSCHALTER1, 11))
        {
            ArtKZ[pos] = 'L';       /* vom Hersteller nicht lieferbar */
            if (++pos > 5) break;
        }
        if (AllgBitleisteN((Bitleiste)ETARTSCHALTER1, 6))
        {
            ArtKZ[pos] = 'P';       /* Netto */
            if (++pos > 5) break;
        }
        if (AllgBitleisteN((Bitleiste)ETARTSCHALTER3, 7))
        {
            ArtKZ[pos] = 'N';       /* Natra */
            if (++pos > 5) break;
        }
        if (AllgBitleisteN((Bitleiste)ETARTSCHALTER4, 1))
        {
            ArtKZ[pos] = 'R';       /* Reimport */
            if (++pos > 5) break;
        }
        if (!AllgBitleisteN((Bitleiste)ETARTSCHALTER2, 15)
                               && BESTAND==0)
        {
            ArtKZ[pos] = 'F';       /* Artikel wird nicht gefuehrt */
            if (++pos > 5) break;
        }
        break;
    }
    ArtKZ[pos] = '\0';
    return 0;
}

int AaauftSel_fili_auft_nr(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short Vz_von;
    short Vz_bis;
    long lDatum;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        lDatum = AllgGetDate();
        sdatum = a->DATUM;     /* spaeter extra feld in view */
        datum = a->DATUM;      /* spaeter extra feld in view */
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        ppGStripLast(a->KDAUFTRAGART);
        ppGStripLast(a->TOURID);
        ppGStripLast(a->SORTFIELD);
        if (a->SORTFIELD[0] == '\0') strcpy(a->SORTFIELD, "kdauftragnrfiliale");
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        if (a->DATUM == 0)
        {
            strcpy(str, "select ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "KDAUFTRAG.IDFNR, ");
            strcat(str, "KDAUFTRAG.GERAETNAME, ");
            strcat(str, "KDAUFTRAG.TOURID, ");
            strcat(str, "KDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "KDAUFTRAG.KOART, ");
            strcat(str, "KDAUFTRAG.BUCHART, ");
            strcat(str, "KDAUFTRAG.ANZPOS, ");
            strcat(str, "KDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "KDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "KDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "KDAUFTRAG.ANZPOSOB, ");
            strcat(str, "KDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "KDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "KDAUFTRAG.SENDESTATUS, ");
            strcat(str, "KDAUFTRAG.ZUGRUND, ");
            strcat(str, "KDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "KDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "KDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "KDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "KDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "KDAUFTRAG.ORDERLABEL, ");
            strcat(str, "KDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "CSCORDERFLAGS.WAITFORIBTPICKING, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "from kdauftrag, kunde, cscorderflags ");
            strcat(str, "where kdauftrag.kdauftragstat like ? and ");
            strcat(str, "kdauftrag.geraetname like ? and ");
            strcat(str, "kdauftrag.tourid like ? and ");
            strcat(str, "kdauftrag.kdauftragart like ? and ");
            strcat(str, "kdauftrag.kdauftragnrfiliale >= ? and ");
            strcat(str, "kdauftrag.vertriebszentrumnr >= ? and ");
            strcat(str, "kdauftrag.vertriebszentrumnr <= ? and ");
            strcat(str, "(kdauftrag.datumauslieferung <= ? or ");
            strcat(str, "kdauftrag.datumauslieferung = 0 ) and ");
            strcat(str, "kunde.kundennr = kdauftrag.kundennr and ");
            strcat(str, "kunde.vertriebszentrumnr = kdauftrag.vertriebszentrumnr and ");
            strcat(str, "cscorderflags.cscorderno = kdauftrag.kdauftragnr and ");
            strcat(str, "kdauftrag.vertriebszentrumnr in ( ");
            strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
            strcat(str, "where  RegionArten.RegionNr = ? and ");
            strcat(str, "RegionArten.RegionenTyp=1) ");
            strcat(str, "order by ");
            strcat(str, a->SORTFIELD);
            EXEC SQL prepare dec_Selfilauft from :str;
            EXEC SQL declare Selfilauft scroll cursor with hold for dec_Selfilauft;

            EXEC SQL open Selfilauft using
                :a->KDAUFTRAGSTAT,
                :a->GERAETNAME,
                :a->TOURID,
                :a->KDAUFTRAGART,
                :a->KDAUFTRAGNRFILIALE,
                :Vz_von,
                :Vz_bis,
                :lDatum,
                :a->REGIONNR;
        }
        else
        {
            strcpy(str, "select ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "AKDAUFTRAG.IDFNR, ");
            strcat(str, "AKDAUFTRAG.GERAETNAME, ");
            strcat(str, "AKDAUFTRAG.TOURID, ");
            strcat(str, "AKDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "AKDAUFTRAG.KOART, ");
            strcat(str, "AKDAUFTRAG.BUCHART, ");
            strcat(str, "AKDAUFTRAG.ANZPOS, ");
            strcat(str, "AKDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "AKDAUFTRAG.ANZPOSOB, ");
            strcat(str, "AKDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "AKDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "AKDAUFTRAG.SENDESTATUS, ");
            strcat(str, "AKDAUFTRAG.ZUGRUND, ");
            strcat(str, "AKDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "AKDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "AKDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "AKDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "AKDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "AKDAUFTRAG.ORDERLABEL, ");
            strcat(str, "AKDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "ACSCORDERFLAGS.WAITFORIBTPICKING, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "from akdauftrag, kunde, acscorderflags ");
            strcat(str, "where akdauftrag.kdauftragstat like ? and ");
            strcat(str, "akdauftrag.datum = ? and ");
            strcat(str, "akdauftrag.geraetname like ? and ");
            strcat(str, "akdauftrag.tourid like ? and ");
            strcat(str, "akdauftrag.kdauftragart like ? and ");
            strcat(str, "akdauftrag.kdauftragnrfiliale >= ? and ");
            strcat(str, "akdauftrag.vertriebszentrumnr >= ? and ");
            strcat(str, "akdauftrag.vertriebszentrumnr <= ? and ");
            strcat(str, "kunde.kundennr = akdauftrag.kundennr and ");
            strcat(str, "kunde.vertriebszentrumnr = akdauftrag.vertriebszentrumnr and ");
            strcat(str, "acscorderflags.cscorderno = akdauftrag.kdauftragnr and ");
            strcat(str, "acscorderflags.datum = akdauftrag.datum and ");
            strcat(str, "akdauftrag.vertriebszentrumnr in ( ");
            strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
            strcat(str, "where  RegionArten.RegionNr = ? and ");
            strcat(str, "RegionArten.RegionenTyp=1) ");
            strcat(str, "order by ");
            strcat(str, a->SORTFIELD);
            EXEC SQL prepare dec_Selfilauft2 from :str;
            EXEC SQL declare Selfilauft2 scroll cursor with hold for dec_Selfilauft2;

            EXEC SQL open Selfilauft2 using
                :a->KDAUFTRAGSTAT,
                :a->DATUM,
                :a->GERAETNAME,
                :a->TOURID,
                :a->KDAUFTRAGART,
                :a->KDAUFTRAGNRFILIALE,
                :Vz_von,
                :Vz_bis,
                :a->REGIONNR;
        }
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_fili_auft_nr: open Selfilauft %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        if (sdatum == 0) EXEC SQL close Selfilauft;
        else EXEC SQL close Selfilauft2;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_fili_auft_nr: close Selfilauft %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    if (sdatum == 0) EXEC SQL fetch relative :a->FETCH_REL Selfilauft
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->WAITFORIBTPICKING,
            :a->NAMEINHABER;
    else EXEC SQL fetch relative :a->FETCH_REL Selfilauft2
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->WAITFORIBTPICKING,
            :a->NAMEINHABER;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelzurauft: fetch Selfilauft %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        if (sdatum == 0)    EXEC SQL close Selfilauft;
        else    EXEC SQL close Selfilauft2;
            return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    if (AaauftGetfirstordertime(d, error_msg) < 0) return -1;
    return 0;
}

int AaauftCheck_auftnr(struct AUFIE* d, char* error_msg)
{
    exec sql begin declare section;
    struct AUFIE* a;
    exec sql end declare section;

    a = d;
    exec sql select kdauftragnr from kdauftag where  kdauftragnr = :a->ANZ_IE
        and vertriebszentrumnr = :a->VERTRIEBSZENTRUMNR;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftCheck_auftnr: Select Kdauftrag %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    else if (sqlca.sqlcode == SQLNOTFOUND )
    {
        return 1;
    }

    return 0;
}

int AaauftSel_valutatage(struct AUFARTES* d, char* error_msg)
{
    exec sql begin declare section;
    struct AUFARTES* a;
    exec sql end declare section;

    a = d;

    EXEC SQL select valutatagemax into :a->VALUTAMONATE from kundekondi
        where   kundekondi.kundennr             =   :a->KUNDENNR
        and     kundekondi.vertriebszentrumnr   =   :a->VERTRIEBSZENTRUMNR;
    if (sqlca.sqlcode < 0 )
    {
        sprintf(error_msg, " AaauftSel_valutatage: Select valutatagemax %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
    if (a->VALUTAMONATE == 0) return 1;

    return 0;
}

int AaauftSelzurauftDD(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    long MIN_RECHNR;
    long MAX_RECHNR;
    char MIN_INVOICE[16];
    char MAX_INVOICE[16];
    short Vz_von;
    short Vz_bis;
    long lKnd_von;
    long lKnd_bis;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        sdatum = a->DATUM;     /* spaeter extra feld in view */
        datum = a->DATUM;      /* spaeter extra feld in view */
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        ppGStripLast(a->TOURID);
        ppGStripLast(a->KDAUFTRAGART);
        ppGStripLast(a->SORTFIELD);
        ppGStripLast(a->INVOICENUMBER);
        if (a->SORTFIELD[0] == '\0') strcpy(a->SORTFIELD, "kdauftragnr");
        if (a->ANZPOS == 0) /* nase keine Rechnungsnummer mitgegeben */
        {
            MIN_RECHNR = 0;
            MAX_RECHNR = 2147483647;
        }
        else
        {
            MIN_RECHNR = a->ANZPOS;
            MAX_RECHNR = a->ANZPOS;
        }
        if (a->INVOICENUMBER[0] == '\0') /* nase keine Rechnungsnummer mitgegeben */
        {
            strcpy(MIN_INVOICE, " ");
            strcpy(MAX_INVOICE, "999999999999999");
        }
        else
        {
            strcpy(MIN_INVOICE, a->INVOICENUMBER);
            strcpy(MAX_INVOICE, a->INVOICENUMBER);
        }
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        if (a->KUNDENNR == 0) /* nase alle Kunden */
        {
            lKnd_von = 0;
            lKnd_bis = 9999999;
        }
        else
        {
            lKnd_von = a->KUNDENNR;
            lKnd_bis = a->KUNDENNR;
        }
        if (a->DATUM == 0)
        {
            strcpy(str, "select ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "KDAUFTRAG.IDFNR, ");
            strcat(str, "KDAUFTRAG.GERAETNAME, ");
            strcat(str, "KDAUFTRAG.TOURID, ");
            strcat(str, "KDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "KDAUFTRAG.KOART, ");
            strcat(str, "KDAUFTRAG.BUCHART, ");
            strcat(str, "KDAUFTRAG.ANZPOS, ");
            strcat(str, "KDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "KDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "KDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "KDAUFTRAG.ANZPOSOB, ");
            strcat(str, "KDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "KDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "KDAUFTRAG.SENDESTATUS, ");
            strcat(str, "KDAUFTRAG.ZUGRUND, ");
            strcat(str, "KDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "KDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "KDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "KDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "KDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "KDAUFTRAG.ORDERLABEL, ");
            strcat(str, "KDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "from kdauftrag, kunde ");
            strcat(str, "where kdauftrag.kdauftragstat like ? and ");
            strcat(str, "kdauftrag.geraetname like ? and ");
            strcat(str, "kdauftrag.tourid like ? and ");
            strcat(str, "kdauftrag.kdauftragart like ? and ");
            strcat(str, "kdauftrag.kdauftragnr >= ? and ");
            strcat(str, "kdauftrag.vertriebszentrumnr >= ? and ");
            strcat(str, "kdauftrag.vertriebszentrumnr <= ? and ");
            if (!strncmp(cCountry, "BG", 2))
            {
                strcat(str, "kdauftrag.invoicenumber >= ? and ");
                strcat(str, "kdauftrag.invoicenumber <= ? and ");
            }
            else
            {
                strcat(str, "kdauftrag.rechnungnr >= ? and ");
                strcat(str, "kdauftrag.rechnungnr <= ? and ");
            }
            strcat(str, "kdauftrag.datumauslieferung >= ? and ");
            strcat(str, "kunde.kundennr >= ? and ");
            strcat(str, "kunde.kundennr <= ? and ");
            strcat(str, "kunde.kundennr = kdauftrag.kundennr and ");
            strcat(str, "kunde.vertriebszentrumnr = kdauftrag.vertriebszentrumnr and ");
            strcat(str, "kdauftrag.vertriebszentrumnr in ( ");
            strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
            strcat(str, "where  RegionArten.RegionNr = ? and ");
            strcat(str, "RegionArten.RegionenTyp=1) ");
            strcat(str, "order by datumauslieferung, ");
            strcat(str, a->SORTFIELD);
            EXEC SQL prepare dec_SelzurauftDD from :str;
            EXEC SQL declare SelzurauftDD scroll cursor with hold for dec_SelzurauftDD;

            if (!strncmp(cCountry, "BG", 2))
            {
                EXEC SQL open SelzurauftDD using
                    :a->KDAUFTRAGSTAT,
                    :a->GERAETNAME,
                    :a->TOURID,
                    :a->KDAUFTRAGART,
                    :a->KDAUFTRAGNR,
                    :Vz_von,
                    :Vz_bis,
                    :MIN_INVOICE,
                    :MAX_INVOICE,
                    :a->DATUMAUSLIEFERUNG,
                    :lKnd_von,
                    :lKnd_bis,
                    :a->REGIONNR;
            }
            else
            {
                EXEC SQL open SelzurauftDD using
                    :a->KDAUFTRAGSTAT,
                    :a->GERAETNAME,
                    :a->TOURID,
                    :a->KDAUFTRAGART,
                    :a->KDAUFTRAGNR,
                    :Vz_von,
                    :Vz_bis,
                    :MIN_RECHNR,
                    :MAX_RECHNR,
                    :a->DATUMAUSLIEFERUNG,
                    :lKnd_von,
                    :lKnd_bis,
                    :a->REGIONNR;
            }
        }
        else
        {
            strcpy(str, "select ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "AKDAUFTRAG.IDFNR, ");
            strcat(str, "AKDAUFTRAG.GERAETNAME, ");
            strcat(str, "AKDAUFTRAG.TOURID, ");
            strcat(str, "AKDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "AKDAUFTRAG.KOART, ");
            strcat(str, "AKDAUFTRAG.BUCHART, ");
            strcat(str, "AKDAUFTRAG.ANZPOS, ");
            strcat(str, "AKDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KUNDE.NAMEAPO, ");
            strcat(str, "KUNDE.KZKDKLASSE, ");
            strcat(str, "AKDAUFTRAG.ANZPOSOB, ");
            strcat(str, "AKDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KUNDE.ORT, ");
            strcat(str, "AKDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "AKDAUFTRAG.SENDESTATUS, ");
            strcat(str, "AKDAUFTRAG.ZUGRUND, ");
            strcat(str, "AKDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "AKDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "AKDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "AKDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "AKDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "AKDAUFTRAG.ORDERLABEL, ");
            strcat(str, "AKDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "KUNDE.NAMEINHABER ");
            strcat(str, "from akdauftrag, kunde ");
            strcat(str, "where akdauftrag.kdauftragstat like ? and ");
            strcat(str, "akdauftrag.datum = ? and ");
            strcat(str, "akdauftrag.geraetname like ? and ");
            strcat(str, "akdauftrag.tourid like ? and ");
            strcat(str, "akdauftrag.kdauftragart like ? and ");
            strcat(str, "akdauftrag.kdauftragnr >= ? and ");
            strcat(str, "akdauftrag.vertriebszentrumnr >= ? and ");
            strcat(str, "akdauftrag.vertriebszentrumnr <= ? and ");
            if (!strncmp(cCountry, "BG", 2))
            {
                strcat(str, "akdauftrag.invoicenumber >= ? and ");
                strcat(str, "akdauftrag.invoicenumber <= ? and ");
            }
            else
            {
                strcat(str, "akdauftrag.rechnungnr >= ? and ");
                strcat(str, "akdauftrag.rechnungnr <= ? and ");
            }
            strcat(str, "akdauftrag.datumauslieferung >= ? and ");
            strcat(str, "kunde.kundennr >= ? and ");
            strcat(str, "kunde.kundennr <= ? and ");
            strcat(str, "kunde.kundennr = akdauftrag.kundennr and ");
            strcat(str, "kunde.vertriebszentrumnr = akdauftrag.vertriebszentrumnr and ");
            strcat(str, "akdauftrag.vertriebszentrumnr in ( ");
            strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
            strcat(str, "where  RegionArten.RegionNr = ? and ");
            strcat(str, "RegionArten.RegionenTyp=1) ");
            strcat(str, "order by datumauslieferung, ");
            strcat(str, a->SORTFIELD);
            EXEC SQL prepare dec_SelzurauftDD2 from :str;
            EXEC SQL declare SelzurauftDD2 scroll cursor with hold for dec_SelzurauftDD2;

            if (!strncmp(cCountry, "BG", 2))
            {
                EXEC SQL open SelzurauftDD2 using
                    :a->KDAUFTRAGSTAT,
                    :a->DATUM,
                    :a->GERAETNAME,
                    :a->TOURID,
                    :a->KDAUFTRAGART,
                    :a->KDAUFTRAGNR,
                    :Vz_von,
                    :Vz_bis,
                    :MIN_INVOICE,
                    :MAX_INVOICE,
                    :a->DATUMAUSLIEFERUNG,
                    :lKnd_von,
                    :lKnd_bis,
                    :a->REGIONNR;
            }
            else
            {
                EXEC SQL open SelzurauftDD2 using
                    :a->KDAUFTRAGSTAT,
                    :a->DATUM,
                    :a->GERAETNAME,
                    :a->TOURID,
                    :a->KDAUFTRAGART,
                    :a->KDAUFTRAGNR,
                    :Vz_von,
                    :Vz_bis,
                    :MIN_RECHNR,
                    :MAX_RECHNR,
                    :a->DATUMAUSLIEFERUNG,
                    :lKnd_von,
                    :lKnd_bis,
                    :a->REGIONNR;
            }
        }
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauft: open SelzurauftDD %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        if (sdatum == 0) EXEC SQL close SelzurauftDD;
        else EXEC SQL close SelzurauftDD2;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelzurauft: close SelzurauftDD %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    if (sdatum == 0) EXEC SQL fetch relative :a->FETCH_REL SelzurauftDD
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->NAMEINHABER;
    else EXEC SQL fetch relative :a->FETCH_REL SelzurauftDD2
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->NAMEINHABER;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelzurauft: fetch SelzurauftDD %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        if (sdatum == 0) EXEC SQL close SelzurauftDD;
        else EXEC SQL close SelzurauftDD2;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    if (AaauftGetfirstordertime(d, error_msg) < 0) return -1;
    return 0;
}

/*** AAAUFT-SEL-VBBUCH ******************************************************/

int Aaauft_Sel_vbmoegl(struct N_VBBUCH* d, char* error_msg)
{
    static int fst = 1;
    static int C1Open = 0;
    static int C2Open = 0;
    static int FREMDSPRACHE_ALT = 2;
    static int iNLevelIBT;
    char cFiliale[3];
    char cWeekday[2];
    char cTime[7];

    exec sql begin declare section;
    struct N_VBBUCH* a;
    long lTime;
    char tagtyp[3];
    short sWeekday;
    int iCountPos;
    char cVbfil[17];
    long lBestand;
    long lArtikelNr;
    exec sql end declare section;

    int i;
    char* fun = "Aaauft_Sel_vbmoegl";

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        iNLevelIBT = a->BESTAND;
        exec sql drop table defart_temp; /* sqlcode wird ignoriert, falls temptable noch nicht besteht */
        exec sql drop table vbidf_temp; /* sqlcode wird ignoriert, falls temptable noch nicht besteht */
        exec sql drop table vbart_temp; /* sqlcode wird ignoriert, falls temptable noch nicht besteht */
        exec sql drop table defartikel_temp; /* sqlcode wird ignoriert, falls temptable noch nicht besteht */
        exec sql drop table t_vbfils; /* sqlcode wird ignoriert, falls temptable noch nicht besteht */

        sWeekday = ppGGetWeekDay(ppGGetDate(), error_msg);
        lTime = ppGGetTime();
        sprintf(cWeekday, "'%d'", sWeekday);
        sprintf(cTime, "'%d'", lTime);

        exec sql select count(unique rechner.datenbank_name) into :iCountPos
            from zeitarten, ibtbranches, rechner
        where
            zeitarten.vertriebszentrumnr = :a->FILIALNR and
            zeitarten.zeitart = 2 and
            zeitarten.weekday = :sWeekday and
            zeitarten.zeitbegin <= :lTime and
            zeitarten.zeitende >= :lTime and
            ibtbranches.branchno = :a->FILIALNR and
            ibtbranches.ibtbranchno = zeitarten.zeitschluessel and
            ibtbranches.active_flag = 1 and
            (rechner.filialnr = ibtbranches.ibtbranchno
            or rechner.filialnr = :a->FILIALNR );
        SQLERR( fun, "Check Verbund" )

        if (iCountPos == 0)  /* kein Verbund mehr */
        {
            return 1;
        }

        exec sql select artikel_nr,
                    max(kdauftrag.kdauftragnr) kdauftragnr
                   from kdauftrag, kdauftragpos
                  where kdauftrag.kdauftragnr = kdauftragpos.kdauftragnr
                    and kdauftrag.kdauftragstat[10] = "0"
                    and kdauftrag.idfnr = :a->ARTIKEL_NR
                    and kdauftrag.vertriebszentrumnr = :a->FILIALNR
                    group by artikel_nr
                   into temp vbart_temp with no log;
        SQLERR( fun, "select into temp vbart_temp" )
        exec sql select kdauftragpos.artikel_nr
                   from kdauftrag, kdauftragpos, vbart_temp
                  where kdauftrag.kdauftragnr = kdauftragpos.kdauftragnr
                    and kdauftrag.kdauftragstat[10] = "0"
                    and kdauftrag.idfnr = :a->ARTIKEL_NR
                    and kdauftrag.vertriebszentrumnr = :a->FILIALNR
                    and kdauftragpos.bemerkungen = "Verbund"
                    and kdauftrag.kdauftragnr = vbart_temp.kdauftragnr
                    and kdauftragpos.artikel_nr = vbart_temp.artikel_nr
                   into temp vbidf_temp with no log;
        exec sql insert into vbidf_temp (artikel_nr) values (0);    /* dass wenigstens einSatz drin steht */
        SQLERR( fun, "select into temp vbidf_temp" )

        exec sql select
            KDAUFTRAGPOS.MENGEBESTELLT,
            KDAUFTRAGPOS.MENGEBESTAETIGT,
            KDAUFTRAGPOS.MENGENATRA,
            KDAUFTRAGPOS.BEMERKUNGEN,
            KDAUFTRAGPOS.ARTIKEL_NR
        from
            KDAUFTRAG,
            KDAUFTRAGPOS
        where
            kdauftrag.vertriebszentrumnr = :a->FILIALNR and
            kdauftrag.kundennr = :a->ARTIKEL_NR and
            kdauftrag.kdauftragstat[10] = '0' and
            kdauftragpos.kdauftragnr = kdauftrag.kdauftragnr and
            trunc( kdauftragpos.etposschalter2/256)-2 *
                trunc( kdauftragpos.etposschalter2/(256*2)) = 0 and /* keine verzögerten */
            trunc( kdauftragpos.etposschalter2/32)-2 *
                trunc( kdauftragpos.etposschalter2/(32*2)) = 0 and  /* keine gesplitteten */
            kdauftragpos.mengebestellt > kdauftragpos.mengebestaetigt and
            kdauftragpos.artikel_nr not in
            (select vbidf_temp.artikel_nr from vbidf_temp)
        into temp defartikel_temp with no log;
        SQLERR( fun, "select into temp defartikel_temp" )

        exec sql select
            MENGEBESTELLT,
            MENGEBESTAETIGT,
            MENGENATRA,
            BEMERKUNGEN,
            ARTIKEL_NR
        from
            defartikel_temp
        where
            ARTIKEL_NR not in
            (select articlequota.articleno from articlequota
            where articlequota.branchno = :a->FILIALNR
            and articlequota.customerno = :a->ARTIKEL_NR
            and (articlequota.kumqty - articlequota.quota) = 0)
        into temp defart_temp with no log;
        SQLERR( fun, "select into temp defart_temp" )

        FREMDSPRACHE_ALT = FREMDSPRACHE;
        EXEC SQL free dec_vbdefekt;
        EXEC SQL free CSelVerbundDefekte;

        if (iNLevelIBT == 0)
        {
            strcpy(str, "select ");
            strcat(str, "zeitarten.zeitschluessel ");
            strcat(str, "from ");
            strcat(str, "zeitarten, ibtbranches ");
            strcat(str, "where ");
            strcat(str, "zeitarten.vertriebszentrumnr = ? and ");
            strcat(str, "zeitarten.zeitart = 2 and ");
            strcat(str, "zeitarten.weekday = ? and ");
            strcat(str, "zeitarten.zeitbegin <= ? and ");
            strcat(str, "zeitarten.zeitende >= ? and ");
            strcat(str, "ibtbranches.branchno = ? and ");
            strcat(str, "ibtbranches.ibtbranchno = zeitarten.zeitschluessel and ");
            strcat(str, "ibtbranches.active_flag = 1 ");

            EXEC SQL PREPARE dec_SelVbfils FROM :str;
            SQLERR( fun, "prepare dec_SelVbfils" )
            exec sql declare CSelVbfils scroll cursor with hold for dec_SelVbfils;
            SQLERR( fun, "declare CSelVbfils" )
            exec sql open CSelVbfils using :a->FILIALNR, :sWeekday, :lTime, :lTime, :a->FILIALNR;
            SQLERR( fun, "open CSelVbfils" )
        }

        exec sql declare CSelDefart scroll cursor with hold for
        select
            artikel_nr,
            MENGEBESTELLT-MENGEBESTAETIGT
        from
            defart_temp;
        SQLERR( fun, "declare CSelDefart" )
        exec sql open CSelDefart;
        SQLERR( fun, "open CSelDefart" )
        C1Open = 1;

        if (FREMDSPRACHE)
        {
            strcpy(str, "select ");
            strcat(str, "defart_temp.MENGEBESTELLT, ");
            strcat(str, "defart_temp.MENGEBESTAETIGT, ");
            strcat(str, "defart_temp.MENGENATRA, ");
            strcat(str, "defart_temp.BEMERKUNGEN, ");
            strcat(str, "z.ARTIKEL_NR, ");
            strcat(str, "nvl(c.DARREICHFORM, z.DARREICHFORM), ");
            strcat(str, "nvl(c.EINHEIT, z.EINHEIT), ");
            strcat(str, "nvl(c.ARTIKEL_NAME, z.ARTIKEL_NAME), ");
            strcat(str, "lok.FILIALNR, ");
            strcat(str, "lok.BESTAND, ");
            strcat(str, "z.PRODUSERQUOTA ");
            strcat(str, "from ");
            strcat(str, "defart_temp, ");
            strcat(str, "ARTIKELZENTRAL z, ");
            strcat(str, "ARTIKELLOKAL lok, ");
            if (iNLevelIBT == 1)
            {
                strcat(str, "IBTBRANCHARTICLECONFIG ibt, ");
            }
            strcat(str, "outer ");
            strcat(str, ARTIKELZENTRAL_SPRACHE);
            strcat(str, " c ");
            strcat(str, "where ");
            strcat(str, "defart_temp.artikel_nr = ? and ");
            strcat(str, "z.artikel_nr = ? and ");
            strcat(str, "c.artikel_nr = ? and ");
            strcat(str, "lok.artikel_nr = ? and ");
            if (iNLevelIBT == 1)
            {
                strcat(str, "ibt.ibttypeid != '0' and ");
                sprintf(cFiliale, "'%d'", a->FILIALNR);
                strcat(str, "ibt.branchno = ");
                strcat(str, cFiliale);
                strcat(str, " and ");
                strcat(str, "ibt.articleno = z.artikel_nr and ");
            }
            else
            {
                strcat(str, "lok.verbundartikel != '0' and ");
            }
            strcat(str, "lok.bestand >= ? and ");
            strcat(str, "lok.filialnr in ( ");
            if (iNLevelIBT == 1)
            {
                strcat(str, "select ");
                strcat(str, "zeitarten.zeitschluessel ");
                strcat(str, "from ");
                strcat(str, "zeitarten, ibtbranches ");
                strcat(str, "where ");
                strcat(str, "zeitarten.vertriebszentrumnr = ");
                strcat(str, cFiliale);
                strcat(str, " and ");
                strcat(str, "zeitarten.zeitart = '2' and ");
                strcat(str, "zeitarten.weekday = ");
                strcat(str, cWeekday);
                strcat(str, " and ");
                strcat(str, "zeitarten.zeitbegin <= ");
                strcat(str, cTime);
                strcat(str, " and ");
                strcat(str, "zeitarten.zeitende >= ");
                strcat(str, cTime);
                strcat(str, " and ");
                strcat(str, "ibtbranches.branchno = zeitarten.vertriebszentrumnr and ");
                strcat(str, "ibtbranches.ibtbranchno = zeitarten.zeitschluessel and ");
                strcat(str, "ibtbranches.active_flag = '1' and ");
                strcat(str, "ibtbranches.nlevelibttypeid = ibt.ibttypeid ");
            }
            else
            {
                for (i = 0;; i++)
                {
                    exec sql fetch CSelVbfils into :cVbfil;
                    SQLERR( fun, "fetch CSelVbfils" )
                    if (sqlca.sqlcode == SQLNOTFOUND) break;
                    if (i > 0) strcat(str, ", ");
                    strcat(str, "'");
                    strcat(str, cVbfil);
                    strcat(str, "'");
                }
            }
            strcat(str, ") ");
            strcat(str, "order by lok.bestand desc, defart_temp.mengebestellt desc ");
        }
        else
        {
            strcpy(str, "select ");
            strcat(str, "defart_temp.MENGEBESTELLT, ");
            strcat(str, "defart_temp.MENGEBESTAETIGT, ");
            strcat(str, "defart_temp.MENGENATRA, ");
            strcat(str, "defart_temp.BEMERKUNGEN, ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_NR, ");
            strcat(str, "ARTIKELZENTRAL.DARREICHFORM, ");
            strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
            strcat(str, "lok.FILIALNR, ");
            strcat(str, "lok.BESTAND, ");
            strcat(str, "ARTIKELZENTRAL.PRODUSERQUOTA ");
            strcat(str, "from ");
            strcat(str, "defart_temp, ");
            strcat(str, "ARTIKELZENTRAL, ");
            if (iNLevelIBT == 1)
            {
                strcat(str, "IBTBRANCHARTICLECONFIG ibt, ");
            }
            strcat(str, "ARTIKELLOKAL lok ");
            strcat(str, "where ");
            strcat(str, "defart_temp.artikel_nr = ? and ");
            strcat(str, "artikelzentral.artikel_nr = ? and ");
            strcat(str, "lok.artikel_nr = ? and ");
            if (iNLevelIBT == 1)
            {
                strcat(str, "ibt.ibttypeid != '0' and ");
                sprintf(cFiliale, "'%d'", a->FILIALNR);
                strcat(str, "ibt.branchno = ");
                strcat(str, cFiliale);
                strcat(str, " and ");
                strcat(str, "ibt.articleno = artikelzentral.artikel_nr and ");
            }
            else
            {
                strcat(str, "lok.verbundartikel != '0' and ");
            }
            strcat(str, "lok.bestand >= ? and ");
            strcat(str, "lok.filialnr in ( ");
            if (iNLevelIBT == 1)
            {
                strcat(str, "select ");
                strcat(str, "zeitarten.zeitschluessel ");
                strcat(str, "from ");
                strcat(str, "zeitarten, ibtbranches ");
                strcat(str, "where ");
                strcat(str, "zeitarten.vertriebszentrumnr = ");
                strcat(str, cFiliale);
                strcat(str, " and ");
                strcat(str, "zeitarten.zeitart = '2' and ");
                strcat(str, "zeitarten.weekday = ");
                strcat(str, cWeekday);
                strcat(str, " and ");
                strcat(str, "zeitarten.zeitbegin <= ");
                strcat(str, cTime);
                strcat(str, " and ");
                strcat(str, "zeitarten.zeitende >= ");
                strcat(str, cTime);
                strcat(str, " and ");
                strcat(str, "ibtbranches.branchno = zeitarten.vertriebszentrumnr and ");
                strcat(str, "ibtbranches.ibtbranchno = zeitarten.zeitschluessel and ");
                strcat(str, "ibtbranches.active_flag = '1' and ");
                strcat(str, "ibtbranches.nlevelibttypeid = ibt.ibttypeid ");
            }
            else
            {
                for (i = 0;; i++)
                {
                    exec sql fetch CSelVbfils into :cVbfil;
                    SQLERR( fun, "fetch CSelVbfils" )
                    if (sqlca.sqlcode == SQLNOTFOUND) break;
                    if (i > 0) strcat(str, ", ");
                    strcat(str, "'");
                    strcat(str, cVbfil);
                    strcat(str, "'");
                }
            }
            strcat(str, ") ");
            strcat(str, "order by lok.bestand desc, defart_temp.mengebestellt desc ");
        }

        EXEC SQL PREPARE dec_vbdefekt FROM :str;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " Aaauft_Sel_vbmoegl: declare dec_vbdefekt %ld %ld",
                    sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        exec sql declare CSelVerbundDefekte scroll cursor with hold for dec_vbdefekt;
        SQLERR( fun, "declare CSelVerbundDefekte" )
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        if (C1Open)  exec sql close CSelDefart;
        SQLERR( fun, "close CSelDefart" )
        if (C2Open) EXEC SQL close CSelVerbundDefekte;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSel_vbbuch: close CSelVerbundDefekte %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        exec sql drop table vbidf_temp; /* sqlcode wird ignoriert, falls temptable noch nicht besteht */
        exec sql drop table vbart_temp; /* sqlcode wird ignoriert, falls temptable noch nicht besteht */
        exec sql drop table defart_temp; /* sqlcode wird ignoriert, falls temptable noch nicht besteht */
        exec sql drop table defartikel_temp; /* sqlcode wird ignoriert, falls temptable noch nicht besteht */
        exec sql drop table t_vbfils; /* sqlcode wird ignoriert, falls temptable noch nicht besteht */
        fst = 1;
        C1Open = 0;
        C2Open = 0;
        return 1;
    }
    for (;;)
    {
        exec sql fetch CSelDefart
        into
            :lArtikelNr,
            :lBestand;
        SQLERR( fun, "fetch CSelDefart" )
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            return 1;
        }
        if (FREMDSPRACHE)
        {
            exec sql open CSelVerbundDefekte
            using
                :lArtikelNr,
                :lArtikelNr,
                :lArtikelNr,
                :lArtikelNr,
                :lBestand;
            SQLERR( fun, "open CSelVerbundDefekte" )
            C2Open = 1;
        }
        else
        {
            exec sql open CSelVerbundDefekte
            using
                :lArtikelNr,
                :lArtikelNr,
                :lArtikelNr,
                :lBestand;
            SQLERR( fun, "open CSelVerbundDefekte" )
            C2Open = 1;
        }

        EXEC SQL fetch CSelVerbundDefekte
            into
                :a->MENGEBESTELLT,
                :a->MENGEBESTAETIGT,
                :a->MENGENATRA,
                :a->BEMERKUNGEN,
                :a->ARTIKEL_NR,
                :a->DARREICHFORM,
                :a->EINHEIT,
                :a->ARTIKEL_NAME,
                :a->FILIALNR,
                :a->BESTAND,
                :a->PRODUSERQUOTA
            ;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSel_vbbuch: fetch CSelVerbundDefekte %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close CSelVerbundDefekte;
            return -1;
        }
        if (sqlca.sqlcode == 0)
        {
            break;
        }
    }
    Aaauft_GetArtKennz(a->ARTIKEL_NR, a->KURZBEZKONDI, error_msg);

    return 0;
}

int AaauftSelzurauft_o_kdklasse(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short Vz_von;
    short Vz_bis;
    long lDatum;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        lDatum = AllgGetDate();
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        EXEC SQL declare Selzurauft_o_kdklasse scroll cursor with hold for
            select
                KDAUFTRAG.KDAUFTRAGNR,
                KDAUFTRAG.KDAUFTRAGSTAT,
                KDAUFTRAG.IDFNR,
                KDAUFTRAG.GERAETNAME,
                KDAUFTRAG.TOURID,
                KDAUFTRAG.ETAUFTRAGSCHALTER2,
                KDAUFTRAG.KDAUFTRAGART,
                KDAUFTRAG.KOART,
                KDAUFTRAG.BUCHART,
                KDAUFTRAG.ANZPOS,
                KDAUFTRAG.ANZPOSDAFUE,
                KDAUFTRAG.ZEITENDEAM,
                KDAUFTRAG.ZEITENDEPM,
                KUNDE.NAMEAPO,
                KUNDE.KZKDKLASSE,
                KDAUFTRAG.ANZPOSOB,
                KDAUFTRAG.ANZALPHATEXT,
                KUNDE.ORT,
                KDAUFTRAG.VERTRIEBSZENTRUMNR,
                KDAUFTRAG.KDAUFTRAGNRFILIALE,
                KDAUFTRAG.SENDESTATUS,
                KDAUFTRAG.ZUGRUND,
                KDAUFTRAG.DATUMAUSLIEFERUNG,
                KDAUFTRAG.RECHNUNGNR,
                KDAUFTRAG.INVOICENUMBER,
                KDAUFTRAG.PAYMENTDATE,
                KDAUFTRAG.PAYMENTTYPE,
                KDAUFTRAG.ORDERLABEL,
                KDAUFTRAG.ORDERPERIODID,
                KUNDE.NAMEINHABER
            from kdauftrag, kunde, cscorderflags
            where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT and
                    kdauftrag.geraetname            like :a->GERAETNAME and
                    kdauftrag.vertriebszentrumnr    >=   :Vz_von   and
                    kdauftrag.vertriebszentrumnr    <=   :Vz_bis   and
                    (kdauftrag.datumauslieferung    <=  :lDatum    or
                    kdauftrag.datumauslieferung    =    0      )    and
                    kunde.kundennr                  =    kdauftrag.kundennr and
                    kunde.vertriebszentrumnr        =    kdauftrag.vertriebszentrumnr and
                    cscorderflags.cscorderno = kdauftrag.kdauftragnr and
                    cscorderflags.waitforibtpicking != 1 and
                    kdauftrag.vertriebszentrumnr in (
                        select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr= :a->REGIONNR and
                               RegionArten.RegionenTyp=1)
            and kdauftrag.zugrund like :a->ZUGRUND
            order by kzkdklasse;

        EXEC SQL open Selzurauft_o_kdklasse;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauft_o_kdklasse: open Selzurauft_o_kdklasse %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
            }
        }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Selzurauft_o_kdklasse;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelzurauft_o_kdklasse: close Selzurauft_o_kdklasse %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Selzurauft_o_kdklasse
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->NAMEINHABER;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelzurauft_o_kdklasse: fetch Selzurauft_o_kdklasse %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Selzurauft_o_kdklasse;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    return 0;
}

int AaauftSelzurauft_o_pos(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short Vz_von;
    short Vz_bis;
    long lDatum;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        lDatum = AllgGetDate();
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        EXEC SQL declare Selzurauft_o_pos scroll cursor with hold for
            select
                KDAUFTRAG.KDAUFTRAGNR,
                KDAUFTRAG.KDAUFTRAGSTAT,
                KDAUFTRAG.IDFNR,
                KDAUFTRAG.GERAETNAME,
                KDAUFTRAG.TOURID,
                KDAUFTRAG.ETAUFTRAGSCHALTER2,
                KDAUFTRAG.KDAUFTRAGART,
                KDAUFTRAG.KOART,
                KDAUFTRAG.BUCHART,
                KDAUFTRAG.ANZPOS,
                KDAUFTRAG.ANZPOSDAFUE,
                KDAUFTRAG.ZEITENDEAM,
                KDAUFTRAG.ZEITENDEPM,
                KUNDE.NAMEAPO,
                KUNDE.KZKDKLASSE,
                KDAUFTRAG.ANZPOSOB,
                KDAUFTRAG.ANZALPHATEXT,
                KUNDE.ORT,
                KDAUFTRAG.VERTRIEBSZENTRUMNR,
                KDAUFTRAG.KDAUFTRAGNRFILIALE,
                KDAUFTRAG.SENDESTATUS,
                KDAUFTRAG.ZUGRUND,
                KDAUFTRAG.DATUMAUSLIEFERUNG,
                KDAUFTRAG.RECHNUNGNR,
                KDAUFTRAG.INVOICENUMBER,
                KDAUFTRAG.PAYMENTDATE,
                KDAUFTRAG.PAYMENTTYPE,
                KDAUFTRAG.ORDERLABEL,
                KDAUFTRAG.ORDERPERIODID,
                KUNDE.NAMEINHABER
            from kdauftrag, kunde, cscorderflags
            where   kdauftrag.kdauftragstat like :a->KDAUFTRAGSTAT and
                    kdauftrag.geraetname            like :a->GERAETNAME and
                    kdauftrag.vertriebszentrumnr    >=   :Vz_von   and
                    kdauftrag.vertriebszentrumnr    <=   :Vz_bis   and
                    (kdauftrag.datumauslieferung    <=  :lDatum    or
                    kdauftrag.datumauslieferung    =    0      )    and
                    kunde.kundennr                  =    kdauftrag.kundennr and
                    kunde.vertriebszentrumnr        =    kdauftrag.vertriebszentrumnr and
                    cscorderflags.cscorderno = kdauftrag.kdauftragnr and
                    cscorderflags.waitforibtpicking != 1 and
                    kdauftrag.vertriebszentrumnr in (
                        select RegionArten.RegionTeilNr from RegionArten
                        where  RegionArten.RegionNr= :a->REGIONNR and
                               RegionArten.RegionenTyp=1)
                    and kdauftrag.zugrund like :a->ZUGRUND
            order by anzpos;

        EXEC SQL open Selzurauft_o_pos;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauft_o_pos: open Selzurauft_o_pos %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Selzurauft_o_pos;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelzurauft_o_pos: close Selzurauft_o_pos %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Selzurauft_o_pos
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->NAMEINHABER;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelzurauft_o_pos: fetch Selzurauft_o_pos %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Selzurauft_o_pos;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    return 0;
}


int AaauftSelProLink(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    long MIN_RECHNR;
    long MAX_RECHNR;
    char MIN_INVOICE[16];
    char MAX_INVOICE[16];
    short Vz_von;
    short Vz_bis;
    long lDatum_von;
    long lDatum_bis;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        sdatum = a->DATUM;     /* spaeter extra feld in view */
        datum = a->DATUM;      /* spaeter extra feld in view */
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        ppGStripLast(a->TOURID);
        ppGStripLast(a->SORTFIELD);
        ppGStripLast(a->INVOICENUMBER);
        if (a->SORTFIELD[0] == '\0') strcpy(a->SORTFIELD, "kdauftragnr");
        if (a->ANZPOS == 0) /* nase keine Rechnungsnummer mitgegeben */
        {
            MIN_RECHNR = 0;
            MAX_RECHNR = 2147483647;
        }
        else
        {
            MIN_RECHNR = a->ANZPOS;
            MAX_RECHNR = a->ANZPOS;
        }
        if (a->INVOICENUMBER[0] == '\0') /* nase keine Rechnungsnummer mitgegeben */
        {
            strcpy(MIN_INVOICE, " ");
            strcpy(MAX_INVOICE, "999999999999999");
        }
        else
        {
            strcpy(MIN_INVOICE, a->INVOICENUMBER);
            strcpy(MAX_INVOICE, a->INVOICENUMBER);
        }
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        if (a->DATUM == 0)
        {
            lDatum_von = 0;
            lDatum_bis = 20991231;
        }
        else
        {
            lDatum_von = a->DATUM;
            lDatum_bis = a->DATUM;
        }
        strcpy(str, "select ");
        strcat(str, "AKDAUFTRAG.KDAUFTRAGNR, ");
        strcat(str, "AKDAUFTRAG.KDAUFTRAGSTAT, ");
        strcat(str, "AKDAUFTRAG.IDFNR, ");
        strcat(str, "AKDAUFTRAG.GERAETNAME, ");
        strcat(str, "AKDAUFTRAG.TOURID, ");
        strcat(str, "AKDAUFTRAG.ETAUFTRAGSCHALTER2, ");
        strcat(str, "AKDAUFTRAG.KDAUFTRAGART, ");
        strcat(str, "AKDAUFTRAG.KOART, ");
        strcat(str, "AKDAUFTRAG.BUCHART, ");
        strcat(str, "AKDAUFTRAG.ANZPOS, ");
        strcat(str, "AKDAUFTRAG.ANZPOSDAFUE, ");
        strcat(str, "AKDAUFTRAG.ZEITENDEAM, ");
        strcat(str, "AKDAUFTRAG.ZEITENDEPM, ");
        strcat(str, "KUNDE.NAMEAPO, ");
        strcat(str, "KUNDE.KZKDKLASSE, ");
        strcat(str, "AKDAUFTRAG.ANZPOSOB, ");
        strcat(str, "AKDAUFTRAG.ANZALPHATEXT, ");
        strcat(str, "KUNDE.ORT, ");
        strcat(str, "AKDAUFTRAG.VERTRIEBSZENTRUMNR, ");
        strcat(str, "AKDAUFTRAG.KDAUFTRAGNRFILIALE, ");
        strcat(str, "AKDAUFTRAG.SENDESTATUS, ");
        strcat(str, "AKDAUFTRAG.ZUGRUND, ");
        strcat(str, "AKDAUFTRAG.DATUMAUSLIEFERUNG, ");
        strcat(str, "AKDAUFTRAG.RECHNUNGNR, ");
        strcat(str, "AKDAUFTRAG.DATUM, ");
        strcat(str, "AKDAUFTRAG.INVOICENUMBER, ");
        strcat(str, "AKDAUFTRAG.PAYMENTDATE, ");
        strcat(str, "AKDAUFTRAG.PAYMENTTYPE, ");
        strcat(str, "AKDAUFTRAG.ORDERLABEL, ");
        strcat(str, "AKDAUFTRAG.ORDERPERIODID ");
        strcat(str, "from akdauftrag, kunde ");
        strcat(str, "where akdauftrag.kdauftragstat like ? and ");
        strcat(str, "akdauftrag.datum >= ? and ");
        strcat(str, "akdauftrag.datum <= ? and ");
        strcat(str, "akdauftrag.kdauftragart = 'PF' and ");
        strcat(str, "akdauftrag.geraetname like ? and ");
        strcat(str, "akdauftrag.tourid like ? and ");
        strcat(str, "akdauftrag.kdauftragnr >= ? and ");
        strcat(str, "akdauftrag.vertriebszentrumnr >= ? and ");
        strcat(str, "akdauftrag.vertriebszentrumnr <= ? and ");
        if (!strncmp(cCountry, "BG", 2))
        {
            strcat(str, "akdauftrag.invoicenumber >= ? and ");
            strcat(str, "akdauftrag.invoicenumber <= ? and ");
        }
        else
        {
            strcat(str, "akdauftrag.rechnungnr >= ? and ");
            strcat(str, "akdauftrag.rechnungnr <= ? and ");
        }
        strcat(str, "kunde.kundennr = akdauftrag.kundennr and ");
        strcat(str, "kunde.vertriebszentrumnr = akdauftrag.vertriebszentrumnr and ");
        strcat(str, "akdauftrag.vertriebszentrumnr in ( ");
        strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
        strcat(str, "where  RegionArten.RegionNr= ? and ");
        strcat(str, "RegionArten.RegionenTyp=1) and ");
        strcat(str, "akdauftrag.kdauftragnr not in ( ");
        strcat(str, "select akdauftragprolink.kdauftragnr from akdauftragprolink ");
        strcat(str, "where akdauftragprolink.datum = akdauftrag.datum ) ");
        strcat(str, "order by akdauftrag.datum, akdauftrag.kdauftragnr ");
        EXEC SQL prepare dec_Selprolink from :str;
        EXEC SQL declare Selprolink scroll cursor with hold for dec_Selprolink;

        if (!strncmp(cCountry, "BG", 2))
        {
            EXEC SQL open Selprolink using
                :a->KDAUFTRAGSTAT,
                :lDatum_von,
                :lDatum_bis,
                :a->GERAETNAME,
                :a->TOURID,
                :a->KDAUFTRAGNR,
                :Vz_von,
                :Vz_bis,
                :MIN_INVOICE,
                :MAX_INVOICE,
                :a->REGIONNR;
        }
        else
        {
            EXEC SQL open Selprolink using
                :a->KDAUFTRAGSTAT,
                :lDatum_von,
                :lDatum_bis,
                :a->GERAETNAME,
                :a->TOURID,
                :a->KDAUFTRAGNR,
                :Vz_von,
                :Vz_bis,
                :MIN_RECHNR,
                :MAX_RECHNR,
                :a->REGIONNR;
        }

        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelProLink: open Selprolink %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Selprolink;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelProLink: close Selprolink %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Selprolink
        into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->DATUM,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelProLink: fetch Selprolink %ld %ld",
        sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Selprolink;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    if (AaauftGetfirstordertime(d, error_msg) < 0) return -1;
    return 0;
}

int AaauftSelzurauft_o_sortfield(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;
    static int anz = 0;

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short Vz_von;
    short Vz_bis;
    long IDF_von;
    long IDF_bis;
    long lDatum;
    short sOrderlabeltyp;
    static char cKA[4];
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        anz = 0;
        fst = 0;
        ppGStripLast(a->KDAUFTRAGART);
        sprintf(cKA, "%s", a->KDAUFTRAGART);
        lDatum = AllgGetDate();
        if (a->VERTRIEBSZENTRUMNR == 0) /* nase alle VZs */
        {
            Vz_von = 0;
            Vz_bis = 99;
        }
        else
        {
            Vz_von = a->VERTRIEBSZENTRUMNR;
            Vz_bis = a->VERTRIEBSZENTRUMNR;
        }
        if (a->KUNDENNR == 0)
        {
            IDF_von = 0;
            IDF_bis = 9999999;
        }
        else
        {
            IDF_von = a->KUNDENNR;
            IDF_bis = a->KUNDENNR;
        }

        sOrderlabeltyp = a->SENDESTATUS;
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        strcpy(str, "select ");
        strcat(str, "KDAUFTRAG.KDAUFTRAGNR, ");
        strcat(str, "KDAUFTRAG.KDAUFTRAGSTAT, ");
        strcat(str, "KDAUFTRAG.IDFNR, ");
        strcat(str, "KDAUFTRAG.GERAETNAME, ");
        strcat(str, "KDAUFTRAG.TOURID, ");
        strcat(str, "KDAUFTRAG.ETAUFTRAGSCHALTER2, ");
        strcat(str, "KDAUFTRAG.KDAUFTRAGART, ");
        strcat(str, "KDAUFTRAG.KOART, ");
        strcat(str, "KDAUFTRAG.BUCHART, ");
        strcat(str, "KDAUFTRAG.ANZPOS, ");
        strcat(str, "KDAUFTRAG.ANZPOSDAFUE, ");
        strcat(str, "KDAUFTRAG.ZEITENDEAM, ");
        strcat(str, "KDAUFTRAG.ZEITENDEPM, ");
        strcat(str, "KUNDE.NAMEAPO, ");
        strcat(str, "KUNDE.KZKDKLASSE, ");
        strcat(str, "KDAUFTRAG.ANZPOSOB, ");
        strcat(str, "KDAUFTRAG.ANZALPHATEXT, ");
        strcat(str, "KUNDE.ORT, ");
        strcat(str, "KDAUFTRAG.VERTRIEBSZENTRUMNR, ");
        strcat(str, "KDAUFTRAG.KDAUFTRAGNRFILIALE, ");
        strcat(str, "KDAUFTRAG.SENDESTATUS, ");
        strcat(str, "KDAUFTRAG.ZUGRUND, ");
        strcat(str, "KDAUFTRAG.DATUMAUSLIEFERUNG, ");
        strcat(str, "KDAUFTRAG.RECHNUNGNR, ");
        strcat(str, "KDAUFTRAG.INVOICENUMBER, ");
        strcat(str, "KDAUFTRAG.PAYMENTDATE, ");
        strcat(str, "KDAUFTRAG.PAYMENTTYPE, ");
        strcat(str, "KDAUFTRAG.ORDERLABEL, ");
        strcat(str, "KDAUFTRAG.ORDERPERIODID, ");
        strcat(str, "KUNDE.NAMEINHABER ");
        strcat(str, "from kdauftrag ");
        strcat(str, "inner join kunde ");
        strcat(str, "on kunde.kundennr = kdauftrag.kundennr ");
        strcat(str, "and kunde.vertriebszentrumnr = kdauftrag.vertriebszentrumnr ");
        strcat(str,  "inner join cscorderflags ");
        strcat(str,  "on cscorderflags.cscorderno = kdauftrag.kdauftragnr ");
        strcat(str, "left join auftragartkd ");
        strcat(str, "on auftragartkd.vertriebszentrumnr = kdauftrag.vertriebszentrumnr ");
        strcat(str, "and auftragartkd.kundennr = kdauftrag.kundennr ");
        strcat(str, "and auftragartkd.kdauftragart = kdauftrag.kdauftragart ");
        strcat(str, "where kdauftrag.kdauftragstat like ? ");
        strcat(str, "and kdauftrag.kdauftragart like ? ");
        strcat(str, "and kdauftrag.geraetname like ? ");
        strcat(str, "and kdauftrag.vertriebszentrumnr >= ? ");
        strcat(str, "and kdauftrag.vertriebszentrumnr <= ? ");
        strcat(str, "and kdauftrag.kundennr >= ? ");
        strcat(str, "and kdauftrag.kundennr <= ? ");
        strcat(str, "and (kdauftrag.datumauslieferung <= ? ");
        strcat(str, "or kdauftrag.datumauslieferung = 0 ) ");
        strcat(str, "and kdauftrag.vertriebszentrumnr in ( ");
        strcat(str, "select RegionArten.RegionTeilNr from RegionArten ");
        strcat(str, "where RegionArten.RegionNr = ? ");
        strcat(str, "and RegionArten.RegionenTyp = 1) ");
        strcat(str, "and kdauftrag.zugrund like ? ");
        if (sOrderlabeltyp == 0)
        {
            strcat(str, "and kdauftrag.orderlabel = '' ");
        }
        else if (sOrderlabeltyp == 1)
        {
            strcat(str, "and (kdauftrag.orderlabel = auftragartkd.orderidentificatio ");
            strcat(str, "or kdauftrag.orderlabel = '') ");
        }
        strcat(str, "and cscorderflags.waitforibtpicking != 1 ");
        strcat(str, "order by ");
        strcat(str, a->SORTFIELD);

        EXEC SQL prepare dec_Selzurauft_o_sortfield from :str;
        if (sqlca.sqlcode < 0)
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauft_o_sortfield: prepare dec_Selzurauft_o_sortfield %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }

        EXEC SQL declare Selzurauft_o_sortfield scroll cursor with hold for dec_Selzurauft_o_sortfield;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauft_o_sortfield: declare Selzurauft_o_sortfield %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        EXEC SQL open Selzurauft_o_sortfield using
            :a->KDAUFTRAGSTAT,
            :cKA,
            :a->GERAETNAME,
            :Vz_von,
            :Vz_bis,
            :IDF_von,
            :IDF_bis,
            :lDatum,
            :a->REGIONNR,
            :a->ZUGRUND;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauft_o_sortfield: open Selzurauft_o_sortfield %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        anz = 0;
        EXEC SQL close Selzurauft_o_sortfield;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelzurauft_o_sortfield: close Selzurauft_o_sortfield %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    for (;;)
    {
        EXEC SQL fetch relative :a->FETCH_REL Selzurauft_o_sortfield into
            :a->KDAUFTRAGNR,
            :a->KDAUFTRAGSTAT,
            :a->IDFNR,
            :a->GERAETNAME,
            :a->TOURID,
            :a->ETAUFTRAGSCHALTER2,
            :a->KDAUFTRAGART,
            :a->KOART,
            :a->BUCHART,
            :a->ANZPOS,
            :a->ANZPOSDAFUE,
            :a->ZEITENDEAM,
            :a->ZEITENDEPM,
            :a->NAMEAPO,
            :a->KZKDKLASSE,
            :a->ANZPOSOB,
            :a->ANZALPHATEXT,
            :a->ORT,
            :a->VERTRIEBSZENTRUMNR,
            :a->KDAUFTRAGNRFILIALE,
            :a->SENDESTATUS,
            :a->ZUGRUND,
            :a->DATUMAUSLIEFERUNG,
            :a->RECHNUNGNR,
            :a->INVOICENUMBER,
            :a->PAYMENTDATE,
            :a->PAYMENTTYPE,
            :a->ORDERLABEL,
            :a->ORDERPERIODID,
            :a->NAMEINHABER;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelzurauft_o_sortfield: fetch Selzurauft_o_sortfield %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            EXEC SQL close Selzurauft_o_sortfield;
            return -1;
        }
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            if (anz == 0 && cKA[0] != '%')
            {
                sprintf(cKA, "%s", "%%");
                EXEC SQL open Selzurauft_o_sortfield using
                    :a->KDAUFTRAGSTAT,
                    :cKA,
                    :a->GERAETNAME,
                    :Vz_von,
                    :Vz_bis,
                    :IDF_von,
                    :IDF_bis,
                    :lDatum,
                    :a->REGIONNR,
                    :a->ZUGRUND;
                if (sqlca.sqlcode < 0 )
                {
                    fst = 1;
                    sprintf(error_msg, " AaauftSelzurauft_o_sortfield: open Selzurauft_o_sortfield2 %ld %ld",
                        sqlca.sqlcode, sqlca.sqlerrd[1]);
                    return -1;
                }
                continue;
            }
            else
            {
                return 1;
            }
        }
        anz++;
        break;
    }

    updateZeitEndePM(d);
    return 0;
}

int AaauftSelList_Auftrag(struct AUSTINF* d, char* error_msg)
{
    static int fst = 1;
    char cWhere[2048];
    char cWert[256];
    char cDatum[11];

    EXEC SQL BEGIN DECLARE SECTION;
    struct AUSTINF* a;
    short Vz_von;
    short Vz_bis;
    long lDatum;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        lDatum = AllgGetDate();

        sdatum = a->DATUM;     /* spaeter extra feld in view */
        datum = a->DATUM;      /* spaeter extra feld in view */
        sprintf(cDatum, "%d", lDatum);
        ppGStripLast(a->KDAUFTRAGSTAT);
        ppGStripLast(a->GERAETNAME);
        ppGStripLast(a->KDAUFTRAGART);
        ppGStripLast(a->TOURID);
        ppGStripLast(a->SORTFIELD);
        ppGStripLast(a->INVOICENUMBER);
        ppGStripLast(a->REGIONLIST);
        ppGStripLast(a->ZUGRUND);
        ppGStripLast(a->SAP_REFERENCENO);
        if (a->SORTFIELD[0] == '\0')
        {
            if (a->KDAUFTRAGNRFILIALE > 0)
            {
                strcpy(a->SORTFIELD, "17");
            }
            else
            {
                strcpy(a->SORTFIELD, "1");
            }
        }

        strcpy(str, "select ");
        if (a->ZEITENDEAM > 0)
        {
            strcat(str, "unique ");
        }
        if ((a->DATUM == 0 && a->AKTUELL[0] == '0') || a->DATUM > 0 || a->HISTORY[0] == '1')
        {
            /* Definition where-Klausel */
            if (a->ZEITENDEAM > 0)
            {
                strcpy(cWhere, "where akdauftragpos.artikel_nr = ");
                sprintf(cWert, "%d ", a->ZEITENDEAM);
                strcat(cWhere, cWert);
                if (a->KUNDENNR > 0)
                {
                    strcat(cWhere, "and akdauftrag.kundennr = ");
                    sprintf(cWert, "%d ", a->KUNDENNR);
                    strcat(cWhere, cWert);
                }
                if (a->GERAETNAME[0] != '\0')
                {
                    strcat(cWhere, "and akdauftrag.geraetname like '");
                    strcat(cWhere, a->GERAETNAME);
                    strcat(cWhere, "' ");
                }
            }
            else if (a->INVOICENUMBER[0] != '\0')
            {
                if (!strcmp(cCountry, "BG"))
                {
                    strcpy(cWhere, "where akdauftrag.INVOICENUMBER = '");
                    strcat(cWhere, a->INVOICENUMBER);
                    strcat(cWhere, "' ");
                }
                else
                {
                    strcpy(cWhere, "where akdauftrag.rechnungnr = ");
                    strcat(cWhere, a->INVOICENUMBER);
                    strcat(cWhere, " ");
                }
            }
            else
            {
                strcpy(cWhere, "where akdauftrag.kdauftragstat like '");
                strcat(cWhere, a->KDAUFTRAGSTAT);
                strcat(cWhere, "' ");
                if (a->GERAETNAME[0] != '\0')
                {
                    strcat(cWhere, "and akdauftrag.geraetname like '");
                    strcat(cWhere, a->GERAETNAME);
                    strcat(cWhere, "' ");
                }
                if (a->TOURID[0] != '\0')
                {
                    strcat(cWhere, "and akdauftrag.tourid like '");
                    strcat(cWhere, a->TOURID);
                    strcat(cWhere, "' ");
                }
                if (a->KDAUFTRAGART[0] != '\0')
                {
                    strcat(cWhere, "and akdauftrag.kdauftragart like '");
                    strcat(cWhere, a->KDAUFTRAGART);
                    strcat(cWhere, "' ");
                }
                if (a->ZUGRUND[0] != '\0')
                {
                    strcat(cWhere, "and akdauftrag.zugrund like '");
                    strcat(cWhere, a->ZUGRUND);
                    strcat(cWhere, "' ");
                }
                if (a->TOURID[0] != '\0')
                {
                    strcat(cWhere, "and akdauftrag.tourid like '");
                    strcat(cWhere, a->TOURID);
                    strcat(cWhere, "' ");
                }
                if (a->KDAUFTRAGNR > 0)
                {
                    strcat(cWhere, "and akdauftrag.kdauftragnr ");
                    if (a->ONLYORDER[0] == '1')
                        strcat(cWhere, "= ");
                    else
                        strcat(cWhere, ">= ");
                    sprintf(cWert, "%d ", a->KDAUFTRAGNR);
                    strcat(cWhere, cWert);
                }
                if (a->KDAUFTRAGNRFILIALE > 0)
                {
                    strcat(cWhere, "and akdauftrag.kdauftragnrfiliale ");
                    if (a->ONLYORDERFILI[0] == '1')
                        strcat(cWhere, "= ");
                    else
                        strcat(cWhere, ">= ");
                    sprintf(cWert, "%d ", a->KDAUFTRAGNRFILIALE);
                    strcat(cWhere, cWert);
                }
                if (a->KUNDENNR > 0)
                {
                    strcat(cWhere, "and akdauftrag.kundennr = ");
                    sprintf(cWert, "%d ", a->KUNDENNR);
                    strcat(cWhere, cWert);
                }
            }
            if (a->DATUM > 0)
            {
                strcat(cWhere, "and akdauftrag.datum = ");
                sprintf(cWert, "%d ", a->DATUM);
                strcat(cWhere, cWert);
            }
            if (a->VERTRIEBSZENTRUMNR == 0)
            {
                strcat(cWhere, "and akdauftrag.vertriebszentrumnr in (");
                sprintf(cWert, "%s) ", a->REGIONLIST);
                strcat(cWhere, cWert);
    /*          strcat(cWhere, "and akdauftrag.vertriebszentrumnr in ( ");
                strcat(cWhere, "select RegionArten.RegionTeilNr from RegionArten ");
                strcat(cWhere, "where RegionArten.RegionNr = ");
                sprintf(cWert, "%d ", a->REGIONNR);
                strcat(cWhere, cWert);
                strcat(cWhere, "and RegionArten.RegionenTyp=1) ");   */
            }
            else
            {
                strcat(cWhere, "and akdauftrag.vertriebszentrumnr = ");
                sprintf(cWert, "%d ", a->VERTRIEBSZENTRUMNR);
                strcat(cWhere, cWert);
            }
            if (a->SAP_REFERENCENO[0] != '\0')
            {
                strcat(cWhere, "and aorderremarks.remarktype = 21 ");
                strcat(cWhere, "and aorderremarks.remarktext like '");
                strcat(cWhere, a->SAP_REFERENCENO);
                strcat(cWhere, "' ");
            }

            strcat(str, "AKDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "AKDAUFTRAG.IDFNR, ");
            strcat(str, "AKDAUFTRAG.GERAETNAME, ");
            strcat(str, "AKDAUFTRAG.TOURID, ");
            strcat(str, "AKDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "AKDAUFTRAG.KOART, ");
            strcat(str, "AKDAUFTRAG.BUCHART, ");
            strcat(str, "AKDAUFTRAG.ANZPOS, ");
            strcat(str, "AKDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "AKDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "AKDAUFTRAG.ANZPOSOB, ");
            strcat(str, "AKDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "AKDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "AKDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "AKDAUFTRAG.SENDESTATUS, ");
            strcat(str, "AKDAUFTRAG.ZUGRUND, ");
            strcat(str, "AKDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "AKDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "AKDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "AKDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "AKDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "AKDAUFTRAG.ORDERLABEL, ");
            strcat(str, "AKDAUFTRAG.ORDERPERIODID, ");
            strcat(str, "AKDAUFTRAG.DATUM, ");
            strcat(str, "ACSCORDERFLAGS.WAITFORIBTPICKING ");
            if (a->ZEITENDEAM > 0)
            {
                strcat(str, "from akdauftrag ");
                strcat(str, "inner join akdauftragpos on akdauftrag.kdauftragnr = akdauftragpos.kdauftragnr and akdauftrag.datum = akdauftragpos.datum ");
            }
            else
            {
                strcat(str, "from akdauftrag ");
            }
            strcat(str, "inner join acscorderflags on akdauftrag.kdauftragnr = acscorderflags.cscorderno and akdauftrag.datum = acscorderflags.datum ");
            if (a->SAP_REFERENCENO[0] != '\0')
            {
                strcat(str, "inner join aorderremarks on aorderremarks.cscorderno = akdauftrag.kdauftragnr and aorderremarks.datum = akdauftrag.datum ");
            }
            strcat(str, cWhere);
        }
        if (a->DATUM == 0 && a->AKTUELL[0] == '0' && a->HISTORY[0] == '0')
        {
            strcat(str, "union all ");
            strcat(str, "select ");
            if (a->ZEITENDEAM > 0)
            {
                strcat(str, "unique ");
            }
        }
        else if (a->DATUM == 0 && a->AKTUELL[0] == '1')
        {
            strcpy(str, "select ");
            if (a->ZEITENDEAM > 0)
            {
                strcat(str, "unique ");
            }
        }

        if (a->DATUM == 0 && a->HISTORY[0] == '0')
        {
            /* Definition where-Klausel */
            if (a->ZEITENDEAM > 0)
            {
                strcpy(cWhere, "where kdauftragpos.artikel_nr = ");
                sprintf(cWert, "%d ", a->ZEITENDEAM);
                strcat(cWhere, cWert);
                if (a->KUNDENNR > 0)
                {
                    strcat(cWhere, "and kdauftrag.kundennr = ");
                    sprintf(cWert, "%d ", a->KUNDENNR);
                    strcat(cWhere, cWert);
                }
                if (a->GERAETNAME[0] != '\0')
                {
                    strcat(cWhere, "and kdauftrag.geraetname like '");
                    strcat(cWhere, a->GERAETNAME);
                    strcat(cWhere, "' ");
                }
            }
            else if (a->INVOICENUMBER[0] != '\0')
            {
                if (!strcmp(cCountry, "BG"))
                {
                    strcpy(cWhere, "where kdauftrag.INVOICENUMBER = '");
                    strcat(cWhere, a->INVOICENUMBER);
                    strcat(cWhere, "' ");
                }
                else
                {
                    strcpy(cWhere, "where kdauftrag.rechnungnr = ");
                    strcat(cWhere, a->INVOICENUMBER);
                    strcat(cWhere, " ");
                }
            }
            else
            {
                strcpy(cWhere, "where kdauftrag.kdauftragstat like '");
                strcat(cWhere, a->KDAUFTRAGSTAT);
                strcat(cWhere, "' ");
                if (a->GERAETNAME[0] != '\0')
                {
                    strcat(cWhere, "and kdauftrag.geraetname like '");
                    strcat(cWhere, a->GERAETNAME);
                    strcat(cWhere, "' ");
                }
                if (a->TOURID[0] != '\0')
                {
                    strcat(cWhere, "and kdauftrag.tourid like '");
                    strcat(cWhere, a->TOURID);
                    strcat(cWhere, "' ");
                }
                if (a->KDAUFTRAGART[0] != '\0')
                {
                    strcat(cWhere, "and kdauftrag.kdauftragart like '");
                    strcat(cWhere, a->KDAUFTRAGART);
                    strcat(cWhere, "' ");
                }
                if (a->ZUGRUND[0] != '\0')
                {
                    strcat(cWhere, "and kdauftrag.zugrund like '");
                    strcat(cWhere, a->ZUGRUND);
                    strcat(cWhere, "' ");
                }
                if (a->TOURID[0] != '\0')
                {
                    strcat(cWhere, "and kdauftrag.tourid like '");
                    strcat(cWhere, a->TOURID);
                    strcat(cWhere, "' ");
                }
                if (a->KDAUFTRAGNR > 0)
                {
                    strcat(cWhere, "and kdauftrag.kdauftragnr ");
                    if (a->ONLYORDER[0] == '1')
                        strcat(cWhere, "= ");
                    else
                        strcat(cWhere, ">= ");
                    sprintf(cWert, "%d ", a->KDAUFTRAGNR);
                    strcat(cWhere, cWert);
                }
                if (a->KDAUFTRAGNRFILIALE > 0)
                {
                    strcat(cWhere, "and kdauftrag.kdauftragnrfiliale ");
                    if (a->ONLYORDERFILI[0] == '1')
                        strcat(cWhere, "= ");
                    else
                        strcat(cWhere, ">= ");
                    sprintf(cWert, "%d ", a->KDAUFTRAGNRFILIALE);
                    strcat(cWhere, cWert);
                }
                if (a->KUNDENNR > 0)
                {
                    strcat(cWhere, "and kdauftrag.kundennr = ");
                    sprintf(cWert, "%d ", a->KUNDENNR);
                    strcat(cWhere, cWert);
                }
                if (a->DATUMAUSLIEFERUNG == 0)
                {
                    strcat(cWhere, "and (kdauftrag.datumauslieferung <= ");
                    sprintf(cWert, "%d ", lDatum);
                    strcat(cWhere, cWert);
                    strcat(cWhere, "or kdauftrag.datumauslieferung = 0 ) ");
                }
                else
                {
                    strcat(cWhere, "and kdauftrag.datumauslieferung >= ");
                    sprintf(cWert, "%d ", a->DATUMAUSLIEFERUNG);
                    strcat(cWhere, cWert);
                }
            }
            if (a->VERTRIEBSZENTRUMNR == 0)
            {
                strcat(cWhere, "and kdauftrag.vertriebszentrumnr in (");
                sprintf(cWert, "%s) ", a->REGIONLIST);
                strcat(cWhere, cWert);
            }
            else
            {
                strcat(cWhere, "and kdauftrag.vertriebszentrumnr = ");
                sprintf(cWert, "%d ", a->VERTRIEBSZENTRUMNR);
                strcat(cWhere, cWert);
            }
            if (a->SAP_REFERENCENO[0] != '\0')
            {
                strcat(cWhere, "and orderremarks.remarktype = 21 ");
                strcat(cWhere, "and orderremarks.remarktext like '");
                strcat(cWhere, a->SAP_REFERENCENO);
                strcat(cWhere, "' ");
            }

            strcat(str, "KDAUFTRAG.KDAUFTRAGNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGSTAT, ");
            strcat(str, "KDAUFTRAG.IDFNR, ");
            strcat(str, "KDAUFTRAG.GERAETNAME, ");
            strcat(str, "KDAUFTRAG.TOURID, ");
            strcat(str, "KDAUFTRAG.ETAUFTRAGSCHALTER2, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGART, ");
            strcat(str, "KDAUFTRAG.KOART, ");
            strcat(str, "KDAUFTRAG.BUCHART, ");
            strcat(str, "KDAUFTRAG.ANZPOS, ");
            strcat(str, "KDAUFTRAG.ANZPOSDAFUE, ");
            strcat(str, "KDAUFTRAG.ZEITENDEAM, ");
            strcat(str, "KDAUFTRAG.ZEITENDEPM, ");
            strcat(str, "KDAUFTRAG.ANZPOSOB, ");
            strcat(str, "KDAUFTRAG.ANZALPHATEXT, ");
            strcat(str, "KDAUFTRAG.VERTRIEBSZENTRUMNR, ");
            strcat(str, "KDAUFTRAG.KDAUFTRAGNRFILIALE, ");
            strcat(str, "KDAUFTRAG.SENDESTATUS, ");
            strcat(str, "KDAUFTRAG.ZUGRUND, ");
            strcat(str, "KDAUFTRAG.DATUMAUSLIEFERUNG, ");
            strcat(str, "KDAUFTRAG.RECHNUNGNR, ");
            strcat(str, "KDAUFTRAG.INVOICENUMBER, ");
            strcat(str, "KDAUFTRAG.PAYMENTDATE, ");
            strcat(str, "KDAUFTRAG.PAYMENTTYPE, ");
            strcat(str, "KDAUFTRAG.ORDERLABEL, ");
            strcat(str, "KDAUFTRAG.ORDERPERIODID, ");
            strcat(str,  cDatum);
            strcat(str,  ", ");
            strcat(str, "CSCORDERFLAGS.WAITFORIBTPICKING ");
            if (a->ZEITENDEAM > 0)
            {
                strcat(str, "from kdauftrag ");
                strcat(str, "inner join kdauftragpos on kdauftrag.kdauftragnr = kdauftragpos.kdauftragnr ");
            }
            else
            {
                strcat(str, "from kdauftrag ");
            }
            strcat(str, "inner join cscorderflags on kdauftrag.kdauftragnr = cscorderflags.cscorderno ");
            if (a->SAP_REFERENCENO[0] != '\0')
            {
                strcat(str, "inner join orderremarks on orderremarks.cscorderno = kdauftrag.kdauftragnr ");
            }
            strcat(str, cWhere);
        }
        strcat(str, "order by ");
        strcat(str, a->SORTFIELD);

        EXEC SQL prepare dec_Sellistauft from :str;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_Auftrag: prepare dec_Sellistauft %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        EXEC SQL declare Sellistauft scroll cursor with hold for dec_Sellistauft;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_Auftrag: declare Sellistauft %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }

        EXEC SQL open Sellistauft;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_Auftrag: open Sellistauft %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Sellistauft;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelList_Auftrag: close Sellistauft %ld %ld",
                sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative : a->FETCH_REL Sellistauft
    into
        : a->KDAUFTRAGNR,
        : a->KDAUFTRAGSTAT,
        : a->IDFNR,
        : a->GERAETNAME,
        : a->TOURID,
        : a->ETAUFTRAGSCHALTER2,
        : a->KDAUFTRAGART,
        : a->KOART,
        : a->BUCHART,
        : a->ANZPOS,
        : a->ANZPOSDAFUE,
        : a->ZEITENDEAM,
        : a->ZEITENDEPM,
        : a->ANZPOSOB,
        : a->ANZALPHATEXT,
        : a->VERTRIEBSZENTRUMNR,
        : a->KDAUFTRAGNRFILIALE,
        : a->SENDESTATUS,
        : a->ZUGRUND,
        : a->DATUMAUSLIEFERUNG,
        : a->RECHNUNGNR,
        : a->INVOICENUMBER,
        : a->PAYMENTDATE,
        : a->PAYMENTTYPE,
        : a->ORDERLABEL,
        : a->ORDERPERIODID,
        : a->DATUM,
        : a->WAITFORIBTPICKING;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelList_Auftrag: fetch Sellistauft %ld %ld",
            sqlca.sqlcode, sqlca.sqlerrd[1]);
        EXEC SQL close Selfilauft;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    updateZeitEndePM(d);
    if (AaauftGetfirstordertime(d, error_msg) < 0) return -1;
    return 0;
}

int AaauftSelList_FCOrdersToSolve(fcordersselS* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    fcordersselS* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        strcpy(str, "select unique ");
        strcat(str, "k.kundennr, ");
        strcat(str, "k.nameapo, ");
        strcat(str, "a.kdauftragnr, ");
        strcat(str, "e.datum, ");
        strcat(str, "a.kdauftragart ");
        strcat(str, "from kdauftrag a ");
        strcat(str, "inner join kunde k on k.vertriebszentrumnr = a.vertriebszentrumnr and k.kundennr = a.kundennr ");
        strcat(str, "inner join kdauftragpos p on p.kdauftragnr = a.kdauftragnr ");
        strcat(str, "inner join kdauftragereignis e on e.kdauftragnr = a.kdauftragnr ");
        strcat(str, "inner join artikellokal l on a.vertriebszentrumnr = l.filialnr and p.artikel_nr = l.artikel_nr ");
        strcat(str, "where a.kdauftragart = 'FC' ");
        strcat(str, "and a.kdauftragstat like '00010000000_1%' ");
        strcat(str, "and e.ereignisart = 110 ");
        strcat(str, "and p.mengebestellt+p.mengebestelltnatra > p.mengebestaetigt+p.mengenatra ");
        strcat(str, "and l.bestand >= (p.mengebestellt+p.mengebestelltnatra) - (p.mengebestaetigt+p.mengenatra) ");
        strcat(str, "and a.vertriebszentrumnr = ? ");

        EXEC SQL prepare dec_SellistToSolve from :str;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_FCOrdersToSolve: prepare dec_SellistToSolve %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }
        EXEC SQL declare SellistToSolve scroll cursor with hold for dec_SellistToSolve;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_FCOrdersToSolve: declare SellistToSolve %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }

        EXEC SQL open SellistToSolve using :a->VERTRIEBSZENTRUMNR;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_FCOrdersToSolve: open SellistToSolve %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close SellistToSolve;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelList_FCOrdersToSolve: close SellistToSolve %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL SellistToSolve
        into
        :a->KUNDENNR,
        :a->NAMEAPO,
        :a->KDAUFTRAGNR,
        :a->DATUM,
        :a->KDAUFTRAGART;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelList_FCOrdersToSolve: fetch SellistToSolve %ld %ld %s",
            sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
        EXEC SQL close SellistToSolve;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
}

int AaauftSelList_FCOrdersToClose(fcordersselS* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    fcordersselS* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        strcpy(str, "select unique ");
        strcat(str, "k.kundennr, ");
        strcat(str, "k.nameapo, ");
        strcat(str, "a.kdauftragnr, ");
        strcat(str, "e.datum, ");
        strcat(str, "a.kdauftragart ");
        strcat(str, "from kdauftrag a ");
        strcat(str, "inner join kunde k on k.vertriebszentrumnr = a.vertriebszentrumnr and k.kundennr = a.kundennr ");
        strcat(str, "inner join kdauftragereignis e on e.kdauftragnr = a.kdauftragnr ");
        strcat(str, "left join kdauftragpos p on p.kdauftragnr = a.kdauftragnr and p.mengebestellt+p.mengebestelltnatra > p.mengebestaetigt+p.mengenatra ");
        strcat(str, "where a.kdauftragart = 'FC' ");
        strcat(str, "and a.kdauftragstat like '00010000000_1%' ");
        strcat(str, "and e.ereignisart = 110 ");
        strcat(str, "and a.vertriebszentrumnr = ? ");
        strcat(str, "and p.posnr is null ");

        EXEC SQL prepare dec_SellistToClose from :str;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_FCOrdersToClose: prepare dec_SellistToClose %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }
        EXEC SQL declare SellistToClose scroll cursor with hold for dec_SellistToClose;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_FCOrdersToClose: declare SellistToClose %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }

        EXEC SQL open SellistToClose using :a->VERTRIEBSZENTRUMNR;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_FCOrdersToClose: open SellistToClose %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close SellistToClose;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelList_FCOrdersToClose: close SellistToClose %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL SellistToClose
        into
        :a->KUNDENNR,
        :a->NAMEAPO,
        :a->KDAUFTRAGNR,
        :a->DATUM,
        :a->KDAUFTRAGART;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelList_FCOrdersToClose: fetch SellistToClose %ld %ld %s",
            sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
        EXEC SQL close SellistToClose;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
}

int AaauftSelList_FCOrdersAll(fcordersselS* d, char* error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    fcordersselS* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        strcpy(str, "select unique ");
        strcat(str, "k.kundennr, ");
        strcat(str, "k.nameapo, ");
        strcat(str, "a.kdauftragnr, ");
        strcat(str, "e.datum, ");
        strcat(str, "a.kdauftragart ");
        strcat(str, "from kdauftrag a ");
        strcat(str, "inner join kunde k on k.vertriebszentrumnr = a.vertriebszentrumnr and k.kundennr = a.kundennr ");
        strcat(str, "inner join kdauftragpos p on p.kdauftragnr = a.kdauftragnr ");
        strcat(str, "inner join kdauftragereignis e on e.kdauftragnr = a.kdauftragnr ");
        strcat(str, "inner join artikellokal l on a.vertriebszentrumnr = l.filialnr and p.artikel_nr = l.artikel_nr ");
        strcat(str, "where a.kdauftragart = 'FC' ");
        strcat(str, "and a.kdauftragstat like '00010000000_1%' ");
        strcat(str, "and e.ereignisart = 110 ");
        strcat(str, "and a.vertriebszentrumnr = ? ");

        EXEC SQL prepare dec_SellistAll from :str;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_FCOrdersAll: prepare dec_SellistAll %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }
        EXEC SQL declare SellistAll scroll cursor with hold for dec_SellistAll;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_FCOrdersAll: declare SellistAll %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }

        EXEC SQL open SellistAll using :a->VERTRIEBSZENTRUMNR;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AaauftSelList_FCOrdersAll: open SellistAll %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close SellistAll;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AaauftSelList_FCOrdersAll: close SellistAll %ld %ld %s",
                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL SellistAll
        into
        :a->KUNDENNR,
        :a->NAMEAPO,
        :a->KDAUFTRAGNR,
        :a->DATUM,
        :a->KDAUFTRAGART;
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AaauftSelList_FCOrdersAll: fetch SellistAll %ld %ld %s",
            sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
        EXEC SQL close SellistAll;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
}

/* An der Oberfläche wird immer ZEITENDEPM angezeigt */
void updateZeitEndePM(struct AUSTINF* austinf)
{
    if (AllgGetTime() < ZEIT_WECHSEL_AM_UND_PM)
    {
        austinf->ZEITENDEPM = austinf->ZEITENDEAM;
    }
}
