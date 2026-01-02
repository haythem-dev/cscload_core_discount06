/* ---------------------------------------------------------------------- *
 *   Aufgabe        : generiert die Nachbearbeitungsgruende               *
 *                    bei Datacare-Aenderungen                            *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 31.01.2005                                          *
 *   Autor          : Hörath                                              *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <hdatum/phodate.h>

#include "znb_gen_li.h"

/* ------------------------------------------------------------------- */
struct ERR_MeldungLI PL_MeldungLI[] =
{
	{PL_PHAR		, "PZN: Prüfziffer falsch"},
	{PL_CDSO1		, "allgemeiner Plausi-Fehler"},
	{PL_PRDNO		, "allgemeiner Plausi-Fehler"},
	{PL_SMCAT		, "allgemeiner Plausi-Fehler"},
	{PL_SMNO		, "allgemeiner Plausi-Fehler"},
	{PL_CLINCD		, "allgemeiner Plausi-Fehler"},
	{PL_GRPCD		, "allgemeiner Plausi-Fehler"},
	{PL_SALECD		, "allgemeiner Plausi-Fehler"},
	{PL_VAT			, "allgemeiner Plausi-Fehler"},
	{PL_COOL		, "allgemeiner Plausi-Fehler"},
	{PL_CDBG		, "allgemeiner Plausi-Fehler"},
	{PL_BG			, "allgemeiner Plausi-Fehler"},
	{PL_EXP			, "allgemeiner Plausi-Fehler"},
	{PL_QTY			, "allgemeiner Plausi-Fehler"},
	{PL_DSCRD		, "allgemeiner Plausi-Fehler"},
	{PL_DSCRF		, "allgemeiner Plausi-Fehler"},
	{PL_DSCRLONGD	, "allgemeiner Plausi-Fehler"},
	{PL_DSCRLONGF	, "allgemeiner Plausi-Fehler"},
	{PL_QTYUD		, "allgemeiner Plausi-Fehler"},
	{PL_QTYUF		, "allgemeiner Plausi-Fehler"},
	{PL_PCKTYPD		, "allgemeiner Plausi-Fehler"},
	{PL_PCKTYPF		, "allgemeiner Plausi-Fehler"},
	{PL_NOPCS		, "allgemeiner Plausi-Fehler"},
	{PL_NINCD		, "allgemeiner Plausi-Fehler"},
	{PL_DEPCD		, "allgemeiner Plausi-Fehler"},
	{PL_OUTSAL		, "allgemeiner Plausi-Fehler"},
	{PL_STTOX		, "allgemeiner Plausi-Fehler"},
	{PL_CE			, "allgemeiner Plausi-Fehler"},
	{PL_SMCDAT		, "allgemeiner Plausi-Fehler"},
	{PL_SIST		, "allgemeiner Plausi-Fehler"},
	{PL_ESIST		, "allgemeiner Plausi-Fehler"},
	{PL_BIOCID		, "allgemeiner Plausi-Fehler"},
	{PL_BAGNO		, "allgemeiner Plausi-Fehler"},
	{PL_BAGDOSSIER	, "allgemeiner Plausi-Fehler"},
	{PL_COMPNO		, "allgemeiner Plausi-Fehler"},
	{PL_PHAR2		, "allgemeiner Plausi-Fehler"},
	{PL_VDAT		, "allgemeiner Plausi-Fehler"},
	{PL_PRICE_PEXF	, "allgemeiner Plausi-Fehler"},
	{PL_PRICE_PPUB	, "allgemeiner Plausi-Fehler"},
	{PL_MIGCD		, "allgemeiner Plausi-Fehler"},
	{PL_GENCD		, "allgemeiner Plausi-Fehler"},
	{PL_ATC			, "allgemeiner Plausi-Fehler"},
	{PL_SUPPLNO		, "allgemeiner Plausi-Fehler"},
	{PL_ARTNO1		, "allgemeiner Plausi-Fehler"},
	{PL_BLOOD		, "allgemeiner Plausi-Fehler"},
	{PL_PRDGRPCD	, "allgemeiner Plausi-Fehler"},
	{PL_BIOSIM		, "allgemeiner Plausi-Fehler"},
};

/* ------------------------------------------------------------------- */
struct ERR_MeldungLI ZW_MeldungLI[] =
{
	{ZW_GEP_ERR		, "Änderung Artikelstamm-Grosso auf 0"},
	{ZW_EAN_DIFF    , "Unterschiedliche EAN-NR bei gleicher PZN" },
	{ZW_EAN_MEHRFACH, "Gleiche EAN-NR bei unterschiedlicher PZN" },
	{ZW_PZNNF_GLEICH, "PZN-Vorgänger = PZN" },
	{ZW_HNR_UNSET	, "Hersteller nicht gesetzt" },
	{ZW_CHANGE_BTM	, "Änderung des BTM- Kennzeichens"},
	{ZW_CHANGE_PSYCHOTROP, "Änderung des Psychotrop- Kennzeichens"},
	{ZW_CHANGE_COOL	, "Änderung des Kuehl- Kennzeichens"},
	{ZW_CHANGE_NAME	, "Änderung einer Artikelbezeichnung"},
	{ZW_CHANGE_HNR	, "Änderung des Herstellers"},
	{ZW_CHANGE_AWL	, "Änderung des Ausweichlieferanten"},
	{ZW_GTIN14_EXISTS,"Gleiche GTIN14 bei unterschiedlicher PZN" },
	{ZW_CHANGE_PRICE, "Preisänderung zur manuellen Nachbearbeitung" },
};

/* ------------------------------------------------------------------- */
struct ERR_MeldungLI NZ_MeldungLI[] =
{
	{NZ_GEP_HINW,		"Artikelstamm-Grosso bleibt auf 0"},
	{NZ_AH_PRICE_CHANGE,"Preisänderung bei AH-Artikel"},
	{NZ_CHANGE_AH,		"Änderung des AH- Datums"},
	{NZ_CHANGE_RR,		"Änderung des RR- Datums"},
	{NZ_CHANGE_IKSCODE,	"Änderung des IKS- Codes"},
	{NZ_PZNNF_NVOR   ,  "Kein Artikelstamm fuer PZN-Vorgänger vorhanden" },
	{NZ_HINT_BLOOD,     "Hinweis auf Blutprodukt" },
};

/* ------------------------------------------------------------------- */
char *GetLIErrMeld( struct ERR_MeldungLI *err, int key )
{
  int i;
  i = 0;
  
  while ( err[i].key != NO_WERT && err[i].key != key ) 
	  i++;

  if ( err[i].key == key )
    return err[i].meldung;
  else
    return "";
}

/* ------------------------------------------------------------------- */
char *Get_ZW_ErrMeldLI( int key )
{
  return GetLIErrMeld( ZW_MeldungLI, key );
}

/* ------------------------------------------------------------------- */
char *Get_NZ_ErrMeldLI( int key )
{
  return GetLIErrMeld( NZ_MeldungLI, key );
}

/* ------------------------------------------------------------------- */
char *Get_PL_ErrMeldLI( int key )
{
  return GetLIErrMeld( PL_MeldungLI, key );
}

/* ------------------------------------------------------------------- */
void SetLITrueFalse( int true_false, char *Feld, int key )
{
   if ( Feld[key] != NB_PL_NO_VAL )
      Feld[key] = ( true_false ? NB_PL_ERR : NB_PL_OK );
}

/* ------------------------------------------------------------------- */
void SetLIErr( char* Wert, char *ZulWerte, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     int i;
     i = 0;
     
	 while ( ZulWerte[i] && ZulWerte[i] != *Wert ) 
		 i++;
     
	 Feld[key] = ( ZulWerte[i] ? NB_PL_OK : NB_PL_ERR );

	 if (strcmp(Wert, "") == 0)
	 {
		strcpy(	Wert, " " );
		Feld[key] = NB_PL_OK;
	 }
  }
}

/* ------------------------------------------------------------------- */
void SetLIErrInt( int Wert, char *ZulWerte, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     int i;
     i = 0;
     while ( ZulWerte[i] )
	 {
		 if (((int)ZulWerte[i] - 48) == Wert)
			break;

		 i++;
	 }

     Feld[key] = ( ZulWerte[i] ? NB_PL_OK : NB_PL_ERR );
  }
}

/* ------------------------------------------------------------------- */
void SetLI2Err( char* Wert, char *ZulWerte, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     int i;
     i = 0;
     while ( ZulWerte[i] && memcmp( &ZulWerte[i], Wert, 2 ) != 0 ) i += 2;
     Feld[key] = ( ZulWerte[i] ? NB_PL_OK : NB_PL_ERR );
  }
}

/* ------------------------------------------------------------------- */
void SetLINumErr( long Wert, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     if (  Wert >= 0 )
        Feld[key] = NB_PL_OK;
     else
        Feld[key] = NB_PL_ERR;
  }
}

/* ------------------------------------------------------------------- */
void SetLIPreisErr( double Wert, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     if (  Wert > -0.0001 )  
        Feld[key] = NB_PL_OK;
     else
        Feld[key] = NB_PL_ERR;
  }
}

/* ------------------------------------------------------------------- */
void SetLINumBlankErr( char* Wert, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     int i;
     i = 0;
     while ( Wert[i] && ((Wert[i]>='0' && Wert[i]<='9') || Wert[i]==' ' || Wert[i]==',' || Wert[i]=='.') ) i++;
     Feld[key] = ( Wert[i] ? NB_PL_ERR : NB_PL_OK );
  }
}

/* ------------------------------------------------------------------- */
void SetLIGroesser( double Wert1, double Wert2, char *Feld, int key )
{
  if ( Wert1 >= Wert2 )
     Feld[key] = NB_PL_ERR;
   else
     Feld[key] = NB_PL_OK;
}

/* ------------------------------------------------------------------- */
int IsLIFeldErr( char *Feld, int key )
{
	if ( Feld[key] == NB_PL_OK )
		return 0;
	
	if ( Feld[key] == NB_PL_NO_VAL )
		return 0;

	return 1;
}

/* ------------------------------------------------------------------- */
int IsLIErr( char *Feld )
{
    int i;
    i = 0;

	while ( Feld[i] && ( Feld[i] == NB_PL_NO_VAL || Feld[i] == NB_PL_OK ) ) 
		i++;
    return (char) (Feld[i] ? 1 : 0 );
}

/* ------------------------------------------------------------------- */
void SetLIGueltigabErr( long datum, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     if (  datum == 0 )
        Feld[key] = NB_PL_ERR;
     else
        Feld[key] = NB_PL_OK;
  }
}

/* ------------------------------------------------------------------- */
void SetLIGleich( char* Wert1, char* Wert2, char *Feld, int key )
{
  if ( strcmp( Wert1, Wert2 ) == 0 )
     Feld[key] = NB_PL_ERR;
   else
     Feld[key] = NB_PL_OK;
}

