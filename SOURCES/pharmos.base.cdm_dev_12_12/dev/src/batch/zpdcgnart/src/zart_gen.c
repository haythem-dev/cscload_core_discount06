#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <hdatum/phodate.h>

#include <voodoo_table_header/zdcart.h>
#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartaustria.h>
#include <voodoo_table_header/zartprei.h>
#include <voodoo_table_header/ccomgroupprop.h>
#include <voodoo_table_header/zartwg.h>
#include "znb_gen_dc.h"
#include "zart_gen.h"

#include <libscsvoodoo/libscsvoodoo.h>

/* ----- default vaulues for article fields ------- */
void InitArtikelFields( struct ZARTIKEL *zart, const char* const user )
{
   strcpy(zart->BEARBEITER, user );
   memset(zart->RABATTFAEHIG,'0',L_ZARTIKEL_RABATTFAEHIG); 
   strcpy(zart->ERSATZ_NR_AKTIV, VALUE_ZERO);
   strcpy(zart->PRIVATSORTIMENT, VALUE_NO);
   strcpy(zart->TAXPRUEFGROSSO, VALUE_ZERO);
   strcpy(zart->SONDERGROSSO, VALUE_BLANK);
   strcpy(zart->BESTANDSBUCHUNG, VALUE_ONE);   
   strcpy(zart->INDIKATOR, VALUE_ZERO);
   strcpy(zart->SKONTOFAEHIG, VALUE_ONE);   
   strcpy(zart->PREIS0ARTIKEL, VALUE_ZERO);
   strcpy(zart->MELDEPFL, VALUE_ZERO);
   strcpy(zart->MVDAARTIKEL, VALUE_ZERO);
   strcpy(zart->ZYTOSTATIKA, VALUE_ZERO);
   strcpy(zart->SICHTWAHL, VALUE_ZERO);
   strcpy(zart->RETOURENSPERRE, VALUE_ONE);
   strcpy(zart->ZENTR_EKSPERRE, VALUE_ZERO);
   strcpy(zart->ARTIKEL_GELOESCHT, VALUE_ZERO);
   strcpy(zart->SOMMER_KK, VALUE_ZERO);
   strcpy(zart->PRODUKTART, VALUE_ZERO);   
   strcpy(zart->BESTELLSPERRE, VALUE_ZERO);
   strcpy(zart->KATALOG, VALUE_BLANK);
   strcpy(zart->LABORARTIKEL, VALUE_ZERO);
   memset( zart->ZUZAHLUNG_IFA, '0', L_ZARTIKEL_ZUZAHLUNG_IFA );
   *zart->ZUZAHLUNG_IFA     = '0';
   strcpy(zart->ARTIKEL_GESPERRT, VALUE_ONE);   
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
   strcpy(zart->CHARGENARTIKEL, VALUE_ZERO);
}

/* ----- Default values for zartaustria fields ------- */
void InitZartaustriaFields( struct ZARTAUSTRIA *spZartAustria, const char* const user )
{
	strcpy(spZartAustria->WECHSELARTIKEL, VALUE_ZERO);
	strcpy(spZartAustria->BUENDELPACKUNG, VALUE_ZERO);
	strcpy(spZartAustria->NACHLIEFERUNG, VALUE_ZERO);
	strcpy(spZartAustria->CHARGENARTIKEL, VALUE_ZERO);
    memset( spZartAustria->OELHV_GRUPPE, ' ', L_ZARTAUSTRIA_OELHV_GRUPPE );
    memset( spZartAustria->OELHV_OEKOKZ, ' ', L_ZARTAUSTRIA_OELHV_OEKOKZ );
    memset( spZartAustria->OELHV_SORT, ' ', L_ZARTAUSTRIA_OELHV_SORT );
	strcpy(spZartAustria->HV_BOX, VALUE_ZERO);
	strcpy(spZartAustria->VERTRBIND_PLPL, VALUE_ZERO);
	strcpy(spZartAustria->VERTRBIND_S1S5, VALUE_ZERO);
	strcpy(spZartAustria->VERTRBIND_VPL, VALUE_ZERO);
	strcpy(spZartAustria->VERTRBIND_SP, VALUE_ZERO);
	strcpy(spZartAustria->VERTRBIND_COMPTANT, VALUE_BLANK);
	strcpy(spZartAustria->VERTRBIND_NEUFORM, VALUE_ZERO);
	strcpy(spZartAustria->NICHT_LIEFERBAR, VALUE_ZERO);
	strcpy(spZartAustria->NICHT_GELIEFERT, VALUE_ZERO);
}

/* No Changes from Datacare */ 
static int IsNotChanged( const struct ZDCART *dc, const int pos )  
{
   return NB_PL_NO_VAL == dc->NB_DC_PLAUSI[ pos ];
}

/* change 'J' to '1' and 'N' to '0' */ 
static void CpyNJ01Sign(char *art, const char *dc, const int iExistsArticle, const int isNotChanged )
{
    if ( strcmp( dc, "J" ) == 0 )
       strcpy(art,"1");
     else if ( strcmp( dc, "N" ) == 0 )
       strcpy(art,"0");
}

/* Functions for ZARTAUSTRIA */

static void Make_OELHV_SORT(  struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
	memset( spBuf->OELHV_SORT, ' ', L_ZARTAUSTRIA_OELHV_SORT );
	memcpy( spBuf->OELHV_SORT, spDCBuf->DC_OELHV_SORT, L_ZDCART_DC_OELHV_SORT );
	spBuf->OELHV_SORT[L_ZARTAUSTRIA_OELHV_SORT] = '\0';
}

static void Make_OELHV_OEKOKZ( struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
	memset( spBuf->OELHV_OEKOKZ, ' ', L_ZARTAUSTRIA_OELHV_OEKOKZ );
	memcpy( spBuf->OELHV_OEKOKZ, spDCBuf->DC_OELHV_OEKOKZ, L_ZDCART_DC_OELHV_OEKOKZ );
	spBuf->OELHV_OEKOKZ[L_ZARTAUSTRIA_OELHV_OEKOKZ] = '\0';
}
static void Make_OELHV_GRUPPE( struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
	memset( spBuf->OELHV_GRUPPE, ' ', L_ZARTAUSTRIA_OELHV_GRUPPE );
	memcpy( spBuf->OELHV_GRUPPE, spDCBuf->DC_OELHV_GRUPPE, L_ZDCART_DC_OELHV_GRUPPE );
	spBuf->OELHV_GRUPPE[L_ZARTAUSTRIA_OELHV_GRUPPE] = '\0';
}

static void Make_HV_BOX( struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
	memset( spBuf->HV_BOX, ' ', L_ZARTAUSTRIA_HV_BOX );
	memcpy( spBuf->HV_BOX, spDCBuf->DC_HV_BOX, L_ZDCART_DC_HV_BOX );
	spBuf->HV_BOX[L_ZARTAUSTRIA_HV_BOX] = '\0';
}
/* Artikel nicht verfügbar laut Warenverzeichnis */
static void Make_NV_WV( struct ZARTAUSTRIA *spBuf,  const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
  CpyNJ01Sign( spBuf->NICHT_LIEFERBAR, spDCBuf->DC_NV_WV, iExistsArticle,
              IsNotChanged( spDCBuf, PL_KZNVERFVERL ));
}
/* Artikel nicht verfügbar laut Großhandlesinformation */
static void Make_NV_GH (struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
  CpyNJ01Sign( spBuf->NICHT_GELIEFERT, spDCBuf->DC_NV_GH, iExistsArticle,
              IsNotChanged( spDCBuf, PL_KZNVERFGR ));
}

static void Make_DROGENAGS_KAT1 (struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
  CpyNJ01Sign( spBuf->DROGENAGS_KAT1, spDCBuf->DC_DROGENAGS_KAT1, iExistsArticle,
              IsNotChanged( spDCBuf, PL_DROGAGS_KAT1 ));
}

static void Make_DROGENAGS_KAT2 (struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
  CpyNJ01Sign( spBuf->DROGENAGS_KAT2, spDCBuf->DC_DROGENAGS_KAT2, iExistsArticle,
              IsNotChanged( spDCBuf, PL_DROGAGS_KAT2 ));
}

static void Make_DROGENAGS_KAT3 (struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
  CpyNJ01Sign( spBuf->DROGENAGS_KAT3, spDCBuf->DC_DROGENAGS_KAT3, iExistsArticle,
              IsNotChanged( spDCBuf, PL_DROGAGS_KAT3 ));
}

static void Make_SG_SUBSTANZ (struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
  CpyNJ01Sign( spBuf->SG_SUBSTANZ, spDCBuf->DC_SG_SUBSTANZ, iExistsArticle,
              IsNotChanged( spDCBuf, PL_SG_SUBSTANZ ));
}

static void Make_VERTRBIND_PLPL (struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
	if (strcmp(spDCBuf->DC_REZEPTZEICHEN,"++") == 0)
		spBuf->VERTRBIND_PLPL[0] = '1';
	else
		spBuf->VERTRBIND_PLPL[0] = '0';

	spBuf->VERTRBIND_PLPL[L_ZARTAUSTRIA_VERTRBIND_PLPL] = '\0';
}

static void Make_VERTRBIND_S1S5 (struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf)
{
	if ((strcmp(spDCBuf->DC_REZEPTZEICHEN,"S1") == 0) ||
		(strcmp(spDCBuf->DC_REZEPTZEICHEN,"S5") == 0))
		spBuf->VERTRBIND_S1S5[0] = '1';
	else
		spBuf->VERTRBIND_S1S5[0] = '0';

	spBuf->VERTRBIND_S1S5[L_ZARTAUSTRIA_VERTRBIND_S1S5] = '\0';
}

static void Make_VERTRBIND_COMPTANT (struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf, 
									 const struct ZARTIKEL *CZartBuf)
{
    /* (++ and (VT or VTW or VN or VNW) or P1 or P5 or P or T */
	if (((strcmp(spDCBuf->DC_REZEPTZEICHEN,"++") == 0) &&		
		((strcmp(spDCBuf->DC_KASSENZEICHEN,"VT") == 0) ||
		(strcmp(spDCBuf->DC_KASSENZEICHEN,"VTW") == 0) ||
		(strcmp(spDCBuf->DC_KASSENZEICHEN,"VN")  == 0) ||
		(strcmp(spDCBuf->DC_KASSENZEICHEN,"VNW") == 0))) ||	
	    (strcmp(spDCBuf->DC_REZEPTZEICHEN,"P1")  == 0) ||
	    (strcmp(spDCBuf->DC_REZEPTZEICHEN,"P5")  == 0) ||
	    //(strcmp(spDCBuf->DC_ABGABEBES,"P ")      == 0) ||
		spDCBuf->DC_ABGABEBES[0]				 == 'P' ||
	    //(strcmp(spDCBuf->DC_ABGABEBES," T")      == 0) ||
		spDCBuf->DC_ABGABEBES[1]				 == 'T' ||
		(strcmp(CZartBuf->REZEPTPFL,"1")		 == 0) )
	{
		spBuf->VERTRBIND_COMPTANT[0] = 'B';
	}
	
	spBuf->VERTRBIND_COMPTANT[L_ZARTAUSTRIA_VERTRBIND_COMPTANT] = '\0';
}

static void Make_WECHSELARTIKEL( struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf)
{
  /* --> Wechselartikel doesn´t exist anymore !!!
  if ((strcmp(spDCBuf->DC_MWST_GH,"1") == 0) && (strcmp(spDCBuf->DC_MWST_AP,"0") == 0))
	  spBuf->WECHSELARTIKEL[0] = '1';
  else*/ 
	  spBuf->WECHSELARTIKEL[0] = '0';
  
  spBuf->WECHSELARTIKEL[L_ZARTAUSTRIA_WECHSELARTIKEL] = '\0';
}

static void Make_NACHLIEFERUNG( struct ZARTAUSTRIA *spBuf, const struct ZARTIKEL *spZartBuf)
{
	if ( // (strcmp(spZartBuf->BTM, "1") == 0) ||  --> Mail von Fr. Samsinger (17.12.09): BTM´s sollen wafofähig sein.
		(strcmp(spZartBuf->NICHTUEBERGH, "1") == 0))
		spBuf->NACHLIEFERUNG[0] = '0';
	else 
		spBuf->NACHLIEFERUNG[0] = '1';
  
	spBuf->NACHLIEFERUNG[L_ZARTAUSTRIA_NACHLIEFERUNG] = '\0';
}

static void Make_VERTRBIND_SP(struct ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf)

{
	if (strcmp(spDCBuf->DC_ARTGRP_LTVERORD, " ") == 0 
	 || strcmp(spDCBuf->DC_ARTGRP_LTVERORD, "") == 0)
	{
		spBuf->VERTRBIND_SP[0] = '0';
		spBuf->VERTRBIND_SP[L_ZARTAUSTRIA_VERTRBIND_SP] = '\0';
	}

	if (strcmp(spDCBuf->DC_ARTGRP_LTVERORD, "X") != 0)
		return;

	spBuf->VERTRBIND_SP [0]= '1';
	spBuf->VERTRBIND_SP[L_ZARTAUSTRIA_VERTRBIND_SP] = '\0';
}

/*----- Functions for ZARTIKEL -----------------------------------------------*/


/* ------ attach discontinued date to article name ----- */
static void ChangeArtikelName( struct ZARTIKEL *spBuf, const int iMode )
{
    char szStr[12];

	/* deleted */
	if (( spBuf->DATUM_AH != 0 ) && (1 == iMode ))
    {
      ConvFromPhoDate( szStr, spBuf->DATUM_AH, "mmjj" );
      memcpy( &spBuf->ARTIKEL_NAME[26], szStr, 4 );
    }
	else /* reactivated */
	{
      memcpy( &spBuf->ARTIKEL_NAME[26], "    ", 4 );
	}
}

/* not by wholesaler */
static void Make_NICHTUEBERGH( struct ZARTIKEL *spBuf, const struct  ZDCART *spDCBuf,
                               int iExistsArticle )
{
	CpyNJ01Sign( spBuf->NICHTUEBERGH, spDCBuf->DC_NICHTUEBERGH, iExistsArticle,
              IsNotChanged( spDCBuf, PL_KZNGR ));
}

/*  includes codein */
static void Make_CODEIN( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
   CpyNJ01Sign( spBuf->MELDEPFL, spDCBuf->DC_CODEIN, iExistsArticle,
              IsNotChanged( spDCBuf, PL_KZCODEIN ));
}

/* only available in pharmacies */ 
static void Make_APOTHEKENPFL( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
   CpyNJ01Sign( spBuf->APOTHEKENPFL, spDCBuf->DC_APO_PFLICHTIG, iExistsArticle,
              IsNotChanged( spDCBuf, PL_KZAPOPFL ));
}

static void Make_OHNE_PREISBESCH( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
   CpyNJ01Sign( spBuf->SORTIMENT_1, spDCBuf->DC_OHNE_PREISBESCH, iExistsArticle,
              IsNotChanged( spDCBuf, PL_KZOHNEPRBESCH ));
}

static void Make_UN_NR( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)

{
	memset( spBuf->G_UN_NR, ' ', L_ZARTIKEL_G_UN_NR );
	memcpy( spBuf->G_UN_NR, spDCBuf->DC_UN_NR, L_ZDCART_DC_UN_NR  );
	spBuf->G_UN_NR[L_ZARTIKEL_G_UN_NR] = '\0';
}

static void Make_ZYTOSTATIKA( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
	CpyNJ01Sign( spBuf->ZYTOSTATIKA, spDCBuf->DC_ZYTOSTATIKUM, iExistsArticle,
              IsNotChanged( spDCBuf, PL_ZYTOSTATIKUM ));
}

static void Make_ARZNEIMITTEL( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
	CpyNJ01Sign( spBuf->ARZNEIMITTEL, spDCBuf->DC_ARZNEIMITTEL, iExistsArticle,
              IsNotChanged( spDCBuf, PL_ARZNEIMITTEL ));
}

static void Make_CHARGENARTIKEL( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
// SR-18029416: temporär ausgesetzt ...
// --> wieder aktiviert (21.01.19)
   CpyNJ01Sign( spBuf->CHARGENARTIKEL, spDCBuf->DC_CHARGE, iExistsArticle, IsNotChanged( spDCBuf, PL_CHARGE ));

   if (spBuf->CHARGENARTIKEL[0] == '0' && spDCBuf->DC_FAELSCHSICHER > 0)
	   strcpy(spBuf->CHARGENARTIKEL, "1");

   if (	( strncmp("01110", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01790", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("09110", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) )
   {
	   strcpy(spBuf->CHARGENARTIKEL, "1");
   }
}

static void Make_MEDIZINISCHE_GASE( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf,
                               int iExistsArticle )
{
   CpyNJ01Sign( spBuf->MEDIZINISCHE_GASE, spDCBuf->DC_MEDIZIN_GAS, iExistsArticle,
              IsNotChanged( spDCBuf, PL_MEDIZIN_GAS ));
}

static void Make_AWL( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
	if (( strncmp("01170", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01270", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01370", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01470", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01150", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01250", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01350", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01450", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01180", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01280", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01380", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		( strncmp("01480", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) )
	{
		spBuf->AWL1 = 50015;
		strcpy(spBuf->AWL_AKTIV, "J");
	}
	else if (	( strncmp("01110", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
				( strncmp("01790", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
				( strncmp("09110", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0)  )
	{
		spBuf->AWL1 = 50051;
		strcpy(spBuf->AWL_AKTIV, "J");
	}
	else if (	( strncmp("01740", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) != 0 ) &&
				( strncmp("J",	   spDCBuf->DC_NICHTUEBERGH, L_ZDCART_DC_NICHTUEBERGH) != 0 ) )
	{
		spBuf->AWL1 = 50052;
		strcpy(spBuf->AWL_AKTIV, "J");
	}

	// set in Make_KUEHLARTIKEL before !
	if ( (strcmp(spBuf->KUEHLARTIKEL ,VALUE_ONE ) == 0) ||
	     (strcmp(spBuf->KUEHLARTIKEL ,VALUE_FOUR ) == 0) )
	{
		spBuf->AWL1 = 50017;
		strcpy(spBuf->AWL_AKTIV, "J");
	}
}


/* Articlename */
static void Make_ARTIKEL_NAME( struct ZARTIKEL *spBuf,const  struct ZDCART *spDCBuf, const struct CCOMGROUPPROP *CComBuf, const int iExistsArticle)
{
	if ( iExistsArticle )
	{
		if ( IsNotChanged( spDCBuf, PL_ARTTXT ) ) return;
		if ( CComBuf->ADOPT_ABEZ_FROM_DC[0] != '1') return ;
	}

	memset( spBuf->ARTIKEL_NAME, ' ', L_ZARTIKEL_ARTIKEL_NAME );
	memcpy( spBuf->ARTIKEL_NAME, spDCBuf->DC_ARTIKELTEXT, L_ZDCART_DC_ARTIKELTEXT );
	spBuf->ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME] = '\0';
}

static char *spEinh_DC  = "G  GL M P ";
static char *spEinh_ART = "GRGRLTMTPK";
/*
G_ --> GR
L_ --> LT
M_ --> MT
P_ --> PK
alles andere --> ST
*/


static void NormiereEinheit( char *spStr, const char *spEinheit )
{
   int i;
   int iNormiert = 0;
   for ( i = 0; i < (int) strlen( spEinh_DC ); i += 2 )
   {
	 if ( memcmp( spEinheit, &spEinh_DC[i], 2 ) == 0 )
	 {
		 memcpy( spStr, &spEinh_ART[i], 2 );
		 return;
	 }
   }
   memcpy( spStr, spEinheit, 2 );

   if (spStr[1] == ' ')
		memcpy(spStr,"ST",2);

	
}

static int ShiftMenge( char *str, const char *menge )
{
   int lng;
   int anf = 0;
   int end;
   end = (int) strlen( menge ) - 1;
   while ( (end >= 0) && (menge[end] == ' ') ) end--;
   end++;
   while ( (anf < end) && (menge[anf] == ' ') ) anf++;
   lng = end - anf;
   if ( lng > 0 )
      memcpy( str, &menge[anf], lng );
   str[lng] = '\0';
   return lng;
}

void Build_EINHEIT( char *ArtEinheit,  const char *PgEinh,  const char *PgMeng )
{
   char str[20];
   char *pstr;
   int  maxlng;
   int  lng;
   int  pos;

   memset( ArtEinheit, ' ', L_ZARTIKEL_EINHEIT );
   ArtEinheit[L_ZARTIKEL_EINHEIT] = '\0';

 
   maxlng = L_ZARTIKEL_EINHEIT - 2;
   lng = ShiftMenge( str, PgMeng );
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

static void Make_EINHEIT( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf, 
                          const struct CCOMGROUPPROP *CComBuf, const int iExistsArticle)
{
	if ( iExistsArticle )
	{
		if ( CComBuf->ADOPT_EINH_FROM_DC[0] != '1') return ;

		if ( IsNotChanged( spDCBuf, PL_ARTEINHEIT ) && 
			IsNotChanged( spDCBuf, PL_ARTMENGE )     ) return; 
	}
	Build_EINHEIT( spBuf->EINHEIT, spDCBuf->DC_EINH_EINHEIT, spDCBuf->DC_EINH_MENGE );
}

/* Darreichungsform */
static void Make_DARREICHFORM( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf, 
                               const struct CCOMGROUPPROP *CComBuf, const int iExistsArticle)
{
	if ( iExistsArticle )	
		if ( CComBuf->ADOPT_DRFO_FROM_DC[0] != '1') 
			return ;

/* 16.01.2006  nicht setzen bei Zytostatika */
/* 24.06.2010  Abfrage auf Darreichform statt Kennzeichen */
	if ( iExistsArticle )	
/*		if ( spBuf->ZYTOSTATIKA[0] == '1' ) */
		if ( strncmp(spBuf->DARREICHFORM, "ZYT", L_ZARTIKEL_DARREICHFORM) == 0 ) 
			return;

	memset( spBuf->DARREICHFORM , ' ', L_ZARTIKEL_DARREICHFORM );
	memcpy( spBuf->DARREICHFORM, spDCBuf->DC_DARREICHFORM, L_ZDCART_DC_DARREICHFORM );

	/* PSY setzen */
	//if (strcmp(spDCBuf->DC_ABGABEBES, CDC_ABGABEBES_P) == 0)
	if (spDCBuf->DC_ABGABEBES[0] == 'P' )
	   memcpy(spBuf->DARREICHFORM, "PSY", 3);

	/* ZYT setzen */
	else if (strcmp(spDCBuf->DC_ZYTOSTATIKUM, VALUE_YES) == 0)
	   memcpy(spBuf->DARREICHFORM, "ZYT", 3);

	spBuf->DARREICHFORM[L_ZARTIKEL_DARREICHFORM] = '\0';
}

/* Rezeptpflichtig */
static void Make_REZEPTPFL( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
   if	((strcmp( spDCBuf->DC_REZEPTZEICHEN, CDC_REZEPTZEICHEN_PLUS ) == 0 ) ||
		(strcmp( spDCBuf->DC_REZEPTZEICHEN, CDC_REZEPTZEICHEN_PLUSPLUS ) == 0 ) ||
		(strcmp( spDCBuf->DC_REZEPTZEICHEN, CDC_REZEPTZEICHEN_S1 ) == 0 ) ||
		(strcmp( spDCBuf->DC_REZEPTZEICHEN, CDC_REZEPTZEICHEN_S5 ) == 0 ) ||
		(strcmp( spDCBuf->DC_REZEPTZEICHEN, CDC_REZEPTZEICHEN_SG ) == 0 )) 
		strcpy(spBuf->REZEPTPFL,"1");
   else
		strcpy(spBuf->REZEPTPFL,"0");
}

static void Make_BTM( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
	if (strcmp( spDCBuf->DC_REZEPTZEICHEN, CDC_REZEPTZEICHEN_SG ) == 0 )
		strcpy(spBuf->BTM,"1");
	else
		strcpy(spBuf->BTM,"0");
}

static void Make_PRODUKTART( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
	if (strcmp( spDCBuf->DC_GENERIKUM, "G" ) == 0 )
		strcpy(spBuf->PRODUKTART,"2");
	else
		strcpy(spBuf->PRODUKTART,"0");
}

static void Make_TIERARZNEI( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
	if (((strcmp( spDCBuf->DC_REZEPTZEICHEN, CDC_REZEPTZEICHEN_PLUS ) == 0 ) ||
			(strcmp( spDCBuf->DC_REZEPTZEICHEN, CDC_REZEPTZEICHEN_PLUSPLUS ) == 0 )) && 
	   ((strcmp( spDCBuf->DC_KASSENZEICHEN,CDC_KASSENZEICHEN_VT) == 0) ||
			(strcmp( spDCBuf->DC_KASSENZEICHEN, CDC_KASSENZEICHEN_VTW) == 0) ||
			(strcmp( spDCBuf->DC_KASSENZEICHEN, CDC_KASSENZEICHEN_VN) == 0) ||
			(strcmp( spDCBuf->DC_KASSENZEICHEN, CDC_KASSENZEICHEN_VNW) == 0)))
		strcpy(spBuf->TIERARZNEI,"1");
	else
		strcpy(spBuf->TIERARZNEI,"0");
}

static void Make_KUEHLARTIKEL( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
   if (strcmp(spDCBuf->DC_LAGERHINWEIS,CDC_LAGERHINWEIS_K ) == 0)
	   strcpy(spBuf->KUEHLARTIKEL, VALUE_ONE);
   else if (strcmp(spDCBuf->DC_LAGERHINWEIS,CDC_LAGERHINWEIS_E ) == 0)
	   strcpy(spBuf->KUEHLARTIKEL, VALUE_FOUR);
   else if (strcmp(spDCBuf->DC_LAGERHINWEIS,CDC_LAGERHINWEIS_T ) == 0)	
	   strcpy(spBuf->KUEHLARTIKEL, VALUE_FOUR);
   else if (strcmp(spDCBuf->DC_LAGERHINWEIS, CDC_LAGERHINWEIS_M) == 0)
	   strcpy(spBuf->KUEHLARTIKEL, VALUE_FIVE);
   else if (strcmp(spDCBuf->DC_LAGERHINWEIS, CDC_LAGERHINWEIS_U) == 0)
	   strcpy(spBuf->KUEHLARTIKEL, VALUE_SIX);
   else
	   strcpy(spBuf->KUEHLARTIKEL, VALUE_ZERO);
}

static void Make_SKONTOFAEHIG( struct ZARTIKEL *spBuf, const struct ZARTWG *spBufZdkWgr)
{
   char szSql[100];
   char sktof[2] = {0};

   if (strcmp(spBufZdkWgr->WARENGRUPPE, "     " ) == 0) // keine Warengruppe gesetzt
	   return;

   sprintf( szSql, "select wgr_sktof from zdkwgr where wgr_gruppe = '%s'", spBufZdkWgr->WARENGRUPPE);

   if ( SqlRead( szSql, sktof, NULL ) == 0 )
   {
		// Übernahme der Skontofähigkeit von Warengruppe auf Artikel
		if (sktof[0] == 'J')
			strcpy(spBuf->SKONTOFAEHIG, VALUE_ONE); 
		else
			strcpy(spBuf->SKONTOFAEHIG, VALUE_ZERO); 
   }
}

static void Make_RABATTFAEHIG( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf, const struct ZARTWG *spBufWg)
{
	if ((strcmp(spDCBuf->DC_REZEPTZEICHEN,CDC_REZEPTZEICHEN_SG) == 0) ||
		(strcmp(spDCBuf->DC_LAGERHINWEIS,CDC_LAGERHINWEIS_T)   == 0) ||
		(strcmp(spDCBuf->DC_LAGERHINWEIS,CDC_LAGERHINWEIS_E)   == 0) ||
		(strcmp(spDCBuf->DC_LAGERHINWEIS,CDC_LAGERHINWEIS_K)   == 0) ||
		(strncmp("02200", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		(strncmp("06200", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) ||
		(strncmp("IMP50", spBufWg->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) )
	{
		strcpy(spBuf->RABATTFAEHIG,"01");
	}
}

static void Make_TAXPFL(  struct ZARTIKEL *spBuf,const struct CCOMGROUPPROP *spComBuf)
{
	strcpy(spBuf->TAXPFL, spComBuf->TAX_GROUP );

	// Netto- Artikel ausschalten, wenn Tax-KZ gesetzt wird
	if (spBuf->TAXPFL[0] != '0' && spBuf->NETTOARTIKEL[0] == '1')
		strcpy(spBuf->NETTOARTIKEL,VALUE_ZERO); 
}

static void Make_VERFALL( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
	if ((strcmp(spDCBuf->DC_TAXKZ,"1")		== 0) ||
		(strcmp(spDCBuf->DC_TAXKZ,"2")		== 0) ||
		(strcmp(spDCBuf->DC_KZ_ABLAUF,"T")	== 0))
		 strcpy(spBuf->VERFALL,VALUE_ONE);
}

static void Make_PSYCHOTROP( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
	if (//(strcmp(spDCBuf->DC_ABGABEBES, "P") == 0) ||
		 spDCBuf->DC_ABGABEBES[0]		== 'P' ||
		(strcmp(spDCBuf->DC_REZEPTZEICHEN, "P1")  == 0) ||
		(strcmp(spDCBuf->DC_REZEPTZEICHEN, "PV")  == 0) ||
	    (strcmp(spDCBuf->DC_REZEPTZEICHEN, "P5")  == 0))
		spBuf->PSYCHOTROP[0] = 'P';
	else if ( spDCBuf->DC_ABGABEBES[1]	 == 'T' ) //(strcmp(spDCBuf->DC_ABGABEBES, " T") == 0)
		spBuf->PSYCHOTROP[0] = 'T';
	else
		spBuf->PSYCHOTROP[0] = 'N';

	spBuf->PSYCHOTROP[1] = '\0';
}

static void	Make_WIRKSTOFF( struct ZARTIKEL *Buf, const struct ZDCART *spDCBuf )
{
	if (strcmp(spDCBuf->DC_ARTIKELGRUPPE,"W") == 0)
		Buf->WIRKSTOFF = 1;
	else
		Buf->WIRKSTOFF = 0;
}

static void Make_NAHRUNGSTEST( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
	/* SR-19077822
	1.	Wenn die Datacare in Artikelgruppe = „L“ liefert, dann wird NEM-Artikel = „F“ gesetzt.
		unabhängig davon, welcher andere Wert aktuell in NEM-Artikel steht!
	2.	Wenn die Pharmos- Warengruppe = 02150 / 06160 ist, dann wird NEM-Artikel = „F“ gesetzt.
		unabhängig davon, welcher andere Wert aktuell in NEM-Artikel steht!
	3.	Wenn die Pharmos- Warengruppe = 02100 / 06100 ist und in dem Feld NEM-Artikel aktuell nicht „F" drinsteht, dann wird NEM-Artikel = „D“ gesetzt.
	4.	Wenn die Datacare in  Artikelgruppe = „N“ liefert  und in dem Feld NEM-Artikel aktuell „ " oder „D“ drinsteht, dann wird NEM-Artikel = „K“ gesetzt.
	5.	Wenn die Datacare in  Artikelgruppe = „ “ liefert  und in dem Feld NEM-Artikel aktuell „K" oder „D“ drinsteht, dann wird NEM-Artikel = „ “ gesetzt.
	*/

	if ( spDCBuf->DC_ARTIKELGRUPPE[0] == 'L'								||
		(strncmp("02150", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		(strncmp("06160", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0)	)
	{
		spBuf->NAHRUNGSTEST[0] = 'F';
	}
	else if ((strncmp("02100", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0)	|| 
			 (strncmp("06100", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0)	)
	{
		spBuf->NAHRUNGSTEST[0] = 'D';
	}
	else if (spDCBuf->DC_ARTIKELGRUPPE[0] == 'N'			&&
			 (spBuf->NAHRUNGSTEST[0] == 'D'					||
			  spBuf->NAHRUNGSTEST[0] == 'F'					||
			  spBuf->NAHRUNGSTEST[0] == ' '					))
	{
		  spBuf->NAHRUNGSTEST[0] = 'K';
	}
	else if (spDCBuf->DC_ARTIKELGRUPPE[0] == ' '			&&
			 (spBuf->NAHRUNGSTEST[0] == 'D'					||
			  spBuf->NAHRUNGSTEST[0] == 'F'					||
			  spBuf->NAHRUNGSTEST[0] == 'K'					))
	{
		  spBuf->NAHRUNGSTEST[0] = ' ';
	}

	spBuf->NAHRUNGSTEST[L_ZARTIKEL_NAHRUNGSTEST] = '\0';
}

static void Make_NAHRUNGSERGAENZUNG( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
	if ((strncmp("02200", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) || 
		(strncmp("06200", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0) )
	{
		spBuf->NAHRUNGSERGAENZUNG[0] = 'B';
	}

	spBuf->NAHRUNGSERGAENZUNG[L_ZARTIKEL_NAHRUNGSERGAENZUNG] = '\0';
}

static void Make_ZENTR_EKSPERRE( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
	if ((strncmp("01740", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0))
	{
		spBuf->ZENTR_EKSPERRE[0] = '1';
	}

	spBuf->ZENTR_EKSPERRE[L_ZARTIKEL_ZENTR_EKSPERRE] = '\0';
}

static void Make_MEDIZINPRODUKT(struct  ZARTAUSTRIA *spBuf, const struct ZDCART *spDCBuf)
{
    strcpy(spBuf->MEDPROD_ABG_VERORD,spDCBuf->DC_MEDPROD_ABGABEV);
	strcpy(spBuf->MEDPROD_KLASSE,  spDCBuf->DC_MEDPROD_KLASSE);
}

static void Make_GS(struct  ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
    int i, iEnd = 0;

	strcpy(spBuf->GS_LEICHTENTZ,VALUE_ZERO);
	strcpy(spBuf->GS_HOCHENTZ,VALUE_ZERO);
	strcpy(spBuf->GS_GIFTIG,VALUE_ZERO);
	strcpy(spBuf->GS_SEHRGIFTIG,VALUE_ZERO);
	strcpy(spBuf->GS_VORSLAGERN,VALUE_ZERO);
	strcpy(spBuf->GS_SVORSLAGERN,VALUE_ZERO);
	strcpy(spBuf->GS_GESUNDHSCH,VALUE_ZERO);
	strcpy(spBuf->GS_REIZEND,VALUE_ZERO);
	strcpy(spBuf->GS_EXPLOSION,VALUE_ZERO);
	strcpy(spBuf->GS_BRAND,VALUE_ZERO);
	strcpy(spBuf->GS_AETZEND,VALUE_ZERO);
	strcpy(spBuf->GS_UMWELT,VALUE_ZERO);

    for ( i = 0;i < L_ZDCART_DC_GEFAHRENSYMBOL;i++)
	{
		if ( i == (L_ZDCART_DC_GEFAHRENSYMBOL - 1))
			iEnd = 1;

		/* F or F+ */ 
		if (spDCBuf->DC_GEFAHRENSYMBOL[i] == 'F')
		{
			if (iEnd )
				strcpy(spBuf->GS_LEICHTENTZ,VALUE_ONE);
			else if (spDCBuf->DC_GEFAHRENSYMBOL[i+1] == '+')
				strcpy(spBuf->GS_HOCHENTZ,VALUE_ONE);
			else
				strcpy(spBuf->GS_LEICHTENTZ,VALUE_ONE);
		}
		/* T or T+ */ 
		if (spDCBuf->DC_GEFAHRENSYMBOL[i] == 'T')
		{
			if (iEnd )
				strcpy(spBuf->GS_GIFTIG,VALUE_ONE);
			else if (spDCBuf->DC_GEFAHRENSYMBOL[i+1] == '+')
				strcpy(spBuf->GS_SEHRGIFTIG,VALUE_ONE);
			else
				strcpy(spBuf->GS_GIFTIG,VALUE_ONE);
		}

		/* V or SV */ 
		if (spDCBuf->DC_GEFAHRENSYMBOL[i] == 'V')
		{
			if ( 0 == i )
				strcpy(spBuf->GS_VORSLAGERN,VALUE_ONE);
			else if (spDCBuf->DC_GEFAHRENSYMBOL[i-1] == 'S')
				strcpy(spBuf->GS_SVORSLAGERN,VALUE_ONE);
			else
				strcpy(spBuf->GS_VORSLAGERN,VALUE_ONE);
		}
		/* Xn or Xi */ 
		if (spDCBuf->DC_GEFAHRENSYMBOL[i] == 'X')
		{
			if ( iEnd )
			{
			}
			else if (spDCBuf->DC_GEFAHRENSYMBOL[i+1] == 'n')
				strcpy(spBuf->GS_GESUNDHSCH,VALUE_ONE);
			else if (spDCBuf->DC_GEFAHRENSYMBOL[i+1] == 'i')
				strcpy(spBuf->GS_REIZEND,VALUE_ONE);
		}
		/* E */
		if (spDCBuf->DC_GEFAHRENSYMBOL[i] == 'E')
			strcpy(spBuf->GS_EXPLOSION,VALUE_ONE);
		/* O */
		if (spDCBuf->DC_GEFAHRENSYMBOL[i] == 'O')
			strcpy(spBuf->GS_BRAND,VALUE_ONE);
		/* C */
		if (spDCBuf->DC_GEFAHRENSYMBOL[i] == 'C')

			strcpy(spBuf->GS_AETZEND,VALUE_ONE);
		/* N */
		if (spDCBuf->DC_GEFAHRENSYMBOL[i] == 'N')
			strcpy(spBuf->GS_UMWELT,VALUE_ONE);
	} /* endfor */
}

static int IsKeineAngabe_Blank( char *spDc )
{
   while ( *spDc && *spDc == ' ' ) spDc++;
   return !(*spDc);
}

static void Make_LAENGE( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
   spBuf->LAENGE  = spDCBuf->DC_TIEFE;
}

static void Make_BREITE( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf )
{
   spBuf->BREITE  = spDCBuf->DC_BREITE;
}

static void Make_HOEHE( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
   spBuf->HOEHE  = spDCBuf->DC_HOEHE;
}

static void Make_GEWICHT( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
   spBuf->GEWICHT  = spDCBuf->DC_GEWICHT;
}


static void Make_ARTIKEL_NR_HERST( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf, const struct CCOMGROUPPROP *CComBuf,
								   int iExistsArticle )
{
	if ( CComBuf->ADOPT_ANRH_FROM_DC[0] != '1') return ;

	memcpy( spBuf->ARTIKEL_NR_HERST, spDCBuf->DC_ARTNR_LIEFERANT, L_ZARTIKEL_ARTIKEL_NR_HERST );
	spBuf->ARTIKEL_NR_HERST[L_ZARTIKEL_ARTIKEL_NR_HERST] = '\0';
}

static void Make_WGR2(struct ZARTWG *spBuf, const struct ZDCART *spDCBuf)
{
	memcpy( spBuf->WARENGRUPPE, spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE );
	spBuf->WARENGRUPPE[L_ZARTWG_WARENGRUPPE] = '\0';
}

static void Make_WGR4(struct ZARTWG *spBuf, const struct ZDCART *spDCBuf)
{
	memcpy( spBuf->WARENGRUPPE, spDCBuf->DC_CODE_LIEFERANT, L_ZARTWG_WARENGRUPPE );
	spBuf->WARENGRUPPE[L_ZARTWG_WARENGRUPPE] = '\0';
}

static void Make_BIOSIEGEL( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf, int existsArticle )
{
	spBuf->BIOSIEGEL = spDCBuf->DC_BIOSIEGEL;
}

static void Make_ANTIBIOTIKUM( struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf, int existsArticle )
{
	spBuf->ANTIBIOTIKUM = spDCBuf->DC_ANTIBIOTIKUM;
}

static void Make_SERIAL_NUMBER_TRACKING(struct ZARTIKEL *spBuf, const struct ZDCART *spDCBuf)
{
	if (spDCBuf->DC_MEDPROD_KLASSE[0] == 'K')
	{
		spBuf->SERIAL_NUMBER_TRACKING = 1;
	}
}


static void CpyMwst( char *art, const char *spDCBuf, int iExistsArticle )
{
	strcpy( art, spDCBuf );
}

/* datacare status flags */ 

 /* ---- deleted by Datacare----- */
int GetIsDCDeleted( const struct ZDCART *spDCBuf )
{
    return !IsNotChanged( spDCBuf, PL_AENDERCODE )  && *spDCBuf->DC_AECODE   == 'L';
}

 /* ---- reactivated by Datacare----- */
int GetIsDCReactivated( const struct ZDCART *spDCBuf )
{
    return !IsNotChanged( spDCBuf, PL_AENDERCODE )  && *spDCBuf->DC_AECODE   == 'R';
}

/* ---- Datacare-AH ---- */
int GetIsDCAH( const struct ZDCART *spDCBuf )
{
	return !IsNotChanged( spDCBuf, PL_AENDERCODE )  && *spDCBuf->DC_AECODE   == 'A';
}

/* datacare status flags end */ 

/* Übernahme Datacare auf Zartaustria */
void DCSatzToArtikelAustria(const struct ZDCART *spDCBuf, struct ZARTAUSTRIA *spBuf, 
							struct ZARTIKEL *CZartBuf, int iExistsArticle )
{
   /* Artikel-Nr */
   spBuf->ARTIKEL_NR = spDCBuf->DC_ARTIKEL_NR;

   /* Ökonomieliste Sortierung */
   Make_OELHV_SORT(spBuf,spDCBuf,iExistsArticle);

   /* Ökonomieliste Gruppe */
   Make_OELHV_GRUPPE(spBuf,spDCBuf,iExistsArticle);

   /* Ökonomieliste Kennzeichen */
   Make_OELHV_OEKOKZ(spBuf,spDCBuf,iExistsArticle);

   /* HV-Box */
   Make_HV_BOX(spBuf,spDCBuf,iExistsArticle);

   Make_NV_WV(spBuf,spDCBuf,iExistsArticle);

   Make_NV_GH(spBuf,spDCBuf,iExistsArticle);

   Make_VERTRBIND_PLPL(spBuf,spDCBuf,iExistsArticle);

   Make_VERTRBIND_S1S5(spBuf,spDCBuf);

   Make_VERTRBIND_COMPTANT(spBuf,spDCBuf,CZartBuf);

   Make_VERTRBIND_SP(spBuf, spDCBuf);

   Make_WECHSELARTIKEL(spBuf, spDCBuf);

   Make_MEDIZINPRODUKT(spBuf, spDCBuf);

   /* New Article ? */
   if ( !iExistsArticle )
   {
		Make_NACHLIEFERUNG(spBuf, CZartBuf);
   }
   
   if ((strncmp("01740", spDCBuf->WARENGRUPPE, L_ZARTWG_WARENGRUPPE) == 0))
	   strcpy(spBuf->NACHLIEFERUNG, "0");

	Make_DROGENAGS_KAT1(spBuf,spDCBuf,iExistsArticle);
	Make_DROGENAGS_KAT2(spBuf,spDCBuf,iExistsArticle);
	Make_DROGENAGS_KAT3(spBuf,spDCBuf,iExistsArticle);
	Make_SG_SUBSTANZ(spBuf,spDCBuf,iExistsArticle);

	// wenn "J", dann auch zartikel->MELDEPFL auf "1"
	if (strcmp(spDCBuf->DC_SG_SUBSTANZ, "J") == 0)
		strcpy(CZartBuf->MELDEPFL, "1");
}

void DCSatzToArtWgr2( const struct ZDCART *spDCBuf, struct ZARTWG *spBuf)
{
	Make_WGR2(spBuf,spDCBuf);
}
void DCSatzToArtWgr4( const struct ZDCART *spDCBuf, struct ZARTWG *spBuf)
{
	Make_WGR4(spBuf,spDCBuf);
}                       

/* Übernahme Datacare auf Zartikel*/
void DCSatzToArtikel( const struct ZDCART *spDCBuf, struct ZARTIKEL *spBuf, const struct CCOMGROUPPROP *CComBuf,
                       int iExistsArticle, const struct ZARTWG *spBufWg, const struct ZARTWG *spBufZdkWgr )
{
   long datum_gueltig;
   long datum_ah;

   spBuf->ARTIKEL_NR = spDCBuf->DC_ARTIKEL_NR;
   datum_gueltig = spDCBuf->DC_DATUMGUELTIGAB;
   spBuf->DATUM_IFAAENDER = datum_gueltig;

   spBuf->HERSTELLER_NR = spDCBuf->HERSTELLER_NR;   
   Make_NICHTUEBERGH(spBuf,spDCBuf,iExistsArticle);
   Make_CODEIN(spBuf,spDCBuf,iExistsArticle);
   Make_APOTHEKENPFL(spBuf,spDCBuf,iExistsArticle);
   Make_OHNE_PREISBESCH(spBuf,spDCBuf,iExistsArticle);
   Make_UN_NR(spBuf,spDCBuf);
   Make_ARTIKEL_NAME( spBuf, spDCBuf, CComBuf, iExistsArticle );
   Make_EINHEIT( spBuf, spDCBuf, CComBuf, iExistsArticle);
   Make_DARREICHFORM( spBuf, spDCBuf, CComBuf, iExistsArticle);
   Make_ARTIKEL_NR_HERST( spBuf, spDCBuf, CComBuf, iExistsArticle );
   Make_REZEPTPFL( spBuf, spDCBuf );
   Make_BTM( spBuf, spDCBuf );
   Make_TIERARZNEI( spBuf, spDCBuf);
   Make_KUEHLARTIKEL(spBuf, spDCBuf);
   Make_RABATTFAEHIG(spBuf, spDCBuf, spBufWg);
   Make_SKONTOFAEHIG(spBuf, spBufZdkWgr);
   Make_VERFALL(spBuf, spDCBuf);
   Make_TAXPFL(spBuf,CComBuf);
   
   Make_PSYCHOTROP(spBuf,spDCBuf);
   Make_NAHRUNGSTEST(spBuf,spDCBuf);
   Make_WIRKSTOFF(spBuf,spDCBuf);
   
   Make_NAHRUNGSERGAENZUNG(spBuf,spDCBuf);
   Make_ZENTR_EKSPERRE(spBuf,spDCBuf);

   Make_PRODUKTART(spBuf,spDCBuf);
   Make_ZYTOSTATIKA(spBuf,spDCBuf,iExistsArticle);
   Make_ARZNEIMITTEL(spBuf,spDCBuf,iExistsArticle);
   Make_CHARGENARTIKEL(spBuf,spDCBuf,iExistsArticle);
   Make_MEDIZINISCHE_GASE(spBuf,spDCBuf,iExistsArticle);

   Make_BIOSIEGEL( spBuf, spDCBuf, iExistsArticle);
   Make_ANTIBIOTIKUM( spBuf, spDCBuf, iExistsArticle);
   Make_SERIAL_NUMBER_TRACKING(spBuf, spDCBuf);

	// 21.11.05 Bei Warengruppe 01720 oder 01730 Verfall auf 1 setzen
	if (( strncmp("01720",spDCBuf->WARENGRUPPE,L_ZARTWG_WARENGRUPPE) == 0) ||
		( strncmp("01780",spDCBuf->WARENGRUPPE,L_ZARTWG_WARENGRUPPE) == 0) ||
		( strncmp("01740",spDCBuf->WARENGRUPPE,L_ZARTWG_WARENGRUPPE) == 0) ||
		( strncmp("01730",spDCBuf->WARENGRUPPE,L_ZARTWG_WARENGRUPPE) == 0))
		strcpy(spBuf->VERFALL, VALUE_ONE);

   /* New Article ? */
   if ( !iExistsArticle )
   {
	    Make_GS( spBuf, spDCBuf );
		Make_LAENGE( spBuf, spDCBuf );
		Make_BREITE( spBuf, spDCBuf);
		Make_HOEHE( spBuf, spDCBuf );
		Make_GEWICHT( spBuf, spDCBuf);
        spBuf->DATUM_ANLAGE = datum_gueltig;
		
		if (spBuf->TAXPFL[0] == '0')
			strcpy(spBuf->NETTOARTIKEL,VALUE_ONE); 
		else 
			strcpy(spBuf->NETTOARTIKEL,VALUE_ZERO); 
	
		Make_AWL( spBuf, spDCBuf);
   }

   datum_ah = 0;
   spBuf->DATUM_RR = 0;
   spBuf->DATUM_IFALOESCH = 0;

   if ( GetIsDCAH( spDCBuf ) )
      datum_ah = datum_gueltig;
   else
      datum_ah = 0;

   if ( iExistsArticle )
   {
      if ( spBuf->DATUM_AH == 0 && datum_ah > 0 )
      {
          /* strcpy( Buf->RETOURENSPERRE, "1" ); */ 
          spBuf->DATUM_AH = datum_ah;
      }
   }
   else
   {
   /*   if ( datum_ah > 0 )
          strcpy( Buf->RETOURENSPERRE, "1" ); */
      spBuf->DATUM_AH = datum_ah;
   }

   /* Deleted */
   if ( GetIsDCDeleted( spDCBuf ) )
   {
      spBuf->DATUM_IFALOESCH = datum_gueltig;
	  spBuf->DATUM_AV = datum_gueltig;
	  spBuf->DATUM_RR = datum_gueltig;
	  spBuf->ARTIKEL_GELOESCHT[0] = '1';
	  ChangeArtikelName( spBuf, 1 );
   }
   else
      spBuf->DATUM_IFALOESCH = 0;  

   /* reactivated */
   if (GetIsDCReactivated( spDCBuf ))
   {
	   spBuf->DATUM_AH = 0;
	   ChangeArtikelName( spBuf, 0 );
   }
  
}

/* ---- Preise --------------------- */

int IsPreisChanged( struct ZDCART *spDCBuf )
{
	if ( !IsNotChanged( spDCBuf, PL_GEP ) ||
        !IsNotChanged( spDCBuf, PL_AEP ) ||
        !IsNotChanged( spDCBuf, PL_AVP ) ||
        !IsNotChanged( spDCBuf, PL_MWSTCODEGR ) )    /* Mwst */
        return 1;
	else
        return 0;
}

void DCSatzToPreis( const struct ZDCART *spDCBuf, struct ZARTPREIS *spBuf, const struct CCOMGROUPPROP *CComBuf,
                     int iExistsArticle )
{
	if ( !iExistsArticle)
	{
		spBuf->AEP    = spDCBuf->DC_AEP;
		spBuf->GROSSO = spDCBuf->DC_GEP;
		spBuf->AVP	  = spDCBuf->DC_AVP;
	}

	spBuf->ARTIKEL_NR = spDCBuf->DC_ARTIKEL_NR;
	spBuf->DATUMGUELTIGAB = spDCBuf->DC_DATUMGUELTIGAB;	

	if ( CComBuf->ADOPT_AEP_FROM_DC[0] == '1') 
		spBuf->AEP    = spDCBuf->DC_AEP;

	if ( CComBuf->ADOPT_GEP_FROM_DC[0] == '1') 
		spBuf->GROSSO = spDCBuf->DC_GEP;

	if ( CComBuf->ADOPT_AVP_FROM_DC[0] == '1') 
		spBuf->AVP = spDCBuf->DC_AVP;

   //Buf->EAVP   = DCBuf->EAVP;
   
   CpyMwst( spBuf->KE_MWST, spDCBuf->DC_MWST_GH, iExistsArticle );
}
