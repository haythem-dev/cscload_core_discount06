/* ---------------------------------------------------------------------- *
 *                           U _ I M S W G R . C                          *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   Generiert die IMS-Wgr                                        *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  28.06.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo.h>
#include <phodate.h>

#include <artkatg.h>
#include <zgrppflege.h>
/* -------  Spezielle includes ----------------------------------------- */

#include "pflegevers.h"

/* ---------- schreiben mit Protokoll ----------- */

static char PrimekeyCond[100];

static int  Fd_Artkatg = -1;
static int  m_Fd_Zgrppflege = -1;
static long lStatus_Artkatg;

static struct ARTKATG Buf_Artkatg;
static struct ARTKATG BufOld_Artkatg;
static struct ZGRPPFLEGE Buf_Zgrppflege;

static int GetBufferDesc_Artkatg( char * errmld )
{
   char *tabelle = "artkatg";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Artkatg >= 0 ) return 0;

#ifdef WP_ALTE_VERSION
   lStatus = OpenBufferDesc( &Fd_Artkatg, tabelle,
                              NULL, NULL,
                              V_PROTO_VERTEIL,
                              errstr );
#else
   lStatus = OpenBufferDescProj( &Fd_Artkatg, tabelle, PROJECTION_ARTKATG,
                              NULL, NULL,
                              V_PROTO_VERTEIL,
                              errstr );
#endif

   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Artkatg = -1;
     return -1;
   }
   return 0;
}

static int GetBufferDesc_Zgrppflege( char * errmld )
{
	char *tabelle = "zgrppflege";
	long lStatus;
    char errstr[80];

    strcpy( errmld, "");

	if ( m_Fd_Zgrppflege >= 0 ) return 0;

	lStatus = OpenBufferDesc( &m_Fd_Zgrppflege, tabelle,
                                NULL, NULL, V_OHNE, errstr );
	if ( lStatus != 0 )
	{
		sprintf( errmld, "%s: %s", tabelle, errstr );
		m_Fd_Zgrppflege = -1;
		return -1;
	}
	return 0;
}
static int GetBufferDesc( char * errmld )
{
	int lStatus;
	
	lStatus =  GetBufferDesc_Artkatg( errmld ) ;
	lStatus =  GetBufferDesc_Zgrppflege( errmld ) ;

	return lStatus;
}

static long StoreRecord_Zgrppflege( long datum, char * cErrmld )
{
	long lStatus;

	char PrimekeyCond_Zgrppflege[100];
	char errmld[200];

	strcpy (Buf_Zgrppflege.KEY_GRUPPE, Buf_Artkatg.WARENGRUPPE);
	Buf_Zgrppflege.DATUM		= datum;

	sprintf( PrimekeyCond_Zgrppflege, "KEY_GRUPPE='%s' and DATUM=%ld and DEZAP_SA = '16'",
									Buf_Zgrppflege.KEY_GRUPPE, Buf_Zgrppflege.DATUM );

    lStatus = FdReadRecord( m_Fd_Zgrppflege, PrimekeyCond_Zgrppflege,
				  			  &Buf_Zgrppflege, errmld );

	if ( lStatus == 100 )
	{
		strcpy (Buf_Zgrppflege.KEY_GRUPPE, Buf_Artkatg.WARENGRUPPE);
		Buf_Zgrppflege.DATUM		= datum;
		strcpy (Buf_Zgrppflege.DEZAP_SA, "16");

		lStatus = FdInsertRecord( m_Fd_Zgrppflege, &Buf_Zgrppflege, 
										 PrimekeyCond_Zgrppflege, errmld );
	}

   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );

	return lStatus;
}

static void SetPrimekeyCondition_Artkatg ( )
{
   sprintf( PrimekeyCond, "WARENGRUPPE='%s'", Buf_Artkatg.WARENGRUPPE );
}

static void InitRecord_Artkatg(  )
{
   memset( Buf_Artkatg.BEZEICHNUNG, ' ', L_ARTKATG_BEZEICHNUNG );
}

#ifdef AAA
static long ReadRecord_Artkatg( char *cErrmld )
{
   long lStatus;
   char errmld[200];

   if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

   SetPrimekeyCondition_Artkatg ( );
   lStatus = FdReadRecord( Fd_Artkatg, PrimekeyCond, &Buf_Artkatg, errmld );
   if ( lStatus == 0 )
   {
      BufOld_Artkatg = Buf_Artkatg;  // gelesenen Satz sichern
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
     InitRecord_Artkatg();
     BufOld_Artkatg = Buf_Artkatg;       // initialisierten Satz sichern
   }
   else
      strcpy( cErrmld, errmld );
   lStatus_Artkatg = lStatus;
   return lStatus;
}
#endif

static long DeclReadArtkatg( int *fd, char *errmld )
{
   long s;

#ifdef WP_ALTE_VERSION
   s = SqlDeclareCsWh( fd,
                       "select * from ARTKATG where WARENGRUPPE=?",
                       "ARTKATG.WARENGRUPPE",
                       NULL  );
#else
   char sql[100];
   sprintf( sql, "select %s from ARTKATG where WARENGRUPPE=?",
	             PROJECTION_ARTKATG );

   s = SqlDeclareCsWh( fd, 
	                   sql, 
	                   "ARTKATG.WARENGRUPPE",
                       NULL  );
#endif

   if ( s != 0 )
     sprintf( errmld, "DeclReadTemp: %s", DynErrmld() );
   return s;
}

static long ReadArtkatg( int fd, char *pWgr, char *cErrmld )
{
   long lStatus;
   lStatus = SqlReadDeclCs( fd, &Buf_Artkatg, NULL, pWgr, NULL );
   if ( lStatus == 0 )
   {
      BufOld_Artkatg = Buf_Artkatg;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
     InitRecord_Artkatg();
     BufOld_Artkatg = Buf_Artkatg;       /* initialisierten Satz sichern */
   }
   else
     sprintf( cErrmld, "ReadArtkatg: %s", DynErrmld() );
   lStatus_Artkatg = lStatus;
   return lStatus;
}

static long StoreRecord_Artkatg( char* cErrmld )
{
   long lStatus;
   long lTagesdatum;
   char errmld[200];

   lTagesdatum = PhoToday();
   SetPrimekeyCondition_Artkatg ( );
   if ( lStatus_Artkatg == 100 )
      lStatus = FdInsertRecord( Fd_Artkatg, &Buf_Artkatg,
                                 PrimekeyCond, errmld);
   else if ( lStatus_Artkatg == 0 )
      lStatus = FdUpdateRecord( Fd_Artkatg, &Buf_Artkatg,
                                &BufOld_Artkatg,
                                PrimekeyCond, errmld );
   else
   {
     lStatus = lStatus_Artkatg;
     strcpy( cErrmld, "Interner Fehler" );
   }

	if ((100 == lStatus_Artkatg) || strcmp(Buf_Artkatg.BEZEICHNUNG,BufOld_Artkatg.BEZEICHNUNG ) != 0)
	  lStatus = StoreRecord_Zgrppflege( lTagesdatum, cErrmld );

   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );

   return lStatus;
}

static long DeleteRecord_Artkatg( char *cErrmld )
{
   long lStatus;
   long lTagesdatum;
   char errmld[200];

   lTagesdatum = PhoToday();

   if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

   SetPrimekeyCondition_Artkatg ( );
   lStatus = FdDeleteRecord( Fd_Artkatg, &Buf_Artkatg, PrimekeyCond, errmld );
                                   /* nicht BufOld !!! */

	// Ausgabe zgrppflege für Verteilung mittels tpulzentpfl 
	if (0 == lStatus)
	  lStatus =StoreRecord_Zgrppflege( lTagesdatum, cErrmld );


   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
}



/* ---------- Eintraege aus Artkatg loeschen ----------- */

static long DeclReadTemp( int *fd, char *temp_name, char *errmld )
{
   long s;
   char sql[100];
   char wgr[50];
   sprintf( sql, "select WARENGRUPPE from %s where WARENGRUPPE=?",
                  temp_name );

   sprintf( wgr, "%s.WARENGRUPPE", temp_name );

   s = SqlDeclareCsWh( fd, sql, wgr, NULL  );
   if ( s != 0 )
     sprintf( errmld, "DeclReadTemp: %s", DynErrmld() );
   return s;
}

static long ReadTemp( int fd, char *pWgr, char *errmld )
{
   long s;
   char wgr[L_ARTKATG_WARENGRUPPE + 1];
   s = SqlReadDeclCs( fd, wgr, NULL, pWgr, NULL );
   if ( s != 0 )
     sprintf( errmld, "ReadTemp: %s", DynErrmld() );
   return s;
}

long Loesche_From_Artkatg( char *temp_name, char *errmld )
{
   int fd_sel;
   int fd_read;
   long s;
   char sql[100];

   if (  GetBufferDesc(  errmld ) != 0 )
   {
      return -1;
   }

   if ( DeclReadTemp( &fd_read, temp_name, errmld ) != 0 )
   {
      return -1;
   }

   sprintf( sql, "select %s from ARTKATG order by WARENGRUPPE",
	             PROJECTION_ARTKATG );

   lStatus_Artkatg = SqlOpenCsWh( &fd_sel, sql );
   if ( lStatus_Artkatg != 0 )
   {
      strcpy( errmld, DynErrmld() );
      return lStatus_Artkatg;
   }

   s = 0;
   while ( lStatus_Artkatg == 0 && s == 0 )
   {
     lStatus_Artkatg =  SqlFetch( fd_sel, 1, &Buf_Artkatg, NULL );

     if ( lStatus_Artkatg == 0 )
     {
       s = ReadTemp( fd_read, Buf_Artkatg.WARENGRUPPE, errmld );
       if ( s == 100 )
       {
         s = DeleteRecord_Artkatg( errmld );
/*
         printf( "geloescht: %s %s\n",
                 Buf_Artkatg.WARENGRUPPE, Buf_Artkatg.BEZEICHNUNG );
*/
       }
       else if ( s != 0 )
       {
          strcpy( errmld, DynErrmld() );
       }
     }
     else if ( lStatus_Artkatg != 100 )
     {
       strcpy( errmld, DynErrmld() );
     }
   }

   SqlCloseCs( fd_sel );
   SqlCloseCs( fd_read );

   if ( s != 0 )
      return s;

   if ( lStatus_Artkatg == 100 )
      lStatus_Artkatg = 0;

   return lStatus_Artkatg;
}

/* ---------- Eintraege in Artkatg einfuegen/updaten ----------- */

long Insert_From_Temp( char *temp_name, char *errmld )
{
   int fd_sel;
   int fd_read;
   long s;
   char sql[100];
   struct ARTKATG ims;

   if ( GetBufferDesc( errmld ) != 0 )
   {
      return -1;
   }

   if ( DeclReadArtkatg( &fd_read, errmld ) != 0 )
   {
     return -1;
   }

/* sprintf( sql, "select %s from %s order by WARENGRUPPE", PROJECTION_ARTKATG, temp_name ); */
   sprintf( sql, "select WARENGRUPPE, BEZEICHNUNG from %s order by WARENGRUPPE", temp_name );

   s = SqlOpenCsWh( &fd_sel, sql );
   if ( s != 0 )
   {
      strcpy( errmld, DynErrmld() );
      return s;
   }

   lStatus_Artkatg = 0;
   while ( lStatus_Artkatg == 0 && s == 0 )
   {
     s  =  SqlFetch( fd_sel, 1, &ims, NULL );

     if ( s == 0 )
     {
/*
       strcpy( Buf_Artkatg.WARENGRUPPE, ims.WARENGRUPPE );
       ReadRecord_Artkatg( errmld );
*/
       ReadArtkatg( fd_read, ims.WARENGRUPPE, errmld );
       if ( lStatus_Artkatg == 0 || lStatus_Artkatg == 100 )
       {
			strcpy (Buf_Artkatg.WARENGRUPPE, ims.WARENGRUPPE);
			strcpy (Buf_Artkatg.BEZEICHNUNG, ims.BEZEICHNUNG);

			/* Initialisierung Rabattgruppe bei Neuanlage */
     	    if ( lStatus_Artkatg == 100 )
			{
				strcpy(Buf_Artkatg.RABATTGRUPPE, "");
			}

		   lStatus_Artkatg = StoreRecord_Artkatg( errmld );
/*
          printf( "%s %s\n",
                  Buf_Artkatg.WARENGRUPPE, Buf_Artkatg.BEZEICHNUNG );
*/
       }

     }
     else if ( s != 100 )
     {
       strcpy( errmld, DynErrmld() );
     }
   }

   SqlCloseCs( fd_read );
   SqlCloseCs( fd_sel );

   if ( lStatus_Artkatg != 0 )
     return lStatus_Artkatg;
   if ( s == 100 ) s = 0;
   return s;
}

