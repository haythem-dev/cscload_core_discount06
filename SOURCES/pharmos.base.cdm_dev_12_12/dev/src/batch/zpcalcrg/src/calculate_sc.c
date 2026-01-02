/* ---------------------------------------------------------------------- *
 *                        C A L C U L A T E . C                           *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Spannenclusterberechnung Deutschland                         *
 * ---------------------------------------------------------------------- *
 * Autor  :  Raab                                                         *
 * Anfang :  20.10.2011                                                   *
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

#include <zartikel.h>
#include <zapflege.h>

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Funktion ------------------------ */

static char *	user			= "zpcalcrg";

static int		fd_zartikel		= -1;
static int		fd_zapflege		= -1;

static long		datum_von		= -1;
static long		datum_bis		= -1;
static long		anz_calculated	= 0;
static long		anz_ok			= 0;

static struct ZARTIKEL		BufZartikel;
static struct ZARTIKEL		BufZartikelOld;
static struct ZAPFLEGE		BufZapflege;

static struct SC_SC_SelBuf {
       long    ARTIKEL_NR;
       double  Z_AKTIONSGROSSO;
       short   SPANNENCLUSTER;
       double  K_AKTIONSGROSSO;
       double  GROSSO;
       double  AEP;
} SC_SelBuf;
		
/* ---------------------------------------- */
static void Init( )
{
	fd_zartikel		= -1;
	fd_zapflege			= -1;
}

/* ---------------------------------------- */
static void Free( )
{
    if ( fd_zartikel >= 0 )
        CloseOneBufferDesc( fd_zartikel );
    fd_zartikel = -1;

	if ( fd_zapflege >= 0 )
        CloseOneBufferDesc( fd_zapflege );
    fd_zapflege = -1;
}

/* ---------------------------------------- */
int GetBufferDesc_Zartikel( char *cErrmld )
{
   char *tabelle = "zartikel";
   long s;
   char errmld[100];

/*    *cErrmld = '\0'; */
   if ( fd_zartikel >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zartikel, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zartikel = -1;
     return -1;
   }

   return 0;
}

/* ---------------------------------------- */
int GetBufferDesc_Zapflege( char *cErrmld )
{
   char *tabelle = "zapflege";
   long s;
   char errmld[100];

/*   *cErrmld = '\0'; */
   if ( fd_zapflege >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zapflege, tabelle,
                           NULL, NULL, V_OHNE, errmld ); 
/*						   NULL, NULL, V_PROTO_VERTEIL, errmld ); */
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zapflege = -1;
     return -1;
   }

   return 0;
}

/* ---------------------------------------- */
static long ReadRecord_Zartikel( long artikel_nr, char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	sprintf( PrimeKeyCond, "ARTIKEL_NR = %ld", artikel_nr );

	lStatus = FdReadRecord( fd_zartikel, PrimeKeyCond,
							&BufZartikelOld, buf );
	
	return lStatus;
}

/*----------------------------------------------------------------------------*/
static long StoreRecord_Zapflege( char *buf )
{
	long lStatus;

	/* fürs Lesen zapflege, damit der Puffer nicht durch NotFound überschrieben wird */
	char t_buf[100];

	char PrimekeyCond[100];
	
	BufZapflege.ARTIKEL_NR = SC_SelBuf.ARTIKEL_NR;
	BufZapflege.DATUM = datum_bis;

	sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and DATUM=%ld",
							BufZapflege.ARTIKEL_NR, BufZapflege.DATUM );

    lStatus = FdReadRecord( fd_zapflege, PrimekeyCond,
				  			  &BufZapflege, t_buf );

	if ( lStatus == 100 )
	{
		lStatus = FdDelayInsertRecord( fd_zapflege, &BufZapflege, 
									PrimekeyCond, buf );
	}

	return lStatus;
}

/* ---------------------------------------- */
static long StoreRecord_Zartikel( long artikel_nr, short sSpannencluster, double dAktionsgrosso, char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[100];
	
	lStatus = ReadRecord_Zartikel (artikel_nr, buf);

	if ( lStatus == 0 )
	{
		BufZartikel = BufZartikelOld;
		BufZartikel.AKTIONSGROSSO  = dAktionsgrosso;
		BufZartikel.SPANNENCLUSTER = sSpannencluster;

		sprintf( PrimeKeyCond, "ARTIKEL_NR = %7ld", artikel_nr);

		lStatus = FdDelayUpdateRecord( fd_zartikel, &BufZartikel, &BufZartikelOld, 
										PrimeKeyCond, buf);
		anz_calculated++;

		/* datum_von = 1.1.1900 --> Urladung --> keine zapflege-Ausgabe */
		if (datum_von != 19000101)
		{
			if ( lStatus == 0 )
				lStatus = GetBufferDesc_Zapflege ( buf );

			if ( lStatus == 0 )
				lStatus = StoreRecord_Zapflege( buf );
		}
	}

	return lStatus;
}

/* ---------------------------------------- */
static long SC_Calculate( long artikel_nr, char *buf )
{
	long s;
		
	short sSpannencluster = 0;
	double dSpanne;
	double dAktionsgrosso;

	if (SC_SelBuf.K_AKTIONSGROSSO == 0)
		dAktionsgrosso = SC_SelBuf.GROSSO;
	else
		dAktionsgrosso = SC_SelBuf.K_AKTIONSGROSSO;

	if (SC_SelBuf.AEP == 0 || SC_SelBuf.AEP < dAktionsgrosso)
		sSpannencluster = 1;
	else
	{
		dSpanne = ((SC_SelBuf.AEP - dAktionsgrosso) / SC_SelBuf.AEP * 100);

		if (dSpanne >= 30.005)
			sSpannencluster = 6;
		else if (dSpanne >= 25.005)
			sSpannencluster = 5;
		else if (dSpanne >= 20.005)
			sSpannencluster = 4;
		else if (dSpanne >= 16.005)
			sSpannencluster = 3;
		else if (dSpanne >= 10.005)
			sSpannencluster = 2;
		else
			sSpannencluster = 1;
	}

	if (SC_SelBuf.SPANNENCLUSTER  == sSpannencluster && 
		SC_SelBuf.Z_AKTIONSGROSSO == dAktionsgrosso)
	{
		anz_ok++;
		return 0;
	}

	s = GetBufferDesc_Zartikel ( buf );

	if ( s == 0 )
		s = StoreRecord_Zartikel ( SC_SelBuf.ARTIKEL_NR, sSpannencluster, dAktionsgrosso, buf );

	return s;
}

/* ---------------------------------------- */
static long SC_CalcArticle( long artikel_nr, char *buf )
{
   long s;

   s = SC_Calculate( artikel_nr, buf );
   
   if ( s == 0 )
/*	   s = FdTransactWithoutWork( buf ); */
	   s = FdTransact( buf );

   return s;
}

/* ---------------------------------------- */
static long SC_CalcAll1( char *buf )
{
	long s;
	char z_buf[1500];
	int fd_sel_zartikel = -1;

	sprintf( z_buf,
		"select a.ARTIKEL_NR, a.AKTIONSGROSSO, a.SPANNENCLUSTER, max(k.AKTIONSGROSSO2) as AKTIONSGROSSO2, p.GROSSO, p.AEP " 
		"from zartikel a, kalkppe k, zartpreis p "
		"where a.ARTIKEL_NR = k.ARTIKEL_NR and a.ARTIKEL_NR = p.ARTIKEL_NR and p.PREIS_TYP = 0 "
		"and p.DATUMGUELTIGAB=(SELECT MAX(DATUMGUELTIGAB) from zartpreis where ARTIKEL_NR = a.ARTIKEL_NR and PREIS_TYP = 0 and DATUMGUELTIGAB < %ld) "
		"and (a.AKTIONSGROSSO != AKTIONSGROSSO2 or p.DATUMGUELTIGAB >= %ld) "
		"group by a.ARTIKEL_NR, a.AKTIONSGROSSO, a.SPANNENCLUSTER, p.GROSSO, p.AEP ", datum_bis, datum_von);

	s = SqlOpenCsWh( &fd_sel_zartikel, z_buf );

   if ( s != 0 )
   {
     strcpy( z_buf, "Open ZARTIKEL1\n" );
     strcat( z_buf, DynErrmld() );
	 strcat( buf, z_buf );
     return s;
   }

   s = SqlFetch( fd_sel_zartikel, 1, &SC_SelBuf, NULL );
   
   if ( s != 0 )
   {
	   /* bei leerer Selektion RC = 0 und keine Fehlermeldung */
	   if (s == 100)
	   {
			strcpy( z_buf, "\nkeine Saetze fuer Berechnung #1 selektiert" );
			strcat( buf, z_buf );
			s = 0;
	   }
	   else
	   {
			strcpy( z_buf, "Fetch ZARTIKEL1\n" );
			strcat( z_buf, DynErrmld() );
			strcat( buf, z_buf );
	   }

	   SqlCloseCs( fd_sel_zartikel );
	   return s;
   }
   
   Init( );

   while ( s == 0 )
   {
		s = SC_CalcArticle( SC_SelBuf.ARTIKEL_NR, buf );

		/* TEST !!!! 
		if ((anz_ok + anz_calculated) > 10000) 
			break; */

		if ( s == 0 )
		{
			s = SqlFetch( fd_sel_zartikel, 1, &SC_SelBuf, NULL );
	         
			if ( s != 0 && 
				 s != 100)
			{
				strcpy( z_buf, "Fetch ZARTIKEL1\n" );
				strcat( z_buf, DynErrmld() );
				strcat( buf, z_buf );
			}
		}
   }

   Free( );

   SqlCloseCs( fd_sel_zartikel );

   if ( s == 100 )
      s = 0;

   if ( s == 0 )
   {
		sprintf( z_buf, "\nBerechnung #1 erfolgreich " 
						"\nEs wurden %d Spannencluster neu berechnet."
						"\n%d Spannencluster blieben unveraendert.",
                        anz_calculated, anz_ok );

		strcat( buf, z_buf );

		anz_calculated = 0;
		anz_ok = 0;
   }

   return s;
}

/* ---------------------------------------- */
static long SC_CalcAll2( char *buf )
{
	long s;
	char z_buf[1500];
	int fd_sel_zartikel = -1;

	sprintf( z_buf,
        "select a.ARTIKEL_NR, a.AKTIONSGROSSO, a.SPANNENCLUSTER, 0.00, p.GROSSO, p.AEP " 
		"from zartikel a, zartpreis p "
		"where a.ARTIKEL_NR = p.ARTIKEL_NR and p.PREIS_TYP = 0 "
		"and a.ARTIKEL_NR not in (select distinct ARTIKEL_NR from kalkppe) "
		"and p.DATUMGUELTIGAB=(SELECT MAX(DATUMGUELTIGAB) from zartpreis where ARTIKEL_NR = a.ARTIKEL_NR and PREIS_TYP = 0 and DATUMGUELTIGAB < %ld) "
		"and (a.AKTIONSGROSSO != p.GROSSO or p.DATUMGUELTIGAB >= %ld) ", datum_bis, datum_von);

	s = SqlOpenCsWh( &fd_sel_zartikel, z_buf );

   if ( s != 0 )
   {
     strcpy( z_buf, "Open ZARTIKEL2\n" );
     strcat( z_buf, DynErrmld() );
	 strcat( buf, z_buf );
     return s;
   }

   s = SqlFetch( fd_sel_zartikel, 1, &SC_SelBuf, NULL );
   
   if ( s != 0 )
   {
	   /* bei leerer Selektion RC = 0 und keine Fehlermeldung */
	   if (s == 100)
	   {
			strcpy( z_buf, "\nkeine Saetze fuer Berechnung #2 selektiert" );
			strcat( buf, z_buf );
			s = 0;
	   }
	   else
	   {
			strcpy( z_buf, "Fetch ZARTIKEL2\n" );
			strcat( z_buf, DynErrmld() );
			strcat( buf, z_buf );
	   }

	   SqlCloseCs( fd_sel_zartikel );
	   return s;
   }
   
   Init( );

   while ( s == 0 )
   {
		s = SC_CalcArticle( SC_SelBuf.ARTIKEL_NR, buf );

		/* TEST !!!! 
		if ((anz_ok + anz_calculated) > 10000)
			break; */

		if ( s == 0 )
		{
			s = SqlFetch( fd_sel_zartikel, 1, &SC_SelBuf, NULL );
	         
			if ( s != 0 && 
				 s != 100)
			{
				strcpy( z_buf, "Fetch ZARTIKEL2\n" );
				strcat( z_buf, DynErrmld() );
				strcat( buf, z_buf );
			}
		}
   }

   Free( );

   SqlCloseCs( fd_sel_zartikel );

   if ( s == 100 )
      s = 0;

   if ( s == 0 )
   {
		sprintf( z_buf, "\nBerechnung #2 erfolgreich " 
						"\nEs wurden %d Spannencluster neu berechnet."
						"\n%d Spannencluster blieben unveraendert.",
                        anz_calculated, anz_ok );
		
		strcat( buf, z_buf );

		anz_calculated = 0;
		anz_ok = 0;
   }

   return s;
}

/* ---------------------------------------- */
static long SC_CalcAll3( char *buf )
{
	long s;
	char z_buf[1500];
	int fd_sel_zartikel = -1;

	sprintf( z_buf,
        "select ARTIKEL_NR, AKTIONSGROSSO, SPANNENCLUSTER, 0.00, 0.00, 0.00 " 
		"from zartikel "
		"where ARTIKEL_NR not in (select distinct ARTIKEL_NR from kalkppe) "
		"and ARTIKEL_NR not in (select distinct ARTIKEL_NR from zartpreis) "
		"and (AKTIONSGROSSO > 0 or SPANNENCLUSTER != 1)");

	s = SqlOpenCsWh( &fd_sel_zartikel, z_buf );

   if ( s != 0 )
   {
     strcpy( z_buf, "Open ZARTIKEL3\n" );
     strcat( z_buf, DynErrmld() );
	 strcat( buf, z_buf );
     return s;
   }

   s = SqlFetch( fd_sel_zartikel, 1, &SC_SelBuf, NULL );
   
   if ( s != 0 )
   {
	   /* bei leerer Selektion RC = 0 und keine Fehlermeldung */
	   if (s == 100)
	   {
			strcpy( z_buf, "\nkeine Saetze fuer Berechnung #3 selektiert" );
			strcat( buf, z_buf );
			s = 0;
	   }
	   else
	   {
			strcpy( z_buf, "Fetch ZARTIKEL3\n" );
			strcat( z_buf, DynErrmld() );
			strcat( buf, z_buf );
	   }

	   SqlCloseCs( fd_sel_zartikel );
	   return s;
   }
   
   Init( );

   while ( s == 0 )
   {
		s = SC_CalcArticle( SC_SelBuf.ARTIKEL_NR, buf );

		/* TEST !!!! 
		if ((anz_ok + anz_calculated) > 10000)
			break; */

		if ( s == 0 )
		{
			s = SqlFetch( fd_sel_zartikel, 1, &SC_SelBuf, NULL );
	         
			if ( s != 0 && 
				 s != 100)
			{
				strcpy( z_buf, "Fetch ZARTIKEL3\n" );
				strcat( z_buf, DynErrmld() );
				strcat( buf, z_buf );
			}
		}
   }

   Free( );

   SqlCloseCs( fd_sel_zartikel );

   if ( s == 100 )
      s = 0;

   if ( s == 0 )
   {
		sprintf( z_buf, "\nBerechnung #3 erfolgreich " 
						"\nEs wurden %d Spannencluster neu berechnet."
						"\n%d Spannencluster blieben unveraendert.",
                        anz_calculated, anz_ok );

		strcat( buf, z_buf );

		anz_calculated = 0;
		anz_ok = 0;
   }

   return s;
}

/* ---------------------------------------- */
static long SC_CalcSingle( long artikel_nr, char *buf )
{
	long s;

	sprintf( buf,
        "select a.ARTIKEL_NR, a.AKTIONSGROSSO, a.SPANNENCLUSTER, k.AKTIONSGROSSO2, p.GROSSO, p.AEP "
		"from zartikel a, outer kalkppe k, outer zartpreis p where "
		"a.ARTIKEL_NR = k.ARTIKEL_NR and a.ARTIKEL_NR = p.ARTIKEL_NR and p.PREIS_TYP = 0 "
		"and k.AKTIONSGROSSO2 = (select max(AKTIONSGROSSO2) from kalkppe where ARTIKEL_NR = a.ARTIKEL_NR) "
		"and p.DATUMGUELTIGAB=(SELECT MAX(DATUMGUELTIGAB) from zartpreis where ARTIKEL_NR = a.ARTIKEL_NR and PREIS_TYP = 0 and DATUMGUELTIGAB < %ld) "
		"and a.ARTIKEL_NR = %ld ", datum_bis, artikel_nr);

	s = SqlRead( buf, &SC_SelBuf, NULL ); 
   
   if ( s == 100 )
   {
		strcpy( buf, "Artikel nicht in zartikel! " );
		return 0;
   }

   if ( s != 0 )
   {
		strcpy( buf, "ZARTIKEL\n" );
		strcat( buf, DynErrmld() );
		return s;
   }

   Init( );

   s = SC_CalcArticle( artikel_nr, buf );

   Free( );

   if ( s == 0 )
   {
	   if (anz_ok > 0)
			strcpy( buf, "Spannencluster des angegebenen Artikels blieb unveraendert." );
	   else
			strcpy( buf, "Spannencluster des angegebenen Artikels wurde neu berechnet." );
   }
 
   return s;
}

/* ---------------------------------------- */
long SC_CalcLoop ( char *db, char *cArtNr, char *buf )
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
			{
				/* bewusst keine UNION, weil ein solcher Select viel länger laufen würde */
				s = SC_CalcAll1( buf );

				if ( s == 0 )
					s = SC_CalcAll2( buf );

				if ( s == 0 )
					s = SC_CalcAll3( buf );
			}
			else
				s = SC_CalcSingle( artikel_nr, buf );

			ClosePflege( errmld );
		}
     
		CloseBase( );
	}

	return s;
}

/* ---------------------------------------- */
long SC_CalcScLoop ( char *db, char *cDatumVon, char *cDatumBis, char *cArtNr, char *buf )
{
	datum_von = atoi(cDatumVon);
	datum_bis = atoi(cDatumBis);

	if (datum_von == 0 || datum_bis == 0)
	{
		strcpy( buf, "Datumsfelder muessen groesser 0 sein" );
		return -1;
	}

	if ( ( TestPhoDate( datum_von ) != 2 ) ||
	     ( TestPhoDate( datum_bis ) != 2 ) ||
	     ( datum_von > datum_bis ) )
	{
		strcpy( buf, "Datumsbereich nicht korrekt." );
		return -1;
	}

	return SC_CalcLoop( db, cArtNr, buf );
}
