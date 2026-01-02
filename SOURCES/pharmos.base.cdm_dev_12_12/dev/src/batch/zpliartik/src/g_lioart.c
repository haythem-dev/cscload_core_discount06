/* ---------------------------------------------------------------------- *
 * Aufgabe        : Funktionalität zur Interaktion mit der Datenbank      *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                               *
 * erstellt am    : 26.01.2005                                            *
 * ---------------------------------------------------------------------- */
/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include <hdatum/phodate.h>

#include <voodoo_table_header/clioart.h>
#include <voodoo_table_header/cliart.h>

#include "li_form.h"
#include "znb_gen_li.h"
#include "g_lioart.h"
#include "g_liartik.h"


/* ---------------------------------------------------------------------- */
void ze_lcpy( char *s1, char ze, int lng )
{
  while ( lng-- > 0 ) *s1++ = ze;
   *s1 = '\0';
}

/* ---------------------------------------------------------------------- */
static void str_lcpy( char *s1, char *s2, int lng1 )
{
   int lng2;
   lng2 = (int) strlen( s2 );
   if ( lng2 < lng1 )
   {
      while ( lng2-- > 0 ) { *s1++ = *s2++; lng1--; }
      while ( lng1-- > 0 ) *s1++ = ' ';
   }
   else
      while ( lng1-- > 0 ) *s1++ = *s2++;
   *s1 = '\0';
}

/* --- FehlerFelder initialisieren --- */
static char  NB_PLAUSI[ POSANZ_CLIOART + 1 + POSANZ_UNUSED];
/* ---------------------------------------------------------------------- */
static void ClearNbPlausi( int pos )
{
   if (m_eFileArt == PRODUCT_PRD && pos != PL_PHAR)
	    NB_PLAUSI[ pos ] = NB_PL_NO_VAL;
   else
		NB_PLAUSI[ pos ] = NB_PL_OK;
}

/* ---------------------------------------------------------------------- */
static void InitNbPlausi( )
{
   int i;

   ze_lcpy( NB_PLAUSI, NB_PL_ERR, POSANZ_CLIOART + POSANZ_UNUSED );
   ClearNbPlausi( PL_PHAR );

   // Clear Plausi für Felder, bei denen aktuell keine Plausi- Prüfung erfolgt !!!
	ClearNbPlausi( PL_DSCRD );
	ClearNbPlausi( PL_DSCRF );
	ClearNbPlausi( PL_DSCRLONGD );
	ClearNbPlausi( PL_DSCRLONGF );
	ClearNbPlausi( PL_QTYUD );
	ClearNbPlausi( PL_QTYUF );
	ClearNbPlausi( PL_PCKTYPD );
	ClearNbPlausi( PL_PCKTYPF );
	ClearNbPlausi( PL_BAGNO );
	//ClearNbPlausi( PL_CDSO1 );

   /* letzte Stellen auf 9 setzen! - werden noch nicht benötigt!*/
   for (i = PL_AFTER_LAST; i <= POSANZ_CLIOART + POSANZ_UNUSED - 1; i++)
   {
		NB_PLAUSI[ i ] = NB_PL_NO_VAL;
   }
}

/* ---------- Test LI auf "Keine Aenderung" ---------------------------- */
static int TestNoChangeC( char *LIwert, char *Owert, int pos, short oArtExists )
{
   Trim(Owert);
   Trim(LIwert);
   
   if ( strcmp(LIwert,Owert) == 0 && (oArtExists == 1 || strcmp(LIwert,"") != 0) )
   {
     NB_PLAUSI[ pos ] = NB_PL_NO_VAL;
     return 1;
   }
   NB_PLAUSI[ pos ] = NB_PL_OK;
   return 0;
}

static int TestNoChangeL( long LIwert, long Owert, int pos, short oArtExists )
{
   if ( LIwert == Owert && (oArtExists == 1 || LIwert != 0) )
   {
     NB_PLAUSI[ pos ] = NB_PL_NO_VAL;
     return 1;
   }
   NB_PLAUSI[ pos ] = NB_PL_OK;
   return 0;
}

static int TestNoChangeD( double LIwert, double Owert, int pos, short oArtExists )
{
   long lLI = (long)(LIwert * 100);
   long lO = (long)(Owert * 100);
	
   if ( lLI == lO && (oArtExists == 1 || lLI != 0) ) 
   {
     NB_PLAUSI[ pos ] = NB_PL_NO_VAL;
     return 1;
   }
   NB_PLAUSI[ pos ] = NB_PL_OK;
   return 0;
}

/* ---------- Referenz auf Plausistring ---------------------------- */
void CopyPlausi( char *NB_PLAUSI_Cliart )
{
   int i;
   i = 0;
   while ( NB_PLAUSI_Cliart[i] != '\0' )
   {
     NB_PLAUSI_Cliart[ i ] = NB_PLAUSI[ i ];
     i++;
   }
}

/* ---------------------------------------------------------------------- */
int LIOartFill( struct CLIOART *lio, struct CLIART *li, long tages_datum, char* errmld, short oArtExists )
{
	char *wert;
	//char wert1[5+1];
	long lwert;
	double dwert;

	if (oArtExists == 0)
		lio->DATUM_ANLAGE = tages_datum;

	lio->DATUM_AENDER = tages_datum;
   
   /* --- FehlerFelder initialisieren --- */
	if (update_cliart == 0)
		InitNbPlausi( ); // nur wenn cliart noch nicht vorhanden
	else
		strcpy (NB_PLAUSI, li->NB_LI_PLAUSI); // ansonsten bereits vorhandenen cliart.NB_PLAUSI setzen !!! 

/* ---- auf Aenderungen prüfen ------ */

	switch (m_eFileArt)
	{
	case ARTICLE_ART:	
		/* CDSO1 */
		if ( ( wert = li->CDSO1) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->CDSO1, PL_CDSO1, oArtExists ) )
			str_lcpy( lio->CDSO1, wert, L_CLIOART_CDSO1 );

		/* PRDNO */
		lwert = li->PRDNO;
		if ( !TestNoChangeL( lwert, lio->PRDNO, PL_PRDNO, oArtExists ) )
			lio->PRDNO = lwert;

		/* SMCAT */
		if ( ( wert = li->SMCAT) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->SMCAT, PL_SMCAT, oArtExists ) )
			str_lcpy( lio->SMCAT, wert, L_CLIOART_SMCAT );

		/* SMNO */
		lwert = li->SMNO;
		if ( !TestNoChangeL( lwert, lio->SMNO, PL_SMNO, oArtExists ) )
			lio->SMNO = lwert;

		/* CLINCD */
		if ( ( wert = li->CLINCD) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->CLINCD, PL_CLINCD, oArtExists ) )
			str_lcpy( lio->CLINCD, wert, L_CLIOART_CLINCD );

		/* SALECD */
		if ( ( wert = li->SALECD) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->SALECD, PL_SALECD, oArtExists ) )
			str_lcpy( lio->SALECD, wert, L_CLIOART_SALECD );

		/* GRPCD */
		if ( ( wert = li->GRPCD) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->GRPCD, PL_GRPCD, oArtExists ) )
			str_lcpy( lio->GRPCD, wert, L_CLIOART_GRPCD );

		/* VAT */
		lwert = li->VAT;
		if ( !TestNoChangeL( lwert, lio->VAT, PL_VAT, oArtExists ) )
			lio->VAT = (short)lwert;

		/* COOL */
		if ( ( wert = li->COOL) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->COOL, PL_COOL, oArtExists ) )
			str_lcpy( lio->COOL, wert, L_CLIOART_COOL );

		/* CDBG */
		if ( ( wert = li->CDBG) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->CDBG, PL_CDBG, oArtExists ) )
			str_lcpy( lio->CDBG, wert, L_CLIOART_CDBG );

		/* BG */
		if ( ( wert = li->BG) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->BG, PL_BG, oArtExists ) )
			str_lcpy( lio->BG, wert, L_CLIOART_BG );

		/* EXP */
		lwert = li->EXP;
		if ( !TestNoChangeL( lwert, lio->EXP, PL_EXP, oArtExists ) )
			lio->EXP = (short)lwert;

		/* QTY */
		dwert = li->QTY;
		if ( !TestNoChangeD( dwert, lio->QTY, PL_QTY, oArtExists ) )
			lio->QTY = dwert;

		/* DSCRD */
		if ( ( wert = li->DSCRD) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->DSCRD, PL_DSCRD, oArtExists ) )
			str_lcpy( lio->DSCRD, wert, L_CLIOART_DSCRD );

		/* DSCRF */
		if ( ( wert = li->DSCRF) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->DSCRF, PL_DSCRF, oArtExists ) )
			str_lcpy( lio->DSCRF, wert, L_CLIOART_DSCRF );

		/* DSCRLONGD */
		if ( ( wert = li->DSCRLONGD) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->DSCRLONGD, PL_DSCRLONGD, oArtExists ) )
			str_lcpy( lio->DSCRLONGD, wert, L_CLIOART_DSCRLONGD );

		/* DSCRLONGF */
		if ( ( wert = li->DSCRLONGF) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->DSCRLONGF, PL_DSCRLONGF, oArtExists ) )
			str_lcpy( lio->DSCRLONGF, wert, L_CLIOART_DSCRLONGF );

		/* QTYUD */
		if ( ( wert = li->QTYUD) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->QTYUD, PL_QTYUD, oArtExists ) )
			str_lcpy( lio->QTYUD, wert, L_CLIOART_QTYUD );

		/* QTYUF */
		if ( ( wert = li->QTYUF) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->QTYUF, PL_QTYUF, oArtExists ) )
			str_lcpy( lio->QTYUF, wert, L_CLIOART_QTYUF );

		/* PCKTYPD */
		if ( ( wert = li->PCKTYPD) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->PCKTYPD, PL_PCKTYPD, oArtExists ) )
			str_lcpy( lio->PCKTYPD, wert, L_CLIOART_PCKTYPD );

		/* PCKTYPF */
		if ( ( wert = li->PCKTYPF) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->PCKTYPF, PL_PCKTYPF, oArtExists ) )
			str_lcpy( lio->PCKTYPF, wert, L_CLIOART_PCKTYPF );

		/* NOPCS */
		lwert = li->NOPCS;
		if ( !TestNoChangeL( lwert, lio->NOPCS, PL_NOPCS, oArtExists ) )
			lio->NOPCS = (short)lwert;

		/* DEPCD */
		if ( ( wert = li->DEPCD) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->DEPCD, PL_DEPCD, oArtExists ) )
			str_lcpy( lio->DEPCD, wert, L_CLIOART_DEPCD );

		/* OUTSAL */
		lwert = li->OUTSAL;
		if ( !TestNoChangeL( lwert, lio->OUTSAL, PL_OUTSAL, oArtExists ) )
			lio->OUTSAL = lwert;

		/* STTOX */
		if ( ( wert = li->STTOX) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->STTOX, PL_STTOX, oArtExists ) )
			str_lcpy( lio->STTOX, wert, L_CLIOART_STTOX );

		/* CE */
		if ( ( wert = li->CE) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->CE, PL_CE, oArtExists ) )
			str_lcpy( lio->CE, wert, L_CLIOART_CE );

		/* SMCDAT */
		lwert = li->SMCDAT;
		if ( !TestNoChangeL( lwert, lio->SMCDAT, PL_SMCDAT, oArtExists ) )
			lio->SMCDAT = lwert;

		/* SIST */
		lwert = li->SIST;
		if ( !TestNoChangeL( lwert, lio->SIST, PL_SIST, oArtExists ) )
			lio->SIST = lwert;

		/* ESIST */
		lwert = li->ESIST;
		if ( !TestNoChangeL( lwert, lio->ESIST, PL_ESIST, oArtExists ) )
			lio->ESIST = lwert;

		/* BIOCID */
		lwert = li->BIOCID;
		if ( !TestNoChangeL( lwert, lio->BIOCID, PL_BIOCID, oArtExists ) )
			lio->BIOCID = (short)lwert;

		/* BAGNO */
		if ( ( wert = li->BAGNO) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->BAGNO, PL_BAGNO, oArtExists ) )
			str_lcpy( lio->BAGNO, wert, L_CLIOART_BAGNO );

	case ARTICLE_ARTCOMP:

		/* COMPNO */
		lwert = li->COMPNO;
		if ( !TestNoChangeL( lwert, lio->COMPNO, PL_COMPNO, oArtExists ) )
			lio->COMPNO = lwert;

		/* ARTNO1 */
		if ( ( wert = li->ARTNO1) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->ARTNO1, PL_ARTNO1, oArtExists ) )
			str_lcpy( lio->ARTNO1, wert, L_CLIOART_ARTNO1 );

		/* SUPPLNO */
		lwert = li->SUPPLNO;
		if ( !TestNoChangeL( lwert, lio->SUPPLNO, PL_SUPPLNO, oArtExists ) )
			lio->SUPPLNO = lwert;


		if (li->HERSTELLER_NR <= 0)
			lio->HERSTELLER_NR = -1;
		else
			lio->HERSTELLER_NR = li->HERSTELLER_NR;
		
		break;

	case ARTICLE_ARTBAR:

		/* BC */

		if (bctype_ean == 1)
		{
			if ( (wert = li->BC) == NULL)
				return 1;

			if ( !TestNoChangeC( wert, lio->BC, PL_BC, oArtExists ) )
				str_lcpy( lio->BC, wert, L_CLIOART_BC );
		}
		else
		{
			if ( (wert = li->GTIN14) == NULL)
				return 1;

			if ( !TestNoChangeC( wert, lio->GTIN14, PL_GTIN14, oArtExists ) )
				str_lcpy( lio->GTIN14, wert, L_CLIOART_GTIN14 );
		}

		break;

	case ARTICLE_ARTCH:

		/* PHAR2 */
		lwert = li->PHAR2;
		if ( !TestNoChangeL( lwert, lio->PHAR2, PL_PHAR2, oArtExists ) )
			lio->PHAR2 = lwert;

		break;

	case ARTICLE_ARTPRI:
	case ARTICLE_ARTPRI_NEW:

		/* VDAT */
		lwert = li->VDAT;
		// if both prices are delivered, VDAT always gets status "unchanged" (not a real problem, because this field is always editable on GUI)
		if ( !TestNoChangeL( lwert, lio->VDAT, PL_VDAT, oArtExists ) ) 
			lio->VDAT = lwert;

		if (pricetype_exf == 1)
		{
			/* PRICE */
			dwert = li->PRICE_PEXF;
			if ( !TestNoChangeD( dwert, lio->PRICE_PEXF, PL_PRICE_PEXF, oArtExists ) )
				lio->PRICE_PEXF = dwert;
		}
		else
		{
			/* PRICE */
			dwert = li->PRICE_PPUB;
			if ( !TestNoChangeD( dwert, lio->PRICE_PPUB, PL_PRICE_PPUB, oArtExists ) )
				lio->PRICE_PPUB = dwert;
		}

		break;
	case ARTICLE_ARTMIG:

		/* MIGCD */
		if ( ( wert = li->MIGCD) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->MIGCD, PL_MIGCD, oArtExists ) )
			str_lcpy( lio->MIGCD, wert, L_CLIOART_MIGCD );

		break;

	case ARTICLE_ARTINS:

		/* NINCD */
		lwert = li->NINCD;
		if ( !TestNoChangeL( lwert, lio->NINCD, PL_NINCD, oArtExists ) )
			lio->NINCD = (short)lwert;

		break;

	case PRODUCT_PRD:
		/* MDCLASS */
		strcpy(lio->MDCLASS, li->MDCLASS);

		/* GENCD */
		if ( ( wert = li->GENCD) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->GENCD, PL_GENCD, oArtExists ) )
			str_lcpy( lio->GENCD, wert, L_CLIOART_GENCD );
		
		/* ATC */
		if ( ( wert = li->ATC) == NULL ) 
			return 1;
		if ( !TestNoChangeC( wert, lio->ATC, PL_ATC, oArtExists ) )
			str_lcpy( lio->ATC, wert, L_CLIOART_ATC );

		/* BLOOD */
		lwert = li->BLOOD; 
		if ( !TestNoChangeL( lwert, lio->BLOOD, PL_BLOOD, oArtExists ) )
			lio->BLOOD = (short)lwert;

		/* BIOSIM */
		if ((wert = li->BIOSIM) != NULL)
		{
			strcpy(lio->BIOSIM, li->BIOSIM);
		}

		/* MDATTR */
		lio->SERIAL_NUMBER_TRACKING = li->SERIAL_NUMBER_TRACKING;

		break;

	case PRODUCT_PRD_CPT:
		// no original for prdgrpcd = nothing to do
		break;

	case ARTICLE_ARTDAN:

		/* SIGNALWORD */
		strcpy(lio->CDVAL, li->CDVAL);

		/* EUH Hazard Statement */
		if (0 != strcmp(m_szEUHazard, "INIT"))         // Es gab mind. einen Typ 24
		{
			strcpy(lio->HAZARD_STMT, m_szEUHazard);
		}
		else
		{
			strcpy(lio->HAZARD_STMT, li->HAZARD_STMT); // Alter Wert; bei Neuanlage ohne Typ 24 leer
		}

		/* PICTOGRAM01_FLAG */
		lwert = li->PICTOGRAM01_FLAG;
		lio->PICTOGRAM01_FLAG = (short)lwert;

		/* PICTOGRAM02_FLAG */
		lwert = li->PICTOGRAM02_FLAG;
		lio->PICTOGRAM02_FLAG = (short)lwert;

		/* PICTOGRAM03_FLAG */
		lwert = li->PICTOGRAM03_FLAG;
		lio->PICTOGRAM03_FLAG = (short)lwert;

		/* PICTOGRAM04_FLAG */
		lwert = li->PICTOGRAM04_FLAG;
		lio->PICTOGRAM04_FLAG = (short)lwert;

		/* PICTOGRAM05_FLAG */
		lwert = li->PICTOGRAM05_FLAG;
		lio->PICTOGRAM05_FLAG = (short)lwert;

		/* PICTOGRAM06_FLAG */
		lwert = li->PICTOGRAM06_FLAG;
		lio->PICTOGRAM06_FLAG = (short)lwert;

		/* PICTOGRAM07_FLAG */
		lwert = li->PICTOGRAM07_FLAG;
		lio->PICTOGRAM07_FLAG = (short)lwert;

		/* PICTOGRAM08_FLAG */
		lwert = li->PICTOGRAM08_FLAG;
		lio->PICTOGRAM08_FLAG = (short)lwert;

		/* PICTOGRAM09_FLAG */
		lwert = li->PICTOGRAM09_FLAG;
		lio->PICTOGRAM09_FLAG = (short)lwert;

		break;

		//	/* GS_EXPLOSION */
		//	if((wert = li->GS_EXPLOSION) == NULL)
		//		return 1;
		//	if(!TestNoChangeC(wert, lio->GS_EXPLOSION, PL_GS_EXPLOSION, oArtExists))
		//		str_lcpy(lio->GS_EXPLOSION, wert, L_CLIART_GS_EXPLOSION);

		//	/* GS_HOCHENTZ */
		//	if((wert = li->GS_HOCHENTZ) == NULL)
		//		return 1;
		//	if(!TestNoChangeC(wert, lio->GS_HOCHENTZ, PL_GS_HOCHENTZ, oArtExists))
		//		str_lcpy(lio->GS_HOCHENTZ, wert, L_CLIART_GS_HOCHENTZ);

		//	/* GS_LEICHTENTZ */
		//	if((wert = li->GS_LEICHTENTZ) == NULL)
		//		return 1;
		//	if(!TestNoChangeC(wert, lio->GS_LEICHTENTZ, PL_GS_LEICHTENTZ, oArtExists))
		//		str_lcpy(lio->GS_LEICHTENTZ, wert, L_CLIART_GS_LEICHTENTZ);

		//	/* GS_BRAND */
		//	if((wert = li->GS_BRAND) == NULL)
		//		return 1;
		//	if(!TestNoChangeC(wert, lio->GS_BRAND, PL_GS_BRAND, oArtExists))
		//		str_lcpy(lio->GS_BRAND, wert, L_CLIART_GS_BRAND);

		//	/* GS_AETZEND */
		//	if((wert = li->GS_AETZEND) == NULL)
		//		return 1;
		//	if(!TestNoChangeC( wert, lio->GS_AETZEND, PL_GS_AETZEND, oArtExists))
		//		str_lcpy(lio->GS_AETZEND, wert, L_CLIART_GS_AETZEND);

		//	/* GS_SEHRGIFTIG */
		//	if((wert = li->GS_SEHRGIFTIG) == NULL)
		//		return 1;
		//	if(!TestNoChangeC( wert, lio->GS_SEHRGIFTIG, PL_GS_SEHRGIFTIG, oArtExists))
		//		str_lcpy(lio->GS_SEHRGIFTIG, wert, L_CLIART_GS_SEHRGIFTIG);

		//	/* GS_GIFTIG */
		//	if((wert = li->GS_GIFTIG) == NULL)
		//		return 1;
		//	if(!TestNoChangeC( wert, lio->GS_GIFTIG, PL_GS_GIFTIG, oArtExists))
		//		str_lcpy(lio->GS_GIFTIG, wert, L_CLIART_GS_GIFTIG);

		//	/* GS_GESUNDHSCH */
		//	if((wert = li->GS_GESUNDHSCH) == NULL)
		//		return 1;
		//	if(!TestNoChangeC( wert, lio->GS_GESUNDHSCH, PL_GS_GESUNDHSCH, oArtExists))
		//		str_lcpy(lio->GS_GESUNDHSCH, wert, L_CLIART_GS_GESUNDHSCH);

		//	/* GS_REIZEND */
		//	if((wert = li->GS_REIZEND) == NULL)
		//		return 1;
		//	if(!TestNoChangeC( wert, lio->GS_REIZEND, PL_GS_REIZEND, oArtExists))
		//		str_lcpy(lio->GS_REIZEND, wert, L_CLIART_GS_REIZEND);

		//	/* GS_UMWELT */
		//	if((wert = li->GS_UMWELT) == NULL)
		//		return 1;
		//	if(!TestNoChangeC( wert, lio->GS_UMWELT, PL_GS_UMWELT, oArtExists))
		//		str_lcpy(lio->GS_UMWELT, wert, L_CLIART_GS_UMWELT);

	case ARTICLE_ARTSL:
		/* BAGDOSSIER */
		lwert = li->BAGDOSSIER;
		if (!TestNoChangeL(lwert, lio->BAGDOSSIER, PL_BAGDOSSIER, oArtExists))
			lio->BAGDOSSIER = lwert;
		break;

	case ARTICLE_ARTADR:

		/* KL/KC/VG */
		strcpy(lio->LAGERKLASSE, li->LAGERKLASSE);
		strcpy(lio->GG_KLASSCODE, li->GG_KLASSCODE);
		strcpy(lio->GG_VERPACKCODE, li->GG_VERPACKCODE);

		/* G_UN_NR */
		strcpy(lio->G_UN_NR, li->G_UN_NR);

		break;

	case ARTICLE_REGULATIONS:
		/* FMD_FLAG */
		lwert = li->FMD_FLAG;
		if (!TestNoChangeL(lwert, lio->FMD_FLAG, PL_FMD_FLAG, oArtExists))
			lio->FMD_FLAG = (short)lwert;
		break;

	case ARTICLE_SDS:
		/* SDS_DATE_DE */
		lwert = li->SDS_DATE_DE;
		if ( !TestNoChangeL(lwert, lio->SDS_DATE_DE, PL_SDS_DATE_DE, oArtExists))
			lio->SDS_DATE_DE = (long)lwert;

		/* SDS_DATE_IT */
		lwert = li->SDS_DATE_IT;
		if (!TestNoChangeL(lwert, lio->SDS_DATE_IT, PL_SDS_DATE_IT, oArtExists))
			lio->SDS_DATE_IT = (long)lwert;

		/* SDS_DATE_EN */
		lwert = li->SDS_DATE_EN;
		if (!TestNoChangeL(lwert, lio->SDS_DATE_EN, PL_SDS_DATE_EN, oArtExists))
			lio->SDS_DATE_EN = (long)lwert;

		/* SDS_DATE_FR */
		lwert = li->SDS_DATE_FR;
		if (!TestNoChangeL(lwert, lio->SDS_DATE_FR, PL_SDS_DATE_FR, oArtExists))
			lio->SDS_DATE_FR = (long)lwert;

		break;
	default:
		break;
	}

	return 0;
}
