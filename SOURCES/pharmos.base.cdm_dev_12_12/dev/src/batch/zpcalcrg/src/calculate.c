/* ---------------------------------------------------------------------- *
 *                        C A L C U L A T E . C                           *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Rabattgruppenberechnung Frankreich                           *
 * ---------------------------------------------------------------------- *
 * Autor  :  Raab                                                         *
 * Anfang :  18.01.2007                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <phodate.h>
#include <phozeit.h>
#include <libscsvoodoo.h>

#include <wpp_prot.h>
#include <wpp_dbas.h>
#include <math.h>

#include <zartprei.h>
#include <zartikel.h>
#include <zartfrance.h>
#include <zartwg.h>

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

void Runden_Modf( double *wert, int stellen );

/* ----------------- Funktion ------------------------ */

static char *	user			= "zpcalcrg";

static int		fd_zartpreis	= -1;
static int		fd_zartwg		= -1;

static long		datum_von		= -1;
static long		datum_bis		= -1;
static long		anz_calculated	= 0;
static long		anz_ok			= 0;
static long		anz_nix			= 0;

static double	count_cdiscount;
/* static double	count_cdiscgrpmem; */

static struct	ZARTWG			BufZartwg;
static struct	ZARTWG			BufZartwgOld;

static struct SELBUF {
       long    ARTIKEL_NR;
/*     char    WARENGRUPPE [3]; */
       char    WARENGRUPPE [6];
       char    BTM [2];
       char    KUEHLARTIKEL [2];
       char    PRODUKTART [2];
       char    REIMBURSEMENT_TYPE [2];
} SelBuf;
		
static struct	ZARTPREIS		BufZartpreis;

/* ---------------------------------------- */
static void Init( )
{
	fd_zartpreis		= -1;
	fd_zartwg			= -1;
}

/* ---------------------------------------- */
static void Free( )
{
    if ( fd_zartpreis >= 0 )
        CloseOneBufferDesc( fd_zartpreis );
    fd_zartpreis = -1;

	if ( fd_zartwg >= 0 )
        CloseOneBufferDesc( fd_zartwg );
    fd_zartwg = -1;
}

/* ---------------------------------------- */
int GetBufferDesc_Zartpreis( char *cErrmld )
{
   char *tabelle = "zartpreis";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_zartpreis >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zartpreis, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zartpreis = -1;
     return -1;
   }
   return 0;
}

/* ---------------------------------------- */
int GetBufferDesc_Zartwg( char *cErrmld )
{
   char *tabelle = "zartwg";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_zartwg >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zartwg, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zartwg = -1;
     return -1;
   }

   return 0;
}

/* ---------------------------------------- */
static long ReadRecord_Zartwg( long artikel_nr, char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	sprintf( PrimeKeyCond, "ARTIKEL_NR = %ld and ART = '9'", artikel_nr );

	lStatus = FdReadRecord( fd_zartwg, PrimeKeyCond,
							&BufZartwgOld, buf );
	
	return lStatus;
}

/* ---------------------------------------- */
static long ReadRecord_ZartPreisCurrent( long artikel_nr, char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	long tagesdatum;
	
	/* einen Tag addieren, damit bei der Urladung Preise zum kommenden Monatsersten schon berücksichtigt werden */
	tagesdatum = AddDayToPhoDate(GetPhoDate(), 1);
	/* tagesdatum = GetPhoDate(); */

	if (datum_bis == 0)
		sprintf( PrimeKeyCond, "ARTIKEL_NR = %ld and DATUMGUELTIGAB <= %ld ORDER BY DATUMGUELTIGAB desc",
				artikel_nr, tagesdatum );
	else
		sprintf( PrimeKeyCond, "ARTIKEL_NR = %ld and DATUMGUELTIGAB <= %ld ORDER BY DATUMGUELTIGAB desc",
				artikel_nr, datum_bis );

	FdInitTabBuf( fd_zartpreis, &BufZartpreis );

	lStatus = FdReadRecord( fd_zartpreis, PrimeKeyCond,
							  &BufZartpreis, buf );
	
	return lStatus;
}

/* ---------------------------------------- */
static long ReadCountCdiscount( long artikel_nr, double *dCount, char *buf )
{
	long s;
   
	sprintf( buf, "select count(*) from cdiscount where PHARMACYGROUPID = '700' and "
				  "ARTICLENO = %ld ", artikel_nr );

	s = SqlRead( buf, dCount, NULL ); 
   
	if ( s != 0 )
	{
		strcpy( buf, "CDISCOUNT\n" );
		strcat( buf, DynErrmld() );
	}

	return s;
}

/* ---------------------------------------- */
static long ReadCountCdiscgrpmem( long artikel_nr, long rabattgruppe, double *dCount, char *buf )
{
	long s;
   
	sprintf( buf, "select count(*) from cdiscgrpmem where DISCOUNTGRPNO in "
				  "(select DISCOUNTGRPNO from cdiscgrp where DISCOUNTGRPTYPE = 4) and "
				  "DISCOUNTGRPNO = %ld and ARTICLENO = %ld ", rabattgruppe, artikel_nr );

	s = SqlRead( buf, dCount, NULL ); 
   
	if ( s != 0 )
	{
		strcpy( buf, "CDISCGRPMEM\n" );
		strcat( buf, DynErrmld() );
	}

	return s;
}

/* ---------------------------------------- */
static long StoreRecord_Zartwg( long artikel_nr, short sRabattgruppe, char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	char Rabattgruppe[4];
	
	sprintf(Rabattgruppe, "%-3.3ld", sRabattgruppe);

	lStatus = ReadRecord_Zartwg (artikel_nr, buf);

	/* wenn noch keine Rabattgruppe da, auf jeden Fall neue schreiben */
	if ( lStatus == 100 )
	{
		FdInitTabBuf( fd_zartwg, &BufZartwg );
		BufZartwg.ARTIKEL_NR = artikel_nr;
		strcpy (BufZartwg.ART, "9");
		strcpy (BufZartwg.WARENGRUPPE, Rabattgruppe);

		sprintf( PrimeKeyCond, "ARTIKEL_NR = %7ld and ART = '9'", artikel_nr );

		lStatus = FdDelayInsertRecord( fd_zartwg, &BufZartwg, PrimeKeyCond, buf);
		anz_calculated++;
	}
	else if ( lStatus == 0 )
	{
		if (strncmp(BufZartwgOld.WARENGRUPPE, Rabattgruppe, 3) == 0)
			anz_ok++;
		else
		{
			BufZartwg = BufZartwgOld;
			strcpy (BufZartwg.WARENGRUPPE, Rabattgruppe);

			sprintf( PrimeKeyCond, "ARTIKEL_NR = %7ld and ART = '9'", artikel_nr);
	
			lStatus = FdDelayUpdateRecord( fd_zartwg, &BufZartwg, &BufZartwgOld, 
										 PrimeKeyCond, buf);
			anz_calculated++;
		}
	}

	return lStatus;
}

/* das war die alte Berechnung (vor Änderung 19.07.12) */
static long Calculate_Old( long artikel_nr, char *buf )
{
	long s;
	short sGenerikum = 0;
	short sRabattgruppe = 0;		
	short sPreisgruppe = 0;		
	
	if ( SelBuf.PRODUKTART[0] == '2' ||
		 SelBuf.PRODUKTART[0] == '4')
		sGenerikum = 1;

	/* Subfamily 95 - 96 ---> 43 */
	if ( strncmp(SelBuf.WARENGRUPPE, "95", 2) >= 0 &&
		 strncmp(SelBuf.WARENGRUPPE, "96", 2) <= 0 )
		sRabattgruppe = 43;

	/* LPPR ---> 44 */
	else if ( SelBuf.REIMBURSEMENT_TYPE[0] == '2' )
		sRabattgruppe = 44;

	/* Subfamily = 02 ---> 36 */
	else if ( strncmp (SelBuf.WARENGRUPPE, "02", 2) == 0)
		sRabattgruppe = 36;

	/* Subfamily 03 - 04 ---> 37 */
	else if ( strncmp(SelBuf.WARENGRUPPE, "03", 2) >= 0 &&
			  strncmp(SelBuf.WARENGRUPPE, "04", 2) <= 0 )
		sRabattgruppe = 37;

	/* Subfamily 08, 09, 70, 72, 93, 94, 98, 99 ---> 42 */
	else if ( strncmp(SelBuf.WARENGRUPPE, "08", 2) == 0 ||
			  strncmp(SelBuf.WARENGRUPPE, "09", 2) == 0 ||
			  strncmp(SelBuf.WARENGRUPPE, "70", 2) == 0 ||
 			  strncmp(SelBuf.WARENGRUPPE, "72", 2) == 0 ||
			  strncmp(SelBuf.WARENGRUPPE, "93", 2) == 0 ||
			  strncmp(SelBuf.WARENGRUPPE, "94", 2) == 0 ||
			  strncmp(SelBuf.WARENGRUPPE, "98", 2) == 0 ||
			  strncmp(SelBuf.WARENGRUPPE, "99", 2) == 0 )
		sRabattgruppe = 42;

	/* Subfamily 10 - 19, 97 ---> 38 */
	else if ( ( strncmp(SelBuf.WARENGRUPPE, "10", 2) >= 0 &&
			    strncmp(SelBuf.WARENGRUPPE, "19", 2) <= 0 ) ||
	    		strncmp(SelBuf.WARENGRUPPE, "97", 2) == 0 )
		sRabattgruppe = 38;

	/* Subfamily 20 - 29 ---> 39 */
	else if ( strncmp(SelBuf.WARENGRUPPE, "20", 2) >= 0 &&
			  strncmp(SelBuf.WARENGRUPPE, "29", 2) <= 0 )
		sRabattgruppe = 39;

	/* Subfamily 30 - 39 ---> 40 */
	else if ( strncmp(SelBuf.WARENGRUPPE, "30", 2) >= 0 &&
			  strncmp(SelBuf.WARENGRUPPE, "39", 2) <= 0 )
		sRabattgruppe = 40;

	/* Subfamily 50 - 91 (außer 70 und 72) ---> 41 */
	else if ( strncmp(SelBuf.WARENGRUPPE, "50", 2) >= 0 &&
			  strncmp(SelBuf.WARENGRUPPE, "91", 2) <= 0 &&
			  strncmp(SelBuf.WARENGRUPPE, "70", 2) != 0 &&
			  strncmp(SelBuf.WARENGRUPPE, "72", 2) != 0 )
		sRabattgruppe = 41;
	
	/* BTM ---> 25 */
	else if ( SelBuf.BTM[0] == '1' )
		sRabattgruppe = 25;

	/* Krankenhaus-Produkt (34) lt. Hr. Thollon (mail 31.05.07) nicht mehr benötigt */

	/*  Partenariat nicht mehr über SORTIMENT_2 abfragen, sondern abhängig davon, ob Rabatt 
		für EGR 700 vorhanden ist --> cdiscount lesen (nur falls bis jetzt noch keine Gruppe ermittelt ist) */
	if (sRabattgruppe == 0)
	{
		s = ReadCountCdiscount ( artikel_nr, &count_cdiscount, buf );

		if ( s != 0 )
			return s;

		/* Generika und nicht Partenariat und nicht TFR ---> 23 */
		if ( sGenerikum == 1 &&
			 count_cdiscount == 0 &&
 			 SelBuf.REIMBURSEMENT_TYPE[0] != '1' )
			sRabattgruppe = 23;

		/* Generika und Partenariat und nicht TFR ---> 28 */
		else if ( sGenerikum == 1 &&
				  count_cdiscount > 0 &&
				  SelBuf.REIMBURSEMENT_TYPE[0] != '1' )
			sRabattgruppe = 28;

		/* TFR und weder Generika noch Partenariat ---> 29 */
		else if ( sGenerikum != 1 &&
				  count_cdiscount == 0 &&
				  SelBuf.REIMBURSEMENT_TYPE[0] == '1' )
			sRabattgruppe = 29;

		/* TFR und Generika, nicht Partenariat ---> 33 */
		else if ( sGenerikum == 1 &&
				  count_cdiscount == 0 &&
				  SelBuf.REIMBURSEMENT_TYPE[0] == '1' )
			sRabattgruppe = 33;

		/* TFR, Generika und Partenariat ---> 30 */
		else if ( sGenerikum == 1 &&
				  count_cdiscount > 0 &&
				  SelBuf.REIMBURSEMENT_TYPE[0] == '1' )
			sRabattgruppe = 30;
	}

	/* falls jetzt noch keine Gruppe ermittelt ist, muss der aktuelle Preis gelesen werden */
	if (sRabattgruppe == 0)
	{
		/* ab hier Subfamily 07 wie 01 behandeln */
		if ( strncmp(SelBuf.WARENGRUPPE, "07", 2) == 0 )
			 strncpy(SelBuf.WARENGRUPPE, "01", 2);

        s = GetBufferDesc_Zartpreis ( buf );
		if ( s != 0 )
			return s;

		s = ReadRecord_ZartPreisCurrent ( artikel_nr, buf );

		if (s == 0)
		{
		/* geaenderte Preisgrenzen ab 01.01.2012: 
			vorher:  Stufe 1:   0,00 -  22,89
					 Stufe 2:  22,90 - 149,99
					 Stufe 3: 150,00 - 399,99
					 Stufe 4: 400,00 - xxx,xx
			nachher: Stufe 1:   0,00 -   3,03
					 Stufe 2:   3,04 -   4,50
					 Stufe 3:   4,51 - 132,35
					 Stufe 4: 132,36 - 450,00
					 Stufe 5: 450,01 - xxx,xx */

			if ( BufZartpreis.GROSSO < 3.035 )
				sPreisgruppe = 1;
			else if ( BufZartpreis.GROSSO < 4.505 )
				sPreisgruppe = 2;
			else if ( BufZartpreis.GROSSO < 132.355 )
				sPreisgruppe = 3;
			else if ( BufZartpreis.GROSSO < 450.005 )
				sPreisgruppe = 4;
			else 
				sPreisgruppe = 5;
		}
		/* kein zartpreis gefunden --> behandeln wie 1. Preisgruppe */
		else if (s == 100)
		{
			s = 0;
			sPreisgruppe = 1;
		}
		else 
			return s;
		
		/* Test */
		/* printf("\n%d %f %s %c", artikel_nr, BufZartpreis.GROSSO, SelBuf.WARENGRUPPE, SelBuf.KUEHLARTIKEL[0]); */

		/* Warengruppe 01xxx und Kühlartikel ---> 01 / 24 / 27 / 32 / 35 (preigruppenabhängig) */
		if ( strncmp(SelBuf.WARENGRUPPE, "01", 2) == 0 &&
			 SelBuf.KUEHLARTIKEL[0] != '0' && 
			 SelBuf.KUEHLARTIKEL[0] != ' ' )
		{
			switch (sPreisgruppe)
			{
				case 5: 
					sRabattgruppe = 35;
					break;
				case 4: 
					sRabattgruppe = 32;
					break;
				case 3: 
					sRabattgruppe = 27;
					break;
				case 2: 
					sRabattgruppe = 24;
					break;
				default: 
					sRabattgruppe = 01;
			}
		}

		/* Warengruppe 01xxx und kein Kühlartikel ---> 02 / 19 / 26 / 31 / 34 (preigruppenabhängig) */
		else if ( strncmp(SelBuf.WARENGRUPPE, "01", 2) == 0 &&
			 ( SelBuf.KUEHLARTIKEL[0] == '0' ||
			   SelBuf.KUEHLARTIKEL[0] == ' ' ))
		{
			switch (sPreisgruppe)
			{
				case 5: 
					sRabattgruppe = 34;
					break;
				case 4: 
					sRabattgruppe = 31;
					break;
				case 3: 
					sRabattgruppe = 26;
					break;
				case 2: 
					sRabattgruppe = 19;
					break;
				default: 
					sRabattgruppe = 02;
			}
		}
	}

	/*  falls jetzt immer noch keine Gruppe ermittelt ist, gehts halt nicht */
	if (sRabattgruppe == 0)
	{
		anz_nix++;
		return 4711;
	}
	
	s = GetBufferDesc_Zartwg ( buf );
	if ( s != 0 )
		return s;

	s = StoreRecord_Zartwg ( SelBuf.ARTIKEL_NR, sRabattgruppe, buf );

	return s;
} 

/* ---------------------------------------- */
static long Calculate( long artikel_nr, char *buf )
{
	long s;
	short sGenerikum = 0;
	short sRabattgruppe = 0;		
	short sPreisgruppe = 0;	
	double count_cdiscgrpmem_998 = 0.0;
	double count_cdiscgrpmem_999 = 0.0;
	
	/* CPR-190228: zusätzlicher Parameter Rabattgruppe 999, weil danach auch nochmal Lesen mit 998) */
	s = ReadCountCdiscgrpmem ( artikel_nr, 999, &count_cdiscgrpmem_999, buf );

	if ( s != 0 )
		return s;

	s = ReadCountCdiscgrpmem ( artikel_nr, 998, &count_cdiscgrpmem_998, buf );

	if ( s != 0 )
		return s;

	/* CPR-190228: aktuellen Preis hier schon lesen wegen Prüfung bei LPPR, Toxic, not refunding */
	s = GetBufferDesc_Zartpreis ( buf );
	if ( s != 0 )
		return s;

	s = ReadRecord_ZartPreisCurrent ( artikel_nr, buf );

	/* Satz nicht gefunden --> Preise auf 0 setzen und weitermachen */
	if (s == 100)
	{
		s = 0;
		BufZartpreis.GROSSO = 0.0;
		BufZartpreis.AEP = 0.0;
	}

	if ( s != 0 )
		return s;

	if ( SelBuf.PRODUKTART[0] == '2' ||
		 SelBuf.PRODUKTART[0] == '4' ||
		 SelBuf.PRODUKTART[0] == '5')
		sGenerikum = 1;

	/* Artikel in der Gruppe 999 der nicht zu rabattierenden PZNs ---> 50 */
	if ( count_cdiscgrpmem_999 > 0 )
		sRabattgruppe = 50;

	/* CPR-190228: Ergänzung Warengruppen 01008, 99093 */
	/* (neu 08.03.17: bestimmte Warengruppen ---> ebenfalls 50) */
	else if ( strncmp(SelBuf.WARENGRUPPE, "01007", 5) == 0 || 
              strncmp(SelBuf.WARENGRUPPE, "01008", 5) == 0 ||
              strncmp(SelBuf.WARENGRUPPE, "01009", 5) == 0 ||
			( strncmp(SelBuf.WARENGRUPPE, "05032", 5) >= 0 && 
              strncmp(SelBuf.WARENGRUPPE, "05038", 5) <= 0 ) ||
              strncmp(SelBuf.WARENGRUPPE, "09000", 5) == 0 ||
			( strncmp(SelBuf.WARENGRUPPE, "09090", 5) >= 0 && 
              strncmp(SelBuf.WARENGRUPPE, "09099", 5) <= 0 ) ||
			( strncmp(SelBuf.WARENGRUPPE, "54000", 5) >= 0 && 
              strncmp(SelBuf.WARENGRUPPE, "54098", 5) <= 0 ) ||
              strncmp(SelBuf.WARENGRUPPE, "98098", 5) == 0 ||
              strncmp(SelBuf.WARENGRUPPE, "98099", 5) == 0 ||
			  strncmp(SelBuf.WARENGRUPPE, "99093", 5) == 0 ||
			  strncmp(SelBuf.WARENGRUPPE, "99999", 5) == 0 ) 
		sRabattgruppe = 50;

	/* Artikel in der Gruppe 998 der nicht zu rabattierenden PZNs ---> 51 */
	else if ( count_cdiscgrpmem_998 > 0 )
		sRabattgruppe = 51;

	/* Generikum ---> 20 (08.03.17: Prio nach oben verschoben) */
	else if ( sGenerikum == 1 )
		sRabattgruppe = 20;

	/* CPR-190228: Preisabfragen für Rabattgruppen 44, 99 & 36) */
	/* Erstattungstyp 2 (LPPR) ---> 44 (08.03.17: Alternativ-Abfragen auf Warengruppe 06000 & 07041 & 07043 entfernt) */
	else if ( SelBuf.REIMBURSEMENT_TYPE[0] == '2' && 
			  BufZartpreis.AEP < 74.995 )
		sRabattgruppe = 44;

	/* BTM ---> 99 (08.03.17: Prio nach oben verschoben) */
	else if ( SelBuf.BTM[0] == '1' && 
			  BufZartpreis.AEP < 74.995 )
		sRabattgruppe = 99;

	/* Warengruppe 01002 ---> 36 */
	else if ( strncmp(SelBuf.WARENGRUPPE, "01002", 5) == 0 && 
			  BufZartpreis.AEP < 29.995 )
		sRabattgruppe = 36;

	/* CPR-190228: Rabattgruppen 30, 37, 39, 40 und 41 entfernt
	// Warengruppe 99093 ---> 30 (08.03.17: wieder aktiviert, war ausgesternt seit 01.01.2013)
	else if ( strncmp(SelBuf.WARENGRUPPE, "99093", 5) == 0 )
		sRabattgruppe = 30; 

	// Warengruppe 01003 & 01004 & 01008 ---> 37 (08.03.17: 01008 hinzugefügt)
	else if ( strncmp(SelBuf.WARENGRUPPE, "01003", 5) == 0 || 
              strncmp(SelBuf.WARENGRUPPE, "01004", 5) == 0 ||
              strncmp(SelBuf.WARENGRUPPE, "01008", 5) == 0 )
		sRabattgruppe = 37;

	// Warengruppe 03001 - 03099 & 04001 - 04099 ---> 39
	else if ( ( strncmp(SelBuf.WARENGRUPPE, "03001", 5) >= 0 && 
                strncmp(SelBuf.WARENGRUPPE, "03099", 5) <= 0 ) ||
	          ( strncmp(SelBuf.WARENGRUPPE, "04001", 5) >= 0 && 
                strncmp(SelBuf.WARENGRUPPE, "04099", 5) <= 0 ) )
		sRabattgruppe = 39;

	// Warengruppe 05001 - 05030 & 05039 ---> 40 (08.03.17: vorher 05001 - 05099)
	else if ( ( strncmp(SelBuf.WARENGRUPPE, "05001", 5) >= 0 && 
                strncmp(SelBuf.WARENGRUPPE, "05030", 5) <= 0 ) || 
	            strncmp(SelBuf.WARENGRUPPE, "05039", 5) == 0 )
		sRabattgruppe = 40;

	// Warengruppe 06000 - 06099 & 07041 - 07043 ---> 41 (08.03.17: 09090 - 09099 & 99999 entfernt, 06000, 07041 & 07043 hinzugefügt)
	else if ( ( strncmp(SelBuf.WARENGRUPPE, "06000", 5) >= 0 && 
                strncmp(SelBuf.WARENGRUPPE, "06099", 5) <= 0 ) ||
	          ( strncmp(SelBuf.WARENGRUPPE, "07041", 5) >= 0 && 
                strncmp(SelBuf.WARENGRUPPE, "07043", 5) <= 0 ) )
		sRabattgruppe = 41; */

	/* Warengruppe 02001 - 02099 ---> 38 */
	else if ( strncmp(SelBuf.WARENGRUPPE, "02001", 5) >= 0 && 
              strncmp(SelBuf.WARENGRUPPE, "02099", 5) <= 0 )
		sRabattgruppe = 38;

	/* CPR-190228: neue Rabattgruppe 42; LPPR, Kühl & BTM explizit ausgeschlossen */
	else if ( SelBuf.REIMBURSEMENT_TYPE[0] != '2' && 
	          SelBuf.BTM[0] != '1' &&
			( SelBuf.KUEHLARTIKEL[0] == '0' || 
			  SelBuf.KUEHLARTIKEL[0] == ' ' ) && 
		    ( strncmp(SelBuf.WARENGRUPPE, "05030", 5) == 0 || 
	        ( strncmp(SelBuf.WARENGRUPPE, "03020", 5) >= 0 && 
              strncmp(SelBuf.WARENGRUPPE, "03025", 5) <= 0 ) ) )
		sRabattgruppe = 42;

	/* falls jetzt noch keine Gruppe ermittelt ist, wird sie anhand des Preises vergeben */ 
	if (sRabattgruppe == 0)
	{
		/* (neu 08.03.17: Abfrage auf Warengruppe 54098 vom 26.07.12 wieder deaktiviert 
	    if ( strncmp(SelBuf.WARENGRUPPE, "54098", 5) != 0 ) 

		/* alle folgenden Gruppen nur für Warengruppe 01001 (08.03.17: wieder aktiviert, war seit 25.07.12 aussgesternt, vorher waren auch 01007 - 01009 abgefragt) */
		/* CPR-190228: LPPR & BTM explizit ausgeschlossen, da solche Artikel mit AEP >= 75,- hier landen könnten */
	    if ( strncmp(SelBuf.WARENGRUPPE, "01001", 5) == 0  && 
	         SelBuf.REIMBURSEMENT_TYPE[0] != '2' && 
	         SelBuf.BTM[0] != '1' )
		{
			/* Anpassung Preisgrenze Stufe 1 von 4,50 auf 3,03 (Mail Delfly 03/10/12, 16:26) */
			/* Anpassung Preisgrenze Stufe 1 von 3,03 auf 4,50 und Stufe 2 von 132,35 auf 150 (Mail Thollon 11/03/16, 12:54) im Rahmen des Projekts FR-UPM */
			/* neue Stufe 5 ab 1.600,- im Rahmen des CPR-190228 */
			/* Grenze für Stufe 5 auf 1.500,- geändert (SR-19100074) */
			if ( BufZartpreis.GROSSO < 4.505 )
				sPreisgruppe = 1;
			else if ( BufZartpreis.GROSSO < 150.005 )
				sPreisgruppe = 2;
			else if ( BufZartpreis.GROSSO < 450.005 )
				sPreisgruppe = 3;
/*			else if ( BufZartpreis.GROSSO < 1600.005 ) */
			else if ( BufZartpreis.GROSSO < 1500.005 )
				sPreisgruppe = 4;
			else 
				sPreisgruppe = 5;

			/* Test */
			/* printf("\n%d %f %s %c", artikel_nr, BufZartpreis.GROSSO, SelBuf.WARENGRUPPE, SelBuf.KUEHLARTIKEL[0]); */

			/* Kühlartikel ---> 81 - 85 (preigruppenabhängig) */
			if ( SelBuf.KUEHLARTIKEL[0] != '0' && 
				 SelBuf.KUEHLARTIKEL[0] != ' ' )
			{
				switch (sPreisgruppe)
				{
					case 5: 
						sRabattgruppe = 85;
						break;
					case 4: 
						sRabattgruppe = 84;
						break;
					case 3: 
						sRabattgruppe = 83;
						break;
					case 2: 
						sRabattgruppe = 82;
						break;
					default: 
						sRabattgruppe = 81;
				}
			}

			/* kein Kühlartikel ---> 91 - 95 (preigruppenabhängig) */
			else 
			{
				switch (sPreisgruppe)
				{
					case 5: 
						sRabattgruppe = 95;
						break;
					case 4: 
						sRabattgruppe = 94;
						break;
					case 3: 
						sRabattgruppe = 93;
						break;
					case 2: 
						sRabattgruppe = 92;
						break;
					default: 
						sRabattgruppe = 91;
				}
			}
		}
	}

	/* falls jetzt immer noch keine Gruppe ermittelt ist, geht's halt nicht */
	/* CPR-190228: Default-Rabattgruppe 50, wenn keine andere vergeben werden kann */
	if (sRabattgruppe == 0)
	{
		sRabattgruppe = 50;
/*		anz_nix++;
		return 4711; */
	}
	
	s = GetBufferDesc_Zartwg ( buf );
	if ( s != 0 )
		return s;

	s = StoreRecord_Zartwg ( SelBuf.ARTIKEL_NR, sRabattgruppe, buf );

	return s;
}

/* ---------------------------------------- */
static long CalcArticle( long artikel_nr, char *buf )
{
   long s;

   s = Calculate( artikel_nr, buf );
   
   if ( s == 0 )
/*	   s = FdTransactWithoutWork( buf ); */
	   s = FdTransact( buf );

   return s;
}

/* ---------------------------------------- */
static long CalcAll( char *buf )
{
   long s;
   char z_buf[500];
   int fd_sel_zartikel = -1;

	sprintf( buf,
/*      "select a.ARTIKEL_NR, substr(w.WARENGRUPPE, 4, 2), a.BTM, a.KUEHLARTIKEL, a.PRODUKTART, " */
        "select a.ARTIKEL_NR, w.WARENGRUPPE, a.BTM, a.KUEHLARTIKEL, a.PRODUKTART, "
		"f.REIMBURSEMENT_TYPE from zartikel a, zartwg w, zartfrance f where "
		"a.ARTIKEL_NR = w.ARTIKEL_NR and a.ARTIKEL_NR = f.ARTICLENO and w.ART = '2'");

	if (!(datum_von == 0 && datum_bis == 0))
	{
		sprintf( z_buf, "%s and a.ARTIKEL_NR in (select ARTIKEL_NR from zapflege where datum >= %ld "
			"and datum <= %ld) order by a.ARTIKEL_NR", buf, datum_von, datum_bis);
		sprintf( buf, "%s", z_buf);	
	}

	s = SqlOpenCsWh( &fd_sel_zartikel, buf );

   if ( s != 0 )
   {
     strcpy( buf, "ZARTIKEL\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd_sel_zartikel, 1, &SelBuf, NULL );
   
   if ( s != 0 )
   {
	   /* bei leerer Selektion RC = 0 und keine Fehlermeldung */
	   if (s == 100)
	   {
			strcpy( buf, "" );
			s = 0;
	   }
	   else
	   {
			strcpy( buf, "ZARTIKEL\n" );
            strcat( buf, DynErrmld() );
	   }

	   SqlCloseCs( fd_sel_zartikel );
	   return s;
   }
   
   Init( );

/*
//--- start transaction
   s = SqlBeginWork();
   if ( s != 0 )
   {
		strcpy( buf, DynErrmld() );
		return -1;
   } */
   
   while ( s == 0 )
   {
		s = CalcArticle( SelBuf.ARTIKEL_NR, buf );

		/* auch wenn bei einem nichts berechnet werden konnte, trotzdem weitermachen */
		if ( s == 4711 )
			s = 0;

		if ( s == 0 )
		{
			s = SqlFetch( fd_sel_zartikel, 1, &SelBuf, NULL );
	         
			if ( s != 0 )
			{
				strcpy( buf, "ZARTIKEL\n" );
				strcat( buf, DynErrmld() );
			}
		}
   }

   Free( );

   SqlCloseCs( fd_sel_zartikel );

   if ( s == 100 )
      s = 0;
   
/*
//--- end transaction
   if ( s == 0 )
   {
      s = SqlCommitWork();
      
	  if ( s != 0 )
         strcpy( buf, DynErrmld() );
   }
   else
      SqlRollbackWork(); */

   if ( s == 0 )
   {
		strcpy( buf, "Berechnung erfolgreich " );
   	
		sprintf( z_buf, "\nEs wurden %d Rabattgruppen neu berechnet."
						"\n%d Rabattgruppen blieben unveraendert."
						"\nFuer %d Artikel konnte keine Rabattgruppe ermittelt werden.",
                        anz_calculated, anz_ok, anz_nix );
   }

   strcat( buf, z_buf );
   return s;
}

/* ---------------------------------------- */
static long CalcSingle( long artikel_nr, char *buf )
{
	long s;
   
	sprintf( buf,
/*		"select a.ARTIKEL_NR, substr(w.WARENGRUPPE, 4, 2), a.BTM, a.KUEHLARTIKEL, a.PRODUKTART, " */
		"select a.ARTIKEL_NR, w.WARENGRUPPE, a.BTM, a.KUEHLARTIKEL, a.PRODUKTART, "
		"f.REIMBURSEMENT_TYPE from zartikel a, zartwg w, zartfrance f where "
		"a.ARTIKEL_NR = w.ARTIKEL_NR and a.ARTIKEL_NR = f.ARTICLENO and w.ART = '2' and "
		"a.ARTIKEL_NR = %ld ", artikel_nr
		);

	s = SqlRead( buf, &SelBuf, NULL ); 
   
   if ( s == 100 )
   {
		strcpy( buf, "Artikel nicht in zartikel, zartwg und zartfrance vorhanden !" );
		return 0;
   }

   if ( s != 0 )
   {
		strcpy( buf, "ZARTIKEL\n" );
		strcat( buf, DynErrmld() );
		return s;
   }

   Init( );

/*
//--- start transaction
   s = SqlBeginWork();
   if ( s != 0 )
   {
		strcpy( buf, DynErrmld() );
		return -1;
   } */
   
   s = CalcArticle( artikel_nr, buf );

   Free( );

/* 
//--- end transaction
   if ( s == 0 )
   {
      s = SqlCommitWork();
      
	  if ( s != 0 )
         strcpy( buf, DynErrmld() );
   }
   else
      SqlRollbackWork(); */

   if ( s == 0 )
		strcpy( buf, "Rabattgruppe des angegebenen Artikels wurde neu berechnet." );
   else if ( s == 4711 )
   		strcpy( buf, "Rabattgruppe des angegebenen Artikels konnte nicht berechnet werden." );
 
   return s;
}

/* ---------------------------------------- */
long CalcLoop ( char *db, char *cArtNr, char *buf )
{
	long s;
   	long artikel_nr;
	char errmld[10];

	//---- PZN -----
	if ( cArtNr != NULL )
	{
		int i = 0;
       
		while ( isdigit(cArtNr[i]) )
			++i;
       
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
		s = OpenPflege( user, buf );

		if ( s == 0 )
		{
			if ( cArtNr == NULL )
				s = CalcAll( buf );
			else
				s = CalcSingle( artikel_nr, buf );

			ClosePflege( errmld );
		}
     
		CloseBase( );
	}

	return s;
}


/* ---------------------------------------- */
long CalcRgLoop ( char *db, char *cDatumVon, char *cDatumBis, char *cArtNr, char *buf )
{
	datum_von = atoi(cDatumVon);
	datum_bis = atoi(cDatumBis);

	if (!(datum_von == 0 && datum_bis == 0))
	{
		if ( ( TestPhoDate( datum_von ) != 2 ) ||
			( TestPhoDate( datum_bis ) != 2 ) ||
			( datum_von > datum_bis ) )
		{
			strcpy( buf, "Datumsbereich nicht korrekt." );
			return -1;
		}
	}

	return CalcLoop( db, cArtNr, buf );
}
