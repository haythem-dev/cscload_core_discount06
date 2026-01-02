/* ---------------------------------------------------------------------- *
 * Aufgabe        : Preistest			                                  *
 * ---------------------------------------------------------------------- *
 * Autor          : Hoerath                                               *
 * erstellt am    : 02.02.2005                                            *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <voodoo_table_header/zdcart.h>
#include <voodoo_table_header/zdcoart.h>

#include "znb_gen_dc.h"
#include "l_taxtab.h"
#include "sql_zdcart.h"
#include "zpreitst.h"

#define TAX_BOX		1
#define TAX_WRGRP	2

static char taxkz_wrgrp;


/* ---------------------------------------------------------------------- */
char GetTaxKennViaWrGrp( struct ZDCART *dc )
{
	return taxkz_wrgrp;
}

/* ---------------------------------------------------------------------- */
char GetTaxKennViaBox( struct ZDCART *dc )
{
	if ( !(strcmp( dc->DC_HV_BOX, DCBOX_GREEN )) || !(strcmp( dc->DC_HV_BOX, DCBOX_YELLOW )))
	{
		return TAXART_4; 
	}
	if ( !(strcmp( dc->DC_HV_BOX, DCBOX_RED )))
	{
		return TAXART_1; 
	}     
	if ( !(strcmp( dc->DC_HV_BOX, DCBOX_EMPTY )))
	{
		return TAXART_NETTO; 
	} 
    return TAXART_NETTO; /* default netto */
}

/* ---------------------------------------------------------------------- */
int IsDCTaxArtikelBox( struct ZDCART *dc )
{
	return GetTaxKennViaBox( dc ) != TAXART_NETTO;
}

/* ---------------------------------------------------------------------- */
int IsDCTaxArtikelWrGrp( struct ZDCART *dc )
{
	return GetTaxKennViaWrGrp ( dc ) != TAXART_NETTO;
}	

/* ---------------------------------------------------------------------- */
/*int IsDCNettoArtikel( struct ZDCART *dc )
{
	if ( strcmp (dc->ZAENDERUNG, ZAENDERUNG_NEU))
		return GetTaxKennViaWrGrp ( dc ) == TAXART_NETTO;
	else
		return GetTaxKennViaBox( dc ) == TAXART_NETTO;
}*/

/* ---------------------------------------------------------------------- */
int IsDCUeberGh( struct ZDCART *dc )
{
	return strcmp( dc->DC_NICHTUEBERGH, "N" ) == 0;
}

/* ---------------------------------------------------------------------- */
int IsDCGrossoNull( double dcGep )
{
    return dcGep >= -0.01 && dcGep <= 0.01;
}

/* ---------------------------------------------------------------------- */
static int IsDCAepNachTaxe( struct ZDCART *dc, int taxmode )
{
   double diff;
   double aep;

   if ( taxmode == TAX_BOX )
       CalcAekAustria( dc->DC_GEP, &aep, dc->DC_DATUMGUELTIGAB, GetTaxKennViaBox( dc ));
   else
       CalcAekAustria( dc->DC_GEP, &aep, dc->DC_DATUMGUELTIGAB, GetTaxKennViaWrGrp( dc ));

   diff = dc->DC_AEP - aep;
   
   if ( diff < -0.005 || diff > 0.005 ) 
	   return 0;
   return 1;
}

/* ---------------------------------------------------------------------- */
static int IsDCAvpNachTaxe( struct ZDCART *dc, int taxmode )
{
   int mwst;
   char btm;
   double diff;
   double avp;

   if ( strcmp( dc->DC_MWST_GH, DCMWST_VERM ) == 0 )        /* Vermindert */
      mwst = TAXTAB_IS_VERMMWST;
   else if ( strcmp( dc->DC_MWST_GH, DCMWST_VOLL ) == 0 )        /* Voll */
      mwst = TAXTAB_IS_VOLLMWST;
   else if ( strcmp( dc->DC_MWST_GH, DCMWST_3RD ) == 0 )        /* 3rd */
	  mwst = TAXTAB_IS_3RD;
   else if (strcmp(dc->DC_MWST_GH, DCMWST_K) == 0)					/* 0 */
	  mwst = TAXTAB_IS_KMWST;

   if ( strcmp(dc->DC_REZEPTZEICHEN, REZEPTZ_BTM) == 0 )
	   btm = '1';
   else
	   btm = '0';
   
   if ( taxmode == TAX_BOX )
       CalcAvkAustriaMwst( dc->DC_AEP, &avp, mwst, dc->DC_DATUMGUELTIGAB, GetTaxKennViaBox( dc ), btm ); 
     else
		CalcAvkAustriaMwst( dc->DC_AEP, &avp, mwst, dc->DC_DATUMGUELTIGAB, GetTaxKennViaWrGrp( dc ), btm  );
   

   diff = dc->DC_AVP - avp;
   
   if ( diff < -0.005 || diff > 0.005 ) 
	   return 0;

   return 1;
}

/* ---------------------------------------------------------------------- */
int TestTaxArtikelBox( struct ZDCART *dc )
{
  if ( ! IsDCGrossoNull( dc->DC_GEP ) )  /* DC-Grosso != 0 */
  {
	if ( ! IsDCAepNachTaxe( dc, TAX_BOX ) || !IsDCAvpNachTaxe( dc, TAX_BOX ) )
    {
		SetDCTrueFalse( 1, dc->NB_DC_ZWING, ZW_PREISE_TAX_BOX );
		return 0;
    }
  }
  else   /* DC-Grosso = 0 */
  {
    if ( IsDCUeberGh( dc ) || !IsDCAvpNachTaxe( dc, TAX_BOX ) )
    {
      SetDCTrueFalse( 1, dc->NB_DC_ZWING, ZW_PREISE_TAX_BOX );
      return 0;
    }
  }
  return 1;
}

/* ---------------------------------------------------------------------- */
int TestTaxArtikelWrGrp( struct ZDCART *dc )
{
  if ( ! IsDCGrossoNull( dc->DC_GEP ) )  /* DC-Grosso != 0 */
  {
    if ( ! IsDCAepNachTaxe( dc, TAX_WRGRP ) || !IsDCAvpNachTaxe( dc, TAX_WRGRP ) )
    {
		SetDCTrueFalse( 1, dc->NB_DC_ZWING, ZW_PREISE_TAX_WRGRP );
		return 0;
    }
  }
  else   /* DC-Grosso = 0 */
  {
	if ( IsDCUeberGh( dc ) || !IsDCAvpNachTaxe( dc, TAX_WRGRP ) )
    {
      SetDCTrueFalse( 1, dc->NB_DC_ZWING, ZW_PREISE_TAX_WRGRP );
      return 0;
    }
  }
  return 1;
}

/* ---------------------------------------------------------------------- */
int TestTaxArtikelNeu( struct ZDCART *dc )
{
  if ( ! IsDCGrossoNull( dc->DC_GEP ) )
  {
    if ( ! IsDCAepNachTaxe( dc, TAX_BOX ) || !IsDCAvpNachTaxe( dc, TAX_BOX ) )
    {
	  SetDCTrueFalse( 1, dc->NB_DC_ZWING, ZW_PREISE_TAX_BOX );
      return 0;
    }
  }
  else
  {
    if ( IsDCUeberGh( dc ) || !IsDCAvpNachTaxe( dc, TAX_BOX ) )
    {
      SetDCTrueFalse( 1, dc->NB_DC_ZWING, ZW_PREISE_TAX_BOX );
      return 0;
    }
  }
  return 1;
}

/* ---------------------------------------------------------------------- */
int TestPreis_Aenderung( struct ZDCART *dc,
                         long ProzentPM,
                         long dc_gro, long dc_aep, long dc_avp, 
                         long art_gro, long art_aep, long art_avp, char taxkzwrgrp )
{
  taxkz_wrgrp = taxkzwrgrp;

  if ( IsDCTaxArtikelBox( dc ) )
  {
    TestTaxArtikelBox( dc );
  }
  if ( IsDCTaxArtikelWrGrp( dc ) )
  {
    TestTaxArtikelWrGrp( dc );
  }
  return 0;
}


/* ---------------------------------------------------------------------- */
int TestPreis_Neuaufnahme( struct ZDCART *dc )
{
  if ( IsDCTaxArtikelBox( dc ) )
     return TestTaxArtikelNeu( dc );
  else   /* keine Pruefung bei NichtTaxartikeln */
     return 1;
}
