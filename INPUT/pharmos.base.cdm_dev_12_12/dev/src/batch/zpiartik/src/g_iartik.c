/* ---------------------------------------------------------------------- *
 *                            G_IARTIK.C                                  *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die IFA-Artikeldatei ein und integriert         *
 *                  die Saetze in den lokalen UPDATE-POOL                 *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 04.03.00                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

/* ab Juni 2002 wegen aut idem */
#define L_ARTIKEL_NR   7
#include <wpp_prot.h>
#include <wpp_dbas.h>
#include <zapflege.h>
/* --------------------------- */

#include "ifa_satz.h"
#include "ifa_info.h"
#include "ifa_stat.h"

#include <zifaart.h>
#include <zifaokbs.h>

#include <zartikel.h>

#include <ean.h>
#include <carticlecodes.h>
#include <herstel.h>

#include "znb_gen.h"
#include "l_taxtab.h"

#include "zifastat.h"

#include "g_ifoart.h"


#include <zpreiserhoehung.h>

/* --- Prototype  ------------------------------------------------------- */

long OpenBase( char *db, char *errmld );
void CloseBase( void );
void UpdateStatistics( char *relation );

int IsIfaNettoArtikel( struct ZIFAART *ifa );

int TestPreis_Neuaufnahme( struct ZIFAART *ifa );

int TestPreis_Aenderung  ( struct ZIFAART *ifa,
                           int IsTaxPruefGrosso, long ProzentPM,
                           long ifa_gro, long ifa_aep, long ifa_avp, long ifa_eavp,
                           long art_gro, long art_aep, long art_avp, long art_eavp );

void TestIfaPreisMeldung( struct ZIFAART *ifa, double herstProz );

static int isNullZeroOrEmpty(char* str);



/* -------- Kennung fuer Artikel --------------- */

static char *SatzartPhx = "PARTIKEL";
static char *SatzartPhxKlinik = "PKLINIKB";

static struct ZIFAOKBS zklinik;
static char NB_PLAUSI_KLINIK[ POSANZ_ZIFAOKBS + 1 ];

/* ------------------- Gloable Variable ------------------------ */


#if defined(MSDOS) || defined(WIN32)
#define ABBRUCH_NO_ERROR  -4711
// MAX_TEST_SATZ limits loaded IFA Data to number of rows
// Set this value to -1 to load all rows of current IFA files
#define MAX_TEST_SATZ      1000
#endif


#define TEST_MODE    0
#define FILL_MODE_1  1
#define FILL_MODE_2  2

static struct ZIFAART ifa;

static struct P_IFAOART oifa;
static struct P_IFAOART old_oifa;   // Alte Werte aus zifaoart fuer spaetere Checks sichern

static short inTransaction = 0;
static long ifadatumnr;
static long satznr;
static long art_ohne_pznneu;
static long art_mit_pznneu;

static long ifadatumnr_klinik;
static long satznr_klinik;

static long anz_upd;
static long anz_del;
static long anz_ins;

/* --- lokale Variablen ------------------------------------------------- */

static long tages_datum;

/* ---------------------------------------------------------------------- *
 * Funktion         : I f a F i l l                                       *
 * ---------------------------------------------------------------------- *
 * Aufgabe          : Fuellt einen Ifa-Satz                               *
 * Eingabe-Parameter: ifa  = Zeiger auf den Puffer mit dem Ifa-Satz       *
 *                  : art  = Zeiger auf den Puffer mit dem Artikelsatz    *
 * Return-Wert      : keiner                                              *
 * Info             : - Diese Funktion wird fuer jeden gelesenen Ifa-     *
 *                      Satz ausgefuehrt.                                 *
 * ---------------------------------------------------------------------- */

static void str_lcpy( char *s1, char *s2, int lng1 )
{
   size_t lng2;
   lng2 = strlen( s2 );
   if ( lng2 < lng1 )
   {
      while ( lng2-- > 0 ) { *s1++ = *s2++; lng1--; }
      while ( lng1-- > 0 ) *s1++ = ' ';
   }
   else
      while ( lng1-- > 0 ) *s1++ = *s2++;
   *s1 = '\0';
}


static void ze_lcpy( char *s1, char ze, int lng )
{
  while ( lng-- > 0 ) *s1++ = ze;
   *s1 = '\0';
}

/* --- EAN --------------------- */

static int TestEanNr( char *ean )
{
  int i;

  /* keine EAN, wenn nur 0 oder blank */
  i = 0;
  while ( ean[i] && ( ean[i] == ' ' || ean[i] == '0' ) ) i++;
  if ( ean[i] == '\0' )
    return 0;

  i = 0;
  while ( ean[i] && ean[i] >= '0' && ean[i] <= '9' ) i++;
  if ( ean[i] == '\0' )
    return  1;     /* EAN-Nr korrekt */
  else
    return -1;     /* EAN-Nr falsch */
}

static int isNullZeroOrEmpty(char* str) 
{
    if (str == NULL) 
    {
        return 1; // string is null
    }

    // Trim leading and trailing white spaces
    while (isspace(*str)) 
    {
        str++;
    }

    if (*str == '\0') 
    {
        return 1; // string is empty
    }

    long number = 0;
    if (sscanf(str, "%d", &number) == 1)
    {
        if (number == 0)
        {
            return 1; // Nummer is 0
        }
    }
    return 0; // string is not null or empty
}

/* --------- Vergleichs-Werte -------------------- */

char *Null_Drei = "0123";
char *Blank_X   = " X";
char *BB_00_01  = "  0001";
char *BB_00_01_99  = "  000199";
char *BB_00_02  = "  000102";
char *BB_00_03  = "  00010203";
char *OB_00_01  = "0001";
char *LIFE012   = "  000102";
char *ATYP		= "00010203040506";


static void FillIfaPlausiErr( struct ZIFAART *ifa )
{
  /* Nur von Ifa abhaengige PlausiFehler setzen */
  SetIfaErr   ( ifa->A00SSATZ , Null_Drei, ifa->NB_PLAUSI, PL_A00SSATZ );
  SetIfaErr   ( ifa->A00LKZ   , Blank_X,   ifa->NB_PLAUSI, PL_A00LKZ   );
  SetIfaNumErr( ifa->A00PZN   ,            ifa->NB_PLAUSI, PL_A00PZN   );
                  /* A00PBEZ    */
                  /* A00PGMENG  */
                  /* A00PGEINH  */
                  /* A00DARFO   */
  SetIfaNumErr( ifa->A00ANBNR ,            ifa->NB_PLAUSI, PL_A00ANBNR     );
  SetIfa2Err  ( ifa->A00ATYP  , ATYP	,  ifa->NB_PLAUSI, PL_A00ATYP      );
  SetIfaTrueFalse( TestEanNr(ifa->A00GTIN) == -1, ifa->NB_PLAUSI, PL_A00GTIN );
  SetIfaTrueFalse( TestEanNr(ifa->A00EAN) == -1, ifa->NB_PLAUSI, PL_A00EAN );
  SetIfaTrueFalse( TestEanNr(ifa->A00NTIN) == -1, ifa->NB_PLAUSI, PL_A00NTIN );
                  /* A00ARTNR */

  SetIfa2Err  ( ifa->A05VFDAT , BB_00_01,  ifa->NB_PLAUSI, PL_A05VFDAT  );
  SetIfaNumErr( ifa->A05LZEIT,             ifa->NB_PLAUSI, PL_A05LZEIT  );
  SetIfa2Err  ( ifa->A05KKETTE, BB_00_01,  ifa->NB_PLAUSI, PL_A05KKETTE );
                  /* A05TMAX */
                  /* A05TMIN */
  SetIfa2Err  ( ifa->A05LICHT,  BB_00_02,  ifa->NB_PLAUSI, PL_A05LICHT  );
  SetIfa2Err  ( ifa->A05FEUCHT, BB_00_01,  ifa->NB_PLAUSI, PL_A05FEUCHT );
  SetIfa2Err  ( ifa->A05LAGE,   BB_00_02,  ifa->NB_PLAUSI, PL_A05LAGE   );
  SetIfa2Err  ( ifa->A05ZERBR,  BB_00_01,  ifa->NB_PLAUSI, PL_A05ZERBR  );

                  /* A04LAENGE  */
                  /* A04HOEHE   */
                  /* A04BREITE  */
                  /* A04GWCHT   */

  SetIfaPdmErr( ifa->A01GEPDM,             ifa->NB_PLAUSI, PL_A01GEPDM  );

  SetIfa2Err  ( ifa->A01AMPVAMG, BB_00_02, ifa->NB_PLAUSI, PL_A01AMPVAMG  );
  SetIfa2Err  ( ifa->A01AMPVSGB, BB_00_02, ifa->NB_PLAUSI, PL_A01AMPVSGB );
  SetIfaPdmErr( ifa->A01ZBV,               ifa->NB_PLAUSI, PL_A01ZBV  );	/* EAVP */

  SetIfaPdmErr( ifa->A01AEPDM,             ifa->NB_PLAUSI, PL_A01AEPDM  );
  SetIfaPdmErr( ifa->A01AVPDM,             ifa->NB_PLAUSI, PL_A01AVPDM  );
  SetIfaPdmErr( ifa->A01UVP,		       ifa->NB_PLAUSI, PL_A01UVP  );
                  /* A01SUVP  */
                  /* A01SGEPDM  */
                  /* A01SAEPDM  */
                  /* A01SAVPDM  */

  SetIfaPdmErr( ifa->A01ERSTATT,           ifa->NB_PLAUSI, PL_A01SERSTAT  );

  SetIfa2Err  ( ifa->A01MWST,   BB_00_02,  ifa->NB_PLAUSI, PL_A01MWST   );

  SetIfa2Err  ( ifa->A02AM    , BB_00_01,  ifa->NB_PLAUSI, PL_A02AM     );
  SetIfa2Err  ( ifa->A02MP    , BB_00_01,  ifa->NB_PLAUSI, PL_A02MP     );
  SetIfa2Err  ( ifa->A02APPFL , BB_00_02,  ifa->NB_PLAUSI, PL_A02APPFL  );
  SetIfa2Err  ( ifa->A02VSPFL , BB_00_03,  ifa->NB_PLAUSI, PL_A02VSPFL  );
  SetIfa2Err  ( ifa->A02BTM   , BB_00_02,  ifa->NB_PLAUSI, PL_A02BTM    );
  SetIfa2Err  ( ifa->A02TFG   , BB_00_02,  ifa->NB_PLAUSI, PL_A02TFG    );
  SetIfa2Err  ( ifa->A02DROCH , BB_00_01,  ifa->NB_PLAUSI, PL_A02DROCH  );
  SetIfa2Err  ( ifa->A02TIERAM, BB_00_02,  ifa->NB_PLAUSI, PL_A02TIERAM );
  SetIfa2Err  ( ifa->A02NEGLIS, BB_00_02,  ifa->NB_PLAUSI, PL_A02NEGLIS );

  SetIfa2Err  ( ifa->A02HMZV,   BB_00_01,  ifa->NB_PLAUSI, PL_A02HMZV   );

  SetIfa2Err  ( ifa->A03VTSTAT, BB_00_02,  ifa->NB_PLAUSI, PL_A03VTSTAT );
  SetIfa2Err  ( ifa->A03VWGGH , BB_00_01,  ifa->NB_PLAUSI, PL_A03VWGGH  );
  SetIfa2Err  ( ifa->A03VWGAPO, BB_00_01,  ifa->NB_PLAUSI, PL_A03VWGAPO );
  SetIfa2Err  ( ifa->A03VWGKAP, BB_00_01,  ifa->NB_PLAUSI, PL_A03VWGKAP );
  SetIfa2Err  ( ifa->A03VWGSEH, BB_00_01,  ifa->NB_PLAUSI, PL_A03VWGSEH );
  SetIfa2Err  ( ifa->A03VKSTAT, BB_00_01,  ifa->NB_PLAUSI, PL_A03VKSTAT );

  SetIfaNumErr( ifa->A06PZNNF,             ifa->NB_PLAUSI, PL_A06PZNNF  );

  SetIfaZuzahlErr( ifa->ZUZAHL,            ifa->NB_PLAUSI, PL_ZUZAHL    );

  SetIfaTaxeErr( ifa->A01AMPVAMG, PL_A01AMPVAMG, ifa->A01AMPVSGB, PL_A01AMPVSGB, 
	             ifa->NB_PLAUSI, PL_TAXKENN );

 SetIfa2Err   ( ifa->A02LIFSTYL , LIFE012, ifa->NB_PLAUSI, PL_A02LIFSTYL );
 
 SetIfa2Err   ( ifa->A02AUSNREI , BB_00_01, ifa->NB_PLAUSI, PL_A02AUSNREI );
 SetIfa2Err   ( ifa->A02GENER ,   BB_00_01, ifa->NB_PLAUSI, PL_A02GENER );
 SetIfa2Err   ( ifa->A02SDB ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02SDB );

 SetIfa2Err   ( ifa->A02NEM ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02NEM );
 SetIfaNumErr ( ifa->A06PZNORIG,            ifa->NB_PLAUSI, PL_A06PZNORIG  );

 SetIfa2Err   ( ifa->A02LEBENSM,  BB_00_01_99, ifa->NB_PLAUSI, PL_A02LEBENSM   );
 SetIfa2Err   ( ifa->A02DIAET,    BB_00_01_99, ifa->NB_PLAUSI, PL_A02DIAET     );

 SetIfa2Err   ( ifa->A02HOMOEO ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02HOMOEO );
 SetIfa2Err   ( ifa->A02ANTHRO ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02ANTHRO );
 SetIfa2Err   ( ifa->A02PHYTO ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02PHYTO );
 SetIfa2Err   ( ifa->A02BIOZID ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02BIOZID );
 SetIfa2Err   ( ifa->A02PSM ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02PSM );
 SetIfa2Err   ( ifa->A02TREZEP ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02TREZEP );
 SetIfa2Err   ( ifa->A0247AMG ,	  BB_00_03, ifa->NB_PLAUSI, PL_A0247AMG );
 
  /* noch pruefen mit den x x x */
                   /* DATUMGUELIGAB immer richtig */

 // PL_A00PPN
 SetIfaPdmErr( ifa->A01AB130A2,					ifa->NB_PLAUSI, PL_A01SAB130A  );
 SetIfa2Err   ( ifa->A02VERIFIZ ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02VERIFIZ );
 SetIfa2Err   ( ifa->A0252B ,		BB_00_01,	ifa->NB_PLAUSI, PL_A0252B );
 
 // PL_A01RESERV1, PL_A01RESERV2, PL_A01RESERV3 --> Preise
 // PL_A02RESERV2, PL_A02RESERV3 --> 2-stellige KZ
 // SetIfa2Err   ( ifa->A02RESERV1 ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02RESERV1 );

	/* ab 01.04.2014 wird kein Erstattungsbetrag mehr geliefert! 
	if ( ifa->NB_PLAUSI[PL_A02RESERV1] != NOVALUE_PL ) // = Preisänderung
	{
		// Kennzeichnung, dass Abzug nach §130, aber gar kein Erstattungsbetrag angegeben
		if ( strcmp( ifa->A02RESERV1, "01" ) == 0  && ifa->A01ERSTATT == 0.0 )
			ifa->NB_PLAUSI[PL_ABZUG_130] = '1';
		else
			ifa->NB_PLAUSI[PL_ABZUG_130] = '0';
	} */
 
 //SetIfa2Err   ( ifa->A02130A18 ,	BB_00_01,	ifa->NB_PLAUSI, PL_A02130A18 );
 //SetIfa2Err   ( ifa->A02130A1A8 ,	BB_00_01,	ifa->NB_PLAUSI, PL_A02130A1A8 );
 SetIfa2Err   ( ifa->A02BIOSIEG ,		BB_00_01,	ifa->NB_PLAUSI, PL_A02BIOSIEG );
 SetIfa2Err   ( ifa->A02KOSMET ,		BB_00_01,	ifa->NB_PLAUSI, PL_A02KOSMET );
 SetIfa2Err   ( ifa->A02STERIL ,		BB_00_01,	ifa->NB_PLAUSI, PL_A02STERIL );

 SetIfa2Err  ( ifa->A02ELEKTRO,   BB_00_01,  ifa->NB_PLAUSI, PL_A02ELEKTRO   );
 SetIfa2Err  ( ifa->A02WIRKSTO,   BB_00_01,  ifa->NB_PLAUSI, PL_A02WIRKSTO   );

 SetIfa2Err   ( ifa->A02EB130B ,	  BB_00_03, ifa->NB_PLAUSI, PL_A02EB130B );
 SetIfa2Err   ( ifa->A02EXPLOS ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02EXPLOS );
 SetIfa2Err   ( ifa->A02BIOTECH ,	  BB_00_03, ifa->NB_PLAUSI, PL_A02BIOTECH );

 SetIfa2Err   ( ifa->A02STIFEAR ,	  BB_00_01, ifa->NB_PLAUSI, PL_A02STIFEAR );
 SetIfaCharNumErr(ifa->A02BATTREG, 0, 99999999, 8, ifa->NB_PLAUSI, PL_A02BATTREG);
 SetIfaCharNumErr(ifa->A02WEEEREG, 0, 99999999, 8, ifa->NB_PLAUSI, PL_A02WEEEREG);
 /* A02BATTG no longer delivered by IFA
    SetIfa2Err(ifa->A02BATTG, BB_00_01, ifa->NB_PLAUSI, PL_A02BATTG); */
 /* some fields are not char but short, for whatever reasons */
 
 SetIfaCharNumErr(ifa->A00OEVNR,  0,  99999, 5, ifa->NB_PLAUSI, PL_A00OEVNR);
 SetIfaCharNumErr(ifa->A00ZINNR,  0,  99999, 5, ifa->NB_PLAUSI, PL_A00ZINNR);
 SetIfaShortErr ( ifa->A02SWUNDB,  -1, 1,     ifa->NB_PLAUSI, PL_A02SWUNDB );
 SetIfaShort2Err( ifa->A02ATMP,    -1, 5, 99, ifa->NB_PLAUSI, PL_A02ATMP );
 SetIfaShortErr ( ifa->A02AUSIMPF, -1, 4,     ifa->NB_PLAUSI, PL_A02AUSIMPF );
 SetIfaShortErr ( ifa->A02EUNOVEL, -1, 3,     ifa->NB_PLAUSI, PL_A02EUNOVEL );
 // remaining fields are char again */
 SetIfa2Err   ( ifa->A02ORDRUG ,       BB_00_01, ifa->NB_PLAUSI, PL_A02ORDRUG );
 SetIfa2Err   ( ifa->A02BEDZUL ,       BB_00_01, ifa->NB_PLAUSI, PL_A02BEDZUL );
 SetIfa2Err   ( ifa->A02ZULAUSN ,      BB_00_01, ifa->NB_PLAUSI, PL_A02ZULAUSN );
 SetIfa2Err   ( ifa->A02AMNOG ,        BB_00_02, ifa->NB_PLAUSI, PL_A02AMNOG );
 SetIfa2Err   ( ifa->A02PRSTRMO ,      BB_00_03, ifa->NB_PLAUSI, PL_A02PRSTRMO );

 // IFA Version 20244
 SetIfa2Err( ifa->A02AMDARKI, BB_00_01, ifa->NB_PLAUSI, PL_A02AMDARKI );
 SetIfa2Err( ifa->A02AMAUFFB, BB_00_01, ifa->NB_PLAUSI, PL_A02AMAUFFB );
 SetIfa2Err( ifa->A02AMBEKI,  BB_00_02, ifa->NB_PLAUSI, PL_A02AMBEKI );
 SetIfa2Err( ifa->A02AMVEKRW, BB_00_02, ifa->NB_PLAUSI, PL_A02AMVEKRW );
 SetIfaNumErr( ifa->A01DAPU78,          ifa->NB_PLAUSI, PL_A01DAPU78 );
 SetIfaNumErr( ifa->A02D130A18,         ifa->NB_PLAUSI, PL_A02D130A18 );

 // IFA Version 20248
 SetIfa2Err( ifa->A02MEDCG,   BB_00_02, ifa->NB_PLAUSI, PL_A02MEDCG );
 SetIfa2Err( ifa->A05LGTMPB,  BB_00_01, ifa->NB_PLAUSI, PL_A05LGTMPB );

 // IFA Version 20252
 SetIfa2Err( ifa->A01B130B1C, BB_00_01, ifa->NB_PLAUSI, PL_A01B130B1C );
 SetIfaNumErr( ifa->A01DAT78,           ifa->NB_PLAUSI, PL_A01DAT78 );
 SetIfaPdmErr( ifa->A01RAB130A,         ifa->NB_PLAUSI, PL_A01RAB130A);
 SetIfaPdmErr( ifa->A01ZUZAH61,         ifa->NB_PLAUSI, PL_A01ZUZAH61);

}


static void FillIfaStatus( struct ZIFAART *ifa )
{
  int index;

  strcpy( ifa->IFASTATUS, " " );

  *ifa->IFASTATUS = IFASTATUS_FREIGEGEBEN;

  /* Bei Neuaufnahme eines geloeschten Artikels -> Sperren */
  if ( IsIfaFeldErr( ifa->NB_ZWING, ZW_LOESCH_KENN_NEU ) )
     *ifa->IFASTATUS = IFASTATUS_GESPERRT;

  /* Wenn Ifa-Satz unvollstandig ( zwingend ) */
  if ( IsIfaFeldErr( ifa->NB_ZWING, ZW_IFA_COMPLETE ) )
  {
      *ifa->IFASTATUS = IFASTATUS_GESPERRT;
      *ifa->AENDERUNG += 2; /* aus 0=Neuanlage wird 2=Neuanlage Ifa unvollst. */
                            /* aus 1=Aenderung wird 3=Aenderung Ifa unvollst. */
  }


  /* NBSTATUS */
  /* xxxx0000 */
  /*      !!L-----  NZ  */
  /*      !L------  ZW  */
  /*      L-------  PL  */


  strcpy( ifa->NBSTATUS,  "0" );

  index = IsIfaErr( ifa->NB_PLAUSI ) << 2;
  ifa->NBSTATUS[0] |= (char) index;

  index = IsIfaErr( ifa->NB_ZWING  ) << 1;
  ifa->NBSTATUS[0] |= (char) index;

  index = IsIfaErr( ifa->NB_NZWING  );
  ifa->NBSTATUS[0] |= (char) index;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Zifa-Satz einfuegen                                 *
 * ---------------------------------------------------------------------- */

static int fd_zifa;

static long PrepareZifa( char *errmld )
{
    long status;
    status = SqlPrepareInsert ( &fd_zifa, "zifaart", "*" );
    if ( status != 0 )
    {
      strcpy( errmld, "zifaart: " );
      strcat( errmld, DynErrmld() );
      fd_zifa = -1;
     }
    return status;
}

static long InsertZifa( char *errmld )
{
    long status;
    status = SqlExecutePrepare( fd_zifa, &ifa, NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "zifaart: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Artikel lesen                                       *
 * ---------------------------------------------------------------------- */

static int fd_zart;

static char* Proj_Zartikel =
             "ARTIKEL_NR,"       \
             "ERSATZ_NR,"        \
             "DATUM_AH,"         \
             "DATUM_AV,"         \
             "DATUM_IFALOESCH,"  \
             "TAXPFL,"           \
             "SONDERGROSSO,"     \
             "TAXPRUEFGROSSO,"   \
             "HERST_PROZENT,"    \
             "ARTIKEL_NAME,"     \
             "EINHEIT,"          \
             "DARREICHFORM,"     \
             "HERSTELLER_NR,"    \
             "REZEPTPFL,"        \
             "APOTHEKENPFL,"     \
             "VERTRBIND_IFA,"    \
             "NETTOARTIKEL,"     \
             "NICHTUEBERGH,"     \
             "NURKVA,"           \
			 "PREISSENKUNG,"     \
			 "RETOURENSPERRE,"   \
			 "NAHRUNGSTEST, "	 \
			 "BIOZID_VERORD, "	 \
			 "PFLSCHUTZ_VERORD, "\
			 "DATUM_PREISSENKUNG, "\
			 "KOSMETIKUM, "		 \
			 "ELEKTROSCHROTT, "  \
			 "G_UN_NR, "         \
             "BATTERIEGESETZ, "  \
             "FMD_RELEVANT, "    \
             "ARTIKEL_GESPERRT, "\
             "EAN_NICHTVORHANDEN, "\
             "SIDABLATT, "       \
             "BIOSIEGEL, "       \
             "MED_CANNABIS_GES ";

struct S_Zartikel
{
    long   ARTIKEL_NR;
    long   ERSATZ_NR;
    long   DATUM_AH;
    long   DATUM_AV;
    long   DATUM_IFALOESCH;
    char   TAXPFL[2];
    char   SONDERGROSSO[2];
    char   TAXPRUEFGROSSO[2];
    double HERST_PROZENT;

    char   ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME + 1];
    char   EINHEIT     [L_ZARTIKEL_EINHEIT + 1];
    char   DARREICHFORM[L_ZARTIKEL_DARREICHFORM + 1];
    long   HERSTELLER_NR ;
    char   REZEPTPFL[2];
    char   APOTHEKENPFL[2];
    char   VERTRBIND_IFA[2];
    char   NETTOARTIKEL[2];
    char   NICHTUEBERGH[2];
    char   NURKVA[2];

	char   PREISSENKUNG[2];
	char   RETOURENSPERRE[2];
	char   NAHRUNGSTEST[2];
	char   BIOZID_VERORD[2];
	char   PFLSCHUTZ_VERORD[2];
	long   DATUM_PREISSENKUNG;
	short  KOSMETIKUM;
	char   ELEKTROSCHROTT[2];
	char   G_UN_NR[5];
    char   BATTERIEGESETZ[2];
    short  FMD_RELEVANT;
    char   ARTIKEL_GESPERRT[2];
    char   EAN_NICHTVORHANDEN[2];
    char   SIDABLATT[2];
    short  BIOSIEGEL;
    short  MED_CANNABIS_GES;

/*
    char   KLINIKPACKUNG[2];
    long   LAENGE         ;
    long   HOEHE          ;
    long   BREITE         ;
    long   GEWICHT        ;
    long   LAUFZEITMONATE ;
*/
};


static struct S_Zartikel s_Zartikel;

static long DeclareZartikel( char *errmld )
{
    char sql[500];
    long status;

    sprintf( sql, "select %s from ZARTIKEL where ARTIKEL_NR=?", Proj_Zartikel );
    status = SqlDeclareCs( &fd_zart, sql, "ZARTIKEL.ARTIKEL_NR", NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "zartikel: " );
      strcat( errmld, DynErrmld() );
      fd_zart = -1;
     }
    return status;
}

static long ReadZartikel( long artikel_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_zart, &s_Zartikel, NULL, &artikel_nr, NULL );
    if ( !( status == 0 || status == 100 ))
    {
      strcpy( errmld, "zartikel: " );
      strcat( errmld, DynErrmld() );
    }
	else if (status == 100)
	{
		// init fields
		s_Zartikel.ARTIKEL_NR = artikel_nr;
		s_Zartikel.ERSATZ_NR = 0;
		s_Zartikel.DATUM_AH = 0;
		s_Zartikel.DATUM_AV = 0;
		s_Zartikel.DATUM_IFALOESCH = 0;
		strcpy(s_Zartikel.TAXPFL, "0");
		strcpy(s_Zartikel.SONDERGROSSO, " ");
		strcpy(s_Zartikel.TAXPRUEFGROSSO, "0");
		s_Zartikel.HERST_PROZENT = 0;

		strcpy(s_Zartikel.ARTIKEL_NAME, "");
		strcpy(s_Zartikel.EINHEIT, "");
		strcpy(s_Zartikel.DARREICHFORM, "");
		s_Zartikel.HERSTELLER_NR =  0;
		strcpy(s_Zartikel.REZEPTPFL, "0");
		strcpy(s_Zartikel.APOTHEKENPFL, "0" );
		strcpy(s_Zartikel.VERTRBIND_IFA, "0");
		strcpy(s_Zartikel.NETTOARTIKEL, "0");
		strcpy(s_Zartikel.NICHTUEBERGH, "0");
		strcpy(s_Zartikel.NURKVA, "0");

		strcpy(s_Zartikel.PREISSENKUNG, "0");
		strcpy(s_Zartikel.RETOURENSPERRE, "0");
		strcpy(s_Zartikel.NAHRUNGSTEST, " ");
		strcpy(s_Zartikel.BIOZID_VERORD, "0");
		strcpy(s_Zartikel.PFLSCHUTZ_VERORD, "N");
		s_Zartikel.DATUM_PREISSENKUNG = 0;
		s_Zartikel.KOSMETIKUM = 0;
		strcpy(s_Zartikel.ELEKTROSCHROTT, "N");
        strcpy(s_Zartikel.BATTERIEGESETZ, "N");
        s_Zartikel.FMD_RELEVANT = 0;
        strcpy(s_Zartikel.ARTIKEL_GESPERRT, "0");
        strcpy(s_Zartikel.EAN_NICHTVORHANDEN, "0");
        strcpy(s_Zartikel.SIDABLATT, "0");
        s_Zartikel.BIOSIEGEL = 0;
    }
    return status;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Artikel mit PZN_neu lesen                           *
 * ---------------------------------------------------------------------- */

static int fd_zersatz;

static char* Proj_Zersatz = "ARTIKEL_NR,ERSATZ_NR";

struct S_Zersatz
{
    long ARTIKEL_NR;
    long ERSATZ_NR;
};

static struct S_Zersatz s_Zersatz;

static long DeclareZersatz( char *errmld )
{
    char sql[200];
    long status;

    sprintf( sql, "select %s from ZARTIKEL where ARTIKEL_NR=?", Proj_Zersatz );
    status = SqlDeclareCs( &fd_zersatz, sql, "ZARTIKEL.ARTIKEL_NR", NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "zartikel: " );
      strcat( errmld, DynErrmld() );
      fd_zersatz = -1;
     }
    return status;
}

static long ReadZersatz( long artikel_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_zersatz, &s_Zersatz, NULL, &artikel_nr, NULL );
    if ( !( status == 0 || status == 100 ))
    {
      strcpy( errmld, "zartikel: " );
      strcat( errmld, DynErrmld() );
     }
    return status;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Ifa mit PZN_neu lesen                               *
 * ---------------------------------------------------------------------- */

static int fd_pznneu;

static long DeclareIfaViaPznNeu( char *errmld )
{
    char sql[200];
    long status;

    sprintf( sql, "select A00PZN from ZIFAART where IFANR=%ld and A00PZN=?",
                  ifadatumnr );

    status = SqlDeclareCs( &fd_pznneu, sql, "ZIFAART.A00PZN", NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "zifaart: " );
      strcat( errmld, DynErrmld() );
      fd_pznneu = -1;
     }
    return status;
}

static long ReadIfaViaPznNeu( long pzn, char *errmld )
{
    long status;
    long artikel_nr;
    status = SqlReadDeclCs( fd_pznneu, &artikel_nr, NULL, &pzn, NULL );
    if ( !( status == 0 || status == 100 ))
    {
      strcpy( errmld, "zifaart: " );
      strcat( errmld, DynErrmld() );
     }
    return status;
}


/* ---------------------------------------------------------------------- *
 * Funktion         : Preis   lesen                                       *
 * ---------------------------------------------------------------------- */

static int fd_zpreis;

static char* Proj_Zpreis = "DATUMGUELTIGAB,GROSSO,AEP,AVP,EAVP,HERST_PROZENT,KE_MWST";

struct S_Zpreis
{
   long    DATUMGUELTIGAB ;
   double  GROSSO         ;
   double  AEP            ;
   double  AVP            ;
   double  EAVP           ;
   double  HERST_PROZENT  ;
   char    KE_MWST    [2] ;
};

static struct S_Zpreis s_Zpreis;

static long DeclareZpreis( char *errmld )
{
    char sql[400];
    long status;

    sprintf( sql, "select %s from ZARTPREIS where ARTIKEL_NR=? " \
                  "and DATUMGUELTIGAB=" \
                  "(select max(DATUMGUELTIGAB) from ZARTPREIS where " \
                  "DATUMGUELTIGAB<=? " \
                  "and ARTIKEL_NR=?)",
                  Proj_Zpreis );

    status = SqlDeclareCs( &fd_zpreis, sql,
                           "ZARTPREIS.ARTIKEL_NR",
                           "ZARTPREIS.DATUMGUELTIGAB",
                           "ZARTPREIS.ARTIKEL_NR", NULL );

    if ( status != 0 )
    {
      strcpy( errmld, "zartpreis: " );
      strcat( errmld, DynErrmld() );
      fd_zpreis = -1;
    }
   return status;
}

static long ReadPreis( long artikel_nr, long datumgueltigab, char *errmld )
{
   long status;
   status = SqlReadDeclCs( fd_zpreis, &s_Zpreis, NULL,
                                      &artikel_nr, &datumgueltigab, &artikel_nr, NULL );
   if ( !( status == 0 || status == 100 ))
   {
     strcpy( errmld, "zartpreis: " );
     strcat( errmld, DynErrmld() );
     s_Zpreis.DATUMGUELTIGAB = 0;
     s_Zpreis.GROSSO = 0.0;
     s_Zpreis.AEP    = 0.0;
     s_Zpreis.AVP    = 0.0;
     s_Zpreis.EAVP   = 0.0;
     memset(s_Zpreis.KE_MWST,0,2);
   }
   return status;
}

#ifdef never
static long ReadAktuellePreisdaten(long artikel_nr, struct S_Zpreis* priceData, char* errmld)
{
    long status;

    status = SqlReadDeclCs(fd_zpreis, priceData, NULL,
        &artikel_nr, priceData->DATUMGUELTIGAB, &artikel_nr, NULL);
    
    if (status != 0)
    {
        strcpy(errmld, "zartpreis: ");
        strcat(errmld, DynErrmld());
    }
    return status;
}

static long ReadAktuellesPreisdatum( long artikel_nr, long *datumgueltigab, char *errmld )
{
   long status;
   struct S_Zpreis pr;

   status = SqlReadDeclCs( fd_zpreis, &pr, NULL,
                                      &artikel_nr, datumgueltigab, &artikel_nr, NULL );
   if ( status == 0 )
	 *datumgueltigab = pr.DATUMGUELTIGAB;
   else
   {
     strcpy( errmld, "zartpreis: " );
     strcat( errmld, DynErrmld() );
	 *datumgueltigab = 0;
   }
   return status;
}
#endif

/* ---------------------------------------------------------------------- *
 * Funktion         : Articlecode 1   lesen                                       *
 * ---------------------------------------------------------------------- */

static int fd_code1;

static char* Proj_Code1 = "ARTICLE_CODE";

struct S_Code1
{
   char ARTICLE_CODE [L_CARTICLECODES_ARTICLE_CODE + 1];
};

static struct S_Code1 s_Code1;

static long DeclareCode1( char *errmld )
{
    char sql[100];
    long status;
    sprintf( sql, "select %s from CARTICLECODES where CODE_TYPE=1 AND ARTICLENO=?", Proj_Code1 );
    status = SqlDeclareCs( &fd_code1, sql, "CARTICLECODES.ARTICLENO", NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "carticlecodes: " );
      strcat( errmld, DynErrmld() );
      fd_code1 = -1;
     }
    return status;
}

static long ReadCode1( long artikel_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_code1, &s_Code1, NULL, &artikel_nr, NULL );
    if ( !( status == 0 || status == 100 ))
    {
      strcpy( errmld, "carticlecodes 1: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Articlecode 2                                       *
 *                    lese articleno ueber article_code                   *
 * ---------------------------------------------------------------------- */

static int fd_code2;

struct S_Code2
{
    long ARTICLENO;
};

static struct S_Code2 s_Code2;

static long DeclareCode2(char* errmld)
{
    char sql[200];
    long status;
    sprintf(sql, "select ARTICLENO from CARTICLECODES where ARTICLE_CODE=? AND CODE_TYPE IN (SELECT code_type FROM ccodetypes WHERE artnr_substitute = 1)"); 
    status = SqlDeclareCs(&fd_code2, sql, "CARTICLECODES.ARTICLE_CODE", NULL);
    if (status != 0)
    {
        strcpy(errmld, "carticlecodes 2: ");
        strcat(errmld, DynErrmld());
        fd_code1 = -1;
    }
    return status;
}

static long ReadCode2(long article_code, char* errmld)
{
    long status;
    char strArticleCode[28];
    sprintf(strArticleCode, "%ld", article_code);
    status = SqlReadDeclCs(fd_code2, &s_Code2, NULL, strArticleCode, NULL);
    if (!(status == 0 || status == 100))
    {
      strcpy( errmld, "carticlecodes: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Ean     lesen                                       *
 * EAN 1: aktuelle EAN auf Basis der Artikel-Nr lesen
 * EAN 2: mögliche andere Artikel-Nr auf Basis der EAN lesen
 * EAN 3: mögliche Duplikate auf Bais der IFA Daten bei Artikeln die nicht
 *        gesperrt sind.
 * ---------------------------------------------------------------------- */

static int fd_ean1;

static char* Proj_Ean1 = "EAN_NR";

struct S_Ean1
{
   char EAN_NR [L_EAN_EAN_NR + 1];
};

static struct S_Ean1 s_Ean1;

static long DeclareEan1( char *errmld )
{
    char sql[100];
    long status;
    sprintf( sql, "select %s from EAN where ARTIKEL_NR=?", Proj_Ean1 );
    status = SqlDeclareCs( &fd_ean1, sql, "EAN.ARTIKEL_NR", NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "ean: " );
      strcat( errmld, DynErrmld() );
      fd_ean1 = -1;
     }
    return status;
}

static long ReadEan1( long artikel_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_ean1, &s_Ean1, NULL, &artikel_nr, NULL );
    if ( !( status == 0 || status == 100 ))
    {
      strcpy( errmld, "ean: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

static int fd_ean2;

static char* Proj_Ean2 = "ARTIKEL_NR";

struct S_Ean2
{
   long ARTIKEL_NR;
};

static struct S_Ean2 s_Ean2;

static long DeclareEan2( char *errmld )
{
    char sql[100];
    long status;
    sprintf( sql, "select %s from EAN where EAN_NR=?", Proj_Ean2 );
    status = SqlDeclareCs( &fd_ean2, sql, "EAN.EAN_NR", NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "ean: " );
      strcat( errmld, DynErrmld() );
      fd_ean2 = -1;
     }
    return status;
}

static long ReadEan2( char *ean_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_ean2, &s_Ean2, NULL, ean_nr, NULL );
    if ( !( status == 0 || status == 100 ))
    {
      strcpy( errmld, "ean: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}


/*
* Prüfung ob mehrere Einträge für Zartikel in IFA Datei mit gleicher EAN sind
* die später übernommen werden sollen. Der aktuelle IFA Eintrag wurde dabei noch
* nicht in die Tabelle geschrieben, aber der aktuelle Artikel-Eintrag ist gültig.
* Wenn also bereits ein aktiver Zartikel mit gleicher EAN in den IFA Daten vermerkt ist
* handelt es sich hierbei bereits um ein Duplikat und der aktuelle Eintrag kann nicht 
* mehr ohne manuelle Enscheidung bei welchem Eintrag die EAN übernommen werden soll
* weiter verabeitet werden.
*/
static int incArticleArraySize = 1000;
static int currentArticleEanArraySize = 0;
static int currentArticleEanEntries = 0;
static long long* activeArticleEanArray = NULL;

static long CheckDuplicateEanInMem(char* ean_nr, int isAenderung)
{
    // Prüfe ob EAN_NR leer oder aus 00000000000000 besteht
    long isDuplicate = 0; // false
    if (!isNullZeroOrEmpty(ean_nr) && ((isAenderung && s_Zartikel.ARTIKEL_GESPERRT[0] != '1') || !isAenderung))
    {
        // EAN für diesen Artikel gültig
        // Wenn die EAN bereit im Array enthalten ist, liegt ein Duplikat vor
        // Ansonsten wird die EAN jetzt im Array registriert und erst der nächste
        // aktive Artikel mit der gleichen EAN wird zum Duplikat.
        long long ean = 0;
        sscanf(ean_nr,"%lld",&ean);

        if (currentArticleEanArraySize <= currentArticleEanEntries)
        {
            if (currentArticleEanArraySize == 0)
            {
                currentArticleEanArraySize += incArticleArraySize;
                activeArticleEanArray = (long long*) calloc(currentArticleEanArraySize, sizeof(long long));
            }
            else if (activeArticleEanArray != NULL && currentArticleEanArraySize <= currentArticleEanEntries)
            {
                currentArticleEanArraySize += incArticleArraySize;
                activeArticleEanArray = (long long*)realloc(activeArticleEanArray, currentArticleEanArraySize * sizeof(long long));
            }
        }
        if (activeArticleEanArray != NULL)
        {
            int found = 0;
            for (int i = 0; i < currentArticleEanEntries; i++)
            {
                if (activeArticleEanArray[i] == ean)
                {
                    found = 1;
                    isDuplicate = 1;
                    break;
                }
            }
            if (!found)
            {
                activeArticleEanArray[currentArticleEanEntries] = ean;
                currentArticleEanEntries++;
            }
        }
        else
        {
            isDuplicate = 1; // eigentlich Fehlerfall weil kein Speicher allokiert wurde
        }
    }
    return isDuplicate;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : NTIN     lesen                                       *
 * ---------------------------------------------------------------------- */

static int fd_ntin1;

static char* Proj_Ntin1 = "ARTICLE_CODE";

struct S_Ntin1
{
   char ARTICLE_CODE [L_CARTICLECODES_ARTICLE_CODE + 1];
};

static struct S_Ntin1 s_Ntin1;

static long DeclareNtin1( char *errmld )
{
    char sql[100];
    long status;
    sprintf( sql, "select %s from CARTICLECODES where CODE_TYPE=22 AND ARTICLENO=?", Proj_Ntin1 );
    status = SqlDeclareCs( &fd_ntin1, sql, "CARTICLECODES.ARTICLENO", NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "carticlecodes(22): " );
      strcat( errmld, DynErrmld() );
      fd_ntin1 = -1;
     }
    return status;
}

static long ReadNtin1( long artikel_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_ntin1, &s_Ntin1, NULL, &artikel_nr, NULL );
    if ( !( status == 0 || status == 100 ))
    {
      strcpy( errmld, "carticlecodes(22): " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

static int fd_ntin2;

static char* Proj_Ntin2 = "ARTICLENO";

struct S_Ntin2
{
   long ARTICLENO;
};

static struct S_Ntin2 s_Ntin2;

static long DeclareNtin2( char *errmld )
{
    char sql[200];
    long status;
    sprintf( sql, "select %s from CARTICLECODES where CODE_TYPE = 22 and ARTICLENO!=? and ARTICLE_CODE=?", Proj_Ntin2 );
    status = SqlDeclareCs( &fd_ntin2, sql, "CARTICLECODES.ARTICLENO", "CARTICLECODES.ARTICLE_CODE", NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "carticlecodes: " );
      strcat( errmld, DynErrmld() );
      fd_ntin2 = -1;
     }
    return status;
}

static long ReadNtin2( char *ntin, long artikel_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_ntin2, &s_Ntin2, NULL, &artikel_nr, ntin, NULL );
    if ( !( status == 0 || status == 100 ))
    {
      strcpy( errmld, "carticlecodes: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

/*
* Prüfung ob mehrere Einträge für Zartikel in IFA Datei mit gleicher NTIN vorhanden sind
* die später übernommen werden sollen. Der aktuelle IFA Eintrag wurde dabei noch
* nicht in die Tabelle geschrieben, aber der aktuelle Artikel-Eintrag ist gültig.
* Wenn also bereits ein aktiver Zartikel mit gleicher EAN in den IFA Daten vermerkt ist
* handelt es sich hierbei bereits um ein Duplikat und der aktuelle Eintrag kann nicht
* mehr ohne manuelle Enscheidung bei welchem Eintrag die EAN übernommen werden soll
* weiter verabeitet werden.
*/


static int currentArticleNtinArraySize = 0;
static int currentArticleNtinEntries = 0;
static long long* activeArticleNtinArray = NULL;

static long CheckDuplicateNtinInMem(char* ntin_nr, int isAenderung)
{
    // Prüfe ob NTIN leer oder aus 00000000000000 besteht
    long isDuplicate = 0; // false
    if (!isNullZeroOrEmpty(ntin_nr) && ((isAenderung && s_Zartikel.ARTIKEL_GESPERRT[0] != '1') || !isAenderung))
    {
        // NTIN für diesen Artikel gültig
        // Wenn die EAN bereit im Array enthalten ist, liegt ein Duplikat vor
        // Ansonsten wird die EAN jetzt im Array registriert und erst der nächste
        // aktive Artikel mit der gleichen EAN wird zum Duplikat.
        long long ntin = 0;
        sscanf(ntin_nr,"%lld",&ntin);

        if (currentArticleNtinArraySize <= currentArticleNtinEntries)
        {
            if (currentArticleNtinArraySize == 0)
            {
                currentArticleNtinArraySize += incArticleArraySize;
                activeArticleNtinArray = (long long*)calloc(currentArticleNtinArraySize, sizeof(long long));
            }
            else if (activeArticleNtinArray != NULL && currentArticleNtinArraySize <= currentArticleNtinEntries)
            {
                currentArticleNtinArraySize += incArticleArraySize;
                activeArticleNtinArray = (long long*)realloc(activeArticleNtinArray, currentArticleNtinArraySize * sizeof(long long));
            }
        }
        if (activeArticleNtinArray != NULL)
        {
            int found = 0;
            for (int i = 0; i < currentArticleNtinEntries; i++)
            {
                if (activeArticleNtinArray[i] == ntin)
                {
                    found = 1;
                    isDuplicate = 1;
                    break;
                }
            }
            if (!found)
            {
                activeArticleNtinArray[currentArticleNtinEntries] = ntin;
                currentArticleNtinEntries++;
            }
        }
        else
        {
            isDuplicate = 1; // eingetlich Fehlerfall weil kein Speicher allokiert wurde
        }
    }
    return isDuplicate;
}


/* ---------------------------------------------------------------------- *
 * Funktion         : GTIN     lesen                                       *
 * ---------------------------------------------------------------------- */

static int fd_gtin1;

static char* Proj_Gtin1 = "ARTICLE_CODE";

struct S_Gtin1
{
    char ARTICLE_CODE[L_CARTICLECODES_ARTICLE_CODE + 1];
};

static struct S_Gtin1 s_Gtin1;

static long DeclareGtin1(char* errmld)
{
    char sql[100];
    long status;
    sprintf(sql, "select %s from CARTICLECODES where CODE_TYPE=26 AND ARTICLENO=?", Proj_Gtin1);
    status = SqlDeclareCs(&fd_gtin1, sql, "CARTICLECODES.ARTICLENO", NULL);
    if (status != 0)
    {
        strcpy(errmld, "gtin1 - declare carticlecodes(26): ");
        strcat(errmld, DynErrmld());
        fd_gtin1 = -1;
    }
    return status;
}

static long ReadGtin1(long artikel_nr, char* errmld)
{
    long status;
    status = SqlReadDeclCs(fd_gtin1, &s_Gtin1, NULL, &artikel_nr, NULL);
    if (!(status == 0 || status == 100))
    {
        strcpy(errmld, "gtin1 - read carticlecodes(26): ");
        strcat(errmld, DynErrmld());
    }
    return status;
}

static int fd_gtin2;

static char* Proj_Gtin2 = "ARTICLENO";

struct S_Gtin2
{
    long ARTICLENO;
};

static struct S_Gtin2 s_Gtin2;

static long DeclareGtin2(char* errmld)
{
    char sql[200];
    long status;
    sprintf(sql, "select %s from CARTICLECODES where CODE_TYPE = 26 and ARTICLENO!=? and ARTICLE_CODE=?", Proj_Ntin2);
    status = SqlDeclareCs(&fd_gtin2, sql, "CARTICLECODES.ARTICLENO", "CARTICLECODES.ARTICLE_CODE", NULL);
    if (status != 0)
    {
        strcpy(errmld, "gtin2 - declare carticlecodes: ");
        strcat(errmld, DynErrmld());
        fd_gtin2 = -1;
    }
    return status;
}

static long ReadGtin2(char* gtin, long artikel_nr, char* errmld)
{
    long status;
    status = SqlReadDeclCs(fd_gtin2, &s_Gtin2, NULL, &artikel_nr, gtin, NULL);
    if (!(status == 0 || status == 100))
    {
        strcpy(errmld, "gtin2 - read carticlecodes: ");
        strcat(errmld, DynErrmld());
    }
    return status;
}

/*
* Prüfung ob mehrere Einträge für Zartikel in IFA Datei mit gleicher GTIN sind
* die später übernommen werden sollen. Der aktuelle IFA Eintrag wurde dabei noch
* nicht in die Tabelle geschrieben, aber der aktuelle Artikel-Eintrag ist gültig.
* Wenn also bereits ein aktiver Zartikel mit gleicher EAN in den IFA Daten vermerkt ist
* handelt es sich hierbei bereits um ein Duplikat und der aktuelle Eintrag kann nicht
* mehr ohne manuelle Enscheidung bei welchem Eintrag die EAN übernommen werden soll
* weiter verabeitet werden.
*/

static int currentArticleGtinArraySize = 0;
static int currentArticleGtinEntries = 0;
static long long* activeArticleGtinArray = NULL;

static long CheckDuplicateGtinInMem(char* gtin_nr, int isAenderung)
{
    // Prüfe ob EAN_NR leer oder aus 00000000000000 besteht
    long isDuplicate = 0; // false
    if (!isNullZeroOrEmpty(gtin_nr) && ((isAenderung && s_Zartikel.ARTIKEL_GESPERRT[0] != '1') || !isAenderung))
    {
        // EAN für diesen Artikel gültig
        // Wenn die EAN bereit im Array enthalten ist, liegt ein Duplikat vor
        // Ansonsten wird die EAN jetzt im Array registriert und erst der nächste
        // aktive Artikel mit der gleichen EAN wird zum Duplikat.
        long long gtin = 0;
        sscanf(gtin_nr,"%lld",&gtin);

        if (currentArticleGtinArraySize <= currentArticleGtinEntries)
        {
            if (currentArticleGtinArraySize == 0)
            {
                currentArticleGtinArraySize += incArticleArraySize;
                activeArticleGtinArray = (long long*)calloc(currentArticleGtinArraySize, sizeof(long long));
            }
            else if (activeArticleGtinArray != NULL && currentArticleGtinArraySize <= currentArticleGtinEntries)
            {
                currentArticleGtinArraySize += incArticleArraySize;
                activeArticleGtinArray = (long long*)realloc(activeArticleGtinArray, currentArticleGtinArraySize * sizeof(long long));
            }
        }
        if (activeArticleGtinArray != NULL)
        {
            int found = 0;
            for (int i = 0; i < currentArticleGtinEntries; i++)
            {
                if (activeArticleGtinArray[i] == gtin)
                {
                    found = 1;
                    isDuplicate = 1;
                    break;
                }
            }
            if (!found)
            {
                activeArticleGtinArray[currentArticleGtinEntries] = gtin;
                currentArticleGtinEntries++;
            }
        }
        else
        {
            isDuplicate = 1; // eigentlich Speicherfehler, sollte aber nicht auftreten
        }
    }
    return isDuplicate;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Hersteller lesen                                    *
 * ---------------------------------------------------------------------- */

static int fd_herstel;

static char* Proj_Herstel = "HERSTELLER_NR,HERSTELL_VERGUETET";

struct S_Herstel
{
    long HERSTELLER_NR;
	char HERSTELL_VERGUETET[2];
};

static struct S_Herstel s_Herstel;

static long DeclareHerstel( char *errmld )
{
    char sql[200];
    long status;

    sprintf( sql,
             "select %s from HERSTEL where HERSTELLER_NR=?", Proj_Herstel );
    status = SqlDeclareCs( &fd_herstel, sql, "HERSTEL.HERSTELLER_NR", NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "herstel: " );
      strcat( errmld, DynErrmld() );
      fd_herstel = -1;
     }
    return status;
}

static long ReadHerstel( long hersteller_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_herstel, &s_Herstel, NULL,
                            &hersteller_nr, NULL );
    if ( !( status == 0 || status == 100 ))
    {
      strcpy( errmld, "herstel: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

static long LeseHersteller( long hersteller_nr, char *errmld )
{
    static long save_hersteller_nr = -1;
    static long save_status = 100;
    long status;

    /* Hersteller lesen */
    if ( hersteller_nr == save_hersteller_nr )
    {
       status = save_status;
    }
    else
    {
       status = ReadHerstel( hersteller_nr, errmld );
       save_status = status;
       save_hersteller_nr = hersteller_nr;
    }
    return status;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Preiserhoehungen                                    *
 * ---------------------------------------------------------------------- */


static int fd_zpreiserh;

static long PrepareZpreiserh( char *errmld )
{
    long status;
    status = SqlPrepareInsert ( &fd_zpreiserh, "zpreiserhoehung", PROJECTION_ZPREISERHOEHUNG );
    if ( status != 0 )
    {
      strcpy( errmld, "zpreiserhoehung: " );
      strcat( errmld, DynErrmld() );
      fd_zpreiserh = -1;
     }
    return status;
}


static long InsertZpreiserh(  char *errmld )
{
	int    b_insert;
	int    i_berechne;
    long   status;
	double grosso;
	int    za_stat;

	struct ZPREISERHOEHUNG pe;

	if ( ifa.DATUMGUELTIGAB <= tages_datum )
		return 0;

	za_stat = 0;

    b_insert = 0;
	i_berechne = 0;

	grosso = ifa.A01GEPDM;

	if ( grosso < 0.005 ) // IFA liefert Grosso = 0
		i_berechne = 1;
	else if (	(grosso > s_Zpreis.GROSSO + 0.001) ||	// Preiserhöhung
				(grosso < s_Zpreis.GROSSO - 0.001))		// Preissenkung
	{
		double diff;
		diff = grosso - ifa.A01AEPDM;
		if ( diff > -0.005 && diff < 0.005 )			// IFA liefert Grosso = AEP
			i_berechne = 2;
		else
			b_insert = 1;
	}

	if ( i_berechne != 0 )
	{
		if ( s_Zartikel.HERST_PROZENT <= -0.005 )
		{
			double wert;

			// Berechnung Grosso aus AEP und herst_prozent:
			wert = ifa.A01AEPDM*s_Zartikel.HERST_PROZENT/100.0;
			grosso = ifa.A01AEPDM + wert;
			KaufmRunden( &grosso, 2);

			b_insert =	(grosso > s_Zpreis.GROSSO + 0.001) || 
						(grosso < s_Zpreis.GROSSO - 0.001);
		}
		else if ( i_berechne == 2 ||							// Änderung Grosso, Grosso = AEP				
				 (ifa.A01AEPDM > s_Zpreis.AEP + 0.001) ||		// Grosso = 0, Änderung AEP
				 (ifa.A01AEPDM < s_Zpreis.AEP - 0.001)	)
		{
			za_stat  = 1;
			b_insert = 1;
		}
	}


	if ( b_insert == 0 )
		return 0;

    pe.ARTIKEL_NR     = ifa.A00PZN;
    pe.DATUMGUELTIGAB = ifa.DATUMGUELTIGAB;
    pe.GROSSO         = ifa.A01GEPDM;
    pe.AEP            = ifa.A01AEPDM;
    pe.GROSSO_ALT     = s_Zpreis.GROSSO;
    pe.AEP_ALT	      = s_Zpreis.AEP;
    pe.HERSTELLER_NR  = ifa.A00ANBNR;
    pe.DATUM_ANLAGE   = tages_datum;
	if ( za_stat == 0 )
		strcpy( pe.ZA_STATUS, "0" );
	else
		strcpy( pe.ZA_STATUS, "1" );

    status = SqlExecutePrepare( fd_zpreiserh, &pe, NULL );
	if ( status != 0 )
	{
		char sql[400];
		sprintf( sql,   "update ZPREISERHOEHUNG set " \
						"GROSSO=%f,"		\
						"AEP=%f,"			\
						"GROSSO_ALT=%f,"	\
						"AEP_ALT=%f,"		\
						"HERSTELLER_NR=%ld," \
						"DATUM_ANLAGE=%ld," \
						"ZA_STATUS=%s "		\
						"where ARTIKEL_NR=%ld and DATUMGUELTIGAB=%ld",
					    pe.GROSSO,
					    pe.AEP,
					    pe.GROSSO_ALT,
					    pe.AEP_ALT,
						pe.HERSTELLER_NR,
						pe.DATUM_ANLAGE,
						pe.ZA_STATUS,
					    pe.ARTIKEL_NR,
						pe.DATUMGUELTIGAB );

		status = SqlExecuteImm( sql );
		status = 0;	 /* !!!!!!!!!!!!!!!!! daran soll#s nicht scheitern */
	}
    if ( status != 0 )
    {
      strcpy( errmld, "zpreiserhoehung: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

static int TestRetourensperreBedingung()   // CPR-230035: wenn sich der AEP um >-10€ ändert soll eine Retourensperre gesetzt werden
{
    if (ifa.A01AEPDM < (s_Zpreis.AEP - 10.00))
        return 1;  // IsRetourensperre

    return 0;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : Preissenkungen    ( aut idem )                      *
 * ---------------------------------------------------------------------- */


/* merker fuer retourensperre */
/* insert into zautidemspere artikel_nr, ifa.DATUMGUELTIGAB */
/* oder update */

static long  MerkeAutidemSperre( long artikel_nr, long datum, char *errmld )
{
	long s;
	long datumgueltigab;
	char sql[100];
	sprintf( sql, "select artikel_nr,datumgueltigab from zautidemsperre where artikel_nr=%ld", 
		          artikel_nr );
	s = SqlRead( sql, &artikel_nr, &datumgueltigab, NULL );
	if ( s == 0 )
	{
		if ( datumgueltigab >= datum )
			return 0;
		sprintf( sql, "delete from zautidemsperre where artikel_nr=%ld", 
		               artikel_nr );		
		s = SqlExecuteImm( sql );
		if ( s != 0 )
		{
			strcpy( errmld, "zautidemsperre: " );
		    strcat( errmld, DynErrmld() );
			return s;
		}
	}

	sprintf( sql, "insert into zautidemsperre values (%ld, %ld)", 
		          artikel_nr, datum );	
	s = SqlExecuteImm( sql );
	if ( s != 0 )
    {
      strcpy( errmld, "zautidemsperre: " );
      strcat( errmld, DynErrmld() );
    }
	else if ( SqlRowsProcessed() != 1 )
	{
        sprintf( errmld, "zautidemsperre: Satz mit PZN=%ld wurde nicht eingefuegt",
			     artikel_nr);
		s = -1;
	}
	return s;
}

 /* -----  Zapflege  ------------------------- */

static int  Fd_Zapflege = -1;

static struct ZAPFLEGE Buf_zapflege;

int GetBufferDesc_Zapflege( char * errmld )
{
   char *tabelle = "zapflege";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zapflege >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zapflege, tabelle, PROJECTION_ZAPFLEGE,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zapflege = -1;
     return -1;
   }
   return 0;
}

long StoreRecord_Zapflege( long artikel_nr, long datum, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[50];

   Buf_zapflege.ARTIKEL_NR = artikel_nr;
   Buf_zapflege.DATUM      = datum;

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and DATUM=%ld",
                          Buf_zapflege.ARTIKEL_NR,
                          Buf_zapflege.DATUM );

   lStatus = FdReadRecord( Fd_Zapflege, PrimekeyCond,
                           &Buf_zapflege, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

   if ( lStatus == 100 )
   {
      Buf_zapflege.ARTIKEL_NR = artikel_nr;
      Buf_zapflege.DATUM      = datum;
      lStatus = FdWithoutWorkInsertRecord( Fd_Zapflege, &Buf_zapflege,
										   PrimekeyCond, cErrmld);
   }
   return lStatus;
}

/* ----- Zartikel ------------------------- */

static int  Fd_Zartikel = -1;

static struct ZARTIKEL Buf_zartikel;
static struct ZARTIKEL BufOld_zartikel;
static char CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];

static int GetBufferDesc_Zartikel( char * errmld )
{
    char *tabelle = "zartikel";
    long lStatus;
    char errstr[80];

    strcpy( errmld, "");
    if ( Fd_Zartikel >= 0 ) return 0;

    memset( CmpIndikator_Zartikel, '0', POSANZ_ZARTIKEL );
    CmpIndikator_Zartikel[POSANZ_ZARTIKEL] = '\0';
    CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_IFAAENDER] = '1';
    CmpIndikator_Zartikel[P_ZARTIKEL_BEARBEITER]      = '1';
    CmpIndikator_Zartikel[P_ZARTIKEL_PREISSENKUNG]    = '1';
    CmpIndikator_Zartikel[P_ZARTIKEL_RETOURENSPERRE]  = '1';

    lStatus = OpenBufferDescProj( &Fd_Zartikel, tabelle, PROJECTION_ZARTIKEL,
                                  CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errstr );
    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_Zartikel = -1;
      return -1;
    }
    return 0;
}

/* --- Prototyping Preise nach long --- */

static long GetIfaPreisLong( double preis );

static long GetPhosixPreisLong( double preis );


static long StoreRecord_Zartikel( long artikel_nr, long datum, char *user,
                                  char *preissenkung, char *retourensperre, long datum_preissenkung, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[50];
   char format[50];

   Buf_zartikel.ARTIKEL_NR = artikel_nr;

   strcpy( cErrmld, "" );

   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartikel.ARTIKEL_NR );

   lStatus = FdReadRecord( Fd_Zartikel, PrimekeyCond,
                           &Buf_zartikel, cErrmld );

   if ( lStatus != 0  ) return lStatus;

   BufOld_zartikel = Buf_zartikel;  /* gelesenen Satz sichern */

   Buf_zartikel.DATUM_IFAAENDER = datum;
   strcpy( Buf_zartikel.BEARBEITER, user );
   strcpy( Buf_zartikel.PREISSENKUNG, preissenkung  );
   Buf_zartikel.DATUM_PREISSENKUNG = datum_preissenkung; 
   
   /* Retourenserre setzen <-- wird nach CPR-230035 nicht mehr bei jeder Presisenkung gesetzt */
   // strcpy(Buf_zartikel.RETOURENSPERRE, retourensperre);

   lStatus = FdWithoutWorkUpdateRecord( Fd_Zartikel, &Buf_zartikel,
                                        &BufOld_zartikel,
                                        PrimekeyCond, cErrmld );
   return lStatus;
}

static long Store_Retourensperre(long artikel_nr, long datum, char* user, char* cErrmld)   // CPR-230035
{
    long lStatus;
    char PrimekeyCond[50];
    char format[50];

    Buf_zartikel.ARTIKEL_NR = artikel_nr;

    strcpy(cErrmld, "");

    sprintf(format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR);
    sprintf(PrimekeyCond, format, Buf_zartikel.ARTIKEL_NR);

    lStatus = FdReadRecord(Fd_Zartikel, PrimekeyCond,
        &Buf_zartikel, cErrmld);

    if (lStatus != 0) return lStatus;

    BufOld_zartikel = Buf_zartikel;  /* gelesenen Satz sichern */

    Buf_zartikel.DATUM_IFAAENDER = datum;
    strcpy(Buf_zartikel.BEARBEITER, user);

    /* Retourenserre setzen */
    strcpy(Buf_zartikel.RETOURENSPERRE, "1");

    lStatus = FdWithoutWorkUpdateRecord(Fd_Zartikel, &Buf_zartikel,
        &BufOld_zartikel,
        PrimekeyCond, cErrmld);


    return lStatus;
}

/*
herstel							 zartikel 
herstell_verguetet  erzeugt     preissenkung 
N                   erzeugt     1 
J                   erzeugt     2 
B                   erzeugt     4 
Preiserhöhung		erzeugt		9
Rest                erzeugt     5 
*/


static long MarkierePreissenkung( long artikel_nr, char *errmld )
{
	long s;
	char preissenkung[2];
	char retourensperre[2];
	long datum_preissenkung;
	
	datum_preissenkung = s_Zartikel.DATUM_PREISSENKUNG;		//default
	strcpy( retourensperre, s_Zartikel.RETOURENSPERRE );	//default
	strcpy( preissenkung, s_Zartikel.PREISSENKUNG );		//default

	/* nur bei Grosshandelsartikel  */
	if ( strcmp( ifa.A03VWGGH, "01") != 0 ) 
		return 0;

	/* nur bei Taxartikeln */
	if ( !( strcmp( ifa.A01AMPVAMG, "01") == 0 || strcmp( ifa.A01AMPVSGB, "01" ) == 0 ) )
		return 0;

	/* nur wenn Preissenkung */
    if ( GetIfaPreisLong( ifa.A01GEPDM ) >= GetPhosixPreisLong( s_Zpreis.GROSSO ) )
	{
		if ( GetIfaPreisLong( ifa.A01GEPDM ) == GetPhosixPreisLong( s_Zpreis.GROSSO ) )
		{
			return 0; // Grosso gleich geblieben (keine Erhöhung + keine Senkung)
		}
		else // ifa.GEP > GROSSO  --> Preiserhöhung
		{
			if ( ( GetIfaPreisLong( ifa.A01AEPDM ) <= GetPhosixPreisLong( s_Zpreis.AEP ) ) &&
				 ( strcmp( s_Zartikel.TAXPRUEFGROSSO, "1" ) == 0 )
			   )
			{
				return 0; // ifa.AEP <= AEP && Taxprüfgrosso-Artikel --> keine Preiserhöhung
			}
			else // tatsächliche Preiserhöhung ! 
			{
				/* nur bei zukuenftigen Aenderungen */
				if ( ifa.DATUMGUELTIGAB <= tages_datum )
					return 0;

				if ( s_Zartikel.DATUM_PREISSENKUNG != 0 )
				{
					if ( s_Zartikel.DATUM_PREISSENKUNG < ifa.DATUMGUELTIGAB )
						datum_preissenkung = ifa.DATUMGUELTIGAB;
					else
						return 0;
				}
				else // Datum Preissenkung nicht gesetzt!
				{
					strcpy( preissenkung, "9" );
					datum_preissenkung = ifa.DATUMGUELTIGAB;
				}

				if ( (strcmp( s_Zartikel.PREISSENKUNG, preissenkung ) == 0) && 
					 (datum_preissenkung == s_Zartikel.DATUM_PREISSENKUNG )		)
				{
					return 0;
				}
				else // KZ Preissenkung oder Datum_Preissenkung hat sich geändert!
				{
					return StoreRecord_Zartikel( artikel_nr, tages_datum, "IFA", preissenkung, retourensperre, 
													datum_preissenkung, errmld );
				}
			}
		}
	}
	
	/* bei Taxprüfgrosso-Artikeln preissenkung nur setzen, wenn sich auch der AEP tatsächlich senkt */
	if ( ( GetIfaPreisLong( ifa.A01AEPDM ) >= GetPhosixPreisLong( s_Zpreis.AEP ) ) &&
		 ( strcmp( s_Zartikel.TAXPRUEFGROSSO, "1" ) == 0 )
		)
		return 0;
	
	/* nur bei zukuenftigen Aenderungen */
	if ( ifa.DATUMGUELTIGAB <= tages_datum )
		return 0;

	// nur wenn Datum_Preissenkung nicht gesetzt!
	if ( s_Zartikel.DATUM_PREISSENKUNG != 0 )
	{
		if ( s_Zartikel.DATUM_PREISSENKUNG < ifa.DATUMGUELTIGAB )
			datum_preissenkung = ifa.DATUMGUELTIGAB;
	}
	else
	{
		/* neu lt. Heidicker 07.03.2003 */
		if ( s_Herstel.HERSTELL_VERGUETET[0] == 'N' )
			strcpy( preissenkung, "1" );
		else if ( s_Herstel.HERSTELL_VERGUETET[0] == 'J' )
			strcpy( preissenkung, "2" );
		else if ( s_Herstel.HERSTELL_VERGUETET[0] == 'B' )
			strcpy( preissenkung, "4" );
		else /*  if ( s_Herstel.HERSTELL_VERGUETET[0] == '0' ) */
			strcpy( preissenkung, "5" );
	
		datum_preissenkung = ifa.DATUMGUELTIGAB;
	}

	/* retourensperre setzen */
    // strcpy( retourensperre, "1" );  // wegen CPR-230035 raus

	/* keine Aenderung bei gleichen Wert */
	if ( strcmp( s_Zartikel.PREISSENKUNG,   preissenkung )   == 0	&&
		 datum_preissenkung == s_Zartikel.DATUM_PREISSENKUNG )
	{
		s = 0;
	}
	else
	{
		s = StoreRecord_Zartikel( artikel_nr, tages_datum, "IFA", preissenkung, retourensperre, 
									datum_preissenkung, errmld );

        /* wird nach CPR-230035 nicht mehr gebraucht */
        //if ( s == 0 &&  strcmp( s_Zartikel.RETOURENSPERRE, retourensperre ) != 0  )
        //	s = StoreRecord_Zapflege( artikel_nr, tages_datum, errmld );
	}

    /* wegen CPR-230035 kein Aufruf von MerkeAutidemSperre() mehr */

	return s;
}

static long SetzeRetourensperre(long artikel_nr, char* errmld)   // CPR-230035
{
    long s;
    int datum;

    s = Store_Retourensperre(artikel_nr, tages_datum, "IFA", errmld);

    if (s == 0)
    {
        s = StoreRecord_Zapflege(artikel_nr, tages_datum, errmld);
        if (s != 0)
            return s;

        // Eintrag aus zautidemsperre soll gelöscht werden, wenn ifa.DATUMGUELTIGAB das Tagesdatum ist
        // das Löschprogramm zpautidm löscht Eintrage mit Datum 14 tage zurück (Aufruf: 
        // durch Korrektur des Datums kann zpautidm wie für die bisherige Lösung genutzt werden
        datum = AddDayToPhoDate(ifa.DATUMGUELTIGAB, -14);

        /* merker fuer retourensperre */
        s = MerkeAutidemSperre(artikel_nr, datum, errmld);
    }

    return s;
}

/* ----------------- FDs ------------------------------- */

static void Init_All_FDs()
{
    fd_zpreis  = -1;
    fd_zart    = -1;
    fd_herstel = -1;
    fd_zersatz = -1;
    fd_pznneu  = -1;
    fd_ean1    = -1;
    fd_ean2    = -1;
	fd_code1   = -1;
    fd_code2   = -1;
	fd_ntin1   = -1;
	fd_ntin2   = -1;
	fd_gtin1   = -1;
	fd_gtin2   = -1;
    fd_zifa    = -1;
	fd_zpreiserh = -1;
	/* Juni 2002 aut idem */
    Fd_Zartikel = -1;
}

static void Close_All_FDs()
{
    if ( fd_zpreis    != -1 ) SqlCloseCs     ( fd_zpreis );
    if ( fd_zart      != -1 ) SqlCloseCs     ( fd_zart );
    if ( fd_zersatz   != -1 ) SqlCloseCs     ( fd_zersatz );
    if ( fd_pznneu    != -1 ) SqlCloseCs     ( fd_pznneu  );
    if ( fd_code1     != -1 ) SqlCloseCs     ( fd_code1  );
    if ( fd_code2     != -1 ) SqlCloseCs     ( fd_code2  );
	if ( fd_ntin1     != -1 ) SqlCloseCs     ( fd_ntin1  );
	if ( fd_ntin2     != -1 ) SqlCloseCs     ( fd_ntin2  );
	if ( fd_ean1      != -1 ) SqlCloseCs     ( fd_ean1  );
    if ( fd_ean2      != -1 ) SqlCloseCs     ( fd_ean2  );
    if ( fd_gtin1     != -1 ) SqlCloseCs     ( fd_gtin1  );
	if ( fd_gtin2     != -1 ) SqlCloseCs     ( fd_gtin2  );
    if ( fd_herstel   != -1 ) SqlCloseCs     ( fd_herstel );
    if ( fd_zifa      != -1 ) SqlFreePrepare ( fd_zifa );
    if ( fd_zpreiserh != -1 ) SqlFreePrepare ( fd_zpreiserh );

	/* Juni 2002 aut idem */
	{
	    char errmld[100];
		ClosePflege( errmld );
	}


    Init_All_FDs();

    Close_IfaOart_FDs();
}

static long Open_All_FDs( char *errmld )
{
    long status;

    Init_All_FDs();

    /* Taxtabelle lesen */
    if ( CreateTaxtab( errmld ) != 0 ) return -1;

    /* Zifa einfuegen */
    status = PrepareZifa( errmld );
    if ( status != 0 ) return status;

    /* Zartikel lesen */
    status =  DeclareZartikel( errmld );
    if ( status != 0 ) return status;

    /* ZPreis lesen */
    status =  DeclareZpreis( errmld );
    if ( status != 0 ) return status;

	/* Articlecode 1 EAR lesen */
    status =  DeclareCode1( errmld );
    if ( status != 0 ) return status;

    /* Articlecode 2 ATC lesen - Artikel Nummer bei Artikel Code */
    status = DeclareCode2(errmld);
    if (status != 0) return status;

    /* EAN  lesen */
    status = DeclareEan1(errmld);
    if (status != 0) return status;

    status = DeclareEan2(errmld);
    if (status != 0) return status;

	/* NTIN lesen */
    status =  DeclareNtin1( errmld );
    if ( status != 0 ) return status;

	status =  DeclareNtin2( errmld );
    if ( status != 0 ) return status;
	
    /* GTIN lesen */
    status = DeclareGtin1(errmld);
    if ( status != 0 ) return status;

    status = DeclareGtin2(errmld);
    if ( status != 0 ) return status;

    /* Ersatznr lesen */
    status =  DeclareZersatz( errmld );
    if ( status != 0 ) return status;

    /* Artikel aus Ifa lesen ueber PZNNF */
    status = DeclareIfaViaPznNeu( errmld );
    if ( status != 0 ) return status;

    /* Hersteller lesen */
    status =  DeclareHerstel( errmld );
    if ( status != 0 ) return status;

    /* IfaOart */
    status = Open_IfaOart_FDs( errmld );
    if ( status != 0 ) return status;

    /* Zpreiserhoehung einfuegen */
    status = PrepareZpreiserh( errmld );
    if ( status != 0 ) return status;

	/* Juni 2002 aut idem */
    status = OpenPflege( "IFA", errmld );
    if ( status != 0 ) return status;
    status = GetBufferDesc_Zartikel( errmld );
	if ( status != 0 ) return status;
    status = GetBufferDesc_Zapflege( errmld );
	if ( status != 0 ) return status;
	
    return 0;
}


/* ----------------- FDs Klinik ------------------------------- */
static int fd_zifaklinik_insert;
static int fd_zifaklinik_update;
static int fd_zifaklinik_read;

static void Init_All_FDs_Klinik()
{
    fd_zifaklinik_insert = -1;
	fd_zifaklinik_update = -1;
	fd_zifaklinik_read = -1;
}

static void Close_All_FDs_Klinik()
{
    if ( fd_zifaklinik_read != -1 ) 
		SqlCloseCs     ( fd_zifaklinik_read );

    if ( fd_zifaklinik_insert != -1 ) 
		SqlFreePrepare ( fd_zifaklinik_insert );

	if ( fd_zifaklinik_update != -1 ) 
		SqlFreePrepare ( fd_zifaklinik_update );

	Init_All_FDs_Klinik();
}


static struct ZIFAOKBS s_KlinikRead;

// ---------------------------------------------------------------------------------- //
static long DeclareReadKlinik( char *errmld )
{
    char sql[500];
    long status;

    sprintf( sql, "select * from zifaokbs where A00PZN=?" );

    status = SqlDeclareCs( &fd_zifaklinik_read, sql, "zifaokbs.A00PZN", NULL );
    
	if ( status != 0 )
    {
      strcpy( errmld, "zifaokbs: " );
      strcat( errmld, DynErrmld() );
      fd_zifaklinik_read = -1;
     }
    return status;
}

// ---------------------------------------------------------------------------------- //
static long ReadZifaKlinik( long artikel_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_zifaklinik_read, &s_KlinikRead, NULL,
                            &artikel_nr, NULL );

    if ( !( status == 0 || status == 100 ))
    {

      strcpy( errmld, "zifaokbs: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

// ---------------------------------------------------------------------------------- //
static long PrepareInsertKlinik( char *errmld )
{
    long status;
    status = SqlPrepareInsert ( &fd_zifaklinik_insert, "zifaokbs", "*" );
    if ( status != 0 )
    {
      strcpy( errmld, "zifaokbs: " );
      strcat( errmld, DynErrmld() );
      fd_zifaklinik_insert = -1;
     }
    return status;
}

// ---------------------------------------------------------------------------------- //
static long InsertKlinik( char *errmld )
{
    long status;
    status = SqlExecutePrepare( fd_zifaklinik_insert, &zklinik, NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "zifaokbs: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

// ---------------------------------------------------------------------------------- //
static long PrepareUpdateKlinik( char *errmld )
{
    long status;
    //status = SqlPrepareUpdate ( &fd_zifaklinik_update, "zifaokbs", "*", "where A00PZN=?" );
    status = SqlPrepareUpdate ( &fd_zifaklinik_update, "zifaokbs", 
								"A00PZN, A00GDAT, A00PBEZ, A00PGMENG, A00PGEINH, A00DARFO, A00ANBNR, A00ATYP, "
								"A00LKZ, A03GDAT, A03VTSTAT, A03VKSTAT, A06GDAT, A06PZNKP, IFANR, SATZNR, "
								"IFASTATUS, AENDERUNG, IFA_SATZART, STAND, A00PPN", 
								"where A00PZN=?" );
    if ( status != 0 )
    {
      strcpy( errmld, "zifaokbs: " );
      strcat( errmld, DynErrmld() );
      fd_zifaklinik_update = -1;
     }
    return status;
}

// ---------------------------------------------------------------------------------- //
static long UpdateKlinik( char *errmld )
{
    long status;
    // status = SqlExecutePrepare( fd_zifaklinik_update, &zklinik, &zklinik.A00PZN, NULL );
	status = SqlExecutePrepare( fd_zifaklinik_update, 
								&zklinik.A00PZN, &zklinik.A00GDAT, zklinik.A00PBEZ, zklinik.A00PGMENG, zklinik.A00PGEINH, 
								zklinik.A00DARFO, &zklinik.A00ANBNR, zklinik.A00ATYP, zklinik.A00LKZ, &zklinik.A03GDAT, 
								zklinik.A03VTSTAT, zklinik.A03VKSTAT, &zklinik.A06GDAT, &zklinik.A06PZNKP, &zklinik.IFANR, 
								&zklinik.SATZNR, zklinik.IFASTATUS, zklinik.AENDERUNG, zklinik.IFA_SATZART, &zklinik.STAND, zklinik.A00PPN,
								
								&zklinik.A00PZN, NULL );
    if ( status != 0 )
    {
      strcpy( errmld, "zifaokbs: " );
      strcat( errmld, DynErrmld() );
    }
    return status;
}

// ---------------------------------------------------------------------------------- //
static int Open_All_FDs_Klinik( char *errmld )
{
    long status;

    Init_All_FDs_Klinik();

	/* lesen */
    status =  DeclareReadKlinik( errmld );
    if ( status != 0 ) 
		return 1;

	/* schreiben */
    status = PrepareUpdateKlinik( errmld );
    if ( status != 0 ) 
		return 1;

	status = PrepareInsertKlinik( errmld );
    if ( status != 0 ) 
		return 1;

    return 0;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : I f a B e a r b e i t e                             *
 * ---------------------------------------------------------------------- *
 * Aufgabe          : Bearbeitet einen ZIFA-Satz                          *
 * Eingabe-Parameter: ifa  = Zeiger auf den Puffer mit dem Ifa-Satz       *
 * Return-Wert      : keiner                                              *
 * Info             : - Diese Funktion wird fuer jeden gelesenen Ifa-     *
 *                      Satz ausgefuehrt.                                 *
 * ---------------------------------------------------------------------- */


/* ---------- Test IFA auf "Keine Angabe" ---------------------------- */

static int TestNoValue( struct ZIFAART *ifa, char *wert, int pos )
{
   if ( *wert == '\0' )
   {
     ifa->NB_PLAUSI[ pos ] = NOVALUE_PL;
     return 1;
   }
   return 0;
}

// ---------------------------------------------------------------------------------- //
static int IsNoValue( struct ZIFAART *ifa, int pos )
{
   return ifa->NB_PLAUSI[ pos ] == NOVALUE_PL;
}

// ---------------------------------------------------------------------------------- //
static void ResetNoValue( struct ZIFAART *ifa, int pos )
{
   ifa->NB_PLAUSI[ pos ] = '0';
}

// ---------------------------------------------------------------------------------- //
/* -------- Preise ---------------- */
static int SindIfaPreisePlausibel( struct ZIFAART *ifa )
{

   /* Ifa-Preise 10-Stellig, Phoenix-Preise 9-stellig */
   if ( ifa->A01GEPDM > 9999999.99 ||
        ifa->A01AEPDM > 9999999.99 ||
        ifa->A01AVPDM > 9999999.99 ||
		ifa->A01UVP   > 9999999.99     )
   {
      SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_PREIS_ZUGROSS );
      return 1;
   }

   if ( !IsNoValue ( ifa, PL_A01GEPDM ) &&
        IsIfaFeldErr( ifa->NB_PLAUSI, PL_A01GEPDM   ) ) return 1;

   if ( !IsNoValue ( ifa, PL_A01AEPDM ) &&
        IsIfaFeldErr( ifa->NB_PLAUSI, PL_A01AEPDM   ) ) return 1;

   if ( !IsNoValue ( ifa, PL_A01AVPDM ) &&
        IsIfaFeldErr( ifa->NB_PLAUSI, PL_A01AVPDM   ) ) return 1;

   if ( !IsNoValue ( ifa, PL_A01AMPVAMG ) &&
        IsIfaFeldErr( ifa->NB_PLAUSI, PL_A01AMPVAMG ) ) return 1;

   if ( !IsNoValue ( ifa, PL_A01AMPVSGB ) &&
        IsIfaFeldErr( ifa->NB_PLAUSI, PL_A01AMPVSGB ) ) return 1;

   if ( !IsNoValue ( ifa, PL_A01UVP ) &&
        IsIfaFeldErr( ifa->NB_PLAUSI, PL_A01UVP ) ) return 1;

   if ( !IsNoValue ( ifa, PL_A01ZBV ) &&						 /* EAVP */
        IsIfaFeldErr( ifa->NB_PLAUSI, PL_A01ZBV   ) ) return 1;	 /* EAVP */	

   if ( !IsNoValue ( ifa, PL_A02APPFL ) &&
        IsIfaFeldErr( ifa->NB_PLAUSI, PL_A02APPFL   ) ) return 1;

   if ( !IsNoValue ( ifa, PL_A03VWGGH ) &&
        IsIfaFeldErr( ifa->NB_PLAUSI, PL_A03VWGGH  ) ) return 1;

   if ( !IsNoValue ( ifa, PL_A01MWST ) &&
        IsIfaFeldErr( ifa->NB_PLAUSI, PL_A01MWST  ) ) return 1;

   return 0;
}

// ---------------------------------------------------------------------------------- //
static int IstDasEinePreisAenderung( struct ZIFAART *ifa )
{
   if ( IsNoValue( ifa, PL_A01GEPDM ) &&
        IsNoValue( ifa, PL_A01UVP ) &&
        IsNoValue( ifa, PL_A01AEPDM ) &&
        IsNoValue( ifa, PL_A01AVPDM ) &&
        // IsNoValue( ifa, PL_A01SERSTAT ) &&  /* ab 01.04.2014 wird kein Erstattungsbetrag mehr geliefert! */
        IsNoValue( ifa, PL_A01MWST  ) &&
        // IsNoValue(ifa, PL_A01ZBV) &&  /* field no longer in ifa version 248 */
        IsNoValue( ifa, PL_A01AMPVAMG ) &&
        IsNoValue( ifa, PL_A01AMPVSGB ) &&
        IsNoValue( ifa, PL_A02APPFL ) &&
		// IsNoValue( ifa, PL_A02RESERV1 ) && 
		IsNoValue( ifa, PL_A02EB130B ) && 
		IsNoValue( ifa, PL_A02VSPFL ) &&		/* 29.03.2001 */
        IsNoValue( ifa, PL_A03VWGGH )     )
      return 0;

   ResetNoValue( ifa, PL_A01GEPDM );
   ResetNoValue( ifa, PL_A01AEPDM );
   ResetNoValue( ifa, PL_A01AVPDM );
   // ResetNoValue( ifa, PL_A01SERSTAT );   /* ab 01.04.2014 wird kein Erstattungsbetrag mehr geliefert! */
   ResetNoValue( ifa, PL_A01MWST  );
   // ResetNoValue( ifa, PL_A01ZBV  );  /* field no longer in ifa version 248 */
   ResetNoValue( ifa, PL_A01UVP  );		
   ResetNoValue( ifa, PL_A01AMPVAMG );
   ResetNoValue( ifa, PL_A01AMPVSGB );
   ResetNoValue( ifa, PL_A02TIERAM );   /* 18.12.2003 Taxkenn auch von tieram abhaengig */
   ResetNoValue( ifa, PL_A02APPFL );
   //ResetNoValue( ifa, PL_A02RESERV1 ); 
   ResetNoValue( ifa, PL_A02EB130B ); 
   ResetNoValue( ifa, PL_A02VSPFL );	/* 29.03.2001 */
   ResetNoValue( ifa, PL_A03VWGGH );
   return 1;
}

// ---------------------------------------------------------------------------------- //
/* --- Preise nach long --- */
static long GetIfaPreisLong( double preis )
{
  return (long)( preis*100.0 + 0.1 );
}

// ---------------------------------------------------------------------------------- //
static long GetPhosixPreisLong( double preis )
{
  return (long)( preis*100.0 + 0.1 );
}

// ---------------------------------------------------------------------------------- //
static long GetPhosixProzent( double proz )
{
   if ( proz >= 0.005 )
    return (long)( proz*100.0 + 0.1 );
   else if ( proz <= -0.005 )
    return (long)( proz*100.0 - 0.1 );
   else
    return 0;
}


// ---------------------------------------------------------------------------------- //
/* --- SonderGrosso Testen --- */
static void TestSonderGrosso( char SonderGrosso,
                              long IfaGro, long IfaAep,
                              long ArtGro, long ArtAep  )
{
   SetIfaTrueFalse( SonderGrosso == 'S',
                    ifa.NB_ZWING, ZW_SONDER_GEP );

   SetIfaTrueFalse( SonderGrosso == 'R',
                    ifa.NB_ZWING, ZW_REWE_SONDER_GEP );

   SetIfaTrueFalse( IfaGro != ArtGro && SonderGrosso == 'E',
                    ifa.NB_ZWING, ZW_GEP_TROTZ_PPE );

   SetIfaTrueFalse( IfaGro != ArtGro && SonderGrosso == 'P',
                    ifa.NB_ZWING, ZW_GEP_TROTZ_PARAM );

   SetIfaTrueFalse( IfaAep != ArtAep && SonderGrosso == 'E',
                    ifa.NB_ZWING, ZW_AEP_TROTZ_PPE );

   SetIfaTrueFalse( IfaAep != ArtAep && SonderGrosso == 'P',
                    ifa.NB_ZWING, ZW_AEP_TROTZ_PARAM );
}

// ---------------------------------------------------------------------------------- //
static int IstMWSTgleich( char *ifa_mwst, char art_mwst )
{
  if ( art_mwst == '0' )       /* voll */
      return strcmp( ifa_mwst, "00" ) == 0 ||
             strcmp( ifa_mwst, "  " ) == 0    ;
  else if ( art_mwst == '1' )  /* halb */
      return  strcmp( ifa_mwst, "01" ) == 0;
  else                         /* ohne */
      return  strcmp( ifa_mwst, "02" ) == 0;
}


// ---------------------------------------------------------------------------------- //
static int IsIfaLoschung( struct ZIFAART *ifa )
{
   if ( !IsIfaFeldErr( ifa->NB_PLAUSI, PL_A00LKZ )   &&
        !IsIfaFeldErr( ifa->NB_PLAUSI, PL_A00SSATZ )    )

     return *ifa->A00LKZ == 'X' || *ifa->A00SSATZ == '2';
   else
     return 0;
}

/* Semantische Prüfung IFA Elektroartikel Attribute
       - A02ELEKTRO - Wertebereich 00, 01 oder leer --> wurde bei Plausicheck überprüft
       - A02STIFEAR - Wertebereich 00, 01 oder leer --> wurde bei Plausicheck überprüft
       - A02BATTREG - Wertebereit 0 - 99999999 oder leer --> wurde bei Plausicheck überprüft
       - A02WEEEREG - Wertebereich 0 - 99999999 oder leer --> wurde bei Plausicheck überprüft
       - Wenn A02STIFEAR = 01 dann muss A02BATTREG und/oder A02WEEREG gesetzt sein
*/
static int TestIfaElectricValuesSemanticIntegrity(struct ZIFAART* ifa)
{
    int valid = 1;
    if (ifa != NULL)
    {
        int isA02STIFEAR = (strcmp(ifa->A02STIFEAR, "01") == 0);
        int isA02ELEKTRO = (strcmp(ifa->A02ELEKTRO, "01") == 0);
        int hasA02BATTREG = !isNullZeroOrEmpty(ifa->A02BATTREG);
        int hasA02WEEEREG = !isNullZeroOrEmpty(ifa->A02WEEEREG);

        if (  (ifa->NB_PLAUSI[PL_A02ELEKTRO] == '1') || 
              (ifa->NB_PLAUSI[PL_A02STIFEAR] == '1') ||
              (ifa->NB_PLAUSI[PL_A02BATTREG] == '1') ||
              (ifa->NB_PLAUSI[PL_A02WEEEREG] == '1')
           )
        {
            // furthter validation on valid data only
            valid = 0;
        }
        if (valid && !IsNoValue(ifa, PL_A02STIFEAR))
        {
            if (isA02STIFEAR)
            {
                if (!hasA02WEEEREG && !hasA02BATTREG)
                {
                    SetIfaTrueFalse(1, ifa->NB_NZWING, NZ_EAR_REG_MISSING);
                        valid = 0;
                }
                else if (hasA02BATTREG)
                {
                    strcpy(ifa->A02BATTG, "01");
                }
            }
            else if (hasA02WEEEREG || hasA02BATTREG)
            {
                SetIfaTrueFalse(1, ifa->NB_NZWING, NZ_EAR_REG_REDUNDANT);
                valid = 0;
            }
        }
    }
    else
    {
        valid = 0;
    }
    return valid;
}

// ---------------------------------------------------------------------------------- //
static int ScanIfaAenderung( long artikel_nr, int *IsZartpreisGelesen, 
							 int *PreisdatumKannVerglichenWerden, char *errmld )
{
   long status;
   int  IsTaxPruefGrosso;
   int  IsPreisPlausibel;
   int  IsPreisAenderung;

   /* 26.11.2002: neu wegen Preiserhoehungen */
   *IsZartpreisGelesen = 0;

   /* neu: das zuerst, dann Plausi-Pruefung */
   IsPreisAenderung = IstDasEinePreisAenderung( &ifa );

   /* --- Plausibilitaetspruefung (ohne Preispruefung) --- */
   FillIfaPlausiErr( &ifa );

   strcpy( ifa.AENDERUNG, "1"  );  /* Aenderung */

   IsTaxPruefGrosso = *s_Zartikel.TAXPRUEFGROSSO == '1';

   /* --- Aenderung bei IFA-Loeschung --- */
   if ( IsIfaLoschung( &ifa ) )
   {
      SetIfaTrueFalse( s_Zartikel.DATUM_AH == 0,
                       ifa.NB_NZWING, NZ_LOESCH_AH_AV );
     /* Keine weitere Pruefung bei Loeschung */
      return 1;
   }

    /* MAIL Peetz vom 8.11.2000: immer setzen  */
/*  if ( ! IsNoValue ( &ifa, PL_A03VTSTAT ) )  */
        SetIfaTrueFalse( strcmp( ifa.A03VTSTAT, "00" ) != 0 &&
                         s_Zartikel.DATUM_AH != 0,
                         ifa.NB_NZWING, NZ_AEN_BEI_AH );

	/* Ermittlung nicht zwingender Fehler aus A02NEM / A02DIAET / A02LEBENSM */
	if ( !IsNoValue(&ifa, PL_A02NEM) || !IsNoValue(&ifa, PL_A02DIAET) || !IsNoValue(&ifa, PL_A02LEBENSM) ) 
	{
		if ( strcmp (ifa.A02NEM, "01") != 0 ) // A02NEM == "00" || A02NEM == "  "
		{
			if ( strcmp(ifa.A02DIAET, "01") == 0 || strcmp(ifa.A02DIAET, "99") == 0) 
			{
				if ( strcmp(ifa.A02LEBENSM, "01") == 0) 		
					SetIfaTrueFalse(  (strcmp( s_Zartikel.NAHRUNGSTEST, " " ) == 0) || 
									  (strcmp( s_Zartikel.NAHRUNGSTEST, "K" ) == 0) || 
									  (strcmp( s_Zartikel.NAHRUNGSTEST, "F" ) == 0) 
									, ifa.NB_NZWING, NZ_NEM_DLM_LM_NEU );
			}
			else // A02DIAET == "00" || A02DIAET == "  "
			{
				if ( strcmp(ifa.A02LEBENSM, "00") == 0)
					SetIfaTrueFalse(  strcmp( s_Zartikel.NAHRUNGSTEST, " " ) != 0 , ifa.NB_NZWING, NZ_AEND_NEM );
				else if ( strcmp(ifa.A02LEBENSM, "99") == 0)
					SetIfaTrueFalse(  (strcmp( s_Zartikel.NAHRUNGSTEST, " " ) == 0) || 
									  (strcmp( s_Zartikel.NAHRUNGSTEST, "K" ) == 0) || 
									  (strcmp( s_Zartikel.NAHRUNGSTEST, "D" ) == 0) 
									, ifa.NB_NZWING, NZ_NEM_DLM_LM_NEU );
			}
		}
		else // A02NEM == "01"
		{
			if ( (strcmp(ifa.A02LEBENSM, "01") == 0) && 
				((strcmp(ifa.A02DIAET, "  ") == 0) || (strcmp(ifa.A02DIAET, "00") == 0)) )
					SetIfaTrueFalse(  (strcmp( s_Zartikel.NAHRUNGSTEST, " " ) == 0) || 
									  (strcmp( s_Zartikel.NAHRUNGSTEST, "D" ) == 0) || 
									  (strcmp( s_Zartikel.NAHRUNGSTEST, "F" ) == 0) 
									, ifa.NB_NZWING, NZ_NEM_DLM_LM_NEU );
		}
	}

	/* Ermittlung nicht zwingender Fehler aus A02BIOZID */
	if ( !IsNoValue(&ifa, PL_A02BIOZID) ) 
	{
		if ( strcmp (ifa.A02BIOZID, "01") != 0 ) // Änderung auf A02BIOZID == "00" || A02BIOZID == "  "
		{
			SetIfaTrueFalse(  strcmp( s_Zartikel.BIOZID_VERORD, "1" ) == 0 ,
							  ifa.NB_NZWING, NZ_NO_BIOZID );
		}
        // Aenderung auf A02BIOZID == "01"
        else if (strcmp(ifa.A02BIOZID, "01") == 0 && strcmp(s_Zartikel.BIOZID_VERORD, "0") == 0)
        {
            SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_CHG_BIOZID);
        }
    }

	/* Ermittlung nicht zwingender Fehler aus A02KOSMET */
	if ( !IsNoValue(&ifa, PL_A02KOSMET) ) 
	{
		if ( strcmp (ifa.A02KOSMET, "01") != 0 ) // Änderung auf A02KOSMET == "00" || A02KOSMET == "  "
		{
			SetIfaTrueFalse(  s_Zartikel.KOSMETIKUM == 1 ,
							  ifa.NB_NZWING, NZ_NO_KOSMETIKUM );
		}
	}
	
	/* Ermittlung nicht zwingender Fehler aus A02PSM */
	if ( !IsNoValue(&ifa, PL_A02PSM) ) 
	{
		if ( strcmp (ifa.A02PSM, "01") != 0 ) // Änderung auf A02PSM == "00" || A02PSM == "  "
		{
			SetIfaTrueFalse(  strcmp( s_Zartikel.PFLSCHUTZ_VERORD, "N" ) != 0 ,
							  ifa.NB_NZWING, NZ_NO_PSM );
		}
        // Aenderung von 00 -> 01
        else if (strcmp(ifa.A02PSM, "01") == 0 && strcmp(s_Zartikel.PFLSCHUTZ_VERORD, "N") == 0)
        {
            SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_CHG_PSM);
        }
    }

	/* Ermittlung nicht zwingender Fehler aus A02UNNR bei Artikel- Änderungen --> NZ_UNNR_DIFF */
	if (  !IsNoValue ( &ifa, PL_A02UNNR ) && strcmp (ifa.A02UNNR, "0   ") != 0 ) 
	{
		if ( strncmp (ifa.A02UNNR, s_Zartikel.G_UN_NR, L_ZIFAOART_A02UNNR) != 0 )
		{
			SetIfaTrueFalse(  1, ifa.NB_NZWING, NZ_UNNR_DIFF );
		}
	}

    /* Ermittlung nicht zwingender Fehler aus A02SDB bei Artikel-Aenderungen --> NZ_CHG_SIDABLATT */
    if ( !IsNoValue( &ifa, PL_A02SDB ) )
    {
        if ((strcmp(ifa.A02SDB, "01") == 0 && strcmp(s_Zartikel.SIDABLATT, "0") == 0) ||
            (strcmp(ifa.A02SDB, "01") != 0 && strcmp(s_Zartikel.SIDABLATT, "1") == 0))
        {
            SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_CHG_SIDABLATT);
        }
    }

    /* Ermittlung nicht zwingender Fehler aus A02BIOSIEG bei Artikel-Aenderungen --> NZ_CHG_BIOSIEGEL */
    if (!IsNoValue(&ifa, PL_A02BIOSIEG))
    {
        if ((strcmp(ifa.A02BIOSIEG, "01") == 0 && s_Zartikel.BIOSIEGEL == 0) ||
            (strcmp(ifa.A02BIOSIEG, "01") != 0 && s_Zartikel.BIOSIEGEL == 1))
        {
            SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_CHG_BIOSIEGEL);
        }
    }

    /* Ermittlung nicht zwingender Fehler aus A05LZEIT bei Artikel-Aenderungen --> NZ_CHG_LZEIT */
    if (!IsNoValue(&ifa, PL_A05LZEIT))
    {
        // Meldung bei Laufzeit > 0 und != 15
        if (ifa.A05LZEIT > 0 && ifa.A05LZEIT != 15)
        {
            SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_CHG_LZEIT);
        }
    }

    /* IFA Version 20248: Nicht zwingenden Fehler nicht mehr setzen 
    if (!IsNoValue(&ifa, PL_A02EUNOVEL))
    {
        if (ifa.A02EUNOVEL == 3)
        {
            SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_NOVEL_FOOD);
        }
    } */

    /* -------- Nicht zwingender Fehler (Aenderung MedCanG), IFA Version 20248 ------ */
    if (!IsNoValue(&ifa, PL_A02MEDCG))
    {
        if ( (strcmp(ifa.A02MEDCG, "01") == 0 || strcmp(ifa.A02MEDCG, "02") == 0) &&
              s_Zartikel.MED_CANNABIS_GES == 0 )
        {   // Flag wird gesetzt
            SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_CHG_MEDCANG_SET);
        }
        else if (strcmp(ifa.A02MEDCG, "01") != 0 &&
                 strcmp(ifa.A02MEDCG, "02") != 0 &&
                 s_Zartikel.MED_CANNABIS_GES > 0 )
        {   // Flag wird zurueckgesetzt
            SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_CHG_MEDCANG_RESET);
        }
    }

    /* Ermittlung zwingender Fehler aus A02APPFL bei Artikel-Aenderungen --> ZW_CHG_APPFL */
    if (!IsNoValue(&ifa, PL_A02APPFL))
    {
        /* Fehler, wenn sich der alte und der neue IFA Wert von A02APPFL unterscheiden */
        if ((strcmp(ifa.A02APPFL, "01") == 0 && strcmp(old_oifa.A02APPFL, "00") == 0) ||
            (strcmp(ifa.A02APPFL, "00") == 0 && strcmp(old_oifa.A02APPFL, "01") == 0))
        {
            SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_CHG_APPFL);
        }
    }

    /* Ermittlung zwingender Fehler aus A02VSPFL bei Artikel-Aenderungen --> ZW_CHG_VSPFL */
    if (!IsNoValue(&ifa, PL_A02VSPFL))
    {
        /* Fehler, wenn sich der alte und der neue IFA Wert von A02VSPFL unterscheiden */
        if ((strcmp(ifa.A02VSPFL, "01") == 0 && strcmp(old_oifa.A02VSPFL, "00") == 0) ||
            (strcmp(ifa.A02VSPFL, "00") == 0 && strcmp(old_oifa.A02VSPFL, "01") == 0))
        {
            SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_CHG_VSPFL);
        }
    }

    /* Emittlung zwingender und nicht zwingender Fehler aus der semantischen Prüfung von Elektrokennzeichen
      A02ELEKTRO, A02STIFEAR, A02BATTG, A02BATTREG, A02WEEEREG */

   if (TestIfaElectricValuesSemanticIntegrity(&ifa) /* && s_Zartikel.ARTIKEL_GESPERRT[0] == '0' */)
   {
       // Wenn keine semantischen Fehler innerhalb der Daten vorliegen, werden die IFA Änderungen im Bestand
       // überprüft
       int isA02ELEKTRO = (strcmp(ifa.A02ELEKTRO, "01") == 0);
       int isA02STIFEAR = (strcmp(ifa.A02STIFEAR, "01") == 0);
       int hasA02BATTREG = !isNullZeroOrEmpty(ifa.A02BATTREG);
       int hasA02WEEEREG = !isNullZeroOrEmpty(ifa.A02WEEEREG);
       int hasEAR = 0; /* EAR für registrierte Elektroartikel kann manuell über Hersteller erfasst worden sein. */
       char currentEAR[26];
       memset(currentEAR, 0, 25);

       if (ReadCode1(s_Zartikel.ARTIKEL_NR, errmld) == 0)
       {
           hasEAR = 1;
           strcpy(currentEAR, s_Code1.ARTICLE_CODE);
       }

       /* Prüfung A02ELEKTRO - Elektroartikel unterliegt der Elektrostoffverordnung die bestimmte Werkstoffe bei
          Elektroartikeln verbietet oder vorschreibt. */
       /* 00 unterliegt nicht der ElektroStoffV
          01 unterliegt der ElektroStoffV
          leer keine Angabe */

       if (!isA02ELEKTRO) 
       {
           /* s_Zartikel.ELEKTROSCHROTT = 'N' ist zulässig */
           /* s_Zartikel.ELEKTROSCHROTT = 'I' ist zulässig - kann nicht aus IFA Daten abgeleitet werden */
           if (s_Zartikel.ELEKTROSCHROTT[0] == 'J')
           {
               /* Die IFA Daten geben keine Auskunft darüber ob ein Artikel ein Elektroartikel ist oder nicht
                  Die IFA Daten lassen nur Rückschlüsse auf Stiftung EAR oder ElektroStoffV zu*/

               if (isA02STIFEAR && hasA02WEEEREG)
               {
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_CHG_ELECTRO_REG);
                   /* Bei Datenübernahme wird der Wert für ELEKTROSCHROTT auf 'R' geändert und ggf. A02WEEEREG als EAR übernommen */
               }
               else if ((s_Zartikel.BATTERIEGESETZ[0] != 'N') || !isA02STIFEAR)
               {
                   /* Es kann sich um einen rein Batterie bestriebenes Elektroartikel handeln */
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_UNKNOWN_ELECTRO);
               }
           }
           else if (s_Zartikel.ELEKTROSCHROTT[0] == 'R')
           {
               /* Bei einem registrierten Elektroartikel muss STIFEAR = 01 und eine WEEEREG vorhanden sein oder die EAR bereits
                  manuell erfasst worden sein */
               if ((!isA02STIFEAR || !hasA02WEEEREG) && !hasEAR)
               {
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_WRONG_ELECTRO_REG);
               }
           }           
       }
       else if (isA02ELEKTRO)
       {
           /* s_Zartikel.ELEKTROSCHROTT = N ist zulässig, weil der Wert bei den Stammdaten sich nicht auf die ElektroStoffV bezieht */
           /* s_Zartikel.ELEKTROSCHROTT = J ist zulässig entspricht dem Wert der Neuanlage ohne WEEEREG */
           /* s_Zartikel.ELEKTROSCHROTT = I ist immer zulässig, weil dieser Werte sich nicht aus IFA Daten ableiten lässt */
           if (s_Zartikel.ELEKTROSCHROTT[0] == 'R')
           {
               if ((!isA02STIFEAR || !hasA02WEEEREG) && !hasEAR)
               {
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_WRONG_ELECTRO_REG);
               }
           }
       }

       /* Prüfung A0STIFEAR - Elektroartikel unterliegt der Stiftung EAR zur Registrierung der Werkstoffe bei Entsorgung */
       /* 00 ist nicht registriert
          01 ist registriert
          leer keine Angabe */

       if (!isA02STIFEAR)
       {
           /* s_Zartikel.ELEKTROSCHROTT = N, J, I sind immer zulässig, da sich sich nicht auf die Registrierung bei Stiftung EAR beziehen */
           if (s_Zartikel.ELEKTROSCHROTT[0] == 'R')
           { 
               /* is nur zulässig, wenn es eine EAR gibt*/
               if (!hasEAR)
               {
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_WRONG_ELECTRO_REG);
               }
               else
               {
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_REG_ELECTRO_IFA_REG_MISSING);
               }
           }
       }
       else if (isA02STIFEAR)
       {
           /* s_Zartikel.ELEKTROSCHROTT = I ist immer zulässig, da sich dieser Status nicht aus IFA Daten ableitet */
           if ((s_Zartikel.ELEKTROSCHROTT[0] == 'N') || (s_Zartikel.ELEKTROSCHROTT[0] == 'J'))
           {
               if (hasA02WEEEREG)
               {
                   /*wird bei Datenübernahme nach 'R' geändert und die Registrierung übernommen */
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_CHG_ELECTRO_REG);
               }
               else if (hasEAR)
               {
                   /*wird bei Datenübernahme nach 'R' geändert weil eine EAR erfasst ist
                     gleichzeitig wird eine zwingende Fehlermeldung ereugt weil die WEEREG bei den IFA Daten fehlt */
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_WRONG_ELECTRO_REG);
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_REG_ELECTRO_IFA_EAR_MISSING);
               }
           }
           if (s_Zartikel.ELEKTROSCHROTT[0] == 'R')
           {
               if (!hasA02WEEEREG && hasEAR)
               {
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_REG_ELECTRO_IFA_EAR_MISSING);
               }
               else if (!hasEAR || hasA02WEEEREG)
               {
                   /*Keine Fehler mehr - EAR wird bei Datenübernahme neu gesetzt werden */
               }
               else if (!hasEAR)
               {
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_WRONG_ELECTRO_REG);
               }
           }
       }

       if (!hasA02BATTREG)
       {
           // Zus. keine Angabe (Blank) pruefen
           if (s_Zartikel.BATTERIEGESETZ[0] != 'N' && s_Zartikel.BATTERIEGESETZ[0] != ' ')
           {
               SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_CHG_BATTG_IFA);
           }
       }
       else if (hasA02BATTREG)
       {
           // Zus. keine Angabe (Blank) pruefen
           if (s_Zartikel.BATTERIEGESETZ[0] == 'N' || s_Zartikel.BATTERIEGESETZ[0] == ' ')
           {
               SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_CHG_BATTREG_REG);
           }
       }

       if (!hasA02WEEEREG)
       {
           if (hasEAR)
           {
               SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_REG_ELECTRO_IFA_EAR_MISSING);
           }
       }
       else if (hasA02WEEEREG)
       {
           if (hasEAR)
           {
               char weeeregEAR[11];
               strcpy(weeeregEAR, "DE");
               strcat(weeeregEAR, ifa.A02WEEEREG);
               if (strncmp(weeeregEAR, currentEAR, strlen(weeeregEAR)) != 0)
               {
                   SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_EAR_DIFF);
               }
           }
       }
   }

   /* wenn keine Preisaenderung, dann keine Preise aus Artikelstamm lesen */
   if ( !IsPreisAenderung ) return 0;

   status = ReadPreis( artikel_nr, ifa.DATUMGUELTIGAB, errmld );

   if ( !( status == 0 || status == 100 )) return -1;


   /* 05.01.2002: Vergleich Datum */
   *PreisdatumKannVerglichenWerden = 1;

   if ( status == 0 )
   {
     long IfaGro;
     long ArtGro;
     long IfaAep;
     long ArtAep;
     long IfaAvp;
     long ArtAvp;
	 long IfaEAvp;
	 long ArtEAvp;
     long ProzentPM;

     IsPreisPlausibel = SindIfaPreisePlausibel( &ifa ) == 0;

     if ( ( IsPreisPlausibel ) && (s_Zartikel.ARTIKEL_GESPERRT[0] == '0') )
     {
     	// Preisprüfungen nur bei nicht gesperrten Artikeln durchführen
     	// Preisänderungen in zpiartik nur übernehmen, wenn für den 
     	// gesperrten Artikel später zum aktuellen datumgueltigab noch
     	// kein Preis erfasst ist.
        IfaGro  = GetIfaPreisLong( ifa.A01GEPDM );
        IfaAep  = GetIfaPreisLong( ifa.A01AEPDM );
        IfaAvp  = GetIfaPreisLong( ifa.A01AVPDM );
        IfaEAvp = GetIfaPreisLong( ifa.A01UVP   );

        ArtGro  = GetPhosixPreisLong( s_Zpreis.GROSSO );
        ArtAep  = GetPhosixPreisLong( s_Zpreis.AEP );
        ArtAvp  = GetPhosixPreisLong( s_Zpreis.AVP );
        ArtEAvp = GetPhosixPreisLong( s_Zpreis.EAVP );

        ProzentPM = GetPhosixProzent( s_Zartikel.HERST_PROZENT );

        SetIfaTrueFalse( !IstMWSTgleich( ifa.A01MWST, *s_Zpreis.KE_MWST ),
                         ifa.NB_NZWING, NZ_MWST_DIFF );

        if ( IsIfaNettoArtikel( &ifa ) )
            TestSonderGrosso( s_Zartikel.SONDERGROSSO[0],
                              IfaGro, IfaAep, ArtGro, ArtAep  );

        // Vor der Preisprüfung ein paar Sonderfälle bei Volldatenimport prüfen
        // Und keine MWst-Änderungen
        if (*ifa.A00SSATZ == '0' && ifa.NB_NZWING[NZ_MWST_DIFF] == '0')
        {
            if ((IfaGro == IfaAep || IfaGro == 0) && 
                ProzentPM < 0 && ArtGro > 0 && ArtGro < ArtAep)
            {
                // Der Grosso wird vom AEP berechnet --> Keine Preisänderung
                SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_AEP_EQ_GR_CALC);
                IfaGro = ArtGro;
                if (IfaAep == 0) // IFA hat keine Preise geliefert
                {
                    IfaAep = ArtAep;
                    IfaAvp = ArtAvp;
                    IfaEAvp = ArtEAvp;
                }
                *PreisdatumKannVerglichenWerden = 0;
            }
            else if ((IfaGro == IfaAep || IfaAep == 0) &&
                     ProzentPM > 0 && ArtGro > 0 && ArtGro < ArtAep)
            {
                // Der AEP wurde vom Grosso berechnet --> Keine Preisänderung
                SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_GR_EQ_AEP_CALC);
                IfaAep = ArtAep;
                if (IfaGro == 0) // IFA hat keine Preise geliefert
                {
                    IfaGro = ArtGro;
                    IfaAvp = ArtAvp;
                    IfaEAvp = ArtEAvp;
                }
                *PreisdatumKannVerglichenWerden = 0;
            }
            else if (IfaGro == 0 && IfaAep == ArtGro && ProzentPM > 0)
            {
                // Der von IFA gemeldete AEP ist eigentlich der Grosso und
                // der AEP wurde über die Herstellerprozente neu berechnet
                SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_AEP_ART_GRO);
                IfaGro = ArtGro;
                IfaAep = ArtAep;
                IfaAvp = ArtAvp;
                IfaEAvp = ArtEAvp;
                *PreisdatumKannVerglichenWerden = 0;
            }
            else if ((IfaGro == 0 || IfaAep == 0 || IfaGro == IfaAep) &&
                     (IfaGro == ArtGro || IfaAep == ArtAep) &&
                     (ArtGro > 0 && ArtGro < ArtAep) &&
                     ProzentPM == 0 && ifa.DATUMGUELTIGAB == s_Zpreis.DATUMGUELTIGAB)
            {
                // Das Preisdatum is unverändert
                // Die Artikelpreise wurden manuell angepasst
                SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_GROSSO_AEP_NULL_ART);
                IfaGro = ArtGro;
                IfaAep = ArtAep;
                IfaAvp = ArtAvp;
                IfaEAvp = ArtEAvp;
                *PreisdatumKannVerglichenWerden = 0;

            }
            else if (IfaGro == 0 && IfaAep == 0 && 
                     ArtGro > 0  && ArtGro < ArtAep && 
                     ProzentPM == 0 && ifa.DATUMGUELTIGAB == s_Zpreis.DATUMGUELTIGAB && strcmp(ifa.A03VTSTAT, "00") != 0)
            {
                // Von IFA werden keine Preise geliefert, aber die aktuellen Preise sind noch gültig
                SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_GROSSO_AEP_NULL_ART);
                IfaGro = ArtGro;
                IfaAep = ArtAep;
                IfaAvp = ArtAvp;
                IfaEAvp = ArtEAvp;
                *PreisdatumKannVerglichenWerden = 0;
            }
            else if (strcmp(ifa.A03VTSTAT, "00") != 0)
            {
                // Artikel ist außerhandel und Preisänderungen werden nicht übernommen
                *PreisdatumKannVerglichenWerden = 0;
            }
            else
            {
        TestPreis_Aenderung( &ifa,
                             IsTaxPruefGrosso, ProzentPM,
                             IfaGro, IfaAep, IfaAvp, IfaEAvp,
                             ArtGro, ArtAep, ArtAvp, ArtEAvp  );
            }
        }
        else
        {
            TestPreis_Aenderung(&ifa,
                IsTaxPruefGrosso, ProzentPM,
                IfaGro, IfaAep, IfaAvp, IfaEAvp,
                ArtGro, ArtAep, ArtAvp, ArtEAvp);
        }
        /* 26.11.2002: neu wegen Preiserhoehungen */
        *IsZartpreisGelesen = 1;

     }
   }
   else
   {
     /* kein Preissatz vorhanden */
     SetIfaTrueFalse( 1, ifa.NB_ZWING, ZW_ART_OHNE_PREIS );

     IsPreisPlausibel = SindIfaPreisePlausibel( &ifa ) == 0;

     if ( IsPreisPlausibel && (s_Zartikel.ARTIKEL_GESPERRT[0] == '0' ) )
     {
     	// Preisprüfung nur wenn Artikel nicht gesperrt ist. Wenn noch kein
     	// Preisvorhanden wird der aktuelle IFA Preis bei gesperrten Artikeln
     	// einfach übernommen.
        long IfaGro;
        long ArtGro;
        long IfaAep;
        long ArtAep;
        long IfaAvp;
        long ArtAvp;
	    long IfaEAvp;
	    long ArtEAvp;

        IfaGro  = GetIfaPreisLong( ifa.A01GEPDM );
        IfaAep  = GetIfaPreisLong( ifa.A01AEPDM );
        IfaAvp  = GetIfaPreisLong( ifa.A01AVPDM );
        IfaEAvp = GetIfaPreisLong( ifa.A01UVP   );

        ArtGro  = 0;
        ArtAep  = 0;
        ArtAvp  = 0;
        ArtEAvp = 0;

        TestPreis_Aenderung( &ifa,
                             0, 0,
                             IfaGro, IfaAep, IfaAvp, IfaEAvp,
                             ArtGro, ArtAep, ArtAvp, ArtEAvp  ); 
     }
   }

   /* neu */
   /* Ersatz-Nummer entfaellt */

   return 0;
}


// ---------------------------------------------------------------------------------- //
static int ScanIfaNeuanlage( int complete, int *PreisdatumKannVerglichenWerden )
{
   /* --- PlausiFelder auf 0 initialisieren, wenn Satz Vollstaendig --- */
   /* --- d.h: NoValues entfernen ---- */
   if ( complete ) 
   {
       char pl_loe;
       pl_loe = ifa.NB_PLAUSI[PL_A00LKZ];
       ze_lcpy( ifa.NB_PLAUSI, '0', L_ZIFAART_NB_PLAUSI );
       ifa.NB_PLAUSI[PL_A00LKZ] = pl_loe;
	  
	   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   // Rücksetzen von PL_A00LKZ führt zu keiner Übernahme
	   // des Artikelsatzes in zpignart, wenn Artikel von IFA 
	   // nur als Änderung deklariert wurde, im zartikel
	   // tatsächlich aber nicht vorhanden ist, da bei zartikel-
	   // Neuanlagen nur ifa- Sätze ohne NO_VALUE berücksichtigt
	   // werden. (Sollte nur auf der Testmaschine vorkommen!?)
	   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   }


   /* --- Plausibilitaetspruefung (ohne Preispruefung) --- */
   FillIfaPlausiErr( &ifa );

   strcpy( ifa.AENDERUNG, "0" );   /* Neuanlage */

   /* --- Neuaufnahme bei IFA-Loeschung --- */
   if ( IsIfaLoschung( &ifa ) )
   {
       SetIfaTrueFalse( 1, ifa.NB_ZWING, ZW_LOESCH_KENN_NEU );
          return 1;
   }

   /* -------- Preise ---------------- */
   if ( SindIfaPreisePlausibel( &ifa ) == 0 )
   {
       TestPreis_Neuaufnahme( &ifa );
		/* 05.01.2002: Vergleich Datum */
       *PreisdatumKannVerglichenWerden = 1;
   }

   /* ------- Nur Elektro - Semantikprüfungen ------- */
   TestIfaElectricValuesSemanticIntegrity(&ifa);

   return 0;
}


// ---------------------------------------------------------------------------------- //
static long ZifaartBearbeite( int mode, int complete, char Ssatz, char *errmld )
{
    long status = 0;
    long artikel_nr = 0;
    long ersatz_nr = 0;
    
    int  IsAenderung = 0;
    int  IsLoeschung = 0;
	int  IsZartpreisGelesen = 0;
	int  PreisdatumKannVerglichenWerden = 0;
	int  IsHerstellerGelesen = 0;
    int  IsRetourensperre = 0;

    /* --- Plausibilitaetspruefung (ohne Preispruefung) --- */
    /* hier nicht, erst spaeter */

    /* PZN-alt = PZN */
    /* hier nicht
    SetIfaGleich(ifa.A00PZN, ifa.A06PZNNF, ifa.NB_ZWING, ZW_PZNNF_GLEICH);
    */

    /* Zartikel lesen */
    artikel_nr = ifa.A00PZN;
    status = ReadZartikel( artikel_nr, errmld );
    if ( !( status == 0 || status == 100 )) return status;

    /*  status  A00SSATZ      AENDERUNG   */
    /*     0    '0' '1'  '3'     '1'      */
    /*   100    '0' '1'  '3'     '0' wenn !IsNoValue */
    /*                           '2' wenn  IsNoValue */


    if ( status == 0 )   /* Aenderung */
    {
       ersatz_nr = s_Zartikel.ERSATZ_NR;
       IsAenderung = 1;
       IsLoeschung = ScanIfaAenderung( artikel_nr, &IsZartpreisGelesen, 
		                               &PreisdatumKannVerglichenWerden, errmld );
    }
    else
    {
       ersatz_nr = 0;
       IsLoeschung = ScanIfaNeuanlage( complete, &PreisdatumKannVerglichenWerden );
    }

    if ( IsLoeschung == -1 ) return -1;

    /* bei Loeschung keine weiteren Tests */
    if ( IsLoeschung == 1 )
    {
		/* Preisdatum nicht mehr vergleichen */
		PreisdatumKannVerglichenWerden = 0;
        /* nicht zwingend, wenn IfaSatz nicht vorhanden */
        SetIfaTrueFalse( !complete, ifa.NB_NZWING, NZ_IFA_COMPLETE );
    }
    else
    {
       /* zwingend, wenn IfaSatz nicht vorhanden */
       SetIfaTrueFalse( !complete, ifa.NB_ZWING, ZW_IFA_COMPLETE );

       /* Hersteller lesen */
       if ( IsNoValue ( &ifa, PL_A00ANBNR ) ||				/* das wegen aut idem !!!!! */
            !IsIfaFeldErr( ifa.NB_PLAUSI, PL_A00ANBNR ) )
       {
          status = LeseHersteller( ifa.A00ANBNR, errmld );
          if ( !( status == 0 || status == 100 )) return status;
          if ( status == 100 )
             SetIfaTrueFalse( 1, ifa.NB_PLAUSI, PL_A00ANBNR );
		  else
			 IsHerstellerGelesen = 1;
       }

       /* EAN-Nr lesen */
       if ( !IsIfaFeldErr( ifa.NB_PLAUSI, PL_A00EAN ) )
       {
          if ( TestEanNr( ifa.A00EAN ) == 1 )  /* Test nur bei gueltiger EAN-NR */
          {
             /* Bei Änderung muss geprüft werden ob die EAN aus IFA, noch der beim Artikel
                hinterlegten EAN entspricht, oder der bestehende Artikel ggf. gesperrt ist,
                bei gesperrten Artikel, kann bei einem möglichen Duplikat der EAN, bei einem 
                später gelesenen IFA Eintrag, auf dem gesperrten Artikel gelöscht und
                und beim neuen Artikel neu vergeben werden. */
              if (IsAenderung)
              {
                  status = ReadEan1(artikel_nr, errmld); //article check
             if ( !( status == 0 || status == 100 )) return status;
             if ( status == 0 )
             {
                      /* Wenn die EAN unterschiedlich ist, wird ein nicht zwingender Fehler
                         gesetzt, weil, sofern kein Duplikat später auftritt, die neue EAN
                         aus den IFA Daten übernommen wird. Unabhängig davon ob der Eintrag
                         gesperrt ist oder nicht. */
                      if (strncmp(s_Ean1.EAN_NR, ifa.A00EAN, L_ZIFAART_A00EAN) != 0)
                      {
                          /* 30.09.2024: Laut Business ist der nicht zwingende Fehler nicht mehr noetig
                          SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_EAN_DIFF);
                          */

                          /* Wenn der aktuelle Artikel nicht gesperrt ist, kann die gleiche EAN
                             aber noch auf weitere Artkel gemeldet sein */
                          if (s_Zartikel.ARTIKEL_GESPERRT[0] != '1')
                          {
                              status = CheckDuplicateEanInMem(ifa.A00EAN, IsAenderung);
                              if (status != 0 && status != 100)
                              {
                                  /* Das Duplikat aus IFA wird in dem Fall ignoriert, weil 
                                     der aktuelle Artikel bereits eine EAN hat. Die EAN aus
                                     IFA wird im IFA-Dialog also auch im Artikel Dialog angezeigt */
                                  SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_EAN_DUPL_IGNORED);
             }
                          }
                      }
                  }
                  /* Bei der zweiten Prüfung wird die EAN als Schlüssel verwendet. Wenn
                  *  sich die PZN zwischen dem gelesenen Arikel und dem IFA Eintrag unterscheiden
                  *  wurde die EAN schon mal vergeben. Sofern nun der Eintrag auf einem gesperrten
                  *  Artikel liegt, oder der aktuelle IFA Eintrag eine gesperrten Artikel referenziert
                  *  liegt noch kein Duplikat vor. Nur wenn sowohl der Artikel mit gleicher EAN
                  *  und der IFA Artikel beide aktiv sind, dann muss das Duplikat manuell behandelt werden.
                  */
                  status = ReadEan2(ifa.A00EAN, errmld); //unique check
             if ( !( status == 0 || status == 100 )) return status;
             if ( status == 0 )
             {
                if ( s_Ean2.ARTIKEL_NR != ifa.A00PZN )
                      {
                          // Zum aktuellen IFA Eintrag ist der Artikel bereits geladen bei
                          // bei der Prüfung wird jetzt ggf. der korrespondierende Artikel 
                          // aus dem EAN Duplikat geladen
                          // sofern der IFA Eintrag auf einen aktiven Artikel verweist
                          if (*s_Zartikel.ARTIKEL_GESPERRT == '0')
                          {
                              // Der aktuelle Artikel ist nicht gesperrt und weist die gleiche EAN auf
                              // wie der Artikel zu dem die PZN aus der IFA Tabelle gehört
                              // Merke den aktuellen Artikel um später darauf zurücksetzen zu können.
                              int curArticleNo = s_Zartikel.ARTIKEL_NR;
                              status = ReadZartikel(s_Ean2.ARTIKEL_NR, errmld);
                              if (status == 0)
                              {
                                  if (*s_Zartikel.ARTIKEL_GESPERRT == '0')
                                  {
                                      // beide Artikel sind unterschiedlich und nicht gesperrt
                                      SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_EAN_MEHRFACH);
                                  }
                              }
                              else
                              {
                                  // Es kann trotzdem noch ein weiteres Duplikat innerhalb der IFA Daten existieren
                                  // welches zuvor noch nicht geladen war, aber jetzt enthalten ist, da die Prüfung 
                                  // Zeilenweise erfolgt. In der letzten Prüfung werden die Einträge aus der IFA Tabelle
                                  // geladen.
                                  //status = CheckDuplicateEan(ifa.IFANR, ifa.A00EAN, errmld);
                                  status = CheckDuplicateEanInMem(ifa.A00EAN, IsAenderung);
                                  if (status != 0)
                                  {
                                      SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_EAN_MEHRFACH);
                                  }
                              }
                              status = ReadZartikel(curArticleNo, errmld); // zurücksetzen
                          }
                          // Der aktuelle Artikel ist gesperrt, die EAN muss somit nicht aus IFA
                          // übernommen werden, wenn die EAN bereits bei einem anderen Artikel
                          // vergeben ist.
                      }
                  }
              }
              else
              {
                  /** Bei Neuanlag muss nur nach möglichen Duplikation innerhalb der bereits geladenen IFA Daten geprüft werden
                      In dem Fall müssen aber alle bereits geladenen IFA Daten erneut kontrolliert werden */
                  //status = CheckDuplicateEan(ifa.IFANR, ifa.A00EAN, errmld);
                  status = CheckDuplicateEanInMem(ifa.A00EAN, IsAenderung);
                  if (status != 0)
                  {
                   SetIfaTrueFalse( 1, ifa.NB_ZWING, ZW_EAN_MEHRFACH );
             }
           }
       }
       }

	   /* NTIN lesen */
       if ( !IsIfaFeldErr( ifa.NB_PLAUSI, PL_A00NTIN ) )
       {
          if ( TestEanNr( ifa.A00NTIN ) == 1 )  /* Test nur bei gueltiger, numerischer NTIN */
          {
              /* Bei Änderung muss geprüft werden ob die NTIN aus IFA, noch der beim Artikel
                 hinterlegten NTIN entspricht, oder der bestehende Artikel ggf. gesperrt ist,
                 bei gesperrten Artikel, kann bei einem möglichen Duplikat der NTIN, bei einem
                 später gelesenen IFA Eintrag, auf dem gesperrten Artikel gelöscht und
                 und beim neuen Artikel neu vergeben werden. */
              if (IsAenderung)
              {
                  status = ReadNtin1(artikel_nr, errmld); //article check
             if ( !( status == 0 || status == 100 )) return status;
             if ( status == 0 )
             {
                      /* Wenn die NTIN unterschiedlich ist, wird ein nicht zwingender Fehler
                         gesetzt, weil, sofern kein Duplikat später auftritt, die neue NTIN
                         aus den IFA Daten übernommen wird. Unabhängig davon ob der Eintrag
                         gesperrt ist oder nicht. */
				 if ( strncmp( s_Ntin1.ARTICLE_CODE, ifa.A00NTIN, L_ZIFAART_A00NTIN ) != 0 )
                      {
                          /* 30.09.2024: Laut Business ist der nicht zwingende Fehler nicht mehr noetig
                          SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_NTIN_DIFF);
                          */

                          /* Wenn der aktuelle Artikel nicht gesperrt ist, kann die gleiche NTIN
                             auch noch für einen weiteren nicht gesperrten Artikel vergeben worden sein. */
                          if (s_Zartikel.ARTIKEL_GESPERRT[0] != '1')
                          {
                              //status = CheckDuplicateNtin(ifa.IFANR, ifa.A00NTIN, errmld);
                              status = CheckDuplicateNtinInMem(ifa.A00NTIN, IsAenderung);
                              if (status != 0 && status != 100)
                              {
                                  SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_NTIN_MEHRFACH);
                              }
                          }
             }
                  }
                  /* Bei der zweiten Prüfung wird die NTIN als Schlüssel verwendet. Wenn
                  *  sich die PZN zwischen dem gelesenen Arikel und dem IFA Eintrag unterscheiden
                  *  wurde die NTIN schon mal vergeben. Sofern nun der Eintrag auf einem gesperrten
                  *  Artikel liegt, oder der aktuelle IFA Eintrag eine gesperrten Artikel referenziert
                  *  liegt noch kein Duplikat vor. Nur wenn sowohl der Artikel mit gleicher NTIN
                  *  und der IFA Artikel beide aktiv sind, dann muss das Duplikat manuell behandelt werden.
                  */
                  status = ReadNtin2(ifa.A00NTIN, s_Zartikel.ARTIKEL_NR, errmld); //unique check
             if ( !( status == 0 || status == 100 )) return status;
             if ( status == 0 )
             {
                      if (s_Ntin2.ARTICLENO != ifa.A00PZN)
                      {
                          // Zum aktuellen IFA Eintrag ist der Artikel bereits geladen bei
                          // bei der Prüfung wird jetzt ggf. der korrespondierende Artikel 
                          // aus dem EAN Duplikat geladen
                          // sofern der IFA Eintrag auf einen aktiven Artikel verweist
                          if (*s_Zartikel.ARTIKEL_GESPERRT == '0')
                          {
                              int curArticleNo = s_Zartikel.ARTIKEL_NR;
                              status = ReadZartikel(s_Ntin2.ARTICLENO, errmld);
                              if (status == 0)
                              {
                                  if (*s_Zartikel.ARTIKEL_GESPERRT == '0')
                SetIfaTrueFalse( 1, ifa.NB_ZWING, ZW_NTIN_MEHRFACH );
             }
                              else
                              {
                                  //status = CheckDuplicateNtin(ifa.IFANR, ifa.A00NTIN, errmld);
                                  status = CheckDuplicateNtinInMem(ifa.A00NTIN, IsAenderung);
                                  if (status != 0)
                                  {
                                      SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_NTIN_MEHRFACH);
           }
       }
                              status = ReadZartikel(curArticleNo, errmld); // zurücksetzen
                          }
                          // Der aktuelle Artikel ist gesperrt, die NTIN muss somit nicht aus IFA
                          // übernommen werden, wenn die NTIN bereits bei einem anderen Artikel
                          // vergeben ist.
                      }
                  }
              }
              else
       {
                  /** Bei Neuanlag muss nur nach möglichen Duplikation innerhalb der bereits geladenen IFA Daten geprüft werden
                      In dem Fall müssen aber alle bereits geladenen IFA Daten erneut kontrolliert werden */
                  //status = CheckDuplicateNtin(ifa.IFANR, ifa.A00NTIN, errmld);
                  status = CheckDuplicateNtinInMem(ifa.A00NTIN, IsAenderung);
                  if (status != 0)
          {
                      SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_NTIN_MEHRFACH);
                  }
              }
          }
       }

       /* GTIN lesen */
       if (!IsIfaFeldErr(ifa.NB_PLAUSI, PL_A00GTIN))
       {
           if (TestEanNr(ifa.A00GTIN) == 1)  /* Test nur bei gueltiger, numerischer GTIN */
           {
               /* Bei Änderung muss geprüft werden ob die GTIN aus IFA, noch der beim Artikel
                  hinterlegten GTIN entspricht, oder der bestehende Artikel ggf. gesperrt ist,
                  bei gesperrten Artikel, kann bei einem möglichen Duplikat der GTIN, bei einem
                  später gelesenen IFA Eintrag, auf dem gesperrten Artikel gelöscht und
                  und beim neuen Artikel neu vergeben werden. */
               if (IsAenderung)
               {
                   status = ReadGtin1(artikel_nr, errmld); //article check
                   if (!(status == 0 || status == 100)) return status;
                   if (status == 0)
                   {
                       /* Wenn die GTIN unterschiedlich ist, wird ein nicht zwingender Fehler
                          gesetzt, weil, sofern kein Duplikat später auftritt, die neue NTIN
                          aus den IFA Daten übernommen wird. Unabhängig davon ob der Eintrag
                          gesperrt ist oder nicht. */
                       if (strncmp(s_Gtin1.ARTICLE_CODE, ifa.A00GTIN, L_ZIFAART_A00GTIN) != 0)
                       {
                           /* 30.09.2024: Laut Business ist der nicht zwingende Fehler nicht mehr noetig
                           SetIfaTrueFalse(1, ifa.NB_NZWING, NZ_GTIN_DIFF);
                           */

                           /* Wenn der aktuelle Artikel nicht gesperrt ist, muss bei unterschiedlichen Artikeln
                              mit gleicher GTIN muss geprüft werden ob mehrer Einträge mit gleicher GTIN für
                              aktive Artikel bestehen. */
                           if (s_Zartikel.ARTIKEL_GESPERRT[0] != '1')
                           {
                               //status = CheckDuplicateGtin(ifa.IFANR, ifa.A00GTIN, errmld);
                               status = CheckDuplicateGtinInMem(ifa.A00GTIN,IsAenderung);
                               if (status != 0 && status != 100)
                               {
                                   SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_GTIN_MEHRFACH);
                               }
                           }
                       }
                   }
                   /* Bei der zweiten Prüfung wird die GTIN als Schlüssel verwendet. Wenn
                   *  sich die PZN zwischen dem gelesenen Arikel und dem IFA Eintrag unterscheiden
                   *  wurde die GTIN schon mal vergeben. Sofern nun der Eintrag auf einem gesperrten
                   *  Artikel liegt, oder der aktuelle IFA Eintrag eine gesperrten Artikel referenziert
                   *  liegt noch kein Duplikat vor. Nur wenn sowohl der Artikel mit gleicher GTIN
                   *  und der IFA Artikel beide aktiv sind, dann muss das Duplikat manuell behandelt werden.
                   */
                   status = ReadGtin2(ifa.A00GTIN, s_Zartikel.ARTIKEL_NR, errmld); //unique check
                   if (!(status == 0 || status == 100)) return status;
             if ( status == 0 )
             {
                       if (s_Gtin2.ARTICLENO != ifa.A00PZN)
                       {
                           // Zum aktuellen IFA Eintrag ist der Artikel bereits geladen bei
                           // bei der Prüfung wird jetzt ggf. der korrespondierende Artikel 
                           // aus dem EAN Duplikat geladen
                           // sofern der IFA Eintrag auf einen aktiven Artikel verweist
                           if (*s_Zartikel.ARTIKEL_GESPERRT == '0')
                           {
                               int curArticleNo = s_Zartikel.ARTIKEL_NR;
                               status = ReadZartikel(s_Gtin2.ARTICLENO, errmld);
                               if (status == 0)
                               {
                                   if (*s_Zartikel.ARTIKEL_GESPERRT == '0')
                                       SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_GTIN_MEHRFACH);
                               }
                               else
                               {
                                   //status = CheckDuplicateGtin(ifa.IFANR, ifa.A00GTIN, errmld);
                                   status = CheckDuplicateGtinInMem(ifa.A00GTIN, IsAenderung);
                                   if (status != 0)
                                   {
                                       SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_GTIN_MEHRFACH);
                                   }
                               }
                               status = ReadZartikel(curArticleNo, errmld); // zurücksetzen
                           }
                           // Der aktuelle Artikel ist gesperrt, die GTIN muss somit nicht aus IFA
                           // übernommen werden, wenn die GTIN bereits bei einem anderen Artikel
                           // vergeben ist.
                       }
                   }
               }
               else
               {
                   /** Bei Neuanlag muss nur nach möglichen Duplikation innerhalb der bereits geladenen IFA Daten geprüft werden
                       In dem Fall müssen aber alle bereits geladenen IFA Daten erneut kontrolliert werden */
                   //status = CheckDuplicateGtin(ifa.IFANR, ifa.A00GTIN, errmld);
                   status = CheckDuplicateGtinInMem(ifa.A00GTIN, IsAenderung);
                   if (status != 0)
                   {
                       SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_GTIN_MEHRFACH);
                   }
             }
          }
       }

	   TestIfaPreisMeldung(&ifa, s_Zartikel.HERST_PROZENT); // --> NZ_PREISE_GROSSO_AEP

       /* PZN-Neu lesen */
       if ( mode == FILL_MODE_2 )
       {
          long pzn_neu;

          pzn_neu = ifa.A06PZNNF;

          if ( !IsIfaFeldErr( ifa.NB_PLAUSI, PL_A06PZNNF ) && pzn_neu > 0 )
          {
             /* PZN-neu = PZN */
             if ( pzn_neu == artikel_nr )
                SetIfaTrueFalse( 1, ifa.NB_ZWING, ZW_PZNNF_GLEICH );

             /* if ( ersatz_nr > 0 && ersatz_nr != pzn_neu ) */
             /* nach Peetz 10.11.2000 ist das oben falsch, das unten ist richtig */
             if ( ersatz_nr != pzn_neu )
                SetIfaTrueFalse( 1, ifa.NB_NZWING, NZ_PZNNF_DIFF );

             if (  pzn_neu != artikel_nr )
             {
                status = ReadIfaViaPznNeu( ifa.A06PZNNF, errmld );
                if ( !( status == 0 || status == 100 )) return status;
                if ( status == 100 )
                {
                   status = ReadZersatz( pzn_neu, errmld );
                   if ( !( status == 0 || status == 100 )) return status;
                }
                if ( status == 100 )
                  SetIfaTrueFalse( 1, ifa.NB_NZWING, NZ_PZNNF_NVOR );
             }
          }
		  else if (pzn_neu == -1) //articlecode für nachfolger nicht gefunden
		  {
			SetIfaTrueFalse( 1, ifa.NB_NZWING, NZ_PZNNF_NVOR );
		  }
       }
    }

    /* Transferdatum */
    if ( *ifa.AENDERUNG != '1' )  /* Neuanlage */
    {
        if ( ifa.DATUMGUELTIGAB >= tages_datum )
          ifa.DATUMGUELTIGAB = AddDayToPhoDate(tages_datum, 1); // im ZDP sind nur Preise änderbar mit Datum > heute !
    }

	/* 05.01.2002 Preisdatum vergleichen */
	if ( PreisdatumKannVerglichenWerden && *s_Zartikel.ARTIKEL_GESPERRT == '0')
	{
        if ( *ifa.AENDERUNG != '1' )  /* Neuanlage */
		{
			if ( ifa.DATUMGUELTIGAB < 20020101 )	/* wenn noch DM-Preise */
				 SetIfaTrueFalse( 1, ifa.NB_ZWING, ZW_IFADAT_01012002 );
		}
		else  /* bei  Preisaenderung  */
		{
			if ( ifa.DATUMGUELTIGAB < 20020101 )	/* wenn noch DM-Preise */
				 SetIfaTrueFalse( 1, ifa.NB_ZWING, ZW_IFADAT_01012002 );
			else
			{
                // bisher wurde der letzte gültige Preis zum ifa.DATUMGUELTIGAB Zeitpunkt gelesen
                // jetzt benötigen wir jedoch den letzen gültigen Preis
                // status = ReadPreis(artikel_nr, tages_datum, errmld);
                //if (status != 0 && status != 100) return status;
                
                if (status == 0 && 
                    ifa.DATUMGUELTIGAB <= s_Zpreis.DATUMGUELTIGAB &&	/* wenn ifaPreis <= akt. ArtikelPreis */
                    ( ifa.AEP != s_Zpreis.AEP ||
                      ifa.EAVP != s_Zpreis.EAVP ||
                      ifa.GROSSO != s_Zpreis.GROSSO 
                    )
                   )
	{
                    if ((ifa.GROSSO == (double) 0.0 || ifa.GROSSO == ifa.AEP) && ifa.AEP == s_Zpreis.AEP && s_Zpreis.HERST_PROZENT != (double) 0.0)
		{
                        // Wenn kein GROSSO von IFA geliefert wird, aber der vorhandene Grosso != 0 ist, wurde dieser
                        // vermutlich über die Herstellerprozente berechnet und kann übernommen werden.
                        ifa.GROSSO = s_Zpreis.GROSSO;
                    }
                    else
			{
                        SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_IFADAT_ARTDAT);
			}
		}
                // So lange die Preise gleich sind, liegt kein Fehler vor
                // Wenn das Datum bereits größer ist, gehen wir von einem veralteten Preis in der IFA Meldung aus
                // der dann auch bei der Datenübernahme nicht übernommen wird.
		}
		}
	
	}

	/* Test auf gültige Kombinationen aus A02LEBENSM / A02NEM / A02DIAET --> ZW_KOMB_LEBENSM_NEM_DIAET => Plausi-Check */
	if ( !IsNoValue ( &ifa, PL_A02NEM ) || !IsNoValue ( &ifa, PL_A02DIAET ) || !IsNoValue ( &ifa, PL_A02LEBENSM ) ) 
	{
		if ( strcmp (ifa.A02NEM, "01") != 0 ) // A02NEM == "00" || A02NEM == "  "
		{
			if ( strcmp(ifa.A02DIAET, "01") == 0) 
			{
				if ( strcmp(ifa.A02LEBENSM, "01") != 0) 		
					SetIfaTrueFalse( 1, ifa.NB_ZWING, ZW_KOMB_LEBENSM_NEM_DIAET );
			}
			else if ( strcmp(ifa.A02DIAET, "99") == 0) 
			{
				if ( strcmp(ifa.A02LEBENSM, "01") != 0) 		
					SetIfaTrueFalse( 1, ifa.NB_ZWING, ZW_KOMB_LEBENSM_NEM_DIAET );
			}
			else // A02DIAET == "00" || A02DIAET == "  "
			{
				if ( strcmp(ifa.A02LEBENSM, "01") == 0)
					SetIfaTrueFalse( 1, ifa.NB_ZWING, ZW_KOMB_LEBENSM_NEM_DIAET );
			}
		}
		else // A02NEM == "01"
		{
			if ( (strcmp(ifa.A02LEBENSM, "01") != 0) || 
				((strcmp(ifa.A02DIAET, "  ") != 0) && (strcmp(ifa.A02DIAET, "00") != 0)) )
				SetIfaTrueFalse( 1, ifa.NB_ZWING, ZW_KOMB_LEBENSM_NEM_DIAET );
		}
	}

    //check FMD - deaktivieren E-Mail Fr. Radeck 22.02.2023
    /*
    if (ifa.A02ATMP > 0)
    {
        if (status == 0) //update
        {
            if (s_Zartikel.FMD_RELEVANT != 0)
            {
                SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_NO_FMD_CHECK_REQUIRED);
            }
        }
        else
        {
            if (ifa.A11VERIPFL > 0 || oifa.A11VERIHOC > 0)
            {
                // Ist Voraussetzung für FMD Prüfung
                SetIfaTrueFalse(1, ifa.NB_ZWING, ZW_NO_FMD_CHECK_REQUIRED);
            }
        }
    }
    */

	/* Statusfeld fuellen */
    FillIfaStatus( &ifa );

    status = InsertZifa( errmld );

    /* Bei Bestandslieferung (Ssatz == '0') hier keine Pruefungen und Aenderungen machen */
    if (Ssatz != '0')
    {
        if (status == 0 && *ifa.AENDERUNG == '1' && IsZartpreisGelesen)
        {
            status = InsertZpreiserh(errmld);
            IsRetourensperre = TestRetourensperreBedingung();
        }

        /* aut idem Juni 2002 */

        if (status == 0 && *ifa.AENDERUNG == '1' && IsZartpreisGelesen && IsHerstellerGelesen)
            status = MarkierePreissenkung(artikel_nr, errmld);

        if (status == 0 && IsRetourensperre)
            status = SetzeRetourensperre(artikel_nr, errmld);
    }

    return status;
}

// ---------------------------------------------------------------------------------- //
static long test_ifanr_klinik(  long ifadatum, char *errmld )
{
    char sql[50];
    long status;
    long nr;

    sprintf( sql, "select IFANR from zifaokbs where IFANR=%ld",
                  ifadatum );

    status = SqlRead( sql, &nr, NULL );
    
	if ( status == 100 ) 
		return 0;

    if ( status == 0 )
       strcpy( errmld, "IFA-Datei bereits eingelesen" );
    else
    {
       strcpy( errmld, "zifaokbs: " );
       strcat( errmld, DynErrmld() );
    }
    return -1;
}

// ---------------------------------------------------------------------------------- //
static long test_ifanr(  long ifadatum, char *errmld )
{
    char sql[50];
    long status;
    long nr;

    sprintf( sql, "select IFANR from ZIFAART where IFANR=%ld",
                  ifadatum );

    status = SqlRead( sql, &nr, NULL );
    if ( status == 100 ) return 0;

    if ( status == 0 )
       strcpy( errmld, "IFA-Datei bereits eingelesen" );
    else
    {
       strcpy( errmld, "zifaart: " );
       strcat( errmld, DynErrmld() );
    }
    return -1;
}

// ---------------------------------------------------------------------------------- //
int OifaToZifa( struct ZIFAART *zifa, struct P_IFAOART *oifa );

// ---------------------------------------------------------------------------------- //
static long IfaBearbeite( sSatzArt *pSart,
                          long Pzn, char Ssatz, char LoeKenn, int mode, char *errmld )
{

   long status = 0;

   int complete;

   if (inTransaction == 0)
   {
   status = SqlBeginWork();
   }
   if ( status == 0 )
   {
      inTransaction = 1;
      status = IfaOartAendere( pSart, &oifa, &old_oifa,
                               tages_datum, Pzn, Ssatz, LoeKenn,
                               &anz_upd, &anz_del, &anz_ins,
                               errmld );
      complete = 1;
      if ( status == 2 )    /* hier status = 2  relevant !!!!!!!!!!!!!!!!!!!!!!!!!! */
      {
         complete = 0;
         status = 0;
      }
      if ( status == 0 )
      {
         OifaToZifa( &ifa, &oifa );
         status = ZifaartBearbeite( mode, complete, Ssatz, errmld );
      }

      if (satznr % 1000 == 0)
      {
      SqlCommitWork();
          inTransaction = 0;
      }
   }
   else 
   {
      strcpy( errmld, "ifaoart: " );
      strcat( errmld, DynErrmld() );
   }
   return status;
}


// ---------------------------------------------------------------------------------- //
static int GetSonstKenn( struct ZIFAART *ifa, sSatzArt *pSart, char *errmld )
{
   /* --- StatusIndikator --- */
   strcpy( ifa->A00SSATZ, " " );
   if ( GetIfaStatus( ifa->A00SSATZ, pSart, errmld ) != 0 ) return 1;
   if ( TestNoValue( ifa, ifa->A00SSATZ, PL_A00SSATZ ) )
      strcpy( ifa->A00SSATZ, " " );

   /* --- Loeschkennzeichen --- */
   strcpy( ifa->A00LKZ, " " );
   if ( GetLoeschKenn( ifa->A00LKZ, pSart, errmld ) != 0 ) return 1;
   if ( TestNoValue( ifa, ifa->A00LKZ, PL_A00LKZ ) )
      strcpy( ifa->A00LKZ, " " );

   /* ---- Preisindikatoren ---- */
   strcpy( ifa->A01SUVP, " " );
   if ( GetA01SUVP( ifa->A01SUVP, pSart, errmld ) != 0 ) return 1;
   if ( TestNoValue( ifa, ifa->A01SUVP, PL_A01SUVP ) )
      strcpy( ifa->A01SUVP, " " );

   strcpy( ifa->A01SGEPDM, " " );
   if ( GetA01SGEPDM( ifa->A01SGEPDM, pSart, errmld ) != 0 ) return 1;
   if ( TestNoValue( ifa, ifa->A01SGEPDM, PL_A01SGEPDM ) )
      strcpy( ifa->A01SGEPDM, " " );

   strcpy( ifa->A01SAEPDM, " " );
   if ( GetA01SAEPDM( ifa->A01SAEPDM, pSart, errmld ) != 0 ) return 1;
   if ( TestNoValue( ifa, ifa->A01SAEPDM, PL_A01SAEPDM ) )
      strcpy( ifa->A01SAEPDM, " " );

   strcpy( ifa->A01SAVPDM, " " );
   if ( GetA01SAVPDM( ifa->A01SAVPDM, pSart, errmld ) != 0 ) return 1;
   if ( TestNoValue( ifa, ifa->A01SAVPDM, PL_A01SAVPDM ) )
      strcpy( ifa->A01SAVPDM, " " );

   strcpy( ifa->A01SZBV, " " );    /* EAVP */
   // no longer available in ifa version 248
   /*   if (GetA01SZBV(ifa->A01SZBV, pSart, errmld) != 0) return 1;
   if ( TestNoValue( ifa, ifa->A01SZBV, PL_A01SZBV ) )
      strcpy( ifa->A01SZBV, " " ); */

   strcpy( ifa->A01SERSTATT, " " ); 
   *ifa->A01SERSTATT = '\0';
   TestNoValue( ifa, ifa->A01SERSTATT, PL_A01SERSTAT );
   
   strcpy( ifa->A01SAB130A, " " );
   if ( GetA01SAB130A( ifa->A01SAB130A, pSart, errmld ) != 0 ) return 1;
   if ( TestNoValue( ifa, ifa->A01SAB130A, PL_A01SAB130A ) )
      strcpy( ifa->A01SAB130A, " " );

   return 0;
}

/* ------------------------------------------------------------------- */
long sel_ArtNoByCode( const long code, char* errmld)
{
    long artNo;

	/* auch für PZN 7 
	if (code <= 9999999)
		return code; // keine PZN 8 */

	if (code == 0)
		return code;

    /* Followin SQL substituted by prepared statement RadeCode2
	sprintf( sql, "SELECT articleno FROM carticlecodes WHERE article_code ='%ld' "
					"AND code_type IN (SELECT code_type FROM ccodetypes WHERE artnr_substitute = 1)", code); */
  
    long status = ReadCode2(code, errmld);
    if (status == 0)
    {
        artNo = s_Code2.ARTICLENO;
    }
    else
	{
		artNo = -1;
	}

	return artNo;
}

/* ------------------------------------------------------------------- */
long create_NewArtNo	( const long code )
{
    long artNo;
	char sql[250];
	long lStatus;
	double dCount;
	short preferred = 1;

	if (code <= 9999999) // 7-stellige PZN --> 1:1 
	{
		artNo = code;

		if (tages_datum < 20130101)
			preferred = 0; // in 2012 Codetyp "PZN8" für 7-stellige PZN´s noch als NICHT- preferred anlegen!

	}
	else // 8-stellige PZN --> neue ID ermitteln
	{
		strcpy (sql, "select nr from nummerek where nr_art = 'NEWPZN' ");
		lStatus = SqlRead(sql, &artNo, NULL);

		if (lStatus == 0)
		{
			sprintf( sql, "select count(*) from zartikel where artikel_nr = %ld ", artNo );
			lStatus = SqlRead(sql, &dCount, NULL);
		
			while ( lStatus == 0 && (dCount > 0.0 || TestPruefZiffer7(artNo) == 2)) // PZN bereits vorhanden oder Prüfziffer gültig
			{
				sprintf( sql, "select count(*) from zartikel where artikel_nr = %ld ", ++artNo );
				lStatus = SqlRead(sql, &dCount, NULL);
			}

			if ( lStatus != 0 || dCount > 0.0 ) // keine freie PZN gefunden
			{
				artNo = -1;
			}
			else
			{
				// nächste freie Nummer abspeichern
				sprintf( sql, "UPDATE nummerek SET nr = %ld WHERE nr_art = 'NEWPZN' ", artNo + 1);
				SqlExecuteImm( sql );
			}
		}
	}

	if (artNo > 0) // neuen Eintrag für Codetyp "PZN8" als preferred anlegen:
	{
		// Verknüpfung AC - PZN schreiben
		sprintf( sql, "INSERT INTO carticlecodes (ARTICLENO, PREFERRED_FLAG, ARTICLE_CODE, DATE_CHANGED, CODE_TYPE, SERIAL_NUMBER ) "
						"VALUES (%ld, %d, '%ld', %ld, 16, 1) ", artNo, preferred, code, tages_datum);
		SqlExecuteImm( sql );

		sprintf( sql, "INSERT INTO zpznpflege (artikel_nr, datum, dezap_sa ) "
						"VALUES (%ld, %ld, '34') ", artNo, tages_datum);
		SqlExecuteImm( sql );
	}

	return artNo;
}

// ---------------------------------------------------------------------------------- //
static int  FillArtikelSatz( sSatzArt *pSart, int mode, char *errmld )
{
   int  s;
   int  IsPznNeu;
   long Pzn;
   long PznNf;

   ifa.IFANR  = ifadatumnr;

   /* --- FehlerFelder initialisieren --- */
   ze_lcpy( ifa.NB_PLAUSI, '0', L_ZIFAART_NB_PLAUSI );
   ze_lcpy( ifa.NB_ZWING , '0', L_ZIFAART_NB_ZWING  );
   ze_lcpy( ifa.NB_NZWING, '0', L_ZIFAART_NB_NZWING );

   /* --- PZN --- */
   if ( GetIfaPzn( &Pzn, pSart, errmld ) != 0 ) return 1;
   ifa.A00PZN = Pzn;
   ifa.A00PZN8 = Pzn;

   /* --- Sonstige Kennzeichen --- */
   if ( GetSonstKenn( &ifa, pSart, errmld ) != 0 ) return 1;

   /* --- PznNachfolger --- */
   if ( GetIfaPznNF( &PznNf, pSart, errmld ) != 0 ) return 1;
   IsPznNeu = PznNf > 0;
   
   if ( mode == FILL_MODE_1 || mode == FILL_MODE_2 )
   {
	  char Ssatz;
      char LoeKenn;

		//PZN-8 : wenn PZN 8-stellig, dann direkt hier die ID ermitteln (bestehende suchen bzw. neue generieren) und diese als Pzn setzen;
		//			gleichzeitig die Verknüpfung in carticlecodes einstellen, wenn es eine Neuanlage ist
		Pzn = sel_ArtNoByCode(Pzn,errmld); // Suche, ob es für diese PZN8 bereits einen AC gibt
		if (Pzn <= 0) // neuen AC generieren
			Pzn = create_NewArtNo(ifa.A00PZN);
		ifa.A00PZN = Pzn;
		
      s = 0;
      Ssatz   = *ifa.A00SSATZ;
      LoeKenn = *ifa.A00LKZ;
      // bei PZN-8 gibt es keine Prüfziffern mehr:
	  // if ( IsPruefzifferOk( Pzn ) )         /* nur Artikel mit ordentlichr PRN */
      {
         if ( mode == FILL_MODE_1 )         /* Artikel ohne PZN_Neu */
         {
            if ( !IsPznNeu )
            {
               long status;
               art_ohne_pznneu++;
               satznr++;
               ifa.SATZNR = satznr;
               status = IfaBearbeite( pSart, Pzn, Ssatz, LoeKenn, mode, errmld );
               if ( status != 0 ) s = 1;
			}
         }
         else    /* Artikel mit PZN_NEU */
         {
            if ( IsPznNeu )
            {
               long status = 0;
               art_mit_pznneu++;
               satznr++;
               ifa.SATZNR = satznr;
               status = IfaBearbeite( pSart, Pzn, Ssatz, LoeKenn, mode, errmld );
               if ( status != 0 ) s = 1;
             }
         }
      }
   }
   else
   {
      oifa.A00PZN = Pzn;
      s = IfaOartFill( &oifa, pSart, tages_datum, errmld );  /* zum Testen */
      if ( s != 0 ) return 1;
      satznr++;

#if defined(MSDOS) || defined(WIN32)
      printf( "%7.0ld %7.0ld :: %s\n", satznr, oifa.A00PZN, GetRefToIfaOartPlausi() );
#endif
   }

#if defined(MSDOS) || defined(WIN32)
   /* !!!!! zum testen : Abbruch nach x Saetzen !!!!!!!!!!!!!!!*/
/* if ( mode == FILL_MODE_1 ) */
    if ( MAX_TEST_SATZ > 0 && satznr == MAX_TEST_SATZ )
    {
       if ( s == 0 ) s = ABBRUCH_NO_ERROR;    /* !!!!!!!!!!!!!!!!!!!!! */
    }
#endif

   return s;
}

/* ---------- Test IFA auf "Keine Angabe" ---------------------------- */
static void InitNoValueKlinik(  )
{
   int pos;
   for ( pos = 0; pos < POSANZ_ZIFAOKBS; pos++ )
      NB_PLAUSI_KLINIK[ pos ] = '0';
}

static void TestNoValueKlinik( char *wert, int pos )
{
   if ( *wert == '\0' )
      NB_PLAUSI_KLINIK[ pos ] = NOVALUE_PL;
}

static int IsNoValueKlinik( int pos )
{
   return NB_PLAUSI_KLINIK[ pos ] == NOVALUE_PL;
}

static int IsAnyNoValueKlinik( )
{
   int pos;
   for ( pos = 0; pos < POSANZ_ZIFAOKBS; pos++ )
   {
      if ( NB_PLAUSI_KLINIK[ pos ] == NOVALUE_PL ) 
		  return 1;
   }
   return 0;
}

/* ---------- Wert aus IFA extrahieren ---------------- */

static char *GetWert( sSatzArt *pSart, char* feld, char *errmld )
{
   char *wert;
   wert = GetWertFromSatzArtViaFeldName( pSart, feld );
   if ( wert == NULL )
      sprintf( errmld, "kein Wert fuer Feld %s", feld );
   return wert;
}

// ---------------------------------------------------------------------------------- //
static int IfaFillKlinik( struct ZIFAOKBS *k, sSatzArt *pSart, char *errmld )
{
   char *wert;
 
   InitNoValueKlinik(  );

   strcpy( k->IFA_SATZART, "000" );

   if ( ( wert = GetWert( pSart, "A00SSATZ", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_IFA_SATZART );
   if ( *wert == '2' )
      strcpy( k->IFA_SATZART, "003" );   /* Loeschung */

   if ( ( wert = GetWert( pSart, "A00LKZ", errmld ) ) == NULL )
	   return 1;
   str_lcpy( k->A00LKZ, wert, L_ZIFAOKBS_A00LKZ );
   if ( *wert == 'X' )
      strcpy( k->IFA_SATZART, "003" );   /* Loeschung */

   if ( ( wert = GetWert( pSart, "A00GDAT", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A00GDAT );
   k->A00GDAT = atol( wert );  /* jjjjmmtt */

   if ( ( wert = GetWert( pSart, "A00PZN", errmld ) ) == NULL )
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A00PZN );
   k->A00PZN = atol( wert ); // --> keine Umrechnung in AC, da wir diese PZN´s nicht im Artikelstamm haben!!! ==> auch 8-stellige Nummern direkt in dieses Feld, das nicht weiterverarbeitet wird

   if ( ( wert = GetWert( pSart, "A00PBEZ", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A00PBEZ );
   str_lcpy( k->A00PBEZ, wert, L_ZIFAOKBS_A00PBEZ );

   if ( ( wert = GetWert( pSart, "A00PGMENG", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A00PGMENG );
   str_lcpy( k->A00PGMENG, wert, L_ZIFAOKBS_A00PGMENG );

   if ( ( wert = GetWert( pSart, "A00PGEINH", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A00PGEINH );
   str_lcpy( k->A00PGEINH, wert, L_ZIFAOKBS_A00PGEINH );

   if ( ( wert = GetWert( pSart, "A00DARFO", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A00DARFO );
   str_lcpy( k->A00DARFO, wert, L_ZIFAOKBS_A00DARFO );

   if ( ( wert = GetWert( pSart, "A00ANBNR7", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A00ANBNR );
   k->A00ANBNR = atol( wert );

   if ( ( wert = GetWert( pSart, "A00ATYP", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A00ATYP );
   str_lcpy( k->A00ATYP, wert, L_ZIFAOKBS_A00ATYP );

   if ( ( wert = GetWert( pSart, "A03GDAT", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A03GDAT );
   k->A03GDAT = atol( wert );  /* jjjjmmtt */

   if ( ( wert = GetWert( pSart, "A03VTSTAT", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A03VTSTAT );
   str_lcpy( k->A03VTSTAT, wert, L_ZIFAOKBS_A03VTSTAT );

   if ( ( wert = GetWert( pSart, "A03VKSTAT", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A03VKSTAT );
   str_lcpy( k->A03VKSTAT, wert, L_ZIFAOKBS_A03VKSTAT );

   if ( ( wert = GetWert( pSart, "A06GDAT", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A06GDAT );
   k->A06GDAT = atol( wert );  /* jjjjmmtt */

   if ( ( wert = GetWert( pSart, "A06PZNKP", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A06PZNKP );
   k->A06PZNKP = atol( wert ); // --> keine Umrechnung in AC, da wir diese PZN´s nicht im Artikelstamm haben!!! ==> auch 8-stellige Nummern direkt in dieses Feld, das nicht weiterverarbeitet wird

   if ( ( wert = GetWert( pSart, "A00PPN", errmld ) ) == NULL ) 
	   return 1;
   TestNoValueKlinik( wert, P_ZIFAOKBS_A00PPN );
   str_lcpy( k->A00PPN, wert, L_ZIFAOKBS_A00PPN );

   return 0;
}

// ---------------------------------------------------------------------------------- //
static void IfaFillFromOrig( struct ZIFAOKBS *k, struct ZIFAOKBS *orig )
{

   if ( IsNoValueKlinik( P_ZIFAOKBS_STAND ) )
      k->STAND = k->IFANR;                  /* !!!!!!!!!!!!!! */

   if ( IsNoValueKlinik( P_ZIFAOKBS_A00PBEZ ) )
      strcpy( k->A00PBEZ, orig->A00PBEZ );

   if ( IsNoValueKlinik( P_ZIFAOKBS_A00PGMENG ) )
      strcpy( k->A00PGMENG, orig->A00PGMENG );

   if ( IsNoValueKlinik( P_ZIFAOKBS_A00PGEINH ) )
      strcpy( k->A00PGEINH, orig->A00PGEINH );

   if ( IsNoValueKlinik( P_ZIFAOKBS_A00DARFO ) )
      strcpy( k->A00DARFO, orig->A00DARFO );

   if ( IsNoValueKlinik( P_ZIFAOKBS_A00ANBNR ) )
      k->A00ANBNR = orig->A00ANBNR;

   if ( IsNoValueKlinik( P_ZIFAOKBS_A00ATYP ) )
      strcpy( k->A00ATYP, orig->A00ATYP );

   if ( IsNoValueKlinik( P_ZIFAOKBS_A03GDAT ) )
      k->A03GDAT = orig->A03GDAT;

   if ( IsNoValueKlinik( P_ZIFAOKBS_A03VTSTAT ) )
      strcpy( k->A03VTSTAT, orig->A03VTSTAT );

   if ( IsNoValueKlinik( P_ZIFAOKBS_A03VKSTAT ) )
      strcpy( k->A03VKSTAT, orig->A03VKSTAT );

   if ( IsNoValueKlinik( P_ZIFAOKBS_A06GDAT ) )
      k->A06GDAT = orig->A06GDAT;

   if ( IsNoValueKlinik( P_ZIFAOKBS_A06PZNKP ) )
      k->A06PZNKP = orig->A06PZNKP;

   if ( IsNoValueKlinik( P_ZIFAOKBS_A00PPN ) )
      strcpy( k->A00PPN, orig->A00PPN );
}

// ---------------------------------------------------------------------------------- //
static int  FillKlinikSatz( sSatzArt *pSart, int mode, char *errmld )
{
   int  s;

   s = IfaFillKlinik( &zklinik, pSart, errmld );
   
   if ( s != 0 ) 
	   return 1;

   /* --------------------------- */

   satznr_klinik++;

   zklinik.IFANR  = ifadatumnr_klinik;
   zklinik.SATZNR = satznr_klinik;
   strcpy( zklinik.IFASTATUS, "0" );   

   if ( mode == FILL_MODE_1 )
   {
      long status;

      /* zifaokbs lesen */
      status = ReadZifaKlinik( zklinik.A00PZN, errmld );
      
	  if ( !( status == 0 || status == 100 )) 
		  return 1;

    /*  status  B00SSATZ      H_AENDERUNG   */
    /*     0    '0' '1'  '3'     '1'        */
    /*   100    '0' '1'  '3'     '0' wenn !IsNoValue */
    /*                           '2' wenn  IsNoValue */

      if ( status == 0 )
      {
         /* ok !!!!!! */
         strcpy( zklinik.AENDERUNG, "1"  );    /* Aenderung */
         IfaFillFromOrig( &zklinik, &s_KlinikRead );

		 status = UpdateKlinik( errmld );
      }
      else                /* Neuanlage */
      {
        if ( IsAnyNoValueKlinik( ) )
           strcpy( zklinik.AENDERUNG, "2" );     /* Fehler bei Neuanlage */
        else
           strcpy( zklinik.AENDERUNG, "0" );     /* Neuanlage */

		status = InsertKlinik( errmld );
      }

      if ( status != 0 ) 
		  s = 1;
   }

   return s;
}

// ---------------------------------------------------------------------------------- //
static long GenArtikelNeu( char *datei, char *satzart, int mode,
                           char *idd_file, char *errmld )
{
   sSatzDesc sD;

   sD.satzart = satzart;
   sD.mode = mode;
   sD.Fill = &FillArtikelSatz;
   return GenIfaSatz( datei, &sD, idd_file, errmld );
}

// ---------------------------------------------------------------------------------- //
static long GenKlinikNeu( char *datei, char *satzart, int mode,
                           char *idd_file, char *errmld )
{
   sSatzDesc sD;

   sD.satzart = satzart;
   sD.mode = mode;
   sD.Fill = &FillKlinikSatz;
   return GenIfaSatz( datei, &sD, idd_file, errmld );
}

// ---------------------------------------------------------------------------------- //
static void ExtractPfad( char *str )
{
  size_t i;
  int found;
  found = 0;
  i = strlen( str ) - 1;

  while ( i >= 0 && !found )
  {
     found = str[i] == ':' || str[i] == '\\' || str[i] == '/';
     if ( !found ) i--;
  }
  str[i+1] = '\0';
}


// ---------------------------------------------------------------------------------- //
static long GenAll( char *datei[], char *pfad, char *satzart, int mode,
                    char *idd_file, char *errmld  )
{
   int  i;
   long s;

/* !!!!! zum testen : kein Fillmode !!!!!!!!!!!!!!!*/
/* if ( mode == FILL_MODE_1 || mode == FILL_MODE_2 ) return 0; */

   i = 0;
   s = 0;
   while ( s == 0 && datei[i] != NULL )
   {
      ExtractPfad( pfad );
      strcat( pfad, datei[i] );
      s = GenArtikelNeu( pfad, satzart, mode, idd_file, errmld );
      if (inTransaction)
      {
          SqlCommitWork();
          inTransaction = 0;
      }
      i++;
      if (i % 10000 == 0)
      {
          SqlCommitWork();
          SqlBeginWork();
   }
   }
   SqlCommitWork();

#if defined(MSDOS) || defined(WIN32)
   /* !!!!! zum testen : Abbruch nach x Saetzen !!!!!!!!!!!!!!! */
   /* !!!!! siehe in FillArtikelSatz() !!!!!!!!!!!!!! */
   if ( s == ABBRUCH_NO_ERROR ) s = 0;
#endif

   return s;
}

// ---------------------------------------------------------------------------------- //
static long GenAllKlinik( char *datei[], char *pfad, char *satzart, int mode,
							char *idd_file, char *errmld  )
{
   int  i;
   long s;

   i = 0;
   s = 0;
   while ( s == 0 && datei[i] != NULL )
   {
      ExtractPfad( pfad );
      strcat( pfad, datei[i] );
      s = GenKlinikNeu( pfad, satzart, mode, idd_file, errmld );
      i++;
   }
   return s;
}

// ---------------------------------------------------------------------------------- //
#define ANZ_DATEI 10
static long GenArtikel( char *db, char* ili_file, char *idd_file, char *satzart,
                        char *errmld )
{
   long s;
   int i;
   long datum;
   char *datei[ANZ_DATEI];

   s = IfaLieferung( ili_file, satzart, datei, ANZ_DATEI, &datum, idd_file,
                     errmld );

   ifadatumnr  = datum;          /* !!!!!! globale Variable */
   tages_datum = GetPhoDate();   /* !!!!!! globale Variable */

         if ( OpenBase( db, errmld ) == 0 )
         {
           if ( test_ifanr( ifadatumnr, errmld ) == 0 )
           {
              if ( Open_All_FDs( errmld ) == 0 )
              {
               s = GenAll(datei, ili_file, satzart, TEST_MODE, idd_file, errmld);
               if (s == 0)
               {
                 satznr = 0;           /* !!!!!! globale Variable */
                 art_mit_pznneu = 0;
                 art_ohne_pznneu = 0;

                  s = GenAll(datei, ili_file, satzart, FILL_MODE_1, idd_file, errmld);
                 if ( s == 0 )
                  {
                      s = GenAll(datei, ili_file, satzart, FILL_MODE_2,idd_file, errmld);

              }
           }
               Close_All_FDs( );
         }
      }
       CloseBase();
   }

   for ( i = 0; i < ANZ_DATEI; i++ )
     if ( datei[i] != NULL )
       free( datei[i] );

   return s;
}

// ---------------------------------------------------------------------------------- //
static long GenKlinik( char *db, char* ili_file, char *idd_file, char *satzart,
                        char *errmld )
{
   long s;
   int i;
   long datum;
   char *datei[ANZ_DATEI];

   s = IfaLieferung( ili_file, satzart, datei, ANZ_DATEI, &datum, idd_file,
                     errmld );

   ifadatumnr_klinik = datum;   /* !!!!!! globale Variable */

   if ( s == 0 )
   {
      s = GenAllKlinik( datei, ili_file, satzart, TEST_MODE, idd_file, errmld );
      if ( s == 0 )
      {
        s = 1;
        if ( OpenBase( db, errmld ) == 0 )
        {
          if ( test_ifanr_klinik( ifadatumnr_klinik, errmld ) == 0 )
          {
             if ( Open_All_FDs_Klinik( errmld ) == 0 )
			 {
				satznr_klinik = 0;           /* !!!!!! globale Variable */
                s = GenAllKlinik( datei, ili_file, satzart, FILL_MODE_1, idd_file, errmld );
			 }
             Close_All_FDs_Klinik( );
          }
          CloseBase( );
        }
      }
   }

   for ( i = 0; i < ANZ_DATEI; i++ )
     if ( datei[i] != NULL )
       free( datei[i] );

   return s;
}

// ---------------------------------------------------------------------------------- //
#define FILE_LEN 20
long GenIfaArtNeu( char *db, char *ili_direc, char *idd_direc, char *errmld, char *errmld_klinik )
{
    char meld[100];
	
    char satzart[31];
    char *idd_file;
    char *ili_file;
	char *idd_file_klinik;
    char *ili_file_klinik;

    idd_file = malloc( strlen( idd_direc ) + FILE_LEN + 1 );
    if ( idd_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler GenIfaArtNeu" );
       return 1;
    }

    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    if ( ili_file == NULL )
    {
       free( idd_file );
       strcpy( errmld, "malloc-Fehler GenIfaArtNeu" );
       return 1;
    }

    strcpy( idd_file, idd_direc );
    strcat( idd_file, "/defprod.ifa" );
    if ( IfaSatzName( idd_file, SatzartPhx, satzart, errmld ) != 0 )
    {
       free( ili_file );
       free( idd_file );
       return 1;
    }

    strcpy( idd_file, idd_direc );
    strcat( idd_file, "/definifa.idd" );
    strcpy( ili_file, ili_direc );
    strcat( ili_file, "/liefer.ili" );
    if ( GenArtikel( db, ili_file, idd_file, satzart, errmld ) != 0 )
    {
       free( ili_file );
       free( idd_file );
       return 1;
    }

	free( ili_file );
    free( idd_file );

	sprintf( errmld, "%ld IFANR\n" \
                     "%ld IFA-Artikel erfolgreich geladen\n" \
                     "	%ld mit PZNNF\n%ld ohne PZNNF;\n",
					 ifadatumnr,
                     satznr,
                     art_mit_pznneu,
                     art_ohne_pznneu
                    );

// ------ NEUER KLINIK-BAUSTEIN --------
	idd_file_klinik = malloc( strlen( idd_direc ) + FILE_LEN + 1 );
    if ( idd_file_klinik == NULL )
    {
       strcpy( errmld_klinik, "malloc-Fehler GenIfaArtNeu" );
       return 1;
    }

    ili_file_klinik = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    if ( ili_file_klinik == NULL )
    {
       free( idd_file_klinik );
       strcpy( errmld_klinik, "malloc-Fehler GenIfaArtNeu" );
       return 1;
    }

	strcpy( idd_file_klinik, idd_direc );
    strcat( idd_file_klinik, "/defprod.ifa" );
    if ( IfaSatzName( idd_file_klinik, SatzartPhxKlinik, satzart, errmld_klinik ) != 0 )
    {
       free( ili_file_klinik );
       free( idd_file_klinik );
       return 1;
    }

    strcpy( idd_file_klinik, idd_direc );
    strcat( idd_file_klinik, "/definifa.idd" );
	strcpy( ili_file_klinik, ili_direc );
    strcat( ili_file_klinik, "/liefer.ili" );    
    
	GenKlinik( db, ili_file_klinik, idd_file_klinik, satzart, errmld_klinik );
	// auch bei Fehler weiterlaufen !!!
		
	free( ili_file_klinik );
    free( idd_file_klinik );
// --------------

    sprintf( errmld_klinik, "\n%ld KLINIKNR\n" \
							"%ld IFA-Klinikbausteine erfolgreich geladen",
                     ifadatumnr_klinik,
                     satznr_klinik
                    );

	/* als bearbeitet kennzeichnen */
    if ( WriteIfaStatus( SatzartPhx, ili_direc, meld  ) != 0		||
		 WriteIfaStatus( SatzartPhxKlinik, ili_direc, meld  ) != 0)
    {
       strcat( errmld, "\nStatus 'bearbeitet' wurde nicht gesetzt" );
    }

#if defined(MSDOS) || defined(WIN32)
#else
	/* Kommando ifa_ok aufufen */
	sprintf( meld, "ifa_ok %ld", ifadatumnr ); // Lagerwertprognose wird gestartet
	UnxHsystem( meld );
#endif

    return 0; // zpignart mode 3 wird aus EkZdp aufgerufen, um Protokoll der Neuaufnahmen zu erzeugen!
}
