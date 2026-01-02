#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <hdatum/phodate.h>

#include <voodoo_table_header/cliart.h>
#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartswitzerland.h>
#include <voodoo_table_header/csafetydatasheet.h>
#include <voodoo_table_header/carticlecodes.h>
#include <voodoo_table_header/carticlelang.h>
#include <voodoo_table_header/zartprei.h>
#include <voodoo_table_header/zartwg.h>
#include <voodoo_table_header/csdslang.h>
#include "znb_gen_li.h"
#include "zart_gen.h"

#include <libscsvoodoo/libscsvoodoo.h>

/* ----- default values for article fields ------- */
void InitArtikelFields( struct ZARTIKEL *zart, const char* const user )
{
   strcpy(zart->BEARBEITER, user );
   memset(zart->RABATTFAEHIG,'0',L_ZARTIKEL_RABATTFAEHIG); 
   strcpy(zart->ERSATZ_NR_AKTIV, VALUE_ZERO);
   strcpy(zart->PRIVATSORTIMENT, VALUE_NO);
   strcpy(zart->TAXPRUEFGROSSO, VALUE_ZERO);
   strcpy(zart->SONDERGROSSO, VALUE_BLANK);
   strcpy(zart->BESTANDSBUCHUNG, VALUE_ONE);   
   strcpy(zart->VERFALL, VALUE_ONE);   
   strcpy(zart->INDIKATOR, VALUE_ZERO);
   strcpy(zart->SKONTOFAEHIG, VALUE_ONE);   
   strcpy(zart->PREIS0ARTIKEL, VALUE_ZERO);
   strcpy(zart->MELDEPFL, VALUE_ZERO);
   strcpy(zart->MVDAARTIKEL, VALUE_ZERO);
   strcpy(zart->ZYTOSTATIKA, VALUE_ZERO);
   strcpy(zart->SICHTWAHL, VALUE_ZERO);
   strcpy(zart->RETOURENSPERRE, VALUE_ZERO);
   strcpy(zart->ZENTR_EKSPERRE, VALUE_ZERO);
   strcpy(zart->ARTIKEL_GELOESCHT, VALUE_ZERO);
   strcpy(zart->SOMMER_KK, VALUE_ZERO);
   strcpy(zart->PRODUKTART, VALUE_ZERO);   
   strcpy(zart->BESTELLSPERRE, VALUE_ZERO);
   strcpy(zart->KATALOG, VALUE_BLANK);
   strcpy(zart->LABORARTIKEL, VALUE_ZERO);
   memset( zart->ZUZAHLUNG_IFA, '0', L_ZARTIKEL_ZUZAHLUNG_IFA );
   *zart->ZUZAHLUNG_IFA     = '0';
   strcpy(zart->ARTIKEL_GESPERRT, VALUE_ZERO);
   strcpy(zart->VERTRBIND, VALUE_BLANK);
   strcpy(zart->NATURALRABATT, VALUE_ZERO);
   strcpy(zart->PRISMAEDISK, VALUE_ZERO);
   strcpy(zart->GS_EXPLOSION, VALUE_ZERO);
   strcpy(zart->GS_BRAND, VALUE_ZERO);
   strcpy(zart->GS_LEICHTENTZ, VALUE_ZERO);
   strcpy(zart->GS_HOCHENTZ, VALUE_ZERO);
   strcpy(zart->GS_GIFTIG, VALUE_ZERO);
   strcpy(zart->GS_SEHRGIFTIG, VALUE_ZERO);
   strcpy(zart->GS_GESUNDHSCH, VALUE_ZERO);
   strcpy(zart->GS_REIZEND, VALUE_ZERO);
   strcpy(zart->GS_AETZEND, VALUE_ZERO);
   strcpy(zart->GS_UMWELT, VALUE_ZERO);
   strcpy(zart->GS_VORSLAGERN, VALUE_ZERO);
   strcpy(zart->GS_SVORSLAGERN, VALUE_ZERO);
   strcpy(zart->AWL_AKTIV, VALUE_NO);
   strcpy(zart->SORTIMENT_1, VALUE_ZERO);
   strcpy(zart->SORTIMENT_2, VALUE_ZERO);
   strcpy(zart->SORTIMENT_3, VALUE_ZERO);
   strcpy(zart->SORTIMENT_4, VALUE_ZERO);
   strcpy(zart->SORTIMENT_5, VALUE_ZERO);
   strcpy(zart->PERF, VALUE_ZERO);
   strcpy(zart->TIERARZNEI, VALUE_ZERO);   
   strcpy(zart->NAHRUNGSERGAENZUNG, VALUE_NO);  
   strcpy(zart->PREISSENKUNG, VALUE_ZERO);   
   strcpy(zart->BSSICHG, VALUE_ZERO);   
   strcpy(zart->ANBIETERABSCHLAG, VALUE_ZERO);	 
   strcpy(zart->AUTIDEMARTIKEL, VALUE_ZERO);
   strcpy(zart->FESTBETRARTIKEL, VALUE_ZERO);
   strcpy(zart->REZEPTURARZNEI, VALUE_ZERO);	 
   strcpy(zart->MEDIZINPRODUKT, VALUE_ZERO);
   strcpy(zart->IMPFSTOFF, VALUE_ZERO);
   strcpy(zart->CE_KENNZEICHEN, VALUE_ZERO);
   strcpy(zart->ARZNEIMITTEL, VALUE_ZERO);
   strcpy(zart->KONTRAZEPTIVUM, VALUE_ZERO);
   strcpy(zart->ZENTRALPPELIST, VALUE_ZERO);
   strcpy(zart->EKORIGINALHS, VALUE_ZERO);
   strcpy(zart->HILFSM_VERBRAUCH, VALUE_ZERO);
   strcpy(zart->ABGABEBEST_IFA, VALUE_BLANK);
   strcpy(zart->PSYCHOTROP,VALUE_NO);
   strcpy(zart->GS_LICHTGESCH,VALUE_ZERO);
   strcpy(zart->ELEKTROSCHROTT,VALUE_NO);
   strcpy(zart->STELLER,VALUE_NO);
   strcpy(zart->PFLSCHUTZ_VERORD,VALUE_NO);
   strcpy(zart->BIOZID_VERORD,VALUE_ZERO);
   strcpy(zart->BESTELL_NUR_OZEK,VALUE_ZERO);
   strcpy(zart->CHARGENARTIKEL,VALUE_ZERO);
   strcpy(zart->HOMOEOPATHIKUM,VALUE_ZERO);
   strcpy(zart->ANTHROPOSOPHIKUM,VALUE_ZERO);
   strcpy(zart->PHYTOPHARMAKON,VALUE_ZERO);
   strcpy(zart->TREZEPTARZNEI,VALUE_ZERO);
   strcpy(zart->AMG_47,VALUE_ZERO);
   strcpy(zart->BATTERIEGESETZ,VALUE_ZERO);
   strcpy(zart->NEM_PHAGROPRUEFUNG,VALUE_ZERO);
   strcpy(zart->NEM_ZERTIFIKAT,VALUE_ZERO);
   strcpy(zart->BESTELL_NICHT_AUSL,VALUE_ZERO);
   strcpy(zart->EAN_NICHTVORHANDEN,VALUE_ZERO);
   strcpy(zart->FAELSCH_GEFAHR,VALUE_ZERO);
}

/* ----- Default values for ZARTSWITZERLAND fields ------- */
void InitZartswitzerlandFields( struct ZARTSWITZERLAND *spZartSwitz, const char* const user )
{
	strcpy(spZartSwitz->BUENDELPACKUNG,VALUE_ZERO);
	strcpy(spZartSwitz->VERTRBIND_NUR_APO,VALUE_ZERO);
	strcpy(spZartSwitz->VERTRBIND_NUR_SPIT,VALUE_ZERO);
	strcpy(spZartSwitz->VERTRBIND_KUENZLE,VALUE_ZERO);
	strcpy(spZartSwitz->VERTRBIND_INLAND,VALUE_ZERO);
	strcpy(spZartSwitz->VERTRBIND_KANTONAL,VALUE_ZERO);
	strcpy(spZartSwitz->VERTRBIND_PREWHOLE,VALUE_ZERO);
	strcpy(spZartSwitz->VERTRBIND_LISTE_C,VALUE_ZERO);
	strcpy(spZartSwitz->VERTRBIND_LISTE_D,VALUE_ZERO);
}

/* ----- Default values for CSAFETYDATASHEET fields ------- */
void InitCSafetyDataSheetFields( struct CSAFETYDATASHEET *spCSafetyDataSheet, const char* const user )
{
	// ...
}


/* No Changes from LogIndex */ 
int IsNotChanged( const struct CLIART *li, const int pos )  
{
   return NB_PL_NO_VAL == li->NB_LI_PLAUSI[ pos ];
}

/* change 'Y' to '1' and 'N' / ' ' to '0' */ 
static void CpyNY01Sign(char *art, const char *li )
{
    if ( strcmp( li, "Y" ) == 0 )
       strcpy(art,"1");
    else if ( strcmp( li, "N" ) == 0 || strcmp( li, " " ) == 0 )
       strcpy(art,"0");
}


/* ------ attach discontinued date to article name ----- */
static void ChangeArtikelName( struct ZARTIKEL *spBuf, struct CARTICLELANG *spBufLang, long datumah_old ) 
{
    char szStr[12];

	// in CH den Namen nur ändern, wenn AH- Datum kleiner "heute" = wenn AH in der Zukunft, wird der Name erst am entsprechenden Tag durch zpdailyclosing verändert.
	if ( spBuf->DATUM_AH != 0 && spBuf->DATUM_AH <= GetPhoDate())
    {
      ConvFromPhoDate( szStr, spBuf->DATUM_AH, "mmjj" );
      memcpy( &spBuf->ARTIKEL_NAME[26], szStr, 4 );
	  memcpy( &spBufLang->ARTICLENAME[26], szStr, 4 );
    }
	else if (spBuf->DATUM_AH == 0 && datumah_old > 0)	// reactivated
	{
      memcpy( &spBuf->ARTIKEL_NAME[26], "    ", 4 );
	  memcpy( &spBufLang->ARTICLENAME[26], "    ", 4 );
	}

	// nur in der Schweiz "KK" an Stelle 29-30 bei Kuehlkettenartikeln */
	if ( spBuf->KUEHLARTIKEL[0] == '4' )
	{
		memcpy( &spBuf->ARTIKEL_NAME[28], "KK", 2 );
		memcpy( &spBufLang->ARTICLENAME[28], "KK", 2 );
	}

	// nur in der Schweiz "PS" an Stelle 29-30 bei Psychotropen */
	if ( spBuf->PSYCHOTROP[0] != ' ' && spBuf->PSYCHOTROP[0] != 'N' )
	{
		memcpy( &spBuf->ARTIKEL_NAME[28], "PS", 2 );
		memcpy( &spBufLang->ARTICLENAME[28], "PS", 2 );
	}

	// "BM" nur in D an Stelle 27-28, sonst 29-30 */
	if ( spBuf->BTM[0] == '1' )
	{
		memcpy( &spBuf->ARTIKEL_NAME[28], "BM", 2 );
		memcpy( &spBufLang->ARTICLENAME[28], "BM", 2 );
	}
}

/* ---------------------- */
int Trim (char *s)
{
	int i;
	
	for (i = (int) strlen(s)-1; i >= 0; i--)
	{
		if (s[i] != ' ')
		{
			break;
		}
	}

	s[i+1] = '\0';

	return i;
}

static long ReadDfo(char * dfo)
{
   char sql[150];

   sprintf( sql, "select * from DFORM where darreichform='%s' ",
                 dfo );

   return SqlRead(  sql, dfo, NULL );
}

static long ReadZentralPpeList(long hnr, char* zentrppelist)
{
   char sql[150];
   zentrppelist[0] = '0';

   sprintf( sql, "select zentralppelist from HERSTEL where hersteller_nr=%ld ",
                 hnr );

   return SqlRead( sql, zentrppelist, NULL );
}


static char * GetDarCH_D(char * dfo)
{
	Trim(dfo);

	if ( strcmp ( dfo, "GLOB" ) == 0 )
		return "GLO"; 
	else if ( strcmp ( dfo, "GRAN" ) == 0 )
		return "GRA";
	else if ( strcmp ( dfo, "TABL" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "INJ LOES" ) == 0 )
		return "LSG";
	else if ( strcmp ( dfo, "KAPS" ) == 0 )
		return "KPS";
	else if ( strcmp ( dfo, "LIQ" ) == 0 )
		return "LIQ";
	else if ( strcmp ( dfo, "CREME" ) == 0 )
		return "CRE";
	else if ( strcmp ( dfo, "PLV" ) == 0 )
		return "PLV";
	else if ( strcmp ( dfo, "TROPFEN" ) == 0 )
		return "GTT";
	else if ( strcmp ( dfo, "LOES" ) == 0 )
		return "LSG";
	else if ( strcmp ( dfo, "GEL" ) == 0 )
		return "GEL";
	else if ( strcmp ( dfo, "SPR" ) == 0 )
		return "SPR";
	else if ( strcmp ( dfo, "FILMTABL" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "OEL" ) == 0 )
		return "OEL";
	else if ( strcmp ( dfo, "SALBE" ) == 0 )
		return "UNG";
	else if ( strcmp ( dfo, "DRAG" ) == 0 )
		return "DRG";
	else if ( strcmp ( dfo, "LOT" ) == 0 )
		return "LOT";
	else if ( strcmp ( dfo, "INF LOES" ) == 0 )
		return "LSG";
	else if ( strcmp ( dfo, "SUPP" ) == 0 )
		return "SUP";
	else if ( strcmp ( dfo, "GLOB BIOTH" ) == 0 )
		return "GLO";
	else if ( strcmp ( dfo, "VAPO" ) == 0 )
		return "VAP";
	else if ( strcmp ( dfo, "GTT OPHT" ) == 0 )
		return "GTT";
	else if ( strcmp ( dfo, "SIRUP" ) == 0 )
		return "SIR";
	else if ( strcmp ( dfo, "EMULS" ) == 0 )
		return "EMU";
	else if ( strcmp ( dfo, "BRAUSETABL" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "PASTILLEN" ) == 0 )
		return "PAS";
	else if ( strcmp ( dfo, "AROMAESS" ) == 0 )
		return "ESS";
	else if ( strcmp ( dfo, "BALS" ) == 0 )
		return "BAL";
	else if ( strcmp ( dfo, "GLYC MAZ" ) == 0 )
		return "GLM";
	else if ( strcmp ( dfo, "KAUTABL" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "RET TABL" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "GRAN BIOTH" ) == 0 )
		return "GRA";
	else if ( strcmp ( dfo, "TTS" ) == 0 )
		return "TTS";
	else if ( strcmp ( dfo, "LUTSCHTABL" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "INJ SUSP" ) == 0 )
		return "SUS";
	else if ( strcmp ( dfo, "SUSP" ) == 0 )
		return "SUS";
	else if ( strcmp ( dfo, "LACTABS" ) == 0 )
		return "TAB";
	else if ( strcmp ( dfo, "AEROS" ) == 0 )
		return "SPR";
	else if ( strcmp ( dfo, "NASENSPRAY" ) == 0 )
		return "SPR";
	else if ( strcmp ( dfo, "PDR" ) == 0 )
		return "PDR";
	else if (ReadDfo(dfo) == 0)
		return dfo;
	else 
		return "";
}

static char * GetDarCH_F(char * dfo)
{
	Trim(dfo);

	if ( strcmp ( dfo, "GLOB" ) == 0 )
		return "GLO"; 
	else if ( strcmp ( dfo, "GRAN" ) == 0 )
		return "GRA";	
	else if ( strcmp ( dfo, "CPR" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "SOL INJ" ) == 0 )
		return "SOL";
	else if ( strcmp ( dfo, "CAPS" ) == 0 )
		return "CAP";
	else if ( strcmp ( dfo, "LIQ" ) == 0 )
		return "LIQ";
	else if ( strcmp ( dfo, "CREME" ) == 0 )
		return "CRE";
	else if ( strcmp ( dfo, "PDR" ) == 0 )
		return "PDR";
	else if ( strcmp ( dfo, "GOUTTES" ) == 0 )
		return "GTT";
	else if ( strcmp ( dfo, "SOL" ) == 0 )
		return "SOL";
	else if ( strcmp ( dfo, "GEL" ) == 0 )
		return "GEL";
	else if ( strcmp ( dfo, "SPR" ) == 0 )
		return "SPR";
	else if ( strcmp ( dfo, "CPR FILM" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "HUILE" ) == 0 )
		return "HUI";
	else if ( strcmp ( dfo, "ONG" ) == 0 )
		return "ONG";
	else if ( strcmp ( dfo, "DRAG" ) == 0 )
		return "DRG";
	else if ( strcmp ( dfo, "LOT" ) == 0 )
		return "LOT";
	else if ( strcmp ( dfo, "SOL PERF" ) == 0 )
		return "SOL";
	else if ( strcmp ( dfo, "TEINT MERE" ) == 0 )
		return "TM ";
	else if ( strcmp ( dfo, "SUBST SECHE" ) == 0 )
		return "SUB";
	else if ( strcmp ( dfo, "SUPP" ) == 0 )
		return "SUP";
	else if ( strcmp ( dfo, "SIROP" ) == 0 )
		return "SIR";
	else if ( strcmp ( dfo, "GLOB BIOTH" ) == 0 )
		return "GLO";
	else if ( strcmp ( dfo, "VAPO" ) == 0 )
		return "VAP";
	else if ( strcmp ( dfo, "GTT OPHT" ) == 0 )
		return "GTT";
	else if ( strcmp ( dfo, "EMULS" ) == 0 )
		return "EMU";
	else if ( strcmp ( dfo, "CPR EFF" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "PASTILLES" ) == 0 )
		return "PAS";
	else if ( strcmp ( dfo, "ESS AROMAT" ) == 0 )
		return "ESS";
	else if ( strcmp ( dfo, "BAUME" ) == 0 )
		return "BAU";
	else if ( strcmp ( dfo, "MAC GLYC" ) == 0 )
		return "MAC";
	else if ( strcmp ( dfo, "CPR CROQUER" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "CPR RET" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "TTS" ) == 0 )
		return "TTS";
	else if ( strcmp ( dfo, "GRAN BIOTH" ) == 0 )
		return "GRA";
	else if ( strcmp ( dfo, "CPR SUCER" ) == 0 )
		return "CPR";
	else if ( strcmp ( dfo, "SUSP INJ" ) == 0 )
		return "SUS";
	else if ( strcmp ( dfo, "SUSP" ) == 0 )
		return "SUS";
	else if ( strcmp ( dfo, "LACTABS" ) == 0 )
		return "TAB";
	else if ( strcmp ( dfo, "AEROS" ) == 0 )
		return "SPR";
	else if ( strcmp ( dfo, "SPRAY NASAL" ) == 0 )
		return "SPR";
	else if ( strcmp ( dfo, "PDR" ) == 0 )
		return "PDR";
	else if (ReadDfo(dfo) == 0)
		return dfo;
	else 
		return "";
}


/* Articlename */
static void Make_ARTIKEL_NAME( struct ZARTIKEL *spBuf, struct CARTICLELANG *spBufLang, const  struct CLIART *spLIBuf, const int iExistsArticle)
{
	char * spCut;

	if ( iExistsArticle == 0 || !IsNotChanged( spLIBuf, PL_DSCRD ) )
	{
		memset( spBuf->ARTIKEL_NAME, ' ', L_ZARTIKEL_ARTIKEL_NAME );
		memcpy( spBuf->ARTIKEL_NAME, spLIBuf->DSCRD, L_ZARTIKEL_ARTIKEL_NAME );

		spCut = strstr(spBuf->ARTIKEL_NAME, "[!]");

		if ( spCut == NULL )
			spBuf->ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME] = '\0';
		else
			spBuf->ARTIKEL_NAME[strlen(spBuf->ARTIKEL_NAME) - strlen(spCut)] = '\0';
	}

	if ( iExistsArticle == 0 || !IsNotChanged( spLIBuf, PL_DSCRF ) )
	{
		memset( spBufLang->ARTICLENAME, ' ', L_CARTICLELANG_ARTICLENAME );
		memcpy( spBufLang->ARTICLENAME, spLIBuf->DSCRF, L_CARTICLELANG_ARTICLENAME );

		spCut = strstr(spBufLang->ARTICLENAME, "[!]");

		if ( spCut == NULL )
			spBufLang->ARTICLENAME[L_CARTICLELANG_ARTICLENAME] = '\0';
		else
			spBufLang->ARTICLENAME[strlen(spBufLang->ARTICLENAME) - strlen(spCut)] = '\0';
	}

	if ( iExistsArticle == 0 || !IsNotChanged( spLIBuf, PL_DSCRLONGD ) )
	{
		memset( spBuf->ARTIKEL_LANGNAME, ' ', L_ZARTIKEL_ARTIKEL_LANGNAME );
		memcpy( spBuf->ARTIKEL_LANGNAME, spLIBuf->DSCRLONGD, L_ZARTIKEL_ARTIKEL_LANGNAME );

		spCut = strstr(spBuf->ARTIKEL_LANGNAME, "[!]");

		if ( spCut == NULL )
			spBuf->ARTIKEL_LANGNAME[L_ZARTIKEL_ARTIKEL_LANGNAME] = '\0';
		else
			spBuf->ARTIKEL_LANGNAME[strlen(spBuf->ARTIKEL_LANGNAME) - strlen(spCut)] = '\0';
	}

	if ( iExistsArticle == 0 || !IsNotChanged( spLIBuf, PL_DSCRLONGF ) )
	{
		memset( spBufLang->ARTICLENAMELONG, ' ', L_CARTICLELANG_ARTICLENAMELONG );
		memcpy( spBufLang->ARTICLENAMELONG, spLIBuf->DSCRLONGF, L_CARTICLELANG_ARTICLENAMELONG );

		spCut = strstr(spBufLang->ARTICLENAMELONG, "[!]");

		if ( spCut == NULL )
			spBufLang->ARTICLENAMELONG[L_CARTICLELANG_ARTICLENAMELONG] = '\0';
		else
			spBufLang->ARTICLENAMELONG[strlen(spBufLang->ARTICLENAMELONG) - strlen(spCut)] = '\0';
	}
}


static void NormiereEinheit( char *spStr, char *spEinheit )
{
	Trim(spEinheit);

	if ( strcmp ( spEinheit, "METER" ) == 0 )
		memcpy( spStr, "M ", 2 ); 
	else if ( strcmp ( spEinheit, "PAAR" ) == 0 )
		memcpy( spStr, "PA", 2 );
	else if ( strcmp ( spEinheit, "STK" ) == 0 )
		memcpy( spStr, "ST", 2 );
	else if ( strcmp ( spEinheit, "G" ) == 0 )
		memcpy( spStr, "GR", 2 );
	else if ( strcmp ( spEinheit, "PAIRE" ) == 0 )
		memcpy( spStr, "PA", 2 );
	else
		memcpy( spStr, spEinheit, 2 );
}

void Build_EINHEIT( char *ArtEinheit, char *PgEinh, const double PgMeng, const short Multiplier )
{
   char str[20] = {0};
   char *pstr;
   int  maxlng;
   size_t  lng;
   size_t  pos;

   memset( ArtEinheit, ' ', L_ZARTIKEL_EINHEIT );
   ArtEinheit[L_ZARTIKEL_EINHEIT] = '\0';
 
   maxlng = L_ZARTIKEL_EINHEIT - 2;

   if (Multiplier > 1 && Multiplier != PgMeng)
	   sprintf(str, "%dX%.3f", Multiplier, PgMeng);
   else
	   sprintf(str, "%.3f", PgMeng);

   // --- entfernen unnötiger Nachkommastellen
    lng = strlen(str);

    while ( lng > 0 )
	{
		if ( str[lng-1] == '0' ) 
		{
			--lng;
		}
		else if ( str[lng-1] == '.' )
		{
			--lng;
			str[lng] = '\0';
			break;
		}
		else
		{
			str[lng] = '\0';
			break;
		}
	}
   // --- 

   lng = strlen(str);
   if ( lng > maxlng ) 
	   lng = maxlng;
   pos = maxlng - lng;
   if ( pos > 0 )
      pos--;	/* 1 blank lassen zwischen Groesse und Einheit */
   if (  lng > 0 )
      memcpy( &ArtEinheit[pos], str, lng );

   NormiereEinheit( &ArtEinheit[L_ZARTIKEL_EINHEIT - 2], PgEinh );

   /* change point to comma */
   pstr = ArtEinheit;
   while ( *pstr )
   {
      if ( *pstr == '.' ) *pstr = ',';
      pstr++;
   }
}

/* Übernahme LogIndex auf Zartswitzerland */
void LISatzToArtikelSwitz(const struct CLIART *spLIBuf, struct ZARTSWITZERLAND *spBuf, 
							struct ZARTIKEL *CZartBuf, int iExistsArticle )
{
    char spSmNo[9]	= {0};
	char temp[6]	= {0};

	/* Artikel-Nr */
   spBuf->ARTIKEL_NR = spLIBuf->PHAR;

   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_SMCAT ) == 0 )
   {
		strcpy (spBuf->IKS_CODE, spLIBuf->SMCAT);

		if ( strcmp(spLIBuf->SMCAT, "A") == 0 || 
			 strcmp(spLIBuf->SMCAT, "B") == 0  )
			strcpy(CZartBuf->REZEPTPFL, "1");
		else
			strcpy(CZartBuf->REZEPTPFL, "0");

		if ( strcmp(spLIBuf->SMCAT, "C") == 0 )
			strcpy(spBuf->VERTRBIND_LISTE_C, "1");
		else
			strcpy(spBuf->VERTRBIND_LISTE_C, "0");
		
		if ( strcmp(spLIBuf->SMCAT, "D") == 0 )
			strcpy(spBuf->VERTRBIND_LISTE_D, "1");
		else
			strcpy(spBuf->VERTRBIND_LISTE_D, "0");


		if ( strcmp(spLIBuf->SMCAT, "A") == 0 || 
			 strcmp(spLIBuf->SMCAT, "B") == 0 ||
			 strcmp(spLIBuf->SMCAT, "C") == 0 || 
			 strcmp(spLIBuf->SMCAT, "D") == 0 ||
			 strcmp(spLIBuf->SMCAT, "E") == 0 )
		{
			strcpy(CZartBuf->ARZNEIMITTEL, "1");
			strcpy(CZartBuf->CHARGENARTIKEL, "1");   // CPR-210673
		}
   }

   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_SMNO ) == 0 )
   {
		sprintf(spSmNo, "%08.8ld", spLIBuf->SMNO);
	   strncpy(temp, spSmNo, 5);
	   spBuf->SWISSMEDIC_REGNR = atoi(temp);

	   if ( spBuf->SWISSMEDIC_REGNR > 0 )
		   spBuf->SWISSMEDIC_ZUSATZ = atoi(spSmNo + 6);
   }
	
	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_BAGDOSSIER ) == 0 )
		spBuf->BAGDOSSIER = spLIBuf->BAGDOSSIER;

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_MIGCD ) == 0 )
		strcpy (spBuf->MIGCD, spLIBuf->MIGCD);

	if (iExistsArticle == 0)
	{
		strcpy(spBuf->VERTRBIND_INLAND, spLIBuf->VERTRBIND_INLAND);
		strcpy(spBuf->VERTRBIND_KANTONAL, spLIBuf->VERTRBIND_KANTONAL);
		strcpy(spBuf->VERTRBIND_KUENZLE, spLIBuf->VERTRBIND_KUENZLE);
		strcpy(spBuf->VERTRBIND_NUR_APO, spLIBuf->VERTRBIND_NUR_APO);
		strcpy(spBuf->VERTRBIND_NUR_SPIT, spLIBuf->VERTRBIND_NUR_SPIT);
	}
}

void LISatzToCSafetyDataSheet(const struct CLIART *spLIBuf, struct CSAFETYDATASHEET *spBuf, 
								struct ZARTIKEL *CZartBuf, int iExistsArticle )
{
	/* Artikel-Nr */
	spBuf->ARTICLENO = spLIBuf->PHAR;

	// Falls das SIGNALWORT == 3 ist (Manuell) dann werden SIGNALWORT und GHS-Felder nicht
	// upgedatet. Der Benutzer erhält einen Hinweis in der GUI.
	if (3 != spBuf->SIGNALWORD)
	{
		if (0 == strncmp(spLIBuf->CDVAL, "ATTENTION", 9))
		{
			spBuf->SIGNALWORD = 1;
		}
		else if (0 == strncmp(spLIBuf->CDVAL, "DANGER", 6))
		{
			spBuf->SIGNALWORD = 2;
		}
		else if (0 == strncmp(spLIBuf->CDVAL, "NOSIGNALWORD", 12))
		{
			spBuf->SIGNALWORD = 4;
		}
		else
		{
			spBuf->SIGNALWORD = 0;
		}

		spBuf->PICTOGRAM01_FLAG = spLIBuf->PICTOGRAM01_FLAG;
		spBuf->PICTOGRAM02_FLAG = spLIBuf->PICTOGRAM02_FLAG;
		spBuf->PICTOGRAM03_FLAG = spLIBuf->PICTOGRAM03_FLAG;
		spBuf->PICTOGRAM04_FLAG = spLIBuf->PICTOGRAM04_FLAG;
		spBuf->PICTOGRAM05_FLAG = spLIBuf->PICTOGRAM05_FLAG;
		spBuf->PICTOGRAM06_FLAG = spLIBuf->PICTOGRAM06_FLAG;
		spBuf->PICTOGRAM07_FLAG = spLIBuf->PICTOGRAM07_FLAG;
		spBuf->PICTOGRAM08_FLAG = spLIBuf->PICTOGRAM08_FLAG;
		spBuf->PICTOGRAM09_FLAG = spLIBuf->PICTOGRAM09_FLAG;
	}

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_SDS_DATE_DE ) == 0 )
		ConvFromPhoDate ( spBuf->SDS_VERSION, spLIBuf->SDS_DATE_DE, "tt.mm.jjjj" );

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_GS_EXPLOSION ) == 0 )
		strcpy (CZartBuf->GS_EXPLOSION, spLIBuf->GS_EXPLOSION);

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_GS_HOCHENTZ ) == 0 )
		strcpy (CZartBuf->GS_HOCHENTZ, spLIBuf->GS_HOCHENTZ);

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_GS_LEICHTENTZ ) == 0 )
		strcpy (CZartBuf->GS_LEICHTENTZ, spLIBuf->GS_LEICHTENTZ);

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_GS_BRAND ) == 0 )
		strcpy (CZartBuf->GS_BRAND, spLIBuf->GS_BRAND);

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_GS_AETZEND ) == 0 )
		strcpy (CZartBuf->GS_AETZEND, spLIBuf->GS_AETZEND);

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_GS_SEHRGIFTIG ) == 0 )
		strcpy (CZartBuf->GS_SEHRGIFTIG, spLIBuf->GS_SEHRGIFTIG);

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_GS_GIFTIG ) == 0 )
		strcpy (CZartBuf->GS_GIFTIG, spLIBuf->GS_GIFTIG);

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_GS_GESUNDHSCH ) == 0 )
		strcpy (CZartBuf->GS_GESUNDHSCH, spLIBuf->GS_GESUNDHSCH);

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_GS_REIZEND ) == 0 )
		strcpy (CZartBuf->GS_REIZEND, spLIBuf->GS_REIZEND);

	if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_GS_UMWELT ) == 0 )
		strcpy (CZartBuf->GS_UMWELT, spLIBuf->GS_UMWELT);

	strcpy (spBuf->EU_HAZARD_STATM, spLIBuf->HAZARD_STMT);
}


/* Übernahme LogIndex auf Zartwg */
void LISatzToArtWgr2( const struct CLIART *spLIBuf, struct ZARTWG *spBuf )
{
	strncpy(spBuf->WARENGRUPPE, spLIBuf->WGR_PHARMOS, L_ZARTWG_WARENGRUPPE);
}

void LISatzToArtWgr5( const struct CLIART *spLIBuf, struct ZARTWG *spBuf )
{
	strncpy(spBuf->WARENGRUPPE, spLIBuf->WGR_SAISON, 2);
}

void LISatzToArtWgrA( const struct CLIART *spLIBuf, struct ZARTWG *spBuf )
{
	strncpy(spBuf->WARENGRUPPE, spLIBuf->WGR_SAISON2, 2);
}

void LISatzToCSdsLang(const struct CLIART *spLIBuf, struct CSDSLANG *spBuf)
{
	if (spBuf->SDS_VERSION[0] != ' ')
		sprintf(spBuf->SDS_LINK, "%s%ld/%s", "http://apps.hcisolutions.ch/sds/phc/", spLIBuf->PHAR, spBuf->LANGID);
}

/* Übernahme LogIndex auf CArticlecodes */
void LISatzToCodeATC( const struct CLIART *spLIBuf, struct CARTICLECODES *spBuf )
{
	strncpy(spBuf->ARTICLE_CODE, spLIBuf->ATC, L_CLIART_ATC); // ohne abschließende 0
}

void LISatzToCodeBAG( const struct CLIART *spLIBuf, struct CARTICLECODES *spBuf )
{
	strncpy(spBuf->ARTICLE_CODE, spLIBuf->BAGNO, L_CLIART_BAGNO);  // ohne abschließende 0
}

void LISatzToCodeCDSO(const struct CLIART *spLIBuf, struct CARTICLECODES *spBuf )
{
	strncpy(spBuf->ARTICLE_CODE, spLIBuf->CDSO1, L_CLIART_CDSO1); // ohne abschließende 0
}

/* ------------- Nullen am Anfang eines Strings eliminieren ---------- */
int Trim_Leading_Zeros (char *s)
{
	int i;
	 
	i = (int) strspn(s, "0"); // Anzahl der Nullen am Anfang

	strcpy(s, &s[i]);
	
	return i;
}

void LISatzToCodeGtin14(const struct CLIART *spLIBuf, struct CARTICLECODES *spBuf )
{
	strncpy(spBuf->ARTICLE_CODE, spLIBuf->GTIN14, L_CLIART_GTIN14); // ohne abschließende 0
	spBuf->SERIAL_NUMBER = 1;
	
	Trim_Leading_Zeros(spBuf->ARTICLE_CODE);
}

/* Übernahme LogIndex auf Zartikel*/
void LISatzToArtikel( struct CLIART *spLIBuf, struct ZARTIKEL *spBuf, struct ZARTIKEL *spBufOld, struct CARTICLELANG *spBufLang, int iExistsArticle )
{
   // generell nur Werte übernehmen, die tatsächlich von LogIndex geändert wurden!
   spBuf->ARTIKEL_NR = spLIBuf->PHAR;
   spBuf->DATUM_IFAAENDER = spLIBuf->LINR;
   spBuf->DATUM_AENDER = GetPhoDate();

   if (iExistsArticle == 0)
   {
	   spBuf->DATUM_ANLAGE = GetPhoDate();
   }

   spBuf->HERSTELLER_NR = spLIBuf->HERSTELLER_NR;   
   
   if (spLIBuf->AWL1 > 0) // AWL1 über LogIndex nicht auf 0 zurücksetzen!
		spBuf->AWL1	= spLIBuf->AWL1; 

   if (spBuf->AWL1 > 0)
	   strcpy(spBuf->AWL_AKTIV, "J");
   else
	   strcpy(spBuf->AWL_AKTIV, "N");

   if (iExistsArticle == 0)
		CpyNY01Sign( spBuf->KLINIKPACKUNG, spLIBuf->CLINCD );

   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_COOL ) == 0 )
   {
	   if ( strcmp(spLIBuf->COOL, "Y") == 0 || 
			strcmp(spLIBuf->COOL, "1") == 0 || 
			strcmp(spLIBuf->COOL, "2") == 0    )
	   {
			strcpy(spBuf->KUEHLARTIKEL, "4");
	   }
	   else
			strcpy(spBuf->KUEHLARTIKEL, "0");
   }

  if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_CDBG ) == 0 )
  {
		if ( strcmp(spLIBuf->CDBG, " ") == 0 )
			strcpy(spBuf->PSYCHOTROP, "N");
		else if ( strcmp(spLIBuf->CDBG, "A") == 0 )
		{
			strcpy(spBuf->PSYCHOTROP, "N");
			strcpy(spBuf->BTM, "1");
		}
		else
			strcpy(spBuf->PSYCHOTROP, spLIBuf->CDBG); // 1:1 Übernahme, auch Artikeländerungen
  }

   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_BG ) == 0 )
	   CpyNY01Sign(spBuf->BTM, spLIBuf->BG);

   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_EXP ) == 0 )
   {
	   if (spLIBuf->EXP < 9)
		   spBuf->LAUFZEITMONATE = spLIBuf->EXP;

	 //	if (spLIBuf->EXP > 0)
	 //	   strcpy(spBuf->VERFALL, "1"); --> wird per Default bei alle Neuanlage gesetzt, aber keine Abhängigkeit mehr zu laufzeitmonate !
   }

   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_NINCD ) == 0 )
   {
		if ( spLIBuf->NINCD == 10 )
			strcpy( spBuf->SORTIMENT_1, "1");
		else
			strcpy( spBuf->SORTIMENT_1, "0");
   }

   if (iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_NINCD ) == 0 || IsNotChanged( spLIBuf, PL_CDSO1 ) == 0 )
   {
		if(strncmp(spLIBuf->CDSO1,"11.", 3) == 0 && spLIBuf->NINCD == 10)
			strcpy(spBuf->SORTIMENT_4, "1");
		
		// CPR-210673
		if (iExistsArticle == 0)
		{
			if (strncmp(spLIBuf->CDSO1, "19.", 3) == 0)
				strcpy(spBuf->CHARGENARTIKEL, "1");
		}
		else if (IsNotChanged(spLIBuf, PL_CDSO1) == 0)
		{
			if (strncmp(spLIBuf->CDSO1, "19.", 3) != 0)
			{
				if (spLIBuf->BLOOD != 1 && (
					strcmp(spLIBuf->SMCAT, "A") < 0 ||
					strcmp(spLIBuf->SMCAT, "E") > 0))
				{
					strcpy(spBuf->CHARGENARTIKEL, "0");
				}
			}
		}
   }

   // CpyNY01Sign(spBuf->NICHTUEBERGH, spLIBuf->DEPCD);

   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_OUTSAL ) == 0 )
   {
	   spBuf->DATUM_AH = spLIBuf->OUTSAL;

	   if (spBuf->DATUM_AH > 0)   // Retourensperre should be set automatically, when DATUM_AH was set (see SR-23013365)
		   strcpy(spBuf->RETOURENSPERRE, "1");
   }

   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_STTOX ) == 0 )
		CpyNY01Sign(spBuf->SIDABLATT, spLIBuf->STTOX);

   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_CE ) == 0 )
		CpyNY01Sign(spBuf->CE_KENNZEICHEN, spLIBuf->CE);
   
   if ( iExistsArticle == 0 || 
	    IsNotChanged( spLIBuf, PL_SMCDAT ) == 0 ||
	    IsNotChanged( spLIBuf, PL_SIST )   == 0 ||
		IsNotChanged( spLIBuf, PL_ESIST )  == 0  )
   {
		if ( spLIBuf->SMCDAT > 0 )
			spBuf->DATUM_RR = spLIBuf->SMCDAT;
	   else if ( spLIBuf->SIST > 0 && spLIBuf->SIST > spLIBuf->ESIST )
			spBuf->DATUM_RR = spLIBuf->SIST;
	   else // if ( spLIBuf->ESIST > spLIBuf->SIST && IsNotChanged( spLIBuf, PL_ESIST ) == 0) --> CPR-171010: RR- Datum zurücksetzen, wenn SMCDAT=0 kommt und RR- Datum nicht via SIST gesetzt wird!
			spBuf->DATUM_RR = 0;
   }

   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_BIOCID ) == 0 )
   {
	   if ( spLIBuf->BIOCID > 0 )
		   strcpy (spBuf->BIOZID_VERORD, "1");
	   else
		   strcpy (spBuf->BIOZID_VERORD, "0");
   }

   // SR-112613: keine Versorgung des Vorgängers wg Pharmos- Problemen !?
   // --> Probleme kamen nicht von hier, sondern von manueller Pflege = wieder aktiviert (09/2014)
   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_PHAR2 ) == 0)
   	   spBuf->ARTIKEL_NR_ORIG = spLIBuf->PHAR2;

   if ( iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_BLOOD ) == 0)
   {
	   if ( spLIBuf->BLOOD != 0 )
		   strcpy (spBuf->CHARGENARTIKEL, "1");
   }

   if ( spLIBuf->BLOOD != 0 )
   {
	   strcpy (spBuf->TFG, "1");
   }

   if ((iExistsArticle == 0 || IsNotChanged(spLIBuf, PL_BIOSIM)) && strcmp(spLIBuf->BIOSIM, "1") == 0) {
	   strcpy(spBuf->PRODUKTART, "A"); // A for Biosimilar
   }
   else if (iExistsArticle == 0 || IsNotChanged(spLIBuf, PL_GENCD) == 0)
   {
	   if (strcmp(spLIBuf->GENCD, "O") == 0)
	   {
		   strcpy(spBuf->PRODUKTART, "1");
	   }
	   else if (strcmp(spLIBuf->GENCD, "S") == 0)
	   {
		   strcpy(spBuf->PRODUKTART, "A");
	   }
	   else if (strcmp(spLIBuf->GENCD, "G") == 0)
	   {
		   strcpy(spBuf->PRODUKTART, "2");
	   }
	   else 
	   {
		   strcpy(spBuf->PRODUKTART, "0");
	   }
   }

   if (iExistsArticle == 0)
	   strncpy(spBuf->ARTIKEL_NR_HERST, spLIBuf->ARTNO1, L_ZARTIKEL_ARTIKEL_NR_HERST);

   if (iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_QTYUD ) == 0 || IsNotChanged( spLIBuf, PL_QTY ) == 0 || IsNotChanged( spLIBuf, PL_NOPCS ) == 0)
		Build_EINHEIT(spBuf->EINHEIT, spLIBuf->QTYUD, spLIBuf->QTY, spLIBuf->NOPCS);
   
   if (iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_QTYUF ) == 0 || IsNotChanged( spLIBuf, PL_QTY ) == 0 || IsNotChanged( spLIBuf, PL_NOPCS ) == 0)
	   Build_EINHEIT(spBufLang->PACKAGINGUNIT, spLIBuf->QTYUF, spLIBuf->QTY, spLIBuf->NOPCS);
      
   if (iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_PCKTYPD ) == 0)
		strncpy (spBuf->DARREICHFORM, GetDarCH_D(spLIBuf->PCKTYPD), L_ZARTIKEL_DARREICHFORM);
   
   if (iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_PCKTYPF ) == 0)
		strncpy (spBufLang->PHARMAFORM, GetDarCH_F(spLIBuf->PCKTYPF), L_ZARTIKEL_DARREICHFORM);


   Make_ARTIKEL_NAME(spBuf, spBufLang, spLIBuf, iExistsArticle );   
  
   spBuf->DATUM_IFALOESCH = 0;  

   ChangeArtikelName( spBuf, spBufLang, spBufOld->DATUM_AH ); 

   if (iExistsArticle == 0) // Übernahme zentralppelist aus herstel
	   ReadZentralPpeList(spBuf->HERSTELLER_NR, spBuf->ZENTRALPPELIST);

   if (iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_SALECD ) == 0)
   {
		if(strcmp(spLIBuf->SALECD, "P") == 0 || strcmp(spLIBuf->SALECD, "R") == 0)
			strcpy(spBuf->ARTIKEL_GESPERRT, "1");
		else if(strcmp(spLIBuf->SALECD, "N") == 0)
			strcpy(spBuf->ARTIKEL_GESPERRT, "0");
   }

   strcpy(spBuf->G_UN_NR, spLIBuf->G_UN_NR);
   strcpy(spBuf->G_VCI, spLIBuf->LAGERKLASSE);
   strcpy(spBuf->GG_KLASSE, spLIBuf->GG_KLASSCODE);
   strcpy(spBuf->VERPACKUNGSGRUPPE, spLIBuf->GG_VERPACKCODE);

   spBuf->SERIAL_NUMBER_TRACKING = spLIBuf->SERIAL_NUMBER_TRACKING;

   if (iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_ATC ) == 0)
   {
		if(strncmp(spLIBuf->ATC, "L01", 3) == 0)
			strcpy(spBuf->ZYTOSTATIKA, "1");
   }
	
   if (iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_GRPCD ) == 0)
   {
		if(strcmp(spLIBuf->GRPCD, "P2") == 0)
			spBuf->KOSMETIKUM = 1;
   }
	
   if (iExistsArticle == 0)
	{
		strcpy(spBuf->PREIS0ARTIKEL, spLIBuf->PREIS0ARTIKEL);
		strcpy(spBuf->ARTIKEL_GESPERRT, spLIBuf->ARTIKEL_GESPERRT);
		strcpy(spBuf->PRIVATSORTIMENT, spLIBuf->PRIVATSORTIMENT);
		strcpy(spBuf->VERFALL, spLIBuf->VERFALL);
	}

   if (iExistsArticle == 0 || IsNotChanged( spLIBuf, PL_PRDGRPCD ) == 0)
   {
	   strcpy(spBuf->PHYTOPHARMAKON, spLIBuf->PHYTOPHARMAKON);
	   strcpy(spBuf->HOMOEOPATHIKUM, spLIBuf->HOMOEOPATHIKUM);
	   strcpy(spBuf->ANTHROPOSOPHIKUM, spLIBuf->ANTHROPOSOPHIKUM);
	   strcpy(spBuf->TIERARZNEI, spLIBuf->TIERARZNEI);
	   strcpy(spBuf->MEDIZINPRODUKT, spLIBuf->MEDIZINPRODUKT);
	   strcpy(spBuf->IMPFSTOFF, spLIBuf->IMPFSTOFF);
   }
}

/* ---- Preise --------------------- */

int IsPreisChanged( struct CLIART *spLIBuf, struct ZARTPREIS *spPreisCurrent )
{
	if ( !IsNotChanged( spLIBuf, PL_PRICE_PEXF	) ||
		 !IsNotChanged( spLIBuf, PL_VAT			) ||
         !IsNotChanged( spLIBuf, PL_PRICE_PPUB	) || 
		 (spLIBuf->HERST_PROZENT != spPreisCurrent->HERST_PROZENT && spLIBuf->HERST_PROZENT != 0.0) || 
		 (spLIBuf->LIEFERBASISPREIS != spPreisCurrent->LIEFERBASISPREIS && spLIBuf->LIEFERBASISPREIS != 0.0))   
        return 1;
	else
        return 0;
}

int LISatzToPreis( const struct CLIART *spLIBuf, struct ZARTPREIS *spBuf, struct ZARTIKEL *bufArt, struct ZARTSWITZERLAND *bufSwitz,
                     int iExistsArticle )
{
	/* Übernahme immer, aber vorher in zpliartik ZWING bei Preisänderung für nicht 1 / A / B   +   Artikel entsperren, wenn Preis von 0 auf gültigen Wert geht !!!
	if (iExistsArticle					 == 0 || 
		strcmp(bufArt->SORTIMENT_1,"1")  == 0 ||
		strcmp(bufSwitz->IKS_CODE, "A")  == 0 ||
		strcmp(bufSwitz->IKS_CODE, "B")  == 0  ) */
	{
		double newGrosso = 0.0;
		double herstproz;
		double lbp;

		if (spLIBuf->HERST_PROZENT != 0.0 || spLIBuf->LIEFERBASISPREIS != 0.0)
		{
			if (spLIBuf->HERST_PROZENT == 0.0)
				herstproz = bufArt->HERST_PROZENT;
			else
				herstproz = spLIBuf->HERST_PROZENT; 

			if (spLIBuf->LIEFERBASISPREIS == 0.0)
				lbp = spBuf->LIEFERBASISPREIS;
			else
				lbp = spLIBuf->LIEFERBASISPREIS;

			if (herstproz != 0.0 && lbp > 0.0)
				newGrosso = lbp - ( lbp * herstproz / 100 );
		}
		else
			spBuf->HERST_PROZENT = bufArt->HERST_PROZENT;
		
		if ( newGrosso > 0.0 && (newGrosso <= spLIBuf->PRICE_PPUB || spLIBuf->PRICE_PPUB == 0)  )
		{
			spBuf->GROSSO = newGrosso;
			spBuf->HERST_PROZENT = herstproz;
			spBuf->LIEFERBASISPREIS = lbp;
			bufArt->HERST_PROZENT = herstproz;
		}
		else
			spBuf->GROSSO = spLIBuf->PRICE_PEXF;

		spBuf->AVP	  = spLIBuf->PRICE_PPUB;
		sprintf(spBuf->KE_MWST, "%d", spLIBuf->VAT); // -1 passiert bereits zpliartik
	}
	//else
	//	return 99; // Preise nicht übernehmen !
		
	spBuf->ARTIKEL_NR = spLIBuf->PHAR;
	spBuf->DATUMGUELTIGAB = spLIBuf->VDAT;	
	return 0;
}

/* ---- EAN --------------------- */
int TestEanNr( char *ean )
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
