/* ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die Datacare-Artikeldatei ein und integriert    *
 *                  die Saetze in den lokalen UPDATE-POOL                 *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 26.01.2005                                            *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include <hdatum/phodate.h>

/* --------------------------- */
#include <eklibs/ifalib/ifa_stat.h>
#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_dbas.h>

#include <voodoo_table_header/zdcart.h>
#include <voodoo_table_header/zdcoart.h>

#include "dc_form.h"
#include "g_dcoart.h" 
#include "sql_zdcart.h"
#include "znb_gen_dc.h"
#include "check_plausi.h"
#include "zpreitst.h"
#include "l_taxtab.h"
#include "g_dcartik.h"

/* --- Prototype  ------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld );
void CloseBase( void );

/* ------------------- Globale Variablen ------------------------ */
static long dcdatumnr;
static long satznr;
static long satznr_prev;
static long linenr;
static long nofilesets;
static long art_ohne_pznneu;
static long art_mit_pznneu;
static long pzn_previous;
static long datgueltab_prev;
static long grenzeHochpreis;

static long anz_upd;
static long anz_del;
static long anz_ins;
static long anz_noact;

static struct ZDCART dc;
static struct ZDCOART dco;

static char pzn_double [28] = "ARTIKEL DOPPELT IN DC-FILE";
static char pzn_error  [28] = "PZN-PRUEFZIFFER FALSCH";

static char adoptgep;
static char adoptaep;
static char adoptavp;
static char adoptbez;

static char taxkz_ccomgroupprop;

/* --------  user -------------- */
static const char* const user = "dc     "  ;


/* --- Preise nach long --- */
static long GetDCPreisLong( double preis )
{
  return (long)( preis*100.0 + 0.1 );
}

static long GetPhosixPreisLong( double preis )
{
  return (long)( preis*100.0 + 0.1 );
}

static long GetPhosixProzent( double proz )
{
   if ( proz >= 0.005 )
    return (long)( proz*100.0 + 0.1 );
   else if ( proz <= -0.005 )
    return (long)( proz*100.0 - 0.1 );
   else
    return 0;
}

/* ------------------------------------------------------------------- */
static void LineToDCStruct (struct ZDCART* dc, char* line, char *errmld)
{
	char TmpNumeric[16];
	memset(TmpNumeric, '\0', 11);
		
	dc->DCNR = dcdatumnr;
	
	strncpy(TmpNumeric, &line[P_PZN], L_PZN);
		dc->DC_ARTIKEL_NR = atol( TmpNumeric );
		memset(TmpNumeric, '\0', 11);
	strncpy(dc->DC_ARTIKELKURZTEXT, &line[P_ARTKURZTXT], L_ARTKURZTXT);
	strncpy(dc->DC_ARTIKELTEXT, &line[P_ARTTXT], L_ARTTXT);
	strncpy(dc->DC_EINH_MENGE, &line[P_ARTMENGE], L_ARTMENGE);
	strncpy(dc->DC_EINH_EINHEIT, &line[P_ARTEINHEIT], L_ARTEINHEIT);
	strncpy(dc->DC_TAXKZ, &line[P_KZTAXE], L_KZTAXE);
	strncpy(dc->DC_ARTIKELKZ, &line[P_KZAPOVERL], L_KZAPOVERL);
	strncpy(dc->DC_REZEPTZEICHEN, &line[P_ZREZEPT], L_ZREZEPT);
	strncpy(dc->DC_KASSENZEICHEN, &line[P_ZKASSE], L_ZKASSE);
	strncpy(dc->DC_KASSENZ_ZUSATZ, &line[P_ZKASSEZUS], L_ZKASSEZUS);
	strncpy(dc->DC_CODEIN, &line[P_KZCODEIN], L_KZCODEIN);
	strncpy(TmpNumeric, &line[P_GEP], L_GEP);
		dc->DC_GEP = atof( TmpNumeric ) / 100;
		KaufmRunden ( &(dc->DC_GEP) , 2 );
		memset(TmpNumeric, '\0', 11);
	strncpy(TmpNumeric, &line[P_AEP], L_AEP);
		dc->DC_AEP = atof( TmpNumeric ) / 100;
		KaufmRunden ( &(dc->DC_AEP) , 2 );
		memset(TmpNumeric, '\0', 11);
	strncpy(TmpNumeric, &line[P_KKP], L_KKP);
		dc->DC_KKP = atof( TmpNumeric ) / 100;
		KaufmRunden ( &(dc->DC_KKP) , 2 );
		memset(TmpNumeric, '\0', 11);
	strncpy(TmpNumeric, &line[P_AVP], L_AVP);
		dc->DC_AVP = atof( TmpNumeric ) / 100;
		KaufmRunden ( &(dc->DC_AVP) , 2 );
		memset(TmpNumeric, '\0', 11);
	strncpy(dc->DC_OHNE_PREISBESCH, &line[P_KZOHNEPRBESCH], L_KZOHNEPRBESCH);
	strncpy(dc->DC_MWST_GH, &line[P_MWSTCODEGR], L_MWSTCODEGR);
	strncpy(dc->DC_MWST_AP, &line[P_MWSTCODEAPO], L_MWSTCODEAPO);
	strncpy(dc->DC_CHARGE, &line[P_CHARGE], L_CHARGE);
	strncpy(TmpNumeric, &line[P_FAELSCHSICHER], L_FAELSCHSICHER );
		dc->DC_FAELSCHSICHER = atoi(TmpNumeric);
		memset(TmpNumeric, '\0', 11 );
	strncpy(TmpNumeric, &line[P_BIOSIEGEL], L_BIOSIEGEL );
		dc->DC_BIOSIEGEL = atoi(TmpNumeric);
		memset(TmpNumeric, '\0', 11 );
	strncpy(TmpNumeric, &line[P_ANTIBIOTIKUM], L_ANTIBIOTIKUM );
		dc->DC_ANTIBIOTIKUM = atoi(TmpNumeric);
		memset(TmpNumeric, '\0', 11 );
	strncpy(dc->DC_VERM_REZ_GEB, &line[P_KZVERMREZGEB], L_KZVERMREZGEB);
	strncpy(dc->DC_CODE_LIEFERANT, &line[P_LIEFERANT], L_LIEFERANT);
	strncpy(dc->DC_ARTNR_LIEFERANT, &line[P_LIEFARTNR], L_LIEFARTNR);
	strncpy(dc->DC_DEFEKTUR_LISTE, &line[P_DEFEKTUR], L_DEFEKTUR);
	strncpy(TmpNumeric, &line[P_MINDABN], L_MINDABN);
		dc->DC_MINDESTABNAHME = atoi(TmpNumeric);
		memset(TmpNumeric, '\0', 11);
	strncpy(dc->DC_NV_WV, &line[P_KZNVERFVERL], L_KZNVERFVERL);
	strncpy(dc->DC_NV_GH, &line[P_KZNVERFGR], L_KZNVERFGR);
	strncpy(TmpNumeric, &line[P_HOEHE], L_HOEHE);
		dc->DC_HOEHE = atoi(TmpNumeric);
		memset(TmpNumeric, '\0', 11);
	strncpy(TmpNumeric, &line[P_BREITE], L_BREITE);
		dc->DC_BREITE = atoi(TmpNumeric);
		memset(TmpNumeric, '\0', 11);
	strncpy(TmpNumeric, &line[P_TIEFE], L_TIEFE);
		dc->DC_TIEFE = atoi(TmpNumeric);
		memset(TmpNumeric, '\0', 11);
	strncpy(dc->DC_LAGERHINWEIS, &line[P_LAGERHINW], L_LAGERHINW);
	strncpy(dc->DC_GEFAHRENSYMBOL, &line[P_GEFAHRHINW], L_GEFAHRHINW);
	strncpy(dc->DC_KZ_ABLAUF, &line[P_KZABLAUF], L_KZABLAUF);
	strncpy(dc->DC_APO_PFLICHTIG, &line[P_KZAPOPFL], L_KZAPOPFL);
	strncpy(dc->DC_REGISTER_NR, &line[P_REGNR], L_REGNR);
	strncpy(dc->DC_THERAPIEGRUPPE, &line[P_THERAPIEGRP], L_THERAPIEGRP);
	strncpy(dc->DC_ARTIKELGRUPPE, &line[P_ARTGRP], L_ARTGRP);
	strncpy(dc->DC_MINIK_BASISS, &line[P_KZMINIBASIS], L_KZMINIBASIS);
	strncpy(dc->DC_AECODE, &line[P_AENDERCODE], L_AENDERCODE);
	strncpy(dc->DC_CODE_HERSTELLER, &line[P_HERSTCODE], L_HERSTCODE);
	strncpy(TmpNumeric, &line[P_GEWICHT], L_GEWICHT);
		dc->DC_GEWICHT = atol(TmpNumeric);
		memset(TmpNumeric, '\0', 11);

/*	strncpy(dc->DC_OELHV_GRUPPE, &line[P_GRPHERSTOEKO], L_GRPHERSTOEKO); 
	strncpy(dc->DC_OELHV_OEKOKZ, &line[P_KZOEKO], L_KZOEKO); */
	strncpy(dc->DC_GENERIKUM, &line[P_GENERIKUM], L_GENERIKUM);
	strncpy(dc->DC_ORIGINALPRODUKT, &line[P_ORIGINALPROD], L_ORIGINALPROD);
	strncpy(dc->DC_ARZNEIMITTEL, &line[P_ARZNEIMITTEL], L_ARZNEIMITTEL);
	strncpy(dc->DC_ABGRENZ_VERORD, &line[P_ABGR_VERORD], L_ABGR_VERORD);
	strncpy(dc->DC_SG_ZUBEREITUNG, &line[P_SG_ZUBEREIT], L_SG_ZUBEREIT);
	strncpy(dc->DC_SG_SUBSTANZ, &line[P_SG_SUBSTANZ], L_SG_SUBSTANZ);
	
	strncpy(dc->DC_ABGABEBES, &line[P_KZ_ABGBESCHR], L_KZ_ABGBESCHR);
	strncpy(dc->DC_VERKEHRSFAEHIG, &line[P_KZVERKEHR], L_KZVERKEHR);
	strncpy(TmpNumeric, &line[P_KKPHAUSAPO], L_KKPHAUSAPO);
		dc->DC_KKP_HAUSAPO = atof(TmpNumeric) / 100;
		KaufmRunden ( &(dc->DC_KKP_HAUSAPO) , 2 );
		memset(TmpNumeric, '\0', 11);
	strncpy(dc->DC_HERKUNFTSLAND, &line[P_HERKUNFT], L_HERKUNFT);

/*	strncpy(dc->DC_OELHV_SORT, &line[P_SORTINGRP], L_SORTINGRP); */
	strncpy(dc->DC_DROGENAGS_KAT1, &line[P_DROGAGSKAT1], L_DROGAGSKAT1);
	strncpy(dc->DC_DROGENAGS_KAT2, &line[P_DROGAGSKAT2], L_DROGAGSKAT2);
	strncpy(dc->DC_DROGENAGS_KAT3, &line[P_DROGAGSKAT3], L_DROGAGSKAT3);
	strncpy(dc->DC_BLUTKONSERVE, &line[P_BLUTKONSERVE], L_BLUTKONSERVE);	
	
	strncpy(dc->DC_HV_BOX, &line[P_BOXERSTATT], L_BOXERSTATT);
	strncpy(dc->DC_DARREICHFORM, &line[P_DAR], L_DAR);
	strncpy(TmpNumeric, &line[P_DATERSTANL], L_DATERSTANL);
		dc->DC_DATUM_ANLAGE = atol(TmpNumeric);
		memset(TmpNumeric, '\0', 11);
	strncpy(TmpNumeric, &line[P_DATLETZTAEND], L_DATLETZTAEND);
		dc->DC_DATUM_AENDER = atol(TmpNumeric);
		memset(TmpNumeric, '\0', 11);
	strncpy(TmpNumeric, &line[P_DATGUELTAB], L_DATGUELTAB);
		dc->DC_DATUMGUELTIGAB = atol(TmpNumeric);
		memset(TmpNumeric, '\0', 11);
	strncpy(TmpNumeric, &line[P_AUSLIEFVERS], L_AUSLIEFVERS);
		dc->DC_LFD_NR = atol(TmpNumeric);
		memset(TmpNumeric, '\0', 11);
	strncpy(dc->DC_NEUANLEGER, &line[P_NEUANLEGER], L_NEUANLEGER);

/*	strncpy(dc->DC_PARTNER, &line[P_PARTNERNR], L_PARTNERNR);
	strncpy(dc->DC_REFERENZ_NR, &line[P_REFERENZNR], L_REFERENZNR); */
	strncpy(dc->DC_RADIOAKT_ARZNEI, &line[P_RAD_AKT_ARZ], L_RAD_AKT_ARZ);
	strncpy(dc->DC_FUETTER_ARZNEI, &line[P_FUETTERARZ], L_FUETTERARZ);
	strncpy(dc->DC_ARZNEI_GEWERBE, &line[P_ARZ_GEWERBE], L_ARZ_GEWERBE);
	strncpy(dc->DC_DENTALARZNEI, &line[P_DENTALARZ], L_DENTALARZ);
	strncpy(dc->DC_MEDIZIN_GAS, &line[P_MEDIZINGAS], L_MEDIZINGAS);
	strncpy(dc->DC_KONTAKTLINSENFL, &line[P_KONTAKTLINSE], L_KONTAKTLINSE);
	strncpy(dc->DC_ALK_UNVERST, &line[P_ALK_UNVERST], L_ALK_UNVERST);
	strncpy(dc->DC_ALK_VERGAELLT, &line[P_ALK_VERGAELLT], L_ALK_VERGAELLT);
	strncpy(dc->DC_GIFT, &line[P_GIFT], L_GIFT);
	strncpy(dc->DC_ZYTOSTATIKUM, &line[P_ZYTOSTATIKUM], L_ZYTOSTATIKUM);

	strncpy(dc->DC_PFLANZENSCHUTZ, &line[P_PFLANZENSCH], L_PFLANZENSCH);
	strncpy(dc->DC_MEDPROD_ABGABEV, &line[P_MEDPROD_ABGVO], L_MEDPROD_ABGVO);
	strncpy(dc->DC_MEDPROD_KLASSE, &line[P_MEDPROD_KLASS], L_MEDPROD_KLASS);
	strncpy(dc->DC_ARTGRP_LTVERORD, &line[P_ARTGRP_LTVO], L_ARTGRP_LTVO);

	strncpy(dc->DC_NICHTUEBERGH, &line[P_KZNGR], L_KZNGR);
	strncpy(dc->DC_WARENGRUPPE, &line[P_WGRPAPOVERL], L_WGRPAPOVERL);
	strncpy(dc->DC_ABEZ_ZEILE2, &line[P_ARTBEZ2], L_ARTBEZ2);
	strncpy(dc->DC_UN_NR, &line[P_UNNR], L_UNNR);
}

/* ------------------------------------------------------------------- */
static void InitializeNBStr()
{
	ze_lcpy( dc.DCSTATUS, '0', L_ZDCART_DCSTATUS );
	ze_lcpy( dc.NBSTATUS, '0', L_ZDCART_NBSTATUS );
	ze_lcpy( dc.ZAENDERUNG, '0', L_ZDCART_ZAENDERUNG );
    ze_lcpy( dc.NB_DC_PLAUSI, '0', L_ZDCART_NB_DC_PLAUSI );
	ze_lcpy( dc.NB_DC_ZWING, '0', L_ZDCART_NB_DC_ZWING );
	ze_lcpy( dc.NB_DC_NZWING, '0', L_ZDCART_NB_DC_NZWING );
}

/* ------------------------------------------------------------------- */
static int LoadZDCOART(char *errmld)
{
	int sqlret;

	sqlret = sel_zdcoart(&Fd_Zdcoart, dc.DC_ARTIKEL_NR, &dco, errmld);

	if (sqlret == 0)
	{
		if ( DCOartFill( &dco, &dc, tages_datum, errmld ) != 0 ) 
			return 1;
		dco.DC_DATUM_AENDER = tages_datum;
		
		if ( !(strcmp (dc.DC_AECODE ,DCAECODE_DEL)))
		{/*delete*/
			sqlret = del_zdcoart( &Fd_Zdcoart, dco.DC_ARTIKEL_NR, errmld );
			if (sqlret == 0 && satznr_prev != satznr)
				anz_del++;
		}
		else
		{/*update*/
			sqlret = upd_zdcoart(&Fd_Zdcoart, &dco, errmld);
			if (sqlret == 0 && satznr_prev != satznr )
				anz_upd++;
		}
	}
	else if (sqlret == 100)
	{
		FdInitTabBuf( Fd_Zdcoart, &dco );		
//		SqlInitBuf( &dco, STRUCDESC_ZDCOART );

		if ( DCOartFill( &dco, &dc, tages_datum, errmld ) != 0 ) 
			return 1;
		
		dco.DC_DATUM_ANLAGE = tages_datum;
		dco.DC_DATUM_AENDER = 0;
		dco.DC_ARTIKEL_NR = dc.DC_ARTIKEL_NR;
		
		/* bei Neuanlage in oart Aenderung von Lief-/Herst-Code zulassen*/
		if ( (IsDCFeldErr ( dc.NB_DC_NZWING, NZ_AEND_LIEF_HERST )) == 1 )
			SetDCTrueFalse(0, dc.NB_DC_NZWING, NZ_AEND_LIEF_HERST);

		/* bei Neuanlage in oart Aenderung von Box-/Tax-KZ zulassen*/
		if ( (IsDCFeldErr ( dc.NB_DC_ZWING, ZW_AEND_BOX_TAX )) == 1 )
			SetDCTrueFalse(0, dc.NB_DC_ZWING, ZW_AEND_BOX_TAX);
		
		if ( strcmp(dc.DC_AECODE,DCAECODE_DEL) != 0 )
		{
			/*insert*/
			sqlret = ins_zdcoart(&Fd_Zdcoart, &dco, errmld); 
			if (sqlret == 0 && satznr_prev != satznr)
				anz_ins++;
		}
		else
		{
			if (satznr_prev != satznr)
				anz_noact++;
			
			sqlret = 0;
		}
	}

	return sqlret;
}

/* --------- Vergleichs-Werte -------------------- */
static char *Tax = " 123LE";
static char *ArtKz   = " *KMNRXSZ";
static char *YesNo  = "JN";
static char *Mwst  = "0123";
static char *NullEins = "01";
static char *Lagerhinw = " TEKUM";
static char *Ablauf = " T";
static char *ArtGrp = "01234569DNLW";
static char *Aender = " NRAL";
static char *OekoKZ = "P1P2";
static char *AbgBesch = "P  T  PT";
static char *Box = " GYRN";
static char *PflSch = " 12";
static char *MedProd_AbgVO = " 1234";
static char *MedProd_Klasse = " ABCDEFGHIJKOPQRSTUV";
static char *ArtGrp_lt_VO = " AEHIKMX";
//static char *FaelschSicher = "0123";

/* ------------------------------------------------------------------- */
static void FillDCPlausiErr( )
{
	SetDCNumBlankErr(dc.DC_EINH_MENGE, dc.NB_DC_PLAUSI, PL_ARTMENGE);
	SetDCErr		(dc.DC_TAXKZ, Tax, dc.NB_DC_PLAUSI, PL_KZTAXE);
	SetDCErr		(dc.DC_ARTIKELKZ, ArtKz, dc.NB_DC_PLAUSI, PL_KZAPOVERL);
	SetDCErr		(dc.DC_CODEIN, YesNo, dc.NB_DC_PLAUSI, PL_KZCODEIN);
	
	SetDCErr		(dc.DC_OHNE_PREISBESCH, YesNo, dc.NB_DC_PLAUSI, PL_KZOHNEPRBESCH);
	SetDCErr		(dc.DC_MWST_GH, Mwst, dc.NB_DC_PLAUSI, PL_MWSTCODEGR);
	SetDCErr		(dc.DC_MWST_AP, Mwst, dc.NB_DC_PLAUSI, PL_MWSTCODEAPO);
	SetDCErr		(dc.DC_CHARGE, YesNo, dc.NB_DC_PLAUSI, PL_CHARGE);
	SetDCNumErr		(dc.DC_FAELSCHSICHER, dc.NB_DC_PLAUSI, PL_FAELSCHSICHER);
	SetDCErr		(dc.DC_VERM_REZ_GEB, NullEins, dc.NB_DC_PLAUSI, PL_KZVERMREZGEB);
	SetDCErr		(dc.DC_NV_GH, YesNo, dc.NB_DC_PLAUSI, PL_KZNVERFGR);
	SetDCErr		(dc.DC_NV_WV, YesNo, dc.NB_DC_PLAUSI, PL_KZNVERFVERL);

	SetDCNumErr		(dc.DC_MINDESTABNAHME, dc.NB_DC_PLAUSI, PL_MINDABN);
	SetDCNumErr		(dc.DC_HOEHE, dc.NB_DC_PLAUSI, PL_HOEHE);
	SetDCNumErr		(dc.DC_BREITE, dc.NB_DC_PLAUSI, PL_BREITE);
	SetDCNumErr		(dc.DC_TIEFE, dc.NB_DC_PLAUSI, PL_TIEFE);

	SetDCErr		(dc.DC_LAGERHINWEIS, Lagerhinw, dc.NB_DC_PLAUSI, PL_LAGERHINW);
	SetDCErr		(dc.DC_KZ_ABLAUF, Ablauf, dc.NB_DC_PLAUSI, PL_KZABLAUF);
	SetDCErr		(dc.DC_APO_PFLICHTIG, YesNo, dc.NB_DC_PLAUSI, PL_KZAPOPFL);

	SetDCNumBlankErr(dc.DC_REGISTER_NR, dc.NB_DC_PLAUSI, PL_REGNR);
//	SetDCNumBlankErr(dc.DC_THERAPIEGRUPPE, dc.NB_DC_PLAUSI, PL_THERAPIEGRP);

	SetDCErr		(dc.DC_ARTIKELGRUPPE, ArtGrp, dc.NB_DC_PLAUSI, PL_ARTGRP);
	SetDCErr		(dc.DC_MINIK_BASISS, YesNo, dc.NB_DC_PLAUSI, PL_KZMINIBASIS);
	SetDCErr		(dc.DC_AECODE, Aender, dc.NB_DC_PLAUSI, PL_AENDERCODE);

	SetDCNumErr		(dc.DC_GEWICHT, dc.NB_DC_PLAUSI, PL_GEWICHT);
	
	/* Version 01.00.01.01 -> Plausi nicht mehr auf OekoKZ prüfen!
	SetDC2Err		(dc.DC_OELHV_OEKOKZ, OekoKZ, dc.NB_DC_PLAUSI, PL_KZOEKO);*/
	SetDC2Err		(dc.DC_ABGABEBES, AbgBesch, dc.NB_DC_PLAUSI, PL_KZ_ABGBESCHR);

	SetDCErr		(dc.DC_VERKEHRSFAEHIG, YesNo, dc.NB_DC_PLAUSI, PL_KZVERKEHR);
	
	SetDCErr		(dc.DC_HV_BOX, Box, dc.NB_DC_PLAUSI, PL_BOXERSTATT);

	SetDCNumErr		(dc.DC_DATUM_ANLAGE, dc.NB_DC_PLAUSI, PL_DATERSTANL);
	SetDCNumErr		(dc.DC_DATUM_AENDER, dc.NB_DC_PLAUSI, PL_DATLETZTAEND);
	SetDCNumErr		(dc.DC_DATUMGUELTIGAB, dc.NB_DC_PLAUSI, PL_DATGUELTAB);
	SetDCNumErr		(dc.DC_LFD_NR, dc.NB_DC_PLAUSI, PL_AUSLIEFVERS);

	SetDCErr		(dc.DC_NICHTUEBERGH, YesNo, dc.NB_DC_PLAUSI, PL_KZNGR);

	SetDCPdmErr		(dc.DC_GEP, dc.NB_DC_PLAUSI, PL_GEP);
	SetDCPdmErr		(dc.DC_AEP, dc.NB_DC_PLAUSI, PL_AEP);
	SetDCPdmErr		(dc.DC_KKP, dc.NB_DC_PLAUSI, PL_KKP);
	SetDCPdmErr		(dc.DC_AVP, dc.NB_DC_PLAUSI, PL_AVP);
	SetDCPdmErr		(dc.DC_KKP_HAUSAPO, dc.NB_DC_PLAUSI, PL_KKPHAUSAPO);

	SetDCErr		(dc.DC_ARZNEIMITTEL,	YesNo, dc.NB_DC_PLAUSI, PL_ARZNEIMITTEL);
	SetDCErr		(dc.DC_ABGRENZ_VERORD,	YesNo, dc.NB_DC_PLAUSI, PL_ABGR_VERORD);
	SetDCErr		(dc.DC_SG_ZUBEREITUNG,	YesNo, dc.NB_DC_PLAUSI, PL_SG_ZUB);
	SetDCErr		(dc.DC_SG_SUBSTANZ,		YesNo, dc.NB_DC_PLAUSI, PL_SG_SUBSTANZ);
	SetDCErr		(dc.DC_DROGENAGS_KAT1,	YesNo, dc.NB_DC_PLAUSI, PL_DROGAGS_KAT1);
	SetDCErr		(dc.DC_DROGENAGS_KAT2,	YesNo, dc.NB_DC_PLAUSI, PL_DROGAGS_KAT2);
	SetDCErr		(dc.DC_DROGENAGS_KAT3,	YesNo, dc.NB_DC_PLAUSI, PL_DROGAGS_KAT3);
	SetDCErr		(dc.DC_BLUTKONSERVE,	YesNo, dc.NB_DC_PLAUSI, PL_BLUTKONSERVE);
	SetDCErr		(dc.DC_RADIOAKT_ARZNEI, YesNo, dc.NB_DC_PLAUSI, PL_RADIOAKT_ARZNEI);
	SetDCErr		(dc.DC_FUETTER_ARZNEI,	YesNo, dc.NB_DC_PLAUSI, PL_FUETTER_ARZNEI);
	SetDCErr		(dc.DC_ARZNEI_GEWERBE,	YesNo, dc.NB_DC_PLAUSI, PL_ARZNEI_GEWERBE);
	SetDCErr		(dc.DC_DENTALARZNEI,	YesNo, dc.NB_DC_PLAUSI, PL_DENTALARZNEI);
	SetDCErr		(dc.DC_MEDIZIN_GAS,		YesNo, dc.NB_DC_PLAUSI, PL_MEDIZIN_GAS);
	SetDCErr		(dc.DC_KONTAKTLINSENFL, YesNo, dc.NB_DC_PLAUSI, PL_KONTAKTLINSENFL);
	SetDCErr		(dc.DC_ALK_UNVERST,		YesNo, dc.NB_DC_PLAUSI, PL_ALK_UNVERST);
	SetDCErr		(dc.DC_ALK_VERGAELLT,	YesNo, dc.NB_DC_PLAUSI, PL_ALK_VERGAELLT);
	SetDCErr		(dc.DC_GIFT,			YesNo, dc.NB_DC_PLAUSI, PL_GIFT);
	SetDCErr		(dc.DC_ZYTOSTATIKUM,	YesNo, dc.NB_DC_PLAUSI, PL_ZYTOSTATIKUM);

	SetDCErr		(dc.DC_PFLANZENSCHUTZ,	PflSch, dc.NB_DC_PLAUSI, PL_PFLANZENSCH);
	SetDCErr		(dc.DC_MEDPROD_ABGABEV,	MedProd_AbgVO, dc.NB_DC_PLAUSI, PL_MEDPROD_ABGVO);
	SetDCErr		(dc.DC_MEDPROD_KLASSE,	MedProd_Klasse, dc.NB_DC_PLAUSI, PL_MEDPROD_KLASS);
	SetDCErr		(dc.DC_ARTGRP_LTVERORD,	ArtGrp_lt_VO, dc.NB_DC_PLAUSI, PL_ARTGRP_LTVO);
	SetDCFlagErr	(dc.DC_BIOSIEGEL,		dc.NB_DC_PLAUSI, PL_BIOSIEGEL);
	SetDCFlagErr	(dc.DC_ANTIBIOTIKUM,		dc.NB_DC_PLAUSI, PL_ANTIBIOTIKUM);
}

/* ------------------------------------------------------------------- */
static void FillDCStatus( )
{
	strcpy (dc.DCSTATUS,  DCSTATUS_FREIGEG);

  /* unvollständige Datensätze -> Sperren */
	if ( *dc.DC_ARTIKELTEXT == ' ' || dc.HERSTELLER_NR == -1 )
	{
		strcpy (dc.DCSTATUS,  DCSTATUS_GESPERRT);
		if ( strcmp (dc.ZAENDERUNG, ZAENDERUNG_NEU) == 0 )
			strcpy (dc.ZAENDERUNG, ZAENDERUNG_NEU_UNVOLLST);
		else
			strcpy (dc.ZAENDERUNG, ZAENDERUNG_AEND_UNVOLLST);
	}
		
  /* Bei Neuaufnahme eines geloeschten Artikels -> Sperren */
	if ( !(strcmp (dc.DC_AECODE, DCAECODE_DEL)) && !(strcmp(dc.ZAENDERUNG, ZAENDERUNG_NEU)) )
     strcpy (dc.DCSTATUS,  DCSTATUS_GESPERRT);

	if ( IsDCErr( dc.NB_DC_PLAUSI ))
	{
		if (IsDCErr (dc.NB_DC_ZWING))
		{
			if ( IsDCErr (dc.NB_DC_NZWING))
				strcpy( dc.NBSTATUS,  NBSTATUS_ZW_PL_NZW );
			else
				strcpy( dc.NBSTATUS,  NBSTATUS_ZWING_PL );
		}
		else
		{
			if ( IsDCErr (dc.NB_DC_NZWING))
				strcpy( dc.NBSTATUS,  NBSTATUS_NZW_PL );
			else
				strcpy( dc.NBSTATUS,  NBSTATUS_PLAUSI );
		}
	}
	else
	{
		if (IsDCErr (dc.NB_DC_ZWING))
		{
			if ( IsDCErr (dc.NB_DC_NZWING))
				strcpy( dc.NBSTATUS,  NBSTATUS_ZWING_NZW );
			else
				strcpy( dc.NBSTATUS,  NBSTATUS_ZWING );
		}
		else
		{
			if ( IsDCErr (dc.NB_DC_NZWING))
				strcpy( dc.NBSTATUS,  NBSTATUS_NZWING );
			else
				strcpy( dc.NBSTATUS,  NBSTATUS_NO_ERR );
		}
	}
}

/* ---------------------------------------------------------------------- */
int SelCComGroup ( )
{
	int sqlret;
	char taxkz[2];
	char adopt_gep[2];
	char adopt_aep[2];
	char adopt_avp[2];
	char adopt_bez[2];
	
	sqlret = sel_ccomgroupprop(dc.WARENGRUPPE, taxkz, 
									adopt_gep, adopt_aep, adopt_avp, adopt_bez); 

	if (sqlret != 0 )
	{
		taxkz_ccomgroupprop = TAXART_NETTO; /* default netto */
		adoptgep = ADOPT_PRICE;
		adoptaep = ADOPT_PRICE;
		adoptavp = ADOPT_PRICE;
		adoptbez = ADOPT_PRICE;
	}
	else
	{
		taxkz_ccomgroupprop = taxkz[0];
		adoptgep = adopt_gep[0];
		adoptaep = adopt_aep[0];
		adoptavp = adopt_avp[0];
		adoptbez = adopt_bez[0];
	}

	return sqlret;
}

/* ------------------------------------------------------------------- */
static int CheckLine(char *errmld)
{
	int sqlret, sqlwrgrp;
	long datum_ah;
	double gep, aep, herst_prozent, avp;

	char sondergrosso[2];
	char skontofaehig[2] = {0};

	datum_ah = -1;
	strcpy (sondergrosso,"");

	gep = 0;
	aep = 0;
	avp = 0;
	herst_prozent = 0;
	
	sqlwrgrp = -1;
	
	sqlret = sel_zartikel(dc.DC_ARTIKEL_NR, &datum_ah, sondergrosso, skontofaehig, errmld);
				
	if ( !( sqlret == 0 || sqlret == 100 )) 
		return sqlret;

	dc.HERSTELLER_NR = -1;

	if ( sqlret == 0 )   /* Aenderung */
    {
		sel_herstellnr(dc.DC_ARTIKEL_NR, &dc.HERSTELLER_NR, errmld);
		sqlwrgrp = sel_warengrp(dc.DC_ARTIKEL_NR, dc.WARENGRUPPE, errmld);
		
		if (sqlwrgrp == 0)
			SelCComGroup();
		else
		{
			taxkz_ccomgroupprop = TAXART_NETTO; /* default netto */
			adoptgep = ADOPT_PRICE;
			adoptaep = ADOPT_PRICE;
			adoptavp = ADOPT_PRICE;
			adoptbez = ADOPT_PRICE;
		}

		if ( (strcmp (sondergrosso, SONDERGRKZ) == 0) && adoptgep == ADOPT_PRICE )
			SetDCTrueFalse (1, dc.NB_DC_ZWING, ZW_SONDERGROSSO);
				
		strcpy(dc.ZAENDERUNG,ZAENDERUNG_AEND); /*Änderung*/
		
		if ( satznr_prev != satznr )
			art_ohne_pznneu++;

		if ( !(strcmp(dc.DC_AECODE, DCAECODE_NEW)) )
			strcpy (dc.DC_AECODE, DCAECODE_AEND);

		/* --- Plausibilitaetspruefung --- */
		FillDCPlausiErr( );
		
		if ( strcmp(dc.DC_AECODE, DCAECODE_DEL)) /* wenn löschen, dann nichts mehr pruefen */
		{
			long DCGro;
			long ArtGro;
			long DCAep;
			long ArtAep;
			long DCAvp;
			long ArtAvp;
			long ProzentPM;

			if ( adoptgep == ADOPT_PRICE || adoptaep == ADOPT_PRICE || adoptavp == ADOPT_PRICE)
			{/*Preise nur prüfen, wenn sie auch in Artikelstamm übernommen werden!*/
				sqlret = CheckPrices ( &dc, &aep, &gep, &avp, &herst_prozent, 
										adoptgep, adoptaep, errmld );

				if ( sqlret == 0 )
				{
					if ( PricesPlausi ( &dc ) == 0 ) /* Preise geaendert u. kein Plausi-Fehler */
					{
						DCGro  = GetDCPreisLong( dc.DC_GEP );
						DCAep  = GetDCPreisLong( dc.DC_AEP );
						DCAvp  = GetDCPreisLong( dc.DC_AVP );

						ArtGro  = GetPhosixPreisLong( gep );
						ArtAep  = GetPhosixPreisLong( aep );
						ArtAvp  = GetPhosixPreisLong( avp );
						
						ProzentPM = GetPhosixProzent( herst_prozent );

						TestPreis_Aenderung (&dc, ProzentPM, DCGro, DCAep, DCAvp, ArtGro, ArtAep, ArtAvp, taxkz_ccomgroupprop);
					}
				}
				else if ( sqlret == 100 ) /* kein Preissatz vorhanden im Artikelstamm!*/
				{
					if ( PricesPlausi ( &dc ) == 0 )
					{
						DCGro  = GetDCPreisLong( dc.DC_GEP );
						DCAep  = GetDCPreisLong( dc.DC_AEP );
						DCAvp  = GetDCPreisLong( dc.DC_AVP );
						
						ArtGro  = 0;
						ArtAep  = 0;
						ArtAvp  = 0;
										
						TestPreis_Aenderung (&dc, 0, DCGro, DCAep, DCAvp, ArtGro, ArtAep, ArtAvp, taxkz_ccomgroupprop);
					}
				}
			}
			
			/* auf zwingenden Fehler 4 erst prüfbar wenn Warengruppe gelesen!*/
			if ( IsChangeArtText15() > 0 && adoptbez == ADOPT_PRICE
				&& dc.WARENGRUPPE[0] == '0' && dc.WARENGRUPPE[1] == '1' )
				SetDCTrueFalse (1, dc.NB_DC_ZWING, ZW_WRGRP_ARTBEZ);
			
			if ( datum_ah == 0 && (strcmp(dc.DC_AECODE, DCAECODE_AUSVERKEHR) == 0))
				SetDCTrueFalse (1, dc.NB_DC_NZWING, NZ_ART_AUSS_HANDEL);
		}
	}
    else /* Neuanlage */
    {
        dc.HERSTELLER_NR = 11111; /*Default-Hersteller-Nr bei Neuanlage*/
		adoptgep = ADOPT_PRICE;
		adoptaep = ADOPT_PRICE;
		adoptavp = ADOPT_PRICE;
		adoptbez = ADOPT_PRICE;
		
		strcpy(dc.ZAENDERUNG,ZAENDERUNG_NEU); /*Neuanlage*/
		
		if ( satznr_prev != satznr )
			art_mit_pznneu++;

		if ( !(strcmp (dc.DC_AECODE, DCAECODE_AEND)) )
			strcpy (dc.DC_AECODE, DCAECODE_NEW);

		/* --- Plausibilitaetspruefung --- */
		FillDCPlausiErr( );

		if ( strcmp(dc.DC_AECODE, DCAECODE_DEL)) /* wenn löschen, dann nichts mehr pruefen */
		{
			/* Preise pruefen */
			CheckPrices ( &dc, &aep, &gep, &avp, &herst_prozent, 
							adoptgep, adoptaep, errmld );

			if ( PricesPlausi ( &dc ) == 0 )
			{
				TestPreis_Neuaufnahme ( &dc );
			}
		}
    }

	/* Datumgueltigab bei Neuanlage = heute */
	if ( strcmp(dc.ZAENDERUNG, ZAENDERUNG_AEND ))
    {
		if ( dc.DC_DATUMGUELTIGAB >= tages_datum )
          dc.DC_DATUMGUELTIGAB = AddDayToPhoDate(tages_datum, 1); // im ZDP sind nur Preise änderbar mit Datum > heute !;

		strcpy( dc.WARENGRUPPE, "     " ); // default bei Neuanlagen
		strcpy( skontofaehig, "1" );
    }
	
	/* Automatismen */
	CalcKZs ( &dc, grenzeHochpreis, skontofaehig, errmld );
	
	/* Fehlerstrings setzen */
	SetNZwing ( &dc, errmld );
	SetZwing ( &dc, errmld );
	
	/* Mwst-Code an Artikelstamm anpassen!
		1 (dc) = vermindert		--> 1 (zartikel)
		2 (dc) = voll			--> 0 (zartikel) */
	if ( strcmp( dc.DC_MWST_GH, DCMWST_VOLL ) == 0 )      
      strcpy(dc.DC_MWST_GH, ZART_MWST_VOLL);
	else if ( strcmp( dc.DC_MWST_GH, DCMWST_3RD ) == 0 )      
      strcpy(dc.DC_MWST_GH, ZART_MWST_3RD);
	else if (strcmp(dc.DC_MWST_GH, DCMWST_K) == 0)
		strcpy(dc.DC_MWST_GH, ZART_MWST_K);

	if ( strcmp( dc.DC_MWST_AP, DCMWST_VOLL ) == 0 )      
      strcpy(dc.DC_MWST_AP, ZART_MWST_VOLL);
	else if ( strcmp( dc.DC_MWST_AP, DCMWST_3RD ) == 0 )      
      strcpy(dc. DC_MWST_AP, ZART_MWST_3RD);	
	else if (strcmp(dc.DC_MWST_AP, DCMWST_K) == 0)
		strcpy(dc.DC_MWST_AP, ZART_MWST_K);
	
	/* keine Warengruppe, obwohl keine Neuanlage -> Fehler zurücksetzen! */
	// -->  I-19000383
	if ( sqlwrgrp > 0 )
	{
		ze_lcpy( dc.NB_DC_ZWING, '0', L_ZDCART_NB_DC_ZWING );
		ze_lcpy( dc.NB_DC_NZWING, '0', L_ZDCART_NB_DC_NZWING );
	}

	if ( strcmp (dc.DC_AECODE, DCAECODE_NEW) == 0)
		datgueltab_prev = dc.DC_DATUMGUELTIGAB;
	else
		datgueltab_prev = -1;
		
   
	/* Statusfeld fuellen */
    FillDCStatus( );
	
	/* insert in zdcart */
	sqlret = ins_zdcart( &dc, errmld );

	return sqlret;
}

/* ------------------------------------------------------------------- */
static int DCLieferung( char *errmld )
{
	int status;
	char zeile[NO_SIGNS + 1];

	pzn_previous = 0;
	status = 0;
	
	while ( status == 0 )/*SCHLEIFE zum Lesen aller Datenzeilen aus datacare.txt*/
	{
		
		status = GetDCZeile( fd_file, zeile );
		if (status == 0)
		{
			linenr++;
			memset(&dco,0,sizeof(dco));
			memset(&dc,0,sizeof(dc));
			InitializeNBStr();
			LineToDCStruct( &dc, zeile, errmld );

			if (dc.DC_ARTIKEL_NR != pzn_previous) /*gleiche PZN noch einmal!*/
			{
				satznr++;
				dc.SATZNR = satznr;
				
				if (CheckPruefziffer ( dc.DC_ARTIKEL_NR ) == 1)
				{
					if ( LoadZDCOART (errmld) == 0 )
					{						
						/* kopieren von dco nach dc */
						dc.DC_DATUMGUELTIGAB = dco.DC_DATUMGUELTIGAB;
						dc.DC_DATUM_ANLAGE = dco.DC_DATUM_ANLAGE;
						dc.DC_DATUM_AENDER = dco.DC_DATUM_AENDER;
						CopyPlausi  ( dc.NB_DC_PLAUSI );

						if ( CheckLine(errmld) == 0 )
						{
							pzn_previous = dc.DC_ARTIKEL_NR;
							satznr_prev = satznr;
							/* WriteProtZeile ( fd_prot, &dc ); PROT */
						}
					}
				}
				else
				{
					/*in Protokoll schreiben, dass Pruefziffer falsch!*/
					strcpy (dc.DC_ARTIKELTEXT, pzn_error);
					/* WriteProtZeile ( fd_prot, &dc ); PROT */
				}
			}
			else /*gleiche PZN noch einmal!*/
			{
				dc.SATZNR = satznr;
				del_zdcart(dcdatumnr, satznr, errmld ); // --> I-18059743: vom zweiten Satz werden letztlich nur die Werte übernommen, die sich von Satz 1 (also von zdcoart) unterscheiden ...

				if (CheckPruefziffer ( dc.DC_ARTIKEL_NR ) == 1)
				{
					if ( datgueltab_prev >= 0 )
						dc.DC_DATUMGUELTIGAB = datgueltab_prev;
					
					if ( LoadZDCOART (errmld) == 0 )
					{						
						/* kopieren von dco nach dc */
						dc.DC_DATUMGUELTIGAB = dco.DC_DATUMGUELTIGAB;
						dc.DC_DATUM_ANLAGE = dco.DC_DATUM_ANLAGE;
						dc.DC_DATUM_AENDER = dco.DC_DATUM_AENDER;
						CopyPlausi  ( dc.NB_DC_PLAUSI );

						if ( CheckLine(errmld) == 0 )
						{
							pzn_previous = dc.DC_ARTIKEL_NR;
							/* WriteProtZeile ( fd_prot, &dc ); PROT */
						}
					}
				}
				else
				{
					/*in Protokoll schreiben, dass Pruefziffer falsch!*/
					strcpy (dc.DC_ARTIKELTEXT, pzn_error);
					/* WriteProtZeile ( fd_prot, &dc ); PROT */
				}

				/*in Protokoll schreiben, dass Artikel 2x in Folge gelesen!
				strcpy (dc.DC_ARTIKELTEXT, pzn_double);
				/* WriteProtZeile ( fd_prot, &dc ); PROT */
			}
		}
	}

	if (status != 2) 
		strcpy(errmld, "Error on reading datacare.txt; file not read to the end!");
	else
	{
		if (linenr == nofilesets) 
			status = 0;/*EOF*/
		else
			sprintf(errmld, "Error on reading datacare.txt; number of datasets in header (%ld) does not match the lines read (%ld)!", nofilesets, linenr );

	}

   CloseDCDatei( fd_file );
   fd_file = NULL;

   /* CloseProtDatei ( fd_prot );
   fd_prot = NULL; PROT */
   
   return status;
}

/* ------------------------------------------------------------------- */
static long test_dcnr(  long dcdatum, char *errmld )
{
    char sql[50];
    long status;
    long nr;

    sprintf( sql, "select DCNR from ZDCART where DCNR=%d",
                  (int)dcdatum );

    status = SqlRead( sql, &nr, NULL );
    if ( status == 100 ) return 0;

    if ( status == 0 )
       strcpy( errmld, "DATACARE-Datei bereits eingelesen" );
    else
    {
       strcpy( errmld, "zdcart: " );
       strcat( errmld, DynErrmld() );
    }
    return -1;
}

/* ------------------------------------------------------------------- */
static long GenArtikel( char *db, char* ili_file, char* prot_file, char *errmld )
{
   int status;
   char zeile[NO_SIGNS + 1] = {0};
   char dat[9] = {0};
   char no[6] = {0};
   char today[9] = {0};
   char *protday;
   
   tages_datum = GetPhoDate();
   
   fd_file = NULL;
   fd_prot = NULL;

   strcat(prot_file, PROTNAME );
   sprintf(today, "%ld", tages_datum);
   protday = today;
   protday = protday + 2;
   strcat(prot_file, protday );
   strcat(prot_file, PROTEND );
   
   /*öffnen des Datacare-Files und Protokoll-File*/
   status = OpenDCDatei( &fd_file, ili_file, errmld );
   if ( status != 0 )
   {
       sprintf(errmld, "datacare-file not found under path %s\n", ili_file);
	   return status;
   }
   
   /*status = OpenProtDatei( &fd_prot, prot_file, tages_datum, errmld );
   if ( status != 0 )
   {
       sprintf(errmld, "not able to open protocol-file\n");
	   return status;
   } PROT */

    if ( OpenBase( db, errmld ) == 0 )
    {
        OpenPflege( (char*)user, errmld );
	
		/*Kopfzeile aus DC-File lesen*/
		status = GetDCZeile( fd_file, zeile ); /*Kopfzeile*/
		if ( status != 0 )
		{
			strcpy(errmld, "no data in datacare-file\n");
			return status;
		}
		
		strncpy(dat, &zeile[DCDATPOS], 8);
		dcdatumnr = atol( dat );
		
		strncpy(no, &zeile[DCNOPOS], 6);
		nofilesets = atol( no );
		
		if ( test_dcnr( dcdatumnr, errmld ) == 0 )
        {
			Fd_Zdcoart = -1;

			if ( OpenBufferDesc( &Fd_Zdcoart, "zdcoart", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 )
			{
				/* Taxtabelle lesen */
				if ( CreateTaxtabAustria( &grenzeHochpreis, errmld ) == 0 ) 
				{
					satznr = 0;
					linenr = 0;
					art_mit_pznneu = 0;
					art_ohne_pznneu = 0;

					status = DCLieferung ( errmld );
				}
			}
			else
			{
				status = 1;
			}
			CloseOneBufferDesc(Fd_Zdcoart);
        }
		else
		{
			status = 1;
		}
        CloseBase( );
    }
   return status;
}

/* ------------------------------------------------------------------- */
#define FILE_LEN 30
long GenDCArtNeu( char *db, char *ili_direc, char *errmld )
{
    char meld[100];
	char *ili_file;
	char *prot_file;

    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
	prot_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
    if ( ili_file == NULL || prot_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler GenDCArtNeu" );
       return 1;
    }

	strcpy( prot_file, ili_direc );
	strcpy( ili_file, ili_direc );
    strcat( ili_file, FILENAME );
    if ( GenArtikel( db, ili_file, prot_file, errmld ) != 0 )
    {
       free( ili_file );
	   free( prot_file );
       return 1;
    }

    free( ili_file );
	free( prot_file );
   sprintf( errmld, "%ld DCNR\n" 
                     "%ld DC-Artikel erfolgreich geladen in zdcart\n" 
                     "   %ld neue ZArtikel\n   %ld vorhandene ZArtikel\n" 
					 "zdcoart %ld updated, %ld deleted, %ld inserted, %ld already deleted",
                     dcdatumnr,
                     satznr,
                     art_mit_pznneu,
                     art_ohne_pznneu,
					 anz_upd, anz_del, anz_ins, anz_noact);

    /* als bearbeitet kennzeichnen */
	if ( WriteIfaStatus( "PARTIKEL", ili_direc, meld  ) != 0 ) /*ifalib ifastat.c*/
    {
         strcat( errmld, "\nStatus 'bearbeitet' wurde nicht gesetzt" );
    }

#if defined(_WIN32)
#else
	/* Kommando datacare_ok aufufen */
	/*sprintf( meld, "datacare_ok %ld", dcdatumnr );*/
	/*UnxHsystem( meld );*/
#endif

    return 0;
}
