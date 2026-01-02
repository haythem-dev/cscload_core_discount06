/* ---------------------------------------------------------------------- *
 *                         Setspkenn.c                                    *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Artikelnamen ändern                                          *
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

#include <zartikel.h>
#include <zapflege.h>
#include <zpznpflege.h>
#include <carticlelang.h>

#define L_ARTIKEL_NR 7


/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void SetArticleNameUsage( char *buf )
{
   strcat( buf, "- zpdailyclosing 1 Database USER Datum-von Datum-bis\n" );
   strcat( buf, "  AH- Datum in Artikelnamen setzen fuer Artikel mit\n" );
   strcat( buf, "  DATUM_AH >= Datum-von && DATUM_AH <= Datum-bis\n" );
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

/* -----  Zpznpflege  ------------------------- */

static int  Fd_Zpznpflege = -1;

static struct ZPZNPFLEGE Buf_zpznpflege;

static int GetBufferDesc_Zpznpflege( char * errmld )
{
   char *tabelle = "zpznpflege";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");

   if ( Fd_Zpznpflege >= 0 ) 
	   return 0;

   lStatus = OpenBufferDescProj( &Fd_Zpznpflege, tabelle, PROJECTION_ZPZNPFLEGE,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zpznpflege = -1;
     return -1;
   }

   return 0;
}

static long StoreRecord_Zpznpflege( char* dezap_sa, long artikel_nr, long datum, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[100];

   Buf_zpznpflege.ARTIKEL_NR = artikel_nr;
   Buf_zpznpflege.DATUM      = datum;
   strcpy (Buf_zpznpflege.DEZAP_SA, dezap_sa);

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and DATUM=%ld and DEZAP_SA = '%s'",
                          Buf_zpznpflege.ARTIKEL_NR,
                          Buf_zpznpflege.DATUM,
						  Buf_zpznpflege.DEZAP_SA);

   lStatus = FdReadRecord( Fd_Zpznpflege, PrimekeyCond,
                           &Buf_zpznpflege, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

   if ( lStatus == 100 )
   {
      Buf_zpznpflege.ARTIKEL_NR = artikel_nr;
      Buf_zpznpflege.DATUM      = datum;
	  strcpy (Buf_zpznpflege.DEZAP_SA, dezap_sa);
      lStatus = FdDelayInsertRecord( Fd_Zpznpflege, &Buf_zpznpflege,
                                     PrimekeyCond, cErrmld);
   }

   return lStatus;
}

/* ----- CArticleLang ------------------------- */

static int  Fd_CArticleLang = -1;

static struct CARTICLELANG Buf_CArticleLang;
static struct CARTICLELANG BufOld_CArticleLang;

static int GetBufferDesc_CArticleLang( char * errmld )
{
    char *tabelle = "carticlelang";
    long lStatus;
    char errstr[80];

    strcpy( errmld, "");

    if ( Fd_CArticleLang >= 0 )
		return 0;

    lStatus = OpenBufferDescProj( &Fd_CArticleLang, tabelle, PROJECTION_CARTICLELANG,
                                  NULL, NULL, V_PROTO_VERTEIL, errstr );
                                
    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_CArticleLang = -1;
      return -1;
    }

    return 0;
}

static long StoreRecord_CArticleLang( long artikel_nr, long datumah, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[100];
   char format[50];
   char szStr[12];

   Buf_CArticleLang.ARTICLENO = artikel_nr;

   strcpy( cErrmld, "" );

   sprintf( format, "LANGID='FR' and ARTICLENO=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_CArticleLang.ARTICLENO );

   lStatus = FdReadRecord( Fd_CArticleLang, PrimekeyCond,
                           &Buf_CArticleLang, cErrmld );

   if ( lStatus != 0  ) 
	   return lStatus;

   BufOld_CArticleLang = Buf_CArticleLang;  /* gelesenen Satz sichern */

   ConvFromPhoDate( szStr, datumah, "mmjj" );
   memcpy( &Buf_CArticleLang.ARTICLENAME[26], szStr, 4 );

   if ( FdIsRecordModified( Fd_CArticleLang, &Buf_CArticleLang, &BufOld_CArticleLang, cErrmld ))
   {
	   lStatus = FdDelayUpdateRecord( Fd_CArticleLang, &Buf_CArticleLang,
                                  &BufOld_CArticleLang,
                                  PrimekeyCond, cErrmld );   
   }
   else
	   lStatus = 99; // no change
   
   return lStatus;
}


/* ----- Zartikel ------------------------- */

static int  Fd_Zartikel = -1;

static struct ZARTIKEL Buf_zartikel;
static struct ZARTIKEL BufOld_zartikel;
static char CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];

static int GetBufferDesc_Zartikel( char * errmld )
{
    char *tabelle = "zartikel";
    long lStatus;
    char errstr[80];

    strcpy( errmld, "");

    if ( Fd_Zartikel >= 0 )
		return 0;

    memset( CmpIndikator_Zartikel, '0', POSANZ_ZARTIKEL );
    CmpIndikator_Zartikel[POSANZ_ZARTIKEL] = '\0';
    CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_AENDER]	= '1';
    CmpIndikator_Zartikel[P_ZARTIKEL_BEARBEITER]	= '1';
    CmpIndikator_Zartikel[P_ZARTIKEL_ARTIKEL_NAME]	= '1';

    lStatus = OpenBufferDescProj( &Fd_Zartikel, tabelle, PROJECTION_ZARTIKEL,
                                  CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errstr );
                                
    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_Zartikel = -1;
      return -1;
    }

    return 0;
}

static long StoreRecord_Zartikel( long artikel_nr, long datum, long * datumah, char *user, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[50];
   char format[50];
   char szStr[12];

   Buf_zartikel.ARTIKEL_NR = artikel_nr;

   strcpy( cErrmld, "" );

   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartikel.ARTIKEL_NR );

   lStatus = FdReadRecord( Fd_Zartikel, PrimekeyCond,
                           &Buf_zartikel, cErrmld );

   if ( lStatus != 0  ) 
	   return lStatus;

   *datumah = Buf_zartikel.DATUM_AH;

   BufOld_zartikel = Buf_zartikel;  /* gelesenen Satz sichern */

   ConvFromPhoDate( szStr, Buf_zartikel.DATUM_AH, "mmjj" );
   memcpy( &Buf_zartikel.ARTIKEL_NAME[26], szStr, 4 );

   if ( FdIsRecordModified( Fd_Zartikel, &Buf_zartikel, &BufOld_zartikel, cErrmld ))
   {
	   Buf_zartikel.DATUM_AENDER = datum;
	   strcpy( Buf_zartikel.BEARBEITER, user );
   
	   lStatus = FdDelayUpdateRecord( Fd_Zartikel, &Buf_zartikel,
                                  &BufOld_zartikel,
                                  PrimekeyCond, cErrmld );
   }
   else
	   lStatus = 99; // no change

   return lStatus;
}

static long InitAll( char *errmld )
{
   if ( GetBufferDesc_Zartikel( errmld ) != 0 ) return -1;
   if ( GetBufferDesc_CArticleLang( errmld ) != 0 ) return -1;
   if ( GetBufferDesc_Zapflege( errmld ) != 0 ) return -1;
   if ( GetBufferDesc_Zpznpflege( errmld ) != 0 ) return -1;
   return 0;
}


static void FreeAll()
{
   if ( Fd_Zartikel >= 0 )
      CloseOneBufferDesc( Fd_Zartikel );
   Fd_Zartikel = -1;

   if ( Fd_CArticleLang >= 0 )
      CloseOneBufferDesc( Fd_CArticleLang );
   Fd_CArticleLang = -1;

   if ( Fd_Zapflege >= 0 )
      CloseOneBufferDesc( Fd_Zapflege );
   Fd_Zapflege = -1;

   if ( Fd_Zpznpflege >= 0 )
      CloseOneBufferDesc( Fd_Zpznpflege );
   Fd_Zpznpflege = -1;
}

static long DoIt( char *user, long artikel_nr, long tagesdatum,
                  char *errmld )
{
   long s;
   long datumah = 0;

   s = StoreRecord_Zartikel( artikel_nr, tagesdatum, &datumah, user, errmld );

   if ( s == 0 )  
      s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );

   if ( s == 0 || s == 99 )  
      s = StoreRecord_CArticleLang( artikel_nr, datumah, errmld );
  
   if ( s == 0 )  
      s = StoreRecord_Zpznpflege( "11", artikel_nr, tagesdatum, errmld );
  
   if ( s == 0 || s == 99 )
      s = FdTransact( errmld );

   return s;
}

static long SetArticleName( char *user, long datum_von, long datum_bis, char *buf )
{
   long tagesdatum;

   long artikel_nr;
   long s;
   long anz;
   int  fd;
   char z_buf[51];

   tagesdatum = GetPhoDate();

   	sprintf( buf,
				"select ARTIKEL_NR from ZARTIKEL where " \
				"datum_ah >= %ld and datum_ah <= %ld", datum_von, datum_bis);
   
   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "ZARTIKEL\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd, 1, &artikel_nr, NULL );
   if ( s == 100 )
   {
     strcpy( buf, "Keine entsprechenden Artikel vorhanden" );
     return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "ZARTIKEL\n" );
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
		s = DoIt( user, artikel_nr, tagesdatum, buf );

		if ( s == 0 )
		{
			anz++;
		}
	
		if ( s == 0 )
		{
			s = SqlFetch( fd, 1, &artikel_nr, NULL );
			if ( s != 0 )
			{
				strcpy( buf, "ZARTIKEL\n" );
				strcat( buf, DynErrmld() );
			}
		}
   }

   FreeAll( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld Artikelnamen geändert", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Aktion erfolgreich" );
   }

   strcat( buf, z_buf );
   return s;
}

long SetArticleNameLoop ( char *db, char *user, char * datefrom, char * dateto, char *buf )
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

   if ( strcmp( db, "ich21" ) != 0 && strcmp( db, "ich21pre" ) != 0 )
   {
       strcpy( buf, "Funktion bislang nur für CH implementiert!" );
       return 1;
   }

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
        s = SetArticleName( user, datum_von, datum_bis, buf );
        ClosePflege( errmld );
     }
     CloseBase( );
   }

   return s;
}
