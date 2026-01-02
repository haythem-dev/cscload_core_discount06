/* ---------------------------------------------------------------------- *
 *                         calcrefundfrance.c                             *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   reimbursement-val aus avp errechnen                          *
 * ---------------------------------------------------------------------- *
 * Autor  :  Hörath                                                       *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <phodate.h>
#include <libscsvoodoo.h>

#include <wpp_prot.h>
#include <wpp_dbas.h>

#include <zartfrance.h>
#include <zapflege.h>

#define L_ARTIKEL_NR 7


/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void SetReimbursementValFranceUsage( char *buf )
{
   strcat( buf, "- zpdailyclosing 2 Database USER Datum-von Datum-bis\n" );
   strcat( buf, "  zartfrance.reimbursement_val errechen fuer Artikel mit reimbursement_type = 3 / 2 und\n" );
   strcat( buf, "  Aenderung AVP / LPPR-Daten mit datumgueltigab >= Datum-von && datumgueltigab <= Datum-bis\n" );
}

/* -----  Zapflege  ------------------------- */

static int  Fd_Zapflege = -1;

static struct ZAPFLEGE Buf_zapflege;

static int GetBufferDesc_Zapflege( char * errmld )
{
   char *tabelle = "zapflege";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");

   if ( Fd_Zapflege >= 0 ) 
	   return 0;

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

static long StoreRecord_Zapflege( long artikel_nr, long datum, char* cErrmld )
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
      lStatus = FdDelayInsertRecord( Fd_Zapflege, &Buf_zapflege,
                                     PrimekeyCond, cErrmld);
   }

   return lStatus;
}

/* ----- Zartfrance ------------------------- */

static int  Fd_Zartfrance = -1;

static struct ZARTFRANCE Buf_zartfrance;
static struct ZARTFRANCE BufOld_zartfrance;
static char CmpIndikator_Zartfrance[POSANZ_ZARTFRANCE + 1];

static int GetBufferDesc_Zartfrance( char * errmld )
{
    char *tabelle = "zartfrance";
    long lStatus;
    char errstr[80];

    strcpy( errmld, "");

    if ( Fd_Zartfrance >= 0 )
		return 0;

    memset( CmpIndikator_Zartfrance, '0', POSANZ_ZARTFRANCE );
    CmpIndikator_Zartfrance[POSANZ_ZARTFRANCE] = '\0';
    CmpIndikator_Zartfrance[P_ZARTFRANCE_REIMBURSEMENT_VAL]	= '1';
    
    lStatus = OpenBufferDescProj( &Fd_Zartfrance, tabelle, PROJECTION_ZARTFRANCE,
                                  CmpIndikator_Zartfrance, NULL, V_PROTO_VERTEIL, errstr );
                                
    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_Zartfrance = -1;
      return -1;
    }

    return 0;
}

static long StoreRecord_Zartfrance( long artikel_nr, double avp, double pct, long datum, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[50];
   char format[50];
   
   
   Buf_zartfrance.ARTICLENO = artikel_nr;

   strcpy( cErrmld, "" );

   sprintf( format, "ARTICLENO=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartfrance.ARTICLENO );

   lStatus = FdReadRecord( Fd_Zartfrance, PrimekeyCond,
                           &Buf_zartfrance, cErrmld );

   if ( lStatus != 0  ) 
	   return lStatus;

   BufOld_zartfrance = Buf_zartfrance;  /* gelesenen Satz sichern */

   if (datum == 0) // typ 3 (AVP)
	   Buf_zartfrance.REIMBURSEMENT_VAL = avp * pct / 100;
   else // typ 2 (LPPR)
   {
		char sql[500];

		sprintf( sql, "select sum(reimbursement_val) from clppr2article a, outer clpprreimb r where articleno = %ld "
				" and a.code_lppr = r.code_lppr and reimbcalcflag = 1 "
				" and a.datefrom <= %ld "
				" and  r.datefrom  = (select max(datefrom) from clpprreimb where code_lppr = a.code_lppr and datefrom <= %ld)", artikel_nr, datum, datum);

		SqlRead(sql, &Buf_zartfrance.REIMBURSEMENT_VAL, NULL);
   }
   
   if ( FdIsRecordModified( Fd_Zartfrance, &Buf_zartfrance, &BufOld_zartfrance, cErrmld ))
   {
	   lStatus = FdDelayUpdateRecord( Fd_Zartfrance, &Buf_zartfrance,
                                  &BufOld_zartfrance,
                                  PrimekeyCond, cErrmld );
   }
   else
	   lStatus = 99; // no change

   return lStatus;
}

static long InitAll( char *errmld )
{
   if ( GetBufferDesc_Zartfrance( errmld ) != 0 ) return -1;
   if ( GetBufferDesc_Zapflege( errmld ) != 0 ) return -1;
   return 0;
}


static void FreeAll()
{
   if ( Fd_Zartfrance >= 0 )
      CloseOneBufferDesc( Fd_Zartfrance );
   Fd_Zartfrance = -1;

   if ( Fd_Zapflege >= 0 )
      CloseOneBufferDesc( Fd_Zapflege );
   Fd_Zapflege = -1;
}

static long DoIt( long artikel_nr, long tagesdatum, double avp, double pct, long datum,
                  char *errmld )
{
   long s;
   
   s = StoreRecord_Zartfrance( artikel_nr, avp, pct, datum, errmld );

   if ( s == 0 )  
      s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );

   if ( s == 0 || s == 99 )
      s = FdTransact( errmld );

   return s;
}

static long SetReimbursementValFrance( long datum_von, long datum_bis, char *buf )
{
   long tagesdatum;

   long artikel_nr;
   double pct;
   double avp;
   long s;
   long anz;
   int  fd;
   char z_buf[51];

   tagesdatum = GetPhoDate();

   sprintf( buf,
				"select articleno, avp, reimbursement_pct from zartfrance, CREIMBURSEMENT_PCT, zartpreis where " \
				"reimbursement_type = 3 and reimbursement_pct_id = reimbursement_perc and articleno = artikel_nr and datumgueltigab between %ld and %ld", datum_von, datum_bis);
   
   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "ZARTPREIS bzw. CREIMBURSEMENT_PCT\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd, 1, &artikel_nr, &avp, &pct, NULL );

   if ( s == 100 )
   {
     strcpy( buf, "Keine Artikel mit AVP-Aenderung und Reimb-Type=3 vorhanden." );
     return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "ZARTPREIS bzw. CREIMBURSEMENT_PCT\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = InitAll( buf );
   if ( s != 0 )
   {
      FreeAll( );
      SqlCloseCs( fd );
      return s;
   }

   anz = 0;
   while ( s == 0 )
   {
		s = DoIt( artikel_nr, tagesdatum, avp, pct, 0, buf );

		if ( s == 0 )
		{
			anz++;
		}
	
		if ( s == 0 )
		{
			s = SqlFetch( fd, 1, &artikel_nr, &avp, &pct, NULL );
			if ( s != 0 )
			{
				strcpy( buf, "ZARTPREIS bzw. CREIMBURSEMENT_PCT\n" );
				strcat( buf, DynErrmld() );
			}
		}
   }

   FreeAll( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld Reimbursement- Values (Typ=3, AVP) geändert", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Aktion erfolgreich" );
   }

   strcat( buf, z_buf );
   return s;
}

static long CalcLpprReimbVal( long datum_von, long datum_bis, char *buf )
{
   long tagesdatum;

   long artikel_nr;
   long s;
   long anz;
   int  fd;
   char z_buf[51];

   tagesdatum = GetPhoDate();

   sprintf( buf,
	   "select a.articleno from clppr2article a, zartfrance z where z.articleno = a.articleno and a.code_lppr in (select code_lppr from clpprreimb where datefrom between %ld and %ld) and z.reimbursement_type = '2' "\
	   "union "\
	   "select a.articleno from clppr2article a, zartfrance z where z.articleno = a.articleno and datefrom between %ld and %ld and z.reimbursement_type = '2'", datum_von, datum_bis, datum_von, datum_bis);
   
   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "clppr2article bzw. zartfrance bzw. clpprreimb\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd, 1, &artikel_nr, NULL );

   if ( s == 100 )
   {
     strcpy( buf, "Keine Artikel mit LPPR-Aenderungen und Reimb-Type=2 vorhanden." );
     return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "clppr2article bzw. zartfrance bzw. clpprreimb\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = InitAll( buf );
   if ( s != 0 )
   {
      FreeAll( );
      SqlCloseCs( fd );
      return s;
   }

   anz = 0;
   while ( s == 0 )
   {
		s = DoIt( artikel_nr, tagesdatum, 0, 0, datum_bis, buf );

		if ( s == 0 )
		{
			anz++;
		}
	
		if ( s == 0 )
		{
			s = SqlFetch( fd, 1, &artikel_nr, NULL );
			if ( s != 0 )
			{
				strcpy( buf, "clppr2article bzw. zartfrance bzw. clpprreimb\n" );
				strcat( buf, DynErrmld() );
			}
		}
   }

   FreeAll( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld Reimbursement- Values (Typ=2, LPPR) geändert", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "\nAktion erfolgreich" );
   }

   strcat( buf, z_buf );
   return s;
}

long SetReimbursementValFranceLoop ( char *db, char *user, char * datefrom, char * dateto, char *buf )
{
   long s;
   long datum_von, datum_bis;
   char errmld[10];

   if ( ConvToPhoDate ( datefrom, &datum_von, "tt.mm.jjjj" ) != 1 )
   {
       strcpy( buf, "Datum-von in der Form tt.mm.jjjj" );
       return 1;
   }

   if ( ConvToPhoDate ( dateto, &datum_bis, "tt.mm.jjjj" ) != 1 )
   {
       strcpy( buf, "Datum-bis in der Form tt.mm.jjjj" );
       return 1;
   }

   if ( strcmp( db, "ifr21" ) != 0 && strcmp( db, "ifr21pre" ) != 0 )
   {
       strcpy( buf, "Funktion nur für FR sinnvoll!" );
       return 1;
   }

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
        s = SetReimbursementValFrance( datum_von, datum_bis, buf );

		if ( s == 0 )
			s = CalcLpprReimbVal( datum_von, datum_bis, buf );

        ClosePflege( errmld );
     }
     CloseBase( );
   }

   return s;
}




