/* ---------------------------------------------------------------------- *
 * Aufgabe        : Funktionalität zum Prüfen der Werte aus DC-Datei      *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 31.01.2005                                            *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <voodoo_table_header/zdcart.h>
#include <voodoo_table_header/zdcoart.h>

#include "znb_gen_dc.h"
#include "sql_zdcart.h"
#include "l_taxtab.h"
#include "check_plausi.h"


/* ---------------------------------------------------------------------- */
int CheckPruefziffer ( long pzn )
{
	int i;
	long zahl, prziff;

	if ( pzn <= 0 ) 
		return 0;

    zahl = pzn;
	
	prziff = 0;
    for (i=7; i>=2; i--)
    {
            zahl /= 10;
            prziff += i * ( zahl % 10 );
    }
    prziff %= 11;

    if (prziff == 10) 
		prziff = 0;

	if ( prziff == ( pzn % 10 ) )
            return 1;
    else
            return 0;
}

/* ---------------------------------------------------------------------- */
static int IsNoChange( struct ZDCART *dc, int pos )
{
	return dc->NB_DC_PLAUSI[ pos ] == NB_PL_NO_VAL;
}

/* ---------------------------------------------------------------------- */
static void ResetNoChange( struct ZDCART *dc, int pos )
{
   dc->NB_DC_PLAUSI[ pos ] = NB_PL_OK;
}

/* -------- Preise ---------------- */
int PricesPlausi( struct ZDCART *dc )
{
	if ( dc->DC_AEP >= 10000000.00 ||
        dc->DC_GEP >= 10000000.00 ||
        dc->DC_AVP   >= 10000000.00     )	
   {
      return 1;
   }

   if ( !IsNoChange ( dc, PL_GEP ) &&
	   IsDCFeldErr( dc->NB_DC_PLAUSI, PL_GEP   ) ) return 1;

   if ( !IsNoChange ( dc, PL_AEP ) &&
        IsDCFeldErr( dc->NB_DC_PLAUSI, PL_AEP   ) ) return 1;

   if ( !IsNoChange ( dc, PL_AVP ) &&
        IsDCFeldErr( dc->NB_DC_PLAUSI, PL_AVP   ) ) return 1;

   return 0;
}

/* ---------------------------------------------------------------------- */
int CheckPrices ( struct ZDCART *dc, double* aep, double *gep, double *avp, 
				 double * herst_prozent, char adgep, char adaep, char *errmld )
{
	int sqlret;
	sqlret = 0;

	if ( strcmp (dc->ZAENDERUNG, ZAENDERUNG_NEU) )
		sqlret = sel_zartpreis	( dc->DC_ARTIKEL_NR, dc->DC_DATUMGUELTIGAB, 
									aep, gep, avp, herst_prozent, errmld);

	/* Preisberechnung aus herst_prozent */
	if ( *herst_prozent < 0.0 && adgep == ADOPT_PRICE )
	{
		dc->DC_GEP = dc->DC_AEP * ( 1 + (*herst_prozent)/100 );
		KaufmRunden ( &(dc->DC_GEP) , 2 );
	}
	else if ( *herst_prozent > 0.0 && adaep == ADOPT_PRICE )
	{
		dc->DC_AEP = dc->DC_GEP * ( 1 + (*herst_prozent)/100 );
		KaufmRunden ( &(dc->DC_AEP) , 2 );
	}
	
	/* GEP und AEP = 0 */
	if ( dc->DC_GEP <= 0.01 && dc->DC_AEP <= 0.01 
		&& ( adgep == ADOPT_PRICE || adaep == ADOPT_PRICE ) )
	{
		if ( !(strcmp (dc->ZAENDERUNG, ZAENDERUNG_NEU)))
			SetDCTrueFalse (1, dc->NB_DC_ZWING, ZW_AEP_GEP_0);
		else
		{
			if ( *gep <= 0.01 || *aep <= 0.01 )
				SetDCTrueFalse (1, dc->NB_DC_ZWING, ZW_AEP_GEP_0);
			else
				SetDCTrueFalse (1, dc->NB_DC_NZWING, NZ_AEP_GEP_0);
		}
	}

	/* GEP = 0 */
	if ( dc->DC_GEP <= 0.01 && adgep == ADOPT_PRICE )
	{
		if ( !(strcmp (dc->ZAENDERUNG, ZAENDERUNG_NEU)))
			SetDCTrueFalse (1, dc->NB_DC_ZWING, ZW_GEP_ERR);
		else
		{
			if ( *gep > 0.01 )
				SetDCTrueFalse (1, dc->NB_DC_ZWING, ZW_GEP_ERR);
			else
				SetDCTrueFalse (1, dc->NB_DC_NZWING, NZ_GEP_HINW);

			SetDCTrueFalse (1, dc->NB_DC_ZWING, ZW_GEP_HERSTPROZ);
		}
	}

	/* AEP = 0 */
	if ( dc->DC_AEP <= 0.01 && adaep == ADOPT_PRICE )
	{
		if ( !(strcmp (dc->ZAENDERUNG, ZAENDERUNG_NEU)))
			SetDCTrueFalse (1, dc->NB_DC_ZWING, ZW_AEP_ERR);
		else
		{
			if ( *aep > 0.01 )
				SetDCTrueFalse (1, dc->NB_DC_ZWING, ZW_AEP_ERR);
			else
				SetDCTrueFalse (1, dc->NB_DC_NZWING, NZ_AEP_HINW);

			SetDCTrueFalse (1, dc->NB_DC_ZWING, ZW_AEP_HERSTPROZ);
		}
	}

	/* GEP > AEP */
	if ( dc->DC_GEP > 0.01 && dc->DC_AEP < dc->DC_GEP 
		&& ( adgep == ADOPT_PRICE || adaep == ADOPT_PRICE ) )
		SetDCTrueFalse (1, dc->NB_DC_ZWING, ZW_GEP_GR_AEP);

	return sqlret;
}

/* ---------------------------------------------------------------------- */
void SetNZwing ( struct ZDCART *dc, char *errmld)
{
	SetDCTrueFalse ( !(strcmp (dc->DC_AECODE,DCAECODE_REACT)), dc->NB_DC_NZWING, NZ_REAKTIV);

	if ( (!IsNoChange ( dc, PL_GEP ) || !IsNoChange ( dc, PL_AEP ) || !IsNoChange ( dc, PL_AVP ) )
		&& (strcmp (dc->DC_AECODE,DCAECODE_AUSVERKEHR) == 0 ) 
		&& (strcmp (dc->WARENGRUPPE, "01720") != 0) && (strcmp (dc->WARENGRUPPE, "01730") != 0))
			SetDCTrueFalse ( 1, dc->NB_DC_NZWING, NZ_AH_PRICE_CHANGE);

}

/* ---------------------------------------------------------------------- */
void SetZwing ( struct ZDCART *dc, char *errmld)
{
	if ( (strcmp (dc->DC_TAXKZ ,"1") != 0) && (strcmp ( dc->DC_TAXKZ ,"L") != 0) && (strcmp ( dc->DC_TAXKZ ,"E") != 0)
		&& (strcmp(dc->DC_HV_BOX ,DCBOX_EMPTY)) )
	{
		if ( (strcmp (dc->DC_TAXKZ, "2") != 0) || (strcmp (dc->DC_HV_BOX, DCBOX_NO) != 0))
			SetDCTrueFalse (1, dc->NB_DC_ZWING, ZW_BOX_N0_TAX_N1); 
	}

	if ( ((strcmp (dc->DC_MEDPROD_ABGABEV , " ") != 0) && (strcmp ( dc->DC_MEDPROD_KLASSE , " ") == 0)) ||
		 ((strcmp (dc->DC_MEDPROD_ABGABEV , " ") == 0) && (strcmp ( dc->DC_MEDPROD_KLASSE , " ") != 0)) )
	{
		SetDCTrueFalse (1, dc->NB_DC_ZWING, ZW_MEDIZIN_PROD); 
	}
}

/* ---------------------------------------------------------------------- */
void SetWarengruppe (char * wgrp, struct ZDCART *dc, const char * wgrp_current, long grenzeHochpreis)
{
	// Umrechnung WGR wegen Hochpreis nur für die Warengruppen, die auch von diesem Programm errechnet / gesetzt werden!
	char new_wrgrp[6] = {0};
	strcpy (new_wrgrp, wgrp);

	if (dc->DC_AEP > grenzeHochpreis && grenzeHochpreis > 0) 
	{
		new_wrgrp[4] = '9';

		if (strcmp (wgrp_current, wgrp) != 0 && wgrp_current[4] != '9') // Änderung Warengruppe
			SetDCTrueFalse ( 1, dc->NB_DC_NZWING, NZ_WRGRP_HOCHPREIS);
	}
	else
	{
		new_wrgrp[4] = '0';

		if (strcmp (wgrp_current, wgrp) != 0 && wgrp_current[4] == '9') // Änderung Warengruppe
			SetDCTrueFalse ( 1, dc->NB_DC_NZWING, NZ_WRGRP_HOCHPREIS_ENTFERNT);
	}
	
	strcpy( dc->WARENGRUPPE, new_wrgrp );
}

/* ---------------------------------------------------------------------- */
void CalcKZs ( struct ZDCART *dc, long grenzeHochpreis, char * skontof, char *errmld )
{
	char tmp_wrgrp[6];
	char new_wrgrp[6] = {0};
	char wgr_sktof[2] = {0};
	strcpy (tmp_wrgrp, dc->WARENGRUPPE);

	if ( !(strcmp (dc->DC_HV_BOX,DCBOX_GREEN)) && !(strcmp (dc->DC_ARTIKELKZ, "R")) )
		SetWarengruppe("01200", dc, tmp_wrgrp, grenzeHochpreis);

	if ( strcmp (dc->DC_ARTIKELGRUPPE, "N") == 0 && strcmp(dc->DC_TAXKZ,"3") == 0 )
	{
		SetWarengruppe("02200", dc, tmp_wrgrp, grenzeHochpreis);
		strcpy( dc->DC_KZ_ABLAUF, "T" );
	}	

	if ( strcmp (dc->DC_ARTIKELGRUPPE, "L") == 0 && strcmp(dc->DC_TAXKZ,"3") == 0 )
	{
		SetWarengruppe("02150", dc, tmp_wrgrp, grenzeHochpreis);
	}	

	if ( !(strcmp (dc->DC_KASSENZEICHEN ,"VNW")) && dc->DC_ABGABEBES[1] == 'T' /*!(strcmp (dc->DC_ABGABEBES, " T"))*/ ) 
	{
		switch ( dc->DC_TAXKZ[0] )
		{
		case ' ':
		case 'E':
			SetWarengruppe("09110", dc, tmp_wrgrp, grenzeHochpreis);
			break;
		case '1':
			strcpy ( dc->WARENGRUPPE, "01110"); // auch bei Hochpreis setzen / überschreiben
			break;
		case '2':
			strcpy ( dc->WARENGRUPPE, "01790"); // auch bei Hochpreis setzen / überschreiben
			break;
		default:
			break;
		}
	}

	if ( !(strcmp (dc->DC_HV_BOX ,"Y")) && !(strcmp (dc->DC_TAXKZ, "1")) )
	{
		if ( !(strcmp (dc->DC_KASSENZEICHEN ,"RE1")) )
			SetWarengruppe("01300", dc, tmp_wrgrp, grenzeHochpreis);
		else if ( !(strcmp (dc->DC_KASSENZEICHEN ,"RE2")) )
			SetWarengruppe("01330", dc, tmp_wrgrp, grenzeHochpreis);
	}
	
	if ( ((!(strcmp (dc->DC_REZEPTZEICHEN, "S1"))) || (!(strcmp (dc->DC_REZEPTZEICHEN, "S2")))) && 
			strcmp (dc->DC_HV_BOX, DCBOX_EMPTY) )
	{
		strcpy ( new_wrgrp, "01X70");
		switch ( dc->DC_HV_BOX[0] )
		{
		case 'N':
			new_wrgrp[2] = '1';
			break;
		case 'G':
			new_wrgrp[2] = '2';
			break;
		case 'Y':
			new_wrgrp[2] = '3';
			break;
		case 'R':
			new_wrgrp[2] = '4';
			break;
		default:
			break;
		}

		SetWarengruppe(new_wrgrp, dc, tmp_wrgrp, grenzeHochpreis);
	}

	if ( ((!(strcmp (dc->DC_REZEPTZEICHEN, "+ "))) || (!(strcmp (dc->DC_REZEPTZEICHEN, "++")))) && 
			!(strcmp (dc->DC_TAXKZ, "1")) && strcmp (dc->DC_HV_BOX ,DCBOX_EMPTY) && strcmp (dc->DC_HV_BOX ,"Y") )
	{
		strcpy ( new_wrgrp, "01XX0");
		
		switch ( dc->DC_HV_BOX[0] )
		{
		case 'N':
			new_wrgrp[2] = '1';
			new_wrgrp[3] = '9';
			break;
		
		case 'G':
			new_wrgrp[2] = '2';
			
			if(!(strcmp (dc->DC_REZEPTZEICHEN, "+ ")))
				new_wrgrp[3] = '9';
			else
				new_wrgrp[3] = '6';

			break;
		
		case 'R':
			new_wrgrp[2] = '4';

			if(!(strcmp (dc->DC_REZEPTZEICHEN, "+ ")))
				new_wrgrp[3] = '9';
			else
				new_wrgrp[3] = '6';

			break;

		default:
			break;
		}

		SetWarengruppe(new_wrgrp, dc, tmp_wrgrp, grenzeHochpreis);
	}

/* -- von Änderungen vom 05.01.2010 unberührt -- */
	if ( dc->DC_ABGABEBES[0] == 'P' /*!(strcmp (dc->DC_ABGABEBES ,"P "))*/ && strcmp (dc->DC_HV_BOX ,DCBOX_EMPTY) )
	{
		strcpy ( new_wrgrp, "01X50");
		switch ( dc->DC_HV_BOX[0] )
		{
		case 'N':
			new_wrgrp[2] = '1';
			break;
		case 'G':
			new_wrgrp[2] = '2';
			break;
		case 'Y':
			new_wrgrp[2] = '3';
			break;
		case 'R':
			new_wrgrp[2] = '4';
			break;
		default:
			break;
		}

		SetWarengruppe(new_wrgrp, dc, tmp_wrgrp, grenzeHochpreis);
	}

	if ( !(strcmp (dc->DC_REZEPTZEICHEN ,"SG")) && strcmp(dc->DC_HV_BOX ,DCBOX_EMPTY) )
	{
		strcpy ( new_wrgrp, "01X80");
		switch ( dc->DC_HV_BOX[0] )
		{
		case 'N':
			new_wrgrp[2] = '1';
			break;
		case 'G':
			new_wrgrp[2] = '2';
			break;
		case 'Y':
			new_wrgrp[2] = '3';
			break;
		case 'R':
			new_wrgrp[2] = '4';
			break;
		default:
			break;
		}

		SetWarengruppe(new_wrgrp, dc, tmp_wrgrp, grenzeHochpreis);
	}
// --

	if ( strcmp (tmp_wrgrp, dc->WARENGRUPPE) )
		SetDCTrueFalse ( 1, dc->NB_DC_NZWING, NZ_AEND_WRGRP);
	
	if ( strcmp (dc->WARENGRUPPE, "     ") != 0 )
	{
		if ( sel_zdkwgr(dc->WARENGRUPPE, wgr_sktof, errmld) != 0 )
			SetDCTrueFalse ( 1, dc->NB_DC_ZWING, ZW_WRGRP_UNBEKANNT); // check, ob Warengruppe überhaupt existiert
		else if ( (wgr_sktof[0] == 'J' && skontof[0] != '1') || (wgr_sktof[0] == 'N' && skontof[0] == '1') ) 
			SetDCTrueFalse ( 1, dc->NB_DC_NZWING, NZ_AEND_SKONTOFAEHIG); // check, ob sich Skontofähigkeit ändert:
	}
}
